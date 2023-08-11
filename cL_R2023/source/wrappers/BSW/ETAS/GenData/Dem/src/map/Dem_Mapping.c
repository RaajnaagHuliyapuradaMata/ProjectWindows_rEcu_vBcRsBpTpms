

#include "Dem_Cfg_EventId.h"
#include "Dem_Cfg_NodeId.h"
#include "Dem_Cfg_DtcId.h"
#include "Dem_Mapping.h"
#include "Dem_Array.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
DEM_MAP_EVENTID_DTCID
DEM_MAP_DTCID_EVENTID

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)

Dem_MAP_J1939NODEIDTODTCID

DEM_MAP_DTCIDTOJ1939NODEID
#endif

#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

DEM_MAP_EVENTID_NODEID
DEM_MAP_NODEID_EVENTID
DEM_MAP_NODEID_CHILDNODEID
DEM_CFG_NODETOCHILDNODEINDEX
#endif
#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
#define DEM_START_SEC_CONST
#include "Dem_MemMap.h"
const Dem_DtcGroupIdMapToDtcIdType Dem_DtcGroupIdMapToDtcId[DEM_DTCGROUPID_ARRAYLENGTH] = DEM_MAP_DTCGROUPID_DTCID;
#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.h"