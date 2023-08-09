

#include "DcmCore_DslDsd_Inf.h"

#define DCM_KWP_PROTOCOL         (0x80u)
#define DCM_KWP_MASK             (0xF0u)

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
#define Dcm_Lok_isHighPrioRequestReceived(DcmRxPduId)                (DcmRxPduId == Dcm_DsldGlobal_st.dataNewRxPduId_u8)

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    #define Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent(DcmRxPduId)   (DcmRxPduId == Dcm_DsldGlobal_st.dataPassRxPduId_u8)
#endif

#endif

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
VAR(PduInfoType,DCM_VAR) Dcm_DsldPduInfo_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_CheckLowPriorityRequestReceived(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{
    return (Dcm_DsldProtocol_pcst[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8].nrc21_b);
}

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isConsecutiveRequestReceived(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED == DCM_CFG_OFF)
    (void)DcmRxPduId;
#endif

    return((Dcm_DsldGlobal_st.flgCommActive_b != FALSE)
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
       && (DcmRxPduId != Dcm_DsldGlobal_st.dataNewRxPduId_u8)
#endif
       );
}
#endif

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isKWPRequestReceived(VAR(uint8,AUTOMATIC) idxProtocol_u8)
{
    return((Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8 & DCM_KWP_MASK) == DCM_KWP_PROTOCOL);
}
#endif

LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_Lok_StartP2Timer(void)
{
    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
                  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - \
                          Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust),
                   Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
}

LOCAL_INLINE FUNC(PduLengthType,DCM_CODE) Dcm_Lok_GetRequestLength(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{
    VAR(PduLengthType,AUTOMATIC) RequestLength = Dcm_DsldGlobal_st.dataRequestLength_u16;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    if(FALSE != Dcm_Lok_isHighPrioRequestReceived(DcmRxPduId))
    {
        RequestLength = Dcm_DsldGlobal_st.dataNewdataRequestLength_u16;
    }
    #if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        else
        {
            if(FALSE != Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent(DcmRxPduId))
            {
                RequestLength = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;
            }
        }
    #endif
#else
    (void)DcmRxPduId;
#endif

    return RequestLength;
}

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void, DCM_CODE) Dcm_Lok_ResetCopyRxDataStatus (VAR(PduIdType,AUTOMATIC) RxPduId)
{
    VAR(PduIdType,AUTOMATIC) idxRxPduid;

    for ( idxRxPduid = 0 ; idxRxPduid < DCM_CFG_NUM_RX_PDUID ; idxRxPduid++ )
    {

        if ((idxRxPduid != RxPduId) && (Dcm_DslRxPduArray_ast[idxRxPduid].Dcm_DslCopyRxData_b != FALSE))
        {
            Dcm_DslRxPduArray_ast[idxRxPduid].Dcm_DslCopyRxData_b = FALSE;
        }
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_DiscardRequest(VAR(PduIdType, AUTOMATIC) DcmRxPduId,
        VAR(Std_ReturnType, AUTOMATIC) Result)
{

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED != DCM_CFG_OFF)
    if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
    {
        (void)DcmAppl_TpRxIndication(DcmRxPduId,Result);
    }
#else
    (void)Result;
#endif

    Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b  = FALSE;
    Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8        = DCM_SERVICEID_DEFAULT_VALUE;

    if((Dcm_DsldGlobal_st.dataActiveRxPduId_u8 == DcmRxPduId) && \
            (Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_RXINDICATION))
    {
        Dcm_Lok_SetDslState(DSL_STATE_IDLE);
        Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);

        Dcm_Lok_ReloadS3Timer();
    }

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    if(FALSE != Dcm_Lok_isHighPrioRequestReceived(DcmRxPduId))
    {
        Dcm_DsldGlobal_st.dataNewRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;
        Dcm_Lok_SetDslPreemptionState(DSL_STATE_IDLE);
    }
    #if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        if(FALSE != Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent(DcmRxPduId))
        {
            Dcm_DsldGlobal_st.dataPassRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;
            Dcm_Lok_SetDslState(DSL_STATE_IDLE);

            if(Dcm_Lok_GetDslState() != DSL_STATE_WAITING_FOR_RXINDICATION)
            {
                Dcm_Lok_SetDslNextState(DSL_STATE_IDLE);
                Dcm_Lok_SetDslNextSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
            }

            Dcm_Lok_ReloadS3Timer();
        }

    #endif
#endif

}

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessHighPriorityRequest(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{
    VAR(PduIdType,AUTOMATIC) dataActiveRxPduId_u8 = 0u;
    VAR(uint8,AUTOMATIC)idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

    Dcm_DsldGlobal_st.dataOldtxPduId_u8 = \
    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8]].txpduid_num_u8;

    SchM_Enter_Dcm_Global_NoNest();

    Dcm_DsldGlobal_st.dataActiveTxPduId_u8    = DCM_PDUID_DEFAULT_VALUE;
    Dcm_Lok_SetDslPreemptionState(DSL_SUBSTATE_STOP_PROTOCOL);
    dataActiveRxPduId_u8 = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;
    Dcm_DsldGlobal_st.dataActiveRxPduId_u8    = DcmRxPduId;

    SchM_Exit_Dcm_Global_NoNest();

    if(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId != Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dataActiveRxPduId_u8]].channel_idx_u8].ComMChannelId)
    {

        ComM_DCM_InactiveDiagnostic (Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dataActiveRxPduId_u8]].channel_idx_u8].ComMChannelId);
    }

    Dcm_DsldGlobal_st.dataNewRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    Dcm_DsldGlobal_st.dataPassRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;
#endif

    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
                  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[idxProtocol_u8].dataP2TmrAdjust),
                   Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
}
#endif

#if((DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF))

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessHighPriorityReqWhileRoeEvent(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{

    Dcm_DsldGlobal_st.dataOldtxPduId_u8 = \
    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8]].txpduid_num_u8;

    SchM_Enter_Dcm_Global_NoNest();

    if(Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_RXINDICATION)
    {
        Dcm_Lok_SetDslState(DSL_STATE_REQUEST_RECEIVED);
        Dcm_Lok_SetDslSubState(DSL_SUBSTATE_START_PROTOCOL);
        Dcm_DsldGlobal_st.dataActiveRxPduId_u8   = DcmRxPduId;
        Dcm_DsldGlobal_st.dataRequestLength_u16  = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;
        Dcm_DsldGlobal_st.dataPassRxPduId_u8     = DCM_PDUID_DEFAULT_VALUE;
    }
    else
    {
        Dcm_DsldGlobal_st.dataActiveTxPduId_u8    = DCM_PDUID_DEFAULT_VALUE;
        Dcm_Lok_SetDslPreemptionState(DSL_SUBSTATE_STOP_ROE);
        Dcm_DsldGlobal_st.dataRequestLength_u16   = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;
        Dcm_DsldGlobal_st.dataActiveRxPduId_u8    = DcmRxPduId;
        Dcm_DsldGlobal_st.dataPassRxPduId_u8      = DCM_PDUID_DEFAULT_VALUE;

        if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
        {
            Dcm_DsldGlobal_st.datActiveSrvtable_u8  = Dcm_DsldGlobal_st.dataOldSrvtable_u8;
        }
        Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
    }
    SchM_Exit_Dcm_Global_NoNest();

    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, \
                  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 -   \
                  Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust), \
                  Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
}
#endif

static FUNC(void,DCM_CODE) Dcm_Lok_ReloadP2maxValue(VAR(PduIdType, AUTOMATIC) DcmRxPduId,VAR(uint8,AUTOMATIC) idxProtocol_u8)
{
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) idxKwpTiming_u8 = 0u;
#endif

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    if(FALSE == Dcm_Lok_isConsecutiveRequestReceived(DcmRxPduId))
    {
        if(FALSE != Dcm_Lok_isKWPRequestReceived(idxProtocol_u8))
        {

            idxKwpTiming_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_idx_u8;
            Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P2_max_u32;
        }
        else
        {
            Dcm_DsldTimer_st.dataTimeoutP2max_u32 = DCM_CFG_DEFAULT_P2MAX_TIME;
        }
    }
#else
    #if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        if(FALSE != Dcm_Lok_isHighPrioRequestReceived(DcmRxPduId))
        {
            Dcm_DsldTimer_st.dataTimeoutP2max_u32 = DCM_CFG_DEFAULT_P2MAX_TIME;
        }
    #endif
        (void)idxProtocol_u8;
#endif

#if((DCM_CFG_KWP_ENABLED == DCM_CFG_OFF) && (DCM_CFG_PROTOCOL_PREMPTION_ENABLED == DCM_CFG_OFF))
        (void)DcmRxPduId;
#endif

}

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessRequest(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{
    VAR(uint8,AUTOMATIC)idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

    Dcm_Lok_ReloadP2maxValue(DcmRxPduId,idxProtocol_u8);

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    if(FALSE != Dcm_Lok_isHighPrioRequestReceived(DcmRxPduId))
    {
        Dcm_Lok_ProcessHighPriorityRequest(DcmRxPduId);
    }
    #if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        else if(FALSE != Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent(DcmRxPduId))
        {
            Dcm_Lok_ProcessHighPriorityReqWhileRoeEvent(DcmRxPduId);
        }
    #endif
    else
#endif
    {
        if(DcmRxPduId == Dcm_DsldGlobal_st.dataActiveRxPduId_u8)
        {

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
            Dcm_DsldGlobal_st.adrBufferPtr_pu8 = Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslBufferPtr_pu8;
#endif
            Dcm_Lok_SetDslState(DSL_STATE_REQUEST_RECEIVED);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_START_PROTOCOL);
            Dcm_Lok_StartP2Timer();
         }
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_SendNrc21(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{
    VAR(PduInfoType,AUTOMATIC) pduInfo_st = {NULL_PTR,DCM_NEGATIVE_RESPONSE_LENGTH};

    if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8))
    {
        if(E_OK != PduR_DcmTransmit(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].txpduid_num_u8, &pduInfo_st))
        {
            Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
        }
    }
    else
    {
        DCM_DET_ERROR(DCM_TPRXIND_ID , DCM_E_FULLCOMM_DISABLED )
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_CheckDiagnosticStatus(VAR(PduIdType, AUTOMATIC) DcmRxPduId,
        VAR(uint8,AUTOMATIC) idxProtocol_u8,P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) RxBuffer_pu8)
{
    if(FALSE == Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b)
    {
        if (idxProtocol_u8 == Dcm_DsldGlobal_st.idxCurrentProtocol_u8)
        {
            if((Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX) && (RxBuffer_pu8 != NULL_PTR))
            {
                Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[\
                                                Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
            }
        }
        else
        {
            if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
            {
                Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[\
                                                    Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
            }
        }
    }
}

static FUNC(void,DCM_CODE) Dcm_Lok_UpdateDSLstate(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{

    if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8 == Dcm_DsldGlobal_st.idxCurrentProtocol_u8)
    {
#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF))

        if(FALSE != Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent(DcmRxPduId))
        {
            Dcm_Lok_SetDslNextState(DSL_STATE_IDLE);
            Dcm_Lok_SetDslNextSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
            Dcm_DsldGlobal_st.dataPassRxPduId_u8  = DCM_PDUID_DEFAULT_VALUE;

            if(Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_RXINDICATION)
            {
                Dcm_Lok_SetDslState(DSL_STATE_IDLE);
                Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
            }
            Dcm_Lok_ReloadS3Timer();
        }
        else
#endif

        {
            Dcm_Lok_SetDslState(DSL_STATE_IDLE);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
            Dcm_Lok_ReloadS3Timer();
        }
    }
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    else
    {

        Dcm_DsldGlobal_st.dataNewRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;
    }
#endif
}

static FUNC(boolean,DCM_CODE) Dcm_Lok_isFunctionalTesterPresentProcessed(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{
    VAR(boolean,AUTOMATIC) processStatus_b = FALSE;

    if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b)
    {
        if(FALSE == Dcm_isRequestTobeProcessedByDSP(DcmRxPduId))
        {
            processStatus_b = TRUE;
            DcmAppl_DcmIndicationFuncTpr();
            Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b = FALSE;
            Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8       = DCM_SERVICEID_DEFAULT_VALUE;

            if(((Dcm_Lok_GetDslState() == DSL_STATE_IDLE) && (FALSE == Dcm_isFuncTPOnOtherConnection_b)) || \
                (Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED))
            {
                Dcm_Lok_ReloadS3Timer();
            }
        }
        else
        {
            if((DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH == Dcm_Lok_GetRequestLength(DcmRxPduId)) && \
                    (DCM_IS_KWPPROT_ACTIVE() == FALSE) && (DCM_IS_KLINEPROT_ACTIVE() == FALSE))
            {
                processStatus_b = TRUE;
                DcmAppl_DcmIndicationFuncTpr();
                Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b = FALSE;

                Dcm_Lok_UpdateDSLstate(DcmRxPduId);
            }
        }
    }
    return processStatus_b;
}

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)

static FUNC(boolean,DCM_CODE) Dcm_Lok_isRequestQueued(VAR(PduIdType, AUTOMATIC) DcmRxPduId,
        VAR(Std_ReturnType, AUTOMATIC) Result)
{
    VAR(boolean,AUTOMATIC) isRequestQueued = TRUE;
    VAR(uint8,AUTOMATIC) idxProtocol_u8    = 0;

    if((Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE) ||\
                    (Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b != FALSE))
    {
        isRequestQueued = FALSE;
    }
    else
    {

        SchM_Enter_Dcm_Global_NoNest();
        if((Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_RUNNING) && \
                (Dcm_Lok_GetDslState() != DSL_STATE_IDLE))
        {
            if(E_OK == Result)
            {

                Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_COMPLETED;
            }
            else
            {
                idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

                (void)Dcm_Lok_ProvideFreeBuffer(idxProtocol_u8,TRUE);

                Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_IDLE;
            }
        }
        SchM_Exit_Dcm_Global_NoNest();
    }

    return isRequestQueued;
}
#endif

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessSharedPduId(P2VAR(PduIdType, AUTOMATIC, DCM_APPL_DATA) RxPduIdPtr)
{
    if(((*RxPduIdPtr) < (DCM_CFG_NUM_RX_PDUID-1u)) && ((*RxPduIdPtr) == DCM_CFG_SHARED_RX_PDUID) && \
            (Dcm_isObdRequestReceived_b != FALSE))
    {
        *RxPduIdPtr = (DCM_CFG_NUM_RX_PDUID-1u);
        Dcm_isObdRequestReceived_b = FALSE;
    }
}
#endif

static FUNC(void,DCM_CODE) Dcm_Lok_ProcessRxIndication(VAR(PduIdType, AUTOMATIC) DcmRxPduId)
{
    VAR(uint8,AUTOMATIC)idxProtocol_u8  = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;
    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) rxBuffer_pu8 = NULL_PTR;

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    rxBuffer_pu8 = (Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslBufferPtr_pu8);
#else
    rxBuffer_pu8 = Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_mainBuffer_pa;
#endif

    Dcm_Lok_CheckDiagnosticStatus(DcmRxPduId,idxProtocol_u8,rxBuffer_pu8);

    if(FALSE == Dcm_isRequestTobeProcessedByDSP(DcmRxPduId))
    {

        if(FALSE == Dcm_Lok_isFunctionalTesterPresentProcessed(DcmRxPduId))
        {
            if(FALSE != Dcm_Lok_CheckLowPriorityRequestReceived(DcmRxPduId))
            {
                Dcm_Lok_SendNrc21(DcmRxPduId);
            }
        }
    }
    else
    {
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
        (void)DcmAppl_TpRxIndication(DcmRxPduId,E_OK);
#endif
        Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;

        if(FALSE == Dcm_Lok_isFunctionalTesterPresentProcessed(DcmRxPduId))
        {
            Dcm_Lok_ProcessRequest(DcmRxPduId);
        }
    }
}

FUNC(void,DCM_CODE) Dcm_TpRxIndication (VAR(PduIdType, AUTOMATIC) id,VAR(Std_ReturnType, AUTOMATIC) result)
{
    if (id >= DCM_CFG_NUM_RX_PDUID)
    {
        DCM_DET_ERROR(DCM_TPRXINDICATION_ID ,DCM_E_DCMRXPDUID_RANGE_EXCEED)
    }
    else
    {

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
        Dcm_Lok_ProcessSharedPduId(&id);
#endif

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
        if(FALSE == Dcm_Lok_isRequestQueued(id,result))
#endif
        {
            if(E_OK == result)
            {
                Dcm_Lok_ProcessRxIndication(id);
            }
            else
            {

                Dcm_Lok_DiscardRequest(id,result);
            }
        }
    }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
