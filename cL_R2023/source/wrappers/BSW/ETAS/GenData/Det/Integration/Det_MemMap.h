
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#define MEMMAP_ERROR

#if defined DET_START_SEC_RAM_CLEARED
#if defined DET_WAS_STARTED_SEC_RAM_CLEARED
#error DET_WAS_STARTED_SEC_RAM_CLEARED already defined
#endif
#define BSW_START_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef BSW_START_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#undef DET_START_SEC_RAM_CLEARED
#define DET_WAS_STARTED_SEC_RAM_CLEARED

#elif defined DET_STOP_SEC_RAM_CLEARED
#if ! defined DET_WAS_STARTED_SEC_RAM_CLEARED
#error DET_STOP_SEC_RAM_CLEARED without START_SEC
#else
#undef DET_WAS_STARTED_SEC_RAM_CLEARED
#endif
#define BSW_STOP_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef BSW_STOP_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#undef DET_STOP_SEC_RAM_CLEARED

#elif defined DET_START_SEC_RAM_INIT
#if defined DET_WAS_STARTED_SEC_RAM_INIT
#error DET_WAS_STARTED_SEC_RAM_INIT already defined
#endif
#define BSW_START_SEC_DEFAULT_RAM0_INIT_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef BSW_START_SEC_DEFAULT_RAM0_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#undef DET_START_SEC_RAM_INIT
#define DET_WAS_STARTED_SEC_RAM_INIT

#elif defined DET_STOP_SEC_RAM_INIT
#if ! defined DET_WAS_STARTED_SEC_RAM_INIT
#error DET_STOP_SEC_RAM_INIT without START_SEC
#else
#undef DET_WAS_STARTED_SEC_RAM_INIT
#endif
#define BSW_STOP_SEC_DEFAULT_RAM0_INIT_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef BSW_STOP_SEC_DEFAULT_RAM0_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#undef DET_STOP_SEC_RAM_INIT

#elif defined DET_START_SEC_ROM_CONST
#if defined DET_WAS_STARTED_SEC_ROM_CONST
#error DET_WAS_STARTED_SEC_ROM_CONST already defined
#endif
#define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#undef DET_START_SEC_ROM_CONST
#define DET_WAS_STARTED_SEC_ROM_CONST

#elif defined DET_STOP_SEC_ROM_CONST
#if ! defined DET_WAS_STARTED_SEC_ROM_CONST
#error DET_STOP_SEC_ROM_CONST without START_SEC
#else
#undef DET_WAS_STARTED_SEC_ROM_CONST
#endif
#define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#undef DET_STOP_SEC_ROM_CONST

#elif defined DET_START_SEC_ROM_CODE
#if defined DET_WAS_STARTED_SEC_ROM_CODE
#error DET_WAS_STARTED_SEC_ROM_CODE already defined
#endif
#define BSW_START_SEC_DEFAULT_CODE
#include "Bsw_MemMap.h"
#undef BSW_START_SEC_DEFAULT_CODE
#undef MEMMAP_ERROR
#undef DET_START_SEC_ROM_CODE
#define DET_WAS_STARTED_SEC_ROM_CODE

#elif defined DET_STOP_SEC_ROM_CODE
#if ! defined DET_WAS_STARTED_SEC_ROM_CODE
#error DET_STOP_SEC_ROM_CODE without START_SEC
#else
#undef DET_WAS_STARTED_SEC_ROM_CODE
#endif
#define BSW_STOP_SEC_DEFAULT_CODE
#include "Bsw_MemMap.h"
#undef BSW_STOP_SEC_DEFAULT_CODE
#undef MEMMAP_ERROR
#undef DET_STOP_SEC_ROM_CODE

#elif defined(Det_START_SEC_CODE)
#define BSW_START_SEC_DEFAULT_CODE
#include "Bsw_MemMap.h"
#undef BSW_START_SEC_DEFAULT_CODE
#undef MEMMAP_ERROR
#undef Det_START_SEC_CODE

#elif defined(Det_STOP_SEC_CODE)
#define BSW_STOP_SEC_DEFAULT_CODE
#include "Bsw_MemMap.h"
#undef BSW_STOP_SEC_DEFAULT_CODE
#undef MEMMAP_ERROR
#undef Det_STOP_SEC_CODE

#elif defined MEMMAP_ERROR
#error "Det_MemMap.h, wrong #pragma command"
#endif

