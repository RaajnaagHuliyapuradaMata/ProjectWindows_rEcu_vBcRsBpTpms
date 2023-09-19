#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmCore_DslDsd_Prot.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_DslTxType_tst,DCM_VAR) Dcm_DslTransmit_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
VAR(boolean,DCM_VAR) Dcm_isSessionStored_b;
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
VAR(boolean,DCM_VAR) Dcm_isFirstReponseSent_b;
static VAR(boolean,DCM_VAR) Dcm_isApplicationCalled_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(void,DCM_CODE) DCM_P2TimerStart(void){
    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,(Dcm_DsldTimer_st.dataTimeoutP2max_u32 - \
             Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust), \
             Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
}
#endif

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isConfirmationOnActiveConnection(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) DcmTxPduId)
{
    return (CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId] == Dcm_DsldGlobal_st.dataActiveTxPduId_u8);
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isPositiveResponseSupressed(\
        P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{
    return((FALSE != (pMsgContext->msgAddInfo).suppressPosResponse) && \
            (Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == 0x00u));
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isNegativeResponseSupressed(\
        P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,VAR(uint8,AUTOMATIC) NrcValue_u8)
{

    return((pMsgContext->dcmRxPduId >= DCM_INDEX_FUNC_RX_PDUID) && (DCM_IS_KWPPROT_ACTIVE() == FALSE) && \
               (DCM_CFG_SUPPRESS_NRC(NrcValue_u8)) && (Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == 0x00u));
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isDcmWaitingForTxConfirmation(void){
    return (!(((Dcm_Lok_GetDslState() == DSL_STATE_REQUEST_RECEIVED)           && \
            (Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_P2MAX_TIMEMONITORING))   || \
            ((Dcm_Lok_GetDslState()   == DSL_STATE_RESPONSE_TRANSMISSION)      && \
            (Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_SEND_GENERAL_REJECT))    || \
            (Dcm_Lok_GetDslState()    == DSL_STATE_ROETYPE1_RECEIVED)));
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isNormalResponseConfirmationProcessed(void){
    return((Dcm_Lok_GetDsdState() == DSD_SENDTXCONF_APPL) && \
       (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE) && \
       (Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX)
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
       && (Dcm_Lok_GetDslPreemptionState() != DSL_SUBSTATE_STOP_PROTOCOL)
#endif
        );
}

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))

LOCAL_INLINE FUNC(boolean,DCM_CODE)Dcm_Lok_isKWPSplitResponseTimeout(void){
   VAR(boolean,AUTOMATIC) isResponseTimeout_b = FALSE;
   VAR(Dcm_DsdStatesType_ten,DCM_VAR) stDsdStateTemp_en  = Dcm_Lok_GetDsdState();

   if((DCM_IS_KWPPROT_ACTIVE() != FALSE) && (Dcm_isFirstReponseSent_b!=FALSE) && \
            (Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX) && \
       ((stDsdStateTemp_en == DSD_CALL_SERVICE)||(stDsdStateTemp_en == DSD_WAITFORTXCONF)))
   {
        isResponseTimeout_b = TRUE;
   }

    return isResponseTimeout_b;
}
#endif

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isConfirmationForPendingResponse(void){
    return (Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 > 0x0u);
}

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isConfirmationForKWPResponse(VAR(Std_ReturnType,AUTOMATIC) Result)
{
    return ((Result == E_OK) && \
            (DCM_IS_KWPPROT_ACTIVE() != FALSE) && \
            (Dcm_DsldGlobal_st.dataResponseByDsd_b == FALSE ) && \
            (Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE));
}
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isConfirmationForRoeType2Response(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) DcmTxPduId)
{
    return ((Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_Roe2MesContext_st.dcmRxPduId]].roetype2_txpdu_u8 == \
            CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId]) && \
            (Dcm_DsdRoe2State_en == DSD_WAITFORTXCONF));
}
#endif

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_CheckWaitPendCounterOverflow(void){
    return((Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 < DCM_CFG_MAX_WAITPEND) \
            || (DCM_CFG_MAX_WAITPEND == DCM_MAXNUMRESPONSEPENDING));
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isConfirmationReceivedForNrc21Response(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) DcmTxPduId
   ,     VAR(uint8,AUTOMATIC) idxRxPduId)
{
   VAR(boolean, AUTOMATIC) confirmStatus_b = FALSE;

   VAR(uint8,AUTOMATIC) ConnectionId_u8     = Dcm_DsldRxTable_pcu8[idxRxPduId];
   VAR(uint8,AUTOMATIC) idxProtocol_u8      = Dcm_DsldConnTable_pcst[ConnectionId_u8].protocol_num_u8;
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) idxTxpduid_u8   = Dcm_DsldConnTable_pcst[ConnectionId_u8].txpduid_num_u8;

   if(( FALSE   != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b)          && \
        ( DCM_SERVICEID_DEFAULT_VALUE !=  Dcm_DslRxPduArray_ast[idxRxPduId].Dcm_DslServiceId_u8 )   && \
        ( idxTxpduid_u8 == CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId] ))
   {
        confirmStatus_b = TRUE;
   }

    return confirmStatus_b;
}

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isResponseSentForDSCService(void){
    return ((Dcm_DsldGlobal_st.dataSid_u8 == DCM_SID_DIAGNOSTICSESSIONCONTROL) &&
            (Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE) &&
            (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE));
}
#endif

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isHighPriorityRequestReceiving(void){
   VAR(boolean,AUTOMATIC) isRequestReceiving_b = FALSE;
   VAR(Dcm_DsdStatesType_ten,DCM_VAR) stDsdStateTemp_en  = Dcm_Lok_GetDsdState();

   if(((Dcm_Lok_GetDslPreemptionState() == DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING) ||\
             (Dcm_Lok_GetDslPreemptionState() == DSL_SUBSTATE_STOP_PROTOCOL))          &&\
             (stDsdStateTemp_en == DSD_WAITFORTXCONF))
   {
        isRequestReceiving_b = TRUE;
   }

    return isRequestReceiving_b;
}
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static FUNC(void,DCM_CODE) Dcm_Lok_InactivateComMChannel(void){
    SchM_Enter_Dcm_Global_NoNest();
   if(FALSE != Dcm_Lok_isNormalResponseConfirmationProcessed())
   {
        ComM_DCM_InactiveDiagnostic(Dcm_active_commode_e[\
                         Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
   }
    SchM_Exit_Dcm_Global_NoNest();

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
   if(FALSE != Dcm_Lok_isKWPSplitResponseTimeout())
   {
        ComM_DCM_InactiveDiagnostic(Dcm_active_commode_e[\
                         Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
   }
#endif
}

#if((DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
static FUNC(void,DCM_CODE) Dcm_Lok_ProcessSessionChangeOnWarmResp (void){
    Dcm_SesChgOnWarmResp_b = FALSE;

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
    (void)SchM_Switch_SwcServiceDcm_tDiagnosticSessionControl(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].SessionMode);
#endif

    Dcm_DsldSetsessionTiming(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32,Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32);
    Dcm_Lok_SetSesCtrlType(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].session_level);
}
#endif

static FUNC(void,DCM_CODE) Dcm_Lok_DsdConfirmation (void){
   if(Dcm_Lok_GetDslState() != DSL_STATE_ROETYPE1_RECEIVED){
        Dcm_Lok_ReloadS3Timer();
   }
   if(Dcm_Lok_GetDsdState() == DSD_WAITFORTXCONF){
        Dcm_Lok_SetDsdState(DSD_SENDTXCONF_APPL);
   }
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
   else{
        if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE){
            Dcm_Lok_SetDsdState(DSD_SENDTXCONF_APPL);
        }
   }
#endif

#if((DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
   if(Dcm_SesChgOnWarmResp_b == TRUE){
        Dcm_Lok_ProcessSessionChangeOnWarmResp();
   }
#endif
    Dcm_Lok_InactivateComMChannel();
}

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )

