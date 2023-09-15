

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#define DCM_KWP_PROTOCOL         (0x80u)
#define DCM_KWP_MASK             (0xF0u)

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
#define Dcm_Lok_isHighPrioRequestReceived(DcmRxPduId)                (DcmRxPduId == Dcm_DsldGlobal_st.dataNewRxPduId_u8)

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
#define Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent(DcmRxPduId)   (DcmRxPduId == Dcm_DsldGlobal_st.dataPassRxPduId_u8)
#endif
#endif

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Type_SwcServiceCom_stInfoPdu Dcm_DsldPduInfo_st;
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
Type_SwcServiceCom_stInfoPdu Dcm_OBDPduInfo_st;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

LOCAL_INLINE boolean Dcm_Lok_CheckLowPriorityRequestReceived(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
    return (Dcm_DsldProtocol_pcst[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8].nrc21_b);
}

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE boolean Dcm_Lok_isConsecutiveRequestReceived(Type_SwcServiceCom_tIdPdu DcmRxPduId)
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

LOCAL_INLINE boolean Dcm_Lok_isKWPRequestReceived(uint8 idxProtocol_u8)
{
    return((Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8 & DCM_KWP_MASK) == DCM_KWP_PROTOCOL);
}
#endif

LOCAL_INLINE void Dcm_Lok_StartP2Timer(void){
    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32
   ,                 (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - \
                          Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust)
   ,                  Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
}

LOCAL_INLINE Type_SwcServiceCom_tLengthPdu Dcm_Lok_GetRequestLength(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
   Type_SwcServiceCom_tLengthPdu RequestLength = Dcm_DsldGlobal_st.dataRequestLength_u16;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   if(FALSE != Dcm_Lok_isHighPrioRequestReceived((DcmRxPduId)))
   {
        RequestLength = Dcm_DsldGlobal_st.dataNewdataRequestLength_u16;
   }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        else{
            if(FALSE != Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent((DcmRxPduId)))
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
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_Lok_ResetCopyRxDataStatus (Type_SwcServiceCom_tIdPdu RxPduId)
{
   Type_SwcServiceCom_tIdPdu idxRxPduid;

   for( idxRxPduid = 0 ; idxRxPduid < DCM_CFG_NUM_RX_PDUID ; idxRxPduid++ )
   {

        if((idxRxPduid != RxPduId) && (Dcm_DslRxPduArray_ast[idxRxPduid].Dcm_DslCopyRxData_b != FALSE))
        {
            Dcm_DslRxPduArray_ast[idxRxPduid].Dcm_DslCopyRxData_b = FALSE;
        }
   }
}

static void Dcm_Lok_DiscardRequest(Type_SwcServiceCom_tIdPdu DcmRxPduId
   ,       Std_ReturnType Result)
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
        Dcm_Lok_SetDslState((DSL_STATE_IDLE));
        Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));

        Dcm_Lok_ReloadS3Timer();
   }

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   if(FALSE != Dcm_Lok_isHighPrioRequestReceived((DcmRxPduId)))
   {
        Dcm_DsldGlobal_st.dataNewRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;
        Dcm_Lok_SetDslPreemptionState((DSL_STATE_IDLE));
   }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        if(FALSE != Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent((DcmRxPduId)))
        {
            Dcm_DsldGlobal_st.dataPassRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;
            Dcm_Lok_SetDslState((DSL_STATE_IDLE));

            if(Dcm_Lok_GetDslState() != DSL_STATE_WAITING_FOR_RXINDICATION)
            {
                Dcm_Lok_SetDslNextState((DSL_STATE_IDLE));
                Dcm_Lok_SetDslNextSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
            }

            Dcm_Lok_ReloadS3Timer();
        }

#endif
#endif
}

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_ProcessHighPriorityRequest(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
   Type_SwcServiceCom_tIdPdu dataActiveRxPduId_u8 = 0u;
   uint8 idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

    Dcm_DsldGlobal_st.dataOldtxPduId_u8 = \
    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8]].txpduid_num_u8;

    SchM_Enter_Dcm_Global_NoNest();

    Dcm_DsldGlobal_st.dataActiveTxPduId_u8    = DCM_PDUID_DEFAULT_VALUE;
    Dcm_Lok_SetDslPreemptionState((DSL_SUBSTATE_STOP_PROTOCOL));
    dataActiveRxPduId_u8 = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;
    Dcm_DsldGlobal_st.dataActiveRxPduId_u8    = DcmRxPduId;

    SchM_Exit_Dcm_Global_NoNest();

#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
   if( ((Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dataActiveRxPduId_u8]].channel_idx_u8].ComMChannelId)
       != (Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_OBDGlobal_st.dataActiveRxPduId_u8]]
       .channel_idx_u8].ComMChannelId)) || (Dcm_Lok_GetOBDState() == DCM_OBD_IDLE))
#endif
   {

        if(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId !=
           Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dataActiveRxPduId_u8]].channel_idx_u8].ComMChannelId)
        {

            ComM_DCM_InactiveDiagnostic (Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dataActiveRxPduId_u8]].channel_idx_u8].ComMChannelId);
        }
   }
    Dcm_DsldGlobal_st.dataNewRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    Dcm_DsldGlobal_st.dataPassRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;
#endif

    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32
   ,                 (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[idxProtocol_u8].dataP2TmrAdjust)
   ,                  Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
}
#endif

#if((DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF))

static void Dcm_Lok_ProcessHighPriorityReqWhileRoeEvent(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{

    Dcm_DsldGlobal_st.dataOldtxPduId_u8 = \
    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8]].txpduid_num_u8;

    SchM_Enter_Dcm_Global_NoNest();

   if(Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_RXINDICATION)
   {
        Dcm_Lok_SetDslState((DSL_STATE_REQUEST_RECEIVED));
        Dcm_Lok_SetDslSubState((DSL_SUBSTATE_START_PROTOCOL));
        Dcm_DsldGlobal_st.dataActiveRxPduId_u8   = DcmRxPduId;
        Dcm_DsldGlobal_st.dataRequestLength_u16  = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;
        Dcm_DsldGlobal_st.dataPassRxPduId_u8     = DCM_PDUID_DEFAULT_VALUE;
   }
   else{
        Dcm_DsldGlobal_st.dataActiveTxPduId_u8    = DCM_PDUID_DEFAULT_VALUE;
        Dcm_Lok_SetDslPreemptionState((DSL_SUBSTATE_STOP_ROE));
        Dcm_DsldGlobal_st.dataRequestLength_u16   = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;
        Dcm_DsldGlobal_st.dataActiveRxPduId_u8    = DcmRxPduId;
        Dcm_DsldGlobal_st.dataPassRxPduId_u8      = DCM_PDUID_DEFAULT_VALUE;

        if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
        {
            Dcm_DsldGlobal_st.datActiveSrvtable_u8  = Dcm_DsldGlobal_st.dataOldSrvtable_u8;
        }
        Dcm_DsldSrvTable_pcst = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
   }
    SchM_Exit_Dcm_Global_NoNest();

    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, \
                  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 -   \
                  Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust), \
                  Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
}
#endif

static void Dcm_Lok_ReloadP2maxValue(Type_SwcServiceCom_tIdPdu DcmRxPduId,uint8 idxProtocol_u8)
{
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
   uint8 idxKwpTiming_u8 = 0u;
#endif

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
   if(FALSE == Dcm_Lok_isConsecutiveRequestReceived(DcmRxPduId))
   {
        if(FALSE != Dcm_Lok_isKWPRequestReceived(idxProtocol_u8))
        {

            idxKwpTiming_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_idx_u8;
            Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P2_max_u32;
        }
        else{
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

#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_OBDSendNRC21(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
   Type_SwcServiceCom_stInfoPdu pduInfo_st = {NULL_PTR,NULL_PTR,DCM_NEGATIVE_RESPONSE_LENGTH};

   if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8))
   {
        if(E_OK != PduR_DcmTransmit(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].txpduid_num_u8,&pduInfo_st))
        {
            Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
        }
   }
   else{
        DCM_DET_ERROR(DCM_TPRXIND_ID , DCM_E_FULLCOMM_DISABLED )
   }
}

