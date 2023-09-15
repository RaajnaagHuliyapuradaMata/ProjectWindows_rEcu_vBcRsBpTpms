
#ifndef DEM_CLIENTMACHINE_DTCRECORDUPDATE_H
#define DEM_CLIENTMACHINE_DTCRECORDUPDATE_H

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

#include "Dem_Client.hpp"

DEM_INLINE void Dem_ClientMachine_DisableDTCRecordUpdate_SetClientRequest(volatile Dem_ClientResultType *result, Dem_ClientRequestType request )
{
    Dem_ClientResultType_setResult(result, request, E_OK);
}

DEM_INLINE void Dem_ClientMachine_EnableDTCRecordUpdate_SetClientRequest(volatile Dem_ClientResultType *result, Dem_ClientRequestType request )
{
    Dem_ClientResultType_setResult(result, request, E_OK);
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

#endif
