

#include "ComM_Priv.h"

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)
LOCAL_INLINE void ComM_Lok_UpdateNvMInhibitionStatus(uint8 ChannelId_u8, uint8 InhibitionStatus_u8,
                                                                                    uint8 * NvM_InhibitionArray_pu8);
#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_DeInit(void)
{

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    #endif
    uint8                           ChannelIndexCtr_u8;
    ComM_GlobalVarType_tst *        globalRamPtr_pst;

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)
    Std_ReturnType                  Ret_NvM_Writeval_tu8;
    uint8                           ChannelId_u8;
    ComM_ChannelVarType_tst *       channelRamPtr_pst;
#endif

    globalRamPtr_pst = &ComM_GlobalStruct;

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (
    globalRamPtr_pst->ComM_InitStatus_en != COMM_INIT)
    {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_DEINIT_APIID,COMM_E_NOT_INITED);
        return;
    }
    else
    {

    }
    #endif

    globalRamPtr_pst->ComM_InitStatus_en = COMM_UNINIT;
    for (ChannelIndexCtr_u8 = C_ZERO ; ChannelIndexCtr_u8 < COMM_NO_OF_CHANNELS ; ChannelIndexCtr_u8++)
    {

        if (ComM_ChannelStruct[ChannelIndexCtr_u8].ChannelState_e != COMM_NO_COM_NO_PENDING_REQUEST)
        {

            globalRamPtr_pst->ComM_InitStatus_en = COMM_INIT;
            break;
        }
    }

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)

        ComM_NvMblock.ComMEcuGroupClassification_u8 = ComM_GlobalStruct.ComM_EcuGroupClassification_u8;
        ComM_NvMblock.Inhibitioncounter_u16 = ComM_GlobalStruct.ComM_InhibitCounter_u16;

        for (ChannelId_u8 = C_ZERO; ChannelId_u8 < COMM_NO_OF_CHANNELS ;++ChannelId_u8)
        {

            channelRamPtr_pst = &ComM_ChannelStruct[ChannelId_u8];
            ComM_Lok_UpdateNvMInhibitionStatus(ChannelId_u8, COMM_GET_PREVENT_WAKEUP(channelRamPtr_pst->InhibitionReqStatus_u8), ComM_NvMblock.ComMNoWakeup_u8);
        }

        Ret_NvM_Writeval_tu8 = NvM_WriteBlock(COMM_NVM_BLOCK_REFERENCE,&ComM_NvMblock);

        #if (COMM_DEV_ERROR_DETECT != STD_OFF)
        if(Ret_NvM_Writeval_tu8 != E_OK)
        {
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NVM_REFERENCE_BLOCK,COMM_E_NVM_WRITE_FAILED);
            return;
        }
        #endif

#endif

        return;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)

LOCAL_INLINE void ComM_Lok_UpdateNvMInhibitionStatus(uint8 ChannelId_u8, uint8 InhibitionStatus_u8,
                                                                            uint8 * NvM_InhibitionArray_pu8)

{

    uint8 mask_u8;
    uint8 byteIndex_u8;
    uint8 bitPosition_u8;

    byteIndex_u8 = (ChannelId_u8) >> 3;
    bitPosition_u8 = (ChannelId_u8) % 8 ;

    if(InhibitionStatus_u8 == 0x01)
    {

         mask_u8 = ((uint8)1 << bitPosition_u8);
        *(NvM_InhibitionArray_pu8+byteIndex_u8) = (uint8)(*(NvM_InhibitionArray_pu8+byteIndex_u8) | (mask_u8)) ;
    }
    else
    {

         mask_u8 = (~ ((uint8)1 << bitPosition_u8));
        *(NvM_InhibitionArray_pu8+byteIndex_u8) = (uint8)(*(NvM_InhibitionArray_pu8+byteIndex_u8) & (mask_u8));
    }
}
#endif

