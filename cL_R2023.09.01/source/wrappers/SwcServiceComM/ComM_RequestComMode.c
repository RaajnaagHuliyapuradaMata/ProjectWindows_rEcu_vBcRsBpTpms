

#include "ComM_Priv.hpp"

LOCAL_INLINE void ComM_Lok_UpdateUserRequest(uint16 * RequestCounter_pu16, ComM_ModeType CurrentComMode_tu8);

#if(COMM_PNC_ENABLED != STD_OFF)
LOCAL_INLINE void ComM_Lok_UpdatePncUserRequest(uint8 * RequestCounter_pu8, ComM_ModeType CurrentComMode_tu8);
#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

Std_ReturnType ComM_RequestComMode(ComM_UserHandleType User, ComM_ModeType ComMode)
{

   ComM_ChannelVarType_tst *   channelRamPtr_pst;
   ComM_UserVarType_tst *      userRamPtr_pst;
   const ComM_UsersType_tst *  userConfigPtr_pcst;
   ComM_ModeType               previousUserRequest_tu8;
   ComM_ModeType               currentUserRequest_tu8;
   uint8                       userId_internal_u8;

#if(COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)
   ComM_ChannelVarType_tst *   masterChannelRamPtr_pst;
   const ComM_ChannelType_tst *    channelConfigPtr_pcst;
   uint8                       masterChannelId_u8;
#endif

#if(COMM_PNC_ENABLED != STD_OFF)
   ComM_PncRamStructType_tst *     pncRamPtr_pst;
#endif

#if(COMM_INHIBITION_ENABLED)
   ComM_GlobalVarType_tst *        globalRamPtr_pst;
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus_en!=COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
   }

   if((ComMode != COMM_NO_COMMUNICATION) && (ComMode != COMM_FULL_COMMUNICATION))
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }

   if( ComM_Lok_ValidateUserId(User) == FALSE )
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }
#endif

   userId_internal_u8 = ComM_UserId_MappingTable_acst[User];
   userConfigPtr_pcst = &(COMM_GET_USER_LIST[userId_internal_u8]);
   userRamPtr_pst = &ComM_UserStruct[userId_internal_u8];
    previousUserRequest_tu8 = userRamPtr_pst->RequestedUserMode_u8;
   userRamPtr_pst->RequestedUserMode_u8 = ComMode;
   currentUserRequest_tu8 = ComMode ;

   if(previousUserRequest_tu8 != currentUserRequest_tu8)
   {
        uint8   loopCounter_u8;
        uint8   channelId_u8;
        uint8   numChannels_u8;

#if(COMM_PNC_ENABLED != STD_OFF)
        uint8   pncId_u8;
        uint8   numPncs_u8;

        numPncs_u8 = userConfigPtr_pcst->NumPnc_u8;
#endif

        numChannels_u8 = userConfigPtr_pcst->NumDirectChannels_u8;

        SchM_Enter_ComM_UserNoNest();

        for(loopCounter_u8 = C_ZERO;loopCounter_u8 < numChannels_u8;loopCounter_u8++)
        {
            channelId_u8 = (userConfigPtr_pcst->DirectChannels_pcu8[loopCounter_u8]);
            channelRamPtr_pst = &ComM_ChannelStruct[channelId_u8];

#if(COMM_MANAGING_CHANNEL_PRESENT != STD_OFF)
            channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
            if(channelConfigPtr_pcst->ComMMasterChannelPresent_b == TRUE)
            {

                masterChannelId_u8 = channelConfigPtr_pcst->masterChannelId_u8;
                masterChannelRamPtr_pst = &ComM_ChannelStruct[masterChannelId_u8];

                ComM_Lok_UpdateUserRequest(&(masterChannelRamPtr_pst->UserRequestCtr_u16), currentUserRequest_tu8);
            }
#endif

            ComM_Lok_UpdateUserRequest(&(channelRamPtr_pst->UserRequestCtr_u16), currentUserRequest_tu8);
        }

#if(COMM_PNC_ENABLED != STD_OFF)

        if(COMM_GET_FEATURE_PNC_ENABLED)
        {
            for(loopCounter_u8 = C_ZERO; loopCounter_u8 < numPncs_u8; loopCounter_u8++)
            {
                pncId_u8 = (userConfigPtr_pcst->Pncs_pcu8[loopCounter_u8]);
                pncRamPtr_pst = &ComM_PncRamStruct[pncId_u8];

                ComM_Lok_UpdatePncUserRequest(&(pncRamPtr_pst ->UserRequestCnt_u8), currentUserRequest_tu8);
            }
        }
#endif

        SchM_Exit_ComM_UserNoNest();
#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
        ComM_Lok_UpdateFullComRequestors(User,ComMode);
#endif

   }

#if(COMM_INHIBITION_ENABLED)
    globalRamPtr_pst = &ComM_GlobalStruct;

   if((userRamPtr_pst->LimitToNoComCtr_u16 != C_ZERO) ||
       ((userRamPtr_pst->WakeUpInhibitionCtr_u16 != C_ZERO) && (userRamPtr_pst->numChannelsInFullCom_u8 != userConfigPtr_pcst->NumAllChannels_u8)))
   {
        if(currentUserRequest_tu8 == COMM_FULL_COMMUNICATION)
        {
            if(globalRamPtr_pst->ComM_InhibitCounter_u16 != COMM_MAX_U16)
            {
                ++(globalRamPtr_pst->ComM_InhibitCounter_u16);
            }

            return COMM_E_MODE_LIMITATION;
        }
        else{

            return E_OK;
        }

   }
   else
#endif
   {
        return E_OK;
   }
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

LOCAL_INLINE void ComM_Lok_UpdateUserRequest(uint16 * RequestCounter_pu16, ComM_ModeType CurrentComMode_tu8)
{

   if(CurrentComMode_tu8 == COMM_FULL_COMMUNICATION)
   {
        ++ (*RequestCounter_pu16);
   }
   else if(CurrentComMode_tu8 == COMM_NO_COMMUNICATION)
   {
        if((*RequestCounter_pu16) != C_ZERO_U16)
        {
            -- (*RequestCounter_pu16);
        }
        else{

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_CNTR_UNDERFLW);
#endif
        }
   }
   else{

   }
}

#if(COMM_PNC_ENABLED != STD_OFF)
LOCAL_INLINE void ComM_Lok_UpdatePncUserRequest(uint8 * RequestCounter_pu8, ComM_ModeType CurrentComMode_tu8)
{

   if(CurrentComMode_tu8 == COMM_FULL_COMMUNICATION)
   {
        ++ (*RequestCounter_pu8);
   }
   else if(CurrentComMode_tu8 == COMM_NO_COMMUNICATION)
   {
        if((*RequestCounter_pu8) != C_ZERO)
        {
            -- (*RequestCounter_pu8);
        }
        else{

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_CNTR_UNDERFLW);
#endif
        }
   }
   else{

   }
}
#endif

