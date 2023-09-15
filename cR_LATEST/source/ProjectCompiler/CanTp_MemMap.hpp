#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#define MEMMAP_ERROR

#if defined CANTP_START_SEC_VAR_CLEARED_8
#define BSW_START_SEC_VAR_CLEARED_8
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_VAR_CLEARED_8
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_VAR_CLEARED_8
#define BSW_STOP_SEC_VAR_CLEARED_8
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_VAR_CLEARED_8
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONST_UNSPECIFIED
#define BSW_START_SEC_CONST_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONST_UNSPECIFIED
#define BSW_STOP_SEC_CONST_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONST_8
#define BSW_START_SEC_CONST_8
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_CONST_8
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONST_8
#define BSW_STOP_SEC_CONST_8
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_CONST_8
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CODE
#define BSW_START_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_CODE
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_CODE
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_FDCALLOUT_CODE
#define BSW_START_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_FDCALLOUT_CODE
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_FDCALLOUT_CODE
#define BSW_STOP_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_FDCALLOUT_CODE
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED
#define BSW_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#define BSW_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONFIG_CODE
#define BSW_START_SEC_DEFAULT_CODE
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_CONFIG_CODE
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONFIG_CODE
#define BSW_STOP_SEC_DEFAULT_CODE
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_CONFIG_CODE
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONFIG_CODE_POSTBUILD
#define BSW_START_SEC_DEFAULT_CODE
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_CONFIG_CODE_POSTBUILD
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONFIG_CODE_POSTBUILD
#define BSW_STOP_SEC_DEFAULT_CODE
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_CONFIG_CODE_POSTBUILD
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef CANTP_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
#error "CanTp_MemMap.h, wrong #pragma command"
#endif

