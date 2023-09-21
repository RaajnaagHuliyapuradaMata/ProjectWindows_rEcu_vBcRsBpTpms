#include "Std_Types.hpp"

#include "rba_BswSrv.hpp"
#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR(boolean, AUTOMATIC) Dcm_isNrc21responseSet_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) Dcm_PduInfo_pst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isRetryRequested(P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr
   ,
   P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
   P2VAR(BufReq_ReturnType,AUTOMATIC,DCM_APPL_DATA) RetValPtr){
   VAR(boolean,AUTOMATIC) isRetryRequested_b = FALSE;
   if(RetryInfoPtr != NULL_PTR){
      if(RetryInfoPtr->TpDataState == TP_DATARETRY){
         if((PduInfoPtr->SduDataPtr != NULL_PTR) && (RetryInfoPtr->TxTpDataCnt > 0u)){
                isRetryRequested_b   = TRUE;
            }
            else{
                *RetValPtr = BUFREQ_E_NOT_OK;
            }
        }
   }
    return isRetryRequested_b;
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isNormalResponseAvailable(
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) DcmTxPduId){
   return((CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId] == Dcm_DsldGlobal_st.dataActiveTxPduId_u8) && \
           ((Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_TXCONFIRMATION)  || \
            (Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED))
         );
}

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
static FUNC(boolean,DCM_CODE) Dcm_Lok_isNrc21ResponseAvailable(
   P2VAR(uint16,AUTOMATIC,DCM_APPL_DATA) ServiceIdPtr,
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmTxPduId){
   VAR(boolean, AUTOMATIC) isNrc21Available_b  = FALSE;
   VAR(uint8,AUTOMATIC) connectionId_u8     = 0u;
   VAR(uint8,AUTOMATIC) idxProtocol_u8      = 0u;
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) idxTxpduid_u8   = 0u;
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) idxPduId_u16   = 0u;
   for(idxPduId_u16 = 0; idxPduId_u16 < DCM_CFG_NUM_RX_PDUID; idxPduId_u16++){
      if(DCM_SERVICEID_DEFAULT_VALUE != Dcm_DslRxPduArray_ast[idxPduId_u16].Dcm_DslServiceId_u8){
            *ServiceIdPtr         = Dcm_DslRxPduArray_ast[idxPduId_u16].Dcm_DslServiceId_u8;
            connectionId_u8       = Dcm_DsldRxTable_pcu8[idxPduId_u16];
            idxProtocol_u8        = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;
            idxTxpduid_u8         = Dcm_DsldConnTable_pcst[connectionId_u8].txpduid_num_u8;
            if(( idxTxpduid_u8 == CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId]) &&
                    (FALSE != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b)){
                isNrc21Available_b = TRUE;
                break;
            }
        }
   }
    return isNrc21Available_b;
}

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_ValidateCopyTxDataType (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmTxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr
   ,
   P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr){
   VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   VAR(uint16,AUTOMATIC) serviceId_u16 = 0u;
   if(FALSE != Dcm_Lok_isNormalResponseAvailable(
      DcmTxPduId)){
        Dcm_PduInfo_pst = &Dcm_DsldPduInfo_st;
        bufRequestStatus_en = BUFREQ_OK;
   }
   else{
      if(FALSE != Dcm_Lok_isNrc21ResponseAvailable(
         &serviceId_u16,
         DcmTxPduId)){
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

static FUNC(boolean,DCM_CODE) Dcm_CopyTxData_CheckEnvironment (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmTxPduId
   ,
   P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr){
   VAR(boolean, AUTOMATIC) environmentStatus_b = FALSE;
   if(PduInfoPtr == NULL_PTR){
        DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_PARAM_POINTER )
   }
   else if((PduInfoPtr->SduDataPtr == NULL_PTR) && (PduInfoPtr->SduLength != 0u)){
        DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_PARAM_POINTER )
   }
   else if(DcmTxPduId >= DCM_NUM_TX_PDUID){
        DCM_DET_ERROR(DCM_COPYTXDATA_ID ,DCM_E_DCMTXPDUID_RANGE_EXCEED)
   }
   else{
        environmentStatus_b = TRUE;
   }
    return environmentStatus_b;
}

FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyTxData (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id,
   P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) info,P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) retry
   ,
   P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) availableDataPtr){
   VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   if(FALSE != Dcm_CopyTxData_CheckEnvironment(
      id,
      info)){
        bufRequestStatus_en = Dcm_Lok_ValidateCopyTxDataType(id,info,retry);
      if((BUFREQ_OK == bufRequestStatus_en) && (Dcm_PduInfo_pst != NULL_PTR)){
         if(info->SduLength == 0u){
                *(availableDataPtr ) = Dcm_PduInfo_pst->SduLength;
            }
            else{
            if(FALSE != Dcm_Lok_isRetryRequested(
               retry,
               info,
               &bufRequestStatus_en)){
                    Dcm_PduInfo_pst->SduDataPtr = Dcm_PduInfo_pst->SduDataPtr - retry->TxTpDataCnt;
                    Dcm_PduInfo_pst->SduLength  = Dcm_PduInfo_pst->SduLength  + retry->TxTpDataCnt;
                }
            if((info->SduLength <= Dcm_PduInfo_pst->SduLength) && (BUFREQ_OK == bufRequestStatus_en)){
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
#include "Dcm_Cfg_MemMap.hpp"
