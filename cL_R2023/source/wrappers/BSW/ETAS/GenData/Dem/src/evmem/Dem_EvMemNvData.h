

#ifndef DEM_EVMEMNVDATA_H
#define DEM_EVMEMNVDATA_H

#include "Dem_EvMemTypes.h"
#include "Dem_Array.h"

#if DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK

    #define DEM_CFG_EVMEM_EVENTMEMORY_LENGTH    (2u * DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL)
#else
    #define DEM_CFG_EVMEM_EVENTMEMORY_LENGTH    DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL
#endif

#define DEM_START_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.h"
DEM_ARRAY_DECLARE(Dem_EvMemEventMemoryType, Dem_EvMemEventMemory, DEM_CFG_EVMEM_EVENTMEMORY_LENGTH);
#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.h"

#endif
