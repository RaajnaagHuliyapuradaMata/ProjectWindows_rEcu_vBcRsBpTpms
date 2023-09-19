

#ifndef DEM_CFG_EVENTSCALLBACK_H
#define DEM_CFG_EVENTSCALLBACK_H

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

void Dem_CallbackDTCStatusChangedIndication (uint32 DTC, Dem_UdsStatusByteType DTCStatusOld, Dem_UdsStatusByteType DTCStatusNew);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.hpp"

#define DEM_EVT_ST_CH_CONTAINERCALLBACKS \

#define DEM_EVT_ST_CH_CALLBACK_FUNCTIONS \

#define DEM_DTC_ST_CH_CALLBACK_FUNCTION \
void Dem_CallbackDTCStatusChangedIndication (uint32 DTC, Dem_UdsStatusByteType DTCStatusOld, Dem_UdsStatusByteType DTCStatusNew) { \
   (void) Dem_CallbackDtcStatusChanged (DTC, DTCStatusOld, DTCStatusNew); \
}\
\

#endif

