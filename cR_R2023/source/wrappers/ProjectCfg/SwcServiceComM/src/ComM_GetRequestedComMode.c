

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(Std_ReturnType,COMM_CODE) ComM_GetRequestedComMode
                                                    (
                                                    VAR(ComM_UserHandleType, COMM_VAR) User ,
                                                    P2VAR(ComM_ModeType, AUTOMATIC, COMM_VAR) ComMode
                                                    )
{

    VAR(Std_ReturnType,AUTOMATIC) ReturnStatus;
    P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;

    ReturnStatus = E_NOT_OK ;

    userRamPtr_ps = &ComM_UserStruct[User];

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_REQ_COMMODE_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }

    if (ComMode == NULL_PTR)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_REQ_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }

    if (User >= COMM_NO_OF_USERS)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_REQ_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif

    *ComMode = userRamPtr_ps->RequestedUserMode_t ;

    ReturnStatus = E_OK;
    return ReturnStatus;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

