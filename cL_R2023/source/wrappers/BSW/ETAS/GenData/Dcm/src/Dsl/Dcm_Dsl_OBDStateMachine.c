
#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "DcmCore_Main_Inf.h"
#include "Dcm_Dsl_Priv.h"
#include "Dcm_Dsd_Prv.h"
#include "Rte_Dcm.h"

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
boolean Dcm_OBDisGeneralRejectSent_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
uint8 Dcm_CurOBDProtocol_u8;
uint8 stObdSubState_en;
uint8 Dcm_OBDWaitPendBuffer_au8[8];
Dcm_SrvOpStatusType Dcm_OBDExtSrvOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
Dcm_OBDStateMachine_tst Dcm_OBDState_en;
Dcm_OBDStateMachine_tst Dcm_OBD_PreviousState;
const Dcm_Dsld_ServiceType* Dcm_OBDSrvTable_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

static void Dcm_Lok_CancelTransmitOnParallelOBDReq(Dcm_DsdStatesType_ten DsdState)
{
    uint8 DslState_u8   = Dcm_Lok_GetDslState();
    if((DslState_u8 == DSL_STATE_WAITING_FOR_TXCONFIRMATION) || \
      ((DslState_u8 == DSL_STATE_ROETYPE1_RECEIVED) && (DsdState == DSD_WAITFORTXCONF)))
    {

        Dcm_isCancelTransmitInvoked_b = TRUE;
    }
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b)
    {

        DcmAppl_DcmCancelPagedBufferProcessing(Dcm_DsldGlobal_st.dataSid_u8);
        Dcm_isCancelTransmitInvoked_b = TRUE;
    }
#endif

    if(Dcm_isCancelTransmitInvoked_b == TRUE)
    {

        if(PduR_DcmCancelTransmit(Dcm_DsldGlobal_st.dataActiveTxPduId_u8) != E_OK)
        {
            Dcm_isCancelTransmitInvoked_b = FALSE;
        }
    }
}

static void Dcm_Lok_CancelService(void)
{
    Dcm_NegativeResponseCodeType TempNrc_u8 = 0x00;
    Dcm_DsdStatesType_ten DsdState = Dcm_Lok_GetDsdState();

    Dcm_Lok_CancelTransmitOnParallelOBDReq(DsdState);
    if((DsdState == DSD_CALL_SERVICE) &&
            (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp != NULL_PTR))
    {

        (void)(*Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp)
                (DCM_CANCEL,&Dcm_DsldMsgContext_st,&TempNrc_u8);
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
    }

    Dcm_Lok_SetDslState((DSL_STATE_IDLE));
    Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
    Dcm_Lok_SetDsdState((DSD_IDLE));
    Dcm_Lok_ResetDsdSubStateMachine();
}

static void Dcm_Lok_CheckSession(void)
{

    if(Dcm_DsldGlobal_st.idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX)
    {
        // Cancel ongoing service execution, if any
        Dcm_Lok_CancelService();
        // Switch to Default Session
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif
        (void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#endif
        Dcm_Lok_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
    }

    else
    {
        if( (Dcm_Lok_GetDslState() !=  DSL_STATE_IDLE) &&
             (Dcm_DsldGlobal_st.dataSid_u8 == DCM_SID_DIAGNOSTICSESSIONCONTROL) )
        {
            Dcm_Lok_CancelService();
        }
    }
}

static void Dcm_Lok_OBDTriggerNRCForProtocolFailure(void)
{
    Dcm_NegativeResponseCodeType dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
    Dcm_MsgItemType *adrRxBuffer_pu8 =
            (&(Dcm_DsldProtocol_pcst[Dcm_OBDGlobal_st.idxCurrentProtocol_u8]))->rx_mainBuffer_pa;

    Dcm_OBDGlobal_st.adrActiveTxBuffer_tpu8 = (&(Dcm_DsldProtocol_pcst[Dcm_OBDGlobal_st.idxCurrentProtocol_u8]))->tx_buffer_pa;
    Dcm_OBDGlobal_st.dataResponseByDsd_b = TRUE;
    Dcm_OBDGlobal_st.dataSid_u8     = adrRxBuffer_pu8[0];
    Dcm_OBDMsgContext_st.idContext  = Dcm_OBDGlobal_st.dataSid_u8;
    Dcm_OBDMsgContext_st.dcmRxPduId = Dcm_OBDGlobal_st.dataActiveRxPduId_u8;
    Dcm_OBDMsgContext_st.resDataLen = 0u;
    Dcm_OBDMsgContext_st.msgAddInfo.reqType = (Dcm_OBDGlobal_st.dataActiveRxPduId_u8 >= DCM_INDEX_FUNC_RX_PDUID)?
                                               DCM_PRV_FUNCTIONAL_REQUEST:DCM_PRV_PHYSICAL_REQUEST;

    Dcm_OBDGlobal_st.stResponseType_en = DCM_DSLD_POS_RESPONSE;
    Dcm_OBDGlobal_st.dataActiveTxPduId_u8 = Dcm_DsldConnTable_pcst[Dcm_OBDGlobal_st.nrActiveConn_u8].txpduid_num_u8;
    Dcm_OBDGlobal_st.cntrWaitpendCounter_u8 = 0;

    Dcm_Lok_SetOBDNegResponse(&Dcm_OBDMsgContext_st,dataNrc_u8);
    Dcm_OBDProcessingDone(&Dcm_OBDMsgContext_st);
}

static Std_ReturnType Dcm_Lok_StartOBDProtocol(void)
{
    Std_ReturnType StartProtocol_u8;

    // If the previously active protocol was an OBD Protocol,only then stop the protocol
    if(Dcm_CurOBDProtocol_u8 != DCM_NO_ACTIVE_PROTOCOL)
    {
        // Call API to inform application
        (void)Dcm_StopProtocol(Dcm_CurOBDProtocol_u8);
    }

    // Activate the protocol
    StartProtocol_u8 = Dcm_StartProtocol(Dcm_DsldProtocol_pcst[Dcm_OBDGlobal_st.idxCurrentProtocol_u8].protocolid_u8);
    if(StartProtocol_u8 == E_OK)
    {
        Dcm_OBDGlobal_st.flgCommActive_b = TRUE;
        Dcm_OBDGlobal_st.datActiveSrvtable_u8 = Dcm_DsldProtocol_pcst[Dcm_OBDGlobal_st.idxCurrentProtocol_u8].
                                                sid_tableid_u8;
        Dcm_OBDSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_OBDGlobal_st.datActiveSrvtable_u8].
                                                ptr_service_table_pcs;
        Dcm_Dsd_ServiceIni(Dcm_OBDGlobal_st.datActiveSrvtable_u8);

        // Set default session
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif
        (void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#endif
        Dcm_Lok_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
        Dcm_CurOBDProtocol_u8 = Dcm_DsldProtocol_pcst[Dcm_OBDGlobal_st.idxCurrentProtocol_u8].protocolid_u8;
    }
    // Protocol cannot be started , trigger NRC 0x22
    else
    {
        Dcm_Lok_OBDTriggerNRCForProtocolFailure();
    }
    return StartProtocol_u8;
}

static void Dcm_Lok_CheckOBDRequest(void)
{

    Std_ReturnType Flag = (Dcm_OBDGlobal_st.flgCommActive_b != TRUE)?Dcm_Lok_StartOBDProtocol():E_OK;
    if(E_OK == Flag)
    {
        // If channel is in full communication mode
        if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_OBDGlobal_st.nrActiveConn_u8].channel_idx_u8))
        {
            // Initialize WaitPend
            Dcm_OBDGlobal_st.cntrWaitpendCounter_u8 = 0x0u;
            // Update state to Verify Data State
            Dcm_Lok_SetOBDState((DCM_OBD_VERIFYDATA));
        }
    }
}

