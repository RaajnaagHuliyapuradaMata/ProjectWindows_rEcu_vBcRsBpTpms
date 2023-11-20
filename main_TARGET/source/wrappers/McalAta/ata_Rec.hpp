
#ifndef ATA_REC_H
#define ATA_REC_H

#include "ata_Rec_X.hpp"

#define c50msCnt        25

static uint8 GetAtaTelegramLength(uint8 ucTelType);
static uint8 appBuild8CRC(const uint8 *pui8Buffer, uint8 ui8MessageLen, uint8 ui8BitsInFirstByte, uint8 ui8Polynom, uint8 ui8CrcStartValue);

#endif