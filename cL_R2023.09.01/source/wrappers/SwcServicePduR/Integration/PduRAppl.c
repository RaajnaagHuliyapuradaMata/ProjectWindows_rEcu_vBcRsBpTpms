
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "PduR_Prv.hpp"

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

void PduRAppl_IncompatibleGenerator(void){
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif
