

#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#include "PduR.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

Std_ReturnType PduR_GF_TTIf_FIFO_TriggerTransmit_Func( PduIdType gwayId,
                                                                PduInfoType * dataPtr)
{
    const PduR_GT_If * gt = PDUR_GW_IF_BASE + gwayId;

    PduR_FifoType         fifo = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr     dyn  = (PduR_FifoDynIfPtr)(fifo->dyn);
    Std_ReturnType        retVal = E_NOT_OK;

    uint16 i;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest();

    if((dyn->actLen[dyn->readIndex] > 0u) && (dyn->actLen[dyn->readIndex] <=  dataPtr->SduLength))
    {

        for(i = 0 ; i < dyn->actLen[dyn->readIndex] ; i++)
        {
            *((dataPtr->SduDataPtr)+i) = *((dyn->readPtr)+i);
         }

        dataPtr->SduLength = dyn->actLen[dyn->readIndex];
        retVal = E_OK;
    }

    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest();
    return retVal;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

