

#include "PduR_Prv.h"
#include "Dem.h"
#if(PDUR_ENABLE_INTER_MODULE_CHECKS)
#if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_BufferPool.h"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_GF_Tp_StartOfReception_Func(PduIdType gwId, const PduInfoType* info,PduLengthType TpSduLength, PduLengthType* bufferSizePtr)
{

    PduR_GT_TpPtr gt;
    const PduR_FIFO_Tp_fixed * fifo;
    BufReq_ReturnType rtn;
    PduR_TpSessDynPtr SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;

    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    rtn = BUFREQ_OK;
    ConnectionPtr = fifo->connectionTable;

    SessionPtr = ConnectionPtr->primarySession;

#ifdef PDUR_QUEUEING_SUPPORT
    if (ConnectionPtr->activeSessionCount == 0)
    {

        rtn = PduR_GetTpBuffer(gt,TpSduLength);
        if (rtn != BUFREQ_OK)
        {
            return rtn;
        }

    }

    else if((ConnectionPtr->activeSessionCount == 1) && (gt->TpGwQueueSize == 2u))

    {

        if(SessionPtr->Rx_Status != PDUR_RX_FINISHED)
        {
            return BUFREQ_E_NOT_OK;
        }
        if(TpSduLength > fifo->connectionTable->secondarySession->bufferLength)
        {
#ifdef PDUR_STORE_AND_FORWARD
            return BUFREQ_OK;
#else
            return BUFREQ_E_OVFL;
#endif
        }

            SessionPtr = ConnectionPtr->secondarySession;
    }
    else
    {

        return BUFREQ_E_NOT_OK;
    }

    ConnectionPtr->activeSessionCount++;

#else

    if (SessionPtr->Rx_Status != PDUR_SESSION_IDLE)
    {
#ifdef PDUR_FIFO_TP_SUPPORT
        if (gt->TpQueueDepth_u8 > 1u)
            {

                if(!((SessionPtr->Rx_Status == PDUR_RX_FINISHED) &&
                    (SessionPtr->Rx_FifoInstanceUsed_u8 != SessionPtr->Tx_FifoInstanceUsed_u8)))
                {

                    return BUFREQ_E_NOT_OK;
                }
            }
        else
#endif
        {

            return BUFREQ_E_NOT_OK;
        }
    }
    rtn = PduR_GetTpBuffer(gt,TpSduLength);

    if (rtn != BUFREQ_OK)
    {
        return rtn;
    }

#endif

#ifdef PDUR_FIFO_TP_SUPPORT

    if (SessionPtr->Rx_Status == PDUR_SESSION_IDLE)
#endif
    {

        SessionPtr->readPtr = SessionPtr->bufferPtr;
        SessionPtr->writePtr = SessionPtr->bufferPtr;
    }

    *bufferSizePtr = SessionPtr->bufferLength;

    SessionPtr->SduLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] = TpSduLength;

#ifdef PDUR_STORE_AND_FORWARD
            SessionPtr->remainingBuffLength = SessionPtr->bufferLength;
#endif
#if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)
    {

       if( info != NULL_PTR)
       {

           SessionPtr->infoPtr = info;
       }
       else
       {

           SessionPtr->infoPtr = NULL_PTR;
       }

    }
#else
    {

         (void) info ;
    }
#endif

    SessionPtr->Rx_Status = PDUR_RX_INPROGRESS;
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

BufReq_ReturnType PduR_GF_Tp_CopyRxData_Func( PduIdType gwId, const PduInfoType* info, PduLengthType* bufferSizePtr)
{

    PduR_GT_TpPtr gt;
    const PduR_FIFO_Tp_fixed * fifo;
    PduR_TpSessDynPtr SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;

    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = fifo->connectionTable;

    PduR_LoadActiveSession(&SessionPtr,ConnectionPtr);

    if ((SessionPtr == NULL_PTR) || (SessionPtr->Rx_Status != PDUR_RX_INPROGRESS) || (info->SduLength > (SessionPtr->SduLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] - SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8])))
    {
        return BUFREQ_E_NOT_OK;
    }

    if ( info->SduLength == 0u )
    {
        *bufferSizePtr = PduR_UpdateBuffSizePtr(SessionPtr);
        return BUFREQ_OK;
    }

#ifdef PDUR_STORE_AND_FORWARD

    if((SessionPtr->RxChunkLength == SessionPtr->bufferLength) && (((SessionPtr->RxChunkLength - SessionPtr->TxChunkLength) != 0u) || (SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] == SessionPtr->numTxLength)))
    {

        SessionPtr->writePtr = SessionPtr->bufferPtr;
        SessionPtr->RxChunkLength = 0;
        SessionPtr->remainingBuffLength = SessionPtr->TxChunkLength;
    }

    if(info->SduLength > SessionPtr->remainingBuffLength)
    {

        return BUFREQ_E_NOT_OK;
    }
    else if(SessionPtr->TxChunkLength > SessionPtr->RxChunkLength)
    {

        rba_BswSrv_MemCopy8(SessionPtr->writePtr,info->SduDataPtr,info->SduLength);

        SessionPtr->writePtr += info->SduLength;

        SessionPtr->RxChunkLength += info->SduLength;

        SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] += info->SduLength;

        SessionPtr->remainingBuffLength = SessionPtr->TxChunkLength - SessionPtr->RxChunkLength;
    }

    else if((SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] == SessionPtr->numTxLength) || (SessionPtr->RxChunkLength > SessionPtr->TxChunkLength))
    {
        PduLengthType availableBuffLength_l;
        availableBuffLength_l = SessionPtr->bufferLength - SessionPtr->RxChunkLength;
        if(info->SduLength > availableBuffLength_l)
        {

              rba_BswSrv_MemCopy8(SessionPtr->writePtr,info->SduDataPtr,availableBuffLength_l);

              SessionPtr->writePtr = SessionPtr->bufferPtr;
              SessionPtr->RxChunkLength = 0;
              rba_BswSrv_MemCopy8(SessionPtr->writePtr,(info->SduDataPtr + availableBuffLength_l),(info->SduLength - availableBuffLength_l));
              SessionPtr->writePtr += (info->SduLength - availableBuffLength_l);
              SessionPtr->RxChunkLength += (info->SduLength - availableBuffLength_l);

              SessionPtr->remainingBuffLength = SessionPtr->TxChunkLength - SessionPtr->RxChunkLength;
        }
        else
        {
            rba_BswSrv_MemCopy8(SessionPtr->writePtr,info->SduDataPtr,info->SduLength);

            SessionPtr->writePtr += info->SduLength;

            SessionPtr->RxChunkLength += info->SduLength;

            SessionPtr->remainingBuffLength = ((SessionPtr->bufferLength - SessionPtr->RxChunkLength) + SessionPtr->TxChunkLength);

        }

        SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] += info->SduLength;

    }
    else
    {

    }

    *bufferSizePtr = SessionPtr->remainingBuffLength;
#else

        rba_BswSrv_MemCopy8(SessionPtr->writePtr,info->SduDataPtr,info->SduLength);

        SessionPtr->writePtr += info->SduLength;

        SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] += info->SduLength;

        *(bufferSizePtr) = SessionPtr->bufferLength - SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8];

#endif

#ifdef PDUR_QUEUEING_SUPPORT

    if(SessionPtr == ConnectionPtr->secondarySession)
    {
        return BUFREQ_OK;
    }
#endif

    if(!((SessionPtr->Tx_Status == PDUR_TX_IDLE) &&
            ((SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] >= gt->TpThreshold) ||
             ((gt->TpThreshold == PDUR_TPTHRESHOLD_DEFVALUE) &&
               (SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] == SessionPtr->bufferLength)))))
     {

            return BUFREQ_OK;
     }
     else
     {

        PduInfoType readerPduInfo;
        Std_ReturnType Ret_val = E_OK;

          readerPduInfo.SduDataPtr = SessionPtr->readPtr;

          readerPduInfo.SduLength = SessionPtr->SduLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8];

         SessionPtr->Tx_Status = PDUR_TX_INPROGRESS;

         #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
         Ret_val = PDUR_BASE_RPTBL(loTxTablePtr)[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
         #else
         Ret_val = PduR_loTransmitTable[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
         #endif

         if(Ret_val != E_OK)
         {

             SessionPtr->Tx_Status = PDUR_TX_IDLE;

              return BUFREQ_E_NOT_OK;
          }
       }

    return BUFREQ_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

void PduR_GF_Tp_RxIndication_Func( PduIdType gwId, Std_ReturnType result)
{

    PduR_GT_TpPtr gt;
    const PduR_FIFO_Tp_fixed * fifo;
    PduR_TpSessDynPtr SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;

    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = (PduR_TpConnDynPtr)(fifo->connectionTable);

    PduR_LoadActiveSession(&SessionPtr,ConnectionPtr);

    if ((SessionPtr == NULL_PTR) || (SessionPtr->Rx_Status != PDUR_RX_INPROGRESS))
    {

        return;
    }

    if (result == E_OK)
    {

         SessionPtr->Rx_Status = PDUR_RX_FINISHED;

         if(ConnectionPtr->primarySession->Tx_Status == PDUR_TX_IDLE)
         {
             VAR(PduInfoType,AUTOMATIC) readerPduInfo;

             readerPduInfo.SduDataPtr = SessionPtr->readPtr;

             readerPduInfo.SduLength = SessionPtr->SduLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8];

             SessionPtr->Tx_Status = PDUR_TX_INPROGRESS;

             #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
             PDUR_BASE_RPTBL(loTxTablePtr)[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
             #else
             PduR_loTransmitTable[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
             #endif
         }
#ifdef PDUR_FIFO_TP_SUPPORT
        if(gt->TpQueueDepth_u8 > 1u)
        {

            SessionPtr->Rx_FifoInstanceUsed_u8++;
            SessionPtr->writePtr = gt->buffer->begin;

            if(SessionPtr->Rx_FifoInstanceUsed_u8 != gt->TpQueueDepth_u8)
            {

                PduLengthType RxInstanceLength_l;
                RxInstanceLength_l = (PduLengthType)((SessionPtr->Rx_FifoInstanceUsed_u8)*(SessionPtr->bufferLength));

                SessionPtr->writePtr += RxInstanceLength_l;
            }
            else
            {

                SessionPtr->Rx_FifoInstanceUsed_u8 = 0;
            }
         }
#endif
    }

    else
    {
#ifdef PDUR_FIFO_TP_SUPPORT

        if(gt->TpQueueDepth_u8 > 1u)
        {

            PduLengthType RxInstanceLength_l;

            SessionPtr->writePtr = gt->buffer->begin;
            RxInstanceLength_l = (PduLengthType)((SessionPtr->Rx_FifoInstanceUsed_u8)*(SessionPtr->bufferLength));

            SessionPtr->writePtr += RxInstanceLength_l;

            SessionPtr->numRxLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8] = 0u;
            SessionPtr->SduLength_auo[SessionPtr->Rx_FifoInstanceUsed_u8]   = 0u;

            if((SessionPtr->Rx_FifoInstanceUsed_u8 == 0u) && (SessionPtr->Tx_FifoInstanceUsed_u8 == 0u))
            {

                SessionPtr->Rx_Status = PDUR_SESSION_IDLE;
            }
            else
            {

                SessionPtr->Rx_Status = PDUR_RX_FINISHED;
            }

            if((SessionPtr->Rx_FifoInstanceUsed_u8 == SessionPtr->Tx_FifoInstanceUsed_u8) && (SessionPtr->Tx_Status == PDUR_TX_INPROGRESS))
            {
                SessionPtr->Tx_Status = PDUR_TX_IDLE;

            }
             else
            {

            }
        }
        else
#endif
        {

#ifdef PDUR_QUEUEING_SUPPORT

        if(ConnectionPtr->activeSessionCount != 0)
        {
            ConnectionPtr->activeSessionCount--;

            if(ConnectionPtr->activeSessionCount == 0)
            {
                PduR_ReleaseTpBuffer(gt);
            }
        }
#else

        PduR_ReleaseTpBuffer(gt);

#endif

        PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr, gt);
        }
    }
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

