

#include "ComM_Priv.h"

#if (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode
                                (
                                    VAR(boolean, COMM_VAR) Status
                                )
{

    uint8 channelId_u8;
    VAR(Std_ReturnType, AUTOMATIC) ret_val;
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;

    ret_val = E_OK;

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_LIMIT_CHNLTO_NOCOMMODE_APIID, COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }
    #endif

    globalRamPtr_ps = &ComM_GlobalStruct;

    if((globalRamPtr_ps->ComM_LimitECUToNoCom_b) != Status)
    {

        globalRamPtr_ps->ComM_LimitECUToNoCom_b = Status;

        if(Status != FALSE)
        {

            for(channelId_u8 = C_ZERO, channelRamPtr_ps = &ComM_ChannelStruct[C_ZERO]; channelId_u8 < COMM_NO_OF_CHANNELS; ++channelId_u8)
            {

                ret_val |= ComM_LProcessLimitToNoCom (channelId_u8, TRUE);
                ++channelRamPtr_ps;
            }
        }

        else
        {

            for(channelId_u8 = C_ZERO, channelRamPtr_ps = &ComM_ChannelStruct[channelId_u8]; channelId_u8 < COMM_NO_OF_CHANNELS; channelId_u8++)
            {

                (void)ComM_LProcessLimitToNoCom (channelId_u8, FALSE);
                channelRamPtr_ps++;
            }
        }
    }

    return ret_val;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif

