

#ifndef PDUR_GW_H
#define PDUR_GW_H

#include "PduR_Cfg_Internal.h"
#include "PduR_Types.h"
#include "rba_BswSrv.h"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_BufferPool.h"
#endif
#define PDUR_SESSION_IDLE                0x00
#define PDUR_RX_INPROGRESS              0x01
#define PDUR_RX_FINISHED                0x02

#define PDUR_TX_IDLE                      0x10
#define PDUR_TX_INPROGRESS                0x20

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_InitilizePduR_Gw_Tp_Session(P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) dyn);
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_InitilizePduR_Gw_If_DynStruct(P2VAR( PduR_FIFO_If_dynamic , TYPEDEF, PDUR_VAR ) dyn, P2CONST( PduR_FIFO_fixed, TYPEDEF, PDUR_CONST ) fifo);
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ResetPduR_FIFO_Tp_dynamic_Structure(P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) dyn);
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_LoadActiveSession(P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) *SessionPtr, P2CONST( PduR_TpConnection_Dynamic, TYPEDEF, PDUR_VAR ) ConnectionPtr);
LOCAL_INLINE FUNC(PduLengthType, PDUR_CODE) PduR_UpdateBuffSizePtr(P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) dyn);

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern FUNC( void, PDUR_CODE ) PduR_GF_If_RxIndication_Func(VAR(PduIdType, AUTOMATIC) gwayId, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) data );

extern FUNC( void, PDUR_CODE ) PduR_GF_DDIf_FIFO_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) gwayId);

extern FUNC( void, PDUR_CODE ) PduR_GF_DDIf_NoBuf_TxConfirmation_Func(VAR(PduIdType, AUTOMATIC) gwayId);

extern FUNC( void, PDUR_CODE ) PduR_GF_TTIf_Buf_TxConfirmation_Func(  VAR(PduIdType, AUTOMATIC) gwayId);

