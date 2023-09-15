

#include "PduR_Prv.hpp"
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"
#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_Cfg_Internal.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

BufReq_ReturnType PduR_GF_Tp_CopyTxData_Func(Type_SwcServiceCom_tIdPdu gwId, const Type_SwcServiceCom_stInfoPdu* info, RetryInfoType* retry, Type_SwcServiceCom_tLengthPdu* availableDataPtr)
{

   PduR_GT_TpPtr      gt;

   const PduR_FIFO_Tp_fixed * fifo;

   PduR_TpConnDynPtr ConnectionPtr;
   PduR_TpSessDynPtr  SessionPtr;
    BufReq_ReturnType rtn;

    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
   ConnectionPtr = fifo->connectionTable;

    SessionPtr = ConnectionPtr->primarySession;
    rtn = BUFREQ_OK;

   if((SessionPtr->Rx_Status == PDUR_SESSION_IDLE) || (SessionPtr->Tx_Status == PDUR_TX_IDLE) || (info->SduLength > (SessionPtr->SduLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8] - SessionPtr->numTxLength)))
   {

        return  BUFREQ_E_NOT_OK;
   }

   if(info->SduLength == 0u)
   {

        *(availableDataPtr) = (SessionPtr->numRxLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8] - SessionPtr->numTxLength);
        if(*(availableDataPtr) != 0u)
        {
            return BUFREQ_OK;
        }
        else{
            return BUFREQ_E_BUSY;
        }
   }

   if(SessionPtr->numRxLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8] >= (info->SduLength + SessionPtr->numTxLength))
   {

        if((retry == NULL_PTR) || (retry->TpDataState == TP_DATACONF))
        {

            if(info->SduLength == SessionPtr->SduLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8])
            {

                rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,info->SduLength);

                *(availableDataPtr) = 0;

            }

            else{

#ifdef PDUR_STORE_AND_FORWARD

                Type_SwcServiceCom_tLengthPdu availableDataLength_l;
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
                else{

                    rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,info->SduLength);

                    SessionPtr->readPtr += info->SduLength;

                    SessionPtr->TxChunkLength += info->SduLength;
                }

#else

                    rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,info->SduLength);
                    SessionPtr->readPtr += info->SduLength;
#endif

                    SessionPtr->numTxLength += info->SduLength;

                    *(availableDataPtr) = SessionPtr->numRxLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8] - SessionPtr->numTxLength;

            }
        }
        else{

            rtn = BUFREQ_E_NOT_OK;
        }
   }
   else{

        rtn = BUFREQ_E_BUSY;

   }
    return rtn;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"
#endif

