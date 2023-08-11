#include "Os.h"
#include "Os_Cfg.h"
#include "Os_ConfigInterrupts.h"
#include "gpioX.h"
#include "clocksX.h"
#include "ata_Rec_X.h"
#include "ostm0X.h"
#include "adcX.h"
#include "rscan.h"
#include "wdt.h"
#include "can.h"
#include "Mcu.h"
#include "CanTrcv.h"
#include "CanManagerX.h"
#include "EnvManagerX.h"
#include "RdcManagerX.h"
#include "SysManagerX.h"
#include "TmsManagerX.h"
#include "iTpms_Interface.h"
#include "RdcStandstillX.h"
#include "DemManagerX.h"
#include "EcuDiagX.h"
#include "DcmManagerX.h"
#include "DcmAppInterfaceX.h"
#include "NvmManagerX.h"

#include "CanIf_Integration.h"
#include "ComM_Main.h"
#include "Com.h"
#include "CanSM.h"
#include "EcuM.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Dem.h"
#include "Fim.h"
#include "Rte_NvM_Type.h"
#include "Nvm.h"

#include "Version.h"
#ifdef DEBUG_PRESSURE_ON_KEY
#include "RdcStandstillDebugX.h"
#endif

static uint8  ucLed = 0;
static uint8  uc100msTimer = 0;
static uint8 ucNoiseMeasureTimer = 0;
static uint8 ucAtaIrqTimeout = 0;
static Can_FrameType tRxCanFrame;

ISR(CAT2ISR_TelRec)
{
  Os_Disable_CAT2ISR_TelRec();
  //TP0(1);
  SetAtaIrqFlag();

  if (GetAtaState() == cRfdProcess)
  {
    CheckAtaRec();
    ClearAtaIrqFlag();
    ActivateTask(TelRecTask);
  }

  ucAtaIrqTimeout = 0;
  //TP0(0);
  Os_Clear_CAT2ISR_TelRec();
  Os_Enable_CAT2ISR_TelRec();
}

ISR(CAT2ISR_OneMillisecond)
{
  Os_IncrementCounter_OneMillisecondCounter();
  Rdc_IncrementTimestamp();
  DCMMGR_IncNonceCounter();
  Os_Clear_CAT2ISR_OneMillisecond();
}

ISR(CAT2ISR_Can0Receive)
{
  Can_ClearRxFiFoInterruptFlag();
  ActivateTask(CanRecTask);
  Os_Clear_CAT2ISR_Can0Receive();
}

ISR(CAT2ISR_Can0Transmit)
{
  Can_ClearTxBufferInterruptFlag();
  Os_Clear_CAT2ISR_Can0Transmit();
}

ISR(CAT2ISR_Wakeup)
{
  //Os_Disable_CAT2ISR_Wakeup();
  SYSMGR_SetEcuEvent(cECUEVENT_CAN_WAKE);
  Os_Clear_CAT2ISR_Wakeup();
  //Os_Enable_CAT2ISR_Wakeup();
}

ISR(CAT2ISR_Can0Status)
{
  Os_Clear_CAT2ISR_Can0Status();
}

ISR(CAT2ISR_CanGlobalStatus)
{
  Os_Clear_CAT2ISR_CanGlobalStatus();
}

ISR(CAT2ISR_Timer0)
{
  RdcSt_StartMonitoringSpecificWS(RDCST_WS_FL);
  Os_Clear_CAT2ISR_Timer0();
}

ISR(CAT2ISR_Timer1)
{
  RdcSt_StartMonitoringSpecificWS(RDCST_WS_FR);
  Os_Clear_CAT2ISR_Timer1();
}

ISR(CAT2ISR_Timer2)
{
  RdcSt_StartMonitoringSpecificWS(RDCST_WS_RL);
  Os_Clear_CAT2ISR_Timer2();
}

ISR(CAT2ISR_Timer3)
{
  RdcSt_StartMonitoringSpecificWS(RDCST_WS_RR);
  Os_Clear_CAT2ISR_Timer3();
}

ISR(CAT2ISR_VoltageMonitor)
{
  ADC_Channel2_GetValue();
  Os_Clear_CAT2ISR_VoltageMonitor();
}

ISR(FLS_FLENDNM_CAT2_ISR)
{
  Os_Clear_FLS_FLENDNM_CAT2_ISR();
}

CAT1_ISR(UndefinedInterrupt){
   __DI();
   while(1){
   TP3(1);
      Wdt_TriggerWD0();
   }
}

FUNC(void, OS_OS_CBK_ALARM_CB_ALARM200MS_CODE) Os_Cbk_Alarm_CB_Alarm200ms(void)
{
}

FUNC(void, OS_OS_CBK_ALARM_CB_ALARMONESECOND_CODE) Os_Cbk_Alarm_CB_AlarmOneSecond(void)
{
}

FUNC(void, OS_OS_CBK_ALARM_CB_ALARM10MS_CODE) Os_Cbk_Alarm_CB_Alarm10ms(void)
{
}

FUNC(void, OS_OS_CBK_ALARM_CB_ALARM50MS_CODE) Os_Cbk_Alarm_CB_Alarm50ms(void)
{
}

FUNC(boolean, OS_OS_CBK_IDLE_CODE) Os_Cbk_Idle(void)
{
  return TRUE;
}

#include "ProductionFlashInterfaceX.h"
#include "DemAppInterfaceX.h"
TASK(InitTask)
{

  HufIf_Init_Huf_SWC();

  Rdc_Init();
  Tms_Init();
  Env_Init();
  CANMGR_Init();
  DemMGR_Init();
  NvmMGR_Init();

  CheckRfState();
  CheckRfState();

  TerminateTask();
}

TASK(TelRecTask)
{
  TerminateTask();
}
TASK(CanRecTask)
{
  Can_RtnType tCanRecStatus;
  tCanRecStatus = Can_ReadRxFiFo(&tRxCanFrame);

  Can_ForwardMessageToCanIf(&tRxCanFrame);
  Os_Enable_CAT2ISR_Can0Receive();  //RST Debug

  if (tCanRecStatus != CAN_RTN_BUFFER_EMPTY)
  {

    ChainTask(CanRecTask);
  }
  else
  {
    TerminateTask();
  }
}
TASK(CyclicTask10ms)
{

  Can_MainFunction_BusOff();
  CanSM_MainFunction();
  ComM_MainFunction_ComMChannel_Can_Network_0_Channel();
  Com_MainFunctionRx();
  Com_MainFunctionTx();
  CanTp_MainFunction();
  Dcm_MainFunction();
  Dem_MainFunction();
  EcuM_MainFunction();
  Memstack_Main();
  SYSMGR_MainFunction();
  DCMMGR_MainFunction();
  Wdt_TriggerWD0();

  #ifdef DEBUG_PRESSURE_ON_KEY
  SSMDEBUG_MainFunction();
  #endif

  TerminateTask();
}
TASK(CyclicTask50ms)
{
  uint8 ucNoise;

  CheckRfState();
  CheckRfState();

  Rdc_ForwardRfDataToTms();

  uc100msTimer++;
  if (uc100msTimer == 1)
  {

    //ECUD_SelfDiag();
    //currently no job here
  }
  else
  {
    uc100msTimer = 0;
  }

  if (GetAtaState() == cRfdProcess)
  {

    ucNoiseMeasureTimer++;
    if ((ucNoiseMeasureTimer == 8) || (ucNoiseMeasureTimer == 20)){
      ucNoise = ATA_MeasureNoiseRssiLevel();
      if (ucNoise != 0xff)
      {

        Env_SetNoiseLevel(ucNoise);
      }
      ucNoiseMeasureTimer %= 20;
    }
  }

  ADC_StartConversionSG1();

  //ECUD_SelfDiag(); RST 09.03.2021: don't use this. It is programmed bad and makes trouble.

  Memstack_WriteCategoryOnEvent();

  TerminateTask();
}

TASK(CyclicTask200ms)
{
  tsTPMS_Data *PS_TmsStatus = Tms_GetTmsStatusPointer();
  tsEnv_Data *PS_EnvData = Env_GetEnvironmentData();
  uint16 ushCategoryConsistency = (uint16)(Memstack_GetCurrentNvMConsistence() & CU16_NVM_ALL_CATEG_CONSISTENT);

  Env_SetNvmBlockConsistency(ushCategoryConsistency);
  HufIf_RCtSaTpmsData(PS_TmsStatus, PS_EnvData);

  if (ushCategoryConsistency != CU16_NVM_ALL_CATEG_CONSISTENT)
  {
    Memstack_WriteAllBlocks();
    Memstack_Appl_JobEndCallback_CAT01();
    Memstack_Appl_JobEndCallback_CAT02();
    Memstack_Appl_JobEndCallback_CAT03();
    Memstack_Appl_JobEndCallback_CAT04();
    Memstack_Appl_JobEndCallback_CAT05();
    Memstack_Appl_JobEndCallback_CAT06();
    Memstack_Appl_JobEndCallback_CAT07();
    Memstack_Appl_JobEndCallback_CAT08();
    Memstack_Appl_JobEndCallback_CAT09();
    Memstack_Appl_JobEndCallback_CAT10();
  }

  CANMGR_ControlCyclicApplicationPdu();
  DemMGR_MainFunction();

  if (ENV_E_IGNITION_OFF == enGetIgnitionStateFromBus())
  {
	  SYSMGR_SetEcuEvent(cECUEVENT_SHUTDOWN);
  }

  TerminateTask();
}

TASK(CyclicTask1sec){
   ucLed ^= 0x01;
   TP0(ucLed);
   DemMGR_EcuVoltageMonitorMainFunction();
   if (++ucAtaIrqTimeout == 20){
      ATA_ReInitAfterError();
   }
   TerminateTask();
}

FUNC(void, OS_STARTUPHOOK_CODE) StartupHook(void)
{

  OSTM0_SetInterrupt(cOSTM0_IRQ_ACTIVE);
  Os_Enable_CAT2ISR_OneMillisecond();
  Os_Disable_CAT2ISR_TelRec();
  Os_Disable_CAT2ISR_Can0Receive();
  Os_Disable_CAT2ISR_Can0Transmit();
  Os_Disable_CAT2ISR_Wakeup();
  Os_Disable_CAT2ISR_Timer0();
  Os_Disable_CAT2ISR_Timer1();
  Os_Disable_CAT2ISR_Timer2();
  Os_Disable_CAT2ISR_Timer3();
  Os_Enable_CAT2ISR_VoltageMonitor();

  EcuM_StartupTwo();

  Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_POWER, DEM_CYCLE_STATE_START);
  Mcu_CheckWakeupSource();

  TP3(0);
}

FUNC(void, OS_SHUTDOWNHOOK_CODE) ShutdownHook(StatusType Error){
   if (Error == E_OS_STACKFAULT){
      Os_Restart();
   }
   else if (Error == E_OS_STATE){
      TP3(1);
      while(1){}
   }
   else if (Error == E_OS_SYS_NO_RESTART){
      EcuM_Shutdown();
   }
   else if (Error == E_OK){
   }
}

FUNC(void, OS_ERRORHOOK_CODE) ErrorHook(StatusType Error)
{
  switch (Error)
  {
    case E_OS_ID:

      break;
    case E_OS_VALUE:

      break;
    case E_OS_STATE:

      break;
    default:

      break;
  }
}

FUNC(void, OS_OS_CBK_STACKOVERRUNHOOK_CODE) Os_Cbk_StackOverrunHook(Os_StackSizeType Overrun, Os_StackOverrunType Reason){
   while(1){
      TP3(1);
      Wdt_TriggerWD0();
   }
}

// RST: attention, this has nothing to do with the TPMS SWC, just the OS internal application

FUNC(void, OS_STARTUPHOOK_HUFTPMS_CODE) StartupHook_HufTpms(void)
{
}

FUNC(void, OS_SHUTDOWNHOOK_HUFTPMS_CODE) ShutdownHook_HufTpms(StatusType Error)
{
}

FUNC(void, OS_ERRORHOOK_HUFTPMS_CODE) ErrorHook_HufTpms(StatusType Error)
{
}

