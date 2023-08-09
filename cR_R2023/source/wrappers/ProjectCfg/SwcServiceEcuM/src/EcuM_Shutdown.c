

#include "EcuM.h"

#include "EcuM_Callout.h"

#include "EcuM_Cfg_SchM.h"

#include "EcuM_RunTime.h"

#include "Mcu.h" 		
#if (!defined(MCU_AR_RELEASE_MAJOR_VERSION) || (MCU_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(MCU_AR_RELEASE_MINOR_VERSION) || (MCU_AR_RELEASE_MINOR_VERSION != 2))
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

#include "EcuM_Prv.h"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDown( VAR(uint16, AUTOMATIC) caller)
{

    VAR(boolean, AUTOMATIC) flgModuleValid_b = FALSE;
    VAR(uint8, AUTOMATIC) cntrLoop_u8;

    VAR(Std_ReturnType, AUTOMATIC) return_value;

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

            for (cntrLoop_u8 = 0; cntrLoop_u8 < ECUM_CFG_GODOWN_CALLER_ARR_LEN; cntrLoop_u8++)
            {
                if (EcuM_Cfg_idxGoDownValidCallerArr_au16[cntrLoop_u8] == caller)
                {
                    flgModuleValid_b = TRUE;
                    break;
                }
            }

            if( flgModuleValid_b == FALSE)
            {

                return_value =  E_NOT_OK;
            }
            else
            {

                SchM_Enter_EcuM();
                if( !(((SwcServiceEcuM_stInfoTargetShutdown.ShutdownTarget) == ECUM_SHUTDOWN_TARGET_OFF)
                        || (((SwcServiceEcuM_stInfoTargetShutdown.ShutdownTarget) == ECUM_SHUTDOWN_TARGET_RESET))))
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

FUNC(void , ECUM_CODE) EcuM_Shutdown(void )
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

        if(SwcServiceEcuM_stInfoTargetShutdown.ShutdownTarget == ECUM_SHUTDOWN_TARGET_RESET)
        {

            EcuM_AL_Reset( (EcuM_ResetType) SwcServiceEcuM_stInfoTargetShutdown.mode);
        }
        else
        {
            EcuM_AL_SwitchOff();
        }
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

