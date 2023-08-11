

#include "Dem_Cfg_DTC_DataStructures.h"
#define DEM_START_SEC_CONST
#include "Dem_MemMap.h"

const Dem_Cfg_Dtc_8Type Dem_Cfg_Dtc_8[35] = {
	
	{ 0 },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY },
	{ DEM_SEVERITY_NO_SEVERITY }
};

const Dem_Cfg_Dtc_32Type Dem_Cfg_Dtc_32[35] = {
	
	{ 0 },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x9CC000u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xC03788u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xC14129u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xC14729u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xDEF129u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xDEF229u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xDEF329u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xDEF429u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xDEF529u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xDEF629u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xF003A2u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0xF003A3u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x500042u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560116u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560131u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560149u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x56014Bu&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560216u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560231u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560249u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x56024Bu&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560316u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560331u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560349u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x56034Bu&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560416u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560431u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560449u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x56044Bu&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560504u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560531u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x56064Au&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560793u&0xFFFFFFu) << 5) },
	{ ( (uint32)(DEM_DTC_KIND_ALL_DTCS&0x3u) << 0) + ( (uint32)(1u&0x1u) << 2) + ( (uint32)(0x00u&0x1u) << 3) + ( (uint32)(0u&0x1u) << 4) + ( (uint32)(0x560929u&0xFFFFFFu) << 5) }
};


#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.h"
