

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmCore_DslDsd_Prot.hpp"
#include "Rte_Dcm.hpp"

#define DCM_PROCESSREQUEST_WHILE_DSL_FREE            (0x00u)
#define DCM_PROCESSREQUEST_WHILE_DSL_BUSY            (0x01u)
#define DCM_PROCESSREQUEST_PRIORITYCHECK             (0x02u)
#define DCM_PROCESS_NO_REQUEST                       (0x03u)
#define DCM_NUMBER_OF_REQUEST_TYPE                   (0x04u)

#define Dcm_Lok_RxProcessRequest(DcmRxPduId,infoPtr,TpSduLength,RxBufferSizePtr)  \
    Dcm_ProcessRequest[Dcm_Lok_ValidateRequestType(DcmRxPduId,infoPtr,TpSduLength)](DcmRxPduId,infoPtr,TpSduLength,\
            RxBufferSizePtr)

typedef BufReq_ReturnType (*Dcm_ProcessRequestType)(PduIdType DcmRxPduId,\
        const PduInfoType * infoPtr,PduLengthType TpSduLength,\
        PduLengthType * RxBufferSizePtr);

static BufReq_ReturnType Dcm_Lok_ProcessRequestWhileDslFree(
                                                                PduIdType DcmRxPduId
   ,                                                               const PduInfoType * infoPtr
   ,                                                               PduLengthType TpSduLength
   ,                                                               PduLengthType * RxBufferSizePtr);

static BufReq_ReturnType Dcm_Lok_ProcessRequestWhileDslBusy(
                                                                PduIdType DcmRxPduId
   ,                                                               const PduInfoType * infoPtr
   ,                                                               PduLengthType TpSduLength
   ,                                                               PduLengthType * RxBufferSizePtr);

static BufReq_ReturnType Dcm_Lok_ProcessRequest_CheckPriority(
                                                                PduIdType DcmRxPduId
   ,                                                               const PduInfoType * infoPtr
   ,                                                               PduLengthType TpSduLength
   ,                                                               PduLengthType * RxBufferSizePtr);

static BufReq_ReturnType Dcm_Lok_ProcessNoRequest(
                                                    PduIdType DcmRxPduId
   ,                                                   const PduInfoType * infoPtr
   ,                                                   PduLengthType TpSduLength
   ,                                                   PduLengthType * RxBufferSizePtr);

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static const Dcm_ProcessRequestType  Dcm_ProcessRequest[DCM_NUMBER_OF_REQUEST_TYPE] =
{
    &Dcm_Lok_ProcessRequestWhileDslFree
   ,   &Dcm_Lok_ProcessRequestWhileDslBusy
   ,   &Dcm_Lok_ProcessRequest_CheckPriority
   ,   &Dcm_Lok_ProcessNoRequest
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
Dcm_DslRxPduArray_tst Dcm_DslRxPduArray_ast[DCM_CFG_NUM_RX_PDUID];

// RxPduArray which is used exclusively for only OBD requests when parallel processing is used
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
Dcm_DslOBDRxPduArray_tst Dcm_DslOBDRxPduArray_ast[DCM_CFG_NUM_RX_PDUID];
#endif

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_isFuncTPOnOtherConnection_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
boolean Dcm_isObdRequestReceived_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)

LOCAL_INLINE boolean Dcm_Lok_isProtocolSupprortedInActiveConfig(
        const Dcm_Dsld_protocol_tableType * adrArrivedProt_pcst)
{
    return((adrArrivedProt_pcst->Config_Mask) & (Dcm_ActiveConfiguration_u8) != 0u);
}
#endif

LOCAL_INLINE boolean Dcm_Lok_isDslStateFree(void){
    return ((Dcm_Lok_GetDslState() == DSL_STATE_IDLE)
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
            &&      \
            ((Dcm_Lok_GetDslPreemptionState()   != DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING) \
            && (Dcm_Lok_GetDslPreemptionState() != DSL_SUBSTATE_STOP_PROTOCOL))
#endif
            );
}

