

#ifndef DEM_CFG_NODEID_H
#define DEM_CFG_NODEID_H

#include "Std_Types.h"

#define DEM_NODEID_INVALID             0
#define DEM_NODEID_COUNT               6u
#define DEM_NODEID_ARRAYLENGTH         (DEM_NODEID_COUNT+1u)

#if (DEM_NODEID_ARRAYLENGTH <= 255)
typedef uint8 Dem_ComponentIdType;
#else
typedef uint16 Dem_ComponentIdType;
#endif

#define DemConf_DemNode_DemComponent_CanBus 1
#define DemConf_DemNode_DemComponent_PowerSystem 2
#define DemConf_DemNode_DemComponent_TpmsConfiguration 3
#define DemConf_DemNode_DemComponent_TpmsEcu 4
#define DemConf_DemNode_DemComponent_TpmsSensors 5
#define DemConf_DemNode_DemComponent_TpmsStatus 6

#endif

