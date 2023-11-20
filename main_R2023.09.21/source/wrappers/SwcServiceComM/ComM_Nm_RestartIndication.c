#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(void,COMM_CODE) ComM_Nm_RestartIndication (VAR(NetworkHandleType,AUTOMATIC) Channel)
{

   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

   channelRamPtr_ps = &ComM_ChannelStruct[Channel];
   channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_RESTARTINDICATION,COMM_E_NOT_INITED);
        return;
   }

   if(Channel >= COMM_NO_OF_CHANNELS)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_RESTARTINDICATION,COMM_E_WRONG_PARAMETERS);\
        return;
   }
#endif

   if((channelConfigPtr_pcs->ComMNmVariant_e==FULL)||(channelConfigPtr_pcs->ComMNmVariant_e==PASSIVE))
   {
        SchM_Enter_ComM_ChannelNoNest();

        if( channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION )
        {
            COMM_SET_BIT((channelRamPtr_ps->PassiveRequestState_u8),(0x02));
        }

        SchM_Exit_ComM_ChannelNoNest();

   }
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

