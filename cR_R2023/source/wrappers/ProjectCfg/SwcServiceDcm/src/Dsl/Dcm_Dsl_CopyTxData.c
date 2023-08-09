

#include "rba_BswSrv.h"
#include "DcmCore_DslDsd_Inf.h"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.h"
static VAR(boolean, AUTOMATIC) Dcm_isNrc21responseSet_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
static P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) Dcm_PduInfo_pst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isRetryRequested(P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
        P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,P2VAR(BufReq_ReturnType,AUTOMATIC,DCM_APPL_DATA) RetValPtr)
{
    VAR(boolean,AUTOMATIC) isRetryRequested_b = FALSE;

    if(RetryInfoPtr != NULL_PTR)
    {
        if(RetryInfoPtr->TpDataState == TP_DATARETRY)
        {
            if((PduInfoPtr->SduDataPtr != NULL_PTR) && (RetryInfoPtr->TxTpDataCnt > 0u ))
            {
                isRetryRequested_b   = TRUE;
            }
            else
            {
                *RetValPtr = BUFREQ_E_NOT_OK;
            }
        }
    }

    return isRetryRequested_b;
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isNormalResponseAvailable(VAR(PduIdType,AUTOMATIC) DcmTxPduId)
{
   return((Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId] == Dcm_DsldGlobal_st.dataActiveTxPduId_u8) && \
           ((Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_TXCONFIRMATION)  || \
            (Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED))

         );
}

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isPagedBufferResponseAvailable(VAR(PduIdType,AUTOMATIC) DcmTxPduId)
{
   return((Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId] == Dcm_DsldGlobal_st.dataActiveTxPduId_u8) && \
        (Dcm_Lok_GetDslState() == DSL_STATE_PAGEDBUFFER_TRANSMISSION));
}
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isRoeType2ResponseAvailable(VAR(PduIdType,AUTOMATIC) DcmTxPduId)
{
    return (Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_Roe2MesContext_st.dcmRxPduId]].roetype2_txpdu_u8 == \
            Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId]);
}
#endif

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isCurrentPageTransmitted(VAR(PduLengthType, AUTOMATIC) SduLength,
        P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr)
{
    VAR(boolean,AUTOMATIC) pageStatus_b = FALSE;

    if(SduLength == 0u)
    {
        if(RetryInfoPtr != NULL_PTR)
        {
            if(RetryInfoPtr->TpDataState == TP_DATACONF)
            {
                pageStatus_b = TRUE;
            }
        }
        else
        {
            pageStatus_b = TRUE;
        }
    }

    return pageStatus_b;
}
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_ProcessPagedBufferResponse(
        P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
        P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr)
{
    VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
    VAR(uint8,AUTOMATIC)subStateTemp_u8 = Dcm_Lok_GetDslSubState();

    switch(subStateTemp_u8)
    {
        case DSL_SUBSTATE_DATA_READY :

            if(PduInfoPtr->SduLength <= (PduLengthType)Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32)
            {
                Dcm_DsldPduInfo_st.SduDataPtr = &Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0];
                Dcm_DsldPduInfo_st.SduLength  = (PduLengthType)Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32;

                Dcm_PduInfo_pst = &Dcm_DsldPduInfo_st;

                Dcm_Lok_SetDslState(DSL_STATE_PAGEDBUFFER_TRANSMISSION);
                Dcm_Lok_SetDslSubState(DSL_SUBSTATE_WAIT_PAGE_TXCONFIRM);
                bufRequestStatus_en = BUFREQ_OK;
            }
            else
            {
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
                Dcm_Lok_SetDslState(DSL_STATE_PAGEDBUFFER_TRANSMISSION);
                Dcm_Lok_SetDslSubState(DSL_SUBSTATE_WAIT_FOR_DATA);
                bufRequestStatus_en = BUFREQ_E_BUSY;
            }
            else
            {
                if((Dcm_DsldPduInfo_st.SduLength < PduInfoPtr->SduLength ) && (Dcm_DsldGlobal_st.flgPagedBufferTxOn_b))
                {

                    DCM_MEMSET(& Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0], (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE,
                                    Dcm_DsldPduInfo_st.SduLength);

                    DCM_MEMCOPY(& Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0], Dcm_DsldPduInfo_st.SduDataPtr,
                                    Dcm_DsldPduInfo_st.SduLength);

                    Dcm_Lok_SetDslState(DSL_STATE_PAGEDBUFFER_TRANSMISSION);
                    Dcm_Lok_SetDslSubState(DSL_SUBSTATE_WAIT_FOR_DATA);
                    bufRequestStatus_en = BUFREQ_E_BUSY;
                }
                else
                {

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

static FUNC(boolean,DCM_CODE)Dcm_Lok_isNrc21ResponseAvailable(P2VAR(uint16,AUTOMATIC,DCM_APPL_DATA) ServiceIdPtr,
        VAR(PduIdType, AUTOMATIC) DcmTxPduId)
{
    VAR(boolean, AUTOMATIC) isNrc21Available_b  = FALSE;
    VAR(uint8,AUTOMATIC) connectionId_u8     = 0u;
    VAR(uint8,AUTOMATIC) idxProtocol_u8      = 0u;
    VAR(PduIdType,AUTOMATIC) idxTxpduid_u8   = 0u;
    VAR(PduIdType, AUTOMATIC) idxPduId_u16   = 0u;

    for ( idxPduId_u16 = 0; idxPduId_u16 < DCM_CFG_NUM_RX_PDUID ; idxPduId_u16++ )
    {
        if(DCM_SERVICEID_DEFAULT_VALUE != Dcm_DslRxPduArray_ast[idxPduId_u16].Dcm_DslServiceId_u8)
        {
            *ServiceIdPtr         = Dcm_DslRxPduArray_ast[idxPduId_u16].Dcm_DslServiceId_u8;
            connectionId_u8       = Dcm_DsldRxTable_pcu8[idxPduId_u16];
            idxProtocol_u8        = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;
            idxTxpduid_u8         = Dcm_DsldConnTable_pcst[connectionId_u8].txpduid_num_u8;

            if (( idxTxpduid_u8 == Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId]) &&
                    (FALSE != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b))
            {
                isNrc21Available_b = TRUE;
                break;
            }
        }
    }
    return isNrc21Available_b;
}

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_ValidateCopyTxDataType (VAR(PduIdType, AUTOMATIC) DcmTxPduId,
        P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
        P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr)
{
    VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
    VAR(uint16,AUTOMATIC) serviceId_u16 = 0u;

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
    else
    {
        if(FALSE !=  Dcm_Lok_isNrc21ResponseAvailable(&serviceId_u16,DcmTxPduId))
        {
            Dcm_isNrc21responseSet_b = TRUE;
            bufRequestStatus_en = BUFREQ_OK;

            Dcm_PduInfo_pst->SduLength = DCM_NEGATIVE_RESPONSE_LENGTH;

            *(Dcm_PduInfo_pst->SduDataPtr) = DCM_NEGRESPONSE_INDICATOR;

            *(Dcm_PduInfo_pst->SduDataPtr + 1u) = (uint8)serviceId_u16;

            *(Dcm_PduInfo_pst->SduDataPtr + 2u) = DCM_E_BUSYREPEATREQUEST;
        }
    }

#if(DCM_PAGEDBUFFER_ENABLED == DCM_CFG_OFF)
    (void)PduInfoPtr;
    (void)RetryInfoPtr;
#endif

    return bufRequestStatus_en;
}

static FUNC(boolean,DCM_CODE) Dcm_CopyTxData_CheckEnvironment (VAR(PduIdType, AUTOMATIC) DcmTxPduId,
        P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr)
{

    VAR(boolean, AUTOMATIC) environmentStatus_b = FALSE;

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
    else
    {
        environmentStatus_b = TRUE;
    }
    return environmentStatus_b;
}

FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyTxData (VAR(PduIdType, AUTOMATIC) id,

    P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) retry,
    P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) availableDataPtr )
{
    VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;

    if(FALSE != Dcm_CopyTxData_CheckEnvironment(id,info))
    {
        bufRequestStatus_en = Dcm_Lok_ValidateCopyTxDataType(id,info,retry);

        if((BUFREQ_OK == bufRequestStatus_en) && (Dcm_PduInfo_pst != NULL_PTR))
        {
            if (info->SduLength == 0u)
            {
                *(availableDataPtr ) = Dcm_PduInfo_pst->SduLength;
            }
            else
            {
                if(FALSE != Dcm_Lok_isRetryRequested(retry,info,&bufRequestStatus_en))
                {
                    Dcm_PduInfo_pst->SduDataPtr = Dcm_PduInfo_pst->SduDataPtr - retry->TxTpDataCnt;
                    Dcm_PduInfo_pst->SduLength  = Dcm_PduInfo_pst->SduLength  + retry->TxTpDataCnt;
                }

                if((info->SduLength <= Dcm_PduInfo_pst->SduLength) && (BUFREQ_OK == bufRequestStatus_en))
                {

                    DCM_MEMCOPY(info->SduDataPtr, Dcm_PduInfo_pst->SduDataPtr, info->SduLength);

                    Dcm_PduInfo_pst->SduDataPtr = Dcm_PduInfo_pst->SduDataPtr + info->SduLength;

                    Dcm_PduInfo_pst->SduLength = (uint16)((uint16)Dcm_PduInfo_pst->SduLength - \
                            (uint16)((FALSE != Dcm_isNrc21responseSet_b) ? 0u : info->SduLength));

                    *(availableDataPtr ) = Dcm_PduInfo_pst->SduLength;
                }
            }
        }
    }
    return(bufRequestStatus_en);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
