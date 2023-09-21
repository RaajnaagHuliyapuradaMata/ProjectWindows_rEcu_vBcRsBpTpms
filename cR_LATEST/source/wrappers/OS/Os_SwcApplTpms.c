#include "Std_Types.hpp"

#include "Os.hpp"
#include "Os_Cfg.hpp"
#include "Os_ConfigInterrupts.hpp"
#include "gpioX.hpp"
#include "clocksX.hpp"
#include "ata_Rec_X.hpp"
#include "ostm0X.hpp"
#include "adcX.hpp"
#include "rscan.hpp"
#include "wdt.hpp"
#include "CfgMcalMcu.hpp"
#include "CanTrcv.hpp"
#include "CanManagerX.hpp"
#include "EnvManagerX.hpp"
#include "RdcManagerX.hpp"
#include "SysManagerX.hpp"
#include "TmsManagerX.hpp"
#include "iTpms_Interface.hpp"
#include "DemManagerX.hpp"
#include "EcuDiag.hpp"
#include "DcmManagerX.hpp"
#include "NvmManagerX.hpp"
#include "CanIf.hpp"
#include "CanIf_Cfg_SymbolicNames.hpp"
#include "ComM_Main.hpp"
#include "Com.hpp"
#include "CanSM.hpp"
#include "EcuM.hpp"
#include "CanTp.hpp"
#include "Dcm.hpp"
#include "Dem.hpp"
#include "Fim.hpp"
#include "Rte_NvM_Type.hpp"
#include "Nvm.hpp"
#include "Version.hpp"

#include "infMcalCanSwcServiceSchM.hpp"

static uint8                ucLed               = 0;
static uint8                uc100msTimer        = 0;
static uint8                ucNoiseMeasureTimer = 0;
static uint8                ucAtaIrqTimeout     = 0;
static Type_McalCan_stFrame tRxCanFrame;

ISR(CAT2ISR_TelRec){
   Os_Disable_CAT2ISR_TelRec();
   SetAtaIrqFlag();
   if(GetAtaState() == cRfdProcess){
      CheckAtaRec();
      ClearAtaIrqFlag();
      ActivateTask(TelRecTask);
   }
   ucAtaIrqTimeout = 0;
   Os_Clear_CAT2ISR_TelRec();
   Os_Enable_CAT2ISR_TelRec();
}

ISR(CAT2ISR_OneMillisecond){
   Os_IncrementCounter_OneMillisecondCounter();
   Rdc_IncrementTimestamp();
   DCMMGR_IncNonceCounter();
   Os_Clear_CAT2ISR_OneMillisecond();
}

ISR(CAT2ISR_Can0Receive){
   Can_ClearRxFiFoInterruptFlag();
   ActivateTask(CanRecTask);
   Os_Clear_CAT2ISR_Can0Receive();
}

ISR(CAT2ISR_Can0Transmit){
   Can_ClearTxBufferInterruptFlag();
   Os_Clear_CAT2ISR_Can0Transmit();
}

ISR(CAT2ISR_Wakeup){
   SYSMGR_SetEcuEvent(cECUEVENT_CAN_WAKE);
   Os_Clear_CAT2ISR_Wakeup();
}

ISR(CAT2ISR_Can0Status){
   Os_Clear_CAT2ISR_Can0Status();
}

ISR(CAT2ISR_CanGlobalStatus){
   Os_Clear_CAT2ISR_CanGlobalStatus();
}

ISR(CAT2ISR_Timer0){
   Os_Clear_CAT2ISR_Timer0();
}

ISR(CAT2ISR_Timer1){
   Os_Clear_CAT2ISR_Timer1();
}

ISR(CAT2ISR_Timer2){
   Os_Clear_CAT2ISR_Timer2();
}

ISR(CAT2ISR_Timer3){
   Os_Clear_CAT2ISR_Timer3();
}

ISR(CAT2ISR_VoltageMonitor){
   ADC_Channel2_GetValue();
   Os_Clear_CAT2ISR_VoltageMonitor();
}

ISR(FLS_FLENDNM_CAT2_ISR){
   Os_Clear_FLS_FLENDNM_CAT2_ISR();
}

CAT1_ISR(UndefinedInterrupt){
   __DI();
   while(1){
      TP3(1);
      Wdt_TriggerWD0();
   }
}

FUNC(void, OS_OS_CBK_ALARM_CB_ALARM200MS_CODE) Os_Cbk_Alarm_CB_Alarm200ms(void){
}

FUNC(void, OS_OS_CBK_ALARM_CB_ALARMONESECOND_CODE) Os_Cbk_Alarm_CB_AlarmOneSecond(void){
}

FUNC(void, OS_OS_CBK_ALARM_CB_ALARM10MS_CODE) Os_Cbk_Alarm_CB_Alarm10ms(void){
}

FUNC(void, OS_OS_CBK_ALARM_CB_ALARM50MS_CODE) Os_Cbk_Alarm_CB_Alarm50ms(void){
}

FUNC(boolean, OS_OS_CBK_IDLE_CODE) Os_Cbk_Idle(void){
  return TRUE;
}