static FUNC(void,DCM_CODE) Dcm_Lok_SetNewSession(void){
   VAR(uint8,AUTOMATIC) nrSessions_u8 = 0u;
   VAR(uint8,AUTOMATIC) idxSession_u8 = 0u;

   if(FALSE != Dcm_Lok_isResponseSentForDSCService())
   {

        Dcm_DsldGlobal_st.PreviousSessionIndex = Dcm_DsldGlobal_st.idxActiveSession_u8;

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
        if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
        {
            nrSessions_u8 = DCM_CFG_NUM_KWP_SESSIONS;
        }
        else{
            nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
        }
#else
        nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
#endif

        for(idxSession_u8 = 0x0; idxSession_u8 < nrSessions_u8 ; idxSession_u8++)
        {
            if(Dcm_DsldSessionTable_pcu8[idxSession_u8]== Dcm_Dsp_Session[Dcm_ctDiaSess_u8].session_level)
            {

                Dcm_DsldGlobal_st.idxActiveSession_u8  = idxSession_u8;
                break;
            }
        }

        Dcm_isSessionStored_b =  TRUE;
   }
}
#endif

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_CheckP2StarTimer(void){
   VAR(Std_ReturnType,AUTOMATIC) halfP2timeStatus = E_NOT_OK;
   VAR(uint32,AUTOMATIC) halfP2timer_u32   = 0u;

#if(DCM_CFG_OSTIMER_USE != FALSE)
   VAR(uint32,AUTOMATIC) currentOSTimerTicks_u32 = 0u;
#endif

   if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == 0u)
   {
        halfP2timeStatus = E_OK;
   }
   else{
        halfP2timer_u32 = Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 >> 1u;

#if(DCM_CFG_OSTIMER_USE != FALSE)

        Dcm_P2OrS3TimerStatus_uchr = Dcm_GetCounterValue(DCM_CFG_COUNTERID, (&currentOSTimerTicks_u32));

        if(E_OK == Dcm_P2OrS3TimerStatus_uchr)
        {
            if((DCM_CFG_TICKS2US_COUNTER(currentOSTimerTicks_u32 - Dcm_P2OrS3StartTick_u32)) >= (halfP2timer_u32))
            {
                halfP2timeStatus = E_OK;
            }
        }
        else{
            if(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32 < (halfP2timer_u32/DCM_CFG_TASK_TIME_US))
            {
                halfP2timeStatus = E_OK;
            }
        }
#else
        if(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32 < (halfP2timer_u32/DCM_CFG_TASK_TIME_US))
        {
            halfP2timeStatus = E_OK;
        }
#endif
   }

    return(halfP2timeStatus);
}

