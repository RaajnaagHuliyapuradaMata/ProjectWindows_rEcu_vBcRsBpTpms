

#ifndef CRC_16_H
#define CRC_16_H

#define CRC_INITIAL_VALUE16      ((uint16)0xFFFFU)

#define CRC_XOR_VALUE16          ((uint16)0U)

#define CRC_16_H1021_JUNK       8U
#define CRC_16_H1021_JUNKREST   8U

#define CRC_16_TABLESIZE         256U
#define CRC_16_TABLEMASK         0xFFU

#define CRC_START_SEC_CONST_16
#include "Crc_MemMap.hpp"
extern const uint16 CRC_16_H1021_Tbl[];
#define CRC_STOP_SEC_CONST_16
#include "Crc_MemMap.hpp"

#define CRC_START_SEC_CODE
#include "Crc_MemMap.hpp"
extern uint16 Crc_CalculateCRC16(const uint8* Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16
   ,     boolean Crc_IsFirstCall);
#define CRC_STOP_SEC_CODE
#include "Crc_MemMap.hpp"

#endif
