#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC (void,COMM_CODE)ComM_CommunicationAllowed
                                                (
                                                        VAR(NetworkHandleType,AUTOMATIC) Channel
   ,     VAR(boolean,AUTOMATIC) Allowed
                                                )
{

   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;

   channelRamPtr_ps = &ComM_ChannelStruct[Channel];

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_COMMUNICATION_ALLOWED,COMM_E_NOT_INITED);
        return;
   }

   if(Channel >= COMM_NO_OF_CHANNELS)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_COMMUNICATION_ALLOWED,COMM_E_WRONG_PARAMETERS);
        return;
   }
#endif

   channelRamPtr_ps->CommunicationAllowed_b = Allowed;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

