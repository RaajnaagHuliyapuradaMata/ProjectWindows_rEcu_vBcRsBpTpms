#include "Std_Types.hpp"

#include "PduR_Prv.hpp"
#include "PduR_Cfg.hpp"
#include "PduR_LoTp.hpp"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"
void infSwcServicePduRSwcServiceCanTp_fptrConfirmation_Rx(
      PduIdType      id
   ,  Std_ReturnType std
){
   PduR_rCanTpRxIndication(
         (id)
      ,  (std)
   );
}

void infSwcServicePduRSwcServiceCanTp_fptrConfirmation_Tx(
      PduIdType      id
   ,  Std_ReturnType std
){
   PduR_rCanTpTxConfirmation(
         (id)
      ,  (std)
   );
}

BufReq_ReturnType PduR_CanTpCopyRxData(
            PduIdType      id
   ,  const PduInfoType*   info
   ,        PduLengthType* bufferSizePtr)
{
   return(
      PduR_rCanTpCopyRxData(
            (id)
         ,  (info)
         ,  (bufferSizePtr)
      )
   );
}

BufReq_ReturnType PduR_CanTpStartOfReception(
            PduIdType      id
   ,  const PduInfoType*   info
   ,        PduLengthType  TpSduLength
   ,        PduLengthType* bufferSizePtr
){
   return(
      PduR_rCanTpStartOfReception(
            (id)
         ,  (info)
         ,  (TpSduLength)
         ,  (bufferSizePtr)
      )
   );
}

BufReq_ReturnType PduR_CanTpCopyTxData(
            PduIdType      id
   ,  const PduInfoType*   info
   ,        RetryInfoType* retry
   ,        PduLengthType* availableDataPtr
){
   return(
      PduR_rCanTpCopyTxData(
            (id)
         ,  (info)
         ,  (retry)
         ,  (availableDataPtr)
      )
   );
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

