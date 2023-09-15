
#include "PduR_Prv.hpp"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.hpp"
#include "PduR.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

Std_ReturnType PduR_GF_TTIf_Buf_TriggerTransmit_Func( PduIdType gwayId
   ,                                                              PduInfoType * dataPtr )
{
   const PduR_GT_If * gt;
   PduR_Buf_If_dynamic  *dyn;
   PduInfoType * infoBuf;
   uint16 i;
    Std_ReturnType retVal;
    gt      = PDUR_GW_IF_BASE + gwayId;

    dyn     =  (PduR_Buf_If_dynamic*) gt->buffer;
   infoBuf = dyn->gwBuf;
    retVal = E_NOT_OK;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest();

   if(dataPtr->SduLength >= infoBuf->SduLength)
   {
        for(i = 0 ; i < infoBuf->SduLength ; i++)
        {
            *((dataPtr->SduDataPtr)+i) = *((infoBuf->SduDataPtr)+i);
        }
        dataPtr->SduLength = infoBuf->SduLength;
        retVal = E_OK;
   }

    dyn->Tx_Status = PDUR_TX_IDLE;
    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest();
    return retVal;
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

