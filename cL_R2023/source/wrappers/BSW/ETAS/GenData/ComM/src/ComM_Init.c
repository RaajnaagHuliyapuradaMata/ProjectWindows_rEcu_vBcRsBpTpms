

#include "ComM_Priv.h"

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)
LOCAL_INLINE boolean ComM_Lok_GetNvMInhibitionStatus
                                                (
                                                 uint8 ChannelId_u8, const uint8 * NvM_InhibitionArray_pcu8
                                                );
#endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
LOCAL_INLINE uint32 ComM_Lok_CompareVersionInfo(const Std_VersionInfoType * srcVersionInfo,
                                            const Std_VersionInfoType * destVersionInfo);
#endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
const ComM_GlobalConfigType_tst * ComM_GlobalConfigPtr_pgcs;
#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Init(const Type_CfgSwcServiceComM_st * config)

{

    uint8                           ChannelIndex_u8;
    ComM_UserHandleType             UserIndex_tu8;
    ComM_ChannelVarType_tst *       channelRamPtr_pst;
    ComM_UserVarType_tst *          userRamPtr_pst;
    #if ((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
    uint8                           Index_u8;
    ComM_UserHandleArrayType *      fullComRequestorRamPtr_pst;
    #endif

    #if(COMM_NVM_ENABLED)
    NvM_RequestResultType           NvM_Status_tu8;
    Std_ReturnType                  Ret_NvM_Readval_u8;
    Std_ReturnType                  Ret_NvM_Error_Statusval_u8;
    #endif

    ComM_GlobalVarType_tst *        globalRamPtr_pst;
    const ComM_UsersType_tst *      userConfigPtr_pcst;
    #if(COMM_INHIBITION_ENABLED)
    const ComM_ChannelType_tst *    channelConfigPtr_pcst;
    #endif

    #if (COMM_PNC_ENABLED != STD_OFF)
    uint8                           PncIndex_u8;
    ComM_PncRamStructType_tst *     pncRamPtr_pst;
    #endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

    Std_VersionInfoType versionInfo;

    #if (COMM_DEV_ERROR_DETECT == STD_ON)

    if (config == NULL_PTR)
    {

        (void) Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_INIT_APIID,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif

    ComM_GetVersionInfo(&versionInfo);

    if (ComM_Lok_CompareVersionInfo(&versionInfo, config->versionInfo) != C_ZERO)
    {

        ComMAppl_IncompatibleGenerator();

        return;
    }

    ComM_GlobalConfigPtr_pgcs = (const ComM_GlobalConfigType_tst * )(config->ComM_GlobalConfigData_pcs);

#else

    (void)config;
#endif

    globalRamPtr_pst = &ComM_GlobalStruct;
    #if(COMM_NVM_ENABLED)
    NvM_Status_tu8 = C_ZERO;
    #endif

    #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

    globalRamPtr_pst->ComM_LimitECUToNoCom_b = FALSE;
    #endif

#if(COMM_INHIBITION_ENABLED)
    #if(COMM_NVM_ENABLED)

        Ret_NvM_Readval_u8 = NvM_ReadBlock(COMM_NVM_BLOCK_REFERENCE,&ComM_NvMblock);

        Ret_NvM_Error_Statusval_u8 = NvM_GetErrorStatus(COMM_NVM_BLOCK_REFERENCE,&NvM_Status_tu8);

        if((Ret_NvM_Readval_u8 == E_OK  ) && (Ret_NvM_Error_Statusval_u8 == E_OK))
        {

            ComM_GlobalStruct.ComM_EcuGroupClassification_u8 = ComM_NvMblock.ComMEcuGroupClassification_u8;
            ComM_GlobalStruct.ComM_InhibitCounter_u16 = ComM_NvMblock.Inhibitioncounter_u16;

            for (ChannelIndex_u8 = C_ZERO, channelRamPtr_pst = &ComM_ChannelStruct[C_ZERO]; ChannelIndex_u8 < COMM_NO_OF_CHANNELS ;++ChannelIndex_u8)
            {
                channelConfigPtr_pcst= &(COMM_GET_CHANNEL_LIST[ChannelIndex_u8]);
                if(channelConfigPtr_pcst->ComMNoWakeUpInhibitionNvmStorage_b == TRUE)
                {

                    channelRamPtr_pst->InhibitionReqStatus_u8 = ComM_Lok_GetNvMInhibitionStatus(ChannelIndex_u8, ComM_NvMblock.ComMNoWakeup_u8);
                }
                else
                {

                    channelRamPtr_pst->InhibitionReqStatus_u8 = channelConfigPtr_pcst->InhibitionInitValue_u8;
                }
                ++channelRamPtr_pst;
            }
        }
        else
    #endif
        {

            globalRamPtr_pst->ComM_EcuGroupClassification_u8 = ComM_EcuGroupClassification_Init;
            globalRamPtr_pst->ComM_InhibitCounter_u16 = C_ZERO;
            for (ChannelIndex_u8 = C_ZERO; ChannelIndex_u8 < COMM_NO_OF_CHANNELS ;++ChannelIndex_u8)
            {
                channelRamPtr_pst = &ComM_ChannelStruct[ChannelIndex_u8];
                channelConfigPtr_pcst= &(COMM_GET_CHANNEL_LIST[ChannelIndex_u8]);
                channelRamPtr_pst->InhibitionReqStatus_u8 = channelConfigPtr_pcst->InhibitionInitValue_u8;
            }
        }
#else
        for (ChannelIndex_u8 = C_ZERO ; ChannelIndex_u8 < COMM_NO_OF_CHANNELS ; ChannelIndex_u8++)
        {
            channelRamPtr_pst = &ComM_ChannelStruct[ChannelIndex_u8];
            channelRamPtr_pst->InhibitionReqStatus_u8 = C_ZERO;
        }
#endif

    for (UserIndex_tu8 = C_ZERO ; UserIndex_tu8 < COMM_NO_OF_USERS ; UserIndex_tu8++)
    {
        userRamPtr_pst = &ComM_UserStruct[UserIndex_tu8];
        userConfigPtr_pcst = &(COMM_GET_USER_LIST[UserIndex_tu8]);
        userRamPtr_pst->RequestedUserMode_u8 = COMM_NO_COMMUNICATION;
        userRamPtr_pst->numChannelsInFullCom_u8 = C_ZERO;
        userRamPtr_pst->numChannelsInSilentCom_u8 = C_ZERO;
        userRamPtr_pst->numChannelsInNoCom_u8 = userConfigPtr_pcst->NumAllChannels_u8;

        userRamPtr_pst->LimitToNoComCtr_u16 = C_ZERO;
        userRamPtr_pst->WakeUpInhibitionCtr_u16 = C_ZERO;

        userRamPtr_pst->IndicatedUserMode_u8 = COMM_NO_COMMUNICATION;
    }

    #if (COMM_PNC_ENABLED != STD_OFF)

    for (PncIndex_u8 = C_ZERO; PncIndex_u8 < COMM_NO_OF_PNCS ;PncIndex_u8++)
    {
        pncRamPtr_pst = &ComM_PncRamStruct[PncIndex_u8];
        #if (COMM_PNC_GW_ENABLED != STD_OFF)
        pncRamPtr_pst->ActiveERACnt_u8 = C_ZERO;
        pncRamPtr_pst->ERACnt_u8 = C_ZERO;
        pncRamPtr_pst->ActiveERAStateOld_b = FALSE;
        #endif
        pncRamPtr_pst->EIRACnt_u8 = C_ZERO;
        pncRamPtr_pst->PncState_en = COMM_PNC_NO_COMMUNICATION;
        pncRamPtr_pst->PrepareSleepTimer_u16 = C_ZERO;
        pncRamPtr_pst->UserRequestCnt_u8 = C_ZERO;
        pncRamPtr_pst->WakeUpStatus_b = FALSE;
        #if(COMM_INHIBITION_ENABLED)

        pncRamPtr_pst->LimitToNoComCtr_u16 = C_ZERO;
        pncRamPtr_pst->WakeUpInhibitionCtr_u16 = C_ZERO;
        #endif
    }
    #endif

    for (ChannelIndex_u8 = C_ZERO ; ChannelIndex_u8 < COMM_NO_OF_CHANNELS ; ChannelIndex_u8++)
    {
        channelRamPtr_pst = &ComM_ChannelStruct[ChannelIndex_u8];
        #if ((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
        fullComRequestorRamPtr_pst = &ComM_FullComRequestors[ChannelIndex_u8];
        #endif
        #if(COMM_INHIBITION_ENABLED)
        channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[ChannelIndex_u8]);
        #endif

        channelRamPtr_pst->CommunicationAllowed_b = FALSE;
        channelRamPtr_pst->ChannelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
        channelRamPtr_pst->ChannelMode_u8 = COMM_NO_COMMUNICATION;
        channelRamPtr_pst->BusSmMode_u8 = COMM_NO_COMMUNICATION;
        channelRamPtr_pst->PassiveRequestState_u8 = C_ZERO;
        channelRamPtr_pst->UserRequestCtr_u16 = C_ZERO_U16;
        channelRamPtr_pst->PncRequestCtr_u8 = C_ZERO;
        #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
        if(COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_pst->InhibitionReqStatus_u8)) != FALSE)
        {
            ComM_Lok_TranslateInhibitionStatus(ChannelIndex_u8,COMM_LIMITTONOCOM,TRUE);
        }
        #endif
        #if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)
        if(COMM_GET_PREVENT_WAKEUP((channelRamPtr_pst->InhibitionReqStatus_u8)) != FALSE)
        {
            ComM_Lok_TranslateInhibitionStatus(ChannelIndex_u8,COMM_PREVENTWAKEUP,TRUE);
        }
        #endif
        channelRamPtr_pst->NmBusSleepIndicationStatus_b = FALSE;
        channelRamPtr_pst->NmPrepareBusSleepIndicationStatus_b = FALSE;
        channelRamPtr_pst->DiagnosticRequestState_b = COMM_INACTIVE_DIAGNOSTICS;
        channelRamPtr_pst->NmNetworkModeStatus_b = FALSE;
        channelRamPtr_pst->NmNetworkRequestStatus_b = FALSE;
        channelRamPtr_pst->MinFullComTimeoutCtr_u16 = C_ZERO;
        #if ((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
        channelRamPtr_pst->ComMFullComReqNotify_b = FALSE;
        fullComRequestorRamPtr_pst->numberOfRequesters = C_ZERO;
        for(Index_u8 = 0;Index_u8 < COMM_MAX_CHANNEL_REQUESTERS;Index_u8++)
        {
           fullComRequestorRamPtr_pst->handleArray[Index_u8]=COMM_NOT_USED_USER_ID;
        }
        #endif
    }

    globalRamPtr_pst->ComM_InitStatus_en = COMM_INIT;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

LOCAL_INLINE uint32 ComM_Lok_CompareVersionInfo(const Std_VersionInfoType * srcVersionInfo,
                                            const Std_VersionInfoType * destVersionInfo)
{
    uint32 stEqual_u32;
    stEqual_u32 = 1;
    if ((srcVersionInfo->vendorID == destVersionInfo->vendorID) &&
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

#if(COMM_INHIBITION_ENABLED) && (COMM_NVM_ENABLED)
LOCAL_INLINE boolean ComM_Lok_GetNvMInhibitionStatus(uint8 ChannelId_u8, const uint8 * NvM_InhibitionArray_pcu8)

{

    uint8 byteIndex_u8, bitPosition_u8, Value_u8, mask_u8;
    boolean RetVal_b;

    byteIndex_u8 = (ChannelId_u8 ) >> 3;
    bitPosition_u8 = (ChannelId_u8) % 8;
    mask_u8 = (uint8)1 << (bitPosition_u8);

    Value_u8 = ((NvM_InhibitionArray_pcu8[byteIndex_u8]) & (mask_u8)) ;
    RetVal_b = (Value_u8 == 0) ? (FALSE) : (TRUE) ;

    return RetVal_b ;
}
#endif
