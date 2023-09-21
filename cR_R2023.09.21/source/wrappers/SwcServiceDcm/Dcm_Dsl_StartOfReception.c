#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmCore_DslDsd_Prot.hpp"

#define DCM_PROCESSREQUEST_WHILE_DSL_FREE            (0x00u)
#define DCM_PROCESSREQUEST_WHILE_DSL_BUSY            (0x01u)
#define DCM_PROCESSREQUEST_PRIORITYCHECK             (0x02u)
#define DCM_PROCESS_NO_REQUEST                       (0x03u)
#define DCM_NUMBER_OF_REQUEST_TYPE                   (0x04u)

#define Dcm_Lok_RxProcessRequest(DcmRxPduId,infoPtr,TpSduLength,RxBufferSizePtr)  \
    Dcm_ProcessRequest[Dcm_Lok_ValidateRequestType(DcmRxPduId,infoPtr,TpSduLength)](DcmRxPduId,infoPtr,TpSduLength,\
            RxBufferSizePtr)

typedef BufReq_ReturnType (*Dcm_ProcessRequestType)(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId,\
        P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength,\
        P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr);

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
const Dcm_ProcessRequestType  Dcm_ProcessRequest[DCM_NUMBER_OF_REQUEST_TYPE];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_DslRxPduArray_tst,DCM_VAR)Dcm_DslRxPduArray_ast[DCM_CFG_NUM_RX_PDUID];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
VAR(boolean , DCM_VAR)Dcm_isFuncTPOnOtherConnection_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
VAR (boolean,DCM_VAR) Dcm_isObdRequestReceived_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isProtocolSupprortedInActiveConfig(
        P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrArrivedProt_pcst)
{
    return((adrArrivedProt_pcst->Config_Mask) & (Dcm_ActiveConfiguration_u8) != 0u);
}
#endif

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isDslStateFree(void){
    return ((Dcm_Lok_GetDslState() == DSL_STATE_IDLE)
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
            &&      \
            ((Dcm_Lok_GetDslPreemptionState()   != DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING) \
            && (Dcm_Lok_GetDslPreemptionState() != DSL_SUBSTATE_STOP_PROTOCOL))
#endif
            );
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isDcmInitalised(void){
    return ((Dcm_isInitialised_b != FALSE) && (Dcm_acceptRequests_b != FALSE));
}

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isRxQueueFree(
        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ConnectionId
   ,     VAR(BufReq_ReturnType, AUTOMATIC) ReturnValue_en)
{
    return ((Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE) && \
            (ReturnValue_en != BUFREQ_E_OVFL)                            && \
            (Dcm_DsldGlobal_st.nrActiveConn_u8 == ConnectionId)          && \
            (Dcm_Lok_GetDslState()    != DSL_STATE_WAITING_FOR_RXINDICATION));
}
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isDcmProcessingRoeEvent(VAR(uint8,AUTOMATIC) idxProtocol_u8
   ,     VAR(uint8,AUTOMATIC) connectionId_u8)
{
   VAR(boolean, AUTOMATIC) isRoeEventOn_b = FALSE;

   if(Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED)
   {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        (void)connectionId_u8;

        if((Dcm_DsldProtocol_pcst[idxProtocol_u8].premption_level_u8 == \
                Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].premption_level_u8))
#else
        (void)idxProtocol_u8;
        if(Dcm_DsldGlobal_st.nrActiveConn_u8 == connectionId_u8)
#endif
        {
            isRoeEventOn_b = TRUE;
        }
   }

    return isRoeEventOn_b;
}
#endif

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Lok_PremptionHandling(
        P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) ArrivedProtocol_pcst
   ,     VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC) TpSduLength,VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) RxpduId)
{
   VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   VAR(uint8,AUTOMATIC) idxProtocol_u8  = Dcm_DsldGlobal_st.idxCurrentProtocol_u8;
   VAR(uint8,AUTOMATIC) connectionId_u8 = 0u;

   if(ArrivedProtocol_pcst->rx_buffer_size_u32 < (uint32)TpSduLength)
   {
        bufRequestStatus_en = BUFREQ_E_OVFL;
   }
   else{
        bufRequestStatus_en = BUFREQ_OK;

        if(0xFF != Dcm_DsldGlobal_st.dataNewRxPduId_u8)
        {

            connectionId_u8 = Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataNewRxPduId_u8];
            idxProtocol_u8  = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;
        }

        if(ArrivedProtocol_pcst->premption_level_u8 < Dcm_DsldProtocol_pcst[idxProtocol_u8].premption_level_u8)
        {
            Dcm_DsldGlobal_st.dataNewRxPduId_u8             = RxpduId;
            Dcm_DsldGlobal_st.dataNewdataRequestLength_u16  = TpSduLength;

            Dcm_Lok_SetDslPreemptionState(DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING);
            Dcm_DslRxPduArray_ast[RxpduId].Dcm_DslCopyRxData_b  = TRUE;
            Dcm_Lok_ResetCopyRxDataStatus(RxpduId);
        }
        else{

            if(FALSE == ArrivedProtocol_pcst->nrc21_b)
            {
                bufRequestStatus_en = BUFREQ_E_NOT_OK;
            }
        }
   }
    return bufRequestStatus_en;
}
#endif

