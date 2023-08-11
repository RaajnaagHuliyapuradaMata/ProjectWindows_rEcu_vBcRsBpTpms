
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "ComM_Cfg.h"

#define MEMMAP_ERROR
#if(COMM_CONFIGURATION_VARIANT == COMM_VARIANT_PRECOMPILE)
// If Module is pre-compile , then map post-build memmap to pre-compile memmap
#ifdef COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

    #undef COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define COMM_START_SEC_CONST_UNSPECIFIED
#endif

#ifdef COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

    #undef COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define COMM_STOP_SEC_CONST_UNSPECIFIED
#endif

#endif

#if defined COMM_START_SEC_CONST_UNSPECIFIED

    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef COMM_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined COMM_START_SEC_CONST_8
    #define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.h"

    #undef COMM_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR

#elif defined COMM_START_SEC_VAR_CLEARED_BOOLEAN

    #define BSW_START_SEC_VAR_CLEARED_BOOLEAN
    #include "Bsw_MemMap.h"

    #undef COMM_START_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_STOP_SEC_VAR_CLEARED_BOOLEAN
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined COMM_START_SEC_VAR_CLEARED_8

    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"

    #undef COMM_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR

#elif defined COMM_START_SEC_VAR_CLEARED_UNSPECIFIED

    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

 #elif defined COMM_START_SEC_VAR_INIT_UNSPECIFIED

    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef COMM_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined COMM_START_SEC_CODE
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"

    #undef COMM_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_CODE
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_CODE
    #undef MEMMAP_ERROR

// Memmap for Post build data
#elif defined COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

    #define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
    #error "ComM_Cfg_MemMap.h, wrong #pragma command"
#endif

