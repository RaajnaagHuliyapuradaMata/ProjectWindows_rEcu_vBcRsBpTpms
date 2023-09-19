#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LUpdateUserRequest
                        (
                        P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) RequestCounter_u8
   ,     VAR(ComM_ModeType, AUTOMATIC) CurrentComMode_t
                        );

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

FUNC(Std_ReturnType,COMM_CODE) ComM_RequestComMode
                                                (
                                                VAR(ComM_UserHandleType, COMM_VAR) User
   ,     VAR(ComM_ModeType, COMM_VAR) ComMode
                                                )
{

   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
   P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;
   P2CONST(ComM_UsersType,AUTOMATIC,COMM_APPL_CONST) userConfigPtr_pcs;
   VAR(ComM_ModeType, AUTOMATIC) previousUserRequest_t;
   VAR(ComM_ModeType, AUTOMATIC) currentUserRequest_t;

#if(COMM_PNC_ENABLED != STD_OFF)
   P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
#endif

#if(COMM_INHIBITION_ENABLED)
   P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus!=COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
   }

   if((ComMode != COMM_NO_COMMUNICATION) && (ComMode != COMM_FULL_COMMUNICATION))
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }

   if(User >= COMM_NO_OF_USERS)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
   }
#endif

   userConfigPtr_pcs = &(COMM_GET_USER_LIST[User]);
   userRamPtr_ps = &ComM_UserStruct[User];
    previousUserRequest_t = userRamPtr_ps->RequestedUserMode_t;
   userRamPtr_ps->RequestedUserMode_t = ComMode;
   currentUserRequest_t = ComMode ;

   if(previousUserRequest_t != currentUserRequest_t)
   {
        uint8 loopCounter_u8;
        uint8 channelId_u8;
        uint8 numChannels_u8;

#if(COMM_PNC_ENABLED != STD_OFF)
        uint8 pncId_u8;
        uint8 numPncs_u8;

        numPncs_u8 = userConfigPtr_pcs->NumPnc_u8;
#endif

        numChannels_u8 = userConfigPtr_pcs->NumDirectChannels_u8;

        SchM_Enter_ComM_UserNoNest();

        for(loopCounter_u8 = C_ZERO;loopCounter_u8 < numChannels_u8;loopCounter_u8++)
        {
            channelId_u8 = (userConfigPtr_pcs->DirectChannels_p[loopCounter_u8]);
            channelRamPtr_ps = &ComM_ChannelStruct[channelId_u8];

            ComM_LUpdateUserRequest(&(channelRamPtr_ps->UserRequestCtr_u8), currentUserRequest_t);
        }

#if(COMM_PNC_ENABLED != STD_OFF)

        if(COMM_GET_FEATURE_PNC_ENABLED)
        {
            for(loopCounter_u8 = C_ZERO; loopCounter_u8 < numPncs_u8; loopCounter_u8++)
            {
                pncId_u8 = (userConfigPtr_pcs->Pncs_p[loopCounter_u8]);
                pncRamPtr_ps = &ComM_PncRamStruct[pncId_u8];

                ComM_LUpdateUserRequest(&(pncRamPtr_ps ->UserRequestCnt_u8), currentUserRequest_t);
            }
        }
#endif

        SchM_Exit_ComM_UserNoNest();
#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
        ComM_LUpdateFullComRequestors(User,ComMode);
#endif

   }

#if(COMM_INHIBITION_ENABLED)
    globalRamPtr_ps = &ComM_GlobalStruct;

   if((userRamPtr_ps->LimitToNoComCtr_u16 != C_ZERO) ||
       ((userRamPtr_ps->WakeUpInhibitionCtr_u16 != C_ZERO) && (userRamPtr_ps->numChannelsInFullCom_u8 != userConfigPtr_pcs->NumAllChannels_u8)))
   {
        if(currentUserRequest_t == COMM_FULL_COMMUNICATION)
        {
            if(globalRamPtr_ps->ComM_InhibitCounter_u16 != COMM_MAX_U16)
            {
                ++(globalRamPtr_ps->ComM_InhibitCounter_u16);
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
#include "ComM_Cfg_MemMap.hpp"

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LUpdateUserRequest
                        (
                        P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) RequestCounter_u8
   ,     VAR(ComM_ModeType, AUTOMATIC) CurrentComMode_t
                        )
{

   if(CurrentComMode_t == COMM_FULL_COMMUNICATION)
   {
        ++ (*RequestCounter_u8);
   }
   else if(CurrentComMode_t == COMM_NO_COMMUNICATION)
   {
        if((*RequestCounter_u8) != C_ZERO)
        {
            -- (*RequestCounter_u8);
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

