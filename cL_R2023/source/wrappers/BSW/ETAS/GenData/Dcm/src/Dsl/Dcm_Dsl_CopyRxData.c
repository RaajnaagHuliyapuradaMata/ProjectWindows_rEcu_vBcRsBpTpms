
#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "DcmCore_DslDsd_Prot.h"
#include "Rte_Dcm.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

LOCAL_INLINE boolean Dcm_Lok_isFunctionalTesterPresentReceived(PduIdType DcmRxPduId)
{
    return ((Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b) && \
            !(Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b));
}

LOCAL_INLINE boolean Dcm_Lok_isValidRequestReceived(PduIdType DcmRxPduId)
{
    return(Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b);
}

LOCAL_INLINE boolean Dcm_Lok_isLowPriorityRequestReceived(PduIdType DcmRxPduId)
{
  return((Dcm_DsldProtocol_pcst[(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8)].nrc21_b)&& \
            (DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8)));
}

static void Dcm_Lok_CopyDataToRxBuffer(PduIdType DcmRxPduId,
        const PduInfoType * PduInfoPtr,
        PduLengthType * RxBufferSizePtr)
{

    DCM_MEMCOPY(Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr,PduInfoPtr->SduDataPtr,
            PduInfoPtr->SduLength);

    Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr += PduInfoPtr->SduLength;
    Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength  -= PduInfoPtr->SduLength;

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
    #if(DCM_BUFQUEUE_ENABLED !=DCM_CFG_OFF)
        if(Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE)
    #endif
        {
            (void)DcmAppl_CopyRxData(DcmRxPduId,PduInfoPtr->SduLength);
        }
#endif

   *(RxBufferSizePtr) = Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength;
}

static void Dcm_Lok_ProvideRxBufferSize(PduIdType DcmRxPduId,
        PduLengthType * RxBufferSizePtr)
{
    uint8 idxProtocol_u8  = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

    if (FALSE !=  Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
    {

       *(RxBufferSizePtr) = Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength;
    }
    else
    {

       *(RxBufferSizePtr) = (PduLengthType)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
    }
}

static BufReq_ReturnType Dcm_Lok_ProcessCopyRxData(PduIdType DcmRxPduId,
        const PduInfoType * PduInfoPtr,
        PduLengthType * RxBufferSizePtr)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;

    if (FALSE != Dcm_Lok_isValidRequestReceived(DcmRxPduId))
    {
        Dcm_Lok_CopyDataToRxBuffer(DcmRxPduId,PduInfoPtr,RxBufferSizePtr);
        bufRequestStatus_en = BUFREQ_OK;
    }
    else
    {
        if(FALSE != Dcm_Lok_isLowPriorityRequestReceived(DcmRxPduId))
        {

            SchM_Enter_Dcm_Global_NoNest();
            if (Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 == DCM_SERVICEID_DEFAULT_VALUE)
            {
                Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = (uint8)PduInfoPtr->SduDataPtr[0];
            }
            SchM_Exit_Dcm_Global_NoNest();

            bufRequestStatus_en = BUFREQ_OK;
        }
    }

    return bufRequestStatus_en;
}

static boolean Dcm_Lok_CopyRxData_CheckEnvironment(PduIdType DcmRxPduId,
        const PduInfoType * PduInfoPtr,
        const PduLengthType * RxBufferSizePtr)
{
    boolean environmentStatus_b = FALSE;

    if (DcmRxPduId >= DCM_CFG_NUM_RX_PDUID)
    {
        DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_DCMRXPDUID_RANGE_EXCEED)
    }
    else if ((PduInfoPtr == NULL_PTR) || (RxBufferSizePtr == NULL_PTR))
    {
        DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_PARAM_POINTER)
    }
    else if( (PduInfoPtr->SduLength != 0u) && (PduInfoPtr->SduDataPtr == NULL_PTR))
    {
        DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_PARAM_POINTER)
    }
    else
    {
        environmentStatus_b = TRUE;
    }

    return environmentStatus_b;
}

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_ProvideOBDRxBufferSize(PduIdType DcmRxPduId,PduLengthType* RxBufferSizePtr)
{
    uint8 idxProtocol_u8;

    if (FALSE !=  Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
    {

       *(RxBufferSizePtr) = Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength;
    }
    else
    {

        idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;
       *(RxBufferSizePtr) = (PduLengthType)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
    }
}

static void Dcm_Lok_CopyOBDDataToRxBuffer(PduIdType DcmRxPduId, const PduInfoType* PduInfoPtr,
                                                      PduLengthType* RxBufferSizePtr)
{

    DCM_MEMCOPY(Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr,PduInfoPtr->SduDataPtr,
                PduInfoPtr->SduLength);
    Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr += PduInfoPtr->SduLength;
    Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength  -= PduInfoPtr->SduLength;

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
   (void)DcmAppl_CopyRxData(DcmRxPduId,PduInfoPtr->SduLength);
#endif
   *(RxBufferSizePtr) = Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength;
}

static BufReq_ReturnType Dcm_Lok_CheckOBDRxData(PduIdType DcmRxPduId, const PduInfoType* PduInfoPtr,
                                                      PduLengthType* RxBufferSizePtr)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;

    if (FALSE != Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
    {
        Dcm_Lok_CopyOBDDataToRxBuffer(DcmRxPduId,PduInfoPtr,RxBufferSizePtr);
        bufRequestStatus_en = BUFREQ_OK;
    }
    else
    {
        if(FALSE != Dcm_Lok_isLowPriorityRequestReceived(DcmRxPduId))
        {

            SchM_Enter_Dcm_Global_NoNest();
            if (Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 == DCM_SERVICEID_DEFAULT_VALUE)
            {
                Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = (uint8)PduInfoPtr->SduDataPtr[0];
            }
            SchM_Exit_Dcm_Global_NoNest();
            bufRequestStatus_en = BUFREQ_OK;
        }
    }
    return bufRequestStatus_en;
}

static BufReq_ReturnType Dcm_Lok_OBDCopyRxData(PduIdType DcmRxPduId,
       const PduInfoType* PduInfoPtr, PduLengthType* RxBufferSizePtr)
{
    BufReq_ReturnType Result = BUFREQ_E_NOT_OK;
    if(PduInfoPtr->SduLength == 0u)
    {
        Dcm_Lok_ProvideOBDRxBufferSize(DcmRxPduId,RxBufferSizePtr);
        Result = BUFREQ_OK;
    }
    else
    {
        if((PduInfoPtr->SduLength <= Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength) ||
                (Dcm_Lok_isLowPriorityRequestReceived(DcmRxPduId)))
        {
            Result = Dcm_Lok_CheckOBDRxData(DcmRxPduId,PduInfoPtr,RxBufferSizePtr);
        }
        else
        {
            DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_INTERFACE_BUFFER_OVERFLOW)
        }
    }
    return Result;
}

#endif

BufReq_ReturnType Dcm_CopyRxData( PduIdType id,
    const PduInfoType * PduInfoPtr,
    PduLengthType * bufferSizePtr)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;

    if(FALSE != Dcm_Lok_CopyRxData_CheckEnvironment(id,PduInfoPtr,bufferSizePtr))
    {

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
        if ((NULL_PTR != PduInfoPtr->SduDataPtr) && (FALSE != Dcm_isObdRequestReceived_b))
        {
            if(FALSE != Dcm_Lok_isRxPduShared(id,PduInfoPtr->SduDataPtr[0]))
            {
                id = (DCM_CFG_NUM_RX_PDUID-1u);
            }
        }
#endif
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
        if(Dcm_Lok_IsRxPduIdOBD(id))
        {
            bufRequestStatus_en = Dcm_Lok_OBDCopyRxData(id,PduInfoPtr,bufferSizePtr);
        }
        else
#endif
        {

            if(PduInfoPtr->SduLength == 0u)
            {
                Dcm_Lok_ProvideRxBufferSize(id,bufferSizePtr);
                bufRequestStatus_en = BUFREQ_OK;
            }
            else if(FALSE != Dcm_Lok_isFunctionalTesterPresentReceived(id))
            {
                bufRequestStatus_en = BUFREQ_OK;
            }
            else
            {

                if((PduInfoPtr->SduLength <= Dcm_DslRxPduArray_ast[id].Dcm_DslRxPduBuffer_st.SduLength) || \
                        (FALSE != Dcm_Lok_isLowPriorityRequestReceived(id)))
                {
                    bufRequestStatus_en = Dcm_Lok_ProcessCopyRxData(id,PduInfoPtr,bufferSizePtr);
                }
                else
                {
                    DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_INTERFACE_BUFFER_OVERFLOW )
                }
            }
        }
    }
    return (bufRequestStatus_en);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
