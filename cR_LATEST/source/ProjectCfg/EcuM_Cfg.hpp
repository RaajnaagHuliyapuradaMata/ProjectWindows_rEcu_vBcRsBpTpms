#ifndef ECUM_CFG_H
#define ECUM_CFG_H

#include "CfgMcalMcu.hpp"
#include "Os.hpp"
#include "CfgSwcServiceEcuM.hpp"
#include "infMcalMcuSwcApplEcuM.hpp" //TBD: change to Types_McalMcu.hpp

#define ECUM_DEV_ERROR_DETECT 	                                        STD_ON
#define ECUM_INCLUDE_DET                                                 STD_ON
#define ECUM_VERSION_INFO_API	                                           STD_OFF
#define ECUM_CFG_MODE_HANDLING                                           STD_OFF
#define ECUM_SLEEP_SUPPORT_ENABLE                                          FALSE
#define ECUM_CFG_ECUC_RB_RTE_IN_USE                                        FALSE
#define ECUM_CFG_NVM_BLOCK_CONFIGURED                                       TRUE
#define ECUM_CFG_STARTUP_CORE                                  OS_CORE_ID_MASTER
#define ECUM_NORMAL_MCU_MODE                                    ((Mcu_ModeType))
#define EcuMConf_EcuMFlexUserConfig_EcuMFlexUserConfig_0	            ((uint16)1)
#define ECUM_UNCONFIGURED_WKP_SOURCES               (~ECUM_KNOWN_WAKEUP_SOURCES)
#define ECUM_CFG_GODOWN_CALLER_ARR_LEN	                                     (1U)
#define ECUM_CFG_NUM_RESET_MODES	                                           (3U)
#define ECUM_CFG_NUM_SHUTDOWN_CAUSE                                            4
#define CfgSwcServiceEcuM_dNumSourceWakeup                                  (5U)
#define ECUM_CFG_NUM_SLEEP_MODES                                     ((uint16)0)
#define ECUM_CFG_NUM_OS_CORES	                                       ((uint16)1)
#define ECUM_WAKEUP_SOURCES_WITH_VALIDATION                ((uint32)0x00000000u)
#define ECUM_WKUP_SRC_START_BIT_MASK                       ((uint32)0x00000001u)

#define ECUM_UNINTENDED_RESET_MSK (uint32) ( \
      CfgSwcServiceEcuM_dINTERNAL_RESET      \
   |  CfgSwcServiceEcuM_dEXTERNAL_WDG        \
   |  CfgSwcServiceEcuM_dINTERNAL_WDG        \
   |  CfgSwcServiceEcuM_dPOWER               \
   |  CfgSwcServiceEcuM_dRESET               \
)

#define ECUM_KNOWN_WAKEUP_SOURCES (uint32) ( \
      CfgSwcServiceEcuM_dPOWER               \
   |  CfgSwcServiceEcuM_dRESET               \
   |  CfgSwcServiceEcuM_dINTERNAL_RESET      \
   |  CfgSwcServiceEcuM_dINTERNAL_WDG        \
   |  CfgSwcServiceEcuM_dEXTERNAL_WDG        \
)

#define ECUM_NON_BASIC_WKUPS_MSK ((ECUM_KNOWN_WAKEUP_SOURCES^ECUM_UNINTENDED_RESET_MSK))

#define ECUM_WAKEUP_SOURCES_WITHOUT_VALIDATION (uint32)( \
      CfgSwcServiceEcuM_dPOWER                           \
   |  CfgSwcServiceEcuM_dRESET                           \
   |  CfgSwcServiceEcuM_dINTERNAL_RESET                  \
   |  CfgSwcServiceEcuM_dINTERNAL_WDG                    \
   |  CfgSwcServiceEcuM_dEXTERNAL_WDG                    \
)

typedef struct{
   boolean                     IsComChannelPresent;
   uint8                       ComChannelReferance;
   Type_McalMcu_eResetReason ResetReason;
   uint16                      ValidationTimeout;
   boolean                     IsWakeupSourcePolling;
   uint32                      WakeupSourceId;
   uint16                      CheckWakeupTimeout;
}Type_CfgSwcServiceEcuM_stInfoSourceWakeUp;

typedef enum{
      ECUM_FLAG_RESET_E
   ,  ECUM_TIMER_STARTED_E
   ,  ECUM_SET_WAKEUP_EVENT_E
   ,  ECUM_END_CHECK_WAKEUP_E
   ,  ECUM_TIMER_EXPIRED_E
}EcuM_Wakeup_States_ten;

extern CONST(Type_CfgSwcServiceEcuM_stInfoSourceWakeUp, ECUM_CONST) CfgSwcServiceEcuM_castListInfoSourceWakeUp [CfgSwcServiceEcuM_dNumSourceWakeup];
extern CONST(uint16,                                    ECUM_CONST) EcuM_Cfg_idxGoDownValidCallerArr_au16      [ECUM_CFG_GODOWN_CALLER_ARR_LEN];
extern CONST(uint8,                                     ECUM_CONST) CfgSwcServiceEcuM_au8HashPreCompile        [CfgSwcServiceEcuM_dLenHash];

#endif
