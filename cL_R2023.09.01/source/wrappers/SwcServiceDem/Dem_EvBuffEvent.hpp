

#ifndef DEM_EVBUFFEVENT_H
#define DEM_EVBUFFEVENT_H

#include "Dem_Types.hpp"
#include "Dem_Cfg_EnvMain.hpp"
#include "Dem_Cfg_EvBuff.hpp"
#include "Dem_Cfg_Nodes.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_EvBuffTypes.hpp"

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
DEM_INLINE Dem_ComponentIdType Dem_FailureEvent_getNodeId (const Dem_EvBuffEvent *fe)
{
    return Dem_NodeIdFromEventId(fe->eventId);
}
#endif

DEM_INLINE void Dem_EvBuffSetCounter (Dem_EvBuffEvent *evBuff, uint8 value)
{
#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    evBuff->counter = value;
#else
    DEM_UNUSED_PARAM(evBuff);
    DEM_UNUSED_PARAM(value);
#endif
}

DEM_INLINE uint8 Dem_EvBuffGetCounter (const Dem_EvBuffEvent *evBuff)
{
#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    return evBuff->counter;
#else
    DEM_UNUSED_PARAM(evBuff);
    return 0;
#endif
}

#endif
