#include "Std_Types.hpp"

#include "EcuM.hpp"

#if(ECUM_CFG_MODE_HANDLING == STD_ON)

#include "EcuM_Cfg_SchM.hpp"

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#if(!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "BswM_EcuM.hpp"
#if(!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "EcuM_Prv.hpp"
#include "EcuM_Lok_RteActions.hpp"

//FUNC(void, BSWM_CODE) BswM_EcuM_CurrentState(VAR(uint8, AUTOMATIC) CurrentState);

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"

FUNC(void , ECUM_CODE) EcuM_Rn_CurrentState(void){

   VAR(uint8, AUTOMATIC) return_value;

   if( TRUE != SwcServiceEcuM_bIsInitialised )
   {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )

        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_RB_CURRENTSTATE_APIID, ECUM_E_UNINIT );

#endif

   }
   else{

        return_value = EcuM_Lok_GetRteMode();

        switch( return_value )
        {

            case RTE_MODE_EcuM_Mode_STARTUP:
                BswM_EcuM_CurrentState( ECUM_STATE_STARTUP );
                break;

            case RTE_MODE_EcuM_Mode_RUN:
                BswM_EcuM_CurrentState( ECUM_STATE_APP_RUN );
                break;

            case RTE_MODE_EcuM_Mode_POST_RUN:
                BswM_EcuM_CurrentState( ECUM_STATE_APP_POST_RUN );
                break;

            case RTE_MODE_EcuM_Mode_SHUTDOWN:
                BswM_EcuM_CurrentState( ECUM_STATE_SHUTDOWN );
                break;

            case RTE_MODE_EcuM_Mode_SLEEP:
                BswM_EcuM_CurrentState( ECUM_STATE_SLEEP );
                break;

            default :
                //nothing to be executed here
                break;

        }
   }

    return;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"

#else

#endif//ECUM_CFG_MODE_HANDLING

