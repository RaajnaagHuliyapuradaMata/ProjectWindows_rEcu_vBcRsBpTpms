

#include "EcuM.h"

#if (ECUM_CFG_MODE_HANDLING == STD_ON)

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

Std_ReturnType EcuM_RequestPOST_RUN( EcuM_UserType user)

{
    Std_ReturnType Return_Value = E_NOT_OK;
    EcuM_UserType User_u16 = user;

    if(FALSE != EcuM_Lok_IsUserHandlingPossible_b(&User_u16, ECUM_REQUESTPOST_RUN_APIID))
    {
        if(FALSE == EcuM_Lok_userPostRUNReqStatus_ab[User_u16])
        {

            EcuM_Lok_userPostRUNReqStatus_ab[User_u16] = TRUE;

            Return_Value = E_OK;
        }
        else
        {

            #if (ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID,ECUM_REQUESTPOST_RUN_APIID, ECUM_E_MULTIPLE_RUN_REQUESTS);
            #endif//ECUM_DEV_ERROR_DETECT
        }
    }

    return Return_Value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.h"

#else

#endif

