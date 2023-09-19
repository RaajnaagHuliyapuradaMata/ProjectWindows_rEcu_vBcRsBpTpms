#ifndef SYS_MANAGER_X_H
#define SYS_MANAGER_X_H

typedef enum{
  cECUMODE_OFF          = (uint8)0
   ,  cECUMODE_QUIET        = (uint8)1
   ,  cECUMODE_FULL         = (uint8)2
   ,  cECUMODE_MONITOR      = (uint8)3
   ,  cECUMODE_WAKE         = (uint8)4
}eEcuModesType;

typedef enum{
  cECU_NO_EVENT           = (uint8)0x00
   ,  cECUEVENT_IGN_OFF       = (uint8)0x01
   ,  cECUEVENT_IGN_ON        = (uint8)0x02
   ,  cECUEVENT_PON           = (uint8)0x03
   ,  cECUEVENT_CAN_WAKE      = (uint8)0x04
   ,  cECUEVENT_TIMER_WAKE    = (uint8)0x05
   ,  cECUEVENT_COMM_TIMEOUT  = (uint8)0x06
   ,  cECUEVENT_VEH_STOP      = (uint8)0x07
   ,  cECUEVENT_VEH_DRIVE     = (uint8)0x08
   ,  cECUEVENT_COAST_TIMEOUT = (uint8)0x09
   ,  cECUEVENT_DEEPSTOP      = (uint8)0x0A
   ,  cECUEVENT_SHUTDOWN      = (uint8)0x0B
}eEcuEventsType;

typedef enum{
  cCOASTMODE_START = 0x01U
   ,  cCOASTMODE_STOP = 0x02U
   ,  cCOASTMODE_OVER = 0x03U,
}eCoastModeType;

#define cRESET_TYPE_RESET               0
#define cRESET_TYPE_START_BOOTLOADER    1
#define cRESET_TYPE_START_SMART_TESTER  2

extern void SYSMGR_SetEcuMode(eEcuModesType ucMode);
extern void SYSMGR_SetEcuEvent(eEcuEventsType ucEvent);
extern uint8 SYSMGR_GetEcuMode(void);
extern uint8 SYSMGR_GetShutdownTarget(void);
extern uint8 SYSMGR_GeMcalMcu_eReasonReset(void);
extern void SYSMGR_MainFunction(void);
extern void SYSMGR_PrepareReset(uint16 ushTimeout);
extern void SYSMGR_PrepareBootloaderJump(uint16 ushTimeout);
extern void SYSMGR_PrepareSmartTesterJump(uint16 ushTimeout);

#endif