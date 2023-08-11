

#include "SysManager.h"
#include "CanManagerX.h"
#include "DemManagerX.h"
#include "EnvManagerX.h"
#include "RdcStandstillX.h"
#include "version.h"

#include "Mcu.h"
#include "Com.h"  //RST Todo this is for the workaround
#include "ComM.h"
#include "EcuM.h"
#include "Dem.h"
#include "Can.h"
#include "CanTrcv.h"

#include "GpioX.h"

#define cECU_EVENT_FIFO_SIZE  4

static uint16 ushResetTimer = 0;
static uint16 ushShutdownTimer = 0;
static uint16 ushSleepTimer = 0;
static uint16 ushFblJumpTimer = 0;
static uint16 ushSmartTesterTimer = 0;
static uint32 ulCoastModeTimer = 0;

static eEcuModesType  eEcuMode = cECUMODE_OFF;
static eEcuEventsType aucEventBuffer[cECU_EVENT_FIFO_SIZE] = {cECU_NO_EVENT, cECU_NO_EVENT, cECU_NO_EVENT, cECU_NO_EVENT};
static uint8  ucResetType = cRESET_TYPE_RESET;
static uint8  ucShutdownTarget = ECUM_SHUTDOWN_TARGET_OFF;

static eEcuEventsType SYSMGR_GetEvent(void)
{
  uint8 i;
  eEcuEventsType eRetVal;

  eRetVal = aucEventBuffer[0];

  if (eRetVal != cECU_NO_EVENT)
  {

    for (i = 0; i < (cECU_EVENT_FIFO_SIZE - 1); i++)
    {
      aucEventBuffer[i] = aucEventBuffer[i+1];
    }
    aucEventBuffer[cECU_EVENT_FIFO_SIZE - 1] = cECU_NO_EVENT;
  }

  return eRetVal;
}

static void SYSMGR_PrepareShutdown(uint16 ushTimeout)
{

  CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Rx);
  CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx);
  CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic);
  ComM_DeInit();

  if (ushTimeout < 10)
  {
    ushShutdownTimer = 10;
  }
  else
  {
    ushShutdownTimer = ushTimeout;
  }
}

static void SYSMGR_StartCoastModeTimer(void)
{
  ulCoastModeTimer = cCOASTMODE_TIME_MS;
}

static void SYSMGR_StopCoastModeTimer(void)
{
  ulCoastModeTimer = 0;
}

static void SYSMGR_PrepareSleep(uint16 ushTimeout)
{

  CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Rx);
  CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx);
  CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic);
  ComM_DeInit(); //RST 9.9.19: perhaps like this...?

  if (ushTimeout < 10)
  {
    ushSleepTimer = 10;
  }
  else
  {
    ushSleepTimer = ushTimeout;
  }
}