FUNC(void,DCM_CODE) Dcm_TriggerTransmit(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) TxPduId,P2VAR(Type_SwcServiceCom_stInfoPdu,AUTOMATIC,DCM_INTERN_DATA) PduInfoPtr )
{

    (void)TxPduId;
    (void)PduInfoPtr;
}

#if((DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF) && (DCM_CALLAPPLICATIONONREQRX_ENABLED != DCM_CFG_OFF))
static FUNC(void,DCM_CODE) Dcm_Lok_InformApplicationAfterQueueComplete(
VAR(Dcm_DsldQueHandling_ten,AUTOMATIC) QueueHandlingTemp_en
){
   if(QueueHandlingTemp_en == DCM_QUEUE_RUNNING){
      (void)DcmAppl_CopyRxData(
            Dcm_DsldGlobal_st.dataActiveRxPduId_u8
         ,  (
                  Dcm_QueueStructure_st.dataQueueReqLength_u16
               -  Dcm_DslRxPduArray_ast[Dcm_DsldGlobal_st.dataActiveRxPduId_u8].Dcm_DslRxPduBuffer_st.SduLength
            )
      );
   }
   else{
        if(QueueHandlingTemp_en == DCM_QUEUE_COMPLETED){
            (void)DcmAppl_CopyRxData(Dcm_DsldGlobal_st.dataActiveRxPduId_u8,Dcm_DsldGlobal_st.dataRequestLength_u16);
            (void)DcmAppl_TpRxIndication(Dcm_DsldGlobal_st.dataActiveRxPduId_u8,E_OK);
        }
   }
}
#endif

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Lok_ProcessRequestInQueue(void){
   VAR(Dcm_DsldQueHandling_ten,AUTOMATIC) QueueHandlingTemp_en;
    SchM_Enter_Dcm_Global_NoNest();
    QueueHandlingTemp_en = Dcm_QueueStructure_st.Dcm_QueHandling_en;
    SchM_Exit_Dcm_Global_NoNest();
   switch(QueueHandlingTemp_en){
   case DCM_QUEUE_IDLE :
            SchM_Enter_Dcm_Global_NoNest();
            Dcm_Lok_SetDslState(DSL_STATE_IDLE);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
            SchM_Exit_Dcm_Global_NoNest();
        break;

   case DCM_QUEUE_RUNNING :

            SchM_Enter_Dcm_Global_NoNest();
            Dcm_DsldGlobal_st.dataActiveRxPduId_u8  = Dcm_QueueStructure_st.dataQueueRxPduId_u8;
            Dcm_DsldGlobal_st.dataRequestLength_u16 = Dcm_QueueStructure_st.dataQueueReqLength_u16;
            Dcm_DslRxPduArray_ast[Dcm_DsldGlobal_st.dataActiveRxPduId_u8].Dcm_DslBufferPtr_pu8 = \
                                                                            Dcm_QueueStructure_st.adrBufferPtr_pu8;

            Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_IDLE;
            Dcm_Lok_SetDslState(DSL_STATE_WAITING_FOR_RXINDICATION);
            SchM_Exit_Dcm_Global_NoNest();

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED != DCM_CFG_OFF)
            Dcm_Lok_InformApplicationAfterQueueComplete(DCM_QUEUE_RUNNING);
#endif

        break;

   case DCM_QUEUE_COMPLETED :

            SchM_Enter_Dcm_Global_NoNest();
            if(Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX)
            {
                 Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[\
                                          Dcm_QueueStructure_st.dataQueueRxPduId_u8]].channel_idx_u8].ComMChannelId);
            }

            Dcm_DsldGlobal_st.dataActiveRxPduId_u8  = Dcm_QueueStructure_st.dataQueueRxPduId_u8;
            Dcm_DsldGlobal_st.dataRequestLength_u16 = Dcm_QueueStructure_st.dataQueueReqLength_u16;
            Dcm_DsldGlobal_st.adrBufferPtr_pu8      = Dcm_QueueStructure_st.adrBufferPtr_pu8;

            Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_IDLE;

            Dcm_Lok_SetDslState(DSL_STATE_REQUEST_RECEIVED);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_START_PROTOCOL);
            SchM_Exit_Dcm_Global_NoNest();
            DCM_P2TimerStart();

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED != DCM_CFG_OFF)
            Dcm_Lok_InformApplicationAfterQueueComplete(DCM_QUEUE_COMPLETED);
#endif
        break;

    default :

        break;
   }
}
#endif

FUNC(void,DCM_CODE) Dcm_SetNegResponse ( P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) ErrorCode)
{

#if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF))
   P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA) responseBuf_pu8 = NULL_PTR;
#endif

   if((pMsgContext->msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE) || \
          (Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED))
   {
        if(pMsgContext->dcmRxPduId == Dcm_DsldGlobal_st.dataActiveRxPduId_u8)
        {

            SchM_Enter_Dcm_Global_NoNest();
            if(Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)
            {
                Dcm_DsldGlobal_st.stResponseType_en = DCM_DSLD_NEG_RESPONSE;

                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0]= DCM_NEGRESPONSE_INDICATOR;
                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[1]= Dcm_DsldGlobal_st.dataSid_u8;
                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2]= ErrorCode;
            }
            SchM_Exit_Dcm_Global_NoNest();
        }
   }
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
   else if(pMsgContext->msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
   {

        if(Dcm_Roe2ResponseType_en == DCM_DSLD_POS_RESPONSE)
        {

            Dcm_Roe2ResponseType_en = DCM_DSLD_NEG_RESPONSE;
            responseBuf_pu8 = Dcm_DsldRoe2_pcst->txbuffer_ptr;

            responseBuf_pu8[0] = DCM_NEGRESPONSE_INDICATOR;
            responseBuf_pu8[1] = pMsgContext->idContext;
            responseBuf_pu8[2] = ErrorCode;
        }
   }
#endif
   else{
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
        if(pMsgContext->msgAddInfo.sourceofRequest == DCM_RDPI_SOURCE)
        {

            if(Dcm_Rdpi2ResponseType_en == DCM_DSLD_POS_RESPONSE)
            {

                Dcm_Rdpi2ResponseType_en = DCM_DSLD_NEG_RESPONSE;
            }
        }
#endif
   }
}

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

static FUNC(boolean,DCM_CODE) Dcm_Lok_UpdateTxPduIdOnRoeEvent(void){
   VAR(boolean,AUTOMATIC) retVal_b        = TRUE;
   VAR(uint8,AUTOMATIC) connectionId_u8   = 0u;

   connectionId_u8 = Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8];

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   if(FALSE == Dcm_Lok_isProtocolPreemptionInitiated())
   {
        Dcm_DsldGlobal_st.dataActiveTxPduId_u8 = Dcm_DsldConnTable_pcst[connectionId_u8].txpduid_num_u8;
   }
   else{
        retVal_b = FALSE;
   }
#else
    Dcm_DsldGlobal_st.dataActiveTxPduId_u8 = Dcm_DsldConnTable_pcst[connectionId_u8].txpduid_num_u8;
#endif

    return retVal_b;
}
#endif

FUNC(void,DCM_CODE) Dcm_Lok_SendResponse(P2CONST(Type_SwcServiceCom_stInfoPdu,AUTOMATIC,DCM_INTERN_DATA) adrPduStrucutre_pcst)
{
   VAR(boolean,AUTOMATIC) Result_b = TRUE;

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
   if(Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED)
   {
        Result_b = Dcm_Lok_UpdateTxPduIdOnRoeEvent();
   }
   if(FALSE != Result_b)
#endif
   {
        Result_b = FALSE;
        if( DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8) )
        {
            if(E_NOT_OK != PduR_DcmTransmit(Dcm_DsldGlobal_st.dataActiveTxPduId_u8, adrPduStrucutre_pcst))
            {
                Result_b = TRUE;
            }
        }
   }

   if(FALSE == Result_b)
   {
        if(Dcm_Lok_GetDslNextState() != DSL_STATE_IDLE)
        {

            Dcm_Lok_SetDslState(DSL_STATE_REQUEST_RECEIVED);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_P2MAX_TIMEMONITORING);

            if(FALSE != Dcm_Lok_isForcePendingResponse())
            {
                Dcm_DslTransmit_st.isForceResponsePendRequested_b = FALSE;

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
                Dcm_Lok_ConfirmationRespPendForBootloader(DCM_RES_NEG_NOT_OK);
#endif
                (void)Dcm_ConfirmationRespPend(DCM_RES_NEG_NOT_OK);
            }
        }
        else{
            Dcm_DsldGlobal_st.dataResult_u8 = E_NOT_OK;
            Dcm_isGeneralRejectSent_b       = FALSE;
            Dcm_Lok_DsdConfirmation();

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
            Dcm_Lok_ProcessRequestInQueue();
#else
            Dcm_Lok_SetDslState(DSL_STATE_IDLE);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
#endif
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_TransmitNormalResponse(void){
   VAR(boolean,AUTOMATIC) SendResponse_b = FALSE;

   if(Dcm_DslTransmit_st.TxResponseLength_u32 == 0u)
   {

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
        Dcm_Lok_SetNewSession();
#endif

        Dcm_DsldGlobal_st.dataResult_u8 = E_OK;
        Dcm_Lok_DsdConfirmation();

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
        Dcm_Lok_ProcessRequestInQueue();
#else
        Dcm_Lok_SetDslState(DSL_STATE_IDLE);
        Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        Dcm_Lok_SetDslPreemptionState(DSL_STATE_IDLE);
#endif
#endif
   }
   else{
        SchM_Enter_Dcm_Global_NoNest();
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        if(FALSE == Dcm_Lok_isProtocolPreemptionInitiated())
#endif
        {
            if(FALSE == Dcm_Lok_isDcmWaitingForTxConfirmation())
            {

                Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DslTransmit_st.TxBuffer_tpu8;
                Dcm_DsldPduInfo_st.SduLength = (Type_SwcServiceCom_tLengthPdu) Dcm_DslTransmit_st.TxResponseLength_u32;

                Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0x0u;

                if(Dcm_Lok_GetDslState() != DSL_STATE_ROETYPE1_RECEIVED)
                {
                    Dcm_Lok_SetDslState(DSL_STATE_WAITING_FOR_TXCONFIRMATION);
                    Dcm_Lok_SetDslNextState(DSL_STATE_IDLE);
                    Dcm_Lok_SetDslNextSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
                }

                SendResponse_b = TRUE;
            }
            else{
                if(Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_TXCONFIRMATION)
                {
                    Dcm_Lok_SetDslNextState(DSL_STATE_RESPONSE_TRANSMISSION);
                    Dcm_Lok_SetDslNextSubState(DSL_SUBSTATE_SEND_FINAL_RESPONSE);
                }
            }
        }
        SchM_Exit_Dcm_Global_NoNest();

        if(SendResponse_b != FALSE)
        {
            Dcm_Lok_SendResponse(&Dcm_DsldPduInfo_st);
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_TransmitPendingReponse(void){
   if((Dcm_Lok_GetDslState() == DSL_STATE_REQUEST_RECEIVED) &&\
            (Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_P2MAX_TIMEMONITORING))
   {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        if(FALSE == Dcm_Lok_isProtocolPreemptionInitiated())
#endif
        {

            SchM_Enter_Dcm_Global_NoNest();

            Dcm_DslWaitPendBuffer_au8[0] = DCM_NEGRESPONSE_INDICATOR;
            Dcm_DslWaitPendBuffer_au8[1] = Dcm_DsldGlobal_st.dataSid_u8;
            Dcm_DslWaitPendBuffer_au8[2] = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING ;

            Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DslWaitPendBuffer_au8;
            Dcm_DsldPduInfo_st.SduLength  = DCM_NEGATIVE_RESPONSE_LENGTH;

            if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 < DCM_MAXNUMRESPONSEPENDING)
            {

                Dcm_DsldGlobal_st.cntrWaitpendCounter_u8++;
            }
            Dcm_Lok_SetDslState(DSL_STATE_WAITING_FOR_TXCONFIRMATION);
            Dcm_Lok_SetDslNextState(DSL_STATE_REQUEST_RECEIVED);
            Dcm_Lok_SetDslNextSubState(DSL_SUBSTATE_P2MAX_TIMEMONITORING);

            SchM_Exit_Dcm_Global_NoNest();

            Dcm_Lok_SendResponse(&Dcm_DsldPduInfo_st);
        }
   }
}

FUNC(void,DCM_CODE) Dcm_Lok_TriggerTransmit(void){
   if(FALSE != Dcm_Lok_isForcePendingResponse())
   {

        if(E_OK == Dcm_Lok_CheckP2StarTimer())
        {
            if(FALSE != Dcm_Lok_CheckWaitPendCounterOverflow())
            {
                Dcm_Lok_TransmitPendingReponse();
            }
            else{
                Dcm_Lok_SetDslState(DSL_STATE_RESPONSE_TRANSMISSION);
                Dcm_Lok_SetDslSubState(DSL_SUBSTATE_SEND_GENERAL_REJECT);
                Dcm_DslTransmit_st.isForceResponsePendRequested_b = FALSE;

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
                Dcm_Lok_ConfirmationRespPendForBootloader(DCM_RES_NEG_NOT_OK);
#endif
                (void)Dcm_ConfirmationRespPend(DCM_RES_NEG_NOT_OK);
            }
        }
        else{
            Dcm_DslTransmit_st.isForceResponsePendRequested_b = FALSE;

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
            Dcm_Lok_ConfirmationRespPendForBootloader(DCM_RES_NEG_OK);
#endif
            (void)Dcm_ConfirmationRespPend(DCM_RES_NEG_OK);
        }
   }
   else{
        Dcm_Lok_TransmitNormalResponse();
   }
}

#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)

static FUNC(void,DCM_CODE)Dcm_Lok_TransmitRdpiType2Response(void){
   VAR(Std_ReturnType,AUTOMATIC) trasnsmitStatus = E_OK;
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) rdpiTxPduId = 0u;
   VAR(uint8,AUTOMATIC) idxTxPduId_u8   = 0u;

   if(Dcm_Rdpi2ResponseType_en == DCM_DSLD_POS_RESPONSE)
   {
        if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8))
        {

            Dcm_GetRdpiType2Index(&idxTxPduId_u8);

            rdpiTxPduId = Dcm_Dsld_RDPIType2tx_table[idxTxPduId_u8].txpduid_num_u8;

            Dcm_DsldRdpi2pduinfo_ast[idxTxPduId_u8].SduDataPtr = &Dcm_Dsld_RDPIType2tx_table[idxTxPduId_u8].txbuffer_ptr[0];
            Dcm_DsldRdpi2pduinfo_ast[idxTxPduId_u8].SduLength = (Type_SwcServiceCom_tLengthPdu) (Dcm_Rdpi2MesContext_st.resDataLen);

            Dcm_Dsld_RDPIType2tx_table[idxTxPduId_u8].isTxPduId_Busy = TRUE;
            Dcm_Dsld_RDPIType2tx_table[idxTxPduId_u8].cntFreeTxPduRdpi2Cntr_u8 = DCM_CFG_RDPITYPE2FREETXPDUCOUNTER;

            trasnsmitStatus = PduR_DcmTransmit(rdpiTxPduId,&Dcm_DsldRdpi2pduinfo_ast[idxTxPduId_u8]);
        }
        else{
            trasnsmitStatus = E_NOT_OK;
            DCM_DET_ERROR(DCM_PROCESSINGDONE_ID , DCM_E_FULLCOMM_DISABLED )
        }
   }

    DcmAppl_DcmConfirmationRDPI(DCM_RDPI_SID,Dcm_Rdpi2MesContext_st.dcmRxPduId
   ,     (trasnsmitStatus == E_OK) ? DCM_RES_POS_OK : DCM_RES_POS_NOT_OK) ;
}
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

