
#include "PduR_Prv.h"
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_BufferPool.h"
#endif

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_GF_Tp_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) gwId,
                                                   VAR(Std_ReturnType, AUTOMATIC) result)
{

    PduR_GT_TpPtr      gt;

    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;

    PduR_TpSessDynPtr  SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;

    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = fifo->connectionTable;
    SessionPtr = ConnectionPtr->primarySession;

    if ((SessionPtr->Rx_Status == PDUR_SESSION_IDLE) || (SessionPtr->Tx_Status == PDUR_TX_IDLE))
    {
        return;
    }

    if(gt->numOfLowerLayers == 1u)
    {

#ifdef PDUR_QUEUEING_SUPPORT

        if ( ConnectionPtr->activeSessionCount != 0)
        {

            ConnectionPtr->activeSessionCount--;

            PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);
        }
        else
        {

            return;
        }

        if(ConnectionPtr->activeSessionCount == 1)
        {

            ConnectionPtr->primarySession =  ConnectionPtr->secondarySession;

            ConnectionPtr->secondarySession = SessionPtr;

            SessionPtr = ConnectionPtr->primarySession;

            if((SessionPtr->Tx_Status == PDUR_TX_IDLE) && (SessionPtr->numRxLength == SessionPtr->SduLength))
            {
                VAR(PduInfoType,AUTOMATIC) readerPduInfo;
                VAR(Std_ReturnType, AUTOMATIC)  Ret_val;

                readerPduInfo.SduDataPtr = SessionPtr->readPtr;

                readerPduInfo.SduLength  = SessionPtr->SduLength;

                SessionPtr->Tx_Status = PDUR_TX_INPROGRESS;

                #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                Ret_val = PDUR_BASE_RPTBL(loTxTablePtr)[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
                #else
                Ret_val = PduR_loTransmitTable[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
                #endif

                if(Ret_val != E_OK)
                {

                    ConnectionPtr->activeSessionCount--;

                    PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);
                }
            }

        }
        if(ConnectionPtr->activeSessionCount == 0)
        {

            PduR_ReleaseTpBuffer(gt);
        }
#else

        PduR_ReleaseTpBuffer(gt);

        PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);

#endif

    }
    else
    {

        if(SessionPtr->Tx_E_OK_Count != 0)
        {
           SessionPtr->Tx_E_OK_Count--;
        }
        if(SessionPtr->Tx_E_OK_Count == 0)
        {

            PduR_ReleaseTpBuffer(gt);

            PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);
        }
     }
    (void) result;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif

