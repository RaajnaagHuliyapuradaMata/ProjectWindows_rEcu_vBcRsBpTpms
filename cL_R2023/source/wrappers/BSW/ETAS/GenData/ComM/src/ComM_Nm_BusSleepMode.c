

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Nm_BusSleepMode(NetworkHandleType Channel)
{

    ComM_ChannelVarType_tst *       channelRamPtr_pst;
    const ComM_ChannelType_tst *    channelConfigPtr_pcst;

    channelRamPtr_pst = &ComM_ChannelStruct[Channel];
    channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[Channel]);

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_BUS_SLEEPMODE,COMM_E_NOT_INITED);
        return;
    }

    if (Channel >= COMM_NO_OF_CHANNELS)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_BUS_SLEEPMODE,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif

    if ((channelConfigPtr_pcst->ComMNmVariant_en==FULL)||(channelConfigPtr_pcst->ComMNmVariant_en==PASSIVE))
    {
        SchM_Enter_ComM_ChannelNoNest();

        if((channelRamPtr_pst->ChannelMode_u8 == COMM_FULL_COMMUNICATION)|| (channelRamPtr_pst->ChannelMode_u8 == COMM_SILENT_COMMUNICATION))
        {
            channelRamPtr_pst -> NmBusSleepIndicationStatus_b = TRUE;
        }

        SchM_Exit_ComM_ChannelNoNest();
    }
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

