

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComM_EcuM_WakeUpIndication(NetworkHandleType Channel)
{

#if(COMM_SYNCHRONOUS_WAKE_UP == STD_OFF )
   ComM_ChannelVarType_tst *       channelRamPtr_pst;
#if(COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)
   ComM_ChannelVarType_tst *       masterChannelRamPtr_pst;
   const ComM_ChannelType_tst *    channelConfigPtr_pcst;
   uint8                           masterChannelId_u8;
#endif
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_WAKEUP_INDICATION,COMM_E_NOT_INITED);
        return;
   }

   if(Channel >= COMM_NO_OF_CHANNELS)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_WAKEUP_INDICATION,COMM_E_WRONG_PARAMETERS);
        return;
   }
#endif

#if(COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )

   ComM_Lok_SyncWakeUpIndication();

#else

   channelRamPtr_pst = &ComM_ChannelStruct[Channel];

    SchM_Enter_ComM_ChannelNoNest();

   if(channelRamPtr_pst->ChannelMode_u8 == COMM_NO_COMMUNICATION)
   {
#if(COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)
        channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[Channel]);
        if(channelConfigPtr_pcst->ComMMasterChannelPresent_b == TRUE)
        {

            masterChannelId_u8 = channelConfigPtr_pcst->masterChannelId_u8;
            masterChannelRamPtr_pst = &ComM_ChannelStruct[masterChannelId_u8];

            if(masterChannelRamPtr_pst->ChannelMode_u8 == COMM_NO_COMMUNICATION)
            {
                COMM_SET_BIT((masterChannelRamPtr_pst ->PassiveRequestState_u8 ),(0x01));
            }
        }
#endif

        COMM_SET_BIT((channelRamPtr_pst ->PassiveRequestState_u8 ),(0x01));
   }
    SchM_Exit_ComM_ChannelNoNest();

#endif

    (void)(Channel);
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

