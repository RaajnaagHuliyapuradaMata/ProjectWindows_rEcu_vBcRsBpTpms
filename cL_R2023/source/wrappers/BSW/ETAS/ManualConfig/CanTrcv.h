
#ifndef _CANTRCV_H
#define _CANTRCV_H

#include "Can_GeneralTypes.h"

extern void TRCV_Standby(void);
extern void TRCV_Normal(void);
extern boolean TRCV_GetWakeupFlag(void);

#endif

//#if !defined (CANTRCV_30_TJA1043_API_H)
//# define CANTRCV_30_TJA1043_API_H
//
//
//
//
//#define V_CANTRCV_30_TJA1043_HEADER
//
//
//
//# include "CanTrcv_Cfg.h"
//
//# include "SchM_CanTrcv.h"
//
//
//#if ( (CANTRCV_30_TJA1043_AUTOSAR_VERSION==CANTRCV_30_TJA1043_ASR4X) )
//# define CANTRCV_30_TJA1043_AR_RELEASE_MAJOR_VERSION      4
//# define CANTRCV_30_TJA1043_AR_RELEASE_MINOR_VERSION      0
//# define CANTRCV_30_TJA1043_AR_RELEASE_REVISION_VERSION   3
//# define CANTRCV_30_TJA1043_AUTOSARVERSION_4X             0x403
//#endif
//
//#if ( (CANTRCV_30_TJA1043_AUTOSAR_VERSION==CANTRCV_30_TJA1043_ASR3X) )
//# define CANTRCV_30_TJA1043_AR_MAJOR_VERSION               0x02u
//# define CANTRCV_30_TJA1043_AR_MINOR_VERSION               0x00u
//# define CANTRCV_30_TJA1043_AR_PATCH_VERSION               0x00u
//# define CANTRCV_30_TJA1043_AUTOSARVERSION_3X              0x321
//#endif
//
//
//
//# define DRVTRANS_TJA1043CANDIOASR_VERSION                 0x0301u
//# define DRVTRANS_TJA1043CANDIOASR_RELEASE_VERSION         0x00u
//
//#if defined(CANTRCV_30_TJA1043_INCLUDE_INTERNAL)
//
//# define DRVTRANS__CORECANXASR_VERSION                         0x0401u
//# define DRVTRANS__CORECANXASR_RELEASE_VERSION                 0x00u
//#endif
//
//#  define CANTRCV_30_TJA1043_SW_MAJOR_VERSION               ((DRVTRANS_TJA1043CANDIOASR_VERSION & 0xFF00u) >> 8)
//#  define CANTRCV_30_TJA1043_SW_MINOR_VERSION               (DRVTRANS_TJA1043CANDIOASR_VERSION & 0x00FFu)
//#  define CANTRCV_30_TJA1043_SW_PATCH_VERSION               DRVTRANS_TJA1043CANDIOASR_RELEASE_VERSION
//
//
//# define CANTRCV_30_TJA1043_VENDOR_ID                      30
//# define CANTRCV_30_TJA1043_MODULE_ID                      70
//
//
//# define CANTRCV_30_TJA1043_INIT_ID                        0x00
//# define CANTRCV_30_TJA1043_SETOPMODE_ID                   0x01
//# define CANTRCV_30_TJA1043_GETOPMODE_ID                   0x02
//# define CANTRCV_30_TJA1043_GETBUSWUREASON_ID              0x03
//# define CANTRCV_30_TJA1043_GETVERSIONINFO_ID              0x04
//# define CANTRCV_30_TJA1043_SETWAKEUPMODE_ID               0x05
//# define CANTRCV_30_TJA1043_MAINFUNCTION_ID                0x06
//# define CANTRCV_30_TJA1043_CB_WAKEUPBYBUS_ID              0x07
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_4X)
//#  define CANTRCV_30_TJA1043_CHECKWAKEUP_ID CANTRCV_30_TJA1043_CB_WAKEUPBYBUS_ID
//# endif
//# define CANTRCV_30_TJA1043_MAINFUNCTIONDIAGNOSTICS        0x08
//# define CANTRCV_30_TJA1043_GETTRCVSYSTEMDATA_ID           0x09
//# define CANTRCV_30_TJA1043_CLEARTRCVWUFFLAG_ID            0x0A
//# define CANTRCV_30_TJA1043_READTRCVTIMEOUTFLAG_ID         0x0B
//# define CANTRCV_30_TJA1043_CLEARTRCVTIMEOUTFLAG_ID        0x0C
//# define CANTRCV_30_TJA1043_READTRCVSILENCEFLAG_ID         0x0D
//# define CANTRCV_30_TJA1043_CHECKWAKEFLAG_ID               0x0E
//# define CANTRCV_30_TJA1043_SETPNACTIVATIONSTATE_ID        0x0F
//
//
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_4X)
//#  define CANTRCV_30_TJA1043_OP_MODE_NORMAL                 CANTRCV_TRCVMODE_NORMAL
//#  define CANTRCV_30_TJA1043_OP_MODE_STANDBY                CANTRCV_TRCVMODE_STANDBY
//#  define CANTRCV_30_TJA1043_OP_MODE_SLEEP                  CANTRCV_TRCVMODE_SLEEP
//# endif
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_3X)
//#  define CANTRCV_30_TJA1043_OP_MODE_NORMAL                 CANIF_TRCV_MODE_NORMAL
//#  define CANTRCV_30_TJA1043_OP_MODE_STANDBY                CANIF_TRCV_MODE_STANDBY
//#  define CANTRCV_30_TJA1043_OP_MODE_SLEEP                  CANIF_TRCV_MODE_SLEEP
//# endif
//
//
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_4X)
//#  define CANTRCV_30_TJA1043_WU_ENABLE                      CANTRCV_WUMODE_ENABLE
//#  define CANTRCV_30_TJA1043_WU_DISABLE                     CANTRCV_WUMODE_DISABLE
//#  define CANTRCV_30_TJA1043_WU_CLEAR                       CANTRCV_WUMODE_CLEAR
//# endif
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_3X)
//#  define CANTRCV_30_TJA1043_WU_ENABLE                      CANIF_TRCV_WU_ENABLE
//#  define CANTRCV_30_TJA1043_WU_DISABLE                     CANIF_TRCV_WU_DISABLE
//#  define CANTRCV_30_TJA1043_WU_CLEAR                       CANIF_TRCV_WU_CLEAR
//# endif
//
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_4X)
//#  define CANTRCV_30_TJA1043_WU_ERROR                       CANTRCV_WU_ERROR
//#  define CANTRCV_30_TJA1043_WU_NOT_SUPPORTED               CANTRCV_WU_NOT_SUPPORTED
//#  define CANTRCV_30_TJA1043_WU_BY_BUS                      CANTRCV_WU_BY_BUS
//#  define CANTRCV_30_TJA1043_WU_INTERNALLY                  CANTRCV_WU_INTERNALLY
//#  define CANTRCV_30_TJA1043_WU_RESET                       CANTRCV_WU_RESET
//#  define CANTRCV_30_TJA1043_WU_POWER_ON                    CANTRCV_WU_POWER_ON
//#  define CANTRCV_30_TJA1043_WU_BY_PIN                      CANTRCV_WU_BY_PIN
//#  define CANTRCV_30_TJA1043_WU_BY_SYSERR                   CANTRCV_WU_BY_SYSERR
//# endif
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_3X)
//#  define CANTRCV_30_TJA1043_WU_ERROR                       CANIF_TRCV_WU_ERROR
//#  define CANTRCV_30_TJA1043_WU_NOT_SUPPORTED               CANIF_TRCV_WU_NOT_SUPPORTED
//#  define CANTRCV_30_TJA1043_WU_BY_BUS                      CANIF_TRCV_WU_BY_BUS
//#  define CANTRCV_30_TJA1043_WU_INTERNALLY                  CANIF_TRCV_WU_INTERNALLY
//#  define CANTRCV_30_TJA1043_WU_RESET                       CANIF_TRCV_WU_RESET
//#  define CANTRCV_30_TJA1043_WU_POWER_ON                    CANIF_TRCV_WU_POWER_ON
//#  define CANTRCV_30_TJA1043_WU_BY_PIN                      CANIF_TRCV_WU_BY_PIN
//#  define CANTRCV_30_TJA1043_WU_BY_SYSERR                   CANIF_TRCV_WU_BY_SYSERR
//# endif
//
//# define CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK          0x01
//
//#  define CANTRCV_30_TJA1043_E_INVALID_TRANSCEIVER         CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK
//# define CANTRCV_30_TJA1043_E_PARAM_POINTER                0x02
//# define CANTRCV_30_TJA1043_E_UNINIT                       0x11
//# define CANTRCV_30_TJA1043_E_TRCV_NOT_STANDBY             0x21
//# define CANTRCV_30_TJA1043_E_TRCV_NOT_NORMAL              0x22
//# define CANTRCV_30_TJA1043_E_PARAM_TRCV_WAKEUP_MODE       0x23
//# define CANTRCV_30_TJA1043_E_PARAM_TRCV_OP_MODE           0x24
//# define CANTRCV_30_TJA1043_E_BAUDRATE_NOT_SUPPORTED       0x25
//# define CANTRCV_30_TJA1043_E_CLR_TRCV_WUF_NOT_CALLED      0x30
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_4X)
//#  define CANTRCV_30_TJA1043_E_NO_TRCV_CONTROL             0x40
//# endif
//
//
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_4X)
//#  define CANTRCV_30_TJA1043_WAKEUP_NOT_SUPPORTED          0
//#  define CANTRCV_30_TJA1043_WAKEUP_BY_POLLING             1
//
//#  define CANTRCV_30_TJA1043_WAKEUP_NONE                   CANTRCV_30_TJA1043_WAKEUP_NOT_SUPPORTED
//#  define CANTRCV_30_TJA1043_WAKEUP_POLLING                CANTRCV_30_TJA1043_WAKEUP_BY_POLLING
//# endif
//
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_3X)
//#  define CANTRCV_30_TJA1043_WAKEUP_NONE                    0
//#  define CANTRCV_30_TJA1043_WAKEUP_POLLING                 1
//#  define CANTRCV_30_TJA1043_WAKEUP_ISR                     2
//# endif
//
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_4X)
//#  define CanTrcv_30_Tja1043_TrcvModeType                  CanTrcv_TrcvModeType
//#  define CanTrcv_30_Tja1043_TrcvWakeupModeType            CanTrcv_TrcvWakeupModeType
//#  define CanTrcv_30_Tja1043_TrcvWakeupReasonType          CanTrcv_TrcvWakeupReasonType
//# endif
//# if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_3X)
//#  define CanTrcv_30_Tja1043_TrcvModeType                  CanIf_TransceiverModeType
//#  define CanTrcv_30_Tja1043_TrcvWakeupModeType            CanIf_TrcvWakeupModeType
//#  define CanTrcv_30_Tja1043_TrcvWakeupReasonType          CanIf_TrcvWakeupReasonType
//# endif
//
//#define CanTrcv_InitMemory() CanTrcv_30_Tja1043_InitMemory()
//#define CanTrcv_Init(x) CanTrcv_30_Tja1043_Init(x)
//#define CanTrcv_SetOpMode(x, y) CanTrcv_30_Tja1043_SetOpMode(x, y)
//#define CanTrcv_GetOpMode(x, y) CanTrcv_30_Tja1043_GetOpMode(x, y)
//#define CanTrcv_MainFunction() CanTrcv_30_Tja1043_MainFunction()
//
//# if defined(CANTRCV_30_TJA1043_USE_ICU)
//# else
//#  define CANTRCV_30_TJA1043_USE_ICU                       STD_OFF
//# endif
//
//
//
//
//# define CANTRCV_30_TJA1043_USE_TIMERS                    STD_OFF
//
//
//# define kCanTrcv_30_Tja1043_LoopInit                          0x01
//
//
//
//
//
//
//
//
//
//
//typedef enum
//{
//  CANTRCV_30_TJA1043_FLAG_SET,
//  CANTRCV_30_TJA1043_FLAG_CLEARED
//}
//CanTrcv_30_Tja1043_TrcvFlagStateType;
//
//typedef enum
//{
//  CANTRCV_30_TJA1043_PN_ENABLED,
//  CANTRCV_30_TJA1043_PN_DISABLED
//} CanTrcv_30_Tja1043_PNActivationType;
//
//
//
//
//
//# define CANTRCV_30_TJA1043_START_SEC_CODE
//# include "MemMap.h"
//
//
//
//FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_Init( P2CONST(CanTrcv_30_Tja1043_ConfigType, AUTOMATIC, CANTRCV_30_TJA1043_CONST) ConfigPtr );
//
//
//FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_InitMemory(void);
//
//
//#if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_4X)
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_SetOpMode(uint8 CanTrcvIndex, CanTrcv_TrcvModeType OpMode);
//
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_GetOpMode(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_30_TJA1043_APPL_VAR) OpMode);
//
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_GetBusWuReason(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_30_TJA1043_APPL_VAR) Reason);
//
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_SetWakeupMode(uint8 CanTrcvIndex, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);
//
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_CheckWakeup(uint8 CanTrcvIndex);
//#endif
//
//#if defined(CANTRCV_30_TJA1043_AUTOSARVERSION_3X)
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_SetOpMode(CanIf_TransceiverModeType OpMode, uint8 CanTrcvIndex);
//
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_GetOpMode(P2VAR(CanIf_TransceiverModeType, AUTOMATIC, CANTRCV_30_TJA1043_APPL_VAR) OpMode, uint8 CanTrcvIndex);
//
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_GetBusWuReason(uint8 CanTrcvIndex, P2VAR(CanIf_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_30_TJA1043_APPL_VAR) Reason);
//
//
//FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_SetWakeupMode(CanIf_TrcvWakeupModeType TrcvWakeupMode, uint8 CanTrcvIndex);
//#endif
//
//# if (CANTRCV_30_TJA1043_GET_VERSION_INFO == STD_ON)
//
//FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_30_TJA1043_APPL_VAR) VersionInfo);
//# endif
//
//
//
//
//FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_MainFunction(void);
//
//
//
//# define CANTRCV_30_TJA1043_STOP_SEC_CODE
//# include "MemMap.h"
//
//#endif
//
//
