

#include "ComM_Priv.h"

#if ((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))

VAR(ComM_UserHandleArrayType,COMM_VAR)  ComM_FullComRequestors[COMM_NO_OF_CHANNELS];

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LUpdateUser
                        (
                         VAR(ComM_UserHandleType, COMM_VAR) User
                         );

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LDeleteUser
                        (
                         VAR(ComM_UserHandleType, COMM_VAR) User
                         );

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(void,COMM_CODE) ComM_LUpdateFullComRequestors
                                                (
                                                VAR(ComM_UserHandleType, COMM_VAR) User,
                                                VAR(ComM_ModeType, COMM_VAR) ComMode
                                                )
{

    P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;
    P2CONST(ComM_UsersType,AUTOMATIC,COMM_APPL_CONST) userConfPtr_pcs;

    userRamPtr_ps = &ComM_UserStruct[User];
    userConfPtr_pcs = &(COMM_GET_USER_LIST[User]);

    if (ComMode == COMM_FULL_COMMUNICATION)
    {
        #if (COMM_INHIBITION_ENABLED)
            if((userRamPtr_ps->LimitToNoComCtr_u16 != C_ZERO) ||
                ((userRamPtr_ps->WakeUpInhibitionCtr_u16 != C_ZERO) && (userRamPtr_ps->numChannelsInFullCom_u8 != userConfPtr_pcs->NumAllChannels_u8)))
            {

            }
            else
            {

                ComM_LUpdateUser(User);
            }
        #else
            {

                ComM_LUpdateUser(User);
            }
        #endif

    }
    else if(ComMode == COMM_NO_COMMUNICATION)
    {

        ComM_LDeleteUser(User);

    }
    else
    {

    }

}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LUpdateUser
                        (
                         VAR(ComM_UserHandleType, COMM_VAR) User
                        )
{

    P2VAR(ComM_UserHandleArrayType, AUTOMATIC, COMM_APPL_DATA) fullComRequestorRamPtr_ps;
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2CONST(ComM_UsersType,AUTOMATIC,COMM_APPL_CONST) userConfigPtr_pcs;
    VAR(ComM_UserHandleArrayType, AUTOMATIC) fullComRequestor_t;
    VAR(uint8, AUTOMATIC) loopCounter_u8;
    VAR(uint8, AUTOMATIC) channelId_u8;
    VAR(uint8, AUTOMATIC) numChannels_u8;
    VAR(uint8, AUTOMATIC) Index_u8;

    userConfigPtr_pcs = &(COMM_GET_USER_LIST[User]);
    numChannels_u8 = userConfigPtr_pcs->NumDirectChannels_u8;

    for(loopCounter_u8 = C_ZERO;loopCounter_u8 < numChannels_u8;loopCounter_u8++)
    {

       channelId_u8 = (userConfigPtr_pcs->DirectChannels_p[loopCounter_u8]);

       channelRamPtr_ps = &ComM_ChannelStruct[channelId_u8];

       fullComRequestorRamPtr_ps = &ComM_FullComRequestors[channelId_u8];

       SchM_Enter_ComM_FullComRequestors();

       fullComRequestor_t.numberOfRequesters = fullComRequestorRamPtr_ps->numberOfRequesters;

       for(Index_u8 = 0;Index_u8 < COMM_MAX_CHANNEL_REQUESTERS;Index_u8++)
       {
           fullComRequestor_t.handleArray[Index_u8] = fullComRequestorRamPtr_ps->handleArray[Index_u8];

       }

       fullComRequestor_t.handleArray[fullComRequestor_t.numberOfRequesters] =User;

       fullComRequestor_t.numberOfRequesters++;

       fullComRequestorRamPtr_ps->numberOfRequesters = fullComRequestor_t.numberOfRequesters;

       for(Index_u8 = 0;Index_u8 < COMM_MAX_CHANNEL_REQUESTERS;Index_u8++)
       {
           fullComRequestorRamPtr_ps->handleArray[Index_u8]=fullComRequestor_t.handleArray[Index_u8];

       }

       SchM_Exit_ComM_FullComRequestors();

       channelRamPtr_ps->ComMFullComReqNotify_b = TRUE;
   }

}

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LDeleteUser
                        (
                         VAR(ComM_UserHandleType, COMM_VAR) User
                         )
{

        P2VAR(ComM_UserHandleArrayType, AUTOMATIC, COMM_APPL_DATA) fullComReqRamPtr_ps;
        P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
        P2CONST(ComM_UsersType,AUTOMATIC,COMM_APPL_CONST) userCfgPtr_pcs;
        VAR(ComM_UserHandleArrayType, AUTOMATIC) fullComRequestors_t;
        VAR(uint8, AUTOMATIC) loopCount_u8;
        VAR(uint8, AUTOMATIC) channelId_u8;
        VAR(uint8, AUTOMATIC) numofChannels_u8;
        VAR(uint8, AUTOMATIC) arrayIndex_u8;
        VAR(uint8, AUTOMATIC) searchIndex_u8;
        VAR(uint8, AUTOMATIC) nextElementIndex_u8;

        userCfgPtr_pcs = &(COMM_GET_USER_LIST[User]);
        numofChannels_u8 = userCfgPtr_pcs->NumDirectChannels_u8;

        for(loopCount_u8 = C_ZERO;loopCount_u8 < numofChannels_u8;loopCount_u8++)
        {

           channelId_u8 = (userCfgPtr_pcs->DirectChannels_p[loopCount_u8]);

           fullComReqRamPtr_ps = &ComM_FullComRequestors[channelId_u8];

           channelRamPtr_ps = &ComM_ChannelStruct[channelId_u8];

           SchM_Enter_ComM_FullComRequestors();

           fullComRequestors_t.numberOfRequesters = fullComReqRamPtr_ps->numberOfRequesters;

           for(arrayIndex_u8 = 0;arrayIndex_u8 < COMM_MAX_CHANNEL_REQUESTERS;arrayIndex_u8++)
           {
               fullComRequestors_t.handleArray[arrayIndex_u8] = fullComReqRamPtr_ps->handleArray[arrayIndex_u8];

           }

           searchIndex_u8 =0;

           while ((searchIndex_u8 < COMM_MAX_CHANNEL_REQUESTERS) && (User != fullComRequestors_t.handleArray[searchIndex_u8]))
           {

               searchIndex_u8++;
           }
           if(searchIndex_u8 < COMM_MAX_CHANNEL_REQUESTERS)
           {

               for(nextElementIndex_u8=searchIndex_u8+1;nextElementIndex_u8<COMM_MAX_CHANNEL_REQUESTERS;searchIndex_u8++)
               {
                   fullComRequestors_t.handleArray[searchIndex_u8]=fullComRequestors_t.handleArray[nextElementIndex_u8];
                   nextElementIndex_u8++;

               }

               fullComRequestors_t.handleArray[nextElementIndex_u8-1]=COMM_NOT_USED_USER_ID;

               fullComRequestors_t.numberOfRequesters--;

               fullComReqRamPtr_ps->numberOfRequesters = fullComRequestors_t.numberOfRequesters;

               for(arrayIndex_u8 = 0;arrayIndex_u8 < COMM_MAX_CHANNEL_REQUESTERS;arrayIndex_u8++)
               {
                   fullComReqRamPtr_ps->handleArray[arrayIndex_u8] = fullComRequestors_t.handleArray[arrayIndex_u8];
               }

                channelRamPtr_ps->ComMFullComReqNotify_b = TRUE;

           }
           else
           {

           }

           SchM_Exit_ComM_FullComRequestors();

        }

}
#endif

