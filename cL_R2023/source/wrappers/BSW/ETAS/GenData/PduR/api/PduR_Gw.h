

#ifndef PDUR_GW_H
#define PDUR_GW_H

#include "PduR_Cfg_Internal.h"
#include "PduR_Types.h"
#include "rba_BswSrv.h"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_BufferPool.h"
#endif
#define PDUR_SESSION_IDLE                0x00
#define PDUR_RX_INPROGRESS               0x01
#define PDUR_RX_FINISHED                 0x02

#define PDUR_TX_IDLE                     0x10
#define PDUR_TX_INPROGRESS               0x20

LOCAL_INLINE void PduR_InitializePduR_Gw_Tp_Session(PduR_TpSession_Dynamic * dyn, PduR_GT_TpPtr gwTpTablePtr);
LOCAL_INLINE PduLengthType PduR_UpdateBuffSizePtr(PduR_TpSession_Dynamic * dyn);
LOCAL_INLINE void PduR_InitializePduR_Gw_If_DynStruct(PduR_FIFO_If_dynamic * dyn, const PduR_FIFO_fixed * fifo);
LOCAL_INLINE void PduR_ResetPduR_FIFO_Tp_dynamic_Structure(PduR_TpSession_Dynamic * dyn, PduR_GT_TpPtr gwTpTablePtr);
LOCAL_INLINE void PduR_LoadActiveSession(PduR_TpSession_Dynamic * *SessionPtr, const PduR_TpConnection_Dynamic * ConnectionPtr);

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern void PduR_GF_If_RxIndication_Func(PduIdType gwayId, const PduInfoType * data );

#if (AUTOSAR_VERSION_AR42 == STD_ON)
extern void PduR_GF_DDIf_FIFO_TxConfirmation_Func( PduIdType gwayId);
#else
extern void PduR_GF_DDIf_FIFO_TxConfirmation_Func( PduIdType gwayId,Std_ReturnType result);
#endif

#if (AUTOSAR_VERSION_AR42 == STD_ON)
extern void PduR_GF_DDIf_NoBuf_TxConfirmation_Func(PduIdType gwayId);
#else
extern void PduR_GF_DDIf_NoBuf_TxConfirmation_Func(PduIdType gwayId,Std_ReturnType result);
#endif

#if (AUTOSAR_VERSION_AR42 == STD_ON)
extern void PduR_GF_TTIf_Buf_TxConfirmation_Func(  PduIdType gwayId);
#else
extern void PduR_GF_TTIf_Buf_TxConfirmation_Func(  PduIdType gwayId,Std_ReturnType result);
#endif

#if (AUTOSAR_VERSION_AR42 == STD_ON)
extern void PduR_GF_TTIf_FIFO_TxConfirmation_Func( PduIdType gwayId);
#else
extern void PduR_GF_TTIf_FIFO_TxConfirmation_Func( PduIdType gwayId,Std_ReturnType result);
#endif

extern Std_ReturnType PduR_GF_DDIf_FIFO_Transmit_Func(PduIdType id, const PduInfoType * info );

extern Std_ReturnType PduR_GF_TTIf_Buf_Transmit_Func( PduIdType gwayId, const PduInfoType * info );

extern Std_ReturnType PduR_GF_TTIf_FIFO_Transmit_Func(PduIdType gwayId, const PduInfoType * info );

extern Std_ReturnType PduR_GF_TTIf_Buf_TriggerTransmit_Func( PduIdType gwayId, PduInfoType * dataPtr);

extern Std_ReturnType PduR_GF_TTIf_FIFO_TriggerTransmit_Func(PduIdType gwayId, PduInfoType * dataPtr);

extern Std_ReturnType PduR_GwMcTx_Transmit_Func(PduIdType id, const PduInfoType * info);

extern Std_ReturnType PduR_GF_Com_Transmit_Func( PduIdType id, const PduInfoType * info);

extern Std_ReturnType PduR_GF_IpduM_Transmit_Func( PduIdType id, const PduInfoType * info);

extern Std_ReturnType PduR_GF_SecOC_Transmit_Func( PduIdType id, const PduInfoType * info);

extern BufReq_ReturnType PduR_GF_Tp_StartOfReception_Func (  PduIdType gwId,
                                                                                      const PduInfoType * info,
                                                                                      PduLengthType TpSduLength,
                                                                                      PduLengthType * bufferSizePtr);

extern BufReq_ReturnType PduR_GF_Tp_CopyRxData_Func (  PduIdType gwId,
                                                                                                            const PduInfoType * info,
                                                                                                            PduLengthType * bufferSizePtr);

extern void PduR_GF_Tp_RxIndication_Func ( PduIdType gwId,
                                                       Std_ReturnType result);

extern BufReq_ReturnType PduR_GF_Tp_CopyTxData_Func ( PduIdType gwId,
                                                               const PduInfoType * info,
                                                               RetryInfoType * retry,
                                                               PduLengthType * availableDataPtr);

extern void PduR_GF_Tp_TxConfirmation_Func ( PduIdType gwId,
                                                          Std_ReturnType result);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