TASK(InitTask){
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

TASK(TelRecTask){
   TerminateTask();
}

TASK(CanRecTask){
   Can_RtnType tCanRecStatus = Can_ReadRxFiFo(&tRxCanFrame);
   infMcalMcuSwcServiceSchM_vRunnableRx(
      &tRxCanFrame
   );
   Os_Enable_CAT2ISR_Can0Receive();
   if(
         tCanRecStatus
      != CAN_RTN_BUFFER_EMPTY
   ){
      ChainTask(CanRecTask);
   }
   else{
      TerminateTask();
   }
}

#include "infMcalCanSwcServiceSchM.hpp"
#include "infSwcServiceCanSmSwcServiceSchM.hpp"
#include "infSwcServiceCanTpSwcServiceSchM.hpp"
#include "infSwcServiceComSwcServiceSchM.hpp"
#include "infSwcServiceDcmSwcServiceSchM.hpp"
#include "infSwcServiceDemSwcServiceSchM.hpp"
#include "infSwcServiceEcuMSwcServiceSchM.hpp"
TASK(CyclicTask10ms){
   infMcalCanSwcServiceSchM_vMainFunctionBusOff();
   infSwcServiceCanSMSwcServiceSchM_vMainFunction();
   ComM_MainFunction_ComMChannel_Can_Network_Channel();
   infSwcServiceComSwcServiceSchM_vMainFunctionRx();
   infSwcServiceComSwcServiceSchM_vMainFunctionTx();
   infSwcServiceCanTpSwcServiceSchM_vMainFunction();
   infSwcServiceDcmSwcServiceSchM_vMainFunction();
   infSwcServiceDemSwcServiceSchM_vMainFunction();
   FiM_MainFunction();
   infSwcServiceEcuMSwcServiceSchM_vMainFunction();
   Memstack_Main();
   SYSMGR_MainFunction();
   DCMMGR_MainFunction();
   Wdt_TriggerWD0();
   TerminateTask();
}

TASK(CyclicTask50ms){
   uint8 ucNoise;
   CheckRfState();
   CheckRfState();
   Rdc_ForwardRfDataToTms();
   uc100msTimer++;
   if(uc100msTimer == 1){
   }
   else{
      uc100msTimer = 0;
   }
   if(GetAtaState() == cRfdProcess){
      ucNoiseMeasureTimer++;
      if(
            (ucNoiseMeasureTimer == 8)
         || (ucNoiseMeasureTimer == 20)
      ){
         ucNoise = ATA_MeasureNoiseRssiLevel();
         if(ucNoise != 0xff){
            Env_SetNoiseLevel(ucNoise);
         }
         ucNoiseMeasureTimer %= 20;
      }
   }
   ADC_StartConversionSG1();
   Memstack_WriteCategoryOnEvent();
   TerminateTask();
}

TASK(CyclicTask200ms){
   tsTPMS_Data* PS_TmsStatus           = Tms_GetTmsStatusPointer();
   tsEnv_Data*  PS_EnvData             = Env_GetEnvironmentData();
   uint16       ushCategoryConsistency = (uint16)(Memstack_GetCurrentNvMConsistence() & CU16_NVM_ALL_CATEG_CONSISTENT);

   Env_SetNvmBlockConsistency(ushCategoryConsistency);
   HufIf_RCtSaTpmsData(PS_TmsStatus, PS_EnvData);
   if(ushCategoryConsistency != CU16_NVM_ALL_CATEG_CONSISTENT){
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
   ucLed ^= 0x01;
   TP0(ucLed);
   TerminateTask();
}

TASK(CyclicTask1sec){
   DemMGR_EcuVoltageMonitorMainFunction();
   if(++ucAtaIrqTimeout == 20){
      ATA_ReInitAfterError();
   }
   TerminateTask();
}

FUNC(void, OS_STARTUPHOOK_CODE) StartupHook(void){
   OSTM0_SetInterrupt(cOSTM0_IRQ_ACTIVE);
   Os_Enable_CAT2ISR_OneMillisecond();
   Os_Disable_CAT2ISR_TelRec();
   Os_Disable_CAT2ISR_Can0Receive();
   Os_Disable_CAT2ISR_Can0Transmit();
   Os_Disable_CAT2ISR_Wakeup();
   Os_Enable_CAT2ISR_Timer0();
   Os_Enable_CAT2ISR_Timer1();
   Os_Enable_CAT2ISR_Timer2();
   Os_Enable_CAT2ISR_Timer3();
   Os_Enable_CAT2ISR_VoltageMonitor();
   EcuM_StartupTwo();
   Dem_SetOperationCycleState(DemConf_DemOperationCycle_DemOperationCycle_POWER, DEM_CYCLE_STATE_START);
   ApplMcu_vCheckWakeupSource();
   TP3(0);
}

FUNC(void, OS_SHUTDOWNHOOK_CODE) ShutdownHook(StatusType Error){
   if(Error == E_OS_STACKFAULT){
      Os_Restart();
   }
   else if(Error == E_OS_STATE){
      TP3(1);
      while(1){}
   }
   else if(Error == E_OS_SYS_NO_RESTART){
      EcuM_Shutdown();
   }
   else if(Error == E_OK){
   }
}

FUNC(void, OS_ERRORHOOK_CODE) ErrorHook(StatusType Error){
   switch(Error){
      case E_OS_ID:    break;
      case E_OS_VALUE: break;
      case E_OS_STATE: break;
      default:         break;
   }
}

FUNC(void, OS_OS_CBK_STACKOVERRUNHOOK_CODE) Os_Cbk_StackOverrunHook(
      Os_StackSizeType    Overrun
   ,  Os_StackOverrunType Reason
){
   while(1){
      TP3(1);
      Wdt_TriggerWD0();
   }
}

FUNC(void, OS_STARTUPHOOK_HUFTPMS_CODE) StartupHook_HufTpms(void){
}

FUNC(void, OS_SHUTDOWNHOOK_HUFTPMS_CODE) ShutdownHook_HufTpms(StatusType Error){
}

FUNC(void, OS_ERRORHOOK_HUFTPMS_CODE) ErrorHook_HufTpms(StatusType Error){
}