static void SYSMGR_SwitchEcuMode(void)
{
  eEcuEventsType eEvent = SYSMGR_GetEvent();

  if (eEvent != cECU_NO_EVENT)
  {
    switch (eEcuMode)
    {
      // ----------- Quiet Mode ----------------------------------------------------------------
      // ---------------------------------------------------------------------------------------
      case cECUMODE_QUIET:

      // >>>>> Quiet to Full >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      if (eEvent == cECUEVENT_IGN_ON)
      {
        CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx);
        CANMGR_StartCommTimeout();
        DemMGR_StartMonitoring();
        (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_IGNITION, DEM_CYCLE_STATE_START);
        #ifdef IGNORE_PRESSURE_ON_KEY
        #else
        RdcSt_ForwardStandstillDataToTms();
        #endif
        eEcuMode = cECUMODE_FULL;
      }

      // >>>>> Quiet to Monitor >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_COMM_TIMEOUT)
      {
        //CANMGR_SetNoCommunicationMode();  //Put Can Controller into Stop mode RST Debug 12.2.2021: keep CAN alive in monitor mode
        //TRCV_Standby();                   //Save some current
        //GPIO_TjaErrInterrupt(c_IRQ_ACTIVE);

        CANMGR_StopCommTimeout();
        #ifdef IGNORE_PRESSURE_ON_KEY
        SYSMGR_PrepareShutdown(10U);
        eEcuMode = cECUMODE_OFF;
        #else
        RdcSt_StartStandstillMonitoring();
        eEcuMode = cECUMODE_MONITOR;
        #endif
      }

      // >>>>> Quiet to Quiet (Coastmode timeout) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_COAST_TIMEOUT)
      {
        Env_ControlIgnitionByCoastmode(cCOASTMODE_OVER);
      }

      else {}
      break;

      // ---------- Full Mode ------------------------------------------------------------------
      // ---------------------------------------------------------------------------------------
      case cECUMODE_FULL:

      // >>>>> Full to Quiet (regular case: ignition off from bus) >>>>>>>>>>>>>>>>>>>>>>>>>>>
      if ((eEvent == cECUEVENT_IGN_OFF))
      {
        CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx);  //RST Debug: comment this line to send HMI messages also in quiet mode
        (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_IGNITION, DEM_CYCLE_STATE_END);
        DemMGR_StopMonitoring();
        eEcuMode = cECUMODE_QUIET;
      }

      // >>>>> Full to Quiet (error case: rx timeout) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_COMM_TIMEOUT)
      {

        Env_ControlIgnitionByCoastmode(cCOASTMODE_OVER);
        CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx);  //RST Debug: comment this line to send HMI messages also in quiet mode
        (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_IGNITION, DEM_CYCLE_STATE_END);
        DemMGR_StopMonitoring();
        CANMGR_StartCommTimeout();
        eEcuMode = cECUMODE_QUIET;
      }

      // >>>>> Full to Full (vehicle stops: start coastmode timer) >>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_VEH_STOP)
      {
        SYSMGR_StartCoastModeTimer();
        Env_ControlIgnitionByCoastmode(cCOASTMODE_START);
      }

      // >>>>> Full to Full (vehicle starts driving: stop coastmode timer)
      else if (eEvent == cECUEVENT_VEH_DRIVE)
      {
        SYSMGR_StopCoastModeTimer();
        Env_ControlIgnitionByCoastmode(cCOASTMODE_STOP);
      }

      // >>>>> Full to Full (Coastmode timeout) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_COAST_TIMEOUT)
      {
        Env_ControlIgnitionByCoastmode(cCOASTMODE_OVER);
      }

      else{}

      break;

      // ---------- Wake Mode ------------------------------------------------------------------
      // ---------------------------------------------------------------------------------------
      case cECUMODE_WAKE:
      // >>>>> Wake to Quiet >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      if (eEvent == cECUEVENT_CAN_WAKE)
      {
        RdcSt_StopStandstillMonitoring();
        CANMGR_SetFullCommunicationMode();
        TRCV_Normal();
        CANMGR_StartCommTimeout();
        eEcuMode = cECUMODE_QUIET;
      }

      // >>>>> Wake to deepstop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_DEEPSTOP)
      {
        SYSMGR_PrepareSleep(1U);
        eEcuMode = cECUMODE_OFF;
      }

      // >>>>> Wake to shutdown (22 days over) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_SHUTDOWN)
      {
        SYSMGR_PrepareShutdown(10U);
        eEcuMode = cECUMODE_OFF;
      }

      else{}
      break;

      // -------- Monitor Mode -----------------------------------------------------------------
      // ---------------------------------------------------------------------------------------
      case cECUMODE_MONITOR:

      // >>>>> Monitor to Quiet >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      if (eEvent == cECUEVENT_CAN_WAKE)
      {
        RdcSt_StopStandstillMonitoring();
        //CANMGR_SetFullCommunicationMode();  RST Debug 12.2.2021: keep CAN alive in Monitor mode
        //TRCV_Normal();
        CANMGR_StartCommTimeout();
        eEcuMode = cECUMODE_QUIET;
      }

      // >>>>> Monitor to Deepstop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_DEEPSTOP)
      {
        CANMGR_SetNoCommunicationMode();    //Put Can Controller into Stop mode RST Debug 12.2.2021: keep CAN alive in Monitor mode
        TRCV_Standby();                     //Save some current
        GPIO_TjaErrInterrupt(c_IRQ_ACTIVE); //IRQ from TJA will set cECUEVENT_CAN_WAKE
        SYSMGR_PrepareSleep(1U);
        eEcuMode = cECUMODE_OFF;
      }

      // >>>>> Monitor to shutdown (in case there are no sensors) >>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_SHUTDOWN)
      {
        SYSMGR_PrepareShutdown(10U);
        eEcuMode = cECUMODE_OFF;
      }

      // >>>>> Monitor to Monitor (Coastmode timeout) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
      else if (eEvent == cECUEVENT_COAST_TIMEOUT)
      {
        Env_ControlIgnitionByCoastmode(cCOASTMODE_OVER);
      }

      else{}
      break;

      // ------ Deepstop / Shutdown ------------------------------------------------------------
      // ---------------------------------------------------------------------------------------
      case cECUMODE_OFF:
      default:
      break;
    }
  }
}

static void SYSMGR_EcuSleep(void)
{

  (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_POWER, DEM_CYCLE_STATE_END);
  (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_OFF, 0);  //Parameter 2 is only relevant if shutdown target is _SLEEP or _RESET. Sleep not possible because sleep modes cannot be configured.
  ucShutdownTarget = ECUM_SHUTDOWN_TARGET_SLEEP;  //This is the workaround: static local variable here that will be fetched by the shutdown function EcuM_AL_SwitchOff()
  (void)EcuM_GoDown(1); //1 is the module ID of the calling module. Configuration contains just 1 default caller for shutdown, so modules and numbers seem not to be linked in a clear way.
}

