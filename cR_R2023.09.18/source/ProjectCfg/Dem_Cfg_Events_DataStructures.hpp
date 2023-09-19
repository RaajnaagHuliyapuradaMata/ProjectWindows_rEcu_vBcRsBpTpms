
#ifndef DEM_CFG_EVENTS_DATASTRUCTURES_H
#define DEM_CFG_EVENTS_DATASTRUCTURES_H

#include "Dem.hpp"
#include "Dem_Lib.hpp"
#include "rba_DiagLib.hpp"
#include "Dem_Lock.hpp"
#include "Dem_Cfg_StorageCondition.hpp"
#include "Dem_Cfg_EnableCondition.hpp"

typedef Std_ReturnType (*Dem_EvtClearAllowedFncType) ( boolean* Allowed );

#define DEM_RECOV    (1u)
#define DEM_NOTREC   (0u)

#define DEM_DEBOUNCE_RESET    (1u)
#define DEM_DEBOUNCE_FREEZE   (0u)

#define DEM_NO_TF_RESET   (1u)
#define DEM_TF_RESET      (0u)

#define DEM_ONLY_THIS_CYCLE_AND_READINESS   (1u)
#define DEM_NO_STATUS_BYTE_CHANGE           (0u)

typedef struct
{
	uint32 dataDataContainer_1;  // TriggersDataChangedCallback, Significance, OperationCycleID, AgingCycleID, FailureCycleID, DebounceMethodIndex, DebounceParamSettingIndex, EventPriority, MaxNumberFreezeFrameRecords
}Dem_EvtParam_32Type;


extern const Dem_EvtParam_32Type Dem_EvtParam_32[42];


LOCAL_INLINE uint8 Dem_EvtParam_GetDebounceBehavior(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return DEM_DEBOUNCE_FREEZE;
}
LOCAL_INLINE boolean Dem_EvtParam_GetIsRecoverable(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return DEM_RECOV;
}
LOCAL_INLINE boolean Dem_EvtParam_GetStoreTestFailedToNextOC(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return TRUE;
}
LOCAL_INLINE boolean Dem_EvtParam_GetRequestsWarningIndicator(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return FALSE;
}
LOCAL_INLINE Dem_EventCategoryType Dem_EvtParam_GetCategory(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 0;
}
LOCAL_INLINE boolean Dem_EvtParam_GetEventIsStoredInPrimary(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return TRUE;
}
LOCAL_INLINE boolean Dem_EvtParam_GetEventIsStoredInSecondary(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return FALSE;
}
LOCAL_INLINE boolean Dem_EvtParam_GetEventIsStoredInMirror(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return FALSE;
}
LOCAL_INLINE boolean Dem_EvtParam_GetAgingAllowed(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 0uL;
}
LOCAL_INLINE boolean Dem_EvtParam_GetIsGlobalFDCCallbackConfigured(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return FALSE;
}

LOCAL_INLINE boolean Dem_EvtParam_GetTriggersDataChangedCallback(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return RBA_DIAGLIB_ISBITSET32(Dem_EvtParam_32[indx].dataDataContainer_1, 0);
}

LOCAL_INLINE uint8 Dem_EvtParam_GetSignificance(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return (uint8)(RBA_DIAGLIB_GETSINGLEBIT32(Dem_EvtParam_32[indx].dataDataContainer_1, 1));
}

LOCAL_INLINE uint8 Dem_EvtParam_GetOperationCycleID(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return (uint8)(RBA_DIAGLIB_GETBITS32(Dem_EvtParam_32[indx].dataDataContainer_1, 2, 2));
}

LOCAL_INLINE uint8 Dem_EvtParam_GetAgingCycleID(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return (uint8)(RBA_DIAGLIB_GETBITS32(Dem_EvtParam_32[indx].dataDataContainer_1, 4, 2));
}

LOCAL_INLINE uint8 Dem_EvtParam_GetFailureCycleID(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return (uint8)(RBA_DIAGLIB_GETBITS32(Dem_EvtParam_32[indx].dataDataContainer_1, 6, 2));
}
LOCAL_INLINE boolean Dem_EvtParam_GetInitialSuppressionStatus(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 0uL;
}

LOCAL_INLINE uint8 Dem_EvtParam_GetDebounceMethodIndex(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return (uint8)(RBA_DIAGLIB_GETBITS32(Dem_EvtParam_32[indx].dataDataContainer_1, 8, 2));
}

LOCAL_INLINE uint16 Dem_EvtParam_GetDebounceParamSettingIndex(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return (uint16)(RBA_DIAGLIB_GETBITS32(Dem_EvtParam_32[indx].dataDataContainer_1, 10, 6));
}
LOCAL_INLINE uint8 Dem_EvtParam_GetBufferTimeSFB(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 0;
}
LOCAL_INLINE uint8 Dem_EvtParam_GetAgingThreshold(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 0u;
}
LOCAL_INLINE uint8 Dem_EvtParam_GetAgingThresholdForTFSLC(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 0u;
}
LOCAL_INLINE uint8 Dem_EvtParam_GetFailureConfirmationThreshold(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 1u;
}

LOCAL_INLINE uint8 Dem_EvtParam_GetEventPriority(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return (uint8)(RBA_DIAGLIB_GETBITS32(Dem_EvtParam_32[indx].dataDataContainer_1, 16, 3));
}

LOCAL_INLINE uint8 Dem_EvtParam_GetMaxNumberFreezeFrameRecords(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return (uint8)(RBA_DIAGLIB_GETSINGLEBIT32(Dem_EvtParam_32[indx].dataDataContainer_1, 19));
}
LOCAL_INLINE Dem_StoCoList Dem_EvtParam_GetStorageConditions(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 0;
}
LOCAL_INLINE Dem_EnCoList Dem_EvtParam_GetEnableConditions(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return 0;
}
LOCAL_INLINE uint8 Dem_EvtParam_GetCallbackEventStatusChangedIndex(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return FALSE;
}
LOCAL_INLINE Dem_EvtClearAllowedFncType Dem_EvtParam_GetCallbackClearAllowed(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return NULL_PTR;
}
LOCAL_INLINE uint8 Dem_EvtParam_GetClearAllowedBehavior(Dem_EventIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return DEM_NO_STATUS_BYTE_CHANGE;
}



#endif

