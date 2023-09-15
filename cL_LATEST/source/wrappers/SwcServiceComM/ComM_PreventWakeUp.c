

#include "ComM_Priv.hpp"

#if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

Std_ReturnType ComM_PreventWakeUp(NetworkHandleType Channel, boolean Status)
{

   ComM_ChannelVarType_tst * channelRamPtr_pst;

   channelRamPtr_pst = &ComM_ChannelStruct[Channel];

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_PREVENT_WAKEUP_APIID,COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
   }

   if(Channel >= COMM_NO_OF_CHANNELS)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_PREVENT_WAKEUP_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }
#endif

   if((COMM_GET_PREVENT_WAKEUP((channelRamPtr_pst->InhibitionReqStatus_u8))) != Status)
   {
        SchM_Enter_ComM_LimitationNoNest();

        if(Status != FALSE)
        {
            COMM_SET_PREVENT_WAKEUP((channelRamPtr_pst->InhibitionReqStatus_u8));
        }
        else{
            COMM_CLR_PREVENT_WAKEUP((channelRamPtr_pst->InhibitionReqStatus_u8));
        }

        ComM_Lok_TranslateInhibitionStatus(Channel,COMM_PREVENTWAKEUP,Status);

        SchM_Exit_ComM_LimitationNoNest();
   }
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

