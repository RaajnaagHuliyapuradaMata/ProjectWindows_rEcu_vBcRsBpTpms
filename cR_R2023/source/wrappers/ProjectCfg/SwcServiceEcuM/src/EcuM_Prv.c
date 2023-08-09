
#include "EcuM.h"
#include "EcuM_Cfg_SchM.h"
#include "EcuM_RunTime.h"
#include "BswM_EcuM.h"
#if (!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "Mcu.h"
#if (!defined(MCU_AR_RELEASE_MAJOR_VERSION) || (MCU_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(MCU_AR_RELEASE_MINOR_VERSION) || (MCU_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "ComM_EcuMBswM.h"
#if (!defined(COMM_AR_RELEASE_MAJOR_VERSION) || (COMM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMM_AR_RELEASE_MINOR_VERSION) || (COMM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "Os.h"
#if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "EcuM_Callout.h"
#include "EcuM_Prv.h"
#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_Cfg_MemMap.h"
VAR(EcuM_BootTargetType,ECUM_VAR_POWER_ON_CLEARED_8)  EcuM_Lok_dataSelectedBootTarget_u8;
VAR(uint8,ECUM_VAR_POWER_ON_CLEARED_8)  EcuM_Lok_dataSelectedBootTargetInit_u8;
#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_8
#include "EcuM_Cfg_MemMap.h"
VAR( uint8, ECUM_VAR_CLEARED_8 )  EcuM_Lok_SlaveCoreTimeoutCtr_u8;
VAR( Type_SwcServiceEcuM_tCauseShutdown, ECUM_VAR_CLEARED_8 )  EcuM_Lok_dataSelectedShutdownCause_u8 = 0;

#if( ECUM_CFG_MODE_HANDLING == STD_ON)
VAR(uint8, ECUM_VAR_CLEARED_8) EcuM_Lok_RunRequested_u8;
VAR(uint8, ECUM_VAR_CLEARED_8) EcuM_Lok_Post_Run_Requested_u8;
#endif //ECUM_CFG_MODE_HANDLING

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
VAR(EcuM_Lok_SleepType_Enum_ten, ECUM_VAR_CLEARED_8) EcuM_Lok_SleepReqType_en;
VAR(EcuM_Lok_WakeupRestartReason_Enum_ten, ECUM_VAR_CLEARED_8) EcuM_Lok_WakeupRestartReason_en;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_8
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
#if( ECUM_SLEEP_SUPPORT_ENABLE == TRUE )
VAR( EcuM_CurrentCoreInfoType, ECUM_VAR_CLEARED_UNSPECIFIED ) EcuM_Lok_CoreStatus_st;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"
VAR( Type_SwcServiceEcuM_tSourceWakeup, ECUM_VAR_CLEARED_32 ) EcuM_Lok_dataOldPendingWakeupEvents_u32;
VAR( Type_SwcServiceEcuM_tSourceWakeup, ECUM_VAR_CLEARED_32 ) EcuM_Lok_dataExpiredWakeupEvents_u32;
VAR( Type_SwcServiceEcuM_tSourceWakeup, ECUM_VAR_CLEARED_32 ) EcuM_Lok_dataClrWkpEventsInd_u32;
VAR( Type_SwcServiceEcuM_tSourceWakeup, ECUM_VAR_CLEARED_32 ) EcuM_Lok_dataPndWkpEventsInd_u32;
VAR( Type_SwcServiceEcuM_tSourceWakeup, ECUM_VAR_CLEARED_32 )EcuM_Lok_dataExpWkpEventsInd_u32;
#define ECUM_STOP_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_16
#include "EcuM_Cfg_MemMap.h"
VAR( uint16, ECUM_VAR_CLEARED_16 )  EcuM_Lok_WkpSrcValidationTimeoutCtr_u16;

#if (ECUM_SLEEP_SUPPORT_ENABLE== TRUE)
VAR( Type_SwcServiceEcuM_tModeShutdown, ECUM_VAR_CLEARED_16 ) EcuM_Lok_SleepMode_u16;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_16
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
VAR( Type_SwcServiceEcuM_stInfoTargetShutdown, ECUM_VAR_POWER_ON_CLEARED_UNSPECIFIED ) EcuM_Lok_dataShutdownInfo_st;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_INIT_16
#include "EcuM_Cfg_MemMap.h"
#if(ECUM_CFG_MODE_HANDLING == STD_ON)
VAR( uint16, ECUM_VAR_INIT_16 ) EcuM_Lok_RunMinDuration_u16 = ECUM_CFG_RUN_SELF_REQUEST_PERIOD;
#endif//ECUM_CFG_MODE_HANDLING
#define  ECUM_STOP_SEC_VAR_INIT_16
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Lok_flgIsStartupTwoCalled_ab[ECUM_CFG_NUM_OS_CORES];
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Lok_flgCoreReady_ab[ECUM_CFG_NUM_OS_CORES];
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Lok_flgShutdownInfoDoNotUpdate_b;
#if(ECUM_CFG_MODE_HANDLING == STD_ON)
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Lok_userRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Lok_userPostRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Lok_KillAllRUNRequests_b = FALSE;
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Lok_KillAllPostRUNRequests_b = FALSE;
#endif//ECUM_CFG_MODE_HANDLING

VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Lok_flgGoDown_b;

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
VAR(boolean,ECUM_VAR_CLEARED_BOOLEAN)  EcuM_Lok_flgNvMReadStatus_b;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Lok_flgwakeupRestart_b;
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Lok_flgClearWakeupRestart_b;
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Lok_AllCoreSleepReady_b;
static volatile VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Lok_flgSyncWakeupDetected_b;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"
#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
static FUNC(void, ECUM_CODE) EcuM_Lok_HaltingSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16);
static FUNC(void, ECUM_CODE) EcuM_Lok_PollingSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16);
static FUNC( void, ECUM_CODE)EcuM_Lok_McuSetMode( VAR(uint8, AUTOMATIC) Mode, VAR(EcuM_Lok_OperationType_Enum_ten, AUTOMATIC) flgOperation_en);
#endif //ECUM_SLEEP_SUPPORT_ENABLE

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
FUNC( boolean, ECUM_CODE ) EcuM_Lok_IsUserHandlingPossible_b(
        P2VAR(EcuM_UserType, AUTOMATIC, ECUM_APPL_DATA)user,
        VAR(uint8, AUTOMATIC) apiid)
{
    VAR(boolean, AUTOMATIC ) return_value = FALSE;
    VAR(EcuM_UserType, AUTOMATIC) cntrLoop_u16;
    VAR(boolean,AUTOMATIC) is_validuser_b = FALSE;

    if(FALSE != SwcServiceEcuM_bIsInitialised)
    {
        for(cntrLoop_u16 = 0;cntrLoop_u16 < ECUM_CFG_NUM_FLEX_USERS;cntrLoop_u16++)
            {
                if(EcuM_Cfg_flexUsers_au16[cntrLoop_u16] == *user)
                {
                    *user = cntrLoop_u16;
                    is_validuser_b = TRUE;
                    break;
                }
            }

        if(FALSE != is_validuser_b)
        {
            if (((ECUM_REQUESTRUN_APIID == apiid) && (EcuM_Lok_KillAllRUNRequests_b != FALSE)) ||
                            ((ECUM_REQUESTPOST_RUN_APIID == apiid) && (EcuM_Lok_KillAllPostRUNRequests_b != FALSE)))
            {
                #if (ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_RB_E_ALL_RUN_REQUESTS_KILLED);
                #endif
            }
            else
            {
                return_value = TRUE;
            }
        }
        else
        {
            #if (ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_E_INVALID_PAR);
            #endif
        }
    }
    else
    {
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_E_UNINIT);
        #endif
    }

    return return_value;
}
#endif

