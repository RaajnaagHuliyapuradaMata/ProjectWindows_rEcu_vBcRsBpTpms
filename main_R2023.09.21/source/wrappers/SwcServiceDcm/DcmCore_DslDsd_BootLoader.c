#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

VAR(Dcm_BootLoaderStates_ten,DCM_VAR) Dcm_BootLoaderState_en;
static VAR(Dcm_OpStatusType,     AUTOMATIC) s_Dcm_SetProgCondOpstatus_u8;
static VAR(Std_ReturnType,DCM_VAR) Dcm_StoreReturnValue_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
static FUNC(Std_ReturnType,DCM_CODE) Dcm_TimerRemaining(VAR(uint32,AUTOMATIC)timer,VAR(uint32,AUTOMATIC)startTime,P2VAR(Std_ReturnType,DCM_INTERN_DATA,AUTOMATIC)timerStatus);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_SendForcedResponsePend(void);
static FUNC(void, DCM_CODE) Dcm_InvokeSetProgCondition(P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) flag_b, P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);

FUNC(void,DCM_CODE) Dcm_JumpToBootLoader(VAR(uint8,AUTOMATIC) dataBootType_u8, P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8){
   VAR(uint8,     AUTOMATIC) dataProtocolId_u8;
   VAR(Dcm_SesCtrlType,  AUTOMATIC) dataSessionId_u8;
   VAR(Dcm_SecLevelType, AUTOMATIC) dataSecurityLevel_u8;
   VAR(Std_ReturnType,   AUTOMATIC) dataReturnValue_u8;
   VAR(boolean,     AUTOMATIC) flgProcessSrv_b;
   VAR(uint8,     AUTOMATIC) serviceId;

#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))
   VAR(uint8,     AUTOMATIC) idxSeca_qu8;
#endif

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
   VAR(uint16,     AUTOMATIC) dataTimingValue_u16;
#endif

   flgProcessSrv_b  = FALSE;
   Dcm_StoreReturnValue_u8 = E_OK;
   serviceId = Dcm_DsldGlobal_st.dataSid_u8;
   if(Dcm_BootLoaderState_en == DCM_BOOT_IDLE){
      Dcm_ProgConditions_st.StoreType = DcmAppl_DcmGetStoreType(dataBootType_u8,serviceId);
      if((Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE)||
                (Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE)||
                (Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE)
      ){
                if(dataBootType_u8 == DCM_JUMPTOOEMBOOTLOADER){
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (void)SchM_Switch_SwcServiceDcm_tEcuReset(RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER);
#endif
                    (void)DcmAppl_Switch_DcmBootLoaderReset();
                }
                else if(dataBootType_u8 == DCM_JUMPTOSYSSUPPLIERBOOTLOADER){
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (void)SchM_Switch_SwcServiceDcm_tEcuReset(RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER);
#endif
                    (void)DcmAppl_Switch_DcmSysSupplierReset();
                }
                else if(dataBootType_u8 == DCM_JUMPDRIVETODRIVE){
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
                    if(Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE){
                    }
                    else{
                        Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }
#endif
                }
                else{
                }
                if(Dcm_BootLoaderState_en != DCM_BOOT_ERROR){
                    if(CfgSwcServiceDcm_stDsld.protocol_table_pcs[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].sendRespPendTransToBoot){
                        Dcm_BootLoaderState_en = DCM_BOOT_SENDFORCEDRESPPEND;
                    }
                    else{
                        if(Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE){
                            Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMREQ;
                        }
                        else if(Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE){
                            Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMRESP;
                        }
                        else{
                            Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMINIT;
                        }
                    }
            }
        }
        else{
            flgProcessSrv_b  = TRUE;
        }
   }
   if((Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMREQ) ||
            (Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMRESP)||
            (Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT)){
        if(DCM_INITIAL==s_Dcm_SetProgCondOpstatus_u8){
            dataReturnValue_u8 = Dcm_GetActiveProtocol(&dataProtocolId_u8);
            if(dataProtocolId_u8 != DCM_NO_ACTIVE_PROTOCOL){
                dataReturnValue_u8 = Dcm_GetSesCtrlType(&dataSessionId_u8);
                if(dataReturnValue_u8 == E_OK){
                    dataReturnValue_u8 = Dcm_GetSecurityLevel(&dataSecurityLevel_u8);
                    if(dataReturnValue_u8 == E_OK){
                        Dcm_ProgConditions_st.Sid              = Dcm_DsldGlobal_st.dataSid_u8;
                        Dcm_ProgConditions_st.SecurityLevel    = dataSecurityLevel_u8;
                        Dcm_ProgConditions_st.SessionLevel     = dataSessionId_u8;
                        Dcm_ProgConditions_st.ProtocolId       = dataProtocolId_u8;
                        Dcm_ProgConditions_st.TesterSourceAddr = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16;
                        Dcm_ProgConditions_st.ReqResLen        = 0x1;
                        Dcm_ProgConditions_st.NumWaitPend      = Dcm_DsldGlobal_st.cntrWaitpendCounter_u8;

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
                        Dcm_ProgConditions_st.ElapsedTime      = (uint32)(Dcm_Dsp_SecaGlobaltimer_u32 * (uint32)(DCM_CFG_TASK_TIME_US/1000u));
#else
                        Dcm_ProgConditions_st.ElapsedTime      = 0x0;
#endif

#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))
                        Dcm_ProgConditions_st.NumOfSecurityLevels = DCM_CFG_DSP_NUMSECURITY;
                        for(idxSeca_qu8 = 0x0; idxSeca_qu8 < DCM_CFG_DSP_NUMSECURITY; idxSeca_qu8++){
                            Dcm_ProgConditions_st.SecurityInformation[idxSeca_qu8].SecurityLevel = Dcm_Dsp_Security[idxSeca_qu8].Security_level_u8;
                            Dcm_ProgConditions_st.SecurityInformation[idxSeca_qu8].DelayCount = Dcm_Dsp_Seca[idxSeca_qu8].FailedAtm_cnt_u8;
                            if(Dcm_Dsp_Seca[idxSeca_qu8].Residual_delay_u32>Dcm_Dsp_SecaGlobaltimer_u32){
                                Dcm_ProgConditions_st.SecurityInformation[idxSeca_qu8].ResidualDelay = (Dcm_Dsp_Seca[idxSeca_qu8].Residual_delay_u32 - Dcm_Dsp_SecaGlobaltimer_u32)*DCM_CFG_TASK_TIME_MS;
                            }
                            else{
                                Dcm_ProgConditions_st.SecurityInformation[idxSeca_qu8].ResidualDelay = 0;
                            }
                        }
#endif

                        if((Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMRESP)||
                                (Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMREQ)){
                            Dcm_ProgConditions_st.ResponseRequired=TRUE;
                        }
                        else{
                          if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT){
                              Dcm_ProgConditions_st.ResponseRequired= FALSE;
                          }
                        }
                        if(Dcm_ProgConditions_st.Sid == DCM_DSP_SID_DIAGNOSTICSESSIONCONTROL){
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT){
                                Dcm_ProgConditions_st.ReprogramingRequest = TRUE;
                            }
#endif
                        }
                        if(Dcm_ProgConditions_st.Sid == DCM_DSP_SID_ECURESET){
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
                            if((Dcm_stEcuResetState_en == DCM_ECURESET_WAIT)&& (dataBootType_u8 != DCM_JUMPDRIVETODRIVE)){
                                Dcm_ProgConditions_st.ReprogramingRequest = TRUE;
                            }
                            else{
                                Dcm_ProgConditions_st.ReprogramingRequest = FALSE;
                            }
#endif
                        }
                        if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMREQ){
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT){
                                Dcm_ProgConditions_st.SubFncId  = Dcm_ReqSess_u8;
                                Dcm_ProgConditions_st.ReqResLen = 0x2;
                            }
#endif
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT){
                                Dcm_ProgConditions_st.SubFncId  = Dcm_dataEcuRType_u8;
                                Dcm_ProgConditions_st.ReqResLen = 0x2;
                            }
#endif
                        }
                        if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMRESP){
                            Dcm_ProgConditions_st.Sid = Dcm_DsldGlobal_st.dataSid_u8|0x40u;
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT){
                                Dcm_ProgConditions_st.SubFncId  = Dcm_ReqSess_u8;
                                Dcm_ProgConditions_st.ReqResLen = 0x2;
#if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
                                dataTimingValue_u16 = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32 / 1000u);
                                Dcm_ProgConditions_st.ReqResBuf[0] = (uint8)(dataTimingValue_u16 >> 8u);
                                Dcm_ProgConditions_st.ReqResBuf[1] = (uint8)(dataTimingValue_u16 & 0x00ffu);
                                dataTimingValue_u16 = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32/10000u);
                                Dcm_ProgConditions_st.ReqResBuf[2] = (uint8)(dataTimingValue_u16 >> 8u);
                                Dcm_ProgConditions_st.ReqResBuf[3] = (uint8)(dataTimingValue_u16 & 0x00ffu);
                                Dcm_ProgConditions_st.ReqResLen += 0x4;
#endif
                            }
#endif
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT){
                                Dcm_ProgConditions_st.SubFncId  = Dcm_dataEcuRType_u8;
                                Dcm_ProgConditions_st.ReqResLen = 0x2;
                                if(Dcm_dataEcuRType_u8 == DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET){
                                    Dcm_ProgConditions_st.ReqResBuf[0] = DCM_CFG_DSP_POWER_DOWN_TIME;
                                    Dcm_ProgConditions_st.ReqResLen += 0x1;
                                }
                                if(dataBootType_u8 == DCM_JUMPDRIVETODRIVE){
                                    Dcm_ProgConditions_st.SessionLevel     = 0x01;
                                    Dcm_ProgConditions_st.SecurityLevel    = 0x00;
                                }
                            }
#endif
                        }
                        if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT){
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT){
                                Dcm_ProgConditions_st.SessionLevel = Dcm_ReqSess_u8;
                                Dcm_ProgConditions_st.SecurityLevel= 0x0;
                                Dcm_ProgConditions_st.ReqResLen = 0x0;
                            }
#endif
                        }
                        Dcm_InvokeSetProgCondition(&flgProcessSrv_b, dataNegRespCode_u8);
                    }
                }
            }
            if((dataProtocolId_u8 == DCM_NO_ACTIVE_PROTOCOL) || (dataReturnValue_u8 != E_OK)){
                Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
        else{
            Dcm_InvokeSetProgCondition(&flgProcessSrv_b, dataNegRespCode_u8);
        }
   }
   if(Dcm_BootLoaderState_en == DCM_BOOT_SENDFORCEDRESPPEND){
        if(Dcm_Lok_GetDslState() != DSL_STATE_WAITING_FOR_TXCONFIRMATION){
            Dcm_BootLoaderState_en = DCM_BOOT_WAIT;
            if(Dcm_ForceRespPend() == E_OK){
            }
            else{
                Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
            if((Dcm_Lok_GetDslState() == DSL_STATE_RESPONSE_TRANSMISSION) && \
                    (Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_SEND_GENERAL_REJECT)){
                Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }
        }
        else{
        }
   }
   if(Dcm_BootLoaderState_en == DCM_BOOT_WAIT){
   }
   if(Dcm_BootLoaderState_en== DCM_BOOT_PREPARE_RESET){
        if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_P2MAX_TIMEMONITORING){
            Dcm_BootLoaderState_en = DCM_BOOT_WAIT_FOR_RESET;
#if(DCM_CFG_OSTIMER_USE != FALSE)
            if(E_NOT_OK==Dcm_TimerRemaining(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,&Dcm_StoreReturnValue_u8))
#else
            if(E_NOT_OK==Dcm_TimerRemaining(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,0,&Dcm_StoreReturnValue_u8))
#endif
            {
                if(E_OK!=Dcm_SendForcedResponsePend()){
                    Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
            else{
                Dcm_BootLoaderState_en = DCM_BOOT_PERFORM_RESET;
            }
        }
        else{
        }
   }
   if(Dcm_BootLoaderState_en == DCM_BOOT_PERFORM_RESET){
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                (void)SchM_Switch_SwcServiceDcm_tEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
#endif
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF))
                if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT){
                    DcmAppl_Switch_DcmExecuteEcuReset(Dcm_dataEcuRType_u8);
                }
#endif
                Dcm_BootLoaderState_en = DCM_BOOT_WAIT_FOR_RESET;
   }
   if(Dcm_BootLoaderState_en == DCM_BOOT_ERROR){
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT){
            Dcm_stDsc_en = DCM_DSP_DSC_ERROR;
        }
#endif

#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
        if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT){
            Dcm_stEcuResetState_en = DCM_ECURESET_ERROR;
        }
#endif
        Dcm_ProgConditions_st.ReprogramingRequest = FALSE;
        Dcm_ProgConditions_st.ResponseRequired=FALSE;
        Dcm_ResetBootLoader();
   }
   if(flgProcessSrv_b != FALSE){
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT){
            Dcm_stDsc_en = DCM_DSP_DSC_SEND_RESP;
        }
#endif

#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
        if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT){
            Dcm_stEcuResetState_en = DCM_ECURESET_SENDRESPONSE;
        }
#endif
   }
}

FUNC(void,DCM_CODE) Dcm_ResetBootLoader(void){
   if((DCM_BOOT_WAIT==Dcm_BootLoaderState_en)||(DCM_BOOT_SENDFORCEDRESPPEND==Dcm_BootLoaderState_en)){
        (void)Dcm_SetProgConditions(DCM_CANCEL,NULL_PTR);
   }
    Dcm_BootLoaderState_en = DCM_BOOT_IDLE;
   s_Dcm_SetProgCondOpstatus_u8=DCM_INITIAL;
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_TimerRemaining(VAR(uint32,AUTOMATIC)timer,VAR(uint32,AUTOMATIC)startTime,P2VAR(Std_ReturnType,DCM_INTERN_DATA,AUTOMATIC)timerStatus){
   VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
#if( DCM_CFG_OSTIMER_USE != FALSE )
   VAR(uint32,AUTOMATIC) Dcm_GetCurrentTime_u32;
   Dcm_GetCurrentTime_u32 =0x00u;
   if( *timerStatus == E_OK ){
        *timerStatus = Dcm_GetCounterValue(DCM_CFG_COUNTERID, (&Dcm_GetCurrentTime_u32));
        if( *timerStatus == E_OK ){
            if(( (DCM_CFG_TICKS2US_COUNTER(Dcm_GetCurrentTime_u32 - (startTime))) +DCM_CFG_ECURESET_TIME) >=(timer) ){
                retVal_u8 = E_NOT_OK;
            }
        }
        else{
            retVal_u8 = E_NOT_OK;
        }
   }
   else{
        if(timer <= (DCM_CFG_ECURESET_TIME/DCM_CFG_TASK_TIME_US)){
            retVal_u8 =E_NOT_OK;
        }
   }
#else
   if(timer <= (DCM_CFG_ECURESET_TIME/DCM_CFG_TASK_TIME_US)){
        retVal_u8 =E_NOT_OK;
   }
    (void)startTime;
    *timerStatus = E_OK;
#endif
       return (retVal_u8);
}

static FUNC(Std_ReturnType, DCM_CODE) Dcm_SendForcedResponsePend(void){
   VAR(Std_ReturnType,AUTOMATIC) dataRetValue_u8 = E_NOT_OK;
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   VAR(uint8, AUTOMATIC) DslPreemptionStateTemp_u8;
#endif
   VAR(Dcm_DsdStatesType_ten,AUTOMATIC) DsdState_en = Dcm_Lok_GetDsdState();

   if((Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_ROE_SOURCE) && (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_RDPI_SOURCE) && (DSD_CALL_SERVICE  == DsdState_en))
   {

        if(Dcm_DslTransmit_st.isForceResponsePendRequested_b == FALSE)
        {

            Dcm_DslTransmit_st.isForceResponsePendRequested_b = TRUE;

            Dcm_DslTransmit_st.TxBuffer_tpu8 = NULL_PTR;

            Dcm_DslTransmit_st.TxResponseLength_u32 = 0x00;

            if((Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 < DCM_CFG_MAX_WAITPEND) || (DCM_CFG_MAX_WAITPEND == DCM_MAXNUMRESPONSEPENDING))
            {

                if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_P2MAX_TIMEMONITORING)
                {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                    DslPreemptionStateTemp_u8 = Dcm_Lok_GetDslPreemptionState();

                    if((DslPreemptionStateTemp_u8 != DSL_SUBSTATE_STOP_PROTOCOL)&& (DslPreemptionStateTemp_u8 != DSL_SUBSTATE_STOP_ROE))
#endif
                    {

                        SchM_Enter_Dcm_Global_NoNest();

                        Dcm_DslWaitPendBuffer_au8[0] = DCM_NEGRESPONSE_INDICATOR;
                        Dcm_DslWaitPendBuffer_au8[1] = Dcm_DsldGlobal_st.dataSid_u8;
                        Dcm_DslWaitPendBuffer_au8[2] = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING ;

                        Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DslWaitPendBuffer_au8;
                        Dcm_DsldPduInfo_st.SduLength = 0x03;
                        if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 < DCM_MAXNUMRESPONSEPENDING)
                        {

                            Dcm_DsldGlobal_st.cntrWaitpendCounter_u8++;
                        }

                        Dcm_Lok_SetDslState(DSL_STATE_WAITING_FOR_TXCONFIRMATION);

                        Dcm_Lok_SetDslNextState(DSL_STATE_REQUEST_RECEIVED);
                        Dcm_Lok_SetDslNextSubState(DSL_SUBSTATE_P2MAX_TIMEMONITORING);

                        SchM_Exit_Dcm_Global_NoNest();

                        Dcm_Lok_SendResponse(&Dcm_DsldPduInfo_st);
                    }
                }
            }
            else{
                Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
            }

            dataRetValue_u8 = E_OK;

        }
   }
    return(dataRetValue_u8);
}

static FUNC(void, DCM_CODE) Dcm_InvokeSetProgCondition(P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) flag_b, P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
   VAR(Std_ReturnType,   AUTOMATIC) dataRetProgCond_u8;

    dataRetProgCond_u8 = Dcm_SetProgConditions(s_Dcm_SetProgCondOpstatus_u8,&Dcm_ProgConditions_st);

   if(dataRetProgCond_u8 == E_OK)
   {
        if((Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMREQ) ||
                (Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMRESP))
        {
            Dcm_BootLoaderState_en= DCM_BOOT_PREPARE_RESET;
        }
        if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT)
        {

            *flag_b = TRUE;
        }

        s_Dcm_SetProgCondOpstatus_u8=DCM_INITIAL;
   }
   else if(dataRetProgCond_u8 == DCM_E_PENDING)
   {

        s_Dcm_SetProgCondOpstatus_u8=DCM_PENDING;
   }
   else if(dataRetProgCond_u8 == DCM_E_FORCE_RCRRP)
   {

        Dcm_BootLoaderState_en= DCM_BOOT_SENDFORCEDRESPPEND;

        s_Dcm_SetProgCondOpstatus_u8=DCM_FORCE_RCRRP_OK;
   }
   else{

        Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;

        s_Dcm_SetProgCondOpstatus_u8=DCM_INITIAL;

        DCM_DET_ERROR(DCM_BOOTLOADER_ID, DCM_E_SET_PROG_CONDITIONS_FAIL);
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
