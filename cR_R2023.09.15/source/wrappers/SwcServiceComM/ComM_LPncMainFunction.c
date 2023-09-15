#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

#if(COMM_PNC_ENABLED != STD_OFF)
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncNoCommunication_StateHandling
                                                        (
                                                             VAR(NetworkHandleType,AUTOMATIC) PncIndex
   ,     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps
   ,     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps
   ,     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                        );

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncRequested_StateHandling
                                                        (
                                                             VAR(NetworkHandleType,AUTOMATIC) PncIndex
   ,     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps
   ,     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps
   ,     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs
   ,     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                        );

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncPrepareSleep_StateHandling
                                                        (
                                                            VAR(NetworkHandleType,AUTOMATIC) PncIndex
   ,     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps
   ,     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps
   ,     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs
   ,     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                        );

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncReadySleep_StateHandling
                                                        (
                                                            VAR(NetworkHandleType,AUTOMATIC) PncIndex
   ,     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps
   ,     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps
   ,     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs
   ,     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                        );

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LSetbit
                                    (
                                      uint8 PncId, P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) PnTxSignalVal_u8
                                    );

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LResetbit
                                      (
                                        uint8 PncId, P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) PnTxSignalVal_u8
                                      );

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LSetbit
                                    (
                                      uint8 PncId, P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) PnTxSignalVal_u8
                                    )

{

   uint8 byteIndex;
   uint8 bitPosition;
   uint8 mask;

   byteIndex = C_ZERO;
   bitPosition = C_ZERO;
    mask = C_ZERO;

   byteIndex = (PncId - 8) >> 3;
   bitPosition = (PncId - 8) % 8 ;
    mask = ((uint8)1 << bitPosition) ;

    *(PnTxSignalVal_u8+byteIndex) = (uint8)(*(PnTxSignalVal_u8+byteIndex) | (mask)) ;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LResetbit
                                      (
                                        uint8 PncId, P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) PnTxSignalVal_u8
                                      )
{

   uint8 byteIndex;
   uint8 bitPosition;
   uint8 mask;

   byteIndex = C_ZERO;
   bitPosition = C_ZERO;
    mask = C_ZERO;

   byteIndex = (PncId - 8) >> 3;
   bitPosition = (PncId - 8) % 8 ;
    mask = (~ ((uint8)1 << bitPosition));

    *(PnTxSignalVal_u8+byteIndex) = (uint8)(*(PnTxSignalVal_u8+byteIndex) & (mask));
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(void, COMM_CODE) ComM_LPncMainFunction
                                        (
                                            VAR(PNCHandleType,AUTOMATIC) PncIndex
                                        )
{

   VAR(ComM_PncModeType,AUTOMATIC)  pncStateOnEntry_e;
   P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
   P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;
   VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e;
   VAR(ComM_PncEventStructType,COMM_VAR) PncEventStruct;
   P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps;
   boolean stateChangePossible_b;
   boolean userRequestState_b;

#if(COMM_INHIBITION_ENABLED)
   P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
#endif

   PncEventStruct_ps = &PncEventStruct;
   stateChangePossible_b = FALSE;
   PncEventStruct_ps->wakeupRequestState_b = FALSE;
    pncRamPtr_ps = &ComM_PncRamStruct[PncIndex];
    pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[PncIndex]);
#if(COMM_INHIBITION_ENABLED)
    globalRamPtr_ps = &ComM_GlobalStruct;
#endif

   userRequestState_b = ((pncRamPtr_ps->UserRequestCnt_u8) > C_ZERO);

#if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)

   if((COMM_GET_PREVENT_WAKEUP((globalRamPtr_ps->ComM_EcuGroupClassification_u8))) &&
       ((pncRamPtr_ps->WakeUpInhibitionCtr_u16) > C_ZERO) &&
       (((pncRamPtr_ps->PncState_e) == COMM_PNC_NO_COMMUNICATION) || ((pncRamPtr_ps->PncState_e) == COMM_PNC_PREPARE_SLEEP)))
   {
        userRequestState_b = FALSE;
   }
#endif

#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

   if((COMM_GET_LIMIT_TO_NO_COM(globalRamPtr_ps->ComM_EcuGroupClassification_u8)) &&
            ((pncRamPtr_ps->LimitToNoComCtr_u16) != C_ZERO))
   {
        userRequestState_b = FALSE;
   }
#endif

#if(COMM_PNC_GW_ENABLED != STD_OFF)

   PncEventStruct_ps->activeERAState_b = ((pncRamPtr_ps->ActiveERACnt_u8 > C_ZERO) || (userRequestState_b));

   PncEventStruct_ps->activeRequestState_b = ((userRequestState_b)||((pncRamPtr_ps->ERACnt_u8) > C_ZERO));

#else

   PncEventStruct_ps->activeRequestState_b = ((pncRamPtr_ps->UserRequestCnt_u8) > C_ZERO);
#endif

   PncEventStruct_ps->passiveRequestState_b = ((pncRamPtr_ps->EIRACnt_u8) > C_ZERO);

   PncEventStruct_ps->wakeupRequestState_b = pncRamPtr_ps->WakeUpStatus_b;

    pncStateOnEntry_e = pncRamPtr_ps->PncState_e;

    previousPncState_e = pncStateOnEntry_e;

   if(COMM_GET_FEATURE_PNC_ENABLED)
   {

        do
        {
            switch(pncRamPtr_ps->PncState_e)
            {
                case COMM_PNC_NO_COMMUNICATION:
                {
                    ComM_PncNoCommunication_StateHandling(PncIndex, PncEventStruct_ps, pncRamPtr_ps
   ,     previousPncState_e);
                }
                break;

                case COMM_PNC_REQUESTED:
                {
                    ComM_PncRequested_StateHandling(PncIndex, PncEventStruct_ps, pncRamPtr_ps
   ,     pncConfigPtr_pcs, previousPncState_e);
                }
                break;

                case COMM_PNC_READY_SLEEP:
                {
                    ComM_PncReadySleep_StateHandling(PncIndex, PncEventStruct_ps, pncRamPtr_ps
   ,     pncConfigPtr_pcs, previousPncState_e);
                }
                break;

                case COMM_PNC_PREPARE_SLEEP:
                {
                    ComM_PncPrepareSleep_StateHandling(PncIndex, PncEventStruct_ps, pncRamPtr_ps
   ,     pncConfigPtr_pcs, previousPncState_e);
                }
                break;

                default:

                break;
            }

            if(pncStateOnEntry_e != pncRamPtr_ps->PncState_e)
            {
                stateChangePossible_b = TRUE;

                previousPncState_e = pncStateOnEntry_e;

                pncStateOnEntry_e = pncRamPtr_ps->PncState_e;
            }
            else{
                stateChangePossible_b = FALSE;
            }

        }while(stateChangePossible_b != FALSE);

   }
}

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncNoCommunication_StateHandling(
                                                                     VAR(NetworkHandleType,AUTOMATIC) PncIndex
   ,     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps
   ,     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps
   ,     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                                    )
{
   ComM_PncModeType   pncState_e;

    pncState_e = COMM_PNC_NO_COMMUNICATION;

   if(previousPncState_e !=  COMM_PNC_NO_COMMUNICATION)
   {

        BswM_ComM_CurrentPNCMode(PncIndex,COMM_PNC_NO_COMMUNICATION);
   }

   else{

        if(PncEventStruct_ps->activeRequestState_b != FALSE)
        {
            pncState_e = COMM_PNC_REQUESTED;
        }
        else if(PncEventStruct_ps->passiveRequestState_b != FALSE)
        {
            pncState_e = COMM_PNC_READY_SLEEP;
        }
        else if(PncEventStruct_ps->wakeupRequestState_b != FALSE)
        {
            pncState_e = COMM_PNC_PREPARE_SLEEP;
        }
        else{

        }
   }

   if(pncState_e != COMM_PNC_NO_COMMUNICATION)
   {
        SchM_Enter_ComM_PNCWakeUpNoNest();

        pncRamPtr_ps->PncState_e = pncState_e;

        pncRamPtr_ps->WakeUpStatus_b = FALSE;

        SchM_Exit_ComM_PNCWakeUpNoNest();
   }
}

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncRequested_StateHandling
                                                    (
                                                         VAR(NetworkHandleType,AUTOMATIC) PncIndex
   ,     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps
   ,     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps
   ,     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs
   ,     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                    )
{

   ComM_PncModeType   pncState_e;
   uint8 channelId_u8;
   uint8 loopCtr_u8;
   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    pncState_e = COMM_PNC_REQUESTED;

   if(previousPncState_e != COMM_PNC_REQUESTED)
   {

        BswM_ComM_CurrentPNCMode(PncIndex,COMM_PNC_REQUESTED);

        ComM_LPncToChannelInterface(PncIndex,COMM_PNC_REQUESTED,previousPncState_e);

        for(loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcs->NumChannels; loopCtr_u8++)
        {
            channelId_u8 = (pncConfigPtr_pcs->Channels[loopCtr_u8]);

            channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
            channelRamPtr_ps = &(ComM_ChannelStruct[channelId_u8]);

            if((channelConfigPtr_pcs->TxSigId)!= COMM_COMSIGNAL_INVALID_ID)
            {
   			#if(COMM_PNC_GW_ENABLED != STD_OFF)
                if((channelConfigPtr_pcs->PncGwType == COMM_GATEWAY_TYPE_ACTIVE)||
                   ((channelConfigPtr_pcs->PncGwType == COMM_GATEWAY_TYPE_PASSIVE)&&(PncEventStruct_ps->activeERAState_b)))
                {
                    SchM_Enter_ComM_PNCTxSigNoNest();
                    ComM_LSetbit(pncConfigPtr_pcs->PncId, (channelRamPtr_ps->PnTxSigVal_u8));
                    SchM_Exit_ComM_PNCTxSigNoNest();

                    (void)Com_SendSignal(channelConfigPtr_pcs->TxSigId, (channelRamPtr_ps->PnTxSigVal_u8));
                }
                else{
                    SchM_Enter_ComM_PNCTxSigNoNest();
                    ComM_LResetbit(pncConfigPtr_pcs->PncId, (channelRamPtr_ps->PnTxSigVal_u8));
                    SchM_Exit_ComM_PNCTxSigNoNest();

                    (void)Com_SendSignal(channelConfigPtr_pcs->TxSigId, (channelRamPtr_ps->PnTxSigVal_u8));
                }

                pncRamPtr_ps->ActiveERAStateOld_b = PncEventStruct_ps->activeERAState_b;
#else
                SchM_Enter_ComM_PNCTxSigNoNest();
                ComM_LSetbit(pncConfigPtr_pcs->PncId, (channelRamPtr_ps->PnTxSigVal_u8));
                SchM_Exit_ComM_PNCTxSigNoNest();

                (void)Com_SendSignal(channelConfigPtr_pcs->TxSigId, (channelRamPtr_ps->PnTxSigVal_u8));

#endif

            }
        }
   }

   else{

   	if(PncEventStruct_ps->activeRequestState_b != FALSE)
        {

#if(COMM_PNC_GW_ENABLED != STD_OFF)

            if(pncRamPtr_ps->ActiveERAStateOld_b != PncEventStruct_ps->activeERAState_b)
            {
                for(loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcs->NumChannels; loopCtr_u8++)
                {
                   channelId_u8 = pncConfigPtr_pcs->Channels[loopCtr_u8];
                   channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
                   channelRamPtr_ps = &ComM_ChannelStruct[channelId_u8];

                    if((channelConfigPtr_pcs->PncGwType == COMM_GATEWAY_TYPE_PASSIVE))
                    {
                        if((channelConfigPtr_pcs->TxSigId)!= COMM_COMSIGNAL_INVALID_ID)
                        {
   						if(PncEventStruct_ps->activeERAState_b != FALSE)
                            {
   						    SchM_Enter_ComM_PNCTxSigNoNest();
   						    ComM_LSetbit(pncConfigPtr_pcs->PncId, (channelRamPtr_ps->PnTxSigVal_u8));
   						    SchM_Exit_ComM_PNCTxSigNoNest();

                                (void)Com_SendSignal(channelConfigPtr_pcs->TxSigId, &(channelRamPtr_ps->PnTxSigVal_u8[0]));
                            }
                            else
                            {
                                SchM_Enter_ComM_PNCTxSigNoNest();
                                ComM_LResetbit(pncConfigPtr_pcs->PncId, (channelRamPtr_ps->PnTxSigVal_u8));
                                SchM_Exit_ComM_PNCTxSigNoNest();

                                (void)Com_SendSignal(channelConfigPtr_pcs->TxSigId, (channelRamPtr_ps->PnTxSigVal_u8));
                            }

                        }
                    }
                }

                pncRamPtr_ps->ActiveERAStateOld_b = PncEventStruct_ps->activeERAState_b;
            }
#endif
        }
        else{

   		pncState_e = COMM_PNC_READY_SLEEP;
        }
   }

   if(pncState_e != COMM_PNC_REQUESTED)
   {

        pncRamPtr_ps->PncState_e = pncState_e;
   }
}

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncReadySleep_StateHandling
                                                    (
                                                        VAR(NetworkHandleType,AUTOMATIC) PncIndex
   ,     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps
   ,     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps
   ,     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs
   ,     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                    )
{
   ComM_PncModeType   pncState_e;

   uint8 channelId_u8;
   uint8 loopCtr_u8;
   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;
   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;

    pncState_e = COMM_PNC_READY_SLEEP;

   if(previousPncState_e != COMM_PNC_READY_SLEEP)
   {

        BswM_ComM_CurrentPNCMode(PncIndex,COMM_PNC_READY_SLEEP);

        ComM_LPncToChannelInterface(PncIndex,COMM_PNC_READY_SLEEP,previousPncState_e);

        if(previousPncState_e == COMM_PNC_REQUESTED)
        {

            for(loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcs->NumChannels; loopCtr_u8++)
            {
                channelId_u8 = pncConfigPtr_pcs->Channels[loopCtr_u8];
                channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
                channelRamPtr_ps = &ComM_ChannelStruct[channelId_u8];

                if((channelConfigPtr_pcs->TxSigId)!= COMM_COMSIGNAL_INVALID_ID)
                {
                    SchM_Enter_ComM_PNCTxSigNoNest();
                    ComM_LResetbit(pncConfigPtr_pcs->PncId, &(channelRamPtr_ps->PnTxSigVal_u8[0]));
                    SchM_Exit_ComM_PNCTxSigNoNest();

                    (void)Com_SendSignal(channelConfigPtr_pcs->TxSigId,&channelRamPtr_ps->PnTxSigVal_u8[0]);
                }

            }
        }
   }

   else{

        if((PncEventStruct_ps->activeRequestState_b) != FALSE)
        {
            pncState_e = COMM_PNC_REQUESTED;
        }
        else if((PncEventStruct_ps->passiveRequestState_b) != FALSE)
        {

        }
        else{
            pncState_e = COMM_PNC_PREPARE_SLEEP;
        }
   }

   if(pncState_e != COMM_PNC_READY_SLEEP)
   {

        pncRamPtr_ps->PncState_e = pncState_e;
   }
}

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncPrepareSleep_StateHandling
                                                    (
                                                        VAR(NetworkHandleType,AUTOMATIC) PncIndex
   ,     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps
   ,     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps
   ,     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs
   ,     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                    )
{
   ComM_PncModeType   pncState_e;

    pncState_e = COMM_PNC_PREPARE_SLEEP;

   if(previousPncState_e != COMM_PNC_PREPARE_SLEEP)
   {

        BswM_ComM_CurrentPNCMode(PncIndex,COMM_PNC_PREPARE_SLEEP);

        pncRamPtr_ps->PrepareSleepTimer_u16 = pncConfigPtr_pcs->PrepareSleepTimer ;
   }

   else{

        if((pncRamPtr_ps->PrepareSleepTimer_u16)!= C_ZERO)
        {
            --pncRamPtr_ps->PrepareSleepTimer_u16;
        }

        if(PncEventStruct_ps->activeRequestState_b != FALSE)
        {
            pncState_e = COMM_PNC_REQUESTED;
        }
        else if(PncEventStruct_ps->passiveRequestState_b != FALSE)
        {
            pncState_e = COMM_PNC_READY_SLEEP;
        }
        else if(pncRamPtr_ps->PrepareSleepTimer_u16 == C_ZERO)
        {
            pncState_e = COMM_PNC_NO_COMMUNICATION;
        }
        else{

        }
   }

   if(pncState_e != COMM_PNC_PREPARE_SLEEP)
   {

        pncRamPtr_ps->PncState_e = pncState_e;
   }
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