static FUNC(void,DCM_CODE)Dcm_Lok_TransmitRoeType2Response(void){
   VAR(boolean,AUTOMATIC) TransmitSuccess_b = TRUE;

    Dcm_DsdRoe2State_en = DSD_WAITFORTXCONF;

   if(Dcm_Roe2ResponseType_en == DCM_DSLD_POS_RESPONSE)
   {

        if(FALSE == Dcm_Roe2MesContext_st.msgAddInfo.suppressPosResponse)
        {
            Dcm_DsldRoe2_pcst->txbuffer_ptr[2] = Dcm_Roe2MesContext_st.idContext|DCM_SERVICEID_ADDEND;
            Dcm_DsldRoe2PduInfo_st.SduLength   = (Type_SwcServiceCom_tLengthPdu) Dcm_Roe2MesContext_st.resDataLen + 1u ;
            Dcm_DsldRoe2PduInfo_st.SduDataPtr  = &Dcm_DsldRoe2_pcst->txbuffer_ptr[2];
        }
        else{
            Dcm_DsldRoe2PduInfo_st.SduLength = 0x00u;
        }
   }
   else{

        if((Dcm_Roe2MesContext_st.dcmRxPduId >= DCM_INDEX_FUNC_RX_PDUID) && \
                (DCM_CFG_SUPPRESS_NRC(Dcm_DsldRoe2_pcst->txbuffer_ptr[2])))
        {
            Dcm_DsldRoe2PduInfo_st.SduLength = 0x00;
        }
        else{
            Dcm_DsldRoe2PduInfo_st.SduLength = (Type_SwcServiceCom_tLengthPdu) ( Dcm_Roe2MesContext_st.resDataLen + 3u ) ;
            Dcm_DsldRoe2PduInfo_st.SduDataPtr = &Dcm_DsldRoe2_pcst->txbuffer_ptr[0];
        }
   }

   if(0x00u == Dcm_DsldRoe2PduInfo_st.SduLength)
   {

        Dcm_Roe2TxResult_u8 = E_OK;
        Dcm_DsdRoe2State_en = DSD_SENDTXCONF_APPL;
   }
   else{
        if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_Roe2MesContext_st.dcmRxPduId]].channel_idx_u8))
        {
            if(E_NOT_OK == PduR_DcmTransmit(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_Roe2MesContext_st.dcmRxPduId]].\
                    roetype2_txpdu_u8,&Dcm_DsldRoe2PduInfo_st))
            {
                TransmitSuccess_b  = FALSE;
                DCM_DET_ERROR(DCM_PROCESSINGDONE_ID , DCM_E_RET_E_NOT_OK ) //Need to check
            }
        }
        else{
            TransmitSuccess_b  = FALSE;
            DCM_DET_ERROR(DCM_PROCESSINGDONE_ID , DCM_E_FULLCOMM_DISABLED )
        }

        if(FALSE == TransmitSuccess_b)
        {

            Dcm_Roe2TxResult_u8 = E_NOT_OK;
            Dcm_DsdRoe2State_en = DSD_SENDTXCONF_APPL;
        }
   }
}
#endif

