

#include "ComM_Priv.h"

#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_MemMap.h"

ComM_GlobalVarType_tst          ComM_GlobalStruct;
ComM_UserVarType_tst            ComM_UserStruct[COMM_NO_OF_USERS];
ComM_ChannelVarType_tst         ComM_ChannelStruct[COMM_NO_OF_CHANNELS];
ComM_NvMStorageType_tst         ComM_NvMblock;

#if (COMM_PNC_ENABLED != STD_OFF)

ComM_PncRamStructType_tst   ComM_PncRamStruct[COMM_NO_OF_PNCS];
boolean                     ComM_EIRA_RxSigVal[COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA][COMM_NO_OF_PNCS];

#if (COMM_PNC_GW_ENABLED != STD_OFF)
boolean                 ComM_ERA_RxSigVal[COMM_NO_OF_CH_WITH_ERA][COMM_NO_OF_PNCS];
#endif

#endif

#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_MemMap.h"

#if (COMM_PNC_ENABLED != STD_OFF)
LOCAL_INLINE boolean ComM_Lok_Getbit(uint8 PncId_u8, const uint8 Signal_Array_cu8[8]);
#endif

#if(COMM_INHIBITION_ENABLED)
LOCAL_INLINE void ComM_Lok_TranslateInhibitionToUser(const uint8 *             Users_pcu8,
                                                      uint8                     numUsers_u8,
                                                      ComM_InhibitionType_ten   InhibitionType_en,
                                                      boolean               Status_b);
LOCAL_INLINE void ComM_Lok_UpdateInhibitionCounter(uint16 *                InhibitionCounter_pu16,
                                                    boolean                 Status_b,
                                                    uint16                  InhibitionCounterMax_u16);
#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

boolean ComM_Lok_ValidateUserId (ComM_UserHandleType UserId_tu8)
{
    if((UserId_tu8 < COMM_USERID_MIN) || (UserId_tu8 > COMM_USERID_MAX))
    {
        return FALSE;
    }
    else
    {
        return (ComM_UserId_MappingTable_acst[UserId_tu8] == COMM_USER_INVALID_ID ) ? (FALSE) : (TRUE) ;
    }
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#if (COMM_PNC_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Lok_PncToChannelInterface(PNCHandleType      PncIndex_tu8,
                                     ComM_PncModeType   PncState_en,
                                     ComM_PncModeType   PncPreviousState_en,
                                     boolean            ActiveERAState_b)

{

    uint8   loopCtr_u8;
    uint8   ChannelId_u8;
    uint8   numChannels_u8;

    ComM_ChannelVarType_tst *           channelRamPtr_pst;
    const ComM_PncConfigStruct_tst *    pncConfigPtr_pcst;
    const ComM_ChannelType_tst *        channelConfigPtr_pcst;

    pncConfigPtr_pcst = &(COMM_GET_PNC_LIST[PncIndex_tu8]);
    numChannels_u8 = pncConfigPtr_pcst->NumChannels_u8;

    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {

    SchM_Enter_ComM_PNCNoNest();

    for(loopCtr_u8 = 0; loopCtr_u8 < numChannels_u8 ;loopCtr_u8++)
    {
        ChannelId_u8 = (pncConfigPtr_pcst->Channels_pcu8[loopCtr_u8]);

        channelRamPtr_pst = &ComM_ChannelStruct[ChannelId_u8];

        channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[ChannelId_u8]);

        if (PncState_en == COMM_PNC_REQUESTED)
        {
            #if ((COMM_PNC_GW_ENABLED != STD_OFF) && (COMM_ZERO_PNC_VECTOR_AVOIDANCE != STD_OFF))
            if((channelConfigPtr_pcst->PncGwType_en == COMM_GATEWAY_TYPE_PASSIVE) &&
               ((channelConfigPtr_pcst->TxSigId_u16)!= COMM_COMSIGNAL_INVALID_ID) && (ActiveERAState_b == FALSE))
            {

            }
            else
            #endif
            {
                ++(channelRamPtr_pst->PncRequestCtr_u8);

                if(channelConfigPtr_pcst->PncNmRequest_b != FALSE)
                {

                    channelRamPtr_pst->NmNetworkRequestStatus_b = TRUE;
                }
            }
        }

        else if((PncState_en == COMM_PNC_READY_SLEEP) && (PncPreviousState_en == COMM_PNC_REQUESTED))
        {
            #if ((COMM_PNC_GW_ENABLED != STD_OFF) && (COMM_ZERO_PNC_VECTOR_AVOIDANCE != STD_OFF))
            if((channelConfigPtr_pcst->PncGwType_en == COMM_GATEWAY_TYPE_PASSIVE) &&
                ((channelConfigPtr_pcst->TxSigId_u16)!= COMM_COMSIGNAL_INVALID_ID) && (ActiveERAState_b == FALSE))
            {

            }
            else
            #endif
            {
                if(channelRamPtr_pst->PncRequestCtr_u8 != C_ZERO)
                {
                    --(channelRamPtr_pst->PncRequestCtr_u8);
                }
                else
                {

                    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
                    (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_PNC_MAINFNC_APIID,COMM_E_CNTR_UNDERFLW);
                    #endif
                }
            }
        }
        else
        {

        }
    }
    SchM_Exit_ComM_PNCNoNest();
    }
    #if !((COMM_PNC_GW_ENABLED != STD_OFF) && (COMM_ZERO_PNC_VECTOR_AVOIDANCE != STD_OFF))
    (void)ActiveERAState_b;
    #endif
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

#if (COMM_PNC_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Lok_EIRA_CallBack(uint8 PnBusId_u8)
{

    uint8                               PncIndex_u8;
    uint8                               SigValue_u8[8];
    uint16                              ComSigId_u16;
    ComM_PncRamStructType_tst *         pncRamPtr_pst;
    const ComM_PncConfigStruct_tst *    pncConfigPtr_pcst;
    boolean                             EIRA_PncSigValue_b;

    SchM_Enter_ComM_EIRANoNest();

    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {

        ComSigId_u16 = COMM_GET_EIRASIG_TABLE[PnBusId_u8];

        if(ComSigId_u16 != COMM_COMSIGNAL_INVALID_ID)
        {

            (void)Com_ReceiveSignal(ComSigId_u16,&SigValue_u8);

            for(PncIndex_u8=0, pncRamPtr_pst = &ComM_PncRamStruct[0], pncConfigPtr_pcst = &(COMM_GET_PNC_LIST[0]); PncIndex_u8 < COMM_NO_OF_PNCS; PncIndex_u8++)
            {
                EIRA_PncSigValue_b = ComM_Lok_Getbit(pncConfigPtr_pcst->PncId_u8,SigValue_u8);

                if(ComM_EIRA_RxSigVal[PnBusId_u8][PncIndex_u8]!= EIRA_PncSigValue_b)
                {
                    ComM_EIRA_RxSigVal[PnBusId_u8][PncIndex_u8] = EIRA_PncSigValue_b;

                    if(EIRA_PncSigValue_b != FALSE)
                    {
                        ++pncRamPtr_pst->EIRACnt_u8;
                    }
                    else
                    {
                        --pncRamPtr_pst->EIRACnt_u8;
                    }
                }
                pncRamPtr_pst++;
                pncConfigPtr_pcst++;
            }
        }
    }
    SchM_Exit_ComM_EIRANoNest();
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

#if (COMM_PNC_ENABLED != STD_OFF)

#if (COMM_PNC_GW_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Lok_ERA_CallBack(uint8 PnBusId_u8, ComM_PncGatewayType_ten channelGwType_en)
{

    uint8                               PncIndex_u8;
    boolean                             ERA_PncSigValue_b;
    uint16                              ComSigId_u16;
    uint8                               SigValue_u8[8];
    ComM_PncRamStructType_tst *         pncRamPtr_pst;
    const ComM_PncConfigStruct_tst *    pncConfigPtr_pcst;

    SchM_Enter_ComM_ERANoNest();

    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {

        ComSigId_u16 = COMM_GET_ERASIG_TABLE[PnBusId_u8];

        if(ComSigId_u16 != COMM_COMSIGNAL_INVALID_ID)
        {

            (void)Com_ReceiveSignal(ComSigId_u16,&SigValue_u8);

            for(PncIndex_u8=0, pncRamPtr_pst = &ComM_PncRamStruct[0], pncConfigPtr_pcst = &(COMM_GET_PNC_LIST[0]); PncIndex_u8 < COMM_NO_OF_PNCS; PncIndex_u8++)
            {
                ERA_PncSigValue_b = ComM_Lok_Getbit(pncConfigPtr_pcst->PncId_u8 , SigValue_u8);

                if(ComM_ERA_RxSigVal[PnBusId_u8][PncIndex_u8] != ERA_PncSigValue_b)
                {
                    ComM_ERA_RxSigVal[PnBusId_u8][PncIndex_u8] = ERA_PncSigValue_b;
                    if(ERA_PncSigValue_b != FALSE)
                    {

                        if (channelGwType_en == COMM_GATEWAY_TYPE_ACTIVE)
                        {
                            ++pncRamPtr_pst->ActiveERACnt_u8;
                        }
                        ++(pncRamPtr_pst->ERACnt_u8);
                    }
                    else
                    {

                        if (channelGwType_en == COMM_GATEWAY_TYPE_ACTIVE)
                        {
                            --pncRamPtr_pst->ActiveERACnt_u8;
                        }
                        --(pncRamPtr_pst->ERACnt_u8);
                    }
                }
                pncRamPtr_pst++;
                pncConfigPtr_pcst++;
            }
        }
    }

    SchM_Exit_ComM_ERANoNest();
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif
#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

ComM_ModeType ComM_Lok_getLeastBusSmMode(ComM_UserHandleType UserIndex_tu8)

{

    ComM_ModeType           leastModeAmongChannels_tu8;
    ComM_UserVarType_tst *  userRamPtr_pst;

    userRamPtr_pst = &ComM_UserStruct[ComM_UserId_MappingTable_acst[UserIndex_tu8]];

    if(userRamPtr_pst->numChannelsInNoCom_u8 != C_ZERO)
    {
        leastModeAmongChannels_tu8 = COMM_NO_COMMUNICATION;
    }
    else if(userRamPtr_pst->numChannelsInSilentCom_u8 != C_ZERO)
    {
            leastModeAmongChannels_tu8 = COMM_SILENT_COMMUNICATION;
    }
    else
    {
        leastModeAmongChannels_tu8 = COMM_FULL_COMMUNICATION;
    }
    return leastModeAmongChannels_tu8;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#if(COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"
void ComM_Lok_TranslateInhibitionStatus(NetworkHandleType          Channel_tu8,
                                         ComM_InhibitionType_ten    InhibitionType_en,
                                         boolean                    Status_b)
{

    const ComM_ChannelType_tst * channelConfigPtr_pcst;

    #if (COMM_PNC_ENABLED != STD_OFF)
    uint8 numPnc_u8;
    const uint8 * pncs_pcu8;
    #endif

    channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[Channel_tu8]);

    #if (COMM_PNC_ENABLED != STD_OFF)
    pncs_pcu8 = channelConfigPtr_pcst->Pncs_pcu8;
    #endif

    ComM_Lok_TranslateInhibitionToUser(channelConfigPtr_pcst->DirectUsers_pcu8,channelConfigPtr_pcst->numDirectUsers_u8, InhibitionType_en,Status_b);

    #if(COMM_PNC_ENABLED != STD_OFF)

    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {
        for(numPnc_u8 = C_ZERO; numPnc_u8 < channelConfigPtr_pcst->numPncs_u8; ++numPnc_u8)
        {
            uint8 pncId_u8;
            ComM_PncRamStructType_tst *         pncRamPtr_ps;
            const ComM_PncConfigStruct_tst *    pncConfigPtr_pcs;

            pncId_u8 = pncs_pcu8[numPnc_u8];
            pncRamPtr_ps = &ComM_PncRamStruct[pncId_u8];
            pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[pncId_u8]);

            if(InhibitionType_en == COMM_PREVENTWAKEUP)
            {
                ComM_Lok_UpdateInhibitionCounter(&(pncRamPtr_ps->WakeUpInhibitionCtr_u16),Status_b,pncConfigPtr_pcs->NumChannels_u8);
            }
            else
            {
                ComM_Lok_UpdateInhibitionCounter(&(pncRamPtr_ps->LimitToNoComCtr_u16),Status_b,pncConfigPtr_pcs->NumChannels_u8);
            }

            ComM_Lok_TranslateInhibitionToUser(pncConfigPtr_pcs->Users_pcu8,pncConfigPtr_pcs->NumUsers_u8,InhibitionType_en,Status_b);

        }
    }
    #endif
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

#if(COMM_INHIBITION_ENABLED)

LOCAL_INLINE void ComM_Lok_TranslateInhibitionToUser(const uint8 *             Users_pcu8,
                                                      uint8                     numUsers_u8,
                                                      ComM_InhibitionType_ten   InhibitionType_en,
                                                      boolean                   Status_b)
{
    uint8                       loopCounter_u8;
    uint8                       userId_u8;
    ComM_UserVarType_tst *      userRamPtr_ps;
    const ComM_UsersType_tst *  userConfigPtr_pcs;

    for(loopCounter_u8 = C_ZERO; loopCounter_u8 < numUsers_u8; ++loopCounter_u8)
    {
        userId_u8 = Users_pcu8[loopCounter_u8];
        userConfigPtr_pcs = &(COMM_GET_USER_LIST[ComM_UserId_MappingTable_acst[userId_u8]]);
        userRamPtr_ps = &ComM_UserStruct[ComM_UserId_MappingTable_acst[userId_u8]];

        if(InhibitionType_en == COMM_PREVENTWAKEUP)
        {
            ComM_Lok_UpdateInhibitionCounter(&(userRamPtr_ps->WakeUpInhibitionCtr_u16),Status_b,userConfigPtr_pcs->NumAllChannels_u8);
        }
        else
        {
            ComM_Lok_UpdateInhibitionCounter(&(userRamPtr_ps->LimitToNoComCtr_u16),Status_b,userConfigPtr_pcs->NumAllChannels_u8);
        }
    }
}
#endif

#if(COMM_INHIBITION_ENABLED)

LOCAL_INLINE void ComM_Lok_UpdateInhibitionCounter(uint16 *  InhibitionCounter_pu16,
                                                   boolean   Status_b,
                                                   uint16    InhibitionCounterMax_u16)
{
    if(Status_b != FALSE)
    {
        if((*InhibitionCounter_pu16) == InhibitionCounterMax_u16 )
        {

            #if (COMM_DEV_ERROR_DETECT != STD_OFF)
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_INHIBITION_COUNTER,COMM_E_IHHIBITION_CNTR_OVERFLW);
            return;
            #endif
        }
        else
        {
            ++(*InhibitionCounter_pu16);
        }
    }
    else
    {
        if((*InhibitionCounter_pu16) == C_ZERO_U16 )
        {

            #if (COMM_DEV_ERROR_DETECT != STD_OFF)
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_INHIBITION_COUNTER,COMM_E_IHHIBITION_CNTR_UNDERFLW);
            return;
            #endif
        }
        else
        {
            --(*InhibitionCounter_pu16);
        }
    }
}
#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Lok_UpdateChannelModes(NetworkHandleType  Channel_tu8,
                                  ComM_ModeType      PreviousMode_tu8,
                                  ComM_ModeType      CurrentMode_tu8)
{

    uint8                       numUsers_u8;
    uint8                       userId_u8;
    const ComM_ChannelType_tst *    channelConfigPtr_pcst;

    ComM_UserVarType_tst *      userRamPtr_pst;
    const uint8 *               allUsers_pcu8;
    uint8                       userId_internal_u8;

    #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
    const ComM_UsersType_tst *  userConfigPtr_pcst;
    #endif

    channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[Channel_tu8]);
    allUsers_pcu8 = channelConfigPtr_pcst->AllUsers_pcu8;

    if(PreviousMode_tu8 != CurrentMode_tu8)
    {
        for(numUsers_u8= C_ZERO; numUsers_u8 < channelConfigPtr_pcst->numAllUsers_u8; ++numUsers_u8)
        {
            SchM_Enter_ComM_Channel();
            userId_u8 = allUsers_pcu8[numUsers_u8];
            userId_internal_u8 = ComM_UserId_MappingTable_acst[userId_u8];
            userRamPtr_pst = &ComM_UserStruct[userId_internal_u8];

            #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
            userConfigPtr_pcst = &(COMM_GET_USER_LIST[userId_internal_u8]);
            #endif

            switch(PreviousMode_tu8)
            {
                case COMM_NO_COMMUNICATION : --(userRamPtr_pst->numChannelsInNoCom_u8);
                    break;
                case COMM_FULL_COMMUNICATION: --(userRamPtr_pst->numChannelsInFullCom_u8);
                    break;
                case COMM_SILENT_COMMUNICATION: --(userRamPtr_pst->numChannelsInSilentCom_u8);
                    break;
                default:

                    break;
            }

            switch(CurrentMode_tu8)
            {
                case COMM_NO_COMMUNICATION : ++(userRamPtr_pst->numChannelsInNoCom_u8);
                    break;
                case COMM_FULL_COMMUNICATION: ++(userRamPtr_pst->numChannelsInFullCom_u8);
                    break;
                case COMM_SILENT_COMMUNICATION: ++(userRamPtr_pst->numChannelsInSilentCom_u8);
                    break;
                default:

                    break;
            }

            #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

            if((userRamPtr_pst->LimitToNoComCtr_u16 > C_ZERO) &&
                    ((userRamPtr_pst->numChannelsInNoCom_u8) == (userConfigPtr_pcst->NumAllChannels_u8)))
            {
                (void)ComM_RequestComMode(userId_u8,COMM_NO_COMMUNICATION);
            }
            #endif

            #if(COMM_RTE_SUPPORT != STD_OFF)

            ComM_Lok_RteNotifyLowestComMode(userId_u8);
            #endif
            SchM_Exit_ComM_Channel();
        }
    }
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#if (COMM_RTE_SUPPORT != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Lok_RteNotifyLowestComMode(ComM_UserHandleType UserIndex_tu8)
{

    ComM_ModeType           lowestUserMode_tu8;
    ComM_UserVarType_tst *  userRamPtr_pst;
    uint8                   userId_internal_u8;

    userId_internal_u8 = ComM_UserId_MappingTable_acst[UserIndex_tu8];
    userRamPtr_pst = &ComM_UserStruct[userId_internal_u8];

    lowestUserMode_tu8 = ComM_Lok_getLeastBusSmMode(UserIndex_tu8);

    if(userRamPtr_pst->IndicatedUserMode_u8 != lowestUserMode_tu8)
    {
        userRamPtr_pst->IndicatedUserMode_u8 = lowestUserMode_tu8;
        ComM_Lok_Rte_Switch_UM_currentMode (UserIndex_tu8,lowestUserMode_tu8);
    }
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"
#endif

#if (COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Lok_SyncWakeUpIndication(void)
{
    uint8 loopCtr_u8;

    SchM_Enter_ComM_ChannelNoNest();

    for (loopCtr_u8 = C_ZERO; loopCtr_u8 < COMM_NO_OF_CHANNELS ;loopCtr_u8++)
    {
        ComM_ChannelVarType_tst * channelRamPtr_ps;
        channelRamPtr_ps = &ComM_ChannelStruct[loopCtr_u8];

        if(channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)
        {
            COMM_SET_BIT((channelRamPtr_ps -> PassiveRequestState_u8),(0x01));
        }

    }
    SchM_Exit_ComM_ChannelNoNest();

    #if (COMM_PNC_ENABLED != STD_OFF)

    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {
        ComM_PncRamStructType_tst * pncRamPtr_ps;
        SchM_Enter_ComM_PNCWakeUpNoNest();

        for (loopCtr_u8 = C_ZERO; loopCtr_u8 < COMM_NO_OF_PNCS ;loopCtr_u8++)
        {
            pncRamPtr_ps = &ComM_PncRamStruct[loopCtr_u8];

            if(pncRamPtr_ps->PncState_en == COMM_PNC_NO_COMMUNICATION)
            {
                pncRamPtr_ps->WakeUpStatus_b = TRUE;
            }
        }
        SchM_Exit_ComM_PNCWakeUpNoNest();
    }

    #endif
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

#if (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

void ComM_Lok_ProcessLimitToNoCom(NetworkHandleType Channel_tu8, boolean Status_b)
{

    ComM_ChannelVarType_tst * channelRamPtr_pst;

    channelRamPtr_pst = &ComM_ChannelStruct[Channel_tu8];

    if((COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_pst->InhibitionReqStatus_u8))) != Status_b)
    {
        SchM_Enter_ComM_LimitationNoNest();

        if(Status_b != FALSE)
        {

            COMM_SET_LIMIT_TO_NO_COM((channelRamPtr_pst->InhibitionReqStatus_u8));

            ComM_Lok_TranslateInhibitionStatus(Channel_tu8, COMM_LIMITTONOCOM, Status_b);
        }
        else
        {

            COMM_CLR_LIMIT_TO_NO_COM((channelRamPtr_pst->InhibitionReqStatus_u8));

            ComM_Lok_TranslateInhibitionStatus(Channel_tu8, COMM_LIMITTONOCOM, Status_b);
        }
        SchM_Exit_ComM_LimitationNoNest();
    }
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"
void ComM_Nm_TransmissionFailure
(
  NetworkHandleType Channel_tu8
)
{
    (void)(Channel_tu8);
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"
void ComM_Nm_NetworkTimeoutException
(
  NetworkHandleType Channel_tu8
)
{
    (void)(Channel_tu8);
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#if (COMM_PNC_ENABLED != STD_OFF)

LOCAL_INLINE boolean ComM_Lok_Getbit(uint8 PncId_u8, const uint8 Signal_Array_cu8[8])
{
    uint8 mask_u8 = C_ZERO;
    uint8 byteIndex_u8 = C_ZERO;
    uint8 bitPosition_u8 = C_ZERO;
    uint8 Sig_Value_u8 = C_ZERO;
    boolean RetVal_b = FALSE;

    byteIndex_u8 = (PncId_u8 - 8) >> 3;
    bitPosition_u8 = (PncId_u8 - 8) % 8;
    mask_u8 = (uint8)1 << (bitPosition_u8) ;

    Sig_Value_u8 = (Signal_Array_cu8[byteIndex_u8] & (mask_u8));

    RetVal_b = (Sig_Value_u8 == 0) ? (FALSE) : (TRUE) ;

    return RetVal_b;
}
#endif
