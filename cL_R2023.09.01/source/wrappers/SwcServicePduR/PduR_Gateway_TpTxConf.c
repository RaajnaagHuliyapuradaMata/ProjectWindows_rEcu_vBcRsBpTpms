
#include "PduR_Prv.hpp"
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_BufferPool.hpp"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

 void PduR_GF_Tp_TxConfirmation_Func( PduIdType gwId, Std_ReturnType result)
{

   PduR_GT_TpPtr      gt;

   const PduR_FIFO_Tp_fixed * fifo;

   PduR_TpSessDynPtr  SessionPtr;
   PduR_TpConnDynPtr ConnectionPtr;

    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
   ConnectionPtr = fifo->connectionTable;
    SessionPtr = ConnectionPtr->primarySession;

   if((SessionPtr->Rx_Status == PDUR_SESSION_IDLE) || (SessionPtr->Tx_Status == PDUR_TX_IDLE))
   {
        return;
   }

   if(gt->numOfLowerLayers == 1u)
   {

#ifdef PDUR_QUEUEING_SUPPORT

        if( ConnectionPtr->activeSessionCount != 0)
        {

            ConnectionPtr->activeSessionCount--;

            PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr, gt);
        }
        else{

            return;
        }

        if(ConnectionPtr->activeSessionCount == 1)
        {

            ConnectionPtr->primarySession =  ConnectionPtr->secondarySession;

            ConnectionPtr->secondarySession = SessionPtr;

            SessionPtr = ConnectionPtr->primarySession;

            if((SessionPtr->Tx_Status == PDUR_TX_IDLE) && (SessionPtr->numRxLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8] == SessionPtr->SduLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8]))
            {
                PduInfoType readerPduInfo;
                Std_ReturnType Ret_val;

                readerPduInfo.SduDataPtr = SessionPtr->readPtr;

                readerPduInfo.SduLength  = SessionPtr->SduLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8];

                SessionPtr->Tx_Status = PDUR_TX_INPROGRESS;

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                Ret_val = PDUR_BASE_RPTBL(loTxTablePtr)[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
#else
                Ret_val = PduR_loTransmitTable[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
#endif

                if(Ret_val != E_OK)
                {

                    ConnectionPtr->activeSessionCount--;

                    PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr, gt);
                }
            }

        }
        if(ConnectionPtr->activeSessionCount == 0)
        {

            PduR_ReleaseTpBuffer(gt);
        }
#else

#ifdef PDUR_FIFO_TP_SUPPORT
        if(gt->TpQueueDepth_u8 > 1u)
        {
            boolean BreakFlag_b;
            SessionPtr->numTxLength = 0u;
            SessionPtr->Tx_FifoInstanceUsed_u8++;
            BreakFlag_b= TRUE;
            while(BreakFlag_b)
            {
                if(SessionPtr->Tx_FifoInstanceUsed_u8 == gt->TpQueueDepth_u8)
                {

                    SessionPtr->Tx_FifoInstanceUsed_u8 = 0u;

                    SessionPtr->readPtr = fifo->begin;
                    SessionPtr->Tx_Status = PDUR_TX_IDLE;
                }

                if(SessionPtr->Tx_FifoInstanceUsed_u8 != SessionPtr->Rx_FifoInstanceUsed_u8)
                {

                    PduInfoType readerPduInfo;
                    Std_ReturnType Ret_val;

                     PduLengthType TxInstanceLength_l;

                    SessionPtr->Tx_Status = PDUR_TX_IDLE;

                    SessionPtr->readPtr = fifo->begin;
                    TxInstanceLength_l = (PduLengthType)((SessionPtr->Tx_FifoInstanceUsed_u8)*(SessionPtr->bufferLength));

                    SessionPtr->readPtr += TxInstanceLength_l;

                    readerPduInfo.SduDataPtr = SessionPtr->readPtr;

                    readerPduInfo.SduLength  = SessionPtr->SduLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8];

                    Ret_val = PduR_loTransmitTable[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);

                    if(Ret_val == E_OK)
                    {
                        SessionPtr->Tx_Status = PDUR_TX_INPROGRESS;
                        BreakFlag_b = FALSE;
                    }
                    else
                    {

                        SessionPtr->numRxLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8] = 0u;
                        SessionPtr->SduLength_auo[SessionPtr->Tx_FifoInstanceUsed_u8] = 0u;

                        SessionPtr->Tx_FifoInstanceUsed_u8++;

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
                    PDUR_REPORT_ERROR(PDUR_SID_GATEWAYTPTXCONFIRMATION,PDUR_E_PDU_INSTANCES_LOST);
#endif
                    }
                }

                else if(SessionPtr->Rx_Status != PDUR_RX_INPROGRESS)
                {

                    PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr, gt);

                    BreakFlag_b = FALSE;
                }

                else{

                    SessionPtr->Tx_Status = PDUR_TX_IDLE;

                    BreakFlag_b = FALSE;
                }
            }
        }
        else{

            PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr, gt);

        }
#else

        PduR_ReleaseTpBuffer(gt);

        PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr, gt);
#endif
#endif
   }
   else{

        if(SessionPtr->Tx_E_OK_Count != 0)
        {
           SessionPtr->Tx_E_OK_Count--;
        }
        if(SessionPtr->Tx_E_OK_Count == 0)
        {

#ifdef PDUR_QUEUEING_SUPPORT

            ConnectionPtr->activeSessionCount--;
#endif

            PduR_ReleaseTpBuffer(gt);

            PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr, gt);
        }
     }
    (void) result;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"
#endif

