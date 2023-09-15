

#include "ComM_Priv.hpp"

#if(COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

Std_ReturnType ComM_GetInhibitionStatus(NetworkHandleType Channel, ComM_InhibitionStatusType * Status)
{

   ComM_ChannelVarType_tst *  channelRamPtr_pst;

   channelRamPtr_pst = &ComM_ChannelStruct[Channel];

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_INHIBITION_STATUS_APIID,COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
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

    *Status = channelRamPtr_pst->InhibitionReqStatus_u8;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

