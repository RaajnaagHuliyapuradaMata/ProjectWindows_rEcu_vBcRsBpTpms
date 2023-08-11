
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dem_PrjEraseAllNvMDataHandling.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

Dem_EraseAllRequestType Dem_PrjEraseAllNvMDataHandling(Dem_HashIdCheckResultType HashIdCheckResult)
{
    Dem_EraseAllRequestType eraseAll = DEM_ERASE_ALL_REQUEST_NONE;

    if(HashIdCheckResult == DEM_HASH_ID_MISMATCH)
    {
        eraseAll = DEM_ERASE_ALL_REQUEST_ALL;
    }

    return eraseAll;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

