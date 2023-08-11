

#ifndef DCM_APP_INTERFACE_H
#define DCM_APP_INTERFACE_H

#include "DcmAppInterfaceX.h"

#define cCHECKARRAYSIZE 1
#define cCREATESEED 2
#define cCALCULATEKEY 3

#define EOL_ROUT_NEVER_STARTED            0x00U
#define EOL_ROUT_RUNNING                  0x01U
#define EOL_ROUT_FINISHED_SUCCESSFULLY    0x02U
#define EOL_ROUT_RESERVED                 0x03U
#define EOL_ROUT_STOPPED_ON_REQUEST       0x04U
#define EOL_ROUT_START_WRONG_PARAM        0x05U
#define EOL_ROUT_ENDED_WITH_ERROR         0x07U

static void CalculateSeed(uint8* Seed);

static void DecryptAes256CbcMessage(uint8* Message, uint16 ucSizeMessage);

// static boolean DCM_IsMemoryInitialized(uint8* ucBuffer, uint8 ucLength);

#endif