void Dcm_Lok_ResetOBDCopyRxDataStatus(Type_SwcServiceCom_tIdPdu id)
{
   Type_SwcServiceCom_tIdPdu idxRxPduid = 0x00u;

   while(idxRxPduid < DCM_CFG_NUM_RX_PDUID)
   {

        if(idxRxPduid != id)
        {
            Dcm_DslOBDRxPduArray_ast[idxRxPduid].Dcm_DslCopyRxData_b = FALSE;
        }
        idxRxPduid++;
   }
}

static void Dcm_Lok_AcceptOBDRequest(Type_SwcServiceCom_tIdPdu id)
{
   if(id == Dcm_OBDGlobal_st.dataActiveRxPduId_u8)
   {
        Dcm_Lok_SetOBDState((DCM_OBD_REQUESTRECEIVED));
        DCM_TimerStart(Dcm_OBDGlobal_st.dataTimeoutMonitor_u32
   ,                         (DCM_CFG_DEFAULT_P2MAX_TIME - \
                           Dcm_DsldProtocol_pcst[Dcm_OBDGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust)
   ,                          Dcm_OBDP2OrS3StartTick_u32,Dcm_OBDP2OrS3TimerStatus_uchr)
     }
}

static void Dcm_Lok_DiscardOBDRequest(Type_SwcServiceCom_tIdPdu id,Std_ReturnType Result)
{
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED != DCM_CFG_OFF)
   if(FALSE != Dcm_DslOBDRxPduArray_ast[id].Dcm_DslCopyRxData_b)
   {
        (void)DcmAppl_TpRxIndication(id,Result);
   }
#else
    (void)Result;
#endif

    Dcm_DslOBDRxPduArray_ast[id].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;

   if((Dcm_OBDGlobal_st.dataActiveRxPduId_u8 == id) && \
       (Dcm_Lok_GetOBDState() == DCM_OBD_REQUESTRECEIVING))
   {
        Dcm_Lok_SetOBDState((DCM_OBD_IDLE));
   }
}

static void Dcm_Lok_OBDRxIndication(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
   if(FALSE == Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
   {
        if(Dcm_Lok_CheckLowPriorityRequestReceived(DcmRxPduId))
        {
            Dcm_Lok_OBDSendNRC21(DcmRxPduId);
        }
   }
   else{
        Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst
                                       [Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
        (void)DcmAppl_TpRxIndication(DcmRxPduId,E_OK);
#endif
        Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
        Dcm_Lok_AcceptOBDRequest(DcmRxPduId);
   }
}

#endif

static void Dcm_Lok_ProcessRequest(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
   uint8 idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

    Dcm_Lok_ReloadP2maxValue(DcmRxPduId,idxProtocol_u8);

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   if(FALSE != Dcm_Lok_isHighPrioRequestReceived((DcmRxPduId)))
   {
        Dcm_Lok_ProcessHighPriorityRequest(DcmRxPduId);
   }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        else if(FALSE != Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent((DcmRxPduId)))
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
            Dcm_Lok_SetDslState((DSL_STATE_REQUEST_RECEIVED));
            Dcm_Lok_SetDslSubState((DSL_SUBSTATE_START_PROTOCOL));
            Dcm_Lok_StartP2Timer();
         }
   }
}

static void Dcm_Lok_SendNrc21(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
   Type_SwcServiceCom_stInfoPdu pduInfo_st = {NULL_PTR,NULL_PTR,DCM_NEGATIVE_RESPONSE_LENGTH};

   if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8))
   {
        if(E_OK != PduR_DcmTransmit(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].txpduid_num_u8, &pduInfo_st))
        {
            Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
        }
   }
   else{
        DCM_DET_ERROR(DCM_TPRXIND_ID , DCM_E_FULLCOMM_DISABLED )
   }
}

static void Dcm_Lok_CheckDiagnosticStatus(Type_SwcServiceCom_tIdPdu DcmRxPduId
   ,       uint8 idxProtocol_u8,const uint8 * RxBuffer_pu8)
{
   if(FALSE == Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b)
   {
        if(idxProtocol_u8 == Dcm_DsldGlobal_st.idxCurrentProtocol_u8)
        {
            if((Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX) && (RxBuffer_pu8 != NULL_PTR))
            {
                Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[\
                                                Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
            }
        }
        else{
            if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
            {
                Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[\
                                                    Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
            }
        }
   }
}

static void Dcm_Lok_UpdateDSLstate(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{

   if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8 == Dcm_DsldGlobal_st.idxCurrentProtocol_u8)
   {
#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF))

        if(FALSE != Dcm_Lok_isHighPrioReqReceivedWhileRoeEvent((DcmRxPduId)))
        {
            Dcm_Lok_SetDslNextState((DSL_STATE_IDLE));
            Dcm_Lok_SetDslNextSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
            Dcm_DsldGlobal_st.dataPassRxPduId_u8  = DCM_PDUID_DEFAULT_VALUE;

            if(Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_RXINDICATION)
            {
                Dcm_Lok_SetDslState((DSL_STATE_IDLE));
                Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
            }
            Dcm_Lok_ReloadS3Timer();
        }
        else
#endif

        {
            Dcm_Lok_SetDslState((DSL_STATE_IDLE));
            Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
            Dcm_Lok_ReloadS3Timer();
        }
   }
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   else{

        Dcm_DsldGlobal_st.dataNewRxPduId_u8 = DCM_PDUID_DEFAULT_VALUE;
   }
#endif
}

static boolean Dcm_Lok_isFunctionalTesterPresentProcessed(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
   boolean processStatus_b = FALSE;

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
        else{
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

static boolean Dcm_Lok_isRequestQueued(Type_SwcServiceCom_tIdPdu DcmRxPduId
   ,       Std_ReturnType Result)
{
   boolean isRequestQueued = TRUE;
   uint8 idxProtocol_u8    = 0;

   if((Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE) ||\
                    (Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b != FALSE))
   {
        isRequestQueued = FALSE;
   }
   else{

        SchM_Enter_Dcm_Global_NoNest();
        if((Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_RUNNING) && \
                (Dcm_Lok_GetDslState() != DSL_STATE_IDLE))
        {
            if(E_OK == Result)
            {

                Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_COMPLETED;
            }
            else{
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

static void Dcm_Lok_ProcessSharedPduId(Type_SwcServiceCom_tIdPdu * RxPduIdPtr)
{
   if(((*RxPduIdPtr) < (DCM_CFG_NUM_RX_PDUID-1u)) && ((*RxPduIdPtr) == DCM_CFG_SHARED_RX_PDUID) && \
            (Dcm_isObdRequestReceived_b != FALSE))
   {
        *RxPduIdPtr = (DCM_CFG_NUM_RX_PDUID-1u);
        Dcm_isObdRequestReceived_b = FALSE;
   }
}
#endif

static void Dcm_Lok_ProcessRxIndication(Type_SwcServiceCom_tIdPdu DcmRxPduId)
{
   uint8 idxProtocol_u8  = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;
   const uint8 * rxBuffer_pu8 = NULL_PTR;

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
   else{
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

void Dcm_TpRxIndication (Type_SwcServiceCom_tIdPdu id,Std_ReturnType result)
{
   if(id >= DCM_CFG_NUM_RX_PDUID)
   {
        DCM_DET_ERROR(DCM_TPRXINDICATION_ID ,DCM_E_DCMRXPDUID_RANGE_EXCEED)
   }
   else{

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
        Dcm_Lok_ProcessSharedPduId(&id);
#endif

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
        if(FALSE == Dcm_Lok_isRequestQueued(id,result))
#endif
        {
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
            if(Dcm_Lok_IsRxPduIdOBD(id))
            {
                (E_OK == result)?Dcm_Lok_OBDRxIndication(id):Dcm_Lok_DiscardOBDRequest(id,result);
            }
            else
#endif
            {
                (E_OK == result)?Dcm_Lok_ProcessRxIndication(id):Dcm_Lok_DiscardRequest(id,result);
            }
        }
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
