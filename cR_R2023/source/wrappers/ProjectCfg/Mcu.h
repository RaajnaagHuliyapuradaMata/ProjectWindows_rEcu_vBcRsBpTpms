#ifndef _MCU_H
#define _MCU_H

#define MCU_AR_RELEASE_MAJOR_VERSION  4
#define MCU_AR_RELEASE_MINOR_VERSION  2

#include "types.h"

#define MCU_WUP_FACTOR_CAN      (1<<5)  // INTP0 (CAN0 RX ) Pin: Bit 5
#define MCU_WUP_FACTOR_TJA_ERR  (1<<6)  // INTP1 (/ERR) Pin: Bit 6
#define MCU_WUP_FACTOR_TAUJ00   (1<<15) // TAUJ0_0: Bit 15
#define MCU_WUP_FACTOR_TAUJ01   (1<<16) // TAUJ0_1: Bit 16
#define MCU_WUP_FACTOR_TAUJ02   (1<<17) // TAUJ0_2: Bit 17
#define MCU_WUP_FACTOR_TAUJ03   (1<<18) // TAUJ0_3: Bit 18

#define MCU_RESF_SOFT_RESET     (1<<0)
#define MCU_RESF_WD0_RESET      (1<<1)
#define MCU_RESF_WD1_RESET      (1<<2)
#define MCU_RESF_POWER_ON_RESET (1<<9)
#define MCU_RESF_DEEPSTOP_RESET (1<<10)

extern void Mcu_DeepStop(void);
extern void Mcu_Shutdown(void);
extern void Mcu_CheckWakeupSource(void);
extern void Mcu_PerformReset(void);
extern void Mcu_ReleaseIoBuffers(void);
#endif
