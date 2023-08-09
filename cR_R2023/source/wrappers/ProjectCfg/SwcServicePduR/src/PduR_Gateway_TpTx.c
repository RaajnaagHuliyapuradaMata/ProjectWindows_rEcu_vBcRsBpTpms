

#include "PduR_Prv.h"
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_BufferPool.h"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_CopyTxData_Func( VAR(PduIdType, AUTOMATIC) gwId,
                                                               P2CONST(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
                                                               P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                               P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr)
{

    PduR_GT_TpPtr      gt;

    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;

    PduR_TpConnDynPtr ConnectionPtr;
    PduR_TpSessDynPtr  SessionPtr;
    VAR(BufReq_ReturnType, AUTOMATIC) rtn;

    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = fifo->connectionTable;

    SessionPtr = ConnectionPtr->primarySession;
    rtn = BUFREQ_OK;

    if ((SessionPtr->Rx_Status == PDUR_SESSION_IDLE) || (SessionPtr->Tx_Status == PDUR_TX_IDLE) || (info->SduLength > (SessionPtr->SduLength - SessionPtr->numTxLength)))
    {

        return  BUFREQ_E_NOT_OK;
    }

    if(info->SduLength == 0u)
    {

        *(availableDataPtr) = (SessionPtr->numRxLength - SessionPtr->numTxLength);
        if(*(availableDataPtr) != 0u)
        {
            return BUFREQ_OK;
        }
        else
        {
            return BUFREQ_E_BUSY;
        }
    }

    if(gt->numOfLowerLayers > 1u)
    {

        if(info->SduLength == SessionPtr->SduLength)
        {
            if((retry == NULL_PTR) || (retry->TpDataState == TP_DATACONF))
            {

                rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,info->SduLength);

                *(availableDataPtr) = 0;

            }
            else
            {

                rtn = BUFREQ_E_NOT_OK;
            }
        }
        else
        {

            rtn = BUFREQ_E_NOT_OK;

        }
        return rtn;

    }

    if(SessionPtr->numRxLength >= (info->SduLength + SessionPtr->numTxLength))
    {
        if((retry == NULL_PTR) || (retry->TpDataState == TP_DATACONF))
        {

#ifdef PDUR_STORE_AND_FORWARD

            PduLengthType availableDataLength_l;
            if(SessionPtr->TxChunkLength == SessionPtr->bufferLength)
             {

                 SessionPtr->readPtr = SessionPtr->bufferPtr;
                 SessionPtr->TxChunkLength = 0;

             }
            availableDataLength_l = SessionPtr->bufferLength - SessionPtr->TxChunkLength;
            if(info->SduLength > availableDataLength_l)
            {

                 rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,availableDataLength_l);

                 SessionPtr->readPtr = SessionPtr->bufferPtr;
                 SessionPtr->TxChunkLength = 0;

                 rba_BswSrv_MemCopy8((info->SduDataPtr + availableDataLength_l),SessionPtr->readPtr,(info->SduLength - availableDataLength_l));

                 SessionPtr->readPtr += (info->SduLength - availableDataLength_l);

                 SessionPtr->TxChunkLength += (info->SduLength - availableDataLength_l);

             }
            else
            {

                rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,info->SduLength);

                SessionPtr->readPtr += info->SduLength;

                SessionPtr->TxChunkLength += info->SduLength;
            }

#else

            rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,info->SduLength);
            SessionPtr->readPtr += info->SduLength;
#endif

           SessionPtr->numTxLength += info->SduLength;

          *(availableDataPtr) = SessionPtr->numRxLength - SessionPtr->numTxLength;
        }
        else
        {

            rtn = BUFREQ_E_NOT_OK;
        }
    }
    else
    {

        rtn = BUFREQ_E_BUSY;

    }
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

