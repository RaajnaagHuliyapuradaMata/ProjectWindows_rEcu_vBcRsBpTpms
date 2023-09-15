#include "Std_Types.hpp"

#include "infMcalMcuSwcApplEcuM.hpp"

#include "device.hpp"
#include "CfgMcalMcu.hpp"
#include "Can.hpp"
#include "CanTrcv.hpp"
#include "EcuM.hpp"
#include "Dem.hpp"
#include "Os_ConfigInterrupts.hpp"
#include "SysManagerX.hpp"
#include "DcmManagerX.hpp"
#include "gpioX.hpp"
#include "clocksX.hpp"
#include "ata_dev_5785_X.hpp"
#include "wdt.hpp"
#include "tau.hpp"

void ApplMcu_vPerformReset(void){
   __DI();
   Wdt_InitWD1();
   Wdt_TriggerWD1();
   while(1);
}

void ApplMcu_vDeepStop(void){
   __DI();
   Wdt_TriggerWD0();
   if(TRCV_GetWakeupFlag() == TRUE){
      ApplMcu_vPerformReset();
   }
   Can_SetControllerMode(0, CAN_T_STOP);
   Can_SetControllerMode(0, CAN_T_SLEEP);
   TRCV_Standby();
   rf_ata5785_off_mode();
   GPIO_DeInit();
   GPIO_TjaErrInterrupt(c_IRQ_ACTIVE);

   WUFMSK0 = ~(CFGMCALMCU_WUP_FACTOR_TJA_ERR |
              CFGMCALMCU_WUP_FACTOR_TAUJ00  |
              CFGMCALMCU_WUP_FACTOR_TAUJ01  |
              CFGMCALMCU_WUP_FACTOR_TAUJ02  |
              CFGMCALMCU_WUP_FACTOR_TAUJ03);

   WUFMSK20 = 0xffffffffu;
   WUFMSK_ISO0 = 0xffffffffu;

   WUFC0 = 0xffffffffu;
   WUFC20 = 0xffffffffu;
   WUFC_ISO0 = 0xffffffffu;

   RESFC = 0x000007ffu;
   RESFCR = 0x000007ffu;

   CLOCKS_SetMainOscClock();
   CLOCKS_DisableClockDomainsForDeepSleep();

   protected_write(PROTCMD0,PROTS0,STBC0PSC,0x02u);
   while(1){}
}

void ApplMcu_vShutdown(void){
   __DI();
   Wdt_TriggerWD0();
   while(1){
      if(TRCV_GetWakeupFlag() == TRUE){
         ApplMcu_vPerformReset();
      }
      else{
         McalDio_vInitOutputOff(GPIO_STB_TJA);
         WaitHard(2000);
         McalDio_vInitOutputOff(GPIO_EN_TJA);
         GPIO_output_on(GPIO_STB_TJA);
         GPIO_output_on(GPIO_EN_TJA);
         WaitHard(15);
      }
   }
}

void ApplMcu_vCheckWakeupSource(void){
   if(McalMcu_eReasonReset == McalMcu_eReasonReset_WakeupTimer){
      if((WUF0 & CFGMCALMCU_WUP_FACTOR_TAUJ00) == CFGMCALMCU_WUP_FACTOR_TAUJ00){
         MKTAUJ0I0 = 0U;
         RFTAUJ0I0 = 1U;
      }
      else if((WUF0 & CFGMCALMCU_WUP_FACTOR_TAUJ01) == CFGMCALMCU_WUP_FACTOR_TAUJ01){
         MKTAUJ0I1 = 0U;
         RFTAUJ0I1 = 1U;
      }
      else if((WUF0 & CFGMCALMCU_WUP_FACTOR_TAUJ02) == CFGMCALMCU_WUP_FACTOR_TAUJ02){
         MKTAUJ0I2 = 0U;
         RFTAUJ0I2 = 1U;
      }
      else if((WUF0 & CFGMCALMCU_WUP_FACTOR_TAUJ03) == CFGMCALMCU_WUP_FACTOR_TAUJ03){
         MKTAUJ0I3 = 0U;
         RFTAUJ0I3 = 1U;
      }
   }
   else{
   }
   WUFC0   = 0xffffffffu;
   WUFMSK0 = 0xffffffffu;
}

void ApplMcu_vReleaseIoBuffers(void){
   if(WUF0 != 0){
      protected_write(PROTCMD0, PROTS0, IOHOLD, 0x00u);
      while(IOHOLD != 0x00u) {}
   }
}

void Mcu_Halt(void){
}

void Mcu_Stop(void){
   STBC0STPT |= 0x1;
}

void Mcu_CyclicRunMode(void){
}

void Mcu_CyclicStopMode(void){
}

