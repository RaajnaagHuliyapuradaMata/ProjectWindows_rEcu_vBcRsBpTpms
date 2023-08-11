
#ifndef ATA_REC_X_H
#define ATA_REC_X_H

#include "Types.h"
#include "ata_dev_5785.h"

#define cDelay2StartUp   0
#define cRfdStartInit    1
#define cRfdInit         2
#define cRfdWtIniFini    3
#define cRfdProcess      4

#define RB_DATA_LEN (uint8) 16
#define RB_RS_BUF_LEN (uint8) 6

#define cATA_IRQ_PENDING      1
#define cATA_NO_IRQ_PENDING   0

extern void  CheckAtaRec(void);
extern void  CheckRfState (void);
extern uint8 GetAtaState(void);
extern uint8 GetAtaIrqFlag(void);
extern void ClearAtaIrqFlag(void);
extern void SetAtaIrqFlag(void);

extern uint8 ATA_MeasureNoiseRssiLevel(void);
extern uint8 ATA_GetCrcPassedTelCounter(void);
extern uint8 ATA_GetCrcFailedTelCounter(void);
extern void  ATA_ReInitAfterError(void);
#endif