static FUNC(void,DCM_CODE)Dcm_Lok_TransmitCurrentResponse(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{
   VAR(uint8,AUTOMATIC) NrcValue_u8     = 0u;
   VAR(uint32,AUTOMATIC) bufferSize_u32 = 0u;
   VAR(Dcm_DsdStatesType_ten,AUTOMATIC) DsdState_en = Dcm_Lok_GetDsdState();

   if((DsdState_en == DSD_CALL_SERVICE)||(FALSE != Dcm_DsldGlobal_st.dataResponseByDsd_b))
   {
        Dcm_Lok_SetDsdState(DSD_WAITFORTXCONF);
   }

   if(Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)
   {
        if(FALSE == Dcm_DsldGlobal_st.dataResponseByDsd_b)
        {

            bufferSize_u32 = pMsgContext->resMaxDataLen - pMsgContext->resDataLen;

            DcmAppl_DcmModifyResponse(Dcm_DsldGlobal_st.dataSid_u8, NrcValue_u8,\
                    &(pMsgContext->resData[pMsgContext->resDataLen]), &bufferSize_u32);
        }

        if(FALSE != Dcm_Lok_isPositiveResponseSupressed(pMsgContext))
        {
            Dcm_DslTransmit_st.TxBuffer_tpu8 = NULL_PTR;
            Dcm_DslTransmit_st.TxResponseLength_u32 = 0x00u;
        }
        else{
            Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2] = Dcm_DsldGlobal_st.dataSid_u8 | DCM_SERVICEID_ADDEND;
            Dcm_DslTransmit_st.TxBuffer_tpu8 = &Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2] ;

            Dcm_DslTransmit_st.TxResponseLength_u32 = pMsgContext->resDataLen + 1u + bufferSize_u32;
        }
   }
   else{
        if(FALSE == Dcm_DsldGlobal_st.dataResponseByDsd_b)
        {

            bufferSize_u32 = pMsgContext->resMaxDataLen - pMsgContext->resDataLen;
            DcmAppl_DcmModifyResponse(Dcm_DsldGlobal_st.dataSid_u8, Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2], \
                    &(Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2]), &bufferSize_u32);
        }

        if(FALSE != Dcm_Lok_isNegativeResponseSupressed(pMsgContext,Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2]))
        {
            Dcm_DslTransmit_st.TxBuffer_tpu8 = NULL_PTR ;
            Dcm_DslTransmit_st.TxResponseLength_u32 = 0x00u;
        }
        else{
            Dcm_DslTransmit_st.TxBuffer_tpu8 = Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8;
            Dcm_DslTransmit_st.TxResponseLength_u32 = DCM_NEGATIVE_RESPONSE_LENGTH;
        }
   }
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   if(FALSE == Dcm_Lok_isProtocolPreemptionInitiated())
#endif
   {
        if(Dcm_Lok_GetDsdState() == DSD_WAITFORTXCONF)
        {
            Dcm_Lok_TriggerTransmit();
        }
   }
}

FUNC(void,DCM_CODE)Dcm_ProcessingDone(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{
   if(((pMsgContext->msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE)         || \
                (Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED))            && \
                (pMsgContext->dcmRxPduId == Dcm_DsldGlobal_st.dataActiveRxPduId_u8))
   {
        Dcm_Lok_TransmitCurrentResponse(pMsgContext);
   }
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
   else if(pMsgContext->msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
   {
        Dcm_Lok_TransmitRoeType2Response();
   }
#endif
   else{
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
        if(pMsgContext->msgAddInfo.sourceofRequest == DCM_RDPI_SOURCE)
        {
            Dcm_Lok_TransmitRdpiType2Response();
        }
#endif
   }
}

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))

FUNC(void,DCM_CODE) Dcm_KWPConfirmationForSplitResp(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status)
{

    Dcm_Lok_ReloadS3Timer();
    Dcm_Lok_InactivateComMChannel();

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_ProcessRequestInQueue();
#else

    SchM_Enter_Dcm_Global_NoNest();
    Dcm_Lok_SetDslState(DSL_STATE_IDLE);
    Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
    SchM_Exit_Dcm_Global_NoNest();
#endif

   if(Dcm_isApplicationCalled_b == FALSE)
   {
        DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,Dcm_DsldMsgContext_st.dcmRxPduId, \
            Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16, \
            status);
   }

#if((DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS != 0) || (DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS !=0))
        Dcm_Dsd_CallRTEConfirmation(status);
