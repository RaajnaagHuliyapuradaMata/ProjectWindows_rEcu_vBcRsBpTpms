

#ifndef RDC_STANDSTILL_X_H
#define RDC_STANDSTILL_X_H

#include "Std_Types.h"
#include "version.h"
#ifdef DEBUG_PRESSURE_ON_KEY
#include "RdcStandstillDebugX.h"
#endif

#define RDCST_WS_FL       ((uint8) 0U)
#define RDCST_WS_FR       ((uint8) 1U)
#define RDCST_WS_RL       ((uint8) 2U)
#define RDCST_WS_RR       ((uint8) 3U)

extern void RdcSt_Init(void);

extern void RdcSt_InitBSWNvM(void);

extern void RdcSt_StartStandstillMonitoring(void);

extern void RdcSt_StopStandstillMonitoring(void);

extern boolean RdcSt_IsStandstillMonitoringActive(void);

extern void RdcSt_ProcessStandstillTelegram(uint8 *PU8_TelegramData);

extern void RdcSt_MainFunction(void);

extern void RdcSt_ForwardStandstillDataToTms(void);

extern void RdcSt_StartMonitoringSpecificWS(uint8 U8_WsNumber);

extern void RdcSt_ReadPressureOnKeyConfig(uint8 *PU8_Data);

extern void RdcSt_WritePressureOnKeyConfig(const uint8 *PU8_Data);

extern void RdcSt_ReadPressureOnKeyStatus(uint8 *PU8_Data);

#ifdef DEBUG_PRESSURE_ON_KEY

extern void RdcSt_LoadDebugData(tStandstillDebugMsg *PS_Data);

extern boolean RdcSt_IsDebugMessagingActive(void);
#endif

#endif
