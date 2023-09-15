

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmCore_Main_Inf.hpp"
#include "Rte_Dcm.hpp"

#define DCM_MAX_LIMIT_WAITPEND        (0xFFu)

#define Dcm_Lok_ProcessDslStateMachine(stDslState_en)  Dcm_ProcessDslState[stDslState_en]()
typedef void (*Dcm_DslStateType)(void);

static void Dcm_Lok_DslState_Idle(void);
static void Dcm_Lok_DslState_WaitingForRxIndication(void);
static void Dcm_Lok_DslState_RequestReceived(void);
static void Dcm_Lok_DslState_ResponseTransmission(void);
static void Dcm_Lok_DslState_WaitingForTxConfirmation(void);
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_DslState_ProtocolPreemption(void);
#endif
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_DslState_PagedBufferTransmission(void);
#endif

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static const Dcm_DslStateType  Dcm_ProcessDslState[DCM_NUMBER_OF_DSL_STATES] =
{
    Dcm_Lok_DslState_Idle
   ,   Dcm_Lok_DslState_WaitingForRxIndication
   ,   Dcm_Lok_DslState_RequestReceived
   ,   Dcm_Lok_DslState_ResponseTransmission
   ,   Dcm_Lok_DslState_WaitingForTxConfirmation,
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_DslState_ProtocolPreemption,
#endif
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_DslState_PagedBufferTransmission,
#endif
    Dcm_Lok_DslState_Idle //For Roe Type1
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
uint8 Dcm_DslWaitPendBuffer_au8[8];
uint8 Dcm_DslState_u8;
uint8 Dcm_DslSubState_u8;
uint8 Dcm_DslNextState_u8;
uint8 Dcm_DslNextSubState_u8;
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
uint8 Dcm_DslPreemptionState_u8;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Dcm_Dsld_ServiceType * Dcm_DsldSrvTable_pcst;
Dcm_DsldTimingsType_tst Dcm_DsldTimer_st;
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
Dcm_QueueStructure_tst Dcm_QueueStructure_st;
#endif
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
static Std_ReturnType stCancelTx_u8;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_Dsld_KwpTimerServerType Dcm_DsldKwpReqTiming_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_isGeneralRejectSent_b;
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
static boolean flgRoeOn_b;
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
       static boolean flgPersistRoe_b;
#endif
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
StatusType Dcm_P2OrS3TimerStatus_uchr;
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
StatusType Dcm_OBDP2OrS3TimerStatus_uchr;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)

Dcm_MsgItemType* Dcm_Lok_ProvideFreeBuffer(
        uint8 idxProtocolIndex_u8,boolean isQueuedReq_b)
{
   uint8 * RxBuffer_pu8 = NULL_PTR;

   if(isQueuedReq_b == TRUE)
   {
        if(Dcm_QueueStructure_st.idxBufferIndex_u8 == 1)
        {
            Dcm_QueueStructure_st.idxBufferIndex_u8 = 2u;
        }
        else{
            Dcm_QueueStructure_st.idxBufferIndex_u8 = 1u;
        }
   }

   if(Dcm_QueueStructure_st.idxBufferIndex_u8 == 1u)
   {
        RxBuffer_pu8 = Dcm_DsldProtocol_pcst[idxProtocolIndex_u8].rx_mainBuffer_pa;
   }
   else{
        RxBuffer_pu8 = Dcm_DsldProtocol_pcst[idxProtocolIndex_u8].rx_reserveBuffer_pa;
   }

    return (RxBuffer_pu8);
}
#endif

Dcm_MsgItemType* Dcm_GetActiveBuffer(void){

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    return Dcm_DsldGlobal_st.adrBufferPtr_pu8;
#else
    return Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rx_mainBuffer_pa;
#endif
}

static void Dcm_Lok_SetIntermediateResponse(uint8 dataNegativeResponse_u8)
{

    Dcm_Lok_SetDslState((DSL_STATE_WAITING_FOR_TXCONFIRMATION));

    Dcm_DslWaitPendBuffer_au8[0] = DCM_NEGRESPONSE_INDICATOR;
    Dcm_DslWaitPendBuffer_au8[1] = Dcm_DsldGlobal_st.dataSid_u8;
    Dcm_DslWaitPendBuffer_au8[2] = dataNegativeResponse_u8 ;

    Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DslWaitPendBuffer_au8;
    Dcm_DsldPduInfo_st.SduLength = DCM_NEGATIVE_RESPONSE_LENGTH;
}

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_Check_ProtocolPreemptionStatus(void){
    SchM_Enter_Dcm_Global_NoNest();
   if(Dcm_Lok_GetDslPreemptionState() == DSL_SUBSTATE_STOP_PROTOCOL)
   {
        SchM_Exit_Dcm_Global_NoNest();

        stCancelTx_u8 = Dcm_Lok_CancelTransmit();

        SchM_Enter_Dcm_Global_NoNest();
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        if(Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED)
        {
            flgRoeOn_b = TRUE;
        }
#else
        (void)flgRoeOn_b;
#endif

        Dcm_Lok_SetDslState((DSL_STATE_PROTOCOL_PREEMPTION));
        Dcm_Lok_SetDslSubState((DSL_SUBSTATE_STOP_PROTOCOL));
   }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
   else{
        if(Dcm_Lok_GetDslPreemptionState() == DSL_SUBSTATE_STOP_ROE)
        {
            if(Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED)
            {
                flgPersistRoe_b = TRUE;
                SchM_Exit_Dcm_Global_NoNest();

                stCancelTx_u8 = Dcm_Lok_CancelTransmit();

                SchM_Enter_Dcm_Global_NoNest();
            }

            Dcm_Lok_SetDslState((DSL_STATE_PROTOCOL_PREEMPTION));
            Dcm_Lok_SetDslSubState((DSL_SUBSTATE_STOP_ROE));
        }
   }
#endif
    SchM_Exit_Dcm_Global_NoNest();
}
#endif

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_SetDefaultTimerValues(void){
   uint8 idxKwpTiming_u8 = 0u;

    SchM_Enter_Dcm_DsldTimer_NoNest();
   if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
   {

        Dcm_DsldSessionTable_pcu8 = Dcm_Dsld_KWPsupported_sessions_acu8;
        idxKwpTiming_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_idx_u8;
        Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P2_max_u32;
        Dcm_DsldTimer_st.dataTimeoutP3max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P3_max_u32;
        Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;
   }
   else{

        Dcm_DsldSessionTable_pcu8 = CfgSwcServiceDcm_stDsld.session_lookup_table_pcau8;
        Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
        Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
   }
    SchM_Exit_Dcm_DsldTimer_NoNest();
}
#endif

static Std_ReturnType Dcm_Lok_StartProtocol(void){
    Std_ReturnType startProtocolStatus = E_NOT_OK;

   if((Dcm_CurProtocol_u8 != DCM_NO_ACTIVE_PROTOCOL) && (!Dcm_isStopProtocolInvoked_b))
   {
        Dcm_StopProtocol(Dcm_CurProtocol_u8);
   }

   startProtocolStatus = Dcm_StartProtocol(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8);

   if(E_OK == startProtocolStatus)
   {
        Dcm_DsldGlobal_st.flgCommActive_b = TRUE;
        Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].
                sid_tableid_u8;
        Dcm_DsldSrvTable_pcst = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
        Dcm_Dsd_ServiceIni(Dcm_DsldGlobal_st.datActiveSrvtable_u8);

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
        Dcm_Lok_SetDefaultTimerValues();
#endif

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (void)SchM_Switch_SwcServiceDcm_tDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif
        (void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#endif

        Dcm_Lok_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);

        Dcm_CurProtocol_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8;
   }

    return startProtocolStatus;
}

static void Dcm_Lok_SendNrcforStartProtocolFailure(void){
    Dcm_NegativeResponseCodeType dataNrc_u8 = 0x22;
   const Dcm_MsgItemType * adrRxBuffer_pu8 = NULL_PTR;

    Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = (&(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8]))->tx_buffer_pa;
    Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    adrRxBuffer_pu8 = Dcm_GetActiveBuffer();
#else
    adrRxBuffer_pu8 = (&(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8]))->rx_mainBuffer_pa;
#endif

    Dcm_DsldGlobal_st.dataSid_u8     = adrRxBuffer_pu8[0];
    Dcm_DsldMsgContext_st.idContext  = Dcm_DsldGlobal_st.dataSid_u8;

    Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;
    Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_UDS_TESTER_SOURCE;
    Dcm_DsldMsgContext_st.resDataLen = 0u;

   if(Dcm_DsldGlobal_st.dataActiveRxPduId_u8 >= DCM_INDEX_FUNC_RX_PDUID)
   {
        Dcm_DsldMsgContext_st.msgAddInfo.reqType = DCM_PRV_FUNCTIONAL_REQUEST;
   }
   else{
        Dcm_DsldMsgContext_st.msgAddInfo.reqType = DCM_PRV_PHYSICAL_REQUEST;
   }

    Dcm_DsldGlobal_st.stResponseType_en      = DCM_DSLD_POS_RESPONSE;

    Dcm_Lok_SetDslState((DSL_STATE_REQUEST_RECEIVED));
    Dcm_Lok_SetDslSubState((DSL_SUBSTATE_P2MAX_TIMEMONITORING));
    Dcm_DsldGlobal_st.dataActiveTxPduId_u8   = Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].txpduid_num_u8;
    Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0;
    Dcm_DslTransmit_st.isForceResponsePendRequested_b    = FALSE;

    Dcm_SetNegResponse(&Dcm_DsldMsgContext_st ,dataNrc_u8);
    Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
}

static void Dcm_Lok_UpdateStatesForStartProtocol(void){

   if((DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8)) && \
            (FALSE == (DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32))))
   {

        Dcm_isGeneralRejectSent_b = FALSE;

        Dcm_Lok_SetDslState((DSL_STATE_REQUEST_RECEIVED));
        Dcm_Lok_SetDslSubState((DSL_SUBSTATE_P2MAX_TIMEMONITORING));

        Dcm_Lok_SetDslNextState((DSL_STATE_REQUEST_RECEIVED));
        Dcm_Lok_SetDslNextSubState((DSL_SUBSTATE_P2MAX_TIMEMONITORING));

        Dcm_Lok_SetDsdState(DSD_VERIFY_DIAGNOSTIC_DATA);
        Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0x0u;

        Dcm_DsldGlobal_st.dataActiveTxPduId_u8   = Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].txpduid_num_u8;

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
        Dcm_DsldGlobal_st.dataSid_u8 = *(Dcm_GetActiveBuffer());
#else
        Dcm_DsldGlobal_st.dataSid_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rx_mainBuffer_pa[0];
#endif
   }

   else if((Dcm_DsldGlobal_st.idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX) \
            || (FALSE != DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32)))
   {

        DcmAppl_DcmComModeError(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);

        Dcm_Lok_SetDslState((DSL_STATE_IDLE));
        Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
        Dcm_Lok_SetDslNextState((DSL_STATE_IDLE));
        Dcm_Lok_SetDslNextSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
        Dcm_Lok_SetDsdState(DSD_IDLE);
   }

   else{
        DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
   }
}

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_StopLowPriorityProtocol(void){
   uint8 NrcValue_u8 = 0u;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF))
   if(FALSE != Dcm_Lok_isProtocolStarted())
   {
        Dcm_ControlDtcSettingExit();
   }
#endif

   if((Dcm_Lok_GetDsdState() != DSD_IDLE) && \
            (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp != NULL_PTR))
   {
        (void)(*Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp)\
                (DCM_CANCEL,&Dcm_DsldMsgContext_st,&NrcValue_u8);

        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        Dcm_ExtSrvOpStatus_u8 = DCM_INITIAL;
   }

   if(Dcm_Lok_GetDsdState() == DSD_CALL_SERVICE)
   {
        Dcm_isStopProtocolInvoked_b = TRUE;
        Dcm_StopProtocol(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8);
   }
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
   else{
        if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
        {
            Dcm_isStopProtocolInvoked_b = TRUE;

            Dcm_StopProtocol(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8);

            Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = FALSE;
            Dcm_adrUpdatePage_pfct = NULL_PTR;
        }
   }
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

   if(FALSE != flgRoeOn_b)
   {
        if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
        {

            DcmAppl_DcmConfirmation(Dcm_DsldGlobal_st.dataSid_u8
   ,                   Dcm_DsldMsgContext_st.dcmRxPduId
   ,                   Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_DsldMsgContext_st.dcmRxPduId].testsrcaddr_u16
   ,                   DCM_RES_POS_NOT_OK);
        }
   }
#endif
}
#endif

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_DslSubState_StopProtocol(void){

   uint8 idxConnection_u8 = Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8];
   uint8 idxProtocol_u8   = Dcm_DsldConnTable_pcst[idxConnection_u8].protocol_num_u8;

    Dcm_Lok_StopLowPriorityProtocol();

    Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = idxProtocol_u8;
    Dcm_DsldGlobal_st.nrActiveConn_u8       = idxConnection_u8;

   if(Dcm_DsldGlobal_st.idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX)
   {

        Dcm_Lok_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
   }

    Dcm_DsldGlobal_st.flgCommActive_b = FALSE;
    Dcm_DsldGlobal_st.dataRequestLength_u16  = Dcm_DsldGlobal_st.dataNewdataRequestLength_u16;

    Dcm_Lok_SetDslState((DSL_STATE_REQUEST_RECEIVED));
    Dcm_Lok_SetDslSubState((DSL_SUBSTATE_START_PROTOCOL));
    Dcm_Lok_SetDsdState(DSD_IDLE);

    Dcm_Lok_ResetDsdSubStateMachine();
    Dcm_Lok_SetDslPreemptionState((DSL_STATE_IDLE));

   if((stCancelTx_u8 == E_OK) && \
            (Dcm_DsldGlobal_st.dataOldtxPduId_u8 == Dcm_DsldConnTable_pcst[idxConnection_u8].txpduid_num_u8))
   {

        DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
   }
}
#endif

#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF))

static void Dcm_Lok_DslSubState_StopRoe(void){

   if(flgPersistRoe_b != FALSE)
   {

        uint8 idxConnection_u8 = Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8];
        uint8 idxProtocol_u8   = Dcm_DsldConnTable_pcst[idxConnection_u8].protocol_num_u8;

        DcmAppl_DcmConfirmation(Dcm_DsldGlobal_st.dataSid_u8
   ,               Dcm_DsldMsgContext_st.dcmRxPduId
   ,               Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_DsldMsgContext_st.dcmRxPduId].testsrcaddr_u16
   ,               DCM_RES_POS_NOT_OK);

        Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = idxProtocol_u8;
        Dcm_DsldGlobal_st.nrActiveConn_u8       = idxConnection_u8;
        Dcm_DsldGlobal_st.dataRequestLength_u16 = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;

        Dcm_Lok_SetDslState((DSL_STATE_REQUEST_RECEIVED));
        Dcm_Lok_SetDslSubState((DSL_SUBSTATE_START_PROTOCOL));
        Dcm_Lok_SetDsdState(DSD_IDLE);

        Dcm_Lok_ResetDsdSubStateMachine();
        Dcm_Lok_SetDslPreemptionState((DSL_STATE_IDLE));

        if((stCancelTx_u8 == E_OK) &&
                (Dcm_DsldGlobal_st.dataOldtxPduId_u8 == Dcm_DsldConnTable_pcst[idxConnection_u8].txpduid_num_u8))
        {

            DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
        }
   }
}
#endif

static void Dcm_Lok_DslSubState_SendFinalResponse(void){
     Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DslTransmit_st.TxBuffer_tpu8;
     Dcm_DsldPduInfo_st.SduLength = (Type_SwcServiceCom_tLengthPdu)Dcm_DslTransmit_st.TxResponseLength_u32;

     Dcm_Lok_SetDslState((DSL_STATE_WAITING_FOR_TXCONFIRMATION));

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

     if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
     {

         Dcm_Lok_SetDslState((DSL_STATE_PAGEDBUFFER_TRANSMISSION));
         Dcm_Lok_SetDslSubState((DSL_SUBSTATE_DATA_READY));
     }
#endif

     Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0x0u;

     Dcm_Lok_SetDslNextState((DSL_STATE_IDLE));
     Dcm_Lok_SetDslNextSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));

     Dcm_Lok_SendResponse(& Dcm_DsldPduInfo_st);
}

static void Dcm_Lok_DslSubState_SendGeneralReject(void){
   uint8 NrcValue_u8 = 0u;

   if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == DCM_CFG_MAX_WAITPEND)
   {
        if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp != NULL_PTR)
        {

            (void)(*Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp) \
                                (DCM_CANCEL,&Dcm_DsldMsgContext_st,&NrcValue_u8);

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
            Dcm_ExtSrvOpStatus_u8 = DCM_INITIAL;
        }
        Dcm_DsldGlobal_st.idxService_u8       = 0x00u;
        Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
        Dcm_DslTransmit_st.isForceResponsePendRequested_b = FALSE;

        Dcm_Lok_ResetDsdSubStateMachine();
        Dcm_SetNegResponse( &Dcm_DsldMsgContext_st ,DCM_E_GENERALREJECT);

        Dcm_isGeneralRejectSent_b = TRUE;
#if(DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)

        rba_DiagAdapt_Confirmation_GeneralReject(Dcm_DsldGlobal_st.dataSid_u8);
#endif
        Dcm_ProcessingDone (&Dcm_DsldMsgContext_st);
   }
}

static void Dcm_Lok_DslSubState_SendPendingResponse(void){
   uint8 currentprotocolId_u8 ;

   if(FALSE == Dcm_Lok_Check_PendingResponseForKWP())
   {

        if(TRUE == Dcm_Lok_IsVerifyDataProcessing())
        {

            Dcm_Lok_SetDslNextState((DSL_STATE_IDLE));
            Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
            Dcm_Lok_SetDslNextSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));

            currentprotocolId_u8=Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8;
            if(!((currentprotocolId_u8== DCM_OBD_ON_CAN)||(currentprotocolId_u8== DCM_OBD_ON_FLEXRAY)||
                 (currentprotocolId_u8== DCM_OBD_ON_IP)||(currentprotocolId_u8== DCM_OBD_ON_KLINE)))
            {

   		    Dcm_Lok_SetDsdState(DSD_WAITFORTXCONF);

                Dcm_Lok_SetIntermediateResponse(DCM_E_BUSYREPEATREQUEST);
                Dcm_Lok_SendResponse(& Dcm_DsldPduInfo_st);
            }
            else{

   		    Dcm_Lok_SetDsdState(DSD_IDLE);
                Dcm_Lok_SetDslState((DSL_STATE_IDLE));
            }
        }
        else{

#if(DCM_CFG_MAX_WAITPEND > 0)
            if((Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 < DCM_CFG_MAX_WAITPEND) || \
                    (DCM_CFG_MAX_WAITPEND == DCM_MAX_LIMIT_WAITPEND))
            {
                Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;

                Dcm_Lok_SetIntermediateResponse(DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING);

                if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 < DCM_MAX_LIMIT_WAITPEND)
                {

                    Dcm_DsldGlobal_st.cntrWaitpendCounter_u8++;
                }
                Dcm_Lok_SendResponse(&Dcm_DsldPduInfo_st);
            }
            else{

                Dcm_Lok_DslSubState_SendGeneralReject();
            }
#else
                Dcm_Lok_DslSubState_SendGeneralReject();
#endif
        }
   }
}

static void Dcm_Lok_DslSubState_MonitorP2Max(void){
    DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)

   if(FALSE != DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32))
   {
        Dcm_Lok_DslSubState_SendPendingResponse();
   }
}

static void Dcm_Lok_DslSubState_StartProtocol(void){
   if(FALSE == Dcm_Lok_isProtocolStarted())
   {
        if(E_OK != Dcm_Lok_StartProtocol())
        {
            Dcm_Lok_SendNrcforStartProtocolFailure();
        }

        Dcm_isStopProtocolInvoked_b = FALSE;
   }

   if(FALSE != Dcm_Lok_isProtocolStarted())
   {
        Dcm_Lok_UpdateStatesForStartProtocol();
   }
}

