

#ifndef DEM_EVTRELATEDDATA_H
#define DEM_EVTRELATEDDATA_H

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

#if(DEM_CFG_CHECKAPICONSISTENCY == TRUE)

Std_ReturnType Dem_GetEventExtendedDataRecordForRTE(
        Dem_EventIdType EventId
   ,       uint8 RecordNumber
   ,       uint8* DestBuffer
);

Std_ReturnType Dem_GetEventExtendedDataRecord_GeneralEvtInfo(
        Dem_EventIdType EventId
   ,       uint8 RecordNumber
   ,       uint8* DestBuffer
);

Std_ReturnType Dem_GetEventFreezeFrameDataForRTE(
        Dem_EventIdType EventId
   ,       uint8 RecordNumber
   ,       boolean ReportTotalRecord
   ,       uint16 DataId
   ,       Dem_MaxDataValueType DestBuffer
);

Std_ReturnType Dem_GetEventFreezeFrameData_GeneralEvtInfo(
        Dem_EventIdType EventId
   ,       uint8 RecordNumber
   ,       boolean ReportTotalRecord
   ,       uint16 DataId
   ,       Dem_MaxDataValueType DestBuffer
);

Std_ReturnType Dem_GetEventFreezeFrameDataEx_GeneralEvtInfo(
        Dem_EventIdType EventId
   ,       uint8 RecordNumber
   ,       uint16 DataId
   ,       uint8* DestBuffer
   ,       uint16* BufSize
);

Std_ReturnType Dem_GetEventExtendedDataRecordEx_GeneralEvtInfo(
        Dem_EventIdType EventId
   ,       uint8 RecordNumber
   ,       uint8* DestBuffer
   ,       uint16* BufSize
);

#endif

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

#endif
