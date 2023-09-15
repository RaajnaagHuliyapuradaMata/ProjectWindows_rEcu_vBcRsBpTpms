

#ifndef DEM_INDICATORATTRIBUTESNVDATA_H
#define DEM_INDICATORATTRIBUTESNVDATA_H

#include "Dem_IndicatorAttributesTypes.hpp"
#include "Dem_Array.hpp"
#include "Dem_Cfg_EventId.hpp"
#include "Dem_Cfg_EventIndicators.hpp"

#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
#define DEM_START_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"
DEM_ARRAY_DECLARE(Dem_EvtIndicatorAttributeState, Dem_AllEventsIndicatorState, DEM_INDICATOR_ATTRIBUTE_ARRAYLENGTH);
#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"

#endif

#endif
