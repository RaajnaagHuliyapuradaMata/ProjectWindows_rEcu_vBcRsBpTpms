

#include "ComM_Priv.h"

#if (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(Std_ReturnType, COMM_CODE) ComM_LimitChannelToNoComMode
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel,
                                        VAR(boolean, COMM_VAR) Status
                                        )
{

    VAR(Std_ReturnType, AUTOMATIC) ret_Val;

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
       (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_LIMIT_CHNLTO_NOCOMMODE_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }

    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_LIMIT_CHNLTO_NOCOMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif

    ret_Val = ComM_LProcessLimitToNoCom(Channel,Status);

    return ret_Val;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif

