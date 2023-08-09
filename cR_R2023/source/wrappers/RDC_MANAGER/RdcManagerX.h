

#ifndef RDC_MANAGER_X_H
#define RDC_MANAGER_X_H

#include "Std_Types.h"
#include "ata_dev_5785.h"

extern void Rdc_Init(void);

extern void Rdc_ProcessTelegram(struct rfstruct* PS_TelegramData);

extern void Rdc_ForwardRfDataToTms(void);

extern void Rdc_ForwardSimulatedRfDataToTms(uint8* PU8_DataPointer);

extern void Rdc_IncrementTimestamp(void);

extern void Rdc_SynchronizeToCGMTimestamp(uint64 U64_CGMTimestamp);

extern uint32 Rdc_ConvertWheelPulseTimestamp(uint16 U16_WheelPulseTimestamp);

extern void Rdc_StoreLatestCGMTimestamp(uint64 *PU64_CGMTimestamp);

#endif