FUNC( void, ECUM_CODE ) EcuM_Lok_WakeupIndication( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) dataPendingWakeupEvents_u32 )
{
    VAR(uint8, AUTOMATIC) cntrLoopCtr_u8;
    VAR(uint8, AUTOMATIC) ctrLoopPNCNotify_u8;

    if (EcuM_Lok_dataPndWkpEventsInd_u32 != CfgSwcServiceEcuM_dSourceWakeupNone)
    {
        BswM_EcuM_CurrentWakeup (EcuM_Lok_dataPndWkpEventsInd_u32, ECUM_WKSTATUS_PENDING);
    }

    if (SwcServiceEcuM_tSourceWakeup_ValInd !=CfgSwcServiceEcuM_dSourceWakeupNone)
    {
        BswM_EcuM_CurrentWakeup (SwcServiceEcuM_tSourceWakeup_ValInd, ECUM_WKSTATUS_VALIDATED);
        for(cntrLoopCtr_u8 = 0;cntrLoopCtr_u8 < CfgSwcServiceEcuM_dNumSourceWakeup ; cntrLoopCtr_u8++)
        {
            if (((EcuM_Cfg_idxWakeupSourcesPC_au32 [cntrLoopCtr_u8].WakeupSourceId & SwcServiceEcuM_tSourceWakeup_ValInd)
                    != CfgSwcServiceEcuM_dSourceWakeupNone) &&
                    (EcuM_Cfg_idxWakeupSourcesPC_au32 [cntrLoopCtr_u8].IsComChannelPresent == TRUE))
            {
                ComM_EcuM_WakeUpIndication (EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].ComChannelReferance);
            }

            if ( ( ( SwcServiceEcuM_tSourceWakeup_ValInd & EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId ) != CfgSwcServiceEcuM_dSourceWakeupNone ) \
                    && ( SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[cntrLoopCtr_u8].u8NumRefsPncComM > 0 ) )
            {

                for ( ctrLoopPNCNotify_u8 = 0; ctrLoopPNCNotify_u8 <  (SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[cntrLoopCtr_u8].u8NumRefsPncComM); ctrLoopPNCNotify_u8++)
                {
                    ComM_EcuM_PNCWakeUpIndication(SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[cntrLoopCtr_u8].pcau8ListRefsPnc[ctrLoopPNCNotify_u8]);
                }

            }
        }
    }

    if((EcuM_Lok_dataClrWkpEventsInd_u32 != CfgSwcServiceEcuM_dSourceWakeupNone) && ((EcuM_Lok_dataClrWkpEventsInd_u32 &
            (EcuM_Lok_dataPndWkpEventsInd_u32 | SwcServiceEcuM_tSourceWakeup_ValInd|EcuM_Lok_dataExpWkpEventsInd_u32)) ==
                    CfgSwcServiceEcuM_dSourceWakeupNone))
    {
        BswM_EcuM_CurrentWakeup (EcuM_Lok_dataClrWkpEventsInd_u32, ECUM_WKSTATUS_NONE);
    }

    SchM_Enter_EcuM();
    EcuM_Lok_dataPndWkpEventsInd_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    SwcServiceEcuM_tSourceWakeup_ValInd = CfgSwcServiceEcuM_dSourceWakeupNone;
    EcuM_Lok_dataClrWkpEventsInd_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    EcuM_Lok_dataExpWkpEventsInd_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    SchM_Exit_EcuM();

    if (dataPendingWakeupEvents_u32 != (EcuM_Lok_dataOldPendingWakeupEvents_u32&dataPendingWakeupEvents_u32))
    {
        EcuM_StartWakeupSources (EcuM_Lok_dataOldPendingWakeupEvents_u32 ^ dataPendingWakeupEvents_u32);
    }

    EcuM_Lok_dataOldPendingWakeupEvents_u32 = dataPendingWakeupEvents_u32;
}

FUNC( void, ECUM_CODE ) EcuM_Lok_DecValidationCtr( void )
{
    if (EcuM_Lok_WkpSrcValidationTimeoutCtr_u16 > 0)
    {
        SchM_Enter_EcuM();
        EcuM_Lok_WkpSrcValidationTimeoutCtr_u16--;
        SchM_Exit_EcuM();
    }

}

