#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_KWP_PROTOCOL         (0x80u)
#define DCM_KWP_MASK             (0xF0u)

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Type_SwcServiceCom_stInfoPdu,DCM_VAR) Dcm_DsldPduInfo_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_CheckLowPriorityRequestReceived(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
   return (Dcm_DsldProtocol_pcst[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8].nrc21_b);
}

LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_Lok_StartP2Timer(void){
   DCM_TimerStart(
      Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
      (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust),
      Dcm_P2OrS3StartTick_u32,
      Dcm_P2OrS3TimerStatus_uchr)
}

LOCAL_INLINE FUNC(Type_SwcServiceCom_tLengthPdu,DCM_CODE) Dcm_Lok_GetRequestLength(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId)
{
   VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC) RequestLength = Dcm_DsldGlobal_st.dataRequestLength_u16;
   (void)DcmRxPduId;
   return RequestLength;
}

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void, DCM_CODE) Dcm_Lok_ResetCopyRxDataStatus(
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) RxPduId){
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) idxRxPduid;
   for(idxRxPduid = 0; idxRxPduid < DCM_CFG_NUM_RX_PDUID; idxRxPduid++){
      if((idxRxPduid != RxPduId) && (Dcm_DslRxPduArray_ast[idxRxPduid].Dcm_DslCopyRxData_b != FALSE)){
         Dcm_DslRxPduArray_ast[idxRxPduid].Dcm_DslCopyRxData_b = FALSE;
      }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_DiscardRequest(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
,
   VAR(Std_ReturnType, AUTOMATIC) Result){
   if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b){
      (void)DcmAppl_TpRxIndication(
         DcmRxPduId,
         Result);
   }
   Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b = FALSE;
   Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
   if((Dcm_DsldGlobal_st.dataActiveRxPduId_u8 == DcmRxPduId) && (Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_RXINDICATION)){
      Dcm_Lok_SetDslState(
         DSL_STATE_IDLE);
      Dcm_Lok_SetDslSubState(
         DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
      Dcm_Lok_ReloadS3Timer();
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_ReloadP2maxValue(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId,
   VAR(uint8,AUTOMATIC) idxProtocol_u8){
   (void)idxProtocol_u8;
#if((DCM_CFG_KWP_ENABLED == DCM_CFG_OFF) && (DCM_CFG_PROTOCOL_PREMPTION_ENABLED == DCM_CFG_OFF))
   (void)DcmRxPduId;
#endif
}

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessRequest(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
   VAR(uint8,AUTOMATIC) idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;
   Dcm_Lok_ReloadP2maxValue(
      DcmRxPduId,
      idxProtocol_u8);
   if(DcmRxPduId == Dcm_DsldGlobal_st.dataActiveRxPduId_u8){
      Dcm_Lok_SetDslState(
         DSL_STATE_REQUEST_RECEIVED);
      Dcm_Lok_SetDslSubState(
         DSL_SUBSTATE_START_PROTOCOL);
      Dcm_Lok_StartP2Timer();
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SendNrc21(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
   VAR(Type_SwcServiceCom_stInfoPdu,AUTOMATIC) pduInfo_st = {
      NULL_PTR,
      DCM_NEGATIVE_RESPONSE_LENGTH};
   if(DCM_CHKFULLCOMM_MODE(
      Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8)){
      if(E_OK != PduR_DcmTransmit(
         Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].txpduid_num_u8,
         &pduInfo_st)){
         Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
      }
   }
   else{
      DCM_DET_ERROR(
         DCM_TPRXIND_ID,
         DCM_E_FULLCOMM_DISABLED)
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_CheckDiagnosticStatus(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
,
   VAR(uint8,AUTOMATIC) idxProtocol_u8,
   P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) RxBuffer_pu8){
   if(FALSE == Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b){
      if(idxProtocol_u8 == Dcm_DsldGlobal_st.idxCurrentProtocol_u8){
         if((Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX) && (RxBuffer_pu8 != NULL_PTR)){
            Dcm_CheckActiveDiagnosticStatus(
               Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
         }
      }
      else{
         if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
{
            Dcm_CheckActiveDiagnosticStatus(
               Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
         }
      }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_UpdateDSLstate(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
   if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8 == Dcm_DsldGlobal_st.idxCurrentProtocol_u8){
      Dcm_Lok_SetDslState(
         DSL_STATE_IDLE);
      Dcm_Lok_SetDslSubState(
         DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
      Dcm_Lok_ReloadS3Timer();
   }
}

static FUNC(boolean,DCM_CODE) Dcm_Lok_isFunctionalTesterPresentProcessed(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
   VAR(boolean,AUTOMATIC) processStatus_b = FALSE;
   if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b){
      if(FALSE == Dcm_isRequestTobeProcessedByDSP(
         DcmRxPduId)){
         processStatus_b = TRUE;
         Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b = FALSE;
         Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
         if(((Dcm_Lok_GetDslState() == DSL_STATE_IDLE) && (FALSE == Dcm_isFuncTPOnOtherConnection_b)) || (Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED)){
            Dcm_Lok_ReloadS3Timer();
         }
      }
      else{
         if((DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH == Dcm_Lok_GetRequestLength(
            DcmRxPduId)) && (DCM_IS_KWPPROT_ACTIVE() == FALSE) && (DCM_IS_KLINEPROT_ACTIVE() == FALSE)){
            processStatus_b = TRUE;
            Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b = FALSE;
            Dcm_Lok_UpdateDSLstate(
               DcmRxPduId);
         }
      }
   }
   return processStatus_b;
}

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessRxIndication(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId){
   VAR(uint8,AUTOMATIC) idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;
   P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) rxBuffer_pu8 = NULL_PTR;
   rxBuffer_pu8 = Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_mainBuffer_pa;
   Dcm_Lok_CheckDiagnosticStatus(
      DcmRxPduId,
      idxProtocol_u8,
      rxBuffer_pu8);
   if(FALSE == Dcm_isRequestTobeProcessedByDSP(
      DcmRxPduId)){
      if(FALSE == Dcm_Lok_isFunctionalTesterPresentProcessed(
         DcmRxPduId)){
         if(FALSE != Dcm_Lok_CheckLowPriorityRequestReceived(
            DcmRxPduId)){
            Dcm_Lok_SendNrc21(
               DcmRxPduId);
         }
      }
   }
   else{
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
      (void)DcmAppl_TpRxIndication(
         DcmRxPduId,
         E_OK);
#endif
      Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
      if(FALSE == Dcm_Lok_isFunctionalTesterPresentProcessed(
         DcmRxPduId)){
         Dcm_Lok_ProcessRequest(
            DcmRxPduId);
      }
   }
}

FUNC(void,DCM_CODE) Dcm_TpRxIndication(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id,
   VAR(Std_ReturnType, AUTOMATIC) result){
   if(id >= DCM_CFG_NUM_RX_PDUID){
      DCM_DET_ERROR(
         DCM_TPRXINDICATION_ID,
         DCM_E_DCMRXPDUID_RANGE_EXCEED)
   }
   else{
      if(E_OK == result){
         Dcm_Lok_ProcessRxIndication(
            id);
      }
      else{
         Dcm_Lok_DiscardRequest(
            id,
            result);
      }
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
