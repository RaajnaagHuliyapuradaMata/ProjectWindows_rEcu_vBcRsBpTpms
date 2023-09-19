#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#if(COMM_INHIBITION_ENABLED)
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(Std_ReturnType, COMM_CODE) ComM_GetInhibitionStatus
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel
   ,     P2VAR(ComM_InhibitionStatusType, AUTOMATIC, COMM_VAR) Status
                                        )
{

   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;

   channelRamPtr_ps = &ComM_ChannelStruct[Channel];

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_INHIBITION_STATUS_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
   }

   if(Channel >= COMM_NO_OF_CHANNELS)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_INHIBITION_STATUS_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }

   if(Status == NULL_PTR)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_INHIBITION_STATUS_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }
#endif

    *Status = channelRamPtr_ps->InhibitionReqStatus_u8;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

