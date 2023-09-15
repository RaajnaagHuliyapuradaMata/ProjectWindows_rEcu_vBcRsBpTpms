

#include "ComM_Priv.hpp"

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))

ComM_UserHandleArrayType ComM_FullComRequestors[COMM_NO_OF_CHANNELS];

LOCAL_INLINE void ComM_Lok_UpdateUser(ComM_UserHandleType User_tu8);

LOCAL_INLINE void ComM_Lok_DeleteUser(ComM_UserHandleType User_tu8);

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComM_Lok_UpdateFullComRequestors(ComM_UserHandleType User_tu8, ComM_ModeType ComMode_tu8)
{

   ComM_UserVarType_tst *      userRamPtr_pst;
   const ComM_UsersType_tst *  userConfPtr_pcst;

   userRamPtr_pst = &ComM_UserStruct[ComM_UserId_MappingTable_acst[User_tu8]];
   userConfPtr_pcst = &(COMM_GET_USER_LIST[ComM_UserId_MappingTable_acst[User_tu8]]);

   if(ComMode_tu8 == COMM_FULL_COMMUNICATION)
   {
#if(COMM_INHIBITION_ENABLED)
            if((userRamPtr_pst->LimitToNoComCtr_u16 != C_ZERO) ||
                ((userRamPtr_pst->WakeUpInhibitionCtr_u16 != C_ZERO) && (userRamPtr_pst->numChannelsInFullCom_u8 != userConfPtr_pcst->NumAllChannels_u8)))
            {

            }
            else{

                ComM_Lok_UpdateUser(User_tu8);
            }
#else{

                ComM_Lok_UpdateUser(User_tu8);
            }
#endif

   }
   else if(ComMode_tu8 == COMM_NO_COMMUNICATION)
   {

        ComM_Lok_DeleteUser(User_tu8);

   }
   else{

   }
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

LOCAL_INLINE void ComM_Lok_UpdateUser(ComM_UserHandleType User_tu8)
{

   ComM_UserHandleArrayType *  fullComRequestorRamPtr_pst;
   ComM_ChannelVarType_tst *   channelRamPtr_pst;
   const ComM_UsersType_tst *  userConfigPtr_pcst;
   ComM_UserHandleArrayType    fullComRequestor_st;
   uint8                       loopCounter_u8;
   uint8                       channelId_u8;
   uint8                       numChannels_u8;
   uint8                       Index_u8;

   userConfigPtr_pcst = &(COMM_GET_USER_LIST[ComM_UserId_MappingTable_acst[User_tu8]]);
    numChannels_u8 = userConfigPtr_pcst->NumDirectChannels_u8;

   for(loopCounter_u8 = C_ZERO;loopCounter_u8 < numChannels_u8;loopCounter_u8++)
   {

       channelId_u8 = (userConfigPtr_pcst->DirectChannels_pcu8[loopCounter_u8]);

       channelRamPtr_pst = &ComM_ChannelStruct[channelId_u8];

       fullComRequestorRamPtr_pst = &ComM_FullComRequestors[channelId_u8];

       SchM_Enter_ComM_FullComRequestors();

       fullComRequestor_st.numberOfRequesters = fullComRequestorRamPtr_pst->numberOfRequesters;

       for(Index_u8 = 0;Index_u8 < COMM_MAX_CHANNEL_REQUESTERS;Index_u8++)
       {
           fullComRequestor_st.handleArray[Index_u8] = fullComRequestorRamPtr_pst->handleArray[Index_u8];

       }

       fullComRequestor_st.handleArray[fullComRequestor_st.numberOfRequesters] =User_tu8;

       fullComRequestor_st.numberOfRequesters++;

       fullComRequestorRamPtr_pst->numberOfRequesters = fullComRequestor_st.numberOfRequesters;

       for(Index_u8 = 0;Index_u8 < COMM_MAX_CHANNEL_REQUESTERS;Index_u8++)
       {
           fullComRequestorRamPtr_pst->handleArray[Index_u8]=fullComRequestor_st.handleArray[Index_u8];

       }

       SchM_Exit_ComM_FullComRequestors();

       channelRamPtr_pst->ComMFullComReqNotify_b = TRUE;
   }
}

LOCAL_INLINE void ComM_Lok_DeleteUser(ComM_UserHandleType User_tu8)
{

   ComM_UserHandleArrayType *  fullComReqRamPtr_pst;
   ComM_ChannelVarType_tst *   channelRamPtr_pst;
   const ComM_UsersType_tst *  userCfgPtr_pcs;
   ComM_UserHandleArrayType    fullComRequestors_st;
   uint8                       loopCount_u8;
   uint8                       channelId_u8;
   uint8                       numofChannels_u8;
   uint8                       arrayIndex_u8;
   uint8                       searchIndex_u8;
   uint8                       nextElementIndex_u8;

   userCfgPtr_pcs = &(COMM_GET_USER_LIST[ComM_UserId_MappingTable_acst[User_tu8]]);
    numofChannels_u8 = userCfgPtr_pcs->NumDirectChannels_u8;

   for(loopCount_u8 = C_ZERO;loopCount_u8 < numofChannels_u8;loopCount_u8++)
   {

        channelId_u8 = (userCfgPtr_pcs->DirectChannels_pcu8[loopCount_u8]);

        fullComReqRamPtr_pst = &ComM_FullComRequestors[channelId_u8];

        channelRamPtr_pst = &ComM_ChannelStruct[channelId_u8];

        SchM_Enter_ComM_FullComRequestors();

        fullComRequestors_st.numberOfRequesters = fullComReqRamPtr_pst->numberOfRequesters;

        for(arrayIndex_u8 = 0;arrayIndex_u8 < COMM_MAX_CHANNEL_REQUESTERS;arrayIndex_u8++)
        {
            fullComRequestors_st.handleArray[arrayIndex_u8] = fullComReqRamPtr_pst->handleArray[arrayIndex_u8];

        }

        searchIndex_u8 =0;

        while((searchIndex_u8 < COMM_MAX_CHANNEL_REQUESTERS) && (User_tu8 != fullComRequestors_st.handleArray[searchIndex_u8]))
        {

            searchIndex_u8++;
        }
        if(searchIndex_u8 < COMM_MAX_CHANNEL_REQUESTERS)
        {

            for(nextElementIndex_u8=searchIndex_u8+1;nextElementIndex_u8<COMM_MAX_CHANNEL_REQUESTERS;searchIndex_u8++)
            {
                fullComRequestors_st.handleArray[searchIndex_u8]=fullComRequestors_st.handleArray[nextElementIndex_u8];
                nextElementIndex_u8++;

            }

            fullComRequestors_st.handleArray[nextElementIndex_u8-1]=COMM_NOT_USED_USER_ID;

            fullComRequestors_st.numberOfRequesters--;

            fullComReqRamPtr_pst->numberOfRequesters = fullComRequestors_st.numberOfRequesters;

            for(arrayIndex_u8 = 0;arrayIndex_u8 < COMM_MAX_CHANNEL_REQUESTERS;arrayIndex_u8++)
            {
                fullComReqRamPtr_pst->handleArray[arrayIndex_u8] = fullComRequestors_st.handleArray[arrayIndex_u8];
            }

            channelRamPtr_pst->ComMFullComReqNotify_b = TRUE;

        }
        else{

        }

        SchM_Exit_ComM_FullComRequestors();

   }
}
#endif

