#include "Std_Types.hpp"

#include "CfgSwcServiceEcuM.hpp"
#include "EcuM.hpp"
#include "EcuM_Cfg_SchM.hpp"
#include "EcuM_RunTime.hpp"
#include "BswM_EcuM.hpp"
#include "types.hpp" //TBD: Remove
#include "CfgMcalMcu.hpp"

#if( ECUM_INCLUDE_COMM == STD_ON )
#include "ComM_EcuMBswM.hpp"
#endif   

#include "Os.hpp"

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#endif

#include "EcuM_Callout.hpp"
#include "EcuM_Prv.hpp"

#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_MemMap.hpp"
EcuM_BootTargetType EcuM_Lok_dataSelectedBootTarget_u8;
uint8 EcuM_Lok_dataSelectedBootTargetInit_u8;
#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_8
#include "EcuM_MemMap.hpp"
uint8 EcuM_Lok_SlaveCoreTimeoutCtr_u8;
Type_SwcServiceEcuM_tCauseShutdown EcuM_Lok_dataSelectedShutdownCause_u8 = 0;

#if( ECUM_CFG_MODE_HANDLING == STD_ON)
uint8 EcuM_Lok_RunRequested_u8;
uint8 EcuM_Lok_Post_Run_Requested_u8;
#endif //ECUM_CFG_MODE_HANDLING

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
EcuM_Lok_SleepType_Enum_ten EcuM_Lok_SleepReqType_en;
EcuM_Lok_WakeupRestartReason_Enum_ten EcuM_Lok_WakeupRestartReason_en;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_8
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"
#if( ECUM_SLEEP_SUPPORT_ENABLE == TRUE )
EcuM_CurrentCoreInfoType EcuM_Lok_CoreStatus_st;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_32
#include "EcuM_MemMap.hpp"
Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataOldPendingWakeupEvents_u32;
Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataExpiredWakeupEvents_u32;
Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataClrWkpEventsInd_u32;
Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataPndWkpEventsInd_u32;
Type_SwcServiceEcuM_tSourceWakeup EcuM_Lok_dataExpWkpEventsInd_u32;
#define ECUM_STOP_SEC_VAR_CLEARED_32
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_16
#include "EcuM_MemMap.hpp"
uint16 EcuM_Lok_WkpSrcValidationTimeoutCtr_u16;

#if(ECUM_SLEEP_SUPPORT_ENABLE== TRUE)
Type_SwcServiceEcuM_tModeShutdown EcuM_Lok_SleepMode_u16;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_16
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"
#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
Type_SwcServiceEcuM_stInfoTargetShutdown EcuM_Lok_dataShutdownInfo_st;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_INIT_16
#include "EcuM_MemMap.hpp"
#if(ECUM_CFG_MODE_HANDLING == STD_ON)
uint16 EcuM_Lok_RunMinDuration_u16 = ECUM_CFG_RUN_SELF_REQUEST_PERIOD;
#endif//ECUM_CFG_MODE_HANDLING
#define ECUM_STOP_SEC_VAR_INIT_16
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_MemMap.hpp"
boolean EcuM_Lok_flgIsStartupTwoCalled_ab[ECUM_CFG_NUM_OS_CORES];
boolean EcuM_Lok_flgCoreReady_ab[ECUM_CFG_NUM_OS_CORES];
boolean EcuM_Lok_flgShutdownInfoDoNotUpdate_b;
#if(ECUM_CFG_MODE_HANDLING == STD_ON)
boolean EcuM_Lok_userRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];
boolean EcuM_Lok_userPostRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];
boolean EcuM_Lok_KillAllRUNRequests_b = FALSE;
boolean EcuM_Lok_KillAllPostRUNRequests_b = FALSE;
#endif//ECUM_CFG_MODE_HANDLING

boolean EcuM_Lok_flgGoDown_b;

