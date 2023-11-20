#ifndef ECUM_TYPES_H
#define ECUM_TYPES_H

#include "EcuM_Cfg.hpp"
#include "EcuM_RunTime.hpp"

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
#define ECUM_CAUSE_UNKNOWN                       0
#define ECUM_CAUSE_ECU_STATE                     1
#define ECUM_CAUSE_WDGM                          2
#define ECUM_CAUSE_DCM                           3
#define ECUM_BOOT_TARGET_APP                     0
#define ECUM_BOOT_TARGET_OEM_BOOTLOADER          1
#define ECUM_BOOT_TARGET_SYS_BOOTLOADER          2

#ifndef RTE_MODE_EcuM_Mode_POST_RUN
#define RTE_MODE_EcuM_Mode_POST_RUN              0U
#endif

#ifndef RTE_MODE_EcuM_Mode_RUN
#define RTE_MODE_EcuM_Mode_RUN                   1U
#endif

#ifndef RTE_MODE_EcuM_Mode_SHUTDOWN
#define RTE_MODE_EcuM_Mode_SHUTDOWN              2U
#endif

#ifndef RTE_MODE_EcuM_Mode_SLEEP
#define RTE_MODE_EcuM_Mode_SLEEP                 3U
#endif

#ifndef RTE_MODE_EcuM_Mode_STARTUP
#define RTE_MODE_EcuM_Mode_STARTUP               4U
#endif

#ifndef ECUM_SHUTDOWN_TARGET_SLEEP
#define ECUM_SHUTDOWN_TARGET_SLEEP               0U
#endif

#ifndef ECUM_SHUTDOWN_TARGET_RESET
#define ECUM_SHUTDOWN_TARGET_RESET               1U
#endif

#ifndef ECUM_SHUTDOWN_TARGET_OFF
#define ECUM_SHUTDOWN_TARGET_OFF                 2U
#endif

typedef uint8 EcuM_BootTargetType;
typedef uint32 EcuM_TimeType;
typedef uint16  EcuM_UserType;

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
typedef uint8 Rte_ModeType_EcuM_Mode;
#endif

#endif

typedef uint8       EcuM_ResetType;
typedef uint8       EcuM_WakeupStatusType;
typedef uint8       EcuM_RunStatusType;
typedef uint8       EcuM_StateType;

typedef struct{
   Type_SwcServiceEcuM_tCauseShutdown  tCauseShutdown;
}EcuM_ShutdownInfoType;

#endif

