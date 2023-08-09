

#ifndef DEM_DTCGROUP_H
#define DEM_DTCGROUP_H

#include "Dem_ClientBaseHandling.h"
#include "Dem_ClientClearMachine.h"
#include "Dem_Types.h"
#include "Dem_Array.h"
#include "Dem_Cfg_DTCs.h"
#include "Dem_Cfg_DTC_DataStructures.h"

#include "Dem_Cfg_DtcId.h"
#include "Dem_Clear.h"

#define DEM_DTCGROUPS_INIT(CODE) \
{   (CODE) \
}

typedef struct {

	Dem_DTCGroupType dtcGroupCode;
} Dem_DtcGroupParam;

typedef boolean DemControlDtcGroupType;

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
extern DemControlDtcGroupType Dem_DtcGroupDisabledFlag;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE_CONST(Dem_DtcGroupParam, Dem_AllDTCGroupsParam, DEM_DTCGROUPID_ARRAYLENGTH);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
Dem_DTCGroupIdType Dem_DtcGroupIdFromDtcGroupCode (Dem_DTCGroupType dtcGrpCode);
void Dem_DtcsClearDtcInGroup(uint8 GroupId, Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

DEM_INLINE Dem_DTCGroupType Dem_DtcGroupGetCode (Dem_DTCGroupIdType dtcGroupId)
{
	return Dem_AllDTCGroupsParam[dtcGroupId].dtcGroupCode;
}

DEM_INLINE void Dem_SetDtcGroupSettingFlag(Dem_boolean_least DtcGroupDisabled)
{
    Dem_DtcGroupDisabledFlag = DtcGroupDisabled;
}

DEM_INLINE Dem_boolean_least Dem_IsAnyDtcGroupSettingDisabled(void)
{
    return Dem_DtcGroupDisabledFlag;
}

#endif
