

#ifndef DCM_APP_INTERFACE_H
#define DCM_APP_INTERFACE_H

#include "DcmAppInterfaceX.h"

#define SECA_LEVEL_APPLICATION  3
#define SECA_LEVEL_PROGRAMMING  5

static void CalculateSeed(uint8* Seed);

static void ComputeKeyFromSeed(uint8 ucSecaLevel, uint8* seed, uint16 sizeSeed, uint8* key, uint16 maxSizeKey, uint16* sizeKey);

static boolean DCM_IsMemoryInitialized(uint8* ucBuffer, uint8 ucLength);

#endif
