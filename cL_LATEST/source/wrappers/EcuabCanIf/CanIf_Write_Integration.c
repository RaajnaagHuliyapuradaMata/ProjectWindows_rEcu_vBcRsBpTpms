#include "Std_Types.hpp"

#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "CanIf_Integration.hpp"
#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
Can_ReturnType CanIf_Write_Integration(
            Can_HwHandleType Hth
   ,  const Can_PduType*     PduInfoPtr
){
   return Can_Write(
         Hth
      ,  PduInfoPtr
   );
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

