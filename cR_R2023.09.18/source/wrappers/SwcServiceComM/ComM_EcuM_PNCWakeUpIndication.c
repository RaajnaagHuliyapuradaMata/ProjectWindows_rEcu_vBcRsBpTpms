#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC (void,COMM_CODE) ComM_EcuM_PNCWakeUpIndication
                                            (
                                            VAR(PNCHandleType,AUTOMATIC) PNCid
                                            )
{
#if(COMM_PNC_ENABLED != STD_OFF)

#if(COMM_SYNCHRONOUS_WAKE_UP == STD_OFF)

   P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
   P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;
   uint8 numChannels;
   VAR(uint8,AUTOMATIC) loopCtr_u8;

#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
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

#if(COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )

   if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
   {
        ComM_LSyncWakeUpIndication();
   }

#else

    pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[PNCid]);
    numChannels = pncConfigPtr_pcs->NumChannels;

    pncRamPtr_ps = &ComM_PncRamStruct[PNCid];

   if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
   {

        SchM_Enter_ComM_PNCWakeUpNoNest();
        if(pncRamPtr_ps->PncState_e == COMM_PNC_NO_COMMUNICATION)
        {
            pncRamPtr_ps->WakeUpStatus_b = TRUE;
        }
        SchM_Exit_ComM_PNCWakeUpNoNest();

        SchM_Enter_ComM_ChannelNoNest();
        for(loopCtr_u8 = 0; loopCtr_u8 < numChannels ;loopCtr_u8++)
        {
            uint8 ChannelId;

            ChannelId = (pncConfigPtr_pcs->Channels[loopCtr_u8]);

            channelRamPtr_ps = &ComM_ChannelStruct[ChannelId];

            if(channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)
            {
                COMM_SET_BIT((channelRamPtr_ps -> PassiveRequestState_u8),(0x01));
            }
        }
        SchM_Exit_ComM_ChannelNoNest();
   }

#endif

#if((COMM_DEV_ERROR_DETECT == STD_OFF) && (COMM_SYNCHRONOUS_WAKE_UP != STD_OFF))
    (void)(PNCid);
#endif

#else

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

    (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_PNCWAKEUP_INDICATION,COMM_E_ERROR_IN_PROV_SERVICE);
    return;

#endif

#endif
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

