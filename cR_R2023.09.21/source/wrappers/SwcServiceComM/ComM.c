#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"
VAR(ComM_GlobalVarType,COMM_VAR) ComM_GlobalStruct;
VAR(ComM_UserVarType,COMM_VAR)  ComM_UserStruct[COMM_NO_OF_USERS];
VAR(ComM_ChannelVarType,COMM_VAR)  ComM_ChannelStruct[COMM_NO_OF_CHANNELS];
VAR(ComM_NvMStorageType,COMM_VAR) ComM_NvMblock;

#if(COMM_PNC_ENABLED != STD_OFF)

VAR(ComM_PncRamStructType,COMM_VAR) ComM_PncRamStruct[COMM_NO_OF_PNCS];
VAR(boolean,COMM_VAR) ComM_EIRA_RxSigVal[COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA][COMM_NO_OF_PNCS];

#if(COMM_PNC_GW_ENABLED != STD_OFF)
VAR(boolean,COMM_VAR) ComM_ERA_RxSigVal[COMM_NO_OF_CH_WITH_ERA][COMM_NO_OF_PNCS];
#endif

#endif

#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_Cfg_MemMap.hpp"

LOCAL_INLINE FUNC(boolean, COMM_CODE) ComM_LGetbit(uint8 PncId, CONST(uint8, AUTOMATIC) Signal_Array[8]);

#if(COMM_INHIBITION_ENABLED)
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LTranslateInhibitionToUser
                                            (
                                            P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Users_p
   ,     uint8 numUsers
   ,     ComM_InhibitionType InhibitionType
   ,     boolean Status
                                            );
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LUpdateInhibitionCounter
                                            (
                                            P2VAR(uint16, AUTOMATIC,COMM_APPL_DATA) InhibitionCounter_u8
   ,     boolean Status
                                            );
#endif

#if(COMM_PNC_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(void,COMM_CODE) ComM_LPncToChannelInterface
                                (
                                    PNCHandleType PncIndex,ComM_PncModeType PncState,ComM_PncModeType PncPreviousState
                                )

{

   VAR(uint8,AUTOMATIC) loopCtr_u8;
   VAR(uint8,AUTOMATIC) ChannelId;
   VAR(uint8,AUTOMATIC) numChannels;

   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
   P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;
   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[PncIndex]);
    numChannels = pncConfigPtr_pcs->NumChannels;

   if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
   {

    SchM_Enter_ComM_PNCNoNest();

   for(loopCtr_u8 = 0; loopCtr_u8 < numChannels ;loopCtr_u8++)
   {
        ChannelId = (pncConfigPtr_pcs->Channels[loopCtr_u8]);

        channelRamPtr_ps = &ComM_ChannelStruct[ChannelId];

        channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[ChannelId]);

        if(PncState == COMM_PNC_REQUESTED)
        {
            ++(channelRamPtr_ps->PncRequestCtr_u8);

            if(channelConfigPtr_pcs->PncNmRequest != FALSE)
            {

                channelRamPtr_ps->NmNetworkRequestStatus_b = TRUE;
            }
        }

        else if((PncState == COMM_PNC_READY_SLEEP) && (PncPreviousState == COMM_PNC_REQUESTED))
        {
            if(channelRamPtr_ps->PncRequestCtr_u8 != C_ZERO)
            {
                --(channelRamPtr_ps->PncRequestCtr_u8);
            }
            else{

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
                (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_PNC_MAINFNC_APIID,COMM_E_CNTR_UNDERFLW);
#endif
            }
        }
        else{

        }
   }
    SchM_Exit_ComM_PNCNoNest();
   }
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

#if(COMM_PNC_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(void,COMM_CODE) ComM_EIRA_CallBack
                            (
                            uint8 PnBusId
                            )
{

   uint8 PncIndex;
   uint8 SigValue[8];
   uint16 ComSigId_u16;
   P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
   P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;
   boolean EIRA_PncSigValue;

    SchM_Enter_ComM_EIRANoNest();

   if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
   {

        ComSigId_u16 = COMM_GET_EIRASIG_TABLE[PnBusId];

        if(ComSigId_u16 != COMM_COMSIGNAL_INVALID_ID)
        {

            (void)Com_ReceiveSignal(ComSigId_u16,&SigValue);

            for(PncIndex=0, pncRamPtr_ps = &ComM_PncRamStruct[0], pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[0]); PncIndex < COMM_NO_OF_PNCS; PncIndex++)
            {
                EIRA_PncSigValue = ComM_LGetbit(pncConfigPtr_pcs->PncId,SigValue);

                if(ComM_EIRA_RxSigVal[PnBusId][PncIndex]!= EIRA_PncSigValue)
                {
                    ComM_EIRA_RxSigVal[PnBusId][PncIndex] = EIRA_PncSigValue;

                    if(EIRA_PncSigValue != FALSE)
                    {
                        ++pncRamPtr_ps->EIRACnt_u8;
                    }
                    else
                    {
                        --pncRamPtr_ps->EIRACnt_u8;
                    }
                }
                pncRamPtr_ps++;
                pncConfigPtr_pcs++;
            }
        }
   }
    SchM_Exit_ComM_EIRANoNest();
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

#if(COMM_PNC_ENABLED != STD_OFF)

#if(COMM_PNC_GW_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(void,COMM_CODE) ComM_ERA_CallBack
                            (
                            uint8 PnBusId,ComM_PncGatewayType channelGwType
                            )
{

   uint8 PncIndex;
   boolean ERA_PncSigValue;
   uint16 ComSigId_u16;
   uint8 SigValue[8];
   P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
   P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;

    SchM_Enter_ComM_ERANoNest();

   if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
   {

        ComSigId_u16 = COMM_GET_ERASIG_TABLE[PnBusId];

        if(ComSigId_u16 != COMM_COMSIGNAL_INVALID_ID)
        {

            (void)Com_ReceiveSignal(ComSigId_u16,&SigValue);

            for(PncIndex=0, pncRamPtr_ps = &ComM_PncRamStruct[0], pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[0]); PncIndex < COMM_NO_OF_PNCS; PncIndex++)
            {
                ERA_PncSigValue = ComM_LGetbit(pncConfigPtr_pcs->PncId , SigValue);

                if(ComM_ERA_RxSigVal[PnBusId][PncIndex] != ERA_PncSigValue)
                {
                    ComM_ERA_RxSigVal[PnBusId][PncIndex] = ERA_PncSigValue;
                    if(ERA_PncSigValue != FALSE)
                    {

                        if(channelGwType == COMM_GATEWAY_TYPE_ACTIVE)
                        {
                            ++pncRamPtr_ps->ActiveERACnt_u8;
                        }
                        ++(pncRamPtr_ps->ERACnt_u8);
                    }
                    else
                    {

                        if(channelGwType == COMM_GATEWAY_TYPE_ACTIVE)
                        {
                            --pncRamPtr_ps->ActiveERACnt_u8;
                        }
                        --(pncRamPtr_ps->ERACnt_u8);
                    }
                }
                pncRamPtr_ps++;
                pncConfigPtr_pcs++;
            }
        }
   }

    SchM_Exit_ComM_ERANoNest();
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif
#endif

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(ComM_ModeType, COMM_CODE) ComM_LgetLeastBusSmMode(ComM_UserHandleType UserIndex)

{

   VAR(ComM_ModeType,AUTOMATIC) leastModeAmongChannels_e;
   P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;

   userRamPtr_ps = &ComM_UserStruct[UserIndex];

   if(userRamPtr_ps->numChannelsInNoCom_u8 != C_ZERO)
   {
        leastModeAmongChannels_e = COMM_NO_COMMUNICATION;
   }
   else if(userRamPtr_ps->numChannelsInSilentCom_u8 != C_ZERO)
   {
            leastModeAmongChannels_e = COMM_SILENT_COMMUNICATION;
   }
   else{
        leastModeAmongChannels_e = COMM_FULL_COMMUNICATION;
   }
    return leastModeAmongChannels_e;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#if(COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(void, COMM_CODE) ComM_LTranslateInhibitionStatus
                                            (
                                            NetworkHandleType Channel
   ,     ComM_InhibitionType InhibitionType
   ,     boolean Status
                                            )
{

   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

#if(COMM_PNC_ENABLED != STD_OFF)
   uint8 numPnc_u8;
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) pncs_p;
#endif

   channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);

#if(COMM_PNC_ENABLED != STD_OFF)
    pncs_p = channelConfigPtr_pcs->Pncs_p;
#endif

   ComM_LTranslateInhibitionToUser(channelConfigPtr_pcs->DirectUsers_p,channelConfigPtr_pcs->numDirectUsers_u8, InhibitionType,Status);

#if(COMM_PNC_ENABLED != STD_OFF)

   if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
   {
        for(numPnc_u8 = C_ZERO; numPnc_u8 < channelConfigPtr_pcs->numPncs_u8; ++numPnc_u8)
        {
            uint8 pncId_u8;
            P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
            P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;

            pncId_u8 = pncs_p[numPnc_u8];
            pncRamPtr_ps = &ComM_PncRamStruct[pncId_u8];
            pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[pncId_u8]);

            if(InhibitionType == COMM_PREVENTWAKEUP)
            {
                ComM_LUpdateInhibitionCounter(&(pncRamPtr_ps->WakeUpInhibitionCtr_u16),Status);
            }
            else{
                ComM_LUpdateInhibitionCounter(&(pncRamPtr_ps->LimitToNoComCtr_u16),Status);
            }

            ComM_LTranslateInhibitionToUser(pncConfigPtr_pcs->Users_p,pncConfigPtr_pcs->NumUsers_u8,InhibitionType,Status);

        }
   }
#endif
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

#if(COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LTranslateInhibitionToUser
                                            (
                                            P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Users_p
   ,     uint8 numUsers
   ,     ComM_InhibitionType InhibitionType
   ,     boolean Status
                                            )
{
   uint8 loopCounter_u8;
   uint8 userId_u8;
   P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;

   for(loopCounter_u8 = C_ZERO; loopCounter_u8 < numUsers; ++loopCounter_u8)
   {
        userId_u8 = Users_p[loopCounter_u8];
        userRamPtr_ps = &ComM_UserStruct[userId_u8];

        if(InhibitionType == COMM_PREVENTWAKEUP)
        {
            ComM_LUpdateInhibitionCounter(&(userRamPtr_ps->WakeUpInhibitionCtr_u16),Status);
        }
        else{
            ComM_LUpdateInhibitionCounter(&(userRamPtr_ps->LimitToNoComCtr_u16),Status);
        }
   }
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

#if(COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LUpdateInhibitionCounter
                                            (
                                            P2VAR(uint16, AUTOMATIC,COMM_APPL_DATA) InhibitionCounter_u8
   ,     boolean Status
                                            )
{
   if(Status != FALSE)
   {
        ++(*InhibitionCounter_u8);
   }
   else{
        --(*InhibitionCounter_u8);
   }
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
#endif

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(void, COMM_CODE) ComM_LUpdateChannelModes(NetworkHandleType Channel
   ,     ComM_ModeType PreviousMode, ComM_ModeType CurrentMode)
{

   uint8 numUsers_u8;
   uint8 userId_u8;
   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

   P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;
   P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) allUsers_p;

#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
   P2CONST(ComM_UsersType,AUTOMATIC,COMM_APPL_CONST) userConfigPtr_pcs;
#endif

   channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);
    allUsers_p = channelConfigPtr_pcs->AllUsers_p;

   if(PreviousMode != CurrentMode)
   {
        for(numUsers_u8= C_ZERO; numUsers_u8 < channelConfigPtr_pcs->numAllUsers_u8; ++numUsers_u8)
        {
            SchM_Enter_ComM_Channel();
            userId_u8 = allUsers_p[numUsers_u8];
            userRamPtr_ps = &ComM_UserStruct[userId_u8];

#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
            userConfigPtr_pcs = &(COMM_GET_USER_LIST[userId_u8]);
#endif

            switch(PreviousMode)
            {
                case COMM_NO_COMMUNICATION : --(userRamPtr_ps->numChannelsInNoCom_u8);
                    break;
                case COMM_FULL_COMMUNICATION: --(userRamPtr_ps->numChannelsInFullCom_u8);
                    break;
                case COMM_SILENT_COMMUNICATION: --(userRamPtr_ps->numChannelsInSilentCom_u8);
                    break;
                default:

                    break;
            }

            switch(CurrentMode)
            {
                case COMM_NO_COMMUNICATION : ++(userRamPtr_ps->numChannelsInNoCom_u8);
                    break;
                case COMM_FULL_COMMUNICATION: ++(userRamPtr_ps->numChannelsInFullCom_u8);
                    break;
                case COMM_SILENT_COMMUNICATION: ++(userRamPtr_ps->numChannelsInSilentCom_u8);
                    break;
                default:

                    break;
            }

#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

            if((userRamPtr_ps->LimitToNoComCtr_u16 > C_ZERO) &&
                    ((userRamPtr_ps->numChannelsInNoCom_u8) == (userConfigPtr_pcs->NumAllChannels_u8)))
            {
                (void)ComM_RequestComMode(userId_u8,COMM_NO_COMMUNICATION);
            }
#endif

#if(COMM_RTE_SUPPORT != STD_OFF)

            ComM_LRteNotifyLowestComMode(userId_u8);
#endif
            SchM_Exit_ComM_Channel();
        }
   }
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#if(COMM_RTE_SUPPORT != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(void, COMM_CODE) ComM_LRteNotifyLowestComMode
                                                (
                                                    ComM_UserHandleType UserIndex
                                                )
{

   ComM_ModeType lowestUserMode;
   P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;

   userRamPtr_ps = &ComM_UserStruct[UserIndex];

    lowestUserMode = ComM_LgetLeastBusSmMode(UserIndex);

   if(userRamPtr_ps->IndicatedUserMode_t != lowestUserMode)
   {
        userRamPtr_ps->IndicatedUserMode_t = lowestUserMode;
        ComM_Rte_Switch_UM_currentMode (UserIndex,lowestUserMode);
   }
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
#endif

#if(COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(void, COMM_CODE) ComM_LSyncWakeUpIndication(void){
   VAR(uint8,AUTOMATIC) loopCtr_u8;

    SchM_Enter_ComM_ChannelNoNest();

   for(loopCtr_u8 = C_ZERO; loopCtr_u8 < COMM_NO_OF_CHANNELS ;loopCtr_u8++)
   {
        P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
        channelRamPtr_ps = &ComM_ChannelStruct[loopCtr_u8];

        if(channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)
        {
            COMM_SET_BIT((channelRamPtr_ps -> PassiveRequestState_u8),(0x01));
        }

   }
    SchM_Exit_ComM_ChannelNoNest();

#if(COMM_PNC_ENABLED != STD_OFF)

   if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
   {
        P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
        SchM_Enter_ComM_PNCWakeUpNoNest();

        for(loopCtr_u8 = C_ZERO; loopCtr_u8 < COMM_NO_OF_PNCS ;loopCtr_u8++)
        {
            pncRamPtr_ps = &ComM_PncRamStruct[loopCtr_u8];

            if(pncRamPtr_ps->PncState_e == COMM_PNC_NO_COMMUNICATION)
            {
                pncRamPtr_ps->WakeUpStatus_b = TRUE;
            }
        }
        SchM_Exit_ComM_PNCWakeUpNoNest();
   }

#endif
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(Std_ReturnType, COMM_CODE) ComM_LProcessLimitToNoCom
                                (
                                 VAR(NetworkHandleType, COMM_VAR) Channel
   ,     VAR(boolean, COMM_VAR) Status
                                )
{

   VAR(Std_ReturnType, AUTOMATIC) ret_Val;
   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;

    ret_Val = E_OK;
   channelRamPtr_ps = &ComM_ChannelStruct[Channel];

   if((COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8))) != Status)
   {
        SchM_Enter_ComM_LimitationNoNest();

        if(Status != FALSE)
        {

            if(channelRamPtr_ps->ChannelState_e == COMM_FULL_COM_NETWORK_REQUESTED)
            {

                COMM_SET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8));

                ComM_LTranslateInhibitionStatus(Channel, COMM_LIMITTONOCOM, Status);
            }
            else{

                ret_Val = E_NOT_OK;
            }
        }
        else{

            COMM_CLR_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8));

            ComM_LTranslateInhibitionStatus(Channel, COMM_LIMITTONOCOM, Status);
        }
        SchM_Exit_ComM_LimitationNoNest();
   }

    return ret_Val;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(void, COMM_CODE) ComM_Nm_TransmissionFailure
(
  VAR(NetworkHandleType,AUTOMATIC) Channel
)
{
    (void)(Channel);
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(void, COMM_CODE) ComM_Nm_NetworkTimeoutException
(
  VAR(NetworkHandleType,AUTOMATIC) Channel
)
{
    (void)(Channel);
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
LOCAL_INLINE FUNC(boolean, COMM_CODE) ComM_LGetbit(uint8 PncId, CONST(uint8, AUTOMATIC) Signal_Array[8])
{
   uint8 mask;
   uint8 byteIndex;
   uint8 bitPosition;
   uint8 Sig_Value;
   boolean Ret_Val;

    mask = C_ZERO;
   byteIndex = C_ZERO;
   bitPosition = C_ZERO;
    Sig_Value = C_ZERO;
    Ret_Val = FALSE;
   byteIndex = (PncId - 8) >> 3;
   bitPosition = (PncId - 8) % 8;
    mask = (uint8)1 << (bitPosition) ;

    Sig_Value = (Signal_Array[byteIndex] & (mask));

    Ret_Val = (Sig_Value == 0) ? (FALSE) : (TRUE) ;

    return Ret_Val;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

