#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmCore_DslDsd_Prot.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isFunctionalTesterPresentReceived(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
    return ((Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b) && \
            !(Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b));
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isValidRequestReceived(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
    return(Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b);
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isLowPriorityRequestReceived(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
  return((Dcm_DsldProtocol_pcst[(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8)].nrc21_b)&& \
            (DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8)));
}

static FUNC(void,DCM_CODE)Dcm_Lok_CopyDataToRxBuffer(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr
   ,
   P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr){
    DCM_MEMCOPY(Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr,PduInfoPtr->SduDataPtr
   ,     PduInfoPtr->SduLength);
    Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr += PduInfoPtr->SduLength;
    Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength  -= PduInfoPtr->SduLength;

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
   (void)DcmAppl_CopyRxData(
      DcmRxPduId,
      PduInfoPtr->SduLength);
#endif
   *(RxBufferSizePtr) = Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength;
}

static FUNC(void,DCM_CODE)Dcm_Lok_ProvideRxBufferSize(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,
   P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr){
   VAR(uint8,AUTOMATIC) idxProtocol_u8  = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;
   if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b){
       *(RxBufferSizePtr) = Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength;
   }
   else{
       *(RxBufferSizePtr) = (Type_SwcServiceCom_tLengthPdu)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
   }
}

static FUNC(BufReq_ReturnType,DCM_CODE)Dcm_Lok_ProcessCopyRxData(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr
   ,
   P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr){
   VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   if(FALSE != Dcm_Lok_isValidRequestReceived(
      DcmRxPduId)){
        Dcm_Lok_CopyDataToRxBuffer(DcmRxPduId,PduInfoPtr,RxBufferSizePtr);
        bufRequestStatus_en = BUFREQ_OK;
   }
   else{
      if(FALSE != Dcm_Lok_isLowPriorityRequestReceived(
         DcmRxPduId)){
            SchM_Enter_Dcm_Global_NoNest();
         if(Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 == DCM_SERVICEID_DEFAULT_VALUE){
                Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = (uint8)PduInfoPtr->SduDataPtr[0];
            }
            SchM_Exit_Dcm_Global_NoNest();
            bufRequestStatus_en = BUFREQ_OK;
        }
   }
    return bufRequestStatus_en;
}

static FUNC(boolean,DCM_CODE) Dcm_Lok_CopyRxData_CheckEnvironment(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr
   ,
   P2CONST(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr){
   VAR(boolean,AUTOMATIC) environmentStatus_b = FALSE;
   if(DcmRxPduId >= DCM_CFG_NUM_RX_PDUID){
        DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_DCMRXPDUID_RANGE_EXCEED)
   }
   else if((PduInfoPtr == NULL_PTR) || (RxBufferSizePtr == NULL_PTR)){
        DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_PARAM_POINTER)
   }
   else if((PduInfoPtr->SduLength != 0u) && (PduInfoPtr->SduDataPtr == NULL_PTR)){
        DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_PARAM_POINTER)
   }
   else{
        environmentStatus_b = TRUE;
   }
    return environmentStatus_b;
}

FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyRxData( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr
   ,
   P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr){
   VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   if(FALSE != Dcm_Lok_CopyRxData_CheckEnvironment(
      id,
      PduInfoPtr,
      bufferSizePtr)){
      if(PduInfoPtr->SduLength == 0u){
            Dcm_Lok_ProvideRxBufferSize(id,bufferSizePtr);
            bufRequestStatus_en = BUFREQ_OK;
        }
      else if(FALSE != Dcm_Lok_isFunctionalTesterPresentReceived(
         id)){
            bufRequestStatus_en = BUFREQ_OK;
        }
        else{
            if((PduInfoPtr->SduLength <= Dcm_DslRxPduArray_ast[id].Dcm_DslRxPduBuffer_st.SduLength) || \
                    (FALSE != Dcm_Lok_isLowPriorityRequestReceived(
            id))){
                bufRequestStatus_en = Dcm_Lok_ProcessCopyRxData(id,PduInfoPtr,bufferSizePtr);
            }
            else{
                DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_INTERFACE_BUFFER_OVERFLOW )
            }
        }
   }
    return (bufRequestStatus_en);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
