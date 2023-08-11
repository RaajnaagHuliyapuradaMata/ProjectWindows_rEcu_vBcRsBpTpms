

#ifndef CRC_H
#define CRC_H

#include "Std_Types.h"

#include "Crc_Cfg.h"

#define CRC_START_SEC_CODE
#include "Crc_MemMap.h"

extern void Crc_GetVersionInfo(Std_VersionInfoType * const VersionInfo);
extern uint16 Crc_CalculateCRC16(const uint8* Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall);
extern uint32 Crc_CalculateCRC32(const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall);
extern uint32 Crc_CalculateCRC32P4(const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall);

#define CRC_STOP_SEC_CODE
#include "Crc_MemMap.h"

#endif

