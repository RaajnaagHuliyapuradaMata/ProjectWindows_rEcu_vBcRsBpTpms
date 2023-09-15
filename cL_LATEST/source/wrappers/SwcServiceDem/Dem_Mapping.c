

#include "Dem_Cfg_EventId.hpp"
#include "Dem_Cfg_NodeId.hpp"
#include "Dem_Cfg_DtcId.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_Array.hpp"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"
DEM_MAP_EVENTID_DTCID
DEM_MAP_DTCID_EVENTID

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)

Dem_MAP_J1939NODEIDTODTCID

DEM_MAP_DTCIDTOJ1939NODEID
#endif

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

DEM_MAP_EVENTID_NODEID
DEM_MAP_NODEID_EVENTID
DEM_MAP_NODEID_CHILDNODEID
DEM_CFG_NODETOCHILDNODEINDEX
#endif
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"
#define DEM_START_SEC_CONST
#include "Dem_MemMap.hpp"
const Dem_DtcGroupIdMapToDtcIdType Dem_DtcGroupIdMapToDtcId[DEM_DTCGROUPID_ARRAYLENGTH] = DEM_MAP_DTCGROUPID_DTCID;
#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.hpp"
