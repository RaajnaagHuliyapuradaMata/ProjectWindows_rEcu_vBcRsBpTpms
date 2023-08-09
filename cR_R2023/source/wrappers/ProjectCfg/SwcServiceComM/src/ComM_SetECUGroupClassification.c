

#include "ComM_Priv.h"

#if (COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(Std_ReturnType, COMM_CODE) ComM_SetECUGroupClassification
                                        (
                                        VAR(ComM_InhibitionStatusType,COMM_VAR) Status
                                        )
{

    VAR(Std_ReturnType, AUTOMATIC) retVal_e;

    retVal_e = E_NOT_OK;

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_SET_ECUGROUPCLASS_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }
    #endif

    ComM_GlobalStruct.ComM_EcuGroupClassification_u8 = Status;
    retVal_e = E_OK;
    return retVal_e;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif

