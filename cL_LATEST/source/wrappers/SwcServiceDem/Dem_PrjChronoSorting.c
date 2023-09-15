
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dem_ChronoSort.hpp"
#include "Dem_PrjEvmemProjectExtension.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_Dtcs.hpp"

#if(DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

boolean Dem_IsChronoSortEnabled(uint8 ClientId)
{

    return FALSE;
}

static uint32 Dem_ChronoSortGetNewEvMemSortId(uint16_least MemId)
{
}

void Dem_ChronoSortEvMemUpdateSortId(uint16_least LocId,uint16_least MemId,uint16_least StatusOld,uint16_least StatusNew,uint16_least *WriteSts)
{
}

void Dem_ChronoSortDTCFilterInit(uint8 ClientId)
{
}

boolean Dem_ChronoSortSetDTCFilter(Dem_DTCFilterState* dtcFilter_p)
{

    return FALSE;
}

void Dem_ChronoSortMainFunction(Dem_DTCFilterState* dtcFilter_p)
{
}

Std_ReturnType Dem_ChronoSortGetNextFilteredDTCID (uint8 ClientId, Dem_DtcIdType* dtcId, uint32* DTC, uint8* DTCStatus)
{
}

Std_ReturnType Dem_ChronoSortGetNumberOfFilteredDTC(uint8 ClientId, uint16* NumberOfFilteredDTC)
{
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

#endif
