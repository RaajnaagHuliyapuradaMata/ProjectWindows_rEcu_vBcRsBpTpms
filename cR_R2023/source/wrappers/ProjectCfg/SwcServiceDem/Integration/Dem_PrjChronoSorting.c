
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dem_ChronoSort.h"
#include "Dem_PrjEvmemProjectExtension.h"
#include "Dem_EvMem.h"
#include "Dem_Dtcs.h"

#if (DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

boolean Dem_IsChronoSortEnabled(void)
{

    return FALSE;
}

static uint32 Dem_ChronoSortGetNewEvMemSortId(uint16_least MemId)
{

}

void Dem_ChronoSortEvMemUpdateSortId(uint16_least LocId,uint16_least MemId,uint16_least StatusOld,uint16_least StatusNew,uint16_least *WriteSts)
{

}

void Dem_ChronoSortDTCFilterInit(void)
{

}

boolean Dem_ChronoSortSetDTCFilter(Dem_DTCFilterState* DTCFilter)
{

    return FALSE;
}

void Dem_ChronoSortMainFunction(Dem_DTCFilterState* DTCFilter)
{

}

Dem_ReturnGetNextFilteredDTCType Dem_ChronoSortGetNextFilteredDTCID (Dem_DtcIdType* dtcId, uint32* DTC, uint8* DTCStatus)
{

}

Dem_ReturnGetNumberOfFilteredDTCType Dem_ChronoSortGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC)
{

}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif
