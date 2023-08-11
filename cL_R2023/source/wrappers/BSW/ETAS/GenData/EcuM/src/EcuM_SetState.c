

#include "EcuM.h"

#if (ECUM_CFG_MODE_HANDLING == STD_ON)

#include "EcuM_Cfg_SchM.h"

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

#include "EcuM_Lok_RteActions.h"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.h"

void EcuM_SetState( EcuM_StateType state)
{

    if (TRUE != SwcServiceEcuM_bIsInitialised)
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SETSTATE_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT
    }
    else
    {

        switch(state)
        {

            case ECUM_STATE_STARTUP:

                (void)EcuM_Lok_RteModeSwitch(RTE_MODE_EcuM_Mode_STARTUP);
                break;

            case ECUM_STATE_APP_RUN:

                (void)EcuM_Lok_RteModeSwitch(RTE_MODE_EcuM_Mode_RUN);
                break;

            case ECUM_STATE_APP_POST_RUN:

                (void)EcuM_Lok_RteModeSwitch(RTE_MODE_EcuM_Mode_POST_RUN);
                break;

            case ECUM_STATE_SHUTDOWN:

                (void)EcuM_Lok_RteModeSwitch(RTE_MODE_EcuM_Mode_SHUTDOWN);
                break;

           case ECUM_STATE_SLEEP:

                (void)EcuM_Lok_RteModeSwitch(RTE_MODE_EcuM_Mode_SLEEP);
                 break;

            default :
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                   (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SETSTATE_APIID, ECUM_E_STATE_PAR_OUT_OF_RANGE );
#endif//ECUM_DEV_ERROR_DETECT
                   break;

        }

   }

    return;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#else

#endif
