
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "ComM_Priv.hpp"

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComMAppl_IncompatibleGenerator(void){
    // User can report DET error / DEM error etc here
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