extern FUNC( void, PDUR_CODE ) PduR_GF_TTIf_FIFO_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) gwayId);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_DDIf_FIFO_Transmit_Func(VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info );

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_Buf_Transmit_Func( VAR(PduIdType, AUTOMATIC) gwayId, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info );

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_FIFO_Transmit_Func(VAR(PduIdType, AUTOMATIC) gwayId, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info );

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_Buf_TriggerTransmit_Func( VAR(PduIdType, AUTOMATIC) gwayId, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) dataPtr);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_FIFO_TriggerTransmit_Func(VAR(PduIdType, AUTOMATIC) gwayId, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) dataPtr);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GwMcTx_Transmit_Func(VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_Com_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_IpduM_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_SecOC_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info);

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_StartOfReception_Func (  VAR(PduIdType, AUTOMATIC) gwId,
                                                                                      P2CONST(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
                                                                                      VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                                      P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_CopyRxData_Func (  VAR(PduIdType, AUTOMATIC) gwId,
                                                                                                            P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
                                                                                                            P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);

extern FUNC( void, PDUR_CODE )  PduR_GF_Tp_RxIndication_Func ( VAR(PduIdType, AUTOMATIC) gwId,
                                                       VAR(Std_ReturnType, AUTOMATIC) result);

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_CopyTxData_Func ( VAR(PduIdType, AUTOMATIC) gwId,
                                                               P2CONST(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
                                                               P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                               P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr);

extern FUNC( void, PDUR_CODE ) PduR_GF_Tp_TxConfirmation_Func ( VAR(PduIdType, AUTOMATIC) gwId,
                                                          VAR(Std_ReturnType, AUTOMATIC) result);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_InitilizePduR_Gw_Tp_Session(P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) dyn)
        {

            dyn->bufferPtr = NULL_PTR;
            dyn->readPtr = NULL_PTR;
            dyn->writePtr = NULL_PTR;
#if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)
            dyn->infoPtr = NULL_PTR;
#endif
            dyn->SduLength = 0;
            dyn->numRxLength = 0;
            dyn->numTxLength = 0;
            dyn->bufferLength = 0;
#ifdef PDUR_STORE_AND_FORWARD
            dyn->remainingBuffLength = 0;
            dyn->RxChunkLength = 0;
            dyn->TxChunkLength = 0;
#endif
            dyn->Rx_Status = PDUR_SESSION_IDLE;
            dyn->Tx_Status = PDUR_TX_IDLE;
            dyn->Tx_E_OK_Count = 0;
        }

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_InitilizePduR_Gw_If_DynStruct(P2VAR( PduR_FIFO_If_dynamic , TYPEDEF, PDUR_VAR ) dyn, P2CONST( PduR_FIFO_fixed, TYPEDEF, PDUR_CONST ) fifo)
        {

             dyn->writePtr = fifo->begin;
             dyn->readPtr = fifo->begin;
             dyn->actLen = 0;
             dyn->used = 0;
             dyn->txConfPending = 0;
        }

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_ResetPduR_FIFO_Tp_dynamic_Structure(P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) dyn)
        {

            dyn->Rx_Status = PDUR_SESSION_IDLE;
            dyn->Tx_Status = PDUR_TX_IDLE;

            dyn->readPtr = NULL_PTR;
            dyn->writePtr = NULL_PTR;
#if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)
            dyn->infoPtr = NULL_PTR;
#endif
            dyn->SduLength = 0;
            dyn->numRxLength = 0;
            dyn->numTxLength = 0;
#ifdef PDUR_STORE_AND_FORWARD
            dyn->remainingBuffLength = 0;
            dyn->RxChunkLength = 0;
            dyn->TxChunkLength = 0;
#endif
            dyn->Tx_E_OK_Count = 0;

        }

LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_LoadActiveSession(P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) *SessionPtr, P2CONST( PduR_TpConnection_Dynamic, TYPEDEF, PDUR_VAR ) ConnectionPtr)
        {

#ifdef PDUR_QUEUEING_SUPPORT

            uint8 activeSessionCount;
            activeSessionCount = ConnectionPtr->activeSessionCount;
            if(activeSessionCount == 1)
            {

                *SessionPtr = (ConnectionPtr->primarySession);
            }

            else if(activeSessionCount == 2)
            {

                *SessionPtr = (ConnectionPtr->secondarySession);
            }

            else
            {
                *SessionPtr = NULL_PTR;
            }
#else

            *SessionPtr = (ConnectionPtr->primarySession);

#endif

        }

LOCAL_INLINE FUNC(PduLengthType, PDUR_CODE) PduR_UpdateBuffSizePtr(P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) dyn)
        {
    PduLengthType  CurrentBufferLength_l;
#ifdef PDUR_STORE_AND_FORWARD

         if((dyn->RxChunkLength == dyn->bufferLength) && (((dyn->RxChunkLength - dyn->TxChunkLength) != 0u) || (dyn->numRxLength == dyn->numTxLength)))
         {
             dyn->writePtr = dyn->bufferPtr;
             dyn->RxChunkLength = 0;
             dyn->remainingBuffLength = dyn->TxChunkLength;
         }

         else if(dyn->TxChunkLength > dyn->RxChunkLength)
         {
             dyn->remainingBuffLength = dyn->TxChunkLength - dyn->RxChunkLength;
         }

         else if((dyn->numRxLength == dyn->numTxLength) || (dyn->RxChunkLength > dyn->TxChunkLength))
         {
             dyn->remainingBuffLength = dyn->bufferLength - dyn->RxChunkLength;
         }
         else
         {

         }
         CurrentBufferLength_l = dyn->remainingBuffLength;
#else

         CurrentBufferLength_l = dyn->bufferLength - dyn->numRxLength;
#endif
         return CurrentBufferLength_l;

}

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TP_Dcm_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GetTpBuffer(  P2CONST( PduR_GT_Tp, TYPEDEF, PDUR_CONST ) gt,
                                                        VAR(PduLengthType, AUTOMATIC) TpSduLength);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern FUNC( void, PDUR_CODE ) PduR_ReleaseTpBuffer(  P2CONST( PduR_GT_Tp, TYPEDEF, PDUR_CONST ) gt);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

