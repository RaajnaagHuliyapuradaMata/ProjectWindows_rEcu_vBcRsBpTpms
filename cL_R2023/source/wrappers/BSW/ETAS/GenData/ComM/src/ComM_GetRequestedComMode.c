

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

Std_ReturnType ComM_GetRequestedComMode(ComM_UserHandleType User, ComM_ModeType * ComMode)
{

    ComM_UserVarType_tst *      userRamPtr_pst;

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    if (ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_REQ_COMMODE_APIID,COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
    }

    if (ComMode == NULL_PTR)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_REQ_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }

    if ( ComM_Lok_ValidateUserId(User) == FALSE )
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_REQ_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif

    User = ComM_UserId_MappingTable_acst[User];
    userRamPtr_pst = &ComM_UserStruct[User];

    *ComMode = userRamPtr_pst->RequestedUserMode_u8 ;

    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

