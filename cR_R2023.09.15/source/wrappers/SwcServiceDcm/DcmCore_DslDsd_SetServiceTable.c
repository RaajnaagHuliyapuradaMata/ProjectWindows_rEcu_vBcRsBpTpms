#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if(RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED !=  DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveServiceTable(VAR(uint8,AUTOMATIC) Sid_tableid_u8){
   VAR(Std_ReturnType,AUTOMATIC) dataReturnValue_u8;
   VAR(uint8,AUTOMATIC) tempNrc_u8;
   VAR(Std_ReturnType,AUTOMATIC) stCancelTx_u8;
   VAR(Dcm_DsdStatesType_ten,AUTOMATIC) DsdState_en = Dcm_Lok_GetDsdState();
   if(DCM_CFG_NUM_SID_TABLE > Sid_tableid_u8){
        if( Dcm_DsldGlobal_st.idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX ){

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
   		(void)SchM_Switch_SwcServiceDcm_tDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
   #endif
#endif

   		Dcm_Lok_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
        }
        if((DsdState_en != DSD_IDLE) && (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp != NULL_PTR)){
            tempNrc_u8 =0x00;
            Dcm_DsldGlobal_st.dataOldtxPduId_u8 = Dcm_DsldGlobal_st.dataActiveTxPduId_u8;
            stCancelTx_u8 = Dcm_Lok_CancelTransmit();
            (void)(*Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp)(DCM_CANCEL,&Dcm_DsldMsgContext_st,&tempNrc_u8);
        }
        Dcm_Lok_SetDsdState(DSD_IDLE);
        SchM_Enter_Dcm_Global_NoNest();
        Dcm_Lok_SetDslState(DSL_STATE_IDLE);
        Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        SchM_Exit_Dcm_Global_NoNest();
        Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Sid_tableid_u8;
        Dcm_DsldSrvTable_pcst = CfgSwcServiceDcm_stDsld.sid_table_pcs[Sid_tableid_u8].ptr_service_table_pcs;
        Dcm_Dsd_ServiceIni(Sid_tableid_u8);
        dataReturnValue_u8 = E_OK;
   }
   else{
        DCM_DET_ERROR(DCM_SETSRVTABLE_ID , DCM_E_SERVICE_TABLE_OUTOFBOUNDS )
        dataReturnValue_u8 = E_NOT_OK;
   }
   return(dataReturnValue_u8);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
