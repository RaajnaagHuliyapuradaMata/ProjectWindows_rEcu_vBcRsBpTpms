

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

Std_ReturnType ComM_GetStatus(ComM_InitStatusType * Status)
{

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (Status == NULL_PTR)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATUS_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }

    if (ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATUS_APIID,COMM_E_NOT_INITED);

        *Status = COMM_UNINIT;
        return COMM_E_NOT_INITIALIZED;
    }
    #endif

    *Status = ComM_GlobalStruct.ComM_InitStatus_en;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

