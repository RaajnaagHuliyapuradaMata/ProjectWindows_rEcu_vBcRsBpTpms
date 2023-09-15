

#ifndef DEM_CFG_DTC_DATASTRUCTURES_H
#define DEM_CFG_DTC_DATASTRUCTURES_H

#include "Dem_Cfg_DTCs.hpp"
#include "Dem_Lok_Det.hpp"
#include "Dem_Types.hpp"
#include "Dem_Lib.hpp"

//#define DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED   FALSE

typedef struct
{
	Dem_DtcCodeType DtcCode;
	Dem_DTCSeverityType Severity;
	uint8 Func_Unit;
	Dem_DTCKindType Kind;
	boolean DtcCode_Is_Index;
	boolean Nv_Storage;
}Dem_Cfg_DtcType;

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
extern const Dem_Cfg_DtcType Dem_Cfg_Dtc[42];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
LOCAL_INLINE Dem_DTCKindType Dem_Cfg_Dtc_GetKind(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return Dem_Cfg_Dtc[indx].Kind;
}

LOCAL_INLINE Dem_DTCSeverityType Dem_Cfg_Dtc_GetSeverity(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return Dem_Cfg_Dtc[indx].Severity;
}

LOCAL_INLINE boolean Dem_Cfg_Dtc_GetNv_Storage(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return Dem_Cfg_Dtc[indx].Nv_Storage;
}

LOCAL_INLINE uint8 Dem_Cfg_Dtc_GetFunc_Unit(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return Dem_Cfg_Dtc[indx].Func_Unit;
}

LOCAL_INLINE boolean Dem_Cfg_Dtc_GetDtcCode_Is_Index(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return Dem_Cfg_Dtc[indx].DtcCode_Is_Index;
}
LOCAL_INLINE Dem_DtcCodeType Dem_Cfg_Dtc_GetObd_DtcCode(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return DEM_INVALID_DTC;
}

LOCAL_INLINE Dem_DtcCodeType Dem_Cfg_Dtc_GetDtcCode(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
	return Dem_Cfg_Dtc[indx].DtcCode;
}



//#define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_OFF STD_OFF
//#define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_ON STD_ON

#endif
