#ifndef GPIO_X_H
#define GPIO_X_H

#include "std_types.h"
#include "CfgMcalDio.h"
#include "CfgSwcServiceOs.h"

#define cFREQUENCY_433 1
#define cFREQUENCY_315 2

extern void     GPIO_CanInit(void);
extern void     GPIO_DeInit(void);
extern void     GPIO_CanStandby(uint8 ucStb);
extern void     GPIO_CanEnable(uint8 ucEn);
extern void     GPIO_CanInterrupt(uint8 ucVal);
extern void     GPIO_TjaErrInterrupt(uint8 ucVal);
extern uint8    GPIO_GetFrequencySetting(void);
extern uint16   GPIO_input_read(Type_McalDio_eName PortPin);
extern void     GPIO_output_on(Type_McalDio_eName PortPin);
extern void     GPIO_ChipSelectAta(uint8 ucSet);
extern uint8    GPIO_GetAtaIrqPortPinLevel(void);
extern uint8    GPIO_GetAtaIrqPendingFlag(void);
extern void     McalDio_vInitInput     (Type_McalDio_eName leNamePin); //TBD: Remove
extern void     McalDio_vInitOutput    (Type_McalDio_eName leNamePin); //TBD: Remove
extern void     McalDio_vInitOutputOff (Type_McalDio_eName leNamePin); //TBD: Remove
extern void     TP3(uint8 ucSet);
extern void     TP2(uint8 ucSet);
extern void     TP1(uint8 ucSet);
extern void     TP0(uint8 ucSet);

extern uint8 ucGetRF_IRQ_ATA(void);
extern void FastPWR_3Pin4_ATA(uint8 ucSet);

#endif
