

#ifndef DET_H
#define DET_H

#include "Det_Types.h"
#include "Det_Cfg.h"

#define DET_START_SEC_ROM_CODE
#include "Det_MemMap.h"

#if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED)
Std_ReturnType Det_GetLastBufferIndex(Det_BufferIndexType* buffIdx);
#endif

#if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED)
Std_ReturnType Det_GetBufferEntry(Det_BufferIndexType buffIdx, Det_ErrorEntryBufferType* buffEntry);
#endif

void Det_Init(const Det_ConfigType* ConfigPtr);

void Det_Start(void);

#if (DET_CFG_VERSIONINFO_SUPPORTED)
void Det_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

#if (DET_CFG_CHECK_API_CONSISTENCY)

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId);
#endif

#define DET_STOP_SEC_ROM_CODE
#include "Det_MemMap.h"

#endif