static void Dcm_Lok_DslSubState_S3_OR_P3_Timeout(uint8 idxActiveSession_u8)
{
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
   if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
   {
        Dcm_DsldGlobal_st.flgCommActive_b  = FALSE;
        DcmAppl_P3TimeoutIndication();
   }
#endif

   if(idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX)
   {

        ComM_DCM_InactiveDiagnostic (Dcm_active_commode_e \
                [Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
   }

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)

    (void)SchM_Switch_SwcServiceDcm_tDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif

    (void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#endif

    Dcm_Lok_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
    Dcm_DsldGlobal_st.flgMonitorP3timer_b = FALSE;
}

static void Dcm_Lok_DslSubState_S3_OR_P3_TimeMoniotor(void){

   if(FALSE == (DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32)))
   {
        DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,\
                Dcm_P2OrS3TimerStatus_uchr)
   }
   else{
        Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEOUT));
   }
}

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_DslState_PagedBufferTransmission(void){
   uint16 pageLen_u16 = 0u;

   if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_WAIT_FOR_DATA)
   {
        if(Dcm_Lok_GetDsdState() == DSD_WAITFORTXCONF)
        {

            DCM_TimerStart(Dcm_DsldGlobal_st.dataPagedBufferTimeout_u32, DCM_PAGEDBUFFER_TIMEOUT
   ,                   Dcm_PagedBufferStartTick_u32,Dcm_PagedBufferTimerStatus_uchr)

            Dcm_Lok_SetDsdState(DSD_CALL_SERVICE);

            if(Dcm_adrUpdatePage_pfct != NULL_PTR)
            {
                pageLen_u16 = (uint16)(Dcm_DsldMsgContext_st.resMaxDataLen+1uL);

                (*Dcm_adrUpdatePage_pfct)(&Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].tx_buffer_pa[2]
   ,                       pageLen_u16);
            }
        }
   }
   else{
        if((Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_DATA_READY) || \
                (Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_WAIT_PAGE_TXCONFIRM))
        {

        }
   }
}
#endif

static void Dcm_Lok_DslState_WaitingForTxConfirmation(void){
   uint8 Dcm_DslStateTemp_u8 = 0u;
    (void)Dcm_DslStateTemp_u8;
}

static void Dcm_Lok_DslState_ResponseTransmission(void){
   if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_SEND_PENDING_RESPONSE)
   {
        Dcm_Lok_DslSubState_SendPendingResponse();
   }

   if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_SEND_GENERAL_REJECT)
   {
        Dcm_Lok_DslSubState_SendGeneralReject();
   }

   if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_SEND_FINAL_RESPONSE)
   {
        Dcm_Lok_DslSubState_SendFinalResponse();
   }
}

static void Dcm_Lok_DslState_RequestReceived(void){
   if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_START_PROTOCOL)
   {
        Dcm_Lok_DslSubState_StartProtocol();
   }

   if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_P2MAX_TIMEMONITORING)
   {
        Dcm_Lok_DslSubState_MonitorP2Max();
   }
}

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_DslState_ProtocolPreemption(void){
   if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_STOP_PROTOCOL)
   {
        Dcm_Lok_DslSubState_StopProtocol();
   }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
   else{
        if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_STOP_ROE)
        {
            Dcm_Lok_DslSubState_StopRoe();
        }
   }
#endif
}

#endif

static void Dcm_Lok_DslState_WaitingForRxIndication(void){
   uint8 Dcm_DslStateTemp_u8 = 0u;
    (void)Dcm_DslStateTemp_u8;
}

static void Dcm_Lok_DslState_Idle(void){
   uint8 idxActiveSession_u8 = 0u;

    SchM_Enter_Dcm_Global_NoNest();
   idxActiveSession_u8 = Dcm_DsldGlobal_st.idxActiveSession_u8;
    SchM_Exit_Dcm_Global_NoNest();

   if((idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX) || (Dcm_DsldGlobal_st.flgMonitorP3timer_b != FALSE))
   {
        if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING)
        {
            Dcm_Lok_DslSubState_S3_OR_P3_TimeMoniotor();
        }

        if(Dcm_Lok_GetDslSubState() == DSL_SUBSTATE_S3_OR_P3_TIMEOUT)
        {
            Dcm_Lok_DslSubState_S3_OR_P3_Timeout(idxActiveSession_u8);
            Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
        }
   }
}

void Dcm_Lok_DslStateMachine(void){
   uint8 DslStateTemp_u8 = 0u;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_Check_ProtocolPreemptionStatus();
#endif

    SchM_Enter_Dcm_Global_NoNest();
    DslStateTemp_u8 = Dcm_Lok_GetDslState();
    SchM_Exit_Dcm_Global_NoNest();

    Dcm_Lok_ProcessDslStateMachine(DslStateTemp_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

