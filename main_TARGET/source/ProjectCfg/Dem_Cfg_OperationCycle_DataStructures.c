#include "Std_Types.hpp"

#include "Dem_Cfg_OperationCycle_DataStructures.hpp"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
const Dem_Cfg_OperationCycleType Dem_Cfg_OperationCycle[3] = {
   { 0x0, TRUE },
   { 0x0, TRUE },
   { 0x0, TRUE }
};

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