#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
boolean EcuM_Lok_flgNvMReadStatus_b;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
boolean EcuM_Lok_flgwakeupRestart_b;
boolean EcuM_Lok_flgClearWakeupRestart_b;
boolean EcuM_Lok_AllCoreSleepReady_b;
static volatile boolean EcuM_Lok_flgSyncWakeupDetected_b;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.hpp"
#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
static void EcuM_Lok_HaltingSequence(uint16 dataSleepModeHandle_u16);
static void EcuM_Lok_PollingSequence(uint16 dataSleepModeHandle_u16);
static void EcuM_Lok_McuSetMode( uint8 Mode, EcuM_Lok_OperationType_Enum_ten flgOperation_en);
#endif //ECUM_SLEEP_SUPPORT_ENABLE

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
boolean EcuM_Lok_IsUserHandlingPossible_b(
        EcuM_UserType * user
   ,       uint8 apiid
){
   boolean return_value = FALSE;
    EcuM_UserType cntrLoop_u16;
   boolean is_validuser_b = FALSE;
   if(FALSE != SwcServiceEcuM_bIsInitialised){
        for(cntrLoop_u16 = 0;cntrLoop_u16 < ECUM_CFG_NUM_FLEX_USERS;cntrLoop_u16++){
                if(EcuM_Cfg_flexUsers_au16[cntrLoop_u16] == *user){
                    *user = cntrLoop_u16;
                    is_validuser_b = TRUE;
                    break;
                }
            }
        if(FALSE != is_validuser_b){
            if(((ECUM_REQUESTRUN_APIID == apiid) && (EcuM_Lok_KillAllRUNRequests_b != FALSE)) ||
                            ((ECUM_REQUESTPOST_RUN_APIID == apiid) && (EcuM_Lok_KillAllPostRUNRequests_b != FALSE))){
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_RB_E_ALL_RUN_REQUESTS_KILLED);
#endif
            }
            else{
                return_value = TRUE;
            }
        }
        else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_E_INVALID_PAR);
#endif
        }
   }
   else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_E_UNINIT);
#endif
   }

    return return_value;
}
#endif

void EcuM_Lok_WakeupIndication( Type_SwcServiceEcuM_tSourceWakeup dataPendingWakeupEvents_u32 ){
   uint8 cntrLoopCtr_u8;
   uint8 ctrLoopPNCNotify_u8;

   if(EcuM_Lok_dataPndWkpEventsInd_u32 != CfgSwcServiceEcuM_dSourceWakeupNone){
        BswM_EcuM_CurrentWakeup (EcuM_Lok_dataPndWkpEventsInd_u32, ECUM_WKSTATUS_PENDING);
   }

   if(SwcServiceEcuM_tSourceWakeup_ValInd !=CfgSwcServiceEcuM_dSourceWakeupNone){
        BswM_EcuM_CurrentWakeup (SwcServiceEcuM_tSourceWakeup_ValInd, ECUM_WKSTATUS_VALIDATED);
        for(cntrLoopCtr_u8 = 0;cntrLoopCtr_u8 < CfgSwcServiceEcuM_dNumSourceWakeup ; cntrLoopCtr_u8++){
            if(((EcuM_Cfg_idxWakeupSourcesPC_au32 [cntrLoopCtr_u8].WakeupSourceId & SwcServiceEcuM_tSourceWakeup_ValInd)
                    != CfgSwcServiceEcuM_dSourceWakeupNone) &&
                    (EcuM_Cfg_idxWakeupSourcesPC_au32 [cntrLoopCtr_u8].IsComChannelPresent == TRUE)
                    ){
#if( ECUM_INCLUDE_COMM == STD_ON )
               ComM_EcuM_WakeUpIndication (EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].ComChannelReferance);
#endif
            }

            if( ( ( SwcServiceEcuM_tSourceWakeup_ValInd & EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId ) != CfgSwcServiceEcuM_dSourceWakeupNone ) \
                    && ( SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[cntrLoopCtr_u8].u8NumRefsPncComM > 0 ) ){
                for( ctrLoopPNCNotify_u8 = 0; ctrLoopPNCNotify_u8 <  (SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[cntrLoopCtr_u8].u8NumRefsPncComM); ctrLoopPNCNotify_u8++){
#if( ECUM_INCLUDE_COMM == STD_ON )
                  ComM_EcuM_PNCWakeUpIndication(SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[cntrLoopCtr_u8].pcau8ListRefsPnc[ctrLoopPNCNotify_u8]);
#endif
                }
            }
        }
   }
   if((EcuM_Lok_dataClrWkpEventsInd_u32 != CfgSwcServiceEcuM_dSourceWakeupNone) && ((EcuM_Lok_dataClrWkpEventsInd_u32 &
            (EcuM_Lok_dataPndWkpEventsInd_u32 | SwcServiceEcuM_tSourceWakeup_ValInd|EcuM_Lok_dataExpWkpEventsInd_u32)) ==
                    CfgSwcServiceEcuM_dSourceWakeupNone)){
        BswM_EcuM_CurrentWakeup (EcuM_Lok_dataClrWkpEventsInd_u32, ECUM_WKSTATUS_NONE);
   }
    SchM_Enter_EcuM();
    EcuM_Lok_dataPndWkpEventsInd_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    SwcServiceEcuM_tSourceWakeup_ValInd = CfgSwcServiceEcuM_dSourceWakeupNone;
    EcuM_Lok_dataClrWkpEventsInd_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    EcuM_Lok_dataExpWkpEventsInd_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    SchM_Exit_EcuM();
   if(dataPendingWakeupEvents_u32 != (EcuM_Lok_dataOldPendingWakeupEvents_u32&dataPendingWakeupEvents_u32)){
        EcuM_StartWakeupSources (EcuM_Lok_dataOldPendingWakeupEvents_u32 ^ dataPendingWakeupEvents_u32);
   }
    EcuM_Lok_dataOldPendingWakeupEvents_u32 = dataPendingWakeupEvents_u32;
}

void EcuM_Lok_DecValidationCtr(void){
   if(EcuM_Lok_WkpSrcValidationTimeoutCtr_u16 > 0){
        SchM_Enter_EcuM();
        EcuM_Lok_WkpSrcValidationTimeoutCtr_u16--;
        SchM_Exit_EcuM();
   }
}

boolean EcuM_Lok_hasCheckWakeupSourceGetHandle_b( Type_SwcServiceEcuM_tSourceWakeup datasource_u32 ){
   boolean flgValidity_b = FALSE;
   if((datasource_u32 != CfgSwcServiceEcuM_dSourceWakeupNone) && ((ECUM_KNOWN_WAKEUP_SOURCES & datasource_u32) == datasource_u32) ){
      flgValidity_b = TRUE;
   }
   else{}
   return flgValidity_b;
}

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
void EcuM_Lok_GoSleepSequence(uint16 dataSleepModeHandle_u16){
    StatusType Os_api_returnvalue = E_NOT_OK;
    Type_SwcServiceEcuM_tSourceWakeup EcuM_dataPendingWakeupEvents_u32 = 0;
    Type_SwcServiceEcuM_tSourceWakeup EcuM_dataValidatedWakeupEvents_u32 = 0;
    EcuM_Lok_SleepType_Enum_ten RequestedSleepType_en;
   uint16 Core_ID = EcuM_Lok_CoreStatus_st.CurrentCoreID;
   if(((EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE) && (FALSE != EcuM_Lok_AllCoreSleepReady_b)) ||
            (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE)
   ){
        Os_api_returnvalue = EcuM_Lok_GetResource (Core_ID);
   }
   else{}

   if(((Os_api_returnvalue == E_OK) && (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE) &&
            (FALSE != EcuM_Lok_AllCoreSleepReady_b))||
            ((Os_api_returnvalue == E_OK) && (EcuM_Lok_CoreStatus_st.CurrentCore != ECUM_MASTER_CORE))
   ){
        SchM_Enter_EcuM();
        EcuM_dataPendingWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_EventsPending;
        EcuM_dataValidatedWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_Validated;
        SchM_Exit_EcuM();
        if((CfgSwcServiceEcuM_dSourceWakeupNone == EcuM_dataPendingWakeupEvents_u32) &&
                (CfgSwcServiceEcuM_dSourceWakeupNone == EcuM_dataValidatedWakeupEvents_u32)
        ){
            SchM_Enter_EcuM();
            RequestedSleepType_en = EcuM_Lok_SleepReqType_en;
            SchM_Exit_EcuM();
            if(ECUM_PRV_GOHALT_E == RequestedSleepType_en){
                EcuM_Lok_HaltingSequence(dataSleepModeHandle_u16);
            }
            else{
                if(ECUM_PRV_GOPOLL_E == RequestedSleepType_en){
                     EcuM_Lok_PollingSequence(dataSleepModeHandle_u16);
                 }
                 else{}
            }
        }
        else{
            EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_WAKEUP_REQUEST_E;
        }
   }
   else  if((!((EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE) && (FALSE == EcuM_Lok_AllCoreSleepReady_b)))\
            &&(Os_api_returnvalue != E_OK)
   ){
        EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_RESOURCE_NOT_ACQUIRED_E;
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID, ECUM_E_OS_GET_RESOURCE_FAILED );
#endif//ECUM_DEV_ERROR_DETECT
   }
   else{}

   if((Os_api_returnvalue != E_OK) || \
            ((ECUM_PRV_NORMAL_E != EcuM_Lok_WakeupRestartReason_en ) && \
                    (ECUM_PRV_CHECK_WAKEUP_PENDING_E != EcuM_Lok_WakeupRestartReason_en ))
   ){
        SchM_Enter_EcuM();
        EcuM_Lok_flgwakeupRestart_b = TRUE;
        EcuM_Lok_SleepReqType_en = ECUM_PRV_NO_SLEEP_E;
        SchM_Exit_EcuM();
   }
    return;
}

