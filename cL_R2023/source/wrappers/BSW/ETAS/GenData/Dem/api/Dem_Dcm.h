

#ifndef DEM_DCM_H
#define DEM_DCM_H

#include "Dem_Types.h"
#include "Dcm_Types.h"

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
#include "rba_DemObdBasic_Dcm.h"
#endif

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

Dem_DTCTranslationFormatType Dem_GetTranslationType(uint8 ClientId);

Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8 ClientId, Dem_UdsStatusByteType* DTCStatusMask);

Std_ReturnType Dem_GetStatusOfDTC(uint8 ClientId, uint8* DTCStatus);

Std_ReturnType Dem_GetSeverityOfDTC(uint8 ClientId, Dem_DTCSeverityType* DTCSeverity);

Std_ReturnType Dem_GetFunctionalUnitOfDTC(uint8 ClientId, uint8* DTCFunctionalUnit );

Std_ReturnType Dem_SetDTCFilter(uint8 ClientId,
                                         uint8 DTCStatusMask,
                                         Dem_DTCFormatType DTCFormat,
                                         Dem_DTCOriginType DTCOrigin,
                                         boolean FilterWithSeverity,
                                         Dem_DTCSeverityType DTCSeverityMask,
                                         boolean FilterForFaultDetectionCounter);

Std_ReturnType Dem_GetNumberOfFilteredDTC(uint8 ClientId, uint16* NumberOfFilteredDTC);

Std_ReturnType Dem_GetNextFilteredDTC(uint8 ClientId, uint32* DTC, uint8* DTCStatus);

Std_ReturnType Dem_GetNextFilteredDTCAndFDC(uint8 ClientId, uint32* DTC, sint8* DTCFaultDetectionCounter);

Std_ReturnType Dem_GetNextFilteredDTCAndSeverity(uint8 ClientId,
                                                                   uint32* DTC,
                                                                   uint8* DTCStatus,
                                                                   Dem_DTCSeverityType* DTCSeverity,
                                                                   uint8* DTCFunctionalUnit);

Std_ReturnType Dem_SetFreezeFrameRecordFilter(uint8 ClientId, Dem_DTCFormatType DTCFormat, uint16* NumberOfFilteredRecords);

Std_ReturnType Dem_GetNextFilteredRecord(uint8 ClientId, uint32* DTC, uint8* RecordNumber);

#if (DEM_CFG_EVMEMGENERIC_SUPPORTED != FALSE)

Std_ReturnType Dem_GetDTCByOccurrenceTime(uint8 ClientId, Dem_DTCRequestType DTCRequest, uint32* DTC);
#endif

Std_ReturnType Dem_DisableDTCRecordUpdate(uint8 ClientId);

Std_ReturnType Dem_EnableDTCRecordUpdate(uint8 ClientId);

Std_ReturnType Dem_SelectExtendedDataRecord(uint8 ClientId, uint8 ExtendedDataNumber);

Std_ReturnType Dem_GetNextExtendedDataRecord(uint8 ClientId, uint8* DestBuffer, uint16* BufSize);

Std_ReturnType Dem_GetSizeOfExtendedDataRecordSelection(uint8 ClientId, uint16* SizeOfExtendedDataRecord);

Std_ReturnType Dem_SelectFreezeFrameData(uint8 ClientId, uint8 RecordNumber);

Std_ReturnType Dem_GetNextFreezeFrameData(uint8 ClientId, uint8* DestBuffer, uint16* BufSize);

Std_ReturnType Dem_GetSizeOfFreezeFrameSelection(uint8 ClientId, uint16* SizeOfFreezeFrame);

#ifndef DEM_HIDE_RTE_APIS

Std_ReturnType Dem_ClearDTC(uint8 ClientId);

Std_ReturnType Dem_SelectDTC(uint8 ClientId, uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);

#endif

Std_ReturnType Dem_DisableDTCSetting(uint8 ClientId);

Std_ReturnType Dem_EnableDTCSetting(uint8 ClientId);

Std_ReturnType Dem_GetDTCSelectionResult(uint8 ClientId);

Std_ReturnType Dem_GetDTCSelectionResultForClearDTC(uint8 ClientId);

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#endif
