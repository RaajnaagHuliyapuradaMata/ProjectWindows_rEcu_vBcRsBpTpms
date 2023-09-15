

#ifndef DEM_INDICATORATTRIBUTESTYPES_H
#define DEM_INDICATORATTRIBUTESTYPES_H

#include "Platform_Types.hpp"
#include "Dem_Cfg_EventIndicators.hpp"

#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)

typedef struct{
   uint8 failureCycleCounterVal;
   uint8 healingCycleCounterVal;
}Dem_EvtIndicatorAttributeState;

#endif

#endif
