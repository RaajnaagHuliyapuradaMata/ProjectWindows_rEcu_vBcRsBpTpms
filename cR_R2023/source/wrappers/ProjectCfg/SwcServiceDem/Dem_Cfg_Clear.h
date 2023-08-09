

#ifndef DEM_CFG_CLEAR_H
#define DEM_CFG_CLEAR_H

#include "Dem_Types.h"

#define DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH     1
#define DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_TRIGGER    2
#define DEM_CFG_CLEAR_DTC_BEHAVIOR_VOLATILE               3
#define DEM_CFG_CLEAR_DTC_BEHAVIOR                        DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH

#define DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS     1
#define DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS    2
#define DEM_CFG_CLEAR_DTC_LIMITATION                        DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS

#define DEM_CFG_CLEAR_MAX_NO_OF_EVENTS_PER_CYCLE    41u

DEM_INLINE void Dem_ClearDtcNotificationStartCallbacks(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    DEM_UNUSED_PARAM(DTC);
    DEM_UNUSED_PARAM(DTCFormat);
    DEM_UNUSED_PARAM(DTCOrigin);
}
DEM_INLINE void Dem_ClearDtcNotificationFinishCallbacks(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    DEM_UNUSED_PARAM(DTC);
    DEM_UNUSED_PARAM(DTCFormat);
    DEM_UNUSED_PARAM(DTCOrigin);
}

#endif

