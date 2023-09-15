

#ifndef RDC_STANDSTILL_DEBUG_X_H
#define RDC_STANDSTILL_DEBUG_X_H

#include "Types.hpp"
#include "version.hpp"
#include "RdcManager.hpp"

#ifdef DEBUG_PRESSURE_ON_KEY
typedef struct{
  uint8 ucEventType;
  uint8 ucRecCntFL;
  uint8 ucRecCntFR;
  uint8 ucRecCntRL;
  uint8 ucRecCntRR;
  uint8 ucWindowTime[3];
}tStandstillDebugMsg;

#define cSSMDEBUG_EVENT_WAKE_BY_TAU_FL        0x10u
#define cSSMDEBUG_EVENT_WAKE_BY_TAU_FR        0x11u
#define cSSMDEBUG_EVENT_WAKE_BY_TAU_RL        0x12u
#define cSSMDEBUG_EVENT_WAKE_BY_TAU_RR        0x13u

#define cSSMDEBUG_EVENT_REC_WS_FL             0x20u
#define cSSMDEBUG_EVENT_REC_WS_FR             0x21u
#define cSSMDEBUG_EVENT_REC_WS_RL             0x22u
#define cSSMDEBUG_EVENT_REC_WS_RR             0x23u

#define cSSMDEBUG_EVENT_WINDOW_EXPIRED_FL     0x30u
#define cSSMDEBUG_EVENT_WINDOW_EXPIRED_FR     0x31u
#define cSSMDEBUG_EVENT_WINDOW_EXPIRED_RL     0x32u
#define cSSMDEBUG_EVENT_WINDOW_EXPIRED_RR     0x33u

// PC 05/2020: Added these because I needed an array where the event IDs where indexed.
extern const uint8 SSMDEBUG_CAU8_WakeByTau[RDC__NUMBER_OF_WS];
extern const uint8 SSMDEBUG_CAU8_RecWs[RDC__NUMBER_OF_WS];
extern const uint8 SSMDEBUG_CAU8_WindowExpired[RDC__NUMBER_OF_WS];

extern void SSMDEBUG_MainFunction(void);
extern void SSMDEBUG_SetEvent(uint8 ucEventType);
extern tStandstillDebugMsg* SSMDEBUG_GetPointerToBuffer(void);
extern void SSMDEBUG_StopTrigger(void);
#endif //DEBUG_PRESSURE_ON_KEY

#endif
