
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "EcuM.h"

#include "EcuM_Cfg_SchM.h"
#include "EcuM_Callout.h"
#include "EcuM_RunTime.h"
#include "EcuM_Prv.h"

#include "SysManagerX.h"
#include "Dem.h"
#include "ApplVect.h"
#include "Wdt.h"
uint8* __attribute__ ((section (".rdata"))) pClear;
uint32 __attribute__ ((section (".rdata"))) ulRamStart;
uint32 __attribute__ ((section (".rdata"))) ulRamEnd;

#include "Os.h"
#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#include "NvM.h"
#if (!defined(NVM_AR_RELEASE_MAJOR_VERSION) || (NVM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(NVM_AR_RELEASE_MINOR_VERSION) || (NVM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_MemMap.h"

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
#include "EcuM_MemMap.h"

#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_MemMap.h"

void EcuM_ErrorHook(uint16 reason )
{
    while(1)
    {
      Wdt_TriggerWD0();
    }
}

#ifndef ECUM_CFG_ON_GOOFFONE

void EcuM_OnGoOffOne(void )
{

    EcuM_IsOnGoOffOneReached_b = TRUE;
}
#endif

#ifndef ECUM_CFG_ON_GOOFFTWO

void EcuM_OnGoOffTwo(void )
{
    EcuM_IsOnGoOffTwoReached_b = TRUE;
    Dem_Shutdown();
    Memstack_WriteAllBlocks();
}
#endif

#ifndef ECUM_CFG_AL_SWITCHOFF

void EcuM_AL_SwitchOff(void )
{
    Type_SwcServiceEcuM_tTargetShutdown ucSdTarget;
    Type_SwcServiceEcuM_tModeShutdown ucSdMode;

    EcuM_IsALSwitchOffReached_b = TRUE;

    EcuM_GetShutdownTarget(&ucSdTarget, &ucSdMode); //RST Info: this is the BSW function. Only shutdown target "SHUTDOWN" is returned,
                                                    // because sleep mode configuration is not possible (BSWM would be necessary for this).
    ucSdTarget = SYSMGR_GetShutdownTarget();        //RST Workaround: overwrite the shutdown target with the value previously set in SysManager

    if (ucSdTarget == ECUM_SHUTDOWN_TARGET_SLEEP)
    {
      Mcu_DeepStop();
    }
    else if (ucSdTarget == ECUM_SHUTDOWN_TARGET_OFF)
    {
      Mcu_Shutdown();
    }
    else
    {
      Mcu_PerformReset();
    }
}
#endif

void EcuM_AL_Reset( EcuM_ResetType reset )
{

  uint8 ucResetTypeLocal;

  tFblBmHeader* pBootManHeader = (tFblBmHeader*)cBootmanHeaderAddress;

  void(*pFblStart)(void) = (void(*)(void))(pBootManHeader->pFblStartFct);

  const void(*pSmartTesterStart)(void) = (const void(*)(void))(0x78000u);

  ucResetTypeLocal = SYSMGR_GeMcalMcu_eReasonReset();

  if (ucResetTypeLocal == cRESET_TYPE_RESET)
  {
    Wdt_TriggerWD0();
    Mcu_PerformReset();
  }

  else if (ucResetTypeLocal == cRESET_TYPE_START_BOOTLOADER)
  {
    Wdt_TriggerWD0();
    (*pFblStart)();
  }

  else if (ucResetTypeLocal == cRESET_TYPE_START_SMART_TESTER)
  {
    Wdt_TriggerWD0();

    //RST Debug: clear RAM below Stack
    ulRamStart = 0xFEDF8000;
    //ulRamEnd = 0xFEDFB000;
    ulRamEnd = 0xFEE07C00;
    for (pClear=(uint8*)ulRamStart; pClear<(uint8*)ulRamEnd; pClear++)
    {
      *pClear = 0x00;
    }
    //RST Debug: clear RAM above Stack (without RRAM for standstill monitoring because ulRamStart, End and pClear are located there!)

    (*pSmartTesterStart)();
  }

  else {}

  //Mcu_DeepStop(); //RST Info: just for debugging this path
}

void EcuM_CheckWakeup( Type_SwcServiceEcuM_tSourceWakeup wakeupSource )
                        {

                        }

void EcuM_StartWakeupSources( Type_SwcServiceEcuM_tSourceWakeup wakeupSource )
                        {

                        }

void EcuM_StopWakeupSources( Type_SwcServiceEcuM_tSourceWakeup wakeupSource )
                        {

                        }

void EcuM_CheckValidation( Type_SwcServiceEcuM_tSourceWakeup wakeupSource )
                        {

                        }

#if  (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)

void EcuM_EnableWakeupSources(Type_SwcServiceEcuM_tSourceWakeup wakeupSource)
                        {

                        }

void EcuM_DisableWakeupSources(Type_SwcServiceEcuM_tSourceWakeup wakeupSource)
                        {

                        }

uint8 EcuM_CheckRamHash(void)
                        {

                        }

void EcuM_GenerateRamHash(void)
                        {

                        }

void EcuM_StartCheckWakeup(Type_SwcServiceEcuM_tSourceWakeup wakeupSource)
                        {

    uint8 ctrLoop1_u8 = 0;

    Type_SwcServiceEcuM_tModeShutdown dataSleepModeHandle_u16 = 0xFF;

    SchM_Enter_EcuM();

    dataSleepModeHandle_u16 = EcuM_Lok_SleepMode_u16;
    SchM_Exit_EcuM();

    for( ctrLoop1_u8 = 0;ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop1_u8++ )
    {
        SchM_Enter_EcuM();
        if(((EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].WakeupSourceId & wakeupSource)!= CfgSwcServiceEcuM_dSourceWakeupNone) && \
                (EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop1_u8].CheckWakeupTimeout != 0) &&\
                ((EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].WakeupSourceId & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask)!= CfgSwcServiceEcuM_dSourceWakeupNone))
        {
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_TIMER_STARTED_E;
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop1_u8].CheckWakeupTimeout;

        }
        else
        {
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_FLAG_RESET_E;
            EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = 0;

        }
        SchM_Exit_EcuM();
    }

                        }

void EcuM_SleepActivity(void)
                        {

                        }
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_MemMap.h"

