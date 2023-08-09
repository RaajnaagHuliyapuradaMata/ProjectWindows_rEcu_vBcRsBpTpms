

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(void,COMM_CODE) ComM_Nm_PrepareBusSleepMode
                                            (
                                            VAR(NetworkHandleType,AUTOMATIC) Channel
                                            )
{

    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    channelRamPtr_ps = &ComM_ChannelStruct[Channel];
    channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_PREPARE_BUSSLEEPMODE,COMM_E_NOT_INITED);
        return;
    }

    if (Channel >= COMM_NO_OF_CHANNELS)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_PREPARE_BUSSLEEPMODE,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif

    if ((channelConfigPtr_pcs->ComMNmVariant_e==PASSIVE)||(channelConfigPtr_pcs->ComMNmVariant_e==FULL))
    {
        SchM_Enter_ComM_ChannelNoNest();

        if(channelRamPtr_ps->ChannelState_e == COMM_FULL_COM_READY_SLEEP)
        {
            channelRamPtr_ps -> NmPrepareBusSleepIndicationStatus_b = TRUE;
        }

        SchM_Exit_ComM_ChannelNoNest();
    }

}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

