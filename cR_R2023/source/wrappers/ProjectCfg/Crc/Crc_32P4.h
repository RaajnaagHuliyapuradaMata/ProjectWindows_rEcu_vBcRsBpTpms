

#ifndef CRC_32P4_H
#define CRC_32P4_H

#define CRC_INITIAL_VALUE32P4             ((uint32)0xFFFFFFFFUL)

#define CRC_XOR_VALUE32P4                 ((uint32)0xFFFFFFFFUL)

#define  CRC_32P4_CHUNK ((uint8)8U)

#define  CRC_32P4_TABLESIZE        256U
#define  CRC_32P4_TABLEMASK        0xFFU

#define CRC_START_SEC_CONST_32
#include "Crc_MemMap.h"
extern const uint32 CRC_32_REVHF4ACFB13_Tbl[];
#define CRC_STOP_SEC_CONST_32
#include "Crc_MemMap.h"

#define CRC_START_SEC_CODE
#include "Crc_MemMap.h"
extern uint32 Crc_CalculateCRC32P4(const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32,
                                 boolean Crc_IsFirstCall);
#define CRC_STOP_SEC_CODE
#include "Crc_MemMap.h"

#endif
