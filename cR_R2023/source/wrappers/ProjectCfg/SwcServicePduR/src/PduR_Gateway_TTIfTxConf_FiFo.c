
#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_GF_TTIf_FIFO_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) gwayId )
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_BASE + gwayId;

    PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr) fifo->dyn;
    VAR(PduInfoType, AUTOMATIC) info;

    SchM_Enter_PduR_LockIFGatewayTriggerTxConf();

    if( 0 != dyn->txConfPending )
    {
        uint8 BreakFlag = 0;

        while( BreakFlag == 0 )
        {
            if( 1 == dyn->used )
            {

                dyn->writePtr = dyn->readPtr;
                dyn->used = 0;
                dyn->txConfPending = 0;

                BreakFlag = 1;
            }
            else
            {

                PDUR_FIFO_INC_AND_WRAP( fifo, dyn->readPtr );
                dyn->used--;

                info.SduDataPtr = dyn->readPtr;
                info.SduLength = dyn->actLen;

                #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                if( E_OK == PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &info ))
                #else
                if( E_OK == PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &info ))
                #endif
                {
                    BreakFlag = 1;
                }
            }
        }

    }

    SchM_Exit_PduR_LockIFGatewayTriggerTxConf();

}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif
