

#include "ComM_Priv.h"

#if (COMM_PNC_ENABLED != STD_OFF)

LOCAL_INLINE void ComM_Lok_PncNoCommunication_StateHandling(NetworkHandleType               PncIndex_tu8,
                                                            ComM_PncEventStructType_tst *   PncEventStruct_pst,
                                                            ComM_PncRamStructType_tst *     pncRamPtr_pst,
                                                            ComM_PncModeType                previousPncState_en);

LOCAL_INLINE void ComM_Lok_PncRequested_StateHandling(NetworkHandleType                 PncIndex_tu8,
                                                      ComM_PncEventStructType_tst *     PncEventStruct_pst,
                                                      ComM_PncRamStructType_tst *       pncRamPtr_pst,
                                                      const ComM_PncConfigStruct_tst *  pncConfigPtr_pcst,
                                                      ComM_PncModeType                  previousPncState_en);

LOCAL_INLINE void ComM_Lok_PncPrepareSleep_StateHandling(NetworkHandleType                  PncIndex_tu8,
                                                         ComM_PncEventStructType_tst *      PncEventStruct_pst,
                                                         ComM_PncRamStructType_tst *        pncRamPtr_pst,
                                                         const ComM_PncConfigStruct_tst *   pncConfigPtr_pcst,
                                                         ComM_PncModeType                   previousPncState_en);

LOCAL_INLINE void ComM_Lok_PncReadySleep_StateHandling(NetworkHandleType                PncIndex_tu8,
                                                       ComM_PncEventStructType_tst *    PncEventStruct_pst,
                                                       ComM_PncRamStructType_tst *      pncRamPtr_pst,
                                                       const ComM_PncConfigStruct_tst * pncConfigPtr_pcst,
                                                       ComM_PncModeType                 previousPncState_en);

LOCAL_INLINE void ComM_Lok_Setbit(uint8 PncId_u8, uint8 * PnTxSignalVal_pu8);

LOCAL_INLINE void ComM_Lok_Resetbit(uint8 PncId_u8, uint8 * PnTxSignalVal_pu8);

#if ((COMM_PNC_GW_ENABLED != STD_OFF) && (COMM_ZERO_PNC_VECTOR_AVOIDANCE != STD_OFF))
LOCAL_INLINE void ComM_Lok_PncToPassiveChannelInterface(ComM_ChannelVarType_tst *  channelRamPtr_pst,
                                                         boolean                    PncActiveRequestStatus_b,
                                                         boolean                    PncNmRequest_b);
#endif

LOCAL_INLINE void ComM_Lok_Setbit(uint8 PncId_u8, uint8 * PnTxSignalVal_pu8)

{

    uint8   byteIndex_u8;
    uint8   bitPosition_u8;
    uint8   mask_u8;

    byteIndex_u8 = C_ZERO;
    bitPosition_u8 = C_ZERO;
    mask_u8 = C_ZERO;

    byteIndex_u8 = (PncId_u8 - 8) >> 3;
    bitPosition_u8 = (PncId_u8 - 8) % 8 ;
    mask_u8 = ((uint8)1 << bitPosition_u8) ;

    *(PnTxSignalVal_pu8+byteIndex_u8) = (uint8)(*(PnTxSignalVal_pu8+byteIndex_u8) | (mask_u8)) ;
}

LOCAL_INLINE void ComM_Lok_Resetbit(uint8 PncId_u8, uint8 * PnTxSignalVal_pu8)
{

    uint8   byteIndex_u8;
    uint8   bitPosition_u8;
    uint8   mask_u8;

    byteIndex_u8 = C_ZERO;
    bitPosition_u8 = C_ZERO;
    mask_u8 = C_ZERO;

    byteIndex_u8 = (PncId_u8 - 8) >> 3;
    bitPosition_u8 = (PncId_u8 - 8) % 8 ;
    mask_u8 = (~ ((uint8)1 << bitPosition_u8));

    *(PnTxSignalVal_pu8+byteIndex_u8) = (uint8)(*(PnTxSignalVal_pu8+byteIndex_u8) & (mask_u8));
}

#if ((COMM_PNC_GW_ENABLED != STD_OFF) && (COMM_ZERO_PNC_VECTOR_AVOIDANCE != STD_OFF))

LOCAL_INLINE void ComM_Lok_PncToPassiveChannelInterface(ComM_ChannelVarType_tst * channelRamPtr_pst,
                                                         boolean                    PncActiveRequestStatus_b,
                                                         boolean                    PncNmRequest_b)
{

    if(PncActiveRequestStatus_b != FALSE)
    {

        ++(channelRamPtr_pst->PncRequestCtr_u8);

        if(PncNmRequest_b != FALSE)
        {

            channelRamPtr_pst->NmNetworkRequestStatus_b = TRUE;
        }
    }
    else
    {

        if((channelRamPtr_pst->PncRequestCtr_u8) != C_ZERO)
        {
            -- (channelRamPtr_pst->PncRequestCtr_u8);
        }
        else
        {

            #if (COMM_DEV_ERROR_DETECT != STD_OFF)
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_REQ_COMMODE_APIID,COMM_E_CNTR_UNDERFLW);
            #endif
        }
    }
}

#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"
void ComM_Lok_PncMainFunction(PNCHandleType PncIndex_tu8)
{

    ComM_PncModeType                    pncStateOnEntry_en;
    ComM_PncRamStructType_tst *         pncRamPtr_pst;
    const ComM_PncConfigStruct_tst *    pncConfigPtr_pcst;
    ComM_PncModeType                    previousPncState_en;
    ComM_PncEventStructType_tst         PncEventStruct_st;
    ComM_PncEventStructType_tst *       PncEventStruct_pst;
    boolean                             stateChangePossible_b;
    boolean                             userRequestState_b;

    #if(COMM_INHIBITION_ENABLED)
    ComM_GlobalVarType_tst *            globalRamPtr_pst;
    #endif

    PncEventStruct_pst = &PncEventStruct_st;
    stateChangePossible_b = FALSE;
    PncEventStruct_pst->wakeupRequestState_b = FALSE;
    pncRamPtr_pst = &ComM_PncRamStruct[PncIndex_tu8];
    pncConfigPtr_pcst = &(COMM_GET_PNC_LIST[PncIndex_tu8]);
    #if(COMM_INHIBITION_ENABLED)
    globalRamPtr_pst = &ComM_GlobalStruct;
    #endif

    userRequestState_b = ((pncRamPtr_pst->UserRequestCnt_u8) > C_ZERO);

    #if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)

    if((COMM_GET_PREVENT_WAKEUP((globalRamPtr_pst->ComM_EcuGroupClassification_u8))) &&
       ((pncRamPtr_pst->WakeUpInhibitionCtr_u16) > C_ZERO) &&
       (((pncRamPtr_pst->PncState_en) == COMM_PNC_NO_COMMUNICATION) || ((pncRamPtr_pst->PncState_en) == COMM_PNC_PREPARE_SLEEP)))
    {
        userRequestState_b = FALSE;
    }
    #endif

    #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

    if ((COMM_GET_LIMIT_TO_NO_COM(globalRamPtr_pst->ComM_EcuGroupClassification_u8)) &&
            ((pncRamPtr_pst->LimitToNoComCtr_u16) != C_ZERO))
    {
        userRequestState_b = FALSE;
    }
    #endif

    #if (COMM_PNC_GW_ENABLED != STD_OFF)

    PncEventStruct_pst->activeERAState_b = ((pncRamPtr_pst->ActiveERACnt_u8 > C_ZERO) || (userRequestState_b));

    PncEventStruct_pst->activeRequestState_b = ((userRequestState_b)||((pncRamPtr_pst->ERACnt_u8) > C_ZERO));

    #else

    PncEventStruct_pst->activeRequestState_b = ((pncRamPtr_pst->UserRequestCnt_u8) > C_ZERO);
    (void)userRequestState_b;
    #endif

    PncEventStruct_pst->passiveRequestState_b = ((pncRamPtr_pst->EIRACnt_u8) > C_ZERO);

    PncEventStruct_pst->wakeupRequestState_b = pncRamPtr_pst->WakeUpStatus_b;

    pncStateOnEntry_en = pncRamPtr_pst->PncState_en;

    previousPncState_en = pncStateOnEntry_en;

    if(COMM_GET_FEATURE_PNC_ENABLED)
    {

        do
        {
            switch (pncRamPtr_pst->PncState_en)
            {
                case COMM_PNC_NO_COMMUNICATION:
                {
                    ComM_Lok_PncNoCommunication_StateHandling(PncIndex_tu8, PncEventStruct_pst, pncRamPtr_pst,
                                                                        previousPncState_en);
                }
                break;

                case COMM_PNC_REQUESTED:
                {
                    ComM_Lok_PncRequested_StateHandling(PncIndex_tu8, PncEventStruct_pst, pncRamPtr_pst,
                                                            pncConfigPtr_pcst, previousPncState_en);
                }
                break;

                case COMM_PNC_READY_SLEEP:
                {
                    ComM_Lok_PncReadySleep_StateHandling(PncIndex_tu8, PncEventStruct_pst, pncRamPtr_pst,
                                                               pncConfigPtr_pcst, previousPncState_en);
                }
                break;

                case COMM_PNC_PREPARE_SLEEP:
                {
                    ComM_Lok_PncPrepareSleep_StateHandling(PncIndex_tu8, PncEventStruct_pst, pncRamPtr_pst,
                                                                    pncConfigPtr_pcst, previousPncState_en);
                }
                break;

                default:

                break;
            }

            if(pncStateOnEntry_en != pncRamPtr_pst->PncState_en)
            {
                stateChangePossible_b = TRUE;

                previousPncState_en = pncStateOnEntry_en;

                pncStateOnEntry_en = pncRamPtr_pst->PncState_en;
            }
            else
            {
                stateChangePossible_b = FALSE;
            }

        } while (stateChangePossible_b != FALSE);

    }
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

LOCAL_INLINE void ComM_Lok_PncNoCommunication_StateHandling(NetworkHandleType               PncIndex_tu8,
                                                            ComM_PncEventStructType_tst *   PncEventStruct_pst,
                                                            ComM_PncRamStructType_tst *     pncRamPtr_pst,
                                                            ComM_PncModeType                previousPncState_en)
{
    ComM_PncModeType   pncState_en;

    pncState_en = COMM_PNC_NO_COMMUNICATION;

    if(previousPncState_en !=  COMM_PNC_NO_COMMUNICATION)
    {

        BswM_ComM_CurrentPNCMode(PncIndex_tu8,COMM_PNC_NO_COMMUNICATION);
    }

    else
    {

        if(PncEventStruct_pst->activeRequestState_b != FALSE)
        {
            pncState_en = COMM_PNC_REQUESTED;
        }
        else if (PncEventStruct_pst->passiveRequestState_b != FALSE)
        {
            pncState_en = COMM_PNC_READY_SLEEP;
        }
        else if (PncEventStruct_pst->wakeupRequestState_b != FALSE)
        {
            pncState_en = COMM_PNC_PREPARE_SLEEP;
        }
        else
        {

        }
    }

    if(pncState_en != COMM_PNC_NO_COMMUNICATION)
    {
        SchM_Enter_ComM_PNCWakeUpNoNest();

        pncRamPtr_pst->PncState_en = pncState_en;

        pncRamPtr_pst->WakeUpStatus_b = FALSE;

        SchM_Exit_ComM_PNCWakeUpNoNest();
    }
}

LOCAL_INLINE void ComM_Lok_PncRequested_StateHandling(NetworkHandleType                 PncIndex_tu8,
                                                      ComM_PncEventStructType_tst *     PncEventStruct_pst,
                                                      ComM_PncRamStructType_tst *       pncRamPtr_pst,
                                                      const ComM_PncConfigStruct_tst *  pncConfigPtr_pcst,
                                                      ComM_PncModeType                  previousPncState_en)
{

    ComM_PncModeType                pncState_en;
    uint8                           channelId_u8;
    uint8                           loopCtr_u8;
    ComM_ChannelVarType_tst *       channelRamPtr_pst;
    const ComM_ChannelType_tst *    channelConfigPtr_pcst;
    boolean                         ActiveERAStatus_b;

    pncState_en = COMM_PNC_REQUESTED;
    ActiveERAStatus_b = TRUE;

    if(previousPncState_en != COMM_PNC_REQUESTED)
    {

        BswM_ComM_CurrentPNCMode(PncIndex_tu8,COMM_PNC_REQUESTED);

        #if ((COMM_PNC_GW_ENABLED != STD_OFF) && (COMM_ZERO_PNC_VECTOR_AVOIDANCE != STD_OFF))
        ActiveERAStatus_b = PncEventStruct_pst->activeERAState_b;
        #endif

        ComM_Lok_PncToChannelInterface( PncIndex_tu8,COMM_PNC_REQUESTED,previousPncState_en,ActiveERAStatus_b);

        for (loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcst->NumChannels_u8; loopCtr_u8++)
        {
            channelId_u8 = (pncConfigPtr_pcst->Channels_pcu8[loopCtr_u8]);

            channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
            channelRamPtr_pst = &(ComM_ChannelStruct[channelId_u8]);

            if((channelConfigPtr_pcst->TxSigId_u16)!= COMM_COMSIGNAL_INVALID_ID)
            {
                #if (COMM_PNC_GW_ENABLED != STD_OFF)
                if ((channelConfigPtr_pcst->PncGwType_en == COMM_GATEWAY_TYPE_ACTIVE)||
                   ((channelConfigPtr_pcst->PncGwType_en == COMM_GATEWAY_TYPE_PASSIVE)&&(PncEventStruct_pst->activeERAState_b)))
                {
                    SchM_Enter_ComM_PNCTxSigNoNest();
                    ComM_Lok_Setbit(pncConfigPtr_pcst->PncId_u8, (channelRamPtr_pst->PnTxSigVal_u8));
                    SchM_Exit_ComM_PNCTxSigNoNest();

                    (void)Com_SendSignal(channelConfigPtr_pcst->TxSigId_u16, (channelRamPtr_pst->PnTxSigVal_u8));
                }
                else
                {
                    SchM_Enter_ComM_PNCTxSigNoNest();
                    ComM_Lok_Resetbit(pncConfigPtr_pcst->PncId_u8, (channelRamPtr_pst->PnTxSigVal_u8));
                    SchM_Exit_ComM_PNCTxSigNoNest();

                    #if (COMM_ZERO_PNC_VECTOR_AVOIDANCE == STD_OFF)
                    (void)Com_SendSignal(channelConfigPtr_pcst->TxSigId_u16, (channelRamPtr_pst->PnTxSigVal_u8));
                    #endif
                }

                pncRamPtr_pst->ActiveERAStateOld_b = PncEventStruct_pst->activeERAState_b;
                #else
                SchM_Enter_ComM_PNCTxSigNoNest();
                ComM_Lok_Setbit(pncConfigPtr_pcst->PncId_u8, (channelRamPtr_pst->PnTxSigVal_u8));
                SchM_Exit_ComM_PNCTxSigNoNest();

                (void)Com_SendSignal(channelConfigPtr_pcst->TxSigId_u16, (channelRamPtr_pst->PnTxSigVal_u8));

                #endif

            }
        }
    }

    else
    {

        if(PncEventStruct_pst->activeRequestState_b != FALSE)
        {

        #if (COMM_PNC_GW_ENABLED != STD_OFF)

            if(pncRamPtr_pst->ActiveERAStateOld_b != PncEventStruct_pst->activeERAState_b)
            {
                for (loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcst->NumChannels_u8; loopCtr_u8++)
                {
                   channelId_u8 = pncConfigPtr_pcst->Channels_pcu8[loopCtr_u8];
                   channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
                   channelRamPtr_pst = &ComM_ChannelStruct[channelId_u8];

                    if ((channelConfigPtr_pcst->PncGwType_en == COMM_GATEWAY_TYPE_PASSIVE))
                    {
                        if((channelConfigPtr_pcst->TxSigId_u16)!= COMM_COMSIGNAL_INVALID_ID)
                        {

                            #if (COMM_ZERO_PNC_VECTOR_AVOIDANCE != STD_OFF)

                            SchM_Enter_ComM_PNCNoNest();

                            ComM_Lok_PncToPassiveChannelInterface(channelRamPtr_pst, PncEventStruct_pst->activeERAState_b,
                                                                   channelConfigPtr_pcst->PncNmRequest_b);
                            SchM_Exit_ComM_PNCNoNest();

                            #endif
                            if(PncEventStruct_pst->activeERAState_b != FALSE)
                            {
                                SchM_Enter_ComM_PNCTxSigNoNest();
                                ComM_Lok_Setbit(pncConfigPtr_pcst->PncId_u8, (channelRamPtr_pst->PnTxSigVal_u8));
                                SchM_Exit_ComM_PNCTxSigNoNest();

                                (void)Com_SendSignal(channelConfigPtr_pcst->TxSigId_u16, &(channelRamPtr_pst->PnTxSigVal_u8[0]));
                            }
                            else
                            {
                                SchM_Enter_ComM_PNCTxSigNoNest();
                                ComM_Lok_Resetbit(pncConfigPtr_pcst->PncId_u8, (channelRamPtr_pst->PnTxSigVal_u8));
                                SchM_Exit_ComM_PNCTxSigNoNest();

                                 #if (COMM_ZERO_PNC_VECTOR_AVOIDANCE == STD_OFF)

                                (void)Com_SendSignal(channelConfigPtr_pcst->TxSigId_u16, (channelRamPtr_pst->PnTxSigVal_u8));
                                #endif
                            }

                        }
                    }
                }

                pncRamPtr_pst->ActiveERAStateOld_b = PncEventStruct_pst->activeERAState_b;
            }
        #endif
        }
        else
        {

            pncState_en = COMM_PNC_READY_SLEEP;
        }
    }

    if(pncState_en != COMM_PNC_REQUESTED)
    {

        pncRamPtr_pst->PncState_en = pncState_en;
    }
}

LOCAL_INLINE void ComM_Lok_PncReadySleep_StateHandling(NetworkHandleType                PncIndex_tu8,
                                                       ComM_PncEventStructType_tst *    PncEventStruct_pst,
                                                       ComM_PncRamStructType_tst *      pncRamPtr_pst,
                                                       const ComM_PncConfigStruct_tst * pncConfigPtr_pcst,
                                                       ComM_PncModeType                 previousPncState_en)
{

    ComM_PncModeType                pncState_en;
    uint8                           channelId_u8;
    uint8                           loopCtr_u8;
    const ComM_ChannelType_tst *    channelConfigPtr_pcst;
    ComM_ChannelVarType_tst *       channelRamPtr_pst;
    boolean                         ActiveERAStateOldStatus_b;

    pncState_en = COMM_PNC_READY_SLEEP;
    ActiveERAStateOldStatus_b = FALSE;

    if(previousPncState_en != COMM_PNC_READY_SLEEP)
    {

        BswM_ComM_CurrentPNCMode(PncIndex_tu8,COMM_PNC_READY_SLEEP);

        #if ((COMM_PNC_GW_ENABLED != STD_OFF) && (COMM_ZERO_PNC_VECTOR_AVOIDANCE != STD_OFF))
        ActiveERAStateOldStatus_b = pncRamPtr_pst->ActiveERAStateOld_b;
        pncRamPtr_pst->ActiveERAStateOld_b = FALSE;
        #endif

        ComM_Lok_PncToChannelInterface(PncIndex_tu8,COMM_PNC_READY_SLEEP,previousPncState_en,ActiveERAStateOldStatus_b);

        if(previousPncState_en == COMM_PNC_REQUESTED)
        {

            for(loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcst->NumChannels_u8; loopCtr_u8++)
            {
                channelId_u8 = pncConfigPtr_pcst->Channels_pcu8[loopCtr_u8];
                channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
                channelRamPtr_pst = &ComM_ChannelStruct[channelId_u8];

                if((channelConfigPtr_pcst->TxSigId_u16)!= COMM_COMSIGNAL_INVALID_ID)
                {
                    SchM_Enter_ComM_PNCTxSigNoNest();
                    ComM_Lok_Resetbit(pncConfigPtr_pcst->PncId_u8, &(channelRamPtr_pst->PnTxSigVal_u8[0]));
                    SchM_Exit_ComM_PNCTxSigNoNest();

                    (void)Com_SendSignal(channelConfigPtr_pcst->TxSigId_u16,&channelRamPtr_pst->PnTxSigVal_u8[0]);
                }

            }
        }
    }

    else
    {

        if((PncEventStruct_pst->activeRequestState_b) != FALSE)
        {
            pncState_en = COMM_PNC_REQUESTED;
        }
        else if((PncEventStruct_pst->passiveRequestState_b) != FALSE)
        {

        }
        else
        {
            pncState_en = COMM_PNC_PREPARE_SLEEP;
        }
    }

    if(pncState_en != COMM_PNC_READY_SLEEP)
    {

        pncRamPtr_pst->PncState_en = pncState_en;
    }
}

LOCAL_INLINE void ComM_Lok_PncPrepareSleep_StateHandling(NetworkHandleType                  PncIndex_tu8,
                                                         ComM_PncEventStructType_tst *      PncEventStruct_pst,
                                                         ComM_PncRamStructType_tst *        pncRamPtr_pst,
                                                         const ComM_PncConfigStruct_tst *   pncConfigPtr_pcst,
                                                         ComM_PncModeType                   previousPncState_en)
{
    ComM_PncModeType   pncState_en;

    pncState_en = COMM_PNC_PREPARE_SLEEP;

    if(previousPncState_en != COMM_PNC_PREPARE_SLEEP)
    {

        BswM_ComM_CurrentPNCMode(PncIndex_tu8,COMM_PNC_PREPARE_SLEEP);

        pncRamPtr_pst->PrepareSleepTimer_u16 = pncConfigPtr_pcst->PrepareSleepTimer_u16;
    }

    else
    {

        if((pncRamPtr_pst->PrepareSleepTimer_u16)!= C_ZERO)
        {
            --pncRamPtr_pst->PrepareSleepTimer_u16;
        }

        if(PncEventStruct_pst->activeRequestState_b != FALSE)
        {
            pncState_en = COMM_PNC_REQUESTED;
        }
        else if(PncEventStruct_pst->passiveRequestState_b != FALSE)
        {
            pncState_en = COMM_PNC_READY_SLEEP;
        }
        else if(pncRamPtr_pst->PrepareSleepTimer_u16 == C_ZERO)
        {
            pncState_en = COMM_PNC_NO_COMMUNICATION;
        }
        else
        {

        }
    }

    if(pncState_en != COMM_PNC_PREPARE_SLEEP)
    {

        pncRamPtr_pst->PncState_en = pncState_en;
    }
}

#endif

