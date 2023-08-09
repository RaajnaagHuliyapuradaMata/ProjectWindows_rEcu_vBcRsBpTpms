

#ifndef DEM_INTERNALENVDATA_H
#define DEM_INTERNALENVDATA_H

#include "Dem_Types.h"
#include "Dem_EvMemTypes.h"

typedef struct
{

	Dem_EventIdType eventId;
#if (DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
	
	Dem_DebugDataType debug0;
	
	Dem_DebugDataType debug1;
#endif
	
	Dem_EvMemEventMemoryType *evMemLocation;
} Dem_InternalEnvData;

#endif

