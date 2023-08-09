

#include "PduR_Prv.h"
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#include "PduR_BufferPool.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GetTpBuffer(  P2CONST( PduR_GT_Tp, TYPEDEF, PDUR_CONST ) gt,
                                                                    VAR(PduLengthType, AUTOMATIC) TpSduLength)
{

    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;

    PduR_TpSessDynPtr  SessionPtr;
    VAR(BufReq_ReturnType, AUTOMATIC)  rtn;

    fifo = (gt->buffer);
    SessionPtr = fifo->connectionTable->primarySession;
    rtn = BUFREQ_OK;

#ifdef PDUR_BUFFERPOOL_SUPPORT

    if((fifo->begin != NULL_PTR) && (fifo->buffPoolId == 0xFFFFu))
    {
        if (TpSduLength > fifo->eltSize)
        {
#ifdef PDUR_STORE_AND_FORWARD

            fifo->connectionTable->primarySession->bufferPtr = fifo->begin;
            fifo->connectionTable->primarySession->bufferLength = fifo->eltSize;
#else
            rtn =  BUFREQ_E_OVFL;
#endif

        }
        else
        {
            fifo->connectionTable->primarySession->bufferPtr = fifo->begin;
            fifo->connectionTable->primarySession->bufferLength = fifo->eltSize;
        }
    }

    else
    {

        SchM_Enter_PduR_LockTpGatewayBuffer();

        rtn = PduR_BufferPoolRequest(fifo->buffPoolId, TpSduLength, &SessionPtr->bufferLength, &SessionPtr->bufferPtr);

#ifdef PDUR_QUEUEING_SUPPORT

        if ((rtn == BUFREQ_OK) && (gt->TpGwQueueSize == 2u))
        {

            SessionPtr = fifo->connectionTable->secondarySession;
            rtn = PduR_BufferPoolRequest(fifo->buffPoolId, TpSduLength, &SessionPtr->bufferLength, &SessionPtr->bufferPtr);

            if (rtn != BUFREQ_OK)
            {

                PduR_ReleaseTpBuffer(gt);
            }
        }
#endif

        SchM_Exit_PduR_LockTpGatewayBuffer();
    }
#else

    if (TpSduLength > fifo->eltSize)
    {
#ifdef PDUR_STORE_AND_FORWARD

        fifo->connectionTable->primarySession->bufferPtr = fifo->begin;
        fifo->connectionTable->primarySession->bufferLength = fifo->eltSize;
#else
            rtn =  BUFREQ_E_OVFL;
#endif
    }
    else
    {
        fifo->connectionTable->primarySession->bufferPtr = fifo->begin;
        fifo->connectionTable->primarySession->bufferLength = fifo->eltSize;
    }
#endif
    return rtn;

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_ReleaseTpBuffer(  P2CONST( PduR_GT_Tp, TYPEDEF, PDUR_CONST ) gt)
{
#ifdef PDUR_BUFFERPOOL_SUPPORT

    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    PduR_TpSessDynPtr  SessionPtr;

    fifo = (gt->buffer);

    if (fifo->buffPoolId != 0xFFFFu)
    {

        SchM_Enter_PduR_LockTpGatewayBuffer();

        SessionPtr = fifo->connectionTable->primarySession;
        PduR_BufferPoolRelease(fifo->buffPoolId, SessionPtr->bufferPtr);
        SessionPtr->bufferPtr = NULL_PTR;

#ifdef PDUR_QUEUEING_SUPPORT

        if (gt->TpGwQueueSize == 2u)
        {
            SessionPtr = fifo->connectionTable->secondarySession;
            PduR_BufferPoolRelease(fifo->buffPoolId, SessionPtr->bufferPtr);
            SessionPtr->bufferPtr = NULL_PTR;
        }
#endif

        SchM_Exit_PduR_LockTpGatewayBuffer();
    }
#endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

