

#ifndef DEM_CLEAR_H
#define DEM_CLEAR_H

#include "Dem_Cfg_Clear.hpp"
#include "Dem_Types.hpp"
#include "Dem_Cfg_Events.hpp"
#include "Dem_Mapping.hpp"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

void Dem_ClearMainFunction(void);
boolean Dem_ClearIsInProgress (void);

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

#endif
