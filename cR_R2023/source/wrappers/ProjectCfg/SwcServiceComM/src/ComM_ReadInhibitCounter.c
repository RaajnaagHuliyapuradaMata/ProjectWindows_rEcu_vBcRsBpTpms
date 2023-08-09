

#include "ComM_Priv.h"

#if (COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(Std_ReturnType, COMM_CODE) ComM_ReadInhibitCounter
                                        (
                                          P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue
                                        )
{

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_READ_INHIBIT_COUNTER_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }

    if (CounterValue == NULL_PTR)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_READ_INHIBIT_COUNTER_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif

    *CounterValue = ComM_GlobalStruct.ComM_InhibitCounter_u16;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif

