
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Com_Prv.h"

#if (COM_CONFIGURATION_VARIANT == COM_VARIANT_PRE_COMPILE)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.h"

CONST(Type_CfgSwcServiceCom_st, AUTOMATIC) ComConfig = {
    NULL_PTR,
    NULL_PTR
};
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Com_MemMap.h"

#endif

