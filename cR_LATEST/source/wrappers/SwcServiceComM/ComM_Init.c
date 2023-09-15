#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)
LOCAL_INLINE FUNC(boolean, COMM_CODE) ComM_LGetNvMInhibitionStatus
                                    (
                                      uint8 ChannelId,  P2CONST(uint8, AUTOMATIC,COMM_APPL_DATA) NvM_InhibitionArray
                                    );
#endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
LOCAL_INLINE uint32 ComM_CompareVersionInfo(P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST) srcVersionInfo
   ,     P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST) destVersionInfo);
#endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
P2CONST(ComM_GlobalConfigType,AUTOMATIC,COMM_APPL_CONST) ComM_GlobalConfigPtr_pgcs;
#endif

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(void,COMM_CODE) ComM_Init
                            (
                             P2CONST(Type_CfgSwcServiceComM_st,AUTOMATIC,COMM_APPL_CONST) config
                            )

{

   VAR(uint8,AUTOMATIC) ChannelIndex;
   VAR(ComM_UserHandleType,AUTOMATIC) UserIndex;
   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
   P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;
#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
   VAR(uint8, AUTOMATIC) Index_u8;
   P2VAR(ComM_UserHandleArrayType, AUTOMATIC, COMM_APPL_DATA) fullComRequestorRamPtr_ps;
#endif

#if(COMM_NVM_ENABLED)
   VAR(NvM_RequestResultType,AUTOMATIC) NvM_Status;
   VAR(Std_ReturnType, AUTOMATIC) Ret_NvM_Readval_u8;
   VAR(Std_ReturnType, AUTOMATIC) Ret_NvM_Error_Statusval_u8;
#endif

   P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
   P2CONST(ComM_UsersType,AUTOMATIC,COMM_APPL_CONST) userConfigPtr_pcs;
#if(COMM_INHIBITION_ENABLED)
   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;
#endif

#if(COMM_PNC_ENABLED != STD_OFF)
   VAR(uint8,AUTOMATIC) PncIndex;
   P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
#endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
    Std_VersionInfoType versionInfo;

#if(COMM_DEV_ERROR_DETECT == STD_ON)
   if(config == NULL_PTR){
        (void) Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_INIT_APIID,COMM_E_WRONG_PARAMETERS);
        return;
   }
#endif

   ComM_GetVersionInfo(&versionInfo);
   if(ComM_CompareVersionInfo(&versionInfo, config->versionInfo) != C_ZERO){
        return;
   }
   ComM_GlobalConfigPtr_pgcs = (P2CONST(ComM_GlobalConfigType,AUTOMATIC,COMM_APPL_CONST))(config->ComM_GlobalConfigData_pcs);
#else
    (void)config;
#endif

    globalRamPtr_ps = &ComM_GlobalStruct;
   #if(COMM_NVM_ENABLED)
    NvM_Status = C_ZERO;
   #endif

#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

    globalRamPtr_ps->ComM_LimitECUToNoCom_b = FALSE;
#endif

#if(COMM_INHIBITION_ENABLED)
#if(COMM_NVM_ENABLED)

        Ret_NvM_Readval_u8 = NvM_ReadBlock(COMM_NVM_BLOCK_REFERENCE,&ComM_NvMblock);

        Ret_NvM_Error_Statusval_u8 = NvM_GetErrorStatus(COMM_NVM_BLOCK_REFERENCE,&NvM_Status);

        if((Ret_NvM_Readval_u8 == E_OK  ) && (Ret_NvM_Error_Statusval_u8 == E_OK))
        {

            ComM_GlobalStruct.ComM_EcuGroupClassification_u8 = ComM_NvMblock.ComMEcuGroupClassification_u8;
            ComM_GlobalStruct.ComM_InhibitCounter_u16 = ComM_NvMblock.Inhibitioncounter_u16;

            for(ChannelIndex = C_ZERO, channelRamPtr_ps = &ComM_ChannelStruct[C_ZERO]; ChannelIndex < COMM_NO_OF_CHANNELS ;++ChannelIndex)
            {
                channelConfigPtr_pcs= &(COMM_GET_CHANNEL_LIST[ChannelIndex]);
                if(channelConfigPtr_pcs->ComMNoWakeUpInhibitionNvmStorage_b == TRUE)
                {

                    channelRamPtr_ps->InhibitionReqStatus_u8 = ComM_LGetNvMInhibitionStatus(ChannelIndex, ComM_NvMblock.ComMNoWakeup_u8);
                }
                else{

                    channelRamPtr_ps->InhibitionReqStatus_u8 = channelConfigPtr_pcs->InhibitionInitValue_u8;
                }
                ++channelRamPtr_ps;
            }
        }
        else
#endif
        {

            globalRamPtr_ps->ComM_EcuGroupClassification_u8 = ComM_EcuGroupClassification_Init;
            globalRamPtr_ps->ComM_InhibitCounter_u16 = C_ZERO;
            for(ChannelIndex = C_ZERO; ChannelIndex < COMM_NO_OF_CHANNELS ;++ChannelIndex)
            {
                channelRamPtr_ps = &ComM_ChannelStruct[ChannelIndex];
                channelConfigPtr_pcs= &(COMM_GET_CHANNEL_LIST[ChannelIndex]);
                channelRamPtr_ps->InhibitionReqStatus_u8 = channelConfigPtr_pcs->InhibitionInitValue_u8;
            }
        }
#else
        for(ChannelIndex = C_ZERO ; ChannelIndex < COMM_NO_OF_CHANNELS ; ChannelIndex++)
        {
            channelRamPtr_ps = &ComM_ChannelStruct[ChannelIndex];
            channelRamPtr_ps->InhibitionReqStatus_u8 = C_ZERO;
        }
#endif

   for(UserIndex = C_ZERO ; UserIndex < COMM_NO_OF_USERS ; UserIndex++)
   {
        userRamPtr_ps = &ComM_UserStruct[UserIndex];
        userConfigPtr_pcs = &(COMM_GET_USER_LIST[UserIndex]);
        userRamPtr_ps->RequestedUserMode_t = COMM_NO_COMMUNICATION;
        userRamPtr_ps->numChannelsInFullCom_u8 = C_ZERO;
        userRamPtr_ps->numChannelsInSilentCom_u8 = C_ZERO;
        userRamPtr_ps->numChannelsInNoCom_u8 = userConfigPtr_pcs->NumAllChannels_u8;

        userRamPtr_ps->LimitToNoComCtr_u16 = C_ZERO;
        userRamPtr_ps->WakeUpInhibitionCtr_u16 = C_ZERO;

        userRamPtr_ps->IndicatedUserMode_t = COMM_NO_COMMUNICATION;
   }

#if(COMM_PNC_ENABLED != STD_OFF)

   for(PncIndex = C_ZERO; PncIndex < COMM_NO_OF_PNCS ;PncIndex++)
   {
        pncRamPtr_ps = &ComM_PncRamStruct[PncIndex];
#if(COMM_PNC_GW_ENABLED != STD_OFF)
        pncRamPtr_ps->ActiveERACnt_u8 = C_ZERO;
        pncRamPtr_ps->ERACnt_u8 = C_ZERO;
        pncRamPtr_ps->ActiveERAStateOld_b = FALSE;
#endif
        pncRamPtr_ps->EIRACnt_u8 = C_ZERO;
        pncRamPtr_ps->PncState_e = COMM_PNC_NO_COMMUNICATION;
        pncRamPtr_ps->PrepareSleepTimer_u16 = C_ZERO;
        pncRamPtr_ps->UserRequestCnt_u8 = C_ZERO;
        pncRamPtr_ps->WakeUpStatus_b = FALSE;
#if(COMM_INHIBITION_ENABLED)

        pncRamPtr_ps->LimitToNoComCtr_u16 = C_ZERO;
        pncRamPtr_ps->WakeUpInhibitionCtr_u16 = C_ZERO;
#endif
   }
