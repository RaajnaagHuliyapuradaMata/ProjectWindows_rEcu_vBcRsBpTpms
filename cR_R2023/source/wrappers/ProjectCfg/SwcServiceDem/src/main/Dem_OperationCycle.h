

#ifndef DEM_OPERATIONCYCLE_H
#define DEM_OPERATIONCYCLE_H

#include "Dem_Cfg_OperationCycle.h"
#include "Dem_Cfg_OperationCycle_DataStructures.h"
#include "Dem_Types.h"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

extern Dem_OperationCycleList Dem_OperationCycleStates;

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

DEM_INLINE boolean Dem_IsOperationCycleStarted(Dem_OperationCycleIdType OperationCycleId)
{
    return DEM_OPERATIONCYCLE_ISBITSET(Dem_OperationCycleStates, OperationCycleId);
}

void Dem_OperationCycleInit(void);
void Dem_OperationCycleInitCheckNvm(void);
boolean Dem_OperationCyclesMainFunction(void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#endif

