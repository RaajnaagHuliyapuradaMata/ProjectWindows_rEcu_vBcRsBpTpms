
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif
#ifndef ECUM_CFG_MEMMAP_H
#define ECUM_CFG_MEMMAP_H

#if defined ECUM_START_SEC_VAR_CLEARED_8
#define BSW_START_SEC_VAR_CLEARED_8
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_CLEARED_8
#elif defined ECUM_STOP_SEC_VAR_CLEARED_8
#define BSW_STOP_SEC_VAR_CLEARED_8
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_CLEARED_8
#elif defined ECUM_START_SEC_VAR_CLEARED_16
#define BSW_START_SEC_VAR_CLEARED_16
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_CLEARED_16
#elif defined ECUM_STOP_SEC_VAR_CLEARED_16
#define BSW_STOP_SEC_VAR_CLEARED_16
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_CLEARED_16
#elif defined ECUM_START_SEC_VAR_CLEARED_32
#define BSW_START_SEC_VAR_CLEARED_32
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_CLEARED_32
#elif defined ECUM_STOP_SEC_VAR_CLEARED_32
#define BSW_STOP_SEC_VAR_CLEARED_32
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_CLEARED_32
#elif defined ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#define BSW_START_SEC_VAR_CLEARED_8
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#elif defined ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#define BSW_STOP_SEC_VAR_CLEARED_8
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#elif defined ECUM_START_SEC_VAR_INIT_16
#define BSW_START_SEC_VAR_INIT_16
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_INIT_16
#elif defined ECUM_STOP_SEC_VAR_INIT_16
#define BSW_STOP_SEC_VAR_INIT_16
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_INIT_16
#elif defined ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#elif defined ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#elif defined ECUM_START_SEC_VAR_POWER_ON_CLEARED_8
#undef ECUM_START_SEC_VAR_POWER_ON_CLEARED_8
#elif defined ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#undef ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#elif defined ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#undef ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#elif defined ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#undef ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#elif defined ECUM_START_SEC_VAR_SAVED_ZONE0_BOOLEAN
#define BSW_START_SEC_SAVED_ZONE_8
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_SAVED_ZONE0_BOOLEAN
#elif defined ECUM_STOP_SEC_VAR_SAVED_ZONE0_BOOLEAN
#define BSW_STOP_SEC_SAVED_ZONE_8
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_SAVED_ZONE0_BOOLEAN
#elif defined ECUM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#define BSW_START_SEC_SAVED_ZONE_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#elif defined ECUM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#define BSW_STOP_SEC_SAVED_ZONE_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#elif defined ECUM_START_SEC_CONST_8
#define BSW_START_SEC_CONST_8
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_CONST_8
#elif defined ECUM_STOP_SEC_CONST_8
#define BSW_STOP_SEC_CONST_8
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_CONST_8
#elif defined ECUM_START_SEC_CONST_UNSPECIFIED
#define BSW_START_SEC_CONST_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_CONST_UNSPECIFIED
#elif defined ECUM_STOP_SEC_CONST_UNSPECIFIED
#define BSW_STOP_SEC_CONST_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_CONST_UNSPECIFIED
#elif defined ECUM_START_SEC_CONST_16
#define BSW_START_SEC_CONST_16
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_CONST_16
#elif defined ECUM_STOP_SEC_CONST_16
#define BSW_STOP_SEC_CONST_16
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_CONST_16
#elif defined ECUM_START_SEC_CONST_32
#define BSW_START_SEC_CONST_32
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_CONST_32
#elif defined ECUM_STOP_SEC_CONST_32
#define BSW_STOP_SEC_CONST_32
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_CONST_32
#elif defined ECUM_START_SEC_CONFIG_DATA_8
#define BSW_START_SEC_CONST_8
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_CONFIG_DATA_8
#elif defined ECUM_STOP_SEC_CONFIG_DATA_8
#define BSW_STOP_SEC_CONST_8
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_CONFIG_DATA_8
#elif defined ECUM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_START_SEC_CONST_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#elif defined ECUM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_CONST_UNSPECIFIED
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#elif defined ECUM_START_SEC_CALLOUT_CODE
#define BSW_START_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_CALLOUT_CODE
#elif defined ECUM_STOP_SEC_CALLOUT_CODE
#define BSW_STOP_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_CALLOUT_CODE
#elif defined ECUM_START_SEC_VAR_INIT_8
#define BSW_START_SEC_VAR_INIT_8
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_VAR_INIT_8
#elif defined ECUM_STOP_SEC_VAR_INIT_8
#define BSW_STOP_SEC_VAR_INIT_8
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_VAR_INIT_8
#elif defined ECUM_START_SEC_CODE
#define BSW_START_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef ECUM_START_SEC_CODE
#elif defined ECUM_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef ECUM_STOP_SEC_CODE
#elif defined EcuM_START_SEC_CODE
#define BSW_START_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef EcuM_START_SEC_CODE
#elif defined EcuM_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
#include "Bsw_MemMap.hpp"
#undef EcuM_STOP_SEC_CODE
#else
#error "EcuM_Cfg_MemMap.h: Unknown MemMap#define"
#endif

#undef ECUM_CFG_MEMMAP_H
#endif