LOCAL_INLINE void PduR_InitializePduR_Gw_Tp_Session(PduR_TpSession_Dynamic * dyn, PduR_GT_TpPtr gwTpTablePtr)
{

    dyn->bufferPtr = NULL_PTR;
    dyn->readPtr   = NULL_PTR;
    dyn->writePtr  = NULL_PTR;
#if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)
    dyn->infoPtr = NULL_PTR;
#endif
    dyn->numTxLength  = 0;
    dyn->bufferLength = 0;
#ifdef PDUR_STORE_AND_FORWARD
    dyn->remainingBuffLength = 0;
    dyn->RxChunkLength = 0;
    dyn->TxChunkLength = 0;
#endif
    dyn->Rx_Status = PDUR_SESSION_IDLE;
    dyn->Tx_Status = PDUR_TX_IDLE;
    dyn->Tx_E_OK_Count = 0;
    dyn->Rx_FifoInstanceUsed_u8 = 0;
    dyn->Tx_FifoInstanceUsed_u8 = 0;

#ifdef PDUR_FIFO_TP_SUPPORT
    if(gwTpTablePtr->TpQueueDepth_u8 > 1u)
    {
        uint8 index_u8;
        for(index_u8 = 0; index_u8 < gwTpTablePtr->TpQueueDepth_u8; index_u8++)
        {
            dyn->SduLength_auo[index_u8]   = 0;
            dyn->numRxLength_auo[index_u8] = 0;
        }
    }
    else
#endif
    {
        dyn->SduLength_auo[0]   = 0;
        dyn->numRxLength_auo[0] = 0;
        (void)gwTpTablePtr;
    }
}

LOCAL_INLINE void PduR_InitializePduR_Gw_If_DynStruct(PduR_FIFO_If_dynamic * dyn, const PduR_FIFO_fixed * fifo)
        {
             uint8 indexArr_8;

             dyn->writePtr = fifo->begin;
             dyn->readPtr = fifo->begin;
             for(indexArr_8=0; indexArr_8 < fifo->nrElts; indexArr_8++)
             {
                 dyn->actLen[indexArr_8] = 0;
             }

             dyn->used = 0;
             dyn->txConfPending = 0;
             dyn->readIndex = 0;
             dyn->writeIndex = 0;
         }

LOCAL_INLINE void PduR_ResetPduR_FIFO_Tp_dynamic_Structure(PduR_TpSession_Dynamic * dyn, PduR_GT_TpPtr gwTpTablePtr)
{

    dyn->Rx_Status = PDUR_SESSION_IDLE;
    dyn->Tx_Status = PDUR_TX_IDLE;

    dyn->readPtr = NULL_PTR;
    dyn->writePtr = NULL_PTR;
#if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)
    dyn->infoPtr = NULL_PTR;
#endif
    dyn->numTxLength = 0;
#ifdef PDUR_STORE_AND_FORWARD
    dyn->remainingBuffLength = 0;
    dyn->RxChunkLength = 0;
    dyn->TxChunkLength = 0;
#endif
    dyn->Tx_E_OK_Count = 0;
    dyn->Rx_FifoInstanceUsed_u8 = 0;
    dyn->Tx_FifoInstanceUsed_u8 = 0;

#ifdef PDUR_FIFO_TP_SUPPORT
     if(gwTpTablePtr->TpQueueDepth_u8 > 1u)
    {
        uint8 index_u8;
        for(index_u8 = 0; index_u8 < gwTpTablePtr->TpQueueDepth_u8; index_u8++)
        {
            dyn->SduLength_auo[index_u8]   = 0;
            dyn->numRxLength_auo[index_u8] = 0;
        }
    }
    else
#endif
    {
        dyn->SduLength_auo[0]   = 0;
        dyn->numRxLength_auo[0] = 0;
        (void)gwTpTablePtr;
    }
}

LOCAL_INLINE void PduR_LoadActiveSession(PduR_TpSession_Dynamic * *SessionPtr, const PduR_TpConnection_Dynamic * ConnectionPtr)
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

LOCAL_INLINE PduLengthType PduR_UpdateBuffSizePtr(PduR_TpSession_Dynamic * dyn)
{
    PduLengthType  CurrentBufferLength_l;

#ifdef PDUR_STORE_AND_FORWARD

    if((dyn->RxChunkLength == dyn->bufferLength) && (((dyn->RxChunkLength - dyn->TxChunkLength) != 0u) || (dyn->numRxLength_auo[dyn->Rx_FifoInstanceUsed_u8] == dyn->numTxLength)))
    {
         dyn->writePtr = dyn->bufferPtr;
         dyn->RxChunkLength = 0;
         dyn->remainingBuffLength = dyn->TxChunkLength;
    }

    else if(dyn->TxChunkLength > dyn->RxChunkLength)
    {
        dyn->remainingBuffLength = dyn->TxChunkLength - dyn->RxChunkLength;
    }

    else if((dyn->numRxLength_auo[dyn->Rx_FifoInstanceUsed_u8] == dyn->numTxLength) || (dyn->RxChunkLength > dyn->TxChunkLength))
    {
        dyn->remainingBuffLength = ((dyn->bufferLength - dyn->RxChunkLength) + dyn->TxChunkLength);
    }
    else
    {

    }
    CurrentBufferLength_l = dyn->remainingBuffLength;
#else

    CurrentBufferLength_l = dyn->bufferLength - dyn->numRxLength_auo[dyn->Rx_FifoInstanceUsed_u8];

#endif

    return CurrentBufferLength_l;
}

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern Std_ReturnType PduR_GF_TP_Dcm_Transmit_Func( PduIdType id, const PduInfoType * info);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern BufReq_ReturnType PduR_GetTpBuffer(  const PduR_GT_Tp * gt,
                                                        PduLengthType TpSduLength);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

extern void PduR_ReleaseTpBuffer(  const PduR_GT_Tp * gt);

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

