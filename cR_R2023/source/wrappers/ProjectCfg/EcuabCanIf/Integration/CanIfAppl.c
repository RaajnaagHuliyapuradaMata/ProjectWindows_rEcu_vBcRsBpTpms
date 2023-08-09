
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "CanIf_Prv.h"

#if(CANIF_VARIANT_INFO > 1)

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.h"

FUNC(void, CanIf_CODE)  CanIfAppl_IncompatibleGenerator(void)
{
    // User can report DET error / DEM error etc here

}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.h"

#endif
