

#include "ComM_Priv.h"

#if (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

Std_ReturnType ComM_LimitECUToNoComMode(boolean Status)
{

    uint8                       channelId_u8;
    Std_ReturnType              retVal_u8;
    ComM_ChannelVarType_tst *   channelRamPtr_pst;
    ComM_GlobalVarType_tst *    globalRamPtr_pst;

    retVal_u8 = E_OK;

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID, COMM_INSTANCE_ID, COMM_LIMIT_CHNLTO_NOCOMMODE_APIID, COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
    }
    #endif

    globalRamPtr_pst = &ComM_GlobalStruct;

    if((globalRamPtr_pst->ComM_LimitECUToNoCom_b) != Status)
    {

        globalRamPtr_pst->ComM_LimitECUToNoCom_b = Status;

        if(Status != FALSE)
        {

            for(channelId_u8 = C_ZERO, channelRamPtr_pst = &ComM_ChannelStruct[C_ZERO]; channelId_u8 < COMM_NO_OF_CHANNELS; ++channelId_u8)
            {

                ComM_Lok_ProcessLimitToNoCom (channelId_u8, TRUE);
                ++channelRamPtr_pst;
            }

             if((COMM_GET_LIMIT_TO_NO_COM(globalRamPtr_pst->ComM_EcuGroupClassification_u8) == FALSE))
            {
                retVal_u8 = E_NOT_OK;
            }
        }

        else
        {

            for(channelId_u8 = C_ZERO, channelRamPtr_pst = &ComM_ChannelStruct[channelId_u8]; channelId_u8 < COMM_NO_OF_CHANNELS; channelId_u8++)
            {

                ComM_Lok_ProcessLimitToNoCom (channelId_u8, FALSE);
                channelRamPtr_pst++;
            }
        }
    }

    return retVal_u8;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

