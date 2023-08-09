

#ifndef RDC_STANDSTILL_H
#define RDC_STANDSTILL_H

#include "RdcStandstillX.h"

#define RDCST__PACKAGE_ID_STANDSTILL                                ((uint8) 0x90U)
#define RDCST__PACKAGE_ID_AK_STD                                    ((uint8) 0x00U)
#define RDCST__PACKAGE_ID_STATUS                                    ((uint8) 0x83U)
#define RDCST__PACKAGE_ID_STATUS_LEARN                              ((uint8) 0xA3U)
#define RDCST__PACKAGE_ID_ROT_DATA                                  ((uint8) 0xE7U)

#ifdef DEBUG_FAST_SHUTDOWN
#define RDCST__SYNC_PERIOD_DURATION_MINS                            ((uint32) 1U)
#else
#define RDCST__SYNC_PERIOD_DURATION_MINS                            ((uint32) 10U)
#endif
#define RDCST__SYNC_PERIOD_DURATION_MS                              ((uint32) (RDCST__SYNC_PERIOD_DURATION_MINS * 60U * 1000U))

#define RDCST__PRESSURE_ON_KEY_ENABLED_INIT                         ((uint8) 1U)
#define RDCST__WAKEUP_INTERVAL_INIT_XMIN                            ((uint8) 5U)
#define RDCST__WAKE_TIME_INIT_X100MS                                ((uint8) 120U) //70U)  RST Debug XXX: increase this to 12 seconds
#define RDCST__WAKE_OFFSET_INIT_X100MS                              ((uint8) 60U) //35U)   RST Debug XXX: set to 6 seconds (middle of window)
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

/*!************************************************************************************************
 * \brief Defines used to for NvM communication.
 *        The _GLOBAL_ values are absolute block numbers in NVM CAT1..CAT10 memory
 *************************************************************************************************/
#define RDCST__DATA_EXISTENCE_TRUE                                  ((uint8) 0xAAU) //Pressures received during standstill and saved after 21 days - read them on next startup
#define RDCST__DATA_EXISTENCE_FALSE                                 ((uint8) 0x55U) //Only the pressures at ignition off are in NVM - don't read from NVM on next startup
#define RDCST__GLOBAL_INDEX_WS_POS                                  ((uint8) 30U)
#define RDCST__GLOBAL_INDEX_PRESSURES                               ((uint8) 67U) //Block number with pressure FL.FR.RL.RR
#define RDCST__GLOBAL_INDEX_TEMPERATURES                            ((uint8) 68U) //Block number with temperature FL.FR.RL.RR

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
  } Struct_PressureOnKeyConfig;
} RdcSt__Union_PressureOnKeyConfig;

typedef struct
{
  uint32 U32_WsId;
  uint8 U8_Pressure;
  uint8 U8_Temperature;
  uint16 U16_ReceivedCounter;
} RdcSt__Struct_WSData;

typedef enum
{
  RDCST__E_INITIAL = 0U,
  RDCST__E_AFTER_1_DAY = 1U,
  RDCST__E_AFTER_5_DAYS = 2U
} RdcSt__Enum_WakeupTimer;

static void RdcSt__UpdateSyncPeriod(void);

//static boolean RdcSt__FourSensorsSynchronized(void);

static void RdcSt__UpdateMonitoringStatus(void);

static void RdcSt__UpdateWakeupTimer(void);

static boolean RdcSt__AreTimersExpiringSoon(void);

static void RdcSt__CopyPressAndTempToNvmRamBlock(uint8 ucDataExistence);

static void RdcSt__ReadPressAndTempFromBswNvm(void);

static void RdcSt__ReadPressureOnKeyConfig(void);

static boolean RdcSt__DataExistsInNvm(void);

static void Rdc__ConvertLatestReceptionToEpochTime(uint8 *PU8_TimeAndDateString);

static void RdcSt__CopyPressureOnKeyStatusToNvmRamBlock(void);

//static void RdcSt__ReadAndSortIDs(void);

#endif