#endif

   for(ChannelIndex = C_ZERO ; ChannelIndex < COMM_NO_OF_CHANNELS ; ChannelIndex++)
   {
        channelRamPtr_ps = &ComM_ChannelStruct[ChannelIndex];
#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
        fullComRequestorRamPtr_ps = &ComM_FullComRequestors[ChannelIndex];
#endif
#if(COMM_INHIBITION_ENABLED)
        channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[ChannelIndex]);
#endif

        channelRamPtr_ps->CommunicationAllowed_b = FALSE;
        channelRamPtr_ps->ChannelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
        channelRamPtr_ps->ChannelMode_u8 = COMM_NO_COMMUNICATION;
        channelRamPtr_ps->BusSmMode_u8 = COMM_NO_COMMUNICATION;
        channelRamPtr_ps->PassiveRequestState_u8 = C_ZERO;
        channelRamPtr_ps->UserRequestCtr_u8 = C_ZERO;
        channelRamPtr_ps->PncRequestCtr_u8 = C_ZERO;
#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
        if(COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8)) != FALSE)
        {
            ComM_LTranslateInhibitionStatus(ChannelIndex,COMM_LIMITTONOCOM,TRUE);
        }
#endif
#if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)
        if(COMM_GET_PREVENT_WAKEUP((channelRamPtr_ps->InhibitionReqStatus_u8)) != FALSE)
        {
            ComM_LTranslateInhibitionStatus(ChannelIndex,COMM_PREVENTWAKEUP,TRUE);
        }
#endif
        channelRamPtr_ps->NmBusSleepIndicationStatus_b = FALSE;
        channelRamPtr_ps->NmPrepareBusSleepIndicationStatus_b = FALSE;
        channelRamPtr_ps->DiagnosticRequestState_b = COMM_INACTIVE_DIAGNOSTICS;
        channelRamPtr_ps->NmNetworkModeStatus_b = FALSE;
        channelRamPtr_ps->NmNetworkRequestStatus_b = FALSE;
        channelRamPtr_ps->MinFullComTimeoutCtr_u16 = C_ZERO;
#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
        channelRamPtr_ps->ComMFullComReqNotify_b = FALSE;
        fullComRequestorRamPtr_ps->numberOfRequesters = C_ZERO;
        for(Index_u8 = 0;Index_u8 < COMM_MAX_CHANNEL_REQUESTERS;Index_u8++)
        {
           fullComRequestorRamPtr_ps->handleArray[Index_u8]=COMM_NOT_USED_USER_ID;
        }
#endif
   }

    globalRamPtr_ps->ComM_InitStatus = COMM_INIT;
}

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

LOCAL_INLINE uint32 ComM_CompareVersionInfo(P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST) srcVersionInfo
   ,     P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST) destVersionInfo)
{
   uint32 stEqual_u32;
   stEqual_u32 = 1;
   if((srcVersionInfo->vendorID == destVersionInfo->vendorID) &&
        (srcVersionInfo->moduleID == destVersionInfo->moduleID) &&
        (srcVersionInfo->sw_major_version == destVersionInfo->sw_major_version) &&
        (srcVersionInfo->sw_minor_version == destVersionInfo->sw_minor_version) &&
        (srcVersionInfo->sw_patch_version == destVersionInfo->sw_patch_version)
    )
   {
        stEqual_u32 = 0;
   }
    return stEqual_u32;
}

#endif

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)
LOCAL_INLINE FUNC(boolean, COMM_CODE) ComM_LGetNvMInhibitionStatus
                                    (
                                      uint8 ChannelId,  P2CONST(uint8, AUTOMATIC,COMM_APPL_DATA) NvM_InhibitionArray
                                    )

{

   uint8 byteIndex_u8, bitPosition_u8, Value_u8, mask;
   boolean Ret_Val;

   byteIndex_u8 = (ChannelId ) >> 3;
   bitPosition_u8 = (ChannelId) % 8;
    mask = (uint8)1 << (bitPosition_u8);

   Value_u8 = ((NvM_InhibitionArray[byteIndex_u8]) & (mask)) ;
    Ret_Val = (Value_u8 == 0) ? (FALSE) : (TRUE) ;

    return Ret_Val ;
}
#endif
