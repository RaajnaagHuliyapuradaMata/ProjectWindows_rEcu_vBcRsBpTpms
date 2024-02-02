

#ifndef DEM_CFG_OPERATIONCYCLE_DATASTRUCTURES_H
#define DEM_CFG_OPERATIONCYCLE_DATASTRUCTURES_H

#include "Dem_Types.hpp"
#include "Dem_Lib.hpp"
#include "Dem_Cfg_OperationCycle.hpp"

typedef struct
{
   Dem_OperationCycleList DependentCycleMask;
   boolean IsAllowedToBeStartedDirectly;
}Dem_Cfg_OperationCycleType;


#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

extern const Dem_Cfg_OperationCycleType Dem_Cfg_OperationCycle[3];

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

LOCAL_INLINE Dem_OperationCycleList Dem_Cfg_OperationCycle_GetDependentCycleMask(Dem_OperationCycleIdType indx)
{
   DEM_ASSERT_RANGECHECK(indx < 3);
   return Dem_Cfg_OperationCycle[indx].DependentCycleMask;
}

LOCAL_INLINE boolean Dem_Cfg_OperationCycle_GetIsAllowedToBeStartedDirectly(Dem_OperationCycleIdType indx)
{
   DEM_ASSERT_RANGECHECK(indx < 3);
   return Dem_Cfg_OperationCycle[indx].IsAllowedToBeStartedDirectly;
}


#endif
