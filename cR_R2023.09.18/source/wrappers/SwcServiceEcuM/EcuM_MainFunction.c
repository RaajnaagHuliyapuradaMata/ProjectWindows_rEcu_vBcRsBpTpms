#include "Std_Types.hpp"

#include "EcuM.hpp"
#include "EcuM_Callout.hpp"
#include "EcuM_Cfg_SchM.hpp"
#include "BswM_EcuM.hpp"

#if(!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "Rte_Main.hpp"

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#if(!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "Os.hpp"
#if(!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "EcuM_Prv.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
static FUNC(void, ECUM_CODE ) EcuM_Lok_ProceedShutdown(void);
static FUNC(void, ECUM_CODE ) EcuM_Lok_WakeupValidation(void);
static FUNC(Std_ReturnType, ECUM_CODE ) EcuM_Lok_ShutdownSynchronization(void);

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
static FUNC(void, ECUM_CODE) EcuM_Lok_ProceedSleep( VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16 );
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#if(ECUM_CFG_MODE_HANDLING == STD_ON)

static FUNC(void,ECUM_CODE ) EcuM_Lok_RunHandling(void);
static FUNC(void, ECUM_CODE ) EcuM_Lok_PostRunArbitration(void);
static FUNC(void, ECUM_CODE ) EcuM_Lok_RunArbitration(void);

#endif//ECUM_CFG_MODE_HANDLING

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)

static FUNC(void, ECUM_CODE)EcuM_Lok_ReportCheckWakeupError (void);

#endif//ECUM_SLEEP_SUPPORT_ENABLE

FUNC(void, ECUM_CODE) infSwcServiceEcuMSwcServiceSchM_vMainFunction(void){
   if(FALSE ==  SwcServiceEcuM_bIsInitialised)
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID, ECUM_E_UNINIT);
#endif//ECUM_DEV_ERROR_DETECT
   }
   else if(E_NOT_OK ==  EcuM_Lok_ShutdownSynchronization())
   {
#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
        if(EcuM_Lok_WakeupRestartReason_en != ECUM_PRV_CHECK_WAKEUP_PENDING_E)
        {
#endif
        SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseUp;
#if( ECUM_CFG_MODE_HANDLING == STD_ON)
            EcuM_Lok_RunHandling();
#endif//ECUM_CFG_MODE_HANDLING
        EcuM_Lok_WakeupValidation();
#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
        }
#endif
   }
   else{
   }
    return;
}

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
FUNC(boolean, ECUM_CODE)EcuM_Lok_CheckWakeupTimerHandling (void)
         {
     VAR(uint8, AUTOMATIC) ctrLoop1_u8 = 0;
     VAR(EcuM_Lok_SleepStatus_ten, AUTOMATIC) flgExitSleep_u8 = ENTER_SLEEP_E;
     VAR(EcuM_Cfg_CheckWakeupSrc_tst, AUTOMATIC) dataCheckWakeupTimer_ast[CfgSwcServiceEcuM_dNumSourceWakeup];
     VAR(boolean, AUTOMATIC) flgReturnValue_b = FALSE;

     VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC) dataSleepModeHandle_u16 = 0xFF;

     SchM_Enter_EcuM();

     dataSleepModeHandle_u16 = EcuM_Lok_SleepMode_u16;

    (void)dataSleepModeHandle_u16;

     for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ )
     {
     dataCheckWakeupTimer_ast[ctrLoop1_u8] = EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8];
     }
     SchM_Exit_EcuM();

     for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ )
     {

         if(ECUM_SET_WAKEUP_EVENT_E == dataCheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus)
         {
           flgExitSleep_u8 = EXIT_SLEEP_E;//exit sleep
           flgReturnValue_b = FALSE;
           SchM_Enter_EcuM();

           EcuM_Lok_flgShutdownInfoDoNotUpdate_b = FALSE;

           EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_NORMAL_E;
           EcuM_Lok_SleepReqType_en = ECUM_PRV_NO_SLEEP_E;

           SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseUp;
           SchM_Exit_EcuM();

             break;
         }

         else  if((ECUM_TIMER_STARTED_E == dataCheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus)\
                 && (dataCheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout > 0))
         {
             SchM_Enter_EcuM();

             EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout=EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout - 1;

             if(EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout == 0)
             {
                 EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_TIMER_EXPIRED_E;
             }
             else{

                 flgExitSleep_u8 = CONTINUE_WAIT;
                 flgReturnValue_b = TRUE;
             }
             SchM_Exit_EcuM();
           }

         else{

         }

         }

     if(flgExitSleep_u8 == ENTER_SLEEP_E)
         {
            EcuM_Lok_ReportCheckWakeupError();

            EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_NORMAL_E;
         }
     else if(flgExitSleep_u8 == EXIT_SLEEP_E)
     {
         SchM_Enter_EcuM();

         for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ )
         {

         EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_FLAG_RESET_E;
         EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = 0;
         }
         SchM_Exit_EcuM();
     }
     else{

     }
    return flgReturnValue_b;
}

static FUNC(void, ECUM_CODE)EcuM_Lok_ReportCheckWakeupError (void)
        {
   VAR(EcuM_Lok_SleepType_Enum_ten, AUTOMATIC) dataSleepType_en = ECUM_PRV_NO_SLEEP_E;
   VAR(uint8, AUTOMATIC) dataApiId_u8 = 0x00;
   VAR(uint8, AUTOMATIC) ctrLoop1_u8 = 0x00;
   VAR(uint8, AUTOMATIC) cntrEnd_u8 = 0x00;
   VAR(uint8, AUTOMATIC) cntrExp_u8 = 0x00;
   VAR(uint8, AUTOMATIC) cntrReset_u8 = 0x00;
   VAR(EcuM_Cfg_CheckWakeupSrc_tst, AUTOMATIC) dataCheckWakeupTimer_ast[CfgSwcServiceEcuM_dNumSourceWakeup];

    SchM_Enter_EcuM();

    dataSleepType_en = EcuM_Lok_SleepReqType_en;
   for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ )
   {
    dataCheckWakeupTimer_ast[ctrLoop1_u8] = EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8];
   }
    SchM_Exit_EcuM();
        if(dataSleepType_en != ECUM_PRV_NO_SLEEP_E)
        {
            if(dataSleepType_en == ECUM_PRV_GOHALT_E)

            {
                dataApiId_u8 = ECUM_GOHALT_APIID;
            }

            else{
                dataApiId_u8 = ECUM_GOPOLL_APIID;
            }

        for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ )
        {
            if(dataCheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus == ECUM_END_CHECK_WAKEUP_E)
            {

                cntrEnd_u8++;

                SchM_Enter_EcuM();

            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_FLAG_RESET_E;
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = 0x00;

                SchM_Exit_EcuM();
            }
            else if(dataCheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus == ECUM_TIMER_EXPIRED_E)
            {

                cntrExp_u8++;

                SchM_Enter_EcuM();

            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_FLAG_RESET_E;
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = 0x00;

                SchM_Exit_EcuM();
            }

            else{

                cntrReset_u8++;
            }
        }
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            if( (cntrEnd_u8 != 0x00) && (CfgSwcServiceEcuM_dNumSourceWakeup==(cntrEnd_u8 + cntrReset_u8)) )

            {

                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, dataApiId_u8, ECUM_E_WAKEUP_NO_SOURCE_FOUND);
            }
            else if( (cntrExp_u8 != 0x00) && (CfgSwcServiceEcuM_dNumSourceWakeup==(cntrExp_u8 + cntrReset_u8)) )
            {

                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, dataApiId_u8, ECUM_E_WAKEUP_TIMEOUT);
            }
            else if(CfgSwcServiceEcuM_dNumSourceWakeup != cntrReset_u8)
            {

                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, dataApiId_u8, ECUM_E_WAKEUP_NO_SOURCE_FOUND);
            }
            else{

            }
#endif//ECUM_DEV_ERROR_DETECT
        }
            else{

            }

    return;
        }

static FUNC(void, ECUM_CODE) EcuM_Lok_ProceedSleep( uint16 dataSleepModeHandle_u16 )
{
   SchM_Enter_EcuM();
   SwcServiceEcuM_tSourceWakeup_EventsPending  ^= (SwcServiceEcuM_tSourceWakeup_EventsPending
   & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
   SwcServiceEcuM_tSourceWakeup_Validated  ^= (SwcServiceEcuM_tSourceWakeup_Validated
   & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
   EcuM_Lok_dataExpiredWakeupEvents_u32  ^= (EcuM_Lok_dataExpiredWakeupEvents_u32
   & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
   SchM_Exit_EcuM();
   BswM_EcuM_CurrentWakeup(EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask
   ,  ECUM_WKSTATUS_NONE);
   EcuM_EnableWakeupSources (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
   EcuM_Lok_CoreStatus_st.CurrentCore= ECUM_SINGLE_CORE;
   EcuM_Lok_CoreStatus_st.CurrentCoreID=0xFF;//initialise with invalid value
   EcuM_Lok_GoSleepSequence(dataSleepModeHandle_u16);
}

#endif//ECUM_SLEEP_SUPPORT_ENABLE

static FUNC(void, ECUM_CODE) EcuM_Lok_ProceedShutdown(void){
   EcuM_OnGoOffOne();
   BswM_Deinit();
   SchM_Deinit();
   ShutdownOS(E_OS_SYS_NO_RESTART);
}

static FUNC(void, ECUM_CODE ) EcuM_Lok_WakeupValidation(void)
        {
   VAR(uint8, AUTOMATIC) cntrLoopCtr_u8;
   VAR(Type_SwcServiceEcuM_tSourceWakeup,AUTOMATIC) dataPendingWakeupEvents_u32;
   VAR( uint16, ECUM_VAR) datawkpSrcValidationTimeoutCtr_u16;
        SchM_Enter_EcuM();
        dataPendingWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_EventsPending;
        datawkpSrcValidationTimeoutCtr_u16 = EcuM_Lok_WkpSrcValidationTimeoutCtr_u16;
        SchM_Exit_EcuM();
        EcuM_Lok_WakeupIndication(dataPendingWakeupEvents_u32);
        if(EcuM_Lok_dataOldPendingWakeupEvents_u32 != CfgSwcServiceEcuM_dSourceWakeupNone )
        {
            for(cntrLoopCtr_u8 = 0;cntrLoopCtr_u8 < CfgSwcServiceEcuM_dNumSourceWakeup ; cntrLoopCtr_u8++)
            {
                if((EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId & EcuM_Lok_dataOldPendingWakeupEvents_u32) != CfgSwcServiceEcuM_dSourceWakeupNone)
                {
                    EcuM_CheckValidation (EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId);
                }
                if((EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId &
                        SwcServiceEcuM_tSourceWakeup_Validated) != CfgSwcServiceEcuM_dSourceWakeupNone)
                {
                    SchM_Enter_EcuM();
                    EcuM_Lok_dataOldPendingWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_EventsPending;
                     SchM_Exit_EcuM();
                }
            }
        }
   if((datawkpSrcValidationTimeoutCtr_u16 == 0) &&
            ( (EcuM_Lok_dataOldPendingWakeupEvents_u32 & dataPendingWakeupEvents_u32) != CfgSwcServiceEcuM_dSourceWakeupNone))
   {
        SchM_Enter_EcuM();
        EcuM_Lok_dataExpiredWakeupEvents_u32 ^= EcuM_Lok_dataOldPendingWakeupEvents_u32 ;
        SwcServiceEcuM_tSourceWakeup_EventsPending ^= EcuM_Lok_dataOldPendingWakeupEvents_u32;
        EcuM_Lok_dataOldPendingWakeupEvents_u32 = CfgSwcServiceEcuM_dSourceWakeupNone;
        SchM_Exit_EcuM();
        BswM_EcuM_CurrentWakeup ( EcuM_Lok_dataExpiredWakeupEvents_u32 , ECUM_WKSTATUS_EXPIRED);
        EcuM_StopWakeupSources (EcuM_Lok_dataExpiredWakeupEvents_u32 );
   }
    EcuM_Lok_DecValidationCtr();
    return;
}

#if( ECUM_CFG_MODE_HANDLING == STD_ON)
static FUNC(void, ECUM_CODE ) EcuM_Lok_RunHandling(void){

   if( EcuM_Lok_RunMinDuration_u16 > 0 )
   {
        EcuM_Lok_RunMinDuration_u16 = EcuM_Lok_RunMinDuration_u16 - 1;
   }
     else{

   }

    EcuM_Lok_RunArbitration( );

    EcuM_Lok_PostRunArbitration( );

    return;
}

static FUNC(void, ECUM_CODE ) EcuM_Lok_RunArbitration(void)
{

   VAR( uint8, AUTOMATIC ) cntrLoopCtr_u8;

   VAR( boolean, AUTOMATIC ) UserRUNReqPending_b = FALSE;

        for( cntrLoopCtr_u8 = 0; cntrLoopCtr_u8 <ECUM_CFG_NUM_FLEX_USERS;cntrLoopCtr_u8++ )
        {

            if( EcuM_Lok_userRUNReqStatus_ab[ cntrLoopCtr_u8 ] == TRUE )
            {

                if( ( EcuM_Lok_RunRequested_u8 == ECUM_RUNSTATUS_RELEASED ) || ( EcuM_Lok_RunRequested_u8 == ECUM_RUNSTATUS_UNKNOWN ) )
                {
                    BswM_EcuM_RequestedState( ECUM_STATE_APP_RUN,ECUM_RUNSTATUS_REQUESTED );
                    EcuM_Lok_RunRequested_u8 = ECUM_RUNSTATUS_REQUESTED;

                }

                else{

                }
                UserRUNReqPending_b = TRUE;
                break;
            }
            else{

            }
        }

        if( ( EcuM_Lok_RunMinDuration_u16 == 0 ) && ( UserRUNReqPending_b == FALSE )
                && ( ( EcuM_Lok_RunRequested_u8 == ECUM_RUNSTATUS_REQUESTED ) ||  ( EcuM_Lok_RunRequested_u8 == ECUM_RUNSTATUS_UNKNOWN ) ) )
        {
            BswM_EcuM_RequestedState( ECUM_STATE_APP_RUN,ECUM_RUNSTATUS_RELEASED );
            EcuM_Lok_RunRequested_u8 = ECUM_RUNSTATUS_RELEASED;
        }
        else{

        }

        return;
}

static FUNC(void, ECUM_CODE ) EcuM_Lok_PostRunArbitration(void)
{

   VAR( uint8, AUTOMATIC ) cntrLoopCtr_u8;

   VAR( boolean, AUTOMATIC ) UserPostRUNReqPending_b = FALSE;

        for( cntrLoopCtr_u8 = 0; cntrLoopCtr_u8 < ECUM_CFG_NUM_FLEX_USERS;cntrLoopCtr_u8++ )
        {

            if( EcuM_Lok_userPostRUNReqStatus_ab[ cntrLoopCtr_u8 ] == TRUE )
            {

                if( ( EcuM_Lok_Post_Run_Requested_u8 == ECUM_RUNSTATUS_RELEASED ) || ( EcuM_Lok_Post_Run_Requested_u8 == ECUM_RUNSTATUS_UNKNOWN ) )
                {
                    BswM_EcuM_RequestedState( ECUM_STATE_APP_POST_RUN,ECUM_RUNSTATUS_REQUESTED  );
                    EcuM_Lok_Post_Run_Requested_u8 = ECUM_RUNSTATUS_REQUESTED;
                }

                else{

                }
                UserPostRUNReqPending_b = TRUE;
                break;
            }
            else{

            }
        }

        if( ( EcuM_Lok_RunMinDuration_u16 == 0 ) && ( UserPostRUNReqPending_b == FALSE )
                && ( ( EcuM_Lok_Post_Run_Requested_u8 == ECUM_RUNSTATUS_REQUESTED ) || ( EcuM_Lok_Post_Run_Requested_u8 == ECUM_RUNSTATUS_UNKNOWN ) ) )
        {
            BswM_EcuM_RequestedState( ECUM_STATE_APP_POST_RUN,ECUM_RUNSTATUS_RELEASED );
            EcuM_Lok_Post_Run_Requested_u8 = ECUM_RUNSTATUS_RELEASED;
        }
        else{

        }

        return;
}
#endif//ECUM_CFG_MODE_HANDLING

static FUNC(Std_ReturnType , ECUM_CODE ) EcuM_Lok_ShutdownSynchronization(void)
 {
   VAR(Std_ReturnType, AUTOMATIC) return_value = E_NOT_OK;
#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
   VAR(EcuM_Lok_SleepType_Enum_ten, AUTOMATIC)     id_RequestedSleepType_en;
   VAR(boolean, AUTOMATIC) flgWakeRestartStatus_b = FALSE;

   VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC) dataSleepModeHandle_u16 = 0xFF;
   VAR(boolean, AUTOMATIC) flgContinueWakeupCheck_b = FALSE;
   VAR(EcuM_Lok_WakeupRestartReason_Enum_ten, AUTOMATIC)  stWakeupRestartReason_en = ECUM_PRV_NORMAL_E;

    SchM_Enter_EcuM();
   stWakeupRestartReason_en = EcuM_Lok_WakeupRestartReason_en;
    SchM_Exit_EcuM();

   if(ECUM_PRV_CHECK_WAKEUP_PENDING_E == stWakeupRestartReason_en)
   {
        flgContinueWakeupCheck_b = EcuM_Lok_CheckWakeupTimerHandling();
   }

   if(flgContinueWakeupCheck_b == FALSE)
   {
    SchM_Enter_EcuM();

    dataSleepModeHandle_u16 = EcuM_Lok_SleepMode_u16;

   id_RequestedSleepType_en = EcuM_Lok_SleepReqType_en;

    SchM_Exit_EcuM();

   if( (ECUM_PRV_GOHALT_E == id_RequestedSleepType_en) || ( ECUM_PRV_GOPOLL_E == id_RequestedSleepType_en ))
   {
        EcuM_Lok_ProceedSleep(dataSleepModeHandle_u16);
   }
   else{

   }

    SchM_Enter_EcuM();

    flgWakeRestartStatus_b  = EcuM_Lok_flgwakeupRestart_b;

    SchM_Exit_EcuM();

   if( FALSE != flgWakeRestartStatus_b)
   {
        EcuM_Lok_WakeupRestartSequence(dataSleepModeHandle_u16);
   }

   if((((ECUM_PRV_GOPOLL_E != id_RequestedSleepType_en) &&
            (ECUM_PRV_GOHALT_E != id_RequestedSleepType_en)) && (TRUE != flgWakeRestartStatus_b)))
   {
#endif//ECUM_SLEEP_SUPPORT_ENABLE
        if(FALSE != EcuM_Lok_flgGoDown_b)
        {
            EcuM_Lok_ProceedShutdown();
            return_value = E_OK;
        }
        else{
        }
#if ECUM_SLEEP_SUPPORT_ENABLE
   }
   }
   else{

        return_value = E_OK;
   }
#endif//ECUM_SLEEP_SUPPORT_ENABLE
    return return_value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"