FUNC(boolean, ECUM_CODE) EcuM_Lok_hasCheckWakeupSourceGetHandle_b( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC)datasource_u32 )
{
    VAR(boolean, AUTOMATIC) flgValidity_b = FALSE;

    if((datasource_u32 != CfgSwcServiceEcuM_dSourceWakeupNone) && ((ECUM_KNOWN_WAKEUP_SOURCES & datasource_u32) == datasource_u32) )
	{
	   flgValidity_b = TRUE;
	}
	else
	{
	}
    return flgValidity_b;
}

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
FUNC(void, ECUM_CODE) EcuM_Lok_GoSleepSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16)
                {
    StatusType Os_api_returnvalue = E_NOT_OK;
    VAR( Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC )  EcuM_dataPendingWakeupEvents_u32 = 0;
    VAR( Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC )  EcuM_dataValidatedWakeupEvents_u32 = 0;
    VAR(EcuM_Lok_SleepType_Enum_ten, AUTOMATIC) RequestedSleepType_en;
    VAR( uint16, AUTOMATIC )  Core_ID = EcuM_Lok_CoreStatus_st.CurrentCoreID;

    if(((EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE) && (FALSE != EcuM_Lok_AllCoreSleepReady_b)) ||
            (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE))
    {
        Os_api_returnvalue = EcuM_Lok_GetResource (Core_ID);
    }
    else
    {
    }

    if(((Os_api_returnvalue == E_OK) && (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE) &&
            (FALSE != EcuM_Lok_AllCoreSleepReady_b))||
            ((Os_api_returnvalue == E_OK) && (EcuM_Lok_CoreStatus_st.CurrentCore != ECUM_MASTER_CORE)))

    {
        SchM_Enter_EcuM();
        EcuM_dataPendingWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_EventsPending;
        EcuM_dataValidatedWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_Validated;
        SchM_Exit_EcuM();
        if((CfgSwcServiceEcuM_dSourceWakeupNone == EcuM_dataPendingWakeupEvents_u32) &&
                (CfgSwcServiceEcuM_dSourceWakeupNone == EcuM_dataValidatedWakeupEvents_u32))
        {
            SchM_Enter_EcuM();
            RequestedSleepType_en = EcuM_Lok_SleepReqType_en;
            SchM_Exit_EcuM();

            if(ECUM_PRV_GOHALT_E == RequestedSleepType_en)
            {
                EcuM_Lok_HaltingSequence(dataSleepModeHandle_u16);
            }
            else
            {
                if(ECUM_PRV_GOPOLL_E == RequestedSleepType_en)
                 {
                     EcuM_Lok_PollingSequence(dataSleepModeHandle_u16);
                 }
                 else
                 {
                 }
            }
        }
        else
        {
            EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_WAKEUP_REQUEST_E;
        }
    }
    else  if ((!((EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE) && (FALSE == EcuM_Lok_AllCoreSleepReady_b)))\
            &&(Os_api_returnvalue != E_OK))
    {
        EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_RESOURCE_NOT_ACQUIRED_E;
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID, ECUM_E_OS_GET_RESOURCE_FAILED );
#endif//ECUM_DEV_ERROR_DETECT
    }
    else
    {
    }

    if((Os_api_returnvalue != E_OK) || \
            ((ECUM_PRV_NORMAL_E != EcuM_Lok_WakeupRestartReason_en ) && \
                    (ECUM_PRV_CHECK_WAKEUP_PENDING_E != EcuM_Lok_WakeupRestartReason_en )))
    {
        SchM_Enter_EcuM();
        EcuM_Lok_flgwakeupRestart_b = TRUE;
        EcuM_Lok_SleepReqType_en = ECUM_PRV_NO_SLEEP_E;
        SchM_Exit_EcuM();
    }
    return;
}

static FUNC(void, ECUM_CODE) EcuM_Lok_HaltingSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16)
        {
    VAR( EcuM_Lok_OperationType_Enum_ten, AUTOMATIC )  flgOperation_en = ECUM_PRV_HALT_SEQUENCE_E;
    VAR( Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC ) dataPendingWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    VAR( Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC ) dataValidatedWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseSleep;

    DisableAllInterrupts();
    if ((EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE) || (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE))
    {
        EcuM_GenerateRamHash();
    }

    EcuM_Lok_McuSetMode(EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].EquivalentMcuMode, flgOperation_en);

    EnableAllInterrupts();
    if( (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE)||
            (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE))
    {
        if( (uint8)0 == EcuM_CheckRamHash())
        {
            EcuM_ErrorHook(ECUM_E_RAM_CHECK_FAILED);
        }
    }

    SchM_Enter_EcuM();
    dataPendingWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_EventsPending;
    dataValidatedWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_Validated;
    SchM_Exit_EcuM();

    if (CfgSwcServiceEcuM_dSourceWakeupNone != (dataPendingWakeupEvents_u32 &
            EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask))
    {
        BswM_EcuM_CurrentWakeup((dataPendingWakeupEvents_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_PENDING);

        EcuM_Lok_dataPndWkpEventsInd_u32 ^= (EcuM_Lok_dataPndWkpEventsInd_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
    }

    if(CfgSwcServiceEcuM_dSourceWakeupNone != (dataValidatedWakeupEvents_u32 &
                                                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask))
    {
        BswM_EcuM_CurrentWakeup((dataValidatedWakeupEvents_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_VALIDATED);

        SwcServiceEcuM_tSourceWakeup_ValInd ^= (SwcServiceEcuM_tSourceWakeup_ValInd &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask) ;

    }
    EcuM_Lok_WakeupRestartSequence(dataSleepModeHandle_u16);
}

static FUNC(void, ECUM_CODE) EcuM_Lok_PollingSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16)
        {
    VAR( EcuM_Lok_OperationType_Enum_ten, AUTOMATIC )  flgOperation_en = ECUM_PRV_POLL_SEQUENCE_E;
    VAR( Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC ) dataPendingWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    VAR( Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC ) dataValidatedWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    VAR( uint8, AUTOMATIC ) cntrLoopCtr_u8 =0;
    SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseSleep;
    EcuM_Lok_McuSetMode(EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].EquivalentMcuMode, flgOperation_en);
    dataPendingWakeupEvents_u32 = EcuM_GetPendingWakeupEvents();
    dataValidatedWakeupEvents_u32 = EcuM_GetValidatedWakeupEvents();

    while (((dataPendingWakeupEvents_u32 | dataValidatedWakeupEvents_u32) &
                (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask)) == CfgSwcServiceEcuM_dSourceWakeupNone)
    {
        EcuM_SleepActivity();

        for ( cntrLoopCtr_u8 = 0; cntrLoopCtr_u8 < CfgSwcServiceEcuM_dNumSourceWakeup; cntrLoopCtr_u8++ )
        {
            if (((EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId) & (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask)) != CfgSwcServiceEcuM_dSourceWakeupNone )
            {
                    EcuM_CheckWakeup(EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId);
            }

        }
        dataPendingWakeupEvents_u32 = EcuM_GetPendingWakeupEvents();
        dataValidatedWakeupEvents_u32 = EcuM_GetValidatedWakeupEvents();

    }

    if ((dataPendingWakeupEvents_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask) != CfgSwcServiceEcuM_dSourceWakeupNone)
    {
        BswM_EcuM_CurrentWakeup((dataPendingWakeupEvents_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_PENDING);
        EcuM_Lok_dataPndWkpEventsInd_u32 ^= EcuM_Lok_dataPndWkpEventsInd_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask;
    }

    if ((dataValidatedWakeupEvents_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask) != CfgSwcServiceEcuM_dSourceWakeupNone)
    {
        BswM_EcuM_CurrentWakeup((dataValidatedWakeupEvents_u32 & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_VALIDATED);
        SwcServiceEcuM_tSourceWakeup_ValInd ^= SwcServiceEcuM_tSourceWakeup_ValInd & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask;
    }
        EcuM_Lok_WakeupRestartSequence(dataSleepModeHandle_u16);
}

FUNC(void, ECUM_CODE)EcuM_Lok_WakeupRestartSequence ( VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16 )
      {
    VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) dataWakeupSrcMask_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
    VAR(StatusType, AUTOMATIC) Os_api_returnvalue = E_NOT_OK;
    VAR(EcuM_Lok_OperationType_Enum_ten, AUTOMATIC) flgOperation_en = ECUM_PRV_RESTART_SEQUENCE_E;
        if (ECUM_PRV_NORMAL_E == EcuM_Lok_WakeupRestartReason_en)
        {
            EcuM_Lok_McuSetMode (ECUM_NORMAL_MCU_MODE, flgOperation_en);
        }

        dataWakeupSrcMask_u32 = EcuM_GetPendingWakeupEvents();
        dataWakeupSrcMask_u32 = (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask &
                (~dataWakeupSrcMask_u32));
        EcuM_DisableWakeupSources(dataWakeupSrcMask_u32);

        if (ECUM_PRV_RESOURCE_NOT_ACQUIRED_E != EcuM_Lok_WakeupRestartReason_en)
        {
            if((EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE) || \
                    (EcuM_Lok_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE))
            {
                EcuM_AL_DriverRestart (SwcServiceEcuM_pcstCfg);
            }
            Os_api_returnvalue = EcuM_Lok_ReleaseResource (EcuM_Lok_CoreStatus_st.CurrentCoreID);
        }

        if(Os_api_returnvalue != E_OK)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID,
                    ECUM_E_OS_RELEASE_RESOURCE_FAILED);
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

static FUNC( void, ECUM_CODE)EcuM_Lok_McuSetMode( VAR(uint8, AUTOMATIC) Mode, VAR(EcuM_Lok_OperationType_Enum_ten, AUTOMATIC) flgOperation_en)
                {
    VAR(uint8, AUTOMATIC) ctrLoop1_u8 = 0;
    if(flgOperation_en == ECUM_PRV_HALT_SEQUENCE_E)
    {
        SchM_Enter_EcuM();
        EcuM_Lok_flgSyncWakeupDetected_b = FALSE;
        while(FALSE == EcuM_Lok_flgSyncWakeupDetected_b)
        {
            Mcu_SetMode(Mode);
            for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ )
            {
                if((EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus== ECUM_SET_WAKEUP_EVENT_E)\
                        || (EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus== ECUM_TIMER_STARTED_E))
                {
                    EcuM_Lok_flgSyncWakeupDetected_b = TRUE;
                    break;
                }
            }
        }
        SchM_Exit_EcuM();
    }
 else if((flgOperation_en == ECUM_PRV_RESTART_SEQUENCE_E) || ( flgOperation_en == ECUM_PRV_POLL_SEQUENCE_E ))
    {
        DisableAllInterrupts();
        Mcu_SetMode(Mode);
        EnableAllInterrupts();
    }
    else
    {
    }

    if (flgOperation_en == ECUM_PRV_CLEAR_SLEEP_E)
    {
        for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ )
        {
            if(ECUM_SET_WAKEUP_EVENT_E == EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus)
            {
                break;
            }
            else if(ECUM_TIMER_STARTED_E == EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus)
            {
                SchM_Enter_EcuM();
                EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_CHECK_WAKEUP_PENDING_E;
                EcuM_Lok_flgShutdownInfoDoNotUpdate_b = TRUE;
                EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout + 0x01;
                SchM_Exit_EcuM();
            }
            else
            {
            }
        }
    }
    else
    {
    }
    return ;
}
#endif//ECUM_SLEEP_SUPPORT_ENABLE

FUNC(uint32, ECUM_CODE)EcuM_Lok_ComMWakeupHandling (VAR( Type_SwcServiceEcuM_tSourceWakeup,AUTOMATIC )  dataPendingWakeupEvents)
        {
    VAR(uint32, AUTOMATIC) EcuM_CommchlWkupEvents_u32 = 0;
    VAR(uint8, AUTOMATIC) ctrLoop_u8 = 0;
    VAR(uint8, AUTOMATIC) ctrLoopPNCNotify_u8 = 0;
    for( ctrLoop_u8 = 0;ctrLoop_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop_u8++ )
    {
        if ( ( ( dataPendingWakeupEvents & EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId ) != CfgSwcServiceEcuM_dSourceWakeupNone ) \
                && ( EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].IsComChannelPresent == TRUE ) )
        {
            ComM_EcuM_WakeUpIndication ( EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].ComChannelReferance );
            EcuM_CommchlWkupEvents_u32 |= EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId;
        }

        if ( ( ( dataPendingWakeupEvents & EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId ) != CfgSwcServiceEcuM_dSourceWakeupNone ) \
                && ( SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[ctrLoop_u8].u8NumRefsPncComM > 0 ) )
        {
            for ( ctrLoopPNCNotify_u8 = 0; ctrLoopPNCNotify_u8 <  (SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[ctrLoop_u8].u8NumRefsPncComM); ctrLoopPNCNotify_u8++)
            {
                ComM_EcuM_PNCWakeUpIndication(SwcServiceEcuM_pcstCfg->pcstListRefsPncWakeup[ctrLoop_u8].pcau8ListRefsPnc[ctrLoopPNCNotify_u8]);
            }
        }
    }
    return EcuM_CommchlWkupEvents_u32;
}
#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

