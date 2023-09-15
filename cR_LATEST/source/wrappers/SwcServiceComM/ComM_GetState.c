#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(Std_ReturnType, COMM_CODE) ComM_GetState
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel
   ,     P2VAR(ComM_StateType, AUTOMATIC, COMM_VAR) State
                                        )
{

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
   }

   if(Channel >= COMM_NO_OF_CHANNELS)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }

   if(State == NULL_PTR)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }
#endif

    *State = ComM_ChannelStruct[Channel].ChannelState_e;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

