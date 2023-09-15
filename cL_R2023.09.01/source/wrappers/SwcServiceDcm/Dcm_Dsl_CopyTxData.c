

#include "rba_BswSrv.hpp"
#include "DcmCore_DslDsd_Inf.hpp"
#include "Dcm_Dsd_Prv.hpp"
#include "Rte_Dcm.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static boolean Dcm_isNrc21responseSet_b;
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
static boolean Dcm_isOBDNrc21responseSet_b; // Nrc 21 to be sent for an OBD request
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static uint8 adrDataPtr_u8[3];
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
static uint8 ObdadrDataPtr_u8[3];
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static PduInfoType Dcm_adrDataPtr_pst;
static PduInfoType * Dcm_PduInfo_pst;
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
static PduInfoType Dcm_ObdadrDataPtr_pst;
static PduInfoType* Dcm_ObdPduInfo_pst;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

LOCAL_INLINE boolean Dcm_Lok_isRetryRequested(const RetryInfoType * RetryInfoPtr
   ,       const PduInfoType * PduInfoPtr,BufReq_ReturnType * RetValPtr)
{
   boolean isRetryRequested_b = FALSE;

   if(RetryInfoPtr != NULL_PTR)
   {
        if(RetryInfoPtr->TpDataState == TP_DATARETRY)
        {
            if((PduInfoPtr->SduDataPtr != NULL_PTR) && (RetryInfoPtr->TxTpDataCnt > 0u ))
            {
                isRetryRequested_b   = TRUE;
            }
            else{
                *RetValPtr = BUFREQ_E_NOT_OK;
            }
        }
   }

    return isRetryRequested_b;
}

LOCAL_INLINE boolean Dcm_Lok_isNormalResponseAvailable(PduIdType DcmTxPduId)
{
   return((CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId] == Dcm_DsldGlobal_st.dataActiveTxPduId_u8) && \
           ((Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_TXCONFIRMATION)  || \
            (Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED))

         );
}

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE boolean Dcm_Lok_isPagedBufferResponseAvailable(PduIdType DcmTxPduId)
{
   return((CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId] == Dcm_DsldGlobal_st.dataActiveTxPduId_u8) && \
        (Dcm_Lok_GetDslState() == DSL_STATE_PAGEDBUFFER_TRANSMISSION));
}
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE boolean Dcm_Lok_isRoeType2ResponseAvailable(PduIdType DcmTxPduId)
{
    return (Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_Roe2MesContext_st.dcmRxPduId]].roetype2_txpdu_u8 == \
            CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId]);
}
#endif

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE boolean Dcm_Lok_isCurrentPageTransmitted(PduLengthType SduLength
   ,       const RetryInfoType * RetryInfoPtr)
{
   boolean pageStatus_b = FALSE;

   if(SduLength == 0u)
   {
        if(RetryInfoPtr != NULL_PTR)
        {
            if(RetryInfoPtr->TpDataState == TP_DATACONF)
            {
                pageStatus_b = TRUE;
            }
        }
        else{
            pageStatus_b = TRUE;
        }
   }

    return pageStatus_b;
}
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

static BufReq_ReturnType Dcm_Lok_ProcessPagedBufferResponse(
        const PduInfoType * PduInfoPtr
   ,       const RetryInfoType * RetryInfoPtr)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   uint8 subStateTemp_u8 = Dcm_Lok_GetDslSubState();

   switch(subStateTemp_u8)
   {
        case DSL_SUBSTATE_DATA_READY :

            if(PduInfoPtr->SduLength <= (PduLengthType)Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32)
            {
                Dcm_DsldPduInfo_st.SduDataPtr = &Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0];
                Dcm_DsldPduInfo_st.SduLength  = (PduLengthType)Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32;

                Dcm_PduInfo_pst = &Dcm_DsldPduInfo_st;

                Dcm_Lok_SetDslState((DSL_STATE_PAGEDBUFFER_TRANSMISSION));
                Dcm_Lok_SetDslSubState((DSL_SUBSTATE_WAIT_PAGE_TXCONFIRM));
                bufRequestStatus_en = BUFREQ_OK;
            }
            else{
                bufRequestStatus_en = BUFREQ_E_NOT_OK;
                DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_INVALID_LENGTH )
            }
            break;

        case DSL_SUBSTATE_WAIT_FOR_DATA :

            bufRequestStatus_en = BUFREQ_E_BUSY;
            break;

        case DSL_SUBSTATE_WAIT_PAGE_TXCONFIRM :

            if(FALSE != Dcm_Lok_isCurrentPageTransmitted(Dcm_DsldPduInfo_st.SduLength,RetryInfoPtr))
            {
                Dcm_Lok_SetDslState((DSL_STATE_PAGEDBUFFER_TRANSMISSION));
                Dcm_Lok_SetDslSubState((DSL_SUBSTATE_WAIT_FOR_DATA));
                bufRequestStatus_en = BUFREQ_E_BUSY;
            }
            else{
                if((Dcm_DsldPduInfo_st.SduLength < PduInfoPtr->SduLength ) && (Dcm_DsldGlobal_st.flgPagedBufferTxOn_b))
                {

                    DCM_MEMSET(& Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0], (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE
   ,                                   Dcm_DsldPduInfo_st.SduLength);

                    DCM_MEMCOPY(& Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0], Dcm_DsldPduInfo_st.SduDataPtr
   ,                                   Dcm_DsldPduInfo_st.SduLength);

                    Dcm_Lok_SetDslState((DSL_STATE_PAGEDBUFFER_TRANSMISSION));
                    Dcm_Lok_SetDslSubState((DSL_SUBSTATE_WAIT_FOR_DATA));
                    bufRequestStatus_en = BUFREQ_E_BUSY;
                }
                else{

                    Dcm_PduInfo_pst = &Dcm_DsldPduInfo_st;
                    bufRequestStatus_en = BUFREQ_OK;
                }
            }
            break;

        default :

            break;

   }
    return bufRequestStatus_en;
}
#endif

static boolean Dcm_Lok_isNrc21ResponseAvailable(uint16 * ServiceIdPtr
   ,       PduIdType DcmTxPduId)
{
   boolean isNrc21Available_b  = FALSE;
   uint8 connectionId_u8     = 0u;
   uint8 idxProtocol_u8      = 0u;
   PduIdType idxTxpduid_u8   = 0u;
   PduIdType idxPduId_u16   = 0u;

   for( idxPduId_u16 = 0; idxPduId_u16 < DCM_CFG_NUM_RX_PDUID ; idxPduId_u16++ )
   {
        if(DCM_SERVICEID_DEFAULT_VALUE != Dcm_DslRxPduArray_ast[idxPduId_u16].Dcm_DslServiceId_u8)
        {
            *ServiceIdPtr         = Dcm_DslRxPduArray_ast[idxPduId_u16].Dcm_DslServiceId_u8;
            connectionId_u8       = Dcm_DsldRxTable_pcu8[idxPduId_u16];
            idxProtocol_u8        = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;
            idxTxpduid_u8         = Dcm_DsldConnTable_pcst[connectionId_u8].txpduid_num_u8;

            if(( idxTxpduid_u8 == CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId]) &&
                    (FALSE != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b))
            {
                isNrc21Available_b = TRUE;
                break;
            }
        }
   }
    return isNrc21Available_b;
}

#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
static boolean Dcm_Lok_OBDisNrc21ResponseAvailable(uint8* ServiceIdPtr,PduIdType DcmTxPduId)
{
   boolean isNrc21Available_b = FALSE;
   uint8 connectionId_u8 = 0u;
   uint8 idxProtocol_u8 = 0u;
   PduIdType idxTxpduid_u8 = 0u;
   PduIdType idxPduId_u16 = 0u;

   for(idxPduId_u16 = 0; idxPduId_u16 < DCM_CFG_NUM_RX_PDUID; idxPduId_u16++)
   {
        if(DCM_SERVICEID_DEFAULT_VALUE != Dcm_DslOBDRxPduArray_ast[idxPduId_u16].Dcm_DslServiceId_u8)
        {
            *ServiceIdPtr = Dcm_DslOBDRxPduArray_ast[idxPduId_u16].Dcm_DslServiceId_u8;
            connectionId_u8 = Dcm_DsldRxTable_pcu8[idxPduId_u16];
            idxProtocol_u8 = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;
            idxTxpduid_u8 = Dcm_DsldConnTable_pcst[connectionId_u8].txpduid_num_u8;

            if((idxTxpduid_u8 == CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId]) &&
            (FALSE != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b))
            {
                isNrc21Available_b = TRUE;
                break;
            }
        }
   }
    return isNrc21Available_b;
}
#endif

static BufReq_ReturnType Dcm_Lok_ValidateCopyTxDataType (PduIdType DcmTxPduId
   ,       const PduInfoType * PduInfoPtr
   ,       const RetryInfoType * RetryInfoPtr)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   uint16 serviceId_u16 = 0u;

    Dcm_isNrc21responseSet_b = FALSE;

   if(FALSE != Dcm_Lok_isNormalResponseAvailable(DcmTxPduId))
   {
        Dcm_PduInfo_pst = &Dcm_DsldPduInfo_st;
        bufRequestStatus_en = BUFREQ_OK;
   }
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
   else if(FALSE != Dcm_Lok_isPagedBufferResponseAvailable(DcmTxPduId))
   {
        bufRequestStatus_en = Dcm_Lok_ProcessPagedBufferResponse(PduInfoPtr,RetryInfoPtr);
   }
#endif
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
   else if(FALSE != Dcm_Lok_isRoeType2ResponseAvailable(DcmTxPduId))
   {
        Dcm_PduInfo_pst = &Dcm_DsldRoe2PduInfo_st;
        bufRequestStatus_en = BUFREQ_OK;
   }
#endif
   else{
        if(FALSE !=  Dcm_Lok_isNrc21ResponseAvailable(&serviceId_u16,DcmTxPduId))
        {

            Dcm_isNrc21responseSet_b = TRUE;
            bufRequestStatus_en = BUFREQ_OK;

            adrDataPtr_u8[0] = DCM_NEGRESPONSE_INDICATOR;
            adrDataPtr_u8[1] = (uint8)serviceId_u16;
            adrDataPtr_u8[2] = DCM_E_BUSYREPEATREQUEST;

            Dcm_adrDataPtr_pst.SduLength = DCM_NEGATIVE_RESPONSE_LENGTH;
            Dcm_adrDataPtr_pst.SduDataPtr = &adrDataPtr_u8[0];

            Dcm_PduInfo_pst = &Dcm_adrDataPtr_pst;

        }
   }

#if(DCM_PAGEDBUFFER_ENABLED == DCM_CFG_OFF)
    (void)PduInfoPtr;
    (void)RetryInfoPtr;
#endif

    return bufRequestStatus_en;
}

#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
static BufReq_ReturnType Dcm_Lok_OBDValidateCopyTxDataType(PduIdType DcmTxPduId)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   uint8 serviceId_u8 = 0u;

    Dcm_isOBDNrc21responseSet_b = FALSE;

   if( (CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId] == Dcm_OBDGlobal_st.dataActiveTxPduId_u8)
        && (Dcm_Lok_GetOBDState() == DCM_OBD_WAITFORTXCONF) )
   {
        Dcm_ObdPduInfo_pst = &Dcm_OBDPduInfo_st;
        bufRequestStatus_en = BUFREQ_OK;
   }
   else{
        if(FALSE != Dcm_Lok_OBDisNrc21ResponseAvailable(&serviceId_u8,DcmTxPduId))
        {

            Dcm_isOBDNrc21responseSet_b = TRUE;
            bufRequestStatus_en = BUFREQ_OK;

            ObdadrDataPtr_u8[0] = DCM_NEGRESPONSE_INDICATOR;
            ObdadrDataPtr_u8[1] = serviceId_u8;
            ObdadrDataPtr_u8[2] = DCM_E_BUSYREPEATREQUEST;

            Dcm_ObdadrDataPtr_pst.SduLength = DCM_NEGATIVE_RESPONSE_LENGTH;
            Dcm_ObdadrDataPtr_pst.SduDataPtr = &ObdadrDataPtr_u8[0];

            Dcm_ObdPduInfo_pst = &Dcm_ObdadrDataPtr_pst;
        }
   }
    return bufRequestStatus_en;
}
#endif

static boolean Dcm_CopyTxData_CheckEnvironment (PduIdType DcmTxPduId
   ,       const PduInfoType * PduInfoPtr)
{

   boolean environmentStatus_b = FALSE;

   if(PduInfoPtr == NULL_PTR)
   {
        DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_PARAM_POINTER )
   }
   else if((PduInfoPtr->SduDataPtr == NULL_PTR) && (PduInfoPtr->SduLength != 0u))
   {
        DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_PARAM_POINTER )
   }
   else if( DcmTxPduId >= DCM_NUM_TX_PDUID )
   {
        DCM_DET_ERROR(DCM_COPYTXDATA_ID ,DCM_E_DCMTXPDUID_RANGE_EXCEED)
   }
   else{
        environmentStatus_b = TRUE;
   }
    return environmentStatus_b;
}

BufReq_ReturnType Dcm_CopyTxData(PduIdType id,

const PduInfoType * info,RetryInfoType * retry,
PduLengthType * availableDataPtr )
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   PduInfoType* TempPduInfo_pst;
   boolean isNrc21ResponseSet;

#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
   boolean context = (Dcm_Lok_IsTxPduIdOBD(id)?DCM_OBDCONTEXT:DCM_UDSCONTEXT);
#endif

   if(FALSE != Dcm_CopyTxData_CheckEnvironment(id,info))
   {
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
        if(context == DCM_OBDCONTEXT)
        {
            bufRequestStatus_en = Dcm_Lok_OBDValidateCopyTxDataType(id);
            isNrc21ResponseSet = Dcm_isOBDNrc21responseSet_b;
            TempPduInfo_pst = Dcm_ObdPduInfo_pst;
        }
        else
#endif
        {
            bufRequestStatus_en = Dcm_Lok_ValidateCopyTxDataType(id,info,retry);
            isNrc21ResponseSet = Dcm_isNrc21responseSet_b;
            TempPduInfo_pst = Dcm_PduInfo_pst;
        }

        if((BUFREQ_OK == bufRequestStatus_en) && (TempPduInfo_pst != NULL_PTR))
        {
            if(info->SduLength == 0u)
            {
                *(availableDataPtr ) = TempPduInfo_pst->SduLength;
            }
            else{
                if(FALSE != Dcm_Lok_isRetryRequested(retry,info,&bufRequestStatus_en))
                {
                    TempPduInfo_pst->SduDataPtr = TempPduInfo_pst->SduDataPtr - retry->TxTpDataCnt;
                    TempPduInfo_pst->SduLength = TempPduInfo_pst->SduLength + retry->TxTpDataCnt;
                }

                if((info->SduLength <= TempPduInfo_pst->SduLength) && (BUFREQ_OK == bufRequestStatus_en))
                {

                    DCM_MEMCOPY(info->SduDataPtr, TempPduInfo_pst->SduDataPtr, info->SduLength);
                    TempPduInfo_pst->SduDataPtr = TempPduInfo_pst->SduDataPtr + info->SduLength;
                    TempPduInfo_pst->SduLength = (uint16)((uint16)TempPduInfo_pst->SduLength -  \
                    (uint16)((FALSE != isNrc21ResponseSet) ? 0u : info->SduLength));

                    *(availableDataPtr ) = TempPduInfo_pst->SduLength;
                }
            }
        }
   }
    return(bufRequestStatus_en);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
