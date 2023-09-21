#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)
LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LUpdateNvMInhibitionStatus(uint8 ChannelId, uint8 InhibitionStatus, P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) NvM_InhibitionArray);
#endif

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(void,COMM_CODE) ComM_DeInit(void){

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
#endif
   VAR(uint8 ,AUTOMATIC)  ChannelIndexCtr;
   P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)
   VAR(Std_ReturnType, AUTOMATIC) Ret_NvM_Writeval_u8;
   VAR(uint8,AUTOMATIC) ChannelId;
   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
#endif

    globalRamPtr_ps = &ComM_GlobalStruct;

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(
    globalRamPtr_ps->ComM_InitStatus != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_DEINIT_APIID,COMM_E_NOT_INITED);
        return;
   }
   else{

   }
#endif

    globalRamPtr_ps->ComM_InitStatus = COMM_UNINIT;
   for(ChannelIndexCtr = C_ZERO ; ChannelIndexCtr < COMM_NO_OF_CHANNELS ; ChannelIndexCtr++)
   {

        if(ComM_ChannelStruct[ChannelIndexCtr].ChannelState_e != COMM_NO_COM_NO_PENDING_REQUEST)
        {

            globalRamPtr_ps->ComM_InitStatus = COMM_INIT;
            break;
        }
   }

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)

        ComM_NvMblock.ComMEcuGroupClassification_u8 = ComM_GlobalStruct.ComM_EcuGroupClassification_u8;
        ComM_NvMblock.Inhibitioncounter_u16 = ComM_GlobalStruct.ComM_InhibitCounter_u16;

        for(ChannelId = C_ZERO; ChannelId < COMM_NO_OF_CHANNELS ;++ChannelId)
        {

            channelRamPtr_ps = &ComM_ChannelStruct[ChannelId];
            ComM_LUpdateNvMInhibitionStatus(ChannelId, COMM_GET_PREVENT_WAKEUP(channelRamPtr_ps->InhibitionReqStatus_u8), ComM_NvMblock.ComMNoWakeup_u8);
        }

        Ret_NvM_Writeval_u8 = NvM_WriteBlock(COMM_NVM_BLOCK_REFERENCE,&ComM_NvMblock);

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
        if(Ret_NvM_Writeval_u8 != E_OK)
        {
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NVM_REFERENCE_BLOCK,COMM_E_NVM_WRITE_FAILED);
            return;
        }
#endif

#endif

        return;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LUpdateNvMInhibitionStatus
                                    (
                                      uint8 ChannelId, uint8 InhibitionStatus, P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) NvM_InhibitionArray
                                    )

{

   uint8 mask;
   uint8 byteIndex;
   uint8 bitPosition;

   byteIndex = (ChannelId) >> 3;
   bitPosition = (ChannelId) % 8 ;

   if(InhibitionStatus == 0x01)
   {

         mask = ((uint8)1 << bitPosition);
        *(NvM_InhibitionArray+byteIndex) = (uint8)(*(NvM_InhibitionArray+byteIndex) | (mask)) ;
   }
   else{

         mask = (~ ((uint8)1 << bitPosition));
        *(NvM_InhibitionArray+byteIndex) = (uint8)(*(NvM_InhibitionArray+byteIndex) & (mask));
   }
}
#endif