#endif

    Dcm_Lok_SetDsdState(DSD_IDLE);
}
#endif

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessConfirmationForKWPResponse(void){
   VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC) ResponseLength = 0u;

    DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,Dcm_DsldMsgContext_st.dcmRxPduId
   ,     Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16
   ,     DCM_RES_POS_OK);

    DcmAppl_DcmGetRemainingResponseLength(Dcm_DsldMsgContext_st.idContext,&ResponseLength);

   if(0u != ResponseLength)
   {

        if(Dcm_isFirstReponseSent_b == FALSE)
        {

            Dcm_isFirstReponseSent_b = TRUE;
        }

        DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,(DCM_CFG_SPLITRESPONSETIMEFORKWP)
   ,     Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)

        Dcm_Lok_SetDslState(DSL_STATE_REQUEST_RECEIVED);
        Dcm_Lok_SetDslSubState(DSL_SUBSTATE_P2MAX_TIMEMONITORING);
        Dcm_Lok_SetDsdState(DSD_CALL_SERVICE);
   }
   else{

        Dcm_isApplicationCalled_b = TRUE;

        Dcm_KWPConfirmationForSplitResp(DCM_RES_POS_OK);

        Dcm_isFirstReponseSent_b = FALSE;
        Dcm_isApplicationCalled_b = FALSE;
   }
}
#endif

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessConfirmationForCurrentResponse (VAR(Std_ReturnType,AUTOMATIC) Result)
{
   Dcm_DsldGlobal_st.dataResult_u8 = Result;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
   Dcm_Lok_SetNewSession();
#endif

   Dcm_Lok_DsdConfirmation();

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
   Dcm_Lok_ProcessRequestInQueue();
#else
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
       if(FALSE == Dcm_Lok_isHighPriorityRequestReceiving())
       {
           Dcm_Lok_SetDslState(Dcm_Lok_GetDslNextState());
           Dcm_Lok_SetDslSubState(Dcm_Lok_GetDslNextSubState());
       }
#else
       Dcm_Lok_SetDslState(Dcm_Lok_GetDslNextState());
       Dcm_Lok_SetDslSubState(Dcm_Lok_GetDslNextSubState());
#endif
#endif
}

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessConfiramationForPendingResponse (VAR(Std_ReturnType,AUTOMATIC) Result)
{
   VAR(Dcm_ConfirmationStatusType,AUTOMATIC) confirmationStatus = DCM_RES_NEG_NOT_OK;

   if(E_OK == Result)
   {

       DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, \
            (Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 - \
            Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2StarTmrAdjust),\
            Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)

        confirmationStatus = DCM_RES_NEG_OK;
   }

   if(FALSE != Dcm_Lok_isForcePendingResponse())
   {
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
       Dcm_Lok_ConfirmationRespPendForBootloader(confirmationStatus);
#endif

       (void)Dcm_ConfirmationRespPend(confirmationStatus);

       Dcm_DslTransmit_st.isForceResponsePendRequested_b = FALSE;
   }

   Dcm_Lok_SetDslState(Dcm_Lok_GetDslNextState());
   Dcm_Lok_SetDslSubState(Dcm_Lok_GetDslNextSubState());
}

static FUNC(void,DCM_CODE)Dcm_Lok_ProcessTxConfirmation(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) TxPduId
   ,     VAR(Std_ReturnType,AUTOMATIC) result)
{
   VAR(uint8,AUTOMATIC) idxRxPduId_u8;

   if(FALSE != Dcm_Lok_isConfirmationOnActiveConnection(TxPduId))
   {
       if(FALSE != Dcm_Lok_isConfirmationForPendingResponse())
       {
           Dcm_Lok_ProcessConfiramationForPendingResponse(result);
       }
       else{
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
           if(FALSE != Dcm_Lok_isConfirmationForKWPResponse(result))
           {
               Dcm_Lok_ProcessConfirmationForKWPResponse();
           }
           else
#endif
           {
               Dcm_Lok_ProcessConfirmationForCurrentResponse(result);
           }
       }
   }
#if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF))
   else{
        if(FALSE != Dcm_Lok_isConfirmationForRoeType2Response(TxPduId))
        {
            Dcm_Roe2TxResult_u8 = result;
            Dcm_DsdRoe2State_en = DSD_SENDTXCONF_APPL;
        }
   }
#endif

   for(idxRxPduId_u8 = 0; idxRxPduId_u8 < DCM_CFG_NUM_RX_PDUID ; idxRxPduId_u8++)
   {
       if(FALSE != Dcm_Lok_isConfirmationReceivedForNrc21Response(TxPduId,idxRxPduId_u8))
       {
           Dcm_DslRxPduArray_ast[idxRxPduId_u8].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
           break;
       }
   }
}

FUNC(void,DCM_CODE) Dcm_TpTxConfirmation (VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) id,VAR(Std_ReturnType,AUTOMATIC) result)
{
   if( id >= DCM_NUM_TX_PDUID )
   {
         DCM_DET_ERROR(DCM_TPTXCONFIRMATION_ID ,DCM_E_DCMTXPDUID_RANGE_EXCEED)
   }
   else{
        if(FALSE != Dcm_isCancelTransmitInvoked_b)
        {
            Dcm_isCancelTransmitInvoked_b = FALSE;
        }
        else{
            Dcm_Lok_ProcessTxConfirmation(id,result);
        }
   }
}

FUNC(void,DCM_CODE) Dcm_TxConfirmation (VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) DcmTxPduId)
{
   VAR(uint8,AUTOMATIC) idxTxPduid_u8 = 0u;

   if( DcmTxPduId >= DCM_NUM_TX_PDUID )
   {
        DCM_DET_ERROR(DCM_TXCONFIRMATION_ID ,DCM_E_DCMRXPDUID_RANGE_EXCEED)
   }
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
   else{
        for(idxTxPduid_u8 = 0; idxTxPduid_u8 < DCM_CFG_NUM_RDPITYPE2_TXPDU; idxTxPduid_u8++)
        {
            if(Dcm_Dsld_RDPIType2tx_table[idxTxPduid_u8].txpduid_num_u8 == CfgSwcServiceDcm_stDsld.ptr_txtable_pca[DcmTxPduId])
            {
                Dcm_Dsld_RDPIType2tx_table[idxTxPduid_u8].isTxPduId_Busy = FALSE;
                break;
            }
        }
   }
#else
    (void)idxTxPduid_u8;
#endif
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
