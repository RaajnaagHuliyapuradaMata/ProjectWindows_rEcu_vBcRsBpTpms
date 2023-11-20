#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC (void,COMM_CODE) ComM_EcuM_WakeUpIndication
                                            (
                                                VAR(NetworkHandleType,AUTOMATIC) Channel
                                            )
{

#if(COMM_SYNCHRONOUS_WAKE_UP == STD_OFF )
   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
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

   ComM_LSyncWakeUpIndication();

#else

   channelRamPtr_ps = &ComM_ChannelStruct[Channel];

    SchM_Enter_ComM_ChannelNoNest();

   if(channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)
   {

        COMM_SET_BIT((channelRamPtr_ps ->PassiveRequestState_u8 ),(0x01));

   }
    SchM_Exit_ComM_ChannelNoNest();

#endif

    (void)(Channel);
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

