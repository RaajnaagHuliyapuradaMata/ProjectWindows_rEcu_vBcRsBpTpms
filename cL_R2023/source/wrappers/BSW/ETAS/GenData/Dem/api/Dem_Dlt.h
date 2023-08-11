

#ifndef DEM_DLT_H
#define DEM_DLT_H

#include "Dem_Types.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

Std_ReturnType Dem_DltGetAllExtendedDataRecords(Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize);

Std_ReturnType Dem_DltGetMostRecentFreezeFrameRecordData(Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize);

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#endif
