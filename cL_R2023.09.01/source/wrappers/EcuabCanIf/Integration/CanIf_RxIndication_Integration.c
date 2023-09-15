#include "Std_Types.hpp"

#include "CanIf_Cbk.hpp"
#include "CanIf_Integration.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(void, CANIF_CODE) CanIf_RxIndication(
      P2CONST(Can_HwType,  AUTOMATIC, CANIF_APPL_DATA) Mailbox
   ,  P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
){
   CanIf_RxIndication_Internal(
         Mailbox
      ,  PduInfoPtr
   );
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

