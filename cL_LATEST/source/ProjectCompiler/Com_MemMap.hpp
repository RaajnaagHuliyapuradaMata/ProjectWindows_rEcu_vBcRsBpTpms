
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef COM_MEMMAP_H
#define COM_MEMMAP_H

#include "Com_Cfg_SymbolicNames.hpp"

#if defined COM_START_SEC_CONST_UNSPECIFIED
#define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CONST_UNSPECIFIED
#elif defined COM_STOP_SEC_CONST_UNSPECIFIED
#define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CONST_UNSPECIFIED

#elif defined COM_START_SEC_CONST_32
#define BSW_START_SEC_CONST_32
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CONST_32
#elif defined COM_STOP_SEC_CONST_32
#define BSW_STOP_SEC_CONST_32
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CONST_32

#elif defined COM_START_SEC_CONST_8
#define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CONST_8
#elif defined COM_STOP_SEC_CONST_8
#define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CONST_8

#elif defined COM_START_SEC_CODE
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CODE
#elif defined COM_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CODE

#elif defined COM_START_SEC_CODE_FAST
#define BSW_START_SEC_CODE_FAST
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CODE_FAST
#elif defined COM_STOP_SEC_CODE_FAST
#define BSW_STOP_SEC_CODE_FAST
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CODE_FAST

#elif defined COM_START_SEC_VAR_INIT_UNSPECIFIED
#define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_INIT_UNSPECIFIED
#elif defined COM_STOP_SEC_VAR_INIT_UNSPECIFIED
#define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_INIT_UNSPECIFIED

#elif defined COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#elif defined COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED

#elif defined COM_START_SEC_VAR_CLEARED_64
#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_64
#elif defined COM_STOP_SEC_VAR_CLEARED_64
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_64

#elif defined COM_START_SEC_VAR_CLEARED_32
#define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_32
#elif defined COM_STOP_SEC_VAR_CLEARED_32
#define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_32

#elif defined COM_START_SEC_VAR_CLEARED_16
#define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_16
#elif defined COM_STOP_SEC_VAR_CLEARED_16
#define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_16

#elif defined COM_START_SEC_VAR_CLEARED_8
#define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_8
#elif defined COM_STOP_SEC_VAR_CLEARED_8
#define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_8

#elif defined COM_START_SEC_VAR_CLEARED_BOOLEAN
#define BSW_START_SEC_VAR_CLEARED_BOOLEAN
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_BOOLEAN
#elif defined COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#define BSW_STOP_SEC_VAR_CLEARED_BOOLEAN
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#elif defined COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#elif defined COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#elif defined COM_START_SEC_CONFIG_DATA_32
#define BSW_START_SEC_CONST_32
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CONFIG_DATA_32
#elif defined COM_STOP_SEC_CONFIG_DATA_32
#define BSW_STOP_SEC_CONST_32
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CONFIG_DATA_32

#elif defined COM_START_SEC_CONFIG_DATA_POSTBUILD_32
#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_32
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CONFIG_DATA_POSTBUILD_32
#elif defined COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32

#elif defined COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#elif defined COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
#define BSW_START_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
#define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_BOOLEAN

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#define BSW_START_SEC_VAR_CLEARED_POSTBUILD_8
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#define BSW_START_SEC_VAR_CLEARED_POSTBUILD_16
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_16
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#define BSW_START_SEC_VAR_CLEARED_POSTBUILD_32
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_32
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_64
#define BSW_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_64
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
#define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#define BSW_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#else
    #error "Com_MemMap.h, wrong #pragma command"
#endif
#undef COM_MEMMAP_H
#endif

