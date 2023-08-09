
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#define MEMMAP_ERROR

#if defined FIM_START_SEC_RAM_CLEARED
    #if defined FIM_WAS_STARTED_SEC_RAM_CLEARED
        #error FIM_WAS_STARTED_SEC_RAM_CLEARED already defined
    #endif
    #define BSW_START_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
    #undef FIM_START_SEC_RAM_CLEARED
    #define FIM_WAS_STARTED_SEC_RAM_CLEARED

#elif defined FIM_STOP_SEC_RAM_CLEARED
    #if ! defined FIM_WAS_STARTED_SEC_RAM_CLEARED
        #error FIM_STOP_SEC_RAM_CLEARED without START_SEC
    #else
        #undef FIM_WAS_STARTED_SEC_RAM_CLEARED
    #endif
    #define BSW_STOP_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
    #undef FIM_STOP_SEC_RAM_CLEARED

#elif defined FIM_START_SEC_RAM_INIT
    #if defined FIM_WAS_STARTED_SEC_RAM_INIT
        #error FIM_WAS_STARTED_SEC_RAM_INIT already defined
    #endif
    #define BSW_START_SEC_DEFAULT_RAM0_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_DEFAULT_RAM0_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
    #undef FIM_START_SEC_RAM_INIT
    #define FIM_WAS_STARTED_SEC_RAM_INIT

#elif defined FIM_STOP_SEC_RAM_INIT
    #if ! defined FIM_WAS_STARTED_SEC_RAM_INIT
        #error FIM_STOP_SEC_RAM_INIT without START_SEC
    #else
        #undef FIM_WAS_STARTED_SEC_RAM_INIT
    #endif
    #define BSW_STOP_SEC_DEFAULT_RAM0_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_DEFAULT_RAM0_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
    #undef FIM_STOP_SEC_RAM_INIT

#elif defined FIM_START_SEC_ROM_CONST
    #if defined FIM_WAS_STARTED_SEC_ROM_CONST
        #error FIM_WAS_STARTED_SEC_ROM_CONST already defined
    #endif
    #define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
    #undef FIM_START_SEC_ROM_CONST
    #define FIM_WAS_STARTED_SEC_ROM_CONST

#elif defined FIM_STOP_SEC_ROM_CONST
    #if ! defined FIM_WAS_STARTED_SEC_ROM_CONST
        #error FIM_STOP_SEC_ROM_CONST without START_SEC
    #else
        #undef FIM_WAS_STARTED_SEC_ROM_CONST
    #endif
    #define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
    #undef FIM_STOP_SEC_ROM_CONST

#elif defined FIM_START_SEC_ROM_CODE
    #if defined FIM_WAS_STARTED_SEC_ROM_CODE
        #error FIM_WAS_STARTED_SEC_ROM_CODE already defined
    #endif
    #define BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_DEFAULT_CODE
    #undef MEMMAP_ERROR
    #undef FIM_START_SEC_ROM_CODE
    #define FIM_WAS_STARTED_SEC_ROM_CODE

#elif defined FIM_STOP_SEC_ROM_CODE
    #if ! defined FIM_WAS_STARTED_SEC_ROM_CODE
        #error FIM_STOP_SEC_ROM_CODE without START_SEC
    #else
        #undef FIM_WAS_STARTED_SEC_ROM_CODE
    #endif
    #define BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_DEFAULT_CODE
    #undef MEMMAP_ERROR
    #undef FIM_STOP_SEC_ROM_CODE

#elif defined(FiM_START_SEC_CODE)
    #define BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_DEFAULT_CODE
    #undef MEMMAP_ERROR
    #undef FiM_START_SEC_CODE

 #elif defined(FiM_STOP_SEC_CODE)
    #define BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_DEFAULT_CODE
    #undef MEMMAP_ERROR
    #undef FiM_STOP_SEC_CODE

#elif defined(FIM_START_SEC_CODE)
    #define BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_DEFAULT_CODE
    #undef MEMMAP_ERROR
    #undef FIM_START_SEC_CODE
 #elif defined(FIM_STOP_SEC_CODE)
    #define BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_DEFAULT_CODE
    #undef MEMMAP_ERROR
    #undef FIM_STOP_SEC_CODE
#elif defined MEMMAP_ERROR
    #error "FiM_MemMap.h, wrong #pragma command"
#endif
