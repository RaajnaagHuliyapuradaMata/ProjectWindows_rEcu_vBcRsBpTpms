

#ifndef _OSTM0X_H
#define _OSTM0X_H

#include "Std_Types.h"

#define OP_TIME_METHOD_OHDS 0x01U // OHDS
#define OP_TIME_METHOD_CSTDELAY 0x00U //Constant delay

//#define PAL_TEL_CST_DELAY_TIME 0x05U //ms

#define PalAbsConstantDelay		12U

//extern volatile unsigned short ushTimer500ms;
//extern volatile unsigned short ush1MsecSysTime;
//extern volatile unsigned char  ucTimer5ms;
//extern volatile unsigned char  ucTimer10ms;
//extern volatile unsigned char  ucTimer20ms;
//extern volatile unsigned char  ucTimer100ms;
//extern volatile unsigned short ushTimer500ms;
//extern volatile unsigned short ushTimer1s;
//extern volatile unsigned short ushTimer5s;
//extern volatile unsigned char  ucTimerFlags;

//extern uint8 ucManchesterPegelState;
//extern uint8 ucManchesterPeriode;
//extern uint8 ucByte4Manchester;
//extern uint8 ucStopManchesterCodierung;
//extern uint8 ucBreakCnt;
//extern uint8 ucTransmitByteCnt;
//extern uint8 ucBitCnt;

extern uint8 aucRe1DatenString[10];

#define cOSTM0_IRQ_ACTIVE      1
#define cOSTM0_IRQ_NOT_ACTIVE  0

extern void infSwcServiceOsSwcApplEcuM_InitFunction(void);

extern void OSTM0_FreeRunMode(void);
extern void OSTM0_IntervalMode(void);
extern void OSTM0_SetCompareValue(uint16);
extern void OSTM0_Start(void);
extern void OSTM0_Stop(void);
extern void OSTM0_wait_for_overflow(void);
extern void OSTM0_SetInterrupt(uint8 ucValue);

// normally call from diagnostic job
extern uint8 GetPalAbsConstantDelay(void);

#endif
