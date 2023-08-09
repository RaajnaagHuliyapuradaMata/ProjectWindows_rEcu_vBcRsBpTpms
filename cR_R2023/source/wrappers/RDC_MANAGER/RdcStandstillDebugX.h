

#ifndef RDC_STANDSTILL_DEBUG_X_H
#define RDC_STANDSTILL_DEBUG_X_H

#include "Types.h"
#include "version.h"
#include "RdcManager.h"

#ifdef DEBUG_PRESSURE_ON_KEY
typedef struct
{
  uint8 ucEventType;
  uint8 ucRecCntFL;
  uint8 ucRecCntFR;
  uint8 ucRecCntRL;
  uint8 ucRecCntRR;
  uint8 ucWindowTime[3];
} tStandstillDebugMsg;

#define cSSMDEBUG_EVENT_WAKE_BY_TAU_FL        (uint8)0x10
#define cSSMDEBUG_EVENT_WAKE_BY_TAU_FR        (uint8)0x11
#define cSSMDEBUG_EVENT_WAKE_BY_TAU_RL        (uint8)0x12
#define cSSMDEBUG_EVENT_WAKE_BY_TAU_RR        (uint8)0x13

#define cSSMDEBUG_EVENT_REC_WS_FL             (uint8)0x20
#define cSSMDEBUG_EVENT_REC_WS_FR             (uint8)0x21
#define cSSMDEBUG_EVENT_REC_WS_RL             (uint8)0x22
#define cSSMDEBUG_EVENT_REC_WS_RR             (uint8)0x23

#define cSSMDEBUG_EVENT_WINDOW_EXPIRED_FL     (uint8)0x30
#define cSSMDEBUG_EVENT_WINDOW_EXPIRED_FR     (uint8)0x31
#define cSSMDEBUG_EVENT_WINDOW_EXPIRED_RL     (uint8)0x32
#define cSSMDEBUG_EVENT_WINDOW_EXPIRED_RR     (uint8)0x33

#define cSSMDEBUG_EVENT_WAKEUP                (uint8)0xA0  // "wakeup"
#define cSSMDEBUG_EVENT_START_SSM             (uint8)0xC0  // "start standstill monitoring (monitor mode)"
#define cSSMDEBUG_EVENT_DEEPSTOP              (uint8)0xE0  // "go to deepstop"
#define cSSMDEBUG_EVENT_SHUTDOWN_SSMOFF       (uint8)0xF1  // "shutdown because standstill monitoring is switched off by diag switch"
#define cSSMDEBUG_EVENT_SHUTDOWN_NO_SENSORS   (uint8)0xF2  // "shutdown because no 0x90 TGs were received during monitor mode"

#define cLTGDEBUG_EVENT_FILTERED              (uint8)0x40  // notice telegram that failed at specific checkpoint (length, crc, supplier id, continous rx...)
#define cTGFILTER_LENGTH                      (uint8)0x00
#define cTGFILTER_CRC                         (uint8)0x01
#define cTGFILTER_SID                         (uint8)0x02
#define cTGFILTER_NOTINHISTORY                (uint8)0x03
#define cTGFILTER_RBFULL                      (uint8)0x04
#define cTGFILTER_IGNITION_OFF                (uint8)0x05  // filter is in lib
#define cTGFILTER_E7_WITH_INVALID_TS          (uint8)0x06  // filter is in lib
#define cTGFILTER_MULTIFRAME_IN_400MS         (uint8)0x07  // filter is in lib
#define cTGFILTER_0x90_WHILE_DRIVING          (uint8)0x08  // filter is in lib
#define cLTGDEBUG_ATA_SKIPPED_NOISE_MEASUR    (uint8)0x09
#define cLTGDEBUG_ATA_RESTART_BY_TIMEOUT      (uint8)0x0A
#define cLTGDEBUG_ATA_DETECT_SYS_ERROR        (uint8)0x0B

#define cSSMDEBUG_EVENT_TG_FORWARD            (uint8)0x50
#define cSSMDEBUG_EVENT_COPY_TG_TO_RRAM       (uint8)0x60
#define cSSMDEBUG_EVENT_NO_RRAM_DATA          (uint8)0x70
#define cSSMDEBUG_EVENT_NVM_CONTAINS_DATA     (uint8)0x80
#define cSSMDEBUG_EVENT_RRAM_DATA_CLEAR       (uint8)0x90
#define cSSMDEBUG_EVENT_SHOW_RESET_TYPE       (uint8)0x91

// PC 05/2020: Added these because I needed an array where the event IDs where indexed.
extern const uint8 SSMDEBUG_CAU8_WakeByTau[RDC__NUMBER_OF_WS];
extern const uint8 SSMDEBUG_CAU8_RecWs[RDC__NUMBER_OF_WS];
extern const uint8 SSMDEBUG_CAU8_WindowExpired[RDC__NUMBER_OF_WS];

extern void SSMDEBUG_MainFunction(void);
extern void SSMDEBUG_SetEvent(uint8 ucEventType);
extern void LTGDEBUG_SetEvent(uint8 ucTgType, uint32 ulSensorId, uint8 ucFilterType);
extern void SSMDEBUG_SetEvent_in_QuietMode(uint8 ucEventType, uint8 ucTgType, uint32 ulSensorId);
extern tStandstillDebugMsg* SSMDEBUG_GetPointerToBuffer(void);
extern void SSMDEBUG_StopTrigger(void);
#endif //DEBUG_PRESSURE_ON_KEY

#endif