LOCAL_INLINE boolean Dcm_Lok_isDcmInitalised(void){
    return ((Dcm_isInitialised_b != FALSE) && (Dcm_acceptRequests_b != FALSE));
}

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE boolean Dcm_Lok_isRxQueueFree(
        PduIdType ConnectionId
   ,       BufReq_ReturnType ReturnValue_en)
{
    return ((Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE) && \
            (ReturnValue_en != BUFREQ_E_OVFL)                            && \
            (Dcm_DsldGlobal_st.nrActiveConn_u8 == ConnectionId)          && \
            (Dcm_Lok_GetDslState()    != DSL_STATE_WAITING_FOR_RXINDICATION));
}
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE boolean Dcm_Lok_isDcmProcessingRoeEvent(uint8 idxProtocol_u8
   ,       uint8 connectionId_u8)
{
   boolean isRoeEventOn_b = FALSE;

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

#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)

static void Dcm_Lok_ReceiveNewReqWhenOBDIdle(PduIdType DcmRxPduId
   ,       const PduInfoType* info,PduLengthType TpSduLength,const uint8 idxProtocol_u8)
{
   uint8 connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];

    Dcm_Lok_SetOBDState((DCM_OBD_REQUESTRECEIVING));

   if(Dcm_OBDGlobal_st.idxCurrentProtocol_u8 != idxProtocol_u8)
   {
        Dcm_OBDGlobal_st.flgCommActive_b    = FALSE;
   }
    Dcm_OBDGlobal_st.idxCurrentProtocol_u8  = idxProtocol_u8;
    Dcm_OBDGlobal_st.nrActiveConn_u8        = connectionId_u8;
    Dcm_OBDGlobal_st.dataActiveRxPduId_u8   = DcmRxPduId;
    Dcm_OBDGlobal_st.dataActiveTxPduId_u8   = Dcm_DsldConnTable_pcst[connectionId_u8].txpduid_num_u8;
    Dcm_OBDGlobal_st.dataRequestLength_u16  = TpSduLength;
    Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b = TRUE;
    Dcm_Lok_ResetOBDCopyRxDataStatus(DcmRxPduId);
    Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduLength = TpSduLength;
    Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr =
            Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_mainBuffer_pa;
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
    (void)DcmAppl_StartOfReception(info->SduDataPtr[0],DcmRxPduId,TpSduLength
   ,           (Dcm_DslOBDRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr));
#else
    (void)info;
#endif
}

static BufReq_ReturnType Dcm_Lok_ProcessNewObdRequest(PduIdType DcmRxPduId
   ,       const PduInfoType* info,PduLengthType TpSduLength,PduLengthType* RxBufferSizePtr)
{
    BufReq_ReturnType Result = BUFREQ_OK;
   uint8 idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

   if(DCM_OBD_IDLE == Dcm_Lok_GetOBDState())
   {
        Dcm_Lok_ReceiveNewReqWhenOBDIdle(DcmRxPduId,info,TpSduLength,idxProtocol_u8);
   }
   else{
        Result = (FALSE != Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b)?BUFREQ_OK:BUFREQ_E_NOT_OK;
   }

   if(BUFREQ_OK == Result)
   {
        *(RxBufferSizePtr) = (PduLengthType)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
   }

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
   if( (Result == BUFREQ_OK) && (DcmRxPduId == (DCM_CFG_NUM_RX_PDUID-1u)))
   {
        Dcm_isObdRequestReceived_b = TRUE;
   }
#endif
    return Result;
}

#endif

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

static BufReq_ReturnType Dcm_Lok_PremptionHandling(
        const Dcm_Dsld_protocol_tableType * ArrivedProtocol_pcst
   ,       PduLengthType TpSduLength,PduIdType RxpduId)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   uint8 idxProtocol_u8  = Dcm_DsldGlobal_st.idxCurrentProtocol_u8;
   uint8 connectionId_u8 = 0u;

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

            Dcm_Lok_SetDslPreemptionState((DSL_SUBSTATE_STOP_PROTOCOL_RECEIVING));

            Dcm_Lok_SetDslState((DSL_STATE_WAITING_FOR_RXINDICATION));
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

static boolean Dcm_Lok_CheckFunctionalTesterPresent( PduIdType DcmRxPduId
   ,       const PduInfoType * infoPtr
   ,       PduLengthType TpSduLength)
{
   boolean isFuncTesterPresent_b = FALSE;

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

static BufReq_ReturnType Dcm_Lok_InformApplication(PduIdType DcmRxPduId
   ,       const PduInfoType * infoPtr,PduLengthType TpSduLength
   ,       PduLengthType * RxBufferSizePtr
   ,       BufReq_ReturnType BufRequestStatus_en)
{
   uint8 connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   uint8 idxProtocol_u8  = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

   if(BUFREQ_OK == BufRequestStatus_en)
   {
        *(RxBufferSizePtr) = (PduLengthType)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);

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
           (void)DcmAppl_StartOfReception(infoPtr->SduDataPtr[0],DcmRxPduId,TpSduLength,(Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslRxPduBuffer_st.SduDataPtr));
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

            *(RxBufferSizePtr) = (PduLengthType)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);

            Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_RUNNING;
            BufRequestStatus_en = BUFREQ_OK;

            SchM_Exit_Dcm_Global_NoNest();
        }
   }
#endif

    return BufRequestStatus_en;
}

static BufReq_ReturnType Dcm_Lok_ProcessNoRequest( PduIdType DcmRxPduId
   ,       const PduInfoType * infoPtr,PduLengthType TpSduLength,

        PduLengthType * RxBufferSizePtr)
{
    (void)DcmRxPduId;
    (void)infoPtr;
    (void)TpSduLength;
    (void)RxBufferSizePtr;

    return BUFREQ_OK;
}

static BufReq_ReturnType Dcm_Lok_ProcessRequest_CheckPriority( PduIdType DcmRxPduId
   ,       const PduInfoType * infoPtr,PduLengthType TpSduLength
   ,       PduLengthType * RxBufferSizePtr)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   uint8 connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   uint8 idxProtocol_u8  = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

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

