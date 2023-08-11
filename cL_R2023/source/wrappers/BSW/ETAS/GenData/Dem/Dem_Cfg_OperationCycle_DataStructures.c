

#include "Dem_Cfg_OperationCycle_DataStructures.h"

#define DEM_START_SEC_CONST
#include "Dem_MemMap.h"

const Dem_Cfg_OperationCycleType Dem_Cfg_OperationCycle[3] = {
	{ 0x0, TRUE },
	{ 0x0, TRUE },
	{ 0x0, TRUE }
};

#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.h"

