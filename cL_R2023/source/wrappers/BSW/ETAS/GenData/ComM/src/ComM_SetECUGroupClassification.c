

#include "ComM_Priv.h"

#if (COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

Std_ReturnType ComM_SetECUGroupClassification(ComM_InhibitionStatusType Status)
{

    Std_ReturnType retVal_u8;

    retVal_u8 = E_NOT_OK;

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_SET_ECUGROUPCLASS_APIID,COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
    }
    #endif

    ComM_GlobalStruct.ComM_EcuGroupClassification_u8 = Status;
    retVal_u8 = E_OK;
    return retVal_u8;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

