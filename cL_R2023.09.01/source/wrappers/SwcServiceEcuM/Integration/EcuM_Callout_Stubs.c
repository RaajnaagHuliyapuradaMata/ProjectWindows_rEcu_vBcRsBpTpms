#include "Std_Types.hpp"

#include "EcuM.hpp"
#include "EcuM_Callout.hpp"
#include "EcuM_RunTime.hpp"
#include "EcuM_Prv.hpp"
#include "SysManagerX.hpp"
#include "Dem.hpp"
#include "ApplVect.hpp"
#include "Wdt.hpp"

uint8* __attribute__ ((section (".rdata"))) pClear;
uint32 __attribute__ ((section (".rdata"))) ulRamStart;
uint32 __attribute__ ((section (".rdata"))) ulRamEnd;

#include "Os.hpp"
#if(ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#include "NvM.hpp"
#endif

#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_MemMap.hpp"
#ifndef ECUM_CFG_ON_GOOFFONE
static volatile boolean EcuM_IsOnGoOffOneReached_b;
#endif

#ifndef ECUM_CFG_ON_GOOFFTWO
static volatile boolean EcuM_IsOnGoOffTwoReached_b;
#endif

#ifndef ECUM_CFG_AL_SWITCHOFF
static volatile boolean EcuM_IsALSwitchOffReached_b;
#endif
#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_MemMap.hpp"
void EcuM_ErrorHook(uint16 reason){
   while(1){
      Wdt_TriggerWD0();
   }
}

#ifndef ECUM_CFG_ON_GOOFFONE
void EcuM_OnGoOffOne(void){
   EcuM_IsOnGoOffOneReached_b = TRUE;
}
#endif

#ifndef ECUM_CFG_ON_GOOFFTWO
void EcuM_OnGoOffTwo(void){
   EcuM_IsOnGoOffTwoReached_b = TRUE;
   Dem_Shutdown();
   Memstack_WriteAllBlocks();
}
#endif

#ifndef ECUM_CFG_AL_SWITCHOFF
void EcuM_AL_SwitchOff(void){
   Type_SwcServiceEcuM_tTargetShutdown ucSdTarget;
   Type_SwcServiceEcuM_tModeShutdown   ucSdMode;
   EcuM_IsALSwitchOffReached_b = TRUE;
   EcuM_GetShutdownTarget(
         &ucSdTarget
      ,  &ucSdMode
   );
   ucSdTarget = SYSMGR_GetShutdownTarget();

        if(ucSdTarget == ECUM_SHUTDOWN_TARGET_SLEEP){ApplMcu_vDeepStop();     }
   else if(ucSdTarget == ECUM_SHUTDOWN_TARGET_OFF  ){ApplMcu_vShutdown();     }
   else                                             {ApplMcu_vPerformReset(); }
}
#endif

void EcuM_AL_Reset(EcuM_ResetType reset){
  uint8 ucResetTypeLocal;
  tFblBmHeader* pBootManHeader = (tFblBmHeader*)cBootmanHeaderAddress;
  void(*pFblStart)(void) = (void(*)(void))(pBootManHeader->pFblStartFct);
  const void(*pSmartTesterStart)(void) = (const void(*)(void))(0x78000u);
  ucResetTypeLocal = SYSMGR_GeMcalMcu_eReasonReset();
  if(ucResetTypeLocal == cRESET_TYPE_RESET){
    Wdt_TriggerWD0();
    ApplMcu_vPerformReset();
  }
  else if(ucResetTypeLocal == cRESET_TYPE_START_BOOTLOADER){
    Wdt_TriggerWD0();
    (*pFblStart)();
  }
  else if(ucResetTypeLocal == cRESET_TYPE_START_SMART_TESTER){
    Wdt_TriggerWD0();
   ulRamStart = 0xFEDF8000;
   ulRamEnd = 0xFEE07C00;
   for(pClear=(uint8*)ulRamStart; pClear<(uint8*)ulRamEnd; pClear++){
      *pClear = 0x00;
   }
    (*pSmartTesterStart)();
  }
  else{
  }
}

void EcuM_CheckWakeup(        Type_SwcServiceEcuM_tSourceWakeup wakeupSource){}
void EcuM_StartWakeupSources( Type_SwcServiceEcuM_tSourceWakeup wakeupSource){}
void EcuM_StopWakeupSources(  Type_SwcServiceEcuM_tSourceWakeup wakeupSource){}
void EcuM_CheckValidation(    Type_SwcServiceEcuM_tSourceWakeup wakeupSource){}

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
void  EcuM_EnableWakeupSources( Type_SwcServiceEcuM_tSourceWakeup wakeupSource){}
void  EcuM_DisableWakeupSources(Type_SwcServiceEcuM_tSourceWakeup wakeupSource){}
uint8 EcuM_CheckRamHash(void){}
void  EcuM_GenerateRamHash(void){}

void EcuM_StartCheckWakeup(Type_SwcServiceEcuM_tSourceWakeup wakeupSource){
   uint8 ctrLoop1_u8 = 0;
   Type_SwcServiceEcuM_tModeShutdown dataSleepModeHandle_u16 = 0xFF;
   SchM_Enter_EcuM();
   dataSleepModeHandle_u16 = EcuM_Lok_SleepMode_u16;
   SchM_Exit_EcuM();
   for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ ){
        SchM_Enter_EcuM();
        if(((EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].WakeupSourceId & wakeupSource)!= CfgSwcServiceEcuM_dSourceWakeupNone) && \
                (EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop1_u8].CheckWakeupTimeout != 0) &&\
                ((EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].WakeupSourceId & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask)!= CfgSwcServiceEcuM_dSourceWakeupNone)
        ){
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_TIMER_STARTED_E;
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop1_u8].CheckWakeupTimeout;
        }
        else{
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_FLAG_RESET_E;
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = 0;
        }
        SchM_Exit_EcuM();
   }
}

void EcuM_SleepActivity(void){}
#endif
#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_MemMap.hpp"

