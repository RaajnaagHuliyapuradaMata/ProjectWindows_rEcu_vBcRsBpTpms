

#ifndef DEM_DISTURBANCEMEMORYNVDATA_H
#define DEM_DISTURBANCEMEMORYNVDATA_H

#include "Dem_DisturbanceMemoryTypes.hpp"
#include "Dem_Array.hpp"

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)

#define DEM_START_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"
DEM_ARRAY_DECLARE(Dem_DistMemLocationType, Dem_DistMemLocations, (DEM_CFG_DISTURBANCE_MEMORY_ARRAYLENGTH));
#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"

#endif
#endif
