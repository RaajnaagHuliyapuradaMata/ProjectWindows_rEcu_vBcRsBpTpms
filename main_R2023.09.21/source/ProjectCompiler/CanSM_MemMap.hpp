#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#define MEMMAP_ERROR

#if defined CANSM_START_SEC_CONFIG_DATA_POSTBUILD_8
    #undef   CANSM_START_SEC_CONFIG_DATA_POSTBUILD_8
#define CANSM_START_SEC_CONST_8
#endif
#if defined CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #undef   CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#define CANSM_STOP_SEC_CONST_8
#endif
#if defined CANSM_START_SEC_CONFIG_DATA_POSTBUILD_16
    #undef   CANSM_START_SEC_CONFIG_DATA_POSTBUILD_16
#define CANSM_START_SEC_CONST_16
#endif
#if defined CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_16
    #undef   CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_16
#define CANSM_STOP_SEC_CONST_16
#endif
#if defined CANSM_START_SEC_CONFIG_DATA_POSTBUILD_32
    #undef  CANSM_START_SEC_CONFIG_DATA_POSTBUILD_32
#define CANSM_START_SEC_CONST_32
#endif
#if defined CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #undef   CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#define CANSM_STOP_SEC_CONST_32
#endif
#if defined CANSM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef   CANSM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define CANSM_START_SEC_CONST_UNSPECIFIED
#endif
#if defined CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef   CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#endif
#if defined CANSM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef   CANSM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#endif
#if defined CANSM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef   CANSM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#endif

#if defined CANSM_START_SEC_CONST_8
#define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_CONST_8
#define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_CONST_BOOLEAN
#define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_CONST_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_CONST_BOOLEAN
#define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_CONST_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_CONST_UNSPECIFIED

#define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_CONST_UNSPECIFIED
#define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_VAR_CLEARED_BOOLEAN

#define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_VAR_CLEARED_8

#define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_VAR_CLEARED_8
#define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_VAR_CLEARED_16

#define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_VAR_CLEARED_16
#define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_VAR_CLEARED_32

#define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_VAR_CLEARED_32
#define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED

#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_VAR_INIT_UNSPECIFIED
#define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_CODE
#define BSW_START_SEC_CODE
   #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
   #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_CODE
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_CONFIG_DATA_POSTBUILD_8

#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_CONFIG_DATA_POSTBUILD_8
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_CONFIG_DATA_POSTBUILD_16

#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_16
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_CONFIG_DATA_POSTBUILD_16
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_16
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_16
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_16
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_CONFIG_DATA_POSTBUILD_32

#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_32
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_CONFIG_DATA_POSTBUILD_32
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined CANSM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED

#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined CANSM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef CANSM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
    #error "CANSM_MemMap.h, wrong #pragma command"
#endif
