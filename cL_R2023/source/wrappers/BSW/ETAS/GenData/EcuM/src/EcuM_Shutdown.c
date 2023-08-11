

#include "EcuM.h"

#include "EcuM_Callout.h"

#include "EcuM_Cfg_SchM.h"

#include "EcuM_RunTime.h"

#include "Mcu.h" 		
// #if (!defined(MCU_AR_RELEASE_MAJOR_VERSION) || (MCU_AR_RELEASE_MAJOR_VERSION != 4))
// #error "AUTOSAR major version undefined or mismatched"
// #endif
// #if (!defined(MCU_AR_RELEASE_MINOR_VERSION) || ((MCU_AR_RELEASE_MINOR_VERSION != 2) && (MCU_AR_RELEASE_MINOR_VERSION != 3)))
// #error "AUTOSAR minor version undefined or mismatched"
// #endif

#include "Os.h" 		
// #if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
// #error "AUTOSAR major version undefined or mismatched"
// #endif
// #if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
// #error "AUTOSAR minor version undefined or mismatched"
// #endif

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
// #if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
// #error "AUTOSAR major version undefined or mismatched"
// #endif
// #if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
// #error "AUTOSAR minor version undefined or mismatched"
// #endif
#endif

#include "EcuM_Prv.h"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"

Std_ReturnType EcuM_GoDownHaltPoll( uint16 caller)
{
	Std_ReturnType return_value;

    if ( SwcServiceEcuM_bIsInitialised == FALSE )
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GODOWNHALTPOLL_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT
        return_value = E_NOT_OK;
    }
	else
    {
		if ((ECUM_SHUTDOWN_TARGET_OFF == SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown ) || (ECUM_SHUTDOWN_TARGET_RESET == SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown ))
		{
			return_value = EcuM_GoDown(caller);
		}
		#if (ECUM_SLEEP_SUPPORT_ENABLE != FALSE)
		else if ((ECUM_SHUTDOWN_TARGET_SLEEP == SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown ) && (SwcServiceEcuM_stInfoTargetShutdown.mode < ECUM_CFG_NUM_SLEEP_MODES) && (FALSE == EcuM_Cfg_idxSleepModes_au32[SwcServiceEcuM_stInfoTargetShutdown.mode].IsCPUSuspend))
		{
			return_value = EcuM_GoPoll();
		}
		else if( (ECUM_SHUTDOWN_TARGET_SLEEP == SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown ) && (SwcServiceEcuM_stInfoTargetShutdown.mode < ECUM_CFG_NUM_SLEEP_MODES) && (TRUE == EcuM_Cfg_idxSleepModes_au32[SwcServiceEcuM_stInfoTargetShutdown.mode].IsCPUSuspend ) )
		{
			return_value =  EcuM_GoHalt();
		}
		#endif //ECUM_SLEEP_SUPPORT_ENABLE
		else
		{
			return_value = E_NOT_OK;
		}
	}
    return return_value;
}

Std_ReturnType EcuM_GoDown( uint16 caller)
{

    boolean flgModuleValid_b = FALSE;
	
	#ifdef ECUM_CFG_GODOWN_CALLER_ARR_LEN
		uint8 cntrLoop_u8;
	#endif
	
    Std_ReturnType return_value;

    if ( SwcServiceEcuM_bIsInitialised == FALSE )
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GODOWN_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT

        return_value = E_NOT_OK;
    }
    else
    {

        if(EcuM_Lok_flgGoDown_b != FALSE)
        {

            return_value = E_OK;
        }
        else
        {
			#ifdef ECUM_CFG_GODOWN_CALLER_ARR_LEN

            for (cntrLoop_u8 = 0; cntrLoop_u8 < ECUM_CFG_GODOWN_CALLER_ARR_LEN; cntrLoop_u8++)
            {
                if (EcuM_Cfg_idxGoDownValidCallerArr_au16[cntrLoop_u8] == caller)
                {
                    flgModuleValid_b = TRUE;
                    break;
                }
            }
			#else
				
				(void)caller;
			#endif
			

            if( flgModuleValid_b == FALSE)
            {

                return_value =  E_NOT_OK;
            }
            else
            {

                SchM_Enter_EcuM();
                if( !(((SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown) == ECUM_SHUTDOWN_TARGET_OFF)
                        || (((SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown) == ECUM_SHUTDOWN_TARGET_RESET))))
                {
                    return_value = E_NOT_OK;
                }
                else
                {

                    EcuM_Lok_flgGoDown_b   =   TRUE;

                    EcuM_Lok_flgShutdownInfoDoNotUpdate_b = TRUE;

                    SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseShutdownOsPre;
                    return_value = E_OK;
                }
                SchM_Exit_EcuM();
        }
    }
    }
    return return_value;
}

void EcuM_Shutdown(void )
{
	    if ( SwcServiceEcuM_bIsInitialised == FALSE )
        {
            #if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SHUTDOWN_APIID, ECUM_E_UNINIT );
            #endif
			return;
        }
	    SwcServiceEcuM_ePhase = SwcServiceEcuM_ePhaseShutdownOsPost;
        EcuM_OnGoOffTwo();
        if(SwcServiceEcuM_stInfoTargetShutdown.tTargetShutdown == ECUM_SHUTDOWN_TARGET_RESET)
        {
            EcuM_AL_Reset( (EcuM_ResetType) SwcServiceEcuM_stInfoTargetShutdown.mode);
        }
        else
        {
            EcuM_AL_SwitchOff();
        }
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

