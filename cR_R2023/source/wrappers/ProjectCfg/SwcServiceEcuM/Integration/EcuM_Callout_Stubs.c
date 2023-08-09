#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#endif

#include "EcuM.h"
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
#include "EcuM_Cfg_MemMap.h"

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
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_Cfg_MemMap.h"

FUNC(void , ECUM_CALLOUT_CODE) EcuM_ErrorHook(VAR(uint16, AUTOMATIC) reason )
{
    while(1)
    {
      Wdt_TriggerWD0();
    }
}

#ifndef ECUM_CFG_ON_GOOFFONE
FUNC(void , ECUM_CALLOUT_CODE) EcuM_OnGoOffOne(void )
{
    EcuM_IsOnGoOffOneReached_b = TRUE;
}
#endif

#ifndef ECUM_CFG_ON_GOOFFTWO

FUNC(void , ECUM_CALLOUT_CODE) EcuM_OnGoOffTwo(void )
{
    EcuM_IsOnGoOffTwoReached_b = TRUE;
    Dem_Shutdown();
    Memstack_WriteAllBlocks();
}
#endif

#ifndef ECUM_CFG_AL_SWITCHOFF

FUNC(void , ECUM_CALLOUT_CODE) EcuM_AL_SwitchOff(void )
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

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_AL_Reset( VAR(EcuM_ResetType, AUTOMATIC) reset )
{

  uint8 ucResetType;

  tFblBmHeader* pBootManHeader = (tFblBmHeader*)cBootmanHeaderAddress;

  void(*pFblStart)(void) = (void(*)(void))(pBootManHeader->pFblStartFct);

  const void(*pSmartTesterStart)(void) = (const void(*)(void))(0x78000u);

  ucResetType = SYSMGR_GeMcalMcu_eReasonReset();

  if (ucResetType == cRESET_TYPE_RESET)
  {
    Wdt_TriggerWD0();
    Mcu_PerformReset();
  }

  else if (ucResetType == cRESET_TYPE_START_BOOTLOADER)
  {
    Wdt_TriggerWD0();
    (*pFblStart)();
  }

  else if (ucResetType == cRESET_TYPE_START_SMART_TESTER)
  {
    Wdt_TriggerWD0();

    // clear RAM below Stack
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

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_CheckWakeup( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource )
                        {

                        }

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_StartWakeupSources( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource )
                        {

                        }

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_StopWakeupSources( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource )
                        {

                        }

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_CheckValidation( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource )
                        {

                        }

#if ECUM_SLEEP_SUPPORT_ENABLE

FUNC(void, ECUM_CALLOUT_CODE) EcuM_EnableWakeupSources(VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource)
                        {

                        }

FUNC(void, ECUM_CALLOUT_CODE) EcuM_DisableWakeupSources(VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource)
                        {

                        }

FUNC(uint8, ECUM_CALLOUT_CODE) EcuM_CheckRamHash(void)
                        {

                        }

FUNC(void, ECUM_CALLOUT_CODE) EcuM_GenerateRamHash(void)
                        {

                        }

FUNC(void, ECUM_CALLOUT_CODE) EcuM_StartCheckWakeup(VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) wakeupSource)
                        {

    VAR(uint8, AUTOMATIC) ctrLoop1_u8 = 0;

    VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC) dataSleepModeHandle_u16 = 0xFF;

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

FUNC(void, ECUM_CALLOUT_CODE) EcuM_SleepActivity(void)
                        {

                        }
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_Cfg_MemMap.h"

