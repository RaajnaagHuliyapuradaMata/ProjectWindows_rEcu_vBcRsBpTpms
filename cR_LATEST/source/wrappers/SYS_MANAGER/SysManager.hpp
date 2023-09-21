#ifndef SYS_MANAGER_H
#define SYS_MANAGER_H

#include "SysManagerX.hpp"
#include "version.hpp"

#define cECU_RESET  1
#define cECU_SLEEP  2
#define cECU_OFF    3

#define cRESET_DELAY 10 //100ms

#ifdef DEBUG_FAST_SHUTDOWN
#define cCOASTMODE_TIME_MIN (uint32)1    // special for HIL: 1minute
#else
#define cCOASTMODE_TIME_MIN (uint32)10   // 10 minutes
#endif
#define cCOASTMODE_TIME_10MS  (cCOASTMODE_TIME_MIN * 60 * 100) // coastmode timer is count in 10ms cycle //Rivian OIL#134

static eEcuEventsType SYSMGR_GetEvent(void);
static void SYSMGR_SwitchEcuMode(void);
static void SYSMGR_PrepareShutdown(uint16 ushTimeout);
static void SYSMGR_PrepareSleep(uint16 ushTimeout);
static void SYSMGR_StartCoastModeTimer(void);
static void SYSMGR_StopCoastModeTimer(void);
static void SYSMGR_EcuSleep(void);
static void SYSMGR_EcuShutdown(void);
static void SYSMGR_EcuReset(void);
static void SYSMGR_EcuStartBootloader(void);
static void SYSMGR_EcuStartSmartTester(void);

#endif