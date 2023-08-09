
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef ECUM_MEMMAP_H
#define ECUM_MEMMAP_H

#if defined ECUM_START_SEC_CODE
   #define BSW_START_SEC_CODE
   #include "Bsw_MemMap.h"
   #undef ECUM_START_SEC_CODE
#elif defined ECUM_STOP_SEC_CODE
   #define BSW_STOP_SEC_CODE
   #include "Bsw_MemMap.h"
   #undef ECUM_STOP_SEC_CODE

#elif defined EcuM_START_SEC_CODE
   #define BSW_START_SEC_CODE
   #include "Bsw_MemMap.h"
   #undef EcuM_START_SEC_CODE
#elif defined EcuM_STOP_SEC_CODE
   #define BSW_STOP_SEC_CODE
   #include "Bsw_MemMap.h"
   #undef EcuM_STOP_SEC_CODE

#else
    #error "EcuM_MemMap.h: Unknown MemMap #define"
#endif

#undef ECUM_MEMMAP_H
#endif//ECUM_MEMMAP_H