static void SYSMGR_EcuShutdown(void)
{
  (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_POWER, DEM_CYCLE_STATE_END);
  (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_OFF, 0);  //Parameter 2 is only relevant if shutdown target is _SLEEP or _RESET. Sleep not possible because sleep modes cannot be configured.
  ucShutdownTarget = ECUM_SHUTDOWN_TARGET_OFF; //This is the workaround: static local variable here that will be fetched by the shutdown function EcuM_AL_SwitchOff()
  (void)EcuM_GoDown(1); //1 is the module ID of the calling module. Configuration contains just 1 default caller for shutdown, so modules and numbers seem not to be linked in a clear way.
}

static void SYSMGR_EcuReset(void)
{
  (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_POWER, DEM_CYCLE_STATE_END);
  (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_RESET, 0);
  ucResetType = cRESET_TYPE_RESET;
  (void)EcuM_GoDown(1);
}

static void SYSMGR_EcuStartBootloader(void)
{
  (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_POWER, DEM_CYCLE_STATE_END);
  (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_RESET, 0);
  ucResetType = cRESET_TYPE_START_BOOTLOADER;
  (void)EcuM_GoDown(1);
}

static void SYSMGR_EcuStartSmartTester(void)
{
  (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_POWER, DEM_CYCLE_STATE_END);
  (void)EcuM_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_RESET, 0);
  ucResetType = cRESET_TYPE_START_SMART_TESTER;
  (void)EcuM_GoDown(1);
}

void SYSMGR_MainFunction(void)
{

  if (ushShutdownTimer > 0)
  {
    ushShutdownTimer--;
    if (ushShutdownTimer == 0)
    {
      SYSMGR_EcuShutdown();
    }
  }

  else if (ushSleepTimer > 0)
  {
    ushSleepTimer--;
    if (ushSleepTimer == 0)
    {
      SYSMGR_EcuSleep();
    }
  }

  else if (ushResetTimer > 0)
  {
    ushResetTimer--;
    if (ushResetTimer == 0)
    {
      SYSMGR_EcuReset();
    }
  }

  else if (ushFblJumpTimer > 0)
  {
    ushFblJumpTimer--;
    if (ushFblJumpTimer == 0)
    {
      SYSMGR_EcuStartBootloader();
    }
  }

  else if (ushSmartTesterTimer > 0)
  {
    ushSmartTesterTimer--;
    if (ushSmartTesterTimer == 0)
    {
      SYSMGR_EcuStartSmartTester();
    }
  }

  else if (ulCoastModeTimer > 0)
  {
    ulCoastModeTimer--;
    if (ulCoastModeTimer == 0)
    {
      SYSMGR_SetEcuEvent(cECUEVENT_COAST_TIMEOUT);
    }
  }

  else
  {
  }

  CANMGR_TickCommTimeout();
  SYSMGR_SwitchEcuMode();
}

void SYSMGR_SetEcuMode(eEcuModesType ucMode)
{
  eEcuMode = ucMode;
}

uint8 SYSMGR_GetEcuMode(void)
{
  return eEcuMode;
}

void SYSMGR_SetEcuEvent(eEcuEventsType eEvent)
{

  uint8 i = 0;

  while ((aucEventBuffer[i] != cECU_NO_EVENT) && (i < cECU_EVENT_FIFO_SIZE))
  {
    i++;
  }

  if (i < cECU_EVENT_FIFO_SIZE)
  {
    aucEventBuffer[i] = eEvent;
  }
}

void SYSMGR_PrepareReset(uint16 ushTimeout)
{

  if (ushTimeout < cRESET_DELAY)
  {
    ushResetTimer = cRESET_DELAY;
  }
  else
  {
    ushResetTimer = ushTimeout;
  }
}

void SYSMGR_PrepareBootloaderJump(uint16 ushTimeout)
{

  if (ushTimeout < cRESET_DELAY)
  {
    ushFblJumpTimer = cRESET_DELAY;
  }
  else
  {
    ushFblJumpTimer = ushTimeout;
  }
}

void SYSMGR_PrepareSmartTesterJump(uint16 ushTimeout)
{

  if (ushTimeout < cRESET_DELAY)
  {
    ushSmartTesterTimer = cRESET_DELAY;
  }
  else
  {
    ushSmartTesterTimer = ushTimeout;
  }
}

uint8 SYSMGR_GetShutdownTarget(void)
{
  return ucShutdownTarget;
}

uint8 SYSMGR_GeMcalMcu_eReasonReset(void)
{
  return ucResetType;
}