static void EcuM_Lok_HaltingSequence(uint16 dataSleepModeHandle_u16){
    EcuM_Lok_OperationType_Enum_ten flgOperation_en = ECUM_PRV_HALT_SEQUENCE_E;
    Type_SwcServiceEcuM_tSourceWakeup dataPendingWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    Type_SwcServiceEcuM_tSourceWakeup dataValidatedWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseSleep;
   if((EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE) || (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE)){
        EcuM_GenerateRamHash();
   }
    EcuM_Lok_McuSetMode(EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].EquivalentMcuMode, flgOperation_en);
   if( (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE)||
            (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE)
   ){
        if( (uint8)0 == EcuM_CheckRamHash()){
            EcuM_ErrorHook(ECUM_E_RAM_CHECK_FAILED);
        }
   }
    SchM_Enter_EcuM();
    dataPendingWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_EventsPending;
    dataValidatedWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_Validated;
    SchM_Exit_EcuM();
   if(CfgSwcServiceEcuM_dSourceWakeupNone != (dataPendingWakeupEvents_u32 &
            EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask)
   ){
        BswM_EcuM_CurrentWakeup((dataPendingWakeupEvents_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_PENDING);

        EcuM_Lok_dataPndWkpEventsInd_u32 ^= (EcuM_Lok_dataPndWkpEventsInd_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
   }

   if(CfgSwcServiceEcuM_dSourceWakeupNone != (dataValidatedWakeupEvents_u32 &
                                                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask)
   ){
        BswM_EcuM_CurrentWakeup((dataValidatedWakeupEvents_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_VALIDATED);

        SwcServiceEcuM_tSourceWakeup_ValInd ^= (SwcServiceEcuM_tSourceWakeup_ValInd &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask) ;

   }
    EcuM_Lok_WakeupRestartSequence(dataSleepModeHandle_u16);
}

static void EcuM_Lok_PollingSequence(uint16 dataSleepModeHandle_u16){
    EcuM_Lok_OperationType_Enum_ten flgOperation_en = ECUM_PRV_POLL_SEQUENCE_E;
    Type_SwcServiceEcuM_tSourceWakeup dataPendingWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    Type_SwcServiceEcuM_tSourceWakeup dataValidatedWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
   uint8 cntrLoopCtr_u8 =0;
    SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseSleep;
    EcuM_Lok_McuSetMode(EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].EquivalentMcuMode, flgOperation_en);
    dataPendingWakeupEvents_u32 = EcuM_GetPendingWakeupEvents();
    dataValidatedWakeupEvents_u32 = EcuM_GetValidatedWakeupEvents();

   while(((dataPendingWakeupEvents_u32 | dataValidatedWakeupEvents_u32) &
                (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask)) == CfgSwcServiceEcuM_dSourceWakeupNone){
        EcuM_SleepActivity();
        for( cntrLoopCtr_u8 = 0; cntrLoopCtr_u8 < CfgSwcServiceEcuM_dNumSourceWakeup; cntrLoopCtr_u8++ ){
            if(((EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId) & (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask)) != CfgSwcServiceEcuM_dSourceWakeupNone ){
                    EcuM_CheckWakeup(EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId);
            }
        }
        dataPendingWakeupEvents_u32 = EcuM_GetPendingWakeupEvents();
        dataValidatedWakeupEvents_u32 = EcuM_GetValidatedWakeupEvents();
   }
   if((dataPendingWakeupEvents_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask) != CfgSwcServiceEcuM_dSourceWakeupNone){
        BswM_EcuM_CurrentWakeup((dataPendingWakeupEvents_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_PENDING);
        EcuM_Lok_dataPndWkpEventsInd_u32 ^= EcuM_Lok_dataPndWkpEventsInd_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask;
   }
   if((dataValidatedWakeupEvents_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask) != CfgSwcServiceEcuM_dSourceWakeupNone){
        BswM_EcuM_CurrentWakeup((dataValidatedWakeupEvents_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_VALIDATED);
        SwcServiceEcuM_tSourceWakeup_ValInd ^= SwcServiceEcuM_tSourceWakeup_ValInd & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask;
   }
        EcuM_Lok_WakeupRestartSequence(dataSleepModeHandle_u16);
}

void EcuM_Lok_WakeupRestartSequence ( uint16 dataSleepModeHandle_u16 ){
    Type_SwcServiceEcuM_tSourceWakeup dataWakeupSrcMask_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    StatusType Os_api_returnvalue = E_NOT_OK;
    EcuM_Lok_OperationType_Enum_ten flgOperation_en = ECUM_PRV_RESTART_SEQUENCE_E;
        if(ECUM_PRV_NORMAL_E == EcuM_Lok_WakeupRestartReason_en){
            EcuM_Lok_McuSetMode (ECUM_NORMAL_MCU_MODE, flgOperation_en);
        }

        dataWakeupSrcMask_u32 = EcuM_GetPendingWakeupEvents();
        dataWakeupSrcMask_u32 = (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask &
                (~dataWakeupSrcMask_u32));
        EcuM_DisableWakeupSources(dataWakeupSrcMask_u32);

        if(ECUM_PRV_RESOURCE_NOT_ACQUIRED_E != EcuM_Lok_WakeupRestartReason_en){
            if((EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE) || \
                    (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE)){
                EcuM_AL_DriverRestart (SwcServiceEcuM_pcstCfg);
            }
            Os_api_returnvalue = EcuM_Lok_ReleaseResource (EcuM_Lok_CoreStatus_st.CurrentCoreID);
        }

        if(Os_api_returnvalue != E_OK){
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID
   ,                   ECUM_E_OS_RELEASE_RESOURCE_FAILED);
#endif//ECUM_DEV_ERROR_DETECT
        }
            SchM_Enter_EcuM();
            EcuM_Lok_flgClearWakeupRestart_b = TRUE;
            SchM_Exit_EcuM();
        SchM_Enter_EcuM();
        EcuM_Lok_flgwakeupRestart_b = FALSE;
        EcuM_Lok_flgClearWakeupRestart_b = FALSE;
        EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_NORMAL_E;
        SchM_Exit_EcuM();
  flgOperation_en = ECUM_PRV_CLEAR_SLEEP_E;
  EcuM_Lok_McuSetMode( (uint8) 0, flgOperation_en);
  (void)EcuM_Lok_CheckWakeupTimerHandling();
}

static void EcuM_Lok_McuSetMode( uint8 Mode, EcuM_Lok_OperationType_Enum_ten flgOperation_en){
   uint8 ctrLoop1_u8 = 0;
   if(flgOperation_en == ECUM_PRV_HALT_SEQUENCE_E){
        SchM_Enter_EcuM();
        EcuM_Lok_flgSyncWakeupDetected_b = FALSE;
        while(FALSE == EcuM_Lok_flgSyncWakeupDetected_b){
            DisableAllInterrupts();
            Mcu_SetMode(Mode);
            EnableAllInterrupts();
            for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ ){
                if((EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus== ECUM_SET_WAKEUP_EVENT_E)\
                        || (EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus== ECUM_TIMER_STARTED_E)
                ){
                    EcuM_Lok_flgSyncWakeupDetected_b = TRUE;
                    break;
                }
            }
        }
        SchM_Exit_EcuM();
   }
 else if((flgOperation_en == ECUM_PRV_RESTART_SEQUENCE_E) || ( flgOperation_en == ECUM_PRV_POLL_SEQUENCE_E )){
        DisableAllInterrupts();
        Mcu_SetMode(Mode);
        EnableAllInterrupts();
   }
   else{}

   if(flgOperation_en == ECUM_PRV_CLEAR_SLEEP_E){
        for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ ){
            if(ECUM_SET_WAKEUP_EVENT_E == EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus){
                break;
            }
            else if(ECUM_TIMER_STARTED_E == EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus){
                SchM_Enter_EcuM();
                EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_CHECK_WAKEUP_PENDING_E;
                EcuM_Lok_flgShutdownInfoDoNotUpdate_b = TRUE;
                EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout + 0x01;
                SchM_Exit_EcuM();
            }
            else{}
        }
   }
   else{}
    return ;
}
#endif//ECUM_SLEEP_SUPPORT_ENABLE

