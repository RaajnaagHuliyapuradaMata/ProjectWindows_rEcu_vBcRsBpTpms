#ifndef PDUR_GW_H
#define PDUR_GW_H

#include "PduR_Cfg_Internal.hpp"
#include "PduR_Types.hpp"
#include "rba_BswSrv.hpp"

#define PDUR_SESSION_IDLE                0x00
#define PDUR_RX_INPROGRESS               0x01
#define PDUR_RX_FINISHED                 0x02
#define PDUR_TX_IDLE                     0x10
#define PDUR_TX_INPROGRESS               0x20

LOCAL_INLINE Type_SwcServiceCom_tLengthPdu PduR_UpdateBuffSizePtr(PduR_TpSession_Dynamic * dyn);
LOCAL_INLINE void PduR_InitializePduR_Gw_If_DynStruct(PduR_FIFO_If_dynamic * dyn, const PduR_FIFO_fixed * fifo);
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ResetPduR_FIFO_Tp_dynamic_Structure(P2VAR(PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR) dyn);
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_LoadActiveSession(P2VAR(PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR) *SessionPtr, P2CONST(PduR_TpConnection_Dynamic, TYPEDEF, PDUR_VAR) ConnectionPtr);
extern FUNC(void, PDUR_CODE) PduR_GF_If_RxIndication_Func(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) data );
extern FUNC(void, PDUR_CODE) PduR_GF_DDIf_FIFO_TxConfirmation_Func( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId);
extern FUNC(void, PDUR_CODE) PduR_GF_DDIf_NoBuf_TxConfirmation_Func(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId);
extern FUNC(void, PDUR_CODE) PduR_GF_TTIf_Buf_TxConfirmation_Func(  VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId);
extern FUNC(void, PDUR_CODE) PduR_GF_TTIf_FIFO_TxConfirmation_Func( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId);
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_DDIf_FIFO_Transmit_Func(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info );
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_TTIf_Buf_Transmit_Func( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info );
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_TTIf_FIFO_Transmit_Func(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info );
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_TTIf_Buf_TriggerTransmit_Func( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId, P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) dataPtr);
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_TTIf_FIFO_TriggerTransmit_Func(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwayId, P2VAR(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) dataPtr);
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GwMcTx_Transmit_Func(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info);
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_Com_Transmit_Func( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info);
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_IpduM_Transmit_Func( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info);
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_SecOC_Transmit_Func( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id, P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info);

extern FUNC( BufReq_ReturnType, PDUR_CODE) PduR_GF_Tp_StartOfReception_Func(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) gwId
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF,PDUR_APPL_DATA ) info
   ,      VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC              ) TpSduLength
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr
);

extern FUNC( BufReq_ReturnType, PDUR_CODE) PduR_GF_Tp_CopyRxData_Func(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) gwId
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF, PDUR_APPL_DATA) info
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr
);

extern FUNC(void, PDUR_CODE)  PduR_GF_Tp_RxIndication_Func(
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwId
   ,  VAR(Std_ReturnType,            AUTOMATIC) result
);

extern FUNC( BufReq_ReturnType, PDUR_CODE) PduR_GF_Tp_CopyTxData_Func(
          VAR(Type_SwcServiceCom_tIdPdu,     AUTOMATIC              ) gwId
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu,  TYPEDEF,PDUR_APPL_DATA ) info
   ,    P2VAR(RetryInfoType,                 TYPEDEF, PDUR_APPL_DATA) retry
   ,    P2VAR(Type_SwcServiceCom_tLengthPdu, TYPEDEF, PDUR_APPL_DATA) availableDataPtr
);

extern FUNC(void, PDUR_CODE) PduR_GF_Tp_TxConfirmation_Func ( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) gwId
   ,  VAR(Std_ReturnType, AUTOMATIC) result
);

LOCAL_INLINE void PduR_InitializePduR_Gw_If_DynStruct(
   PduR_FIFO_If_dynamic* dyn
   , const PduR_FIFO_fixed* fifo
){
   uint8 indexArr_8;
   dyn->writePtr = fifo->begin;
   dyn->readPtr = fifo->begin;
   for(indexArr_8 = 0; indexArr_8 < fifo->nrElts; indexArr_8++){
      dyn->actLen[indexArr_8] = 0;
   }
   dyn->used = 0;
   dyn->txConfPending = 0;
   dyn->readIndex = 0;
   dyn->writeIndex = 0;
}

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ResetPduR_FIFO_Tp_dynamic_Structure(
   P2VAR(PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR) dyn
){
   dyn->Rx_Status = PDUR_SESSION_IDLE;
   dyn->Tx_Status = PDUR_TX_IDLE;
   dyn->readPtr = NULL_PTR;
   dyn->writePtr = NULL_PTR;
   dyn->numTxLength = 0;
   dyn->Tx_E_OK_Count = 0;
   dyn->Rx_FifoInstanceUsed_u8 = 0;
   dyn->Tx_FifoInstanceUsed_u8 = 0;
   dyn->SduLength_auo[0]   = 0;
   dyn->numRxLength_auo[0] = 0;
   (void)gwTpTablePtr;
}

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_LoadActiveSession(
        P2VAR(PduR_TpSession_Dynamic,    TYPEDEF, PDUR_VAR)* SessionPtr
   ,  P2CONST(PduR_TpConnection_Dynamic, TYPEDEF, PDUR_VAR)  ConnectionPtr
){
   *SessionPtr = (ConnectionPtr->primarySession);
}

LOCAL_INLINE Type_SwcServiceCom_tLengthPdu PduR_UpdateBuffSizePtr(
   PduR_TpSession_Dynamic* dyn
){
   Type_SwcServiceCom_tLengthPdu  CurrentBufferLength_l;
   CurrentBufferLength_l = dyn->bufferLength - dyn->numRxLength_auo[dyn->Rx_FifoInstanceUsed_u8];
   return CurrentBufferLength_l;
}

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_GF_TP_Dcm_Transmit_Func(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC              ) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, TYPEDEF, PDUR_APPL_DATA) info
);

extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_GetTpBuffer(
      P2CONST(PduR_GT_Tp,                    TYPEDEF, PDUR_CONST) gt
   ,      VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC          ) TpSduLength
);

extern void PduR_ReleaseTpBuffer(
   const PduR_GT_Tp* gt
);
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

