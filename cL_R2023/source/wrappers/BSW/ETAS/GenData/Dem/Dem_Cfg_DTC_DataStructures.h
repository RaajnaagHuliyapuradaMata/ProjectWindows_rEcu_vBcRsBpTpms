

#ifndef DEM_CFG_DTC_DATASTRUCTURES_H
#define DEM_CFG_DTC_DATASTRUCTURES_H

#include "Dem_Cfg_DTCs.h"
#include "Dem_Lok_Det.h"
#include "Dem_Types.h"
#include "Dem_Lib.h"
#include "rba_DiagLib.h"

// #define DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED   FALSE

#define DEM_INVALID_DTC                 0xAA000000u

typedef struct{
	uint8 data2;  // Severity
} Dem_Cfg_Dtc_8Type;

typedef struct{
	uint32 data1;  // Kind, Nv_Storage, Func_Unit, DtcCode_Is_Index, DtcCode
} Dem_Cfg_Dtc_32Type;

#define DEM_START_SEC_CONST
#include "Dem_MemMap.h"
extern const Dem_Cfg_Dtc_8Type Dem_Cfg_Dtc_8[35];
extern const Dem_Cfg_Dtc_32Type Dem_Cfg_Dtc_32[35];

LOCAL_INLINE Dem_DTCKindType Dem_Cfg_Dtc_GetKind(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
	return (Dem_DTCKindType)(RBA_DIAGLIB_GETBITS32(Dem_Cfg_Dtc_32[indx].data1, 0, 2));
}

LOCAL_INLINE Dem_DTCSeverityType Dem_Cfg_Dtc_GetSeverity(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
	return Dem_Cfg_Dtc_8[indx].data2;
}

LOCAL_INLINE boolean Dem_Cfg_Dtc_GetNv_Storage(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
	return RBA_DIAGLIB_ISBITSET32(Dem_Cfg_Dtc_32[indx].data1, 2);
}

LOCAL_INLINE uint8 Dem_Cfg_Dtc_GetFunc_Unit(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
	return (uint8)(RBA_DIAGLIB_GETSINGLEBIT32(Dem_Cfg_Dtc_32[indx].data1, 3));
}

LOCAL_INLINE boolean Dem_Cfg_Dtc_GetDtcCode_Is_Index(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
	return RBA_DIAGLIB_ISBITSET32(Dem_Cfg_Dtc_32[indx].data1, 4);
}

LOCAL_INLINE Dem_DtcCodeType Dem_Cfg_Dtc_GetObd_DtcCode(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
	return DEM_INVALID_DTC;
}

LOCAL_INLINE Dem_DtcCodeType Dem_Cfg_Dtc_GetDtcCode(Dem_DtcIdType indx)
{
	DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
	return (Dem_DtcCodeType)(RBA_DIAGLIB_GETBITS32(Dem_Cfg_Dtc_32[indx].data1, 5, 24));
}

#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.h"

// #define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_OFF STD_OFF
// #define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_ON STD_ON

#endif
