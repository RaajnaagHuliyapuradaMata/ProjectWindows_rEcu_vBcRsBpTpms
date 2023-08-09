

#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#include "PduR.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_FIFO_TriggerTransmit_Func( VAR(PduIdType, AUTOMATIC) gwayId,
                                                                P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) dataPtr)
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_BASE + gwayId;

    PduR_FifoType         fifo = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr     dyn  = (PduR_FifoDynIfPtr)(fifo->dyn);

    VAR(uint16, AUTOMATIC)  i;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest();

    for(i = 0 ; i < dyn->actLen ; i++)
    {
        *((dataPtr->SduDataPtr)+i) = *((dyn->readPtr)+i);
    }

    dataPtr->SduLength = dyn->actLen;
    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest();
    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

