

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_CommunicationAllowed(NetworkHandleType Channel, boolean Allowed)
{

    ComM_ChannelVarType_tst *  channelRamPtr_pst;

    channelRamPtr_pst = &ComM_ChannelStruct[Channel];

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    if (ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_COMMUNICATION_ALLOWED,COMM_E_NOT_INITED);
        return;
    }

    if (Channel >= COMM_NO_OF_CHANNELS)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_COMMUNICATION_ALLOWED,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif

    channelRamPtr_pst->CommunicationAllowed_b = Allowed;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

