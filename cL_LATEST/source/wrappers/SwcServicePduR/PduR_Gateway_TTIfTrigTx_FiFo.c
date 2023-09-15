

#include "PduR_Prv.hpp"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"
#include "PduR.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_GF_TTIf_FIFO_TriggerTransmit_Func( Type_SwcServiceCom_tIdPdu gwayId
   ,                                                               Type_SwcServiceCom_stInfoPdu * dataPtr)
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
#include "PduR_MemMap.hpp"

#endif