static Std_ReturnType Dcm_Lok_OBDVerifyDataStateMachine(void)
{
    Std_ReturnType VerificationResult_u8 = E_OK;
    switch(stObdSubState_en)
    {

        case OBDSUBSTATE_SERVICETABLE_INI:
              {
               Dcm_Lok_OBDServiceTableInit();
#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
            stObdSubState_en = OBDSUBSTATE_MANUFACTURER_NOTIFICATION;
#else
            stObdSubState_en = OBDSUBSTATE_VERIFYDATA;
#endif
              }
#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)

        case OBDSUBSTATE_MANUFACTURER_NOTIFICATION:
              {
                  VerificationResult_u8 = Dcm_Lok_DsdNotification(DCM_MANUFACTURERNOTIFICATION,DCM_OBDCONTEXT);
                  if(VerificationResult_u8 != E_OK)
                  {
                   break;
                  }
                  else
                  {
                   stObdSubState_en = OBDSUBSTATE_VERIFYDATA;
                  }
              }
#endif

        case OBDSUBSTATE_VERIFYDATA:
        {
            if(Dcm_Lok_OBDVerifyData() != E_OK)
            {
                VerificationResult_u8 = E_NOT_OK;
                break;
            }
            else
            {
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
                stObdSubState_en = OBDSUBSTATE_SUPPLIER_NOTIFICATION;
#else
                break;
#endif
            }
        }

#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
        case OBDSUBSTATE_SUPPLIER_NOTIFICATION:
        {
             VerificationResult_u8 = Dcm_Lok_DsdNotification(DCM_SUPPLIERNOTIFICATION,DCM_OBDCONTEXT);
             break;
        }
#endif

         default:
         {
             VerificationResult_u8 = E_NOT_OK;
         }
         break;
    }

    if(VerificationResult_u8 != DCM_E_PENDING)
    {
        stObdSubState_en = OBDSUBSTATE_SERVICETABLE_INI;
    }
    return VerificationResult_u8;
}

static void Dcm_Lok_OBDFrameIntermediateResponse(void)
{

    Dcm_OBDWaitPendBuffer_au8[0] = DCM_NEGRESPONSE_INDICATOR;
    Dcm_OBDWaitPendBuffer_au8[1] = Dcm_OBDGlobal_st.dataSid_u8;
    Dcm_OBDWaitPendBuffer_au8[2] = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING ;
    Dcm_OBDPduInfo_st.SduDataPtr = Dcm_OBDWaitPendBuffer_au8;
    Dcm_OBDPduInfo_st.SduLength = 0x03;
    Dcm_Lok_SetOBDPreviousState();
    Dcm_Lok_SetOBDState((DCM_OBD_WAITFORTXCONF));
}

static void Dcm_Lok_OBDSendGeneralReject(void)
{
    uint8 TempNrc_u8 =0x00u;
    Dcm_OBDMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;

    if(Dcm_OBDGlobal_st.cntrWaitpendCounter_u8 == DCM_CFG_MAX_WAITPEND)
    {
        const Dcm_Dsld_ServiceType* adrServiceTable_pcst =
                        &Dcm_OBDSrvTable_pcst[Dcm_OBDGlobal_st.idxService_u8];
        if(adrServiceTable_pcst->service_handler_fp != NULL_PTR)
        {

            Dcm_OBDSrvOpstatus_u8 = DCM_CANCEL;
            (void)(*(adrServiceTable_pcst)->service_handler_fp)
                                              (Dcm_OBDSrvOpstatus_u8,&Dcm_OBDMsgContext_st,&TempNrc_u8);

        }

        Dcm_OBDSrvOpstatus_u8 = DCM_INITIAL;
        Dcm_OBDExtSrvOpStatus_u8 = DCM_INITIAL;
        Dcm_ResetOBDSubStateMachine();
        Dcm_OBDGlobal_st.idxService_u8 = 0x00u;
        Dcm_OBDGlobal_st.dataResponseByDsd_b = TRUE;
        Dcm_Lok_SetOBDNegResponse(&Dcm_OBDMsgContext_st,DCM_E_GENERALREJECT);
        Dcm_OBDisGeneralRejectSent_b = TRUE;

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)

        rba_DiagAdapt_Confirmation_GeneralReject(Dcm_OBDGlobal_st.dataSid_u8);
#endif
        Dcm_OBDProcessingDone(&Dcm_OBDMsgContext_st);
    }
}

static void Dcm_Lok_SendOBDPendingResponse(void)
{
    if((Dcm_OBDGlobal_st.cntrWaitpendCounter_u8 < DCM_CFG_MAX_WAITPEND) || (DCM_CFG_MAX_WAITPEND == 0xFFu))
    {
        Dcm_OBDMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;
        Dcm_Lok_OBDFrameIntermediateResponse();
        if(Dcm_OBDGlobal_st.cntrWaitpendCounter_u8 < 0xFF)
        {

            Dcm_OBDGlobal_st.cntrWaitpendCounter_u8++;
        }
        Dcm_Lok_OBDSendResponse(&Dcm_OBDPduInfo_st);
    }
    else
    {
        // Send General reject for exceeding number of response pend
        Dcm_Lok_OBDSendGeneralReject();
    }
}

static boolean Dcm_Lok_OBDTimerElapsed(Dcm_OBDStateMachine_tst ObdState)
{
    boolean TimerElapsed = FALSE;
    // Timer monitoring is required only for these states
    if((ObdState == DCM_OBD_REQUESTRECEIVED)||(ObdState == DCM_OBD_VERIFYDATA)||(ObdState == DCM_OBD_PROCESSSERVICE))
    {
        // Monitor the timer count
        DCM_TimerProcess(Dcm_OBDGlobal_st.dataTimeoutMonitor_u32,Dcm_OBDP2OrS3StartTick_u32,Dcm_OBDP2OrS3TimerStatus_uchr)

        if(DCM_TimerElapsed(Dcm_OBDGlobal_st.dataTimeoutMonitor_u32))
        {
            TimerElapsed = TRUE;
        }
    }
    return TimerElapsed;
}

void Dcm_Lok_OBDTimerProcessing(void)
{
    Dcm_OBDStateMachine_tst ObdState = Dcm_Lok_GetOBDState();

    // Check whether Timer has elapsed
    if(FALSE != Dcm_Lok_OBDTimerElapsed(ObdState))
    {
        // Only happens for communication mode check
        if((ObdState == DCM_OBD_REQUESTRECEIVED) && (Dcm_OBDGlobal_st.flgCommActive_b == TRUE))
        {
            // Unable to move to FULL Communication mode, reject the request
            DcmAppl_DcmComModeError(Dcm_active_commode_e[Dcm_DsldConnTable_pcst
                                   [Dcm_OBDGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
            Dcm_Lok_SetOBDState((DCM_OBD_IDLE));
        }
        else
        {

            Dcm_Lok_SendOBDPendingResponse();
        }
    }
}

void Dcm_Lok_ConfirmationToOBDApl(void)
{

    Dcm_ConfirmationStatusType ConfirmationStatus_u8 =  (Dcm_OBDGlobal_st.dataResult_u8 == E_OK)?
               ((Dcm_OBDGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)?DCM_RES_POS_OK:DCM_RES_NEG_OK) :
               ((Dcm_OBDGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)?DCM_RES_POS_NOT_OK:DCM_RES_NEG_NOT_OK);

    if (Dcm_OBDGlobal_st.dataResponseByDsd_b == FALSE)
    {

            DcmAppl_DcmConfirmation(Dcm_OBDMsgContext_st.idContext, Dcm_OBDMsgContext_st.dcmRxPduId,
                    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_OBDMsgContext_st.dcmRxPduId]].testaddr_u16,
                    ConfirmationStatus_u8);
    }
    else
    {

        if(Dcm_OBDisGeneralRejectSent_b != FALSE)
        {
            DcmAppl_DcmConfirmation_GeneralReject(Dcm_OBDMsgContext_st.idContext,Dcm_OBDMsgContext_st.dcmRxPduId,
                    ConfirmationStatus_u8);
            Dcm_OBDisGeneralRejectSent_b = FALSE;
        }
        if ((ConfirmationStatus_u8 == DCM_RES_POS_OK) || (ConfirmationStatus_u8 == DCM_RES_POS_NOT_OK))
        {
            DcmAppl_DcmConfirmation(Dcm_OBDMsgContext_st.idContext, Dcm_OBDMsgContext_st.dcmRxPduId,
                    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_OBDMsgContext_st.dcmRxPduId]].testaddr_u16,
                    ConfirmationStatus_u8);
        }
#if(DCM_CFG_NR_CONF_ENABLED != DCM_CFG_OFF)
        else
        {

            DcmAppl_DcmConfirmation_DcmNegResp(Dcm_OBDMsgContext_st.idContext,
                    Dcm_OBDMsgContext_st.dcmRxPduId,ConfirmationStatus_u8);
        }
#endif
    }
