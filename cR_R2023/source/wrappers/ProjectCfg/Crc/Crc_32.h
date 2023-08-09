

#ifndef CRC_32_H
#define CRC_32_H

#define CRC_INITIAL_VALUE32             ((uint32)0xFFFFFFFFUL)

#define CRC_XOR_VALUE32                 ((uint32)0xFFFFFFFFUL)

#define  CRC_32_REVH04C11DB7_JUNK       ((uint8)8U)

#define  CRC_32_TABLESIZE        256U
#define  CRC_32_TABLEMASK        0xFFU

#define CRC_START_SEC_CONST_32
#include "Crc_MemMap.h"
extern const uint32 CRC_32_REVH04C11DB7_Tbl[];
#define CRC_STOP_SEC_CONST_32
#include "Crc_MemMap.h"

#define CRC_START_SEC_CODE
#include "Crc_MemMap.h"
extern uint32 Crc_CalculateCRC32(const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32,
                                 boolean Crc_IsFirstCall);
#define CRC_STOP_SEC_CODE
#include "Crc_MemMap.h"

#endif