static BufReq_ReturnType Dcm_Lok_ProcessRequestWhileRoeEvent(
        PduIdType DcmRxPduId,PduLengthType TpSduLength)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   uint8 connectionId_u8  = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   uint8 idxProtocol_u8   = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

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

static BufReq_ReturnType Dcm_Lok_ProcessRequestWhileDslBusy( PduIdType DcmRxPduId
   ,       const PduInfoType * infoPtr,PduLengthType TpSduLength
   ,       PduLengthType * RxBufferSizePtr)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   uint8 connectionId_u8  = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   uint8 idxProtocol_u8   = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

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

static BufReq_ReturnType Dcm_Lok_ProcessRequestWhileDslFree( PduIdType DcmRxPduId
   ,       const PduInfoType * infoPtr,PduLengthType TpSduLength
   ,       PduLengthType * RxBufferSizePtr)
{

   uint8 connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   uint8 idxProtocol_u8  = Dcm_DsldConnTable_pcst[connectionId_u8].protocol_num_u8;

    SchM_Enter_Dcm_Global_NoNest();

    Dcm_Lok_SetDslState((DSL_STATE_WAITING_FOR_RXINDICATION));

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

static uint8 Dcm_Lok_ValidateRequestType( PduIdType DcmRxPduId
   ,       const PduInfoType * infoPtr,PduLengthType TpSduLength)
{
   uint8 connectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
   uint8 requestType_u8  = DCM_PROCESS_NO_REQUEST;
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

static boolean Dcm_Lok_ProcessSharedRxPduid(PduIdType * RxPduIdPtr
   ,       const PduInfoType * infoPtr)
{
   boolean processStatus_b  = TRUE;
   uint8 idxProtocol_u8  = 0u;
   uint8 protocolId_u8   = 0u;

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

static Std_ReturnType Dcm_Lok_CheckPermissions(PduIdType * RxPduIdPtr
   ,               const PduInfoType * infoPtr,PduLengthType TpSduLength)
{
    Std_ReturnType permissionsStatus  = E_NOT_OK;
   uint8 connectionId_u8 = 0u;
   uint8 idxProtocol_u8  = 0u;
   PduIdType rxPduid     = 0u;

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

static boolean Dcm_Lok_StartOfReception_CheckEnvironment(PduIdType DcmRxPduId
   ,       const PduInfoType * infoPtr
   ,       const PduLengthType * RxBufferSizePtr)
{
   boolean environmentStatus_b = FALSE;

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

static void Dcm_Lok_UpdateRxPduArrayForValidRequest(PduIdType id)
{
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
    // If the requested RxPduId is configured for an OBD Protocol
   if(Dcm_Lok_IsRxPduIdOBD(id))
   {
        SchM_Enter_Dcm_Global_NoNest();
        Dcm_DslOBDRxPduArray_ast[id].Dcm_DslCopyRxData_b  = FALSE;
        Dcm_DslOBDRxPduArray_ast[id].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
        SchM_Exit_Dcm_Global_NoNest();
   }
   else
#endif
   {
        SchM_Enter_Dcm_Global_NoNest();
        Dcm_DslRxPduArray_ast[id].Dcm_DslCopyRxData_b  = FALSE;
        Dcm_DslRxPduArray_ast[id].Dcm_DslServiceId_u8 = DCM_SERVICEID_DEFAULT_VALUE;
        SchM_Exit_Dcm_Global_NoNest();
   }
}

BufReq_ReturnType Dcm_StartOfReception(PduIdType id
   ,               const PduInfoType * info,PduLengthType TpSduLength
   ,               PduLengthType * bufferSizePtr)
{
    BufReq_ReturnType bufRequestStatus_en = BUFREQ_E_NOT_OK;
   uint8 idxProtocol_u8    = 0u;

if(FALSE != Dcm_Lok_StartOfReception_CheckEnvironment(id,info,bufferSizePtr))
   {
        if(E_OK == Dcm_Lok_CheckPermissions(&id,info,TpSduLength))
        {
            idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[id]].protocol_num_u8;
            Dcm_Lok_UpdateRxPduArrayForValidRequest(id);

            if(TpSduLength == 0u)
            {
                *(bufferSizePtr) = (PduLengthType)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
                bufRequestStatus_en = BUFREQ_OK;
            }

            else if((Dcm_MsgLenType)TpSduLength > Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32)
            {
                bufRequestStatus_en = BUFREQ_E_OVFL;
            }
            else{
#if(DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
                // For a request on OBD protocol, handle it separately in parallel to other protocol requests.
                if(Dcm_Lok_IsRxPduIdOBD(id))
                {
                    bufRequestStatus_en = Dcm_Lok_ProcessNewObdRequest(id,info,TpSduLength,bufferSizePtr);
                }
                else
#endif
                {
                    bufRequestStatus_en = Dcm_Lok_RxProcessRequest(id,info,TpSduLength,bufferSizePtr);
                }
            }
        }
   }
    return (bufRequestStatus_en);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

