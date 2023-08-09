
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "PduR_Cfg_SymbolicNames.h"

#define MEMMAP_ERROR

#if ( PDUR_CONFIGURATION_VARIANT == PDUR_VARIANT_PRE_COMPILE )

# if defined PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

#  undef PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#  define PDUR_START_SEC_CONST_UNSPECIFIED
# elif defined PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

#  undef  PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#  define PDUR_STOP_SEC_CONST_UNSPECIFIED
# elif defined PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8

#  undef PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8
#  define PDUR_START_SEC_CONST_8
# elif defined PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8

#  undef  PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#  define PDUR_STOP_SEC_CONST_8
# elif defined PDUR_START_SEC_VAR_CLEARED_POSTBUILD_8

#  undef PDUR_START_SEC_VAR_CLEARED_POSTBUILD_8
#  define PDUR_START_SEC_VAR_CLEARED_8
# elif defined PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_8

#  undef PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#  define PDUR_STOP_SEC_VAR_CLEARED_8
# elif defined PDUR_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED

#  undef PDUR_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#  define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
# elif defined PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED

#  undef PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#  define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# endif
#endif

#if defined PDUR_START_SEC_CONST_UNSPECIFIED

    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CONST_BOOLEAN

    #define BSW_START_SEC_CONST_BOOLEAN
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_CONST_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONST_BOOLEAN
    #define BSW_STOP_SEC_CONST_BOOLEAN
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_CONST_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CONST_8

    #define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_VAR_CLEARED_POSTBUILD_8

    #define BSW_START_SEC_VAR_CLEARED_POSTBUILD_8
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_VAR_CLEARED_POSTBUILD_8
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_VAR_CLEARED_BOOLEAN

    #define BSW_START_SEC_VAR_CLEARED_BOOLEAN
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_STOP_SEC_VAR_CLEARED_BOOLEAN
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_VAR_CLEARED_8

    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED

    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CODE
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CODE
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_CODE
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8

    #define BSW_START_SEC_CONFIG_DATA_POSTBUILD_8
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

    #define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED

    #define BSW_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"

    #undef PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
    #error "PduR_MemMap.h, wrong #pragma command"
#endif