#if ((DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS != 0u) || (DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS !=0u))
    Dcm_Dsd_CallRTEConfirmation(ConfirmationStatus_u8,DCM_OBDCONTEXT);
#endif
}

static void Dcm_Lok_UpdateOBDOpStatus(Std_ReturnType ServiceResult_u8)
{
    if(Dcm_OBDSrvTable_pcst[Dcm_OBDGlobal_st.idxService_u8].servicelocator_b != FALSE)
    {
        if(ServiceResult_u8 != DCM_E_PENDING)
        {
            Dcm_OBDSrvOpstatus_u8 = DCM_INITIAL;
        }
    }
    else
    {
        if(ServiceResult_u8 == DCM_E_PENDING)
        {
            Dcm_OBDExtSrvOpStatus_u8 = DCM_PENDING;
        }
        else
        {
            Dcm_OBDExtSrvOpStatus_u8 = DCM_INITIAL;
        }
    }
}

static void Dcm_Lok_ProcessOBDService(void)
{
    Dcm_NegativeResponseCodeType ErrorCode_u8 = DCM_DEFAULT_VALUE;
    const Dcm_Dsld_ServiceType* adrServiceTable_pcst = &Dcm_OBDSrvTable_pcst[Dcm_OBDGlobal_st.idxService_u8];

    Std_ReturnType ServiceResult_u8;

    if(Dcm_OBDSrvTable_pcst[Dcm_OBDGlobal_st.idxService_u8].servicelocator_b != FALSE)
    {
        ServiceResult_u8 = (*(adrServiceTable_pcst)->service_handler_fp)(Dcm_OBDSrvOpstatus_u8,
                &Dcm_OBDMsgContext_st,&ErrorCode_u8);
    }
    else
    {
        ServiceResult_u8 = (*(adrServiceTable_pcst)->service_handler_fp)(Dcm_OBDExtSrvOpStatus_u8
                ,&Dcm_OBDMsgContext_st,&ErrorCode_u8);
    }

    Dcm_Lok_UpdateOBDOpStatus(ServiceResult_u8);

    if(ServiceResult_u8 == DCM_E_PENDING)
    {

    }
    else
    {
        if(ServiceResult_u8 != E_OK)
        {

            if(ErrorCode_u8 == DCM_DEFAULT_VALUE)
            {
                ErrorCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }

            Dcm_Lok_SetOBDNegResponse(&Dcm_OBDMsgContext_st, ErrorCode_u8);
        }

        Dcm_OBDProcessingDone(&Dcm_OBDMsgContext_st);
    }
}

void Dcm_Lok_OBDStateMachine(void)
{
    switch(Dcm_OBDState_en)
    {
        // OBD request is completely received. Perform Protocol checks
        case DCM_OBD_REQUESTRECEIVED:
        {
            Dcm_Lok_CheckOBDRequest();
            Dcm_Lok_CheckSession();
            if(Dcm_OBDState_en != DCM_OBD_VERIFYDATA)
            {
                break;
            }
        }

        // Perform Service related checks

        case DCM_OBD_VERIFYDATA:
        {
            if(Dcm_Lok_OBDVerifyDataStateMachine() != E_OK)
            {
                break;
            }
            else
            {
                Dcm_Lok_SetOBDState((DCM_OBD_PROCESSSERVICE));
            }
        }

        // All checks are done, Invoke the OBD service

        case DCM_OBD_PROCESSSERVICE:
            Dcm_Lok_ProcessOBDService();
            break;

        default:

            break;
    }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
