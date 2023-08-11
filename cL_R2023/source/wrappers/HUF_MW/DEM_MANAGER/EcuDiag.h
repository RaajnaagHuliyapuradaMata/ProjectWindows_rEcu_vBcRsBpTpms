

#ifndef ECUDIAG_H
#define ECUDIAG_H

#include "Platform_Types.h"
#include "EcuDiagX.h"

#define EcuNoInternalError           ((uint8) 0x00u)
#define EcuUnknownError              ((uint8) 0x01u)
#define EcuTpmsCyclicFunctionDelayed ((uint8) 0x02u)
#define EcuRamTestFailed             ((uint8) 0x04u)
#define EcuRomTestFailed             ((uint8) 0x08u)
#define EcuRfReceiverDefect          ((uint8) 0x20u)

#define cDiagRunning        ((uint8) 0)
#define cDiagError          ((uint8) 1)
#define cDiagFinishNoError  ((uint8) 2)

#define RAM_START_ADDRESS  0xFEDF8000u
#define RAM_END_ADDRESS    0xFEE00000u
#define RAM_TESTENDE_ID    0xFEE55555u

//SYMC / DAI values

//RIVIAN values
#define START_FLASHADD4APPL     0x00020000u
#define END_FLASHADD4APPL       0x00077BFDu
#define CHECKSUMM_ADD_IN_APPL   0x00077BFEu
#define READ_BYTES4CHKInTask    0x40u

#define ushDefDemodSameLevelCtc 1200
#define ushDefDemodDifLevelGoodCtc 1200
#define ui16MaxRfRecInactiveTimeIn50msec 6000
#define ui16RecActiveTimeIn50msec 2400

static boolean ECUD_DiagRFRec(void);
static uint8 ECUD_PerformRamCheck(void);
static uint8 ECUD_PerformRomCheck(void);
static uint32 ECUD_RAMCheckUi32(uint32 ulRamStartAddress);

#endif
