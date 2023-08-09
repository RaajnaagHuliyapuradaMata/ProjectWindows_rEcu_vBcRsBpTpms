

#include "PduR_Prv.h"
#include "Dem.h"
#if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_BufferPool.h"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_StartOfReception_Func( VAR(PduIdType, AUTOMATIC) gwId,
        P2CONST(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
        VAR(PduLengthType, AUTOMATIC) TpSduLength,
        P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{

    PduR_GT_TpPtr gt;
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    VAR(BufReq_ReturnType, AUTOMATIC) rtn;
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
        return BUFREQ_E_NOT_OK;
    }
    rtn = PduR_GetTpBuffer(gt,TpSduLength);

    if (rtn != BUFREQ_OK)
    {
        return rtn;
    }

#endif

    SessionPtr->readPtr = SessionPtr->bufferPtr;
    SessionPtr->writePtr = SessionPtr->bufferPtr;

    *bufferSizePtr = SessionPtr->bufferLength;

    SessionPtr->SduLength = TpSduLength;

#ifdef PDUR_STORE_AND_FORWARD
            SessionPtr->remainingBuffLength = SessionPtr->bufferLength;
#endif
#if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)
    {

        SessionPtr->infoPtr = info;
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

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_CopyRxData_Func( VAR(PduIdType, AUTOMATIC) gwId,
        P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
        P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{

    PduR_GT_TpPtr gt;
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    PduR_TpSessDynPtr SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;

    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = fifo->connectionTable;

    PduR_LoadActiveSession(&SessionPtr,ConnectionPtr);

    if ((SessionPtr == NULL_PTR) || (SessionPtr->Rx_Status != PDUR_RX_INPROGRESS) || (info->SduLength > (SessionPtr->SduLength - SessionPtr->numRxLength)))
    {
        return BUFREQ_E_NOT_OK;
    }

    if ( info->SduLength == 0u )
    {
        *bufferSizePtr = PduR_UpdateBuffSizePtr(SessionPtr);
        return BUFREQ_OK;
    }

#ifdef PDUR_STORE_AND_FORWARD

    if((SessionPtr->RxChunkLength == SessionPtr->bufferLength) && (((SessionPtr->RxChunkLength - SessionPtr->TxChunkLength) != 0u) || (SessionPtr->numRxLength == SessionPtr->numTxLength)))
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

        SessionPtr->numRxLength += info->SduLength;

        SessionPtr->remainingBuffLength = SessionPtr->TxChunkLength - SessionPtr->RxChunkLength;
    }

    else if((SessionPtr->numRxLength == SessionPtr->numTxLength) || (SessionPtr->RxChunkLength > SessionPtr->TxChunkLength))
    {

        rba_BswSrv_MemCopy8(SessionPtr->writePtr,info->SduDataPtr,info->SduLength);

        SessionPtr->writePtr += info->SduLength;

        SessionPtr->RxChunkLength += info->SduLength;

        SessionPtr->numRxLength += info->SduLength;

        SessionPtr->remainingBuffLength = SessionPtr->bufferLength - SessionPtr->RxChunkLength;
    }
    else
    {

    }

    *bufferSizePtr = SessionPtr->remainingBuffLength;
#else

        rba_BswSrv_MemCopy8(SessionPtr->writePtr,info->SduDataPtr,info->SduLength);

        SessionPtr->writePtr += info->SduLength;

        SessionPtr->numRxLength = SessionPtr->numRxLength + info->SduLength;

        *(bufferSizePtr) = SessionPtr->bufferLength - SessionPtr->numRxLength;

#endif

#ifdef PDUR_QUEUEING_SUPPORT

    if(SessionPtr == ConnectionPtr->secondarySession)
    {
        return BUFREQ_OK;
    }
#endif

    if(gt->numOfLowerLayers > 1u)
    {

        if((info->SduLength != SessionPtr->SduLength) || (SessionPtr->Tx_Status != PDUR_TX_IDLE))
            {

                return BUFREQ_E_NOT_OK;

            }
    }

    else  if(!((SessionPtr->Tx_Status == PDUR_TX_IDLE) && ((SessionPtr->numRxLength >= gt->TpThreshold) || ((gt->TpThreshold == PDUR_TPTHRESHOLD_DEFVALUE) && (SessionPtr->numRxLength == SessionPtr->bufferLength)))))
     {

            return BUFREQ_OK;
     }
     else
     {

         VAR(PduInfoType,AUTOMATIC) readerPduInfo;
         VAR(Std_ReturnType, AUTOMATIC) Ret_val = E_OK;

          readerPduInfo.SduDataPtr = SessionPtr->readPtr;

          readerPduInfo.SduLength = SessionPtr->SduLength;

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

FUNC( void, PDUR_CODE ) PduR_GF_Tp_RxIndication_Func( VAR(PduIdType, AUTOMATIC) gwId,
        VAR(Std_ReturnType, AUTOMATIC) result)
{

    PduR_GT_TpPtr gt;
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
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

         if(SessionPtr->Tx_Status == PDUR_TX_IDLE)
         {
             VAR(PduInfoType,AUTOMATIC) readerPduInfo;

             readerPduInfo.SduDataPtr = SessionPtr->readPtr;

             readerPduInfo.SduLength = SessionPtr->SduLength;

             SessionPtr->Tx_Status = PDUR_TX_INPROGRESS;

             #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
             PDUR_BASE_RPTBL(loTxTablePtr)[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
             #else
             PduR_loTransmitTable[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
             #endif
         }
    }
    else
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

        PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);

    }

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

