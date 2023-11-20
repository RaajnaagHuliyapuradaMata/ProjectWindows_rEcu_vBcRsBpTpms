
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef BFX_MEMMAP_H
#define BFX_MEMMAP_H

#endif

#define BFX_MEMMAP_ERROR

#if defined (BFX_START_SEC_CODE)
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BFX_START_SEC_CODE
    #undef BFX_MEMMAP_ERROR
#elif defined (BFX_STOP_SEC_CODE)
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BFX_STOP_SEC_CODE
    #undef BFX_MEMMAP_ERROR

#elif defined (BFX_START_SEC_CODE_SLOW)
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BFX_START_SEC_CODE_SLOW
    #undef BFX_MEMMAP_ERROR
#elif defined (BFX_STOP_SEC_CODE_SLOW)
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BFX_STOP_SEC_CODE_SLOW
    #undef BFX_MEMMAP_ERROR

#elif defined (BFX_START_SEC_CODE_FAST)
#define BSW_START_SEC_CODE_FAST
    #include "Bsw_MemMap.hpp"
    #undef BFX_START_SEC_CODE_FAST
    #undef BFX_MEMMAP_ERROR
#elif defined (BFX_STOP_SEC_CODE_FAST)
#define BSW_STOP_SEC_CODE_FAST
    #include "Bsw_MemMap.hpp"
    #undef BFX_STOP_SEC_CODE_FAST
    #undef BFX_MEMMAP_ERROR

#elif defined BFX_MEMMAP_ERROR
# error "Bfx_MemMap.h, wrong #pragma command"
#endif

