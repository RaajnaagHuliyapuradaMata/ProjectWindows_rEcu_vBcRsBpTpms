

#include "EcuM.hpp"

#if(ECUM_SLEEP_SUPPORT_ENABLE != FALSE)

#include "SchM_EcuM.hpp"

#include "EcuM_Cfg_SchM.hpp"

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
//#if(!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
// #error "AUTOSAR major version undefined or mismatched"
//#endif
//#if(!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
// #error "AUTOSAR minor version undefined or mismatched"
//#endif
#endif

#include "EcuM_Prv.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.hpp"

Std_ReturnType EcuM_GoHalt(void){
   boolean FlagGoHaltCalledAgain_b = FALSE;
    Std_ReturnType return_value = E_NOT_OK;

    Type_SwcServiceEcuM_tModeShutdown SleepMode_u16 =0xFF;

    Type_SwcServiceEcuM_tTargetShutdown shutdownTarget_u8 = ECUM_SHUTDOWN_TARGET_RESET;

   if(FALSE != SwcServiceEcuM_bIsInitialised)
   {

        if(FALSE == EcuM_Lok_flgwakeupRestart_b)
        {
                SchM_Enter_EcuM();

                if(ECUM_PRV_NO_SLEEP_E == EcuM_Lok_SleepReqType_en)
                {

                    shutdownTarget_u8 = SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown;
                    SleepMode_u16 = SwcServiceEcuM_stInfoTargetShutdown.mode;

                        if((ECUM_SHUTDOWN_TARGET_SLEEP == shutdownTarget_u8 ) && (SleepMode_u16 <
                                ECUM_CFG_NUM_SLEEP_MODES) &&
                                (TRUE == EcuM_Cfg_idxSleepModes_au32[SleepMode_u16].IsCPUSuspend) &&
                                    (CfgSwcServiceEcuM_dSourceWakeupNone != EcuM_Cfg_idxSleepModes_au32[SleepMode_u16].WakeupSourceMask ))
                        {
                            EcuM_Lok_SleepReqType_en = ECUM_PRV_GOHALT_E;
                            EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_NORMAL_E;

                            EcuM_Lok_flgShutdownInfoDoNotUpdate_b = TRUE;
                            return_value= E_OK;
                        }
                }//if(ECUM_PRV_NO_SLEEP_E == EcuM_Lok_SleepReqType_en)
                else{

                    if(ECUM_PRV_GOHALT_E == EcuM_Lok_SleepReqType_en)
                    {

                        FlagGoHaltCalledAgain_b= TRUE;
                        return_value= E_OK;

                    }//if(ECUM_PRV_GOHALT_E == EcuM_Lok_SleepReqType_en)
                    else
                    {

                    }
                }
                SchM_Exit_EcuM();
        }//if(FALSE == EcuM_Lok_flgwakeupRestart_b)
        else{

        }

   }//if(TRUE == SwcServiceEcuM_bIsInitialised)
   else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GOHALT_APIID, ECUM_E_UNINIT);
#endif//ECUM_DEV_ERROR_DETECT

   }
   if((FALSE == FlagGoHaltCalledAgain_b) && (E_OK == return_value  ))
   {
          SchM_Enter_EcuM();
          EcuM_Lok_SleepMode_u16 = SleepMode_u16;
          SchM_Exit_EcuM();
   }
    return return_value;
}

Std_ReturnType EcuM_GoPoll(void){
   boolean FlagGoPollCalledAgain_b = FALSE;
    Std_ReturnType return_value = E_NOT_OK;
    Type_SwcServiceEcuM_tModeShutdown SleepMode_u16 =0xFF;
    Type_SwcServiceEcuM_tTargetShutdown shutdownTarget_u8 = ECUM_SHUTDOWN_TARGET_RESET;
   if(FALSE != SwcServiceEcuM_bIsInitialised)
   {

        if(FALSE == EcuM_Lok_flgwakeupRestart_b)
        {
                SchM_Enter_EcuM();

                if(ECUM_PRV_NO_SLEEP_E == EcuM_Lok_SleepReqType_en)
                {

                    shutdownTarget_u8 = SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown;
                    SleepMode_u16 = SwcServiceEcuM_stInfoTargetShutdown.mode;

                        if((ECUM_SHUTDOWN_TARGET_SLEEP == shutdownTarget_u8 ) && (SleepMode_u16 <
                                ECUM_CFG_NUM_SLEEP_MODES) &&
                                (FALSE == EcuM_Cfg_idxSleepModes_au32[SleepMode_u16].IsCPUSuspend))

                        {
                            EcuM_Lok_SleepReqType_en = ECUM_PRV_GOPOLL_E;
                            EcuM_Lok_WakeupRestartReason_en = ECUM_PRV_NORMAL_E;

                            EcuM_Lok_flgShutdownInfoDoNotUpdate_b = TRUE;
                            return_value= E_OK;
                        }
                }//if(ECUM_PRV_NO_SLEEP_E == EcuM_Lok_SleepReqType_en)
                else{

                    if(ECUM_PRV_GOPOLL_E == EcuM_Lok_SleepReqType_en)
                    {

                        FlagGoPollCalledAgain_b= TRUE;
                        return_value= E_OK;

                    }//if(ECUM_PRV_GOPOLL_E == EcuM_Lok_SleepReqType_en)
                    else
                    {

                    }
                }
                SchM_Exit_EcuM();
        }
        else{

        }

   }
   else{
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GOPOLL_APIID, ECUM_E_UNINIT);
#endif//ECUM_DEV_ERROR_DETECT

   }
   if((FALSE == FlagGoPollCalledAgain_b) && (E_OK == return_value  ))
   {
          SchM_Enter_EcuM();
          EcuM_Lok_SleepMode_u16 = SleepMode_u16;
          SchM_Exit_EcuM();
   }
    return return_value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.hpp"

#endif//ECUM_SLEEP_SUPPORT_ENABLE
