

#ifndef RDC_STANDSTILL_H
#define RDC_STANDSTILL_H

#include "RdcStandstillX.hpp"

#define RDCST__PACKAGE_ID_STANDSTILL                                ((uint8) 0x90U)

#ifdef DEBUG_FAST_SHUTDOWN
#define RDCST__SYNC_PERIOD_DURATION_MINS                            ((uint32) 1U)
#else
#define RDCST__SYNC_PERIOD_DURATION_MINS                            ((uint32) 1U)
#endif
#define RDCST__SYNC_PERIOD_DURATION_MS                              ((uint32) (RDCST__SYNC_PERIOD_DURATION_MINS * 60U * 1000U))

#define RDCST__PRESSURE_ON_KEY_ENABLED_INIT                         ((uint8) 1U)
#define RDCST__WAKEUP_INTERVAL_INIT_XMIN                            ((uint8) 5U)
#define RDCST__WAKE_TIME_INIT_X100MS                                ((uint8) 70U)
#define RDCST__WAKE_OFFSET_INIT_X100MS                              ((uint8) 35U)
#define RDCST__POKDB_INIT                                           ((uint8) 0U)

#define RDCST__WAKEUP_TIMER_INITIAL_MULTIPLIER                      ((uint32) 1U)
#define RDCST__WAKEUP_TIMER_AFTER_1_DAY_MULTIPLIER                  ((uint32) 3U)
#define RDCST__WAKEUP_TIMER_AFTER_5_DAYS_MULTIPLIER                 ((uint32) 10U)

#define RDCST__ELAPSED_TIME_1_DAY_MS                                ((uint32) (24U * 60U * 60U * 1000U))
#define RDCST__ELAPSED_TIME_6_DAYS_MS                               ((uint32) (6U * RDCST__ELAPSED_TIME_1_DAY_MS))
#define RDCST__ELAPSED_TIME_22_DAYS_MS                              ((uint32) (22U * RDCST__ELAPSED_TIME_1_DAY_MS))

#define RDCST__WAKEUP_TIMER_MINS_TO_MS(mins)                        ((uint32) ((mins) * 60U * 1000U))
#define RDCST__WAKEUP_TIMER_100MS_TO_MS(units)                      ((uint32) ((units) * 100U))

#define RDCST__PRESSURE_INVALID_VALUE                               ((uint8) 0x00U)
#define RDCST__TEMPERATURE_INVALID_VALUE                            ((uint8) 0x00U)

#define RDCST__MONITORING_STATUS_CLEAR                              ((uint8) 0x00U)
#define RDCST__EXTENDED_WAKEUP_CLEAR                                ((uint8) 0x00U)

#define RDCST__TIMER_CLOSE_TO_EXPIRING_THRESHOLD_MS                 ((uint32) 1000U)
#define RDCST__EXTENDED_WAKEUP_INTERVAL_MIN                         ((uint32) 6U)
#define RDCST__EXTENDED_WAKEUP_INTERVAL_MS                          ((uint32) RDCST__WAKEUP_TIMER_MINS_TO_MS(RDCST__EXTENDED_WAKEUP_INTERVAL_MIN))

#define RDCST__DEFAULT_RSSI_FOR_STANDSTILL_TELEGRAMS                ((uint16) 120U)

#ifdef _RST_VS_EDITOR_SUPPORT_
//just to get an error free view in visual studio -> ms doesn't know ".rdata"
#define RRAM
#else
#define RRAM                                                        __attribute__ ((section (".rdata")))
#endif

#define RDCST__DATA_EXISTENCE_TRUE                                  ((uint8) 0xAAU)
#define RDCST__DATA_EXISTENCE_FALSE                                 ((uint8) 0x55U)
#define RDCST__GLOBAL_INDEX_WS_POS                                  ((uint8) 30U)

typedef union
{
  uint32 U32_Config;
  struct
  {
   uint8 U8_PressureOnKeyEnabled;
   uint8 U8_WakeupInterval_xmin;
   uint8 U8_WakeTime_x100ms;
   uint8 U8_WakeOffset_x100ms;
   uint8 U8_POKDb;
  }Struct_PressureOnKeyConfig;
}RdcSt__Union_PressureOnKeyConfig;

typedef struct{
  uint32 U32_WsId;
  uint8 U8_Pressure;
  uint8 U8_Temperature;
  uint16 U16_ReceivedCounter;
}RdcSt__Struct_WSData;

typedef enum{
  RDCST__E_INITIAL = 0U
   ,  RDCST__E_AFTER_1_DAY = 1U
   ,  RDCST__E_AFTER_5_DAYS = 2U
}RdcSt__Enum_WakeupTimer;

#endif