static FUNC(boolean,DCM_CODE) Dcm_Lok_CheckFunctionalTesterPresent( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr
   ,     VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength)
{
   VAR(boolean, AUTOMATIC) isFuncTesterPresent_b = FALSE;

   if(infoPtr != NULL_PTR)
   {
       if((DcmRxPduId    >= DCM_INDEX_FUNC_RX_PDUID)                  && \
           (TpSduLength  == DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH)     && \
           (infoPtr->SduDataPtr[0] == DCM_DSLD_PARALLEL_TPR_BYTE1)    && \
           (infoPtr->SduDataPtr[1] == DCM_DSLD_PARALLEL_TPR_BYTE2))
           {
               isFuncTesterPresent_b = TRUE;
           }
   }
    return isFuncTesterPresent_b;
}

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_InformApplication(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
   ,     VAR(BufReq_ReturnType, AUTOMATIC) BufRequestStatus_en)
{
   VAR(uint8,AUTOMATIC) connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   VAR(uint8,AUTOMATIC) idxProtocol_u8  = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

   if(BUFREQ_OK == BufRequestStatus_en)
   {
        *(RxBufferSizePtr) = (Type_SwcServiceCom_tLengthPdu)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);

        if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)
        {
           Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength  = TpSduLength;

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
           Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslBufferPtr_pu8 = Dcm_Lok_ProvideFreeBuffer(idxProtocol_u8,FALSE);
           Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr = Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslBufferPtr_pu8;
#else
           Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr = Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_mainBuffer_pa;
#endif

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
#else
          (void)infoPtr;
#endif
        }

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
        if(DcmRxPduId == (DCM_CFG_NUM_RX_PDUID-1u))
        {
            Dcm_isObdRequestReceived_b = TRUE;
        }
#endif
   }
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
   else{

        if(FALSE != Dcm_Lok_isRxQueueFree(connectionId_u8,BufRequestStatus_en))
        {
            SchM_Enter_Dcm_Global_NoNest();

            Dcm_QueueStructure_st.adrBufferPtr_pu8 = Dcm_Lok_ProvideFreeBuffer(idxProtocol_u8,TRUE);
            Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr = Dcm_QueueStructure_st.adrBufferPtr_pu8;
            Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength  = TpSduLength;
            Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b              = TRUE;

            Dcm_QueueStructure_st.dataQueueReqLength_u16 = TpSduLength;
            Dcm_QueueStructure_st.dataQueueRxPduId_u8    = DcmRxPduId;

            *(RxBufferSizePtr) = (Type_SwcServiceCom_tLengthPdu)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);

            Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_RUNNING;
            BufRequestStatus_en = BUFREQ_OK;

            SchM_Exit_Dcm_Global_NoNest();
        }
   }
#endif

    return BufRequestStatus_en;
}

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_ProcessNoRequest( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength,

        P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{
    (void)DcmRxPduId;
    (void)infoPtr;
    (void)TpSduLength;
    (void)RxBufferSizePtr;

    return BUFREQ_OK;
}

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_ProcessRequest_CheckPriority( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{
   VAR(BufReq_ReturnType, AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   VAR(uint8,AUTOMATIC) connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   VAR(uint8,AUTOMATIC) idxProtocol_u8  = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

   if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b)
   {
        bufRequestStatus_en = BUFREQ_OK;
   }
   else{
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        bufRequestStatus_en = Dcm_Lok_PremptionHandling(&Dcm_DsldProtocol_pcst[idxProtocol_u8],TpSduLength,DcmRxPduId);
#else

        bufRequestStatus_en = (FALSE != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b)? BUFREQ_OK : BUFREQ_E_NOT_OK;
#endif
   }

   bufRequestStatus_en = Dcm_Lok_InformApplication(DcmRxPduId,infoPtr,TpSduLength,RxBufferSizePtr,bufRequestStatus_en);

    return bufRequestStatus_en;
}

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_ProcessRequestWhileRoeEvent(
        VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength)
{
   VAR(BufReq_ReturnType, AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   VAR(uint8,AUTOMATIC) connectionId_u8  = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   VAR(uint8,AUTOMATIC) idxProtocol_u8   = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   if(Dcm_DsldProtocol_pcst[idxProtocol_u8].premption_level_u8 == \
            Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].premption_level_u8)
   {

        bufRequestStatus_en = Dcm_DsldPersistentRoeHandling_en(&Dcm_DsldProtocol_pcst[idxProtocol_u8],TpSduLength,DcmRxPduId);

        if((bufRequestStatus_en == BUFREQ_E_NOT_OK) && (Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b != FALSE))
        {
            bufRequestStatus_en = BUFREQ_OK;
        }
   }
#else
   if(Dcm_DsldGlobal_st.nrActiveConn_u8 == connectionId_u8)
   {

        Dcm_Lok_ReloadS3Timer();

        bufRequestStatus_en = (FALSE != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b) ? BUFREQ_OK : BUFREQ_E_NOT_OK;
   }
#endif

    return bufRequestStatus_en;
}
#endif

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_ProcessRequestWhileDslBusy( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{
   VAR(BufReq_ReturnType, AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   VAR(uint8,AUTOMATIC) connectionId_u8  = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   VAR(uint8,AUTOMATIC) idxProtocol_u8   = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

   if(FALSE != Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b)
   {
        bufRequestStatus_en = BUFREQ_OK;
   }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
   else if(FALSE != Dcm_Lok_isDcmProcessingRoeEvent(idxProtocol_u8,connectionId_u8))
   {
        bufRequestStatus_en = Dcm_Lok_ProcessRequestWhileRoeEvent(DcmRxPduId,TpSduLength);
   }
#endif
   else{
        if(Dcm_DsldGlobal_st.nrActiveConn_u8 != connectionId_u8)
        {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
            bufRequestStatus_en = Dcm_Lok_PremptionHandling(&Dcm_DsldProtocol_pcst[idxProtocol_u8],TpSduLength,DcmRxPduId);
#else

            bufRequestStatus_en = (FALSE != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b) ? BUFREQ_OK : BUFREQ_E_NOT_OK;
#endif
        }
   }

   bufRequestStatus_en = Dcm_Lok_InformApplication(DcmRxPduId,infoPtr,TpSduLength,RxBufferSizePtr,bufRequestStatus_en);

    return bufRequestStatus_en;
}

static FUNC(BufReq_ReturnType,DCM_CODE) Dcm_Lok_ProcessRequestWhileDslFree( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{

   VAR(uint8,AUTOMATIC) connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   VAR(uint8,AUTOMATIC) idxProtocol_u8  = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

    SchM_Enter_Dcm_Global_NoNest();

    Dcm_Lok_SetDslState(DSL_STATE_WAITING_FOR_RXINDICATION);

   if(Dcm_DsldGlobal_st.idxCurrentProtocol_u8 != idxProtocol_u8)
   {
        Dcm_DsldGlobal_st.flgCommActive_b    = FALSE;
   }
    Dcm_DsldGlobal_st.idxCurrentProtocol_u8  = idxProtocol_u8;
    Dcm_DsldGlobal_st.nrActiveConn_u8        = connectionId_u8;
    Dcm_DsldGlobal_st.dataActiveRxPduId_u8   = DcmRxPduId;
    Dcm_DsldGlobal_st.dataActiveTxPduId_u8   = Dcm_DsldConnTable_pcst[connectionId_u8].txpduid_num_u8;
    Dcm_DsldGlobal_st.dataRequestLength_u16  = TpSduLength;
    Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b = TRUE;

    SchM_Exit_Dcm_Global_NoNest();

    Dcm_Lok_ResetCopyRxDataStatus(DcmRxPduId);

    (void)Dcm_Lok_InformApplication(DcmRxPduId,infoPtr,TpSduLength,RxBufferSizePtr,BUFREQ_OK);

    return BUFREQ_OK;
}

static FUNC(uint8,DCM_CODE)Dcm_Lok_ValidateRequestType( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength)
{
   VAR(uint8,AUTOMATIC) connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   VAR(uint8,AUTOMATIC) requestType_u8  = DCM_PROCESS_NO_REQUEST;
    Dcm_isFuncTPOnOtherConnection_b      = FALSE;

   if(FALSE != Dcm_Lok_CheckFunctionalTesterPresent(DcmRxPduId,infoPtr,TpSduLength))
   {
        Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslFuncTesterPresent_b = TRUE;

        if(Dcm_DsldGlobal_st.nrActiveConn_u8 != connectionId_u8)
        {
            Dcm_isFuncTPOnOtherConnection_b = TRUE;
        }
   }

   if((Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX) || \
            (Dcm_DsldGlobal_st.nrActiveConn_u8 == connectionId_u8))
   {

        if((FALSE != Dcm_Lok_isDslStateFree()) && (FALSE == Dcm_isFuncTPOnOtherConnection_b))
        {
            requestType_u8 = DCM_PROCESSREQUEST_WHILE_DSL_FREE;
        }
        else{
            requestType_u8 = DCM_PROCESSREQUEST_WHILE_DSL_BUSY;
        }
   }
   else{
        requestType_u8 = DCM_PROCESSREQUEST_PRIORITYCHECK;
   }

    return requestType_u8;
}

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)

static FUNC(boolean,DCM_CODE) Dcm_Lok_ProcessSharedRxPduid(P2VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC, DCM_APPL_DATA) RxPduIdPtr
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr)
{
   VAR(boolean, AUTOMATIC) processStatus_b  = TRUE;
   VAR(uint8,AUTOMATIC) idxProtocol_u8  = 0u;
   VAR(uint8,AUTOMATIC) protocolId_u8   = 0u;

   if(FALSE != Dcm_Lok_isRxPduShared(*RxPduIdPtr,infoPtr->SduDataPtr[0]))
   {
        idxProtocol_u8   = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DCM_CFG_NUM_RX_PDUID-1u]].protocol_num_u8;
        protocolId_u8    = Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8;

        if((protocolId_u8 == DCM_OBD_ON_CAN) || (protocolId_u8  == DCM_OBD_ON_FLEXRAY))
        {
            *RxPduIdPtr = (DCM_CFG_NUM_RX_PDUID-1u);
        }
        else{
            processStatus_b = FALSE;
        }
   }
    return processStatus_b;
}
#endif

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_CheckPermissions(P2VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC,DCM_APPL_DATA) RxPduIdPtr
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength)
{
   VAR(Std_ReturnType,AUTOMATIC) permissionsStatus  = E_NOT_OK;
   VAR(uint8,AUTOMATIC) connectionId_u8 = 0u;
   VAR(uint8,AUTOMATIC) idxProtocol_u8  = 0u;
   VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) rxPduid     = 0u;

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
   if(FALSE != Dcm_Lok_ProcessSharedRxPduid(RxPduIdPtr,infoPtr))
