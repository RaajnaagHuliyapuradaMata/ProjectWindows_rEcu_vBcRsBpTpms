

#ifndef DEM_EVENTSTATUSNVDATA_H
#define DEM_EVENTSTATUSNVDATA_H

#include "Platform_Types.hpp"
#include "Dem_Array.hpp"
#include "Dem_Cfg_Events.hpp"
#include "Dem_BitArray.hpp"

#define DEM_START_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"

DEM_ARRAY_DECLARE(uint8, Dem_AllEventsStatusByte, DEM_EVENTID_ARRAYLENGTH);

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
DEM_BITARRAY_DECLARE  (Dem_AllEventsHistoryStatus, DEM_EVENTID_ARRAYLENGTH);
#endif

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"

#endif