uint32 EcuM_Lok_ComMWakeupHandling (Type_SwcServiceEcuM_tSourceWakeup dataPendingWakeupEvents){
   uint32 EcuM_CommchlWkupEvents_u32 = 0;
   uint8 ctrLoop_u8 = 0;
   uint8 ctrLoopPNCNotify_u8 = 0;
   for( ctrLoop_u8 = 0;ctrLoop_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop_u8++ ){
        if( ( ( dataPendingWakeupEvents & EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId ) != CfgSwcServiceEcuM_dSourceWakeupNone ) \
                && ( EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].IsComChannelPresent == TRUE )
        ){
#if( ECUM_INCLUDE_COMM == STD_ON )
            ComM_EcuM_WakeUpIndication ( EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].ComChannelReferance );
#endif
         EcuM_CommchlWkupEvents_u32 |= EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId;
        }
        if( ( ( dataPendingWakeupEvents & EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId ) != CfgSwcServiceEcuM_dSourceWakeupNone ) \
                && ( SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[ctrLoop_u8].u8NumRefsPncComM > 0 )
                ){
            for( ctrLoopPNCNotify_u8 = 0; ctrLoopPNCNotify_u8 <  (SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[ctrLoop_u8].u8NumRefsPncComM); ctrLoopPNCNotify_u8++
            ){
#if( ECUM_INCLUDE_COMM == STD_ON )
               ComM_EcuM_PNCWakeUpIndication(SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[ctrLoop_u8].pcau8ListRefsPnc[ctrLoopPNCNotify_u8]);
#endif
            }
        }
   }
    return EcuM_CommchlWkupEvents_u32;
}
#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.hpp"