#endif
   {
        rxPduid = *RxPduIdPtr;
        connectionId_u8 = Dcm_DsldRxTable_pcu8[rxPduid];
        idxProtocol_u8  = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

        if(DCM_CHKNOCOMM_MODE(Dcm_DsldConnTable_pcst[connectionId_u8].channel_idx_u8))
        {
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
            if(FALSE != Dcm_Lok_isProtocolSupprortedInActiveConfig(&Dcm_DsldProtocol_pcst[idxProtocol_u8]))
#endif
            {
                if(E_OK == DcmAppl_DcmGetRxPermission(Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8,\
                        rxPduid,infoPtr,TpSduLength))
                {
                    permissionsStatus = E_OK;
                }
            }
        }
   }
    return permissionsStatus;
}

static FUNC(boolean,DCM_CODE) Dcm_Lok_StartOfReception_CheckEnvironment(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) infoPtr
   ,     P2CONST(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{
   VAR(boolean,AUTOMATIC) environmentStatus_b = FALSE;

   if(FALSE == Dcm_Lok_isDcmInitalised())
   {
        DCM_DET_ERROR(DCM_STARTOFRECEPTION_ID , DCM_E_UNINIT);
   }
#if((DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)||(DCM_CALLAPPLICATIONONREQRX_ENABLED != DCM_CFG_OFF))
   else if(infoPtr == NULL_PTR)
   {
        DCM_DET_ERROR(DCM_STARTOFRECEPTION_ID , DCM_E_PARAM_POINTER);
   }
#endif
   else if(DcmRxPduId >= DCM_CFG_NUM_RX_PDUID)
   {
        DCM_DET_ERROR(DCM_STARTOFRECEPTION_ID ,  DCM_E_DCMRXPDUID_RANGE_EXCEED )
   }
   else if(RxBufferSizePtr == NULL_PTR)
   {
       DCM_DET_ERROR(DCM_STARTOFRECEPTION_ID , DCM_E_PARAM_POINTER)
   }
   else{
        environmentStatus_b = TRUE;
   }

#if((DCM_CFG_RXPDU_SHARING_ENABLED == DCM_CFG_OFF) && (DCM_CALLAPPLICATIONONREQRX_ENABLED == DCM_CFG_OFF))
    (void)infoPtr;
#endif

    return environmentStatus_b;
}

FUNC(BufReq_ReturnType,DCM_CODE) Dcm_StartOfReception(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) info,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr)
{
   VAR(BufReq_ReturnType,AUTOMATIC) bufRequestStatus_en = BUFREQ_E_NOT_OK;
   VAR(uint8,AUTOMATIC) idxProtocol_u8    = 0u;

if(FALSE != Dcm_Lok_StartOfReception_CheckEnvironment(id,info,bufferSizePtr))
   {
        if(E_OK == Dcm_Lok_CheckPermissions(&id,info,TpSduLength))
        {
            SchM_Enter_Dcm_Global_NoNest();

            idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[id]].protocol_num_u8;
            Dcm_DslRxPduArray_ast[id].Dcm_DslCopyRxData_b  = FALSE;
            Dcm_DslRxPduArray_ast[id].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;

            SchM_Exit_Dcm_Global_NoNest();

            if(TpSduLength == 0u)
            {
                *(bufferSizePtr) = (Type_SwcServiceCom_tLengthPdu)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
                bufRequestStatus_en = BUFREQ_OK;
            }

            else if((Dcm_MsgLenType)TpSduLength > Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32)
            {
                bufRequestStatus_en = BUFREQ_E_OVFL;
            }
            else{
                bufRequestStatus_en = Dcm_Lok_RxProcessRequest(id,info,TpSduLength,bufferSizePtr);
            }
        }
   }
    return (bufRequestStatus_en);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

const Dcm_ProcessRequestType  Dcm_ProcessRequest[DCM_NUMBER_OF_REQUEST_TYPE] =
{
    &Dcm_Lok_ProcessRequestWhileDslFree
   ,   &Dcm_Lok_ProcessRequestWhileDslBusy
   ,   &Dcm_Lok_ProcessRequest_CheckPriority
   ,   &Dcm_Lok_ProcessNoRequest
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
