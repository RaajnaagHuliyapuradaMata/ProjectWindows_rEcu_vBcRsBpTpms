

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComM_EcuM_PNCWakeUpIndication(PNCHandleType PNCid)
{
#if(COMM_PNC_ENABLED != STD_OFF)

   ComM_PncRamStructType_tst *              pncRamPtr_pst;
   ComM_ChannelVarType_tst *                channelRamPtr_pst;
#if(COMM_SYNCHRONOUS_WAKE_UP != STD_ON )
   const ComM_PncConfigStruct_tst *        pncConfigPtr_pcst;
   uint8                                   numChannels;
#endif
   uint8                                loopCtr_u8;

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_PNCWAKEUP_INDICATION,COMM_E_NOT_INITED);
        return;
   }

   if(PNCid >= COMM_NO_OF_PNCS)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_PNCWAKEUP_INDICATION,COMM_E_WRONG_PARAMETERS);
        return;
   }
#endif

    pncRamPtr_pst = &ComM_PncRamStruct[PNCid];
#if(COMM_SYNCHRONOUS_WAKE_UP != STD_ON )
    pncConfigPtr_pcst = &(COMM_GET_PNC_LIST[PNCid]);
    numChannels = pncConfigPtr_pcst->NumChannels_u8;
#endif

   if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
   {

        SchM_Enter_ComM_PNCWakeUpNoNest();
        if(pncRamPtr_pst->PncState_en == COMM_PNC_NO_COMMUNICATION)
        {
            pncRamPtr_pst->WakeUpStatus_b = TRUE;
        }
        SchM_Exit_ComM_PNCWakeUpNoNest();

        SchM_Enter_ComM_ChannelNoNest();

#if(COMM_SYNCHRONOUS_WAKE_UP != STD_ON )

        for(loopCtr_u8 = C_ZERO; loopCtr_u8 < numChannels ;loopCtr_u8++)
        {
            uint8 ChannelId;

            ChannelId = (pncConfigPtr_pcst->Channels_pcu8[loopCtr_u8]);

            channelRamPtr_pst = &ComM_ChannelStruct[ChannelId];

            if(channelRamPtr_pst->ChannelMode_u8 == COMM_NO_COMMUNICATION)
            {
                COMM_SET_BIT((channelRamPtr_pst -> PassiveRequestState_u8),(0x01));
            }
        }

#endif

#if(COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )

        for(loopCtr_u8 = C_ZERO; loopCtr_u8 < COMM_NO_OF_CHANNELS ;loopCtr_u8++)
        {
            channelRamPtr_pst = &ComM_ChannelStruct[loopCtr_u8];

            if(channelRamPtr_pst->ChannelMode_u8 == COMM_NO_COMMUNICATION)
            {
                COMM_SET_BIT((channelRamPtr_pst -> PassiveRequestState_u8),(0x01));
            }

        }
#endif

        SchM_Exit_ComM_ChannelNoNest();
   }

#else

    (void)(PNCid);

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

    (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_PNCWAKEUP_INDICATION,COMM_E_ERROR_IN_PROV_SERVICE);
    return;

#endif

#endif
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

