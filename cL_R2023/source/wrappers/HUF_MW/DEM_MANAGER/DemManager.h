

#ifndef DEM_MANAGER_H
#define DEM_MANAGER_H

#include "DemManagerX.h"
#include "Rte_Dem_Type.h"

#define DemConf_DemEventParameter_Event_ModuleNotProvisioned                                    DemConf_DemEventParameter_EventParameter_DTC_0x9CC055_Event
#define DemConf_DemEventParameter_Event_FailedMemory                                            DemConf_DemEventParameter_EventParameter_DTC_0x500042_Event
#define DemConf_DemEventParameter_Event_BatteryVoltageLow                                       DemConf_DemEventParameter_EventParameter_DTC_0x5000a2_Event
#define DemConf_DemEventParameter_Event_BatteryVoltageHigh                                      DemConf_DemEventParameter_EventParameter_DTC_0x5000a3_Event
//#define DemConf_DemEventParameter_EventParameter_DTC_0xd60188_Event

#define DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFL                  DemConf_DemEventParameter_EventParameter_DTC_0x560116_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFR                  DemConf_DemEventParameter_EventParameter_DTC_0x560216_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRR                  DemConf_DemEventParameter_EventParameter_DTC_0x560316_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRL                  DemConf_DemEventParameter_EventParameter_DTC_0x560416_Event

#define DemConf_DemEventParameter_DemEventParameter_SensorDefectFL                              DemConf_DemEventParameter_EventParameter_DTC_0x560149_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectFR                              DemConf_DemEventParameter_EventParameter_DTC_0x560249_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectRR                              DemConf_DemEventParameter_EventParameter_DTC_0x560349_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectRL                              DemConf_DemEventParameter_EventParameter_DTC_0x560449_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectUnknownPosition                 DemConf_DemEventParameter_EventParameter_DTC_0x560504_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingFL                             DemConf_DemEventParameter_EventParameter_DTC_0x560131_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingFR                             DemConf_DemEventParameter_EventParameter_DTC_0x560231_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingRR                             DemConf_DemEventParameter_EventParameter_DTC_0x560331_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingRL                             DemConf_DemEventParameter_EventParameter_DTC_0x560431_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingUnknownPosition                DemConf_DemEventParameter_EventParameter_DTC_0x560531_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorOvertempFL                            DemConf_DemEventParameter_EventParameter_DTC_0x56014b_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorOvertempFR                            DemConf_DemEventParameter_EventParameter_DTC_0x56024b_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorOvertempRR                            DemConf_DemEventParameter_EventParameter_DTC_0x56034b_Event
#define DemConf_DemEventParameter_DemEventParameter_SensorOvertempRL                            DemConf_DemEventParameter_EventParameter_DTC_0x56044b_Event

#define DemConf_DemEventParameter_DemEventParameter_DetectedTooManySensors                      DemConf_DemEventParameter_EventParameter_DTC_0xd60429_Event //new U1EF229=0xDEF229
#define DemConf_DemEventParameter_DemEventParameter_NoQualifiedSensorSignals                    DemConf_DemEventParameter_EventParameter_DTC_0xd60529_Event //new U1EF329=0xDEF329
#define DemConf_DemEventParameter_DemEventParameter_AutolocationFail                            DemConf_DemEventParameter_EventParameter_DTC_0x56064a_Event
#define DemConf_DemEventParameter_DemEventParameter_TpmsNotFunctional                           DemConf_DemEventParameter_EventParameter_DTC_0x560793_Event
#define DemConf_DemEventParameter_DemEventParameter_EcuRfInterference                           DemConf_DemEventParameter_EventParameter_DTC_0x560929_Event //LMC OIL#151

#define DemConf_DemEventParameter_DemEventParameter_CanClockSyncSignalMissing                   DemConf_DemEventParameter_EventParameter_DTC_0xd60929_Event //new U014729=0xC14729
#define DemConf_DemEventParameter_DemEventParameter_VehicleModeSignalMissing                    DemConf_DemEventParameter_EventParameter_DTC_0xd60129_Event //new U014129=0xC14129
#define DemConf_DemEventParameter_DemEventParameter_CanAbsWheelPulseSignalMissing               DemConf_DemEventParameter_EventParameter_DTC_0xd60329_Event //new U1EF129=0xDEF129
#define DemConf_DemEventParameter_DemEventParameter_CanAtmosphericTemperatureSignalMissing      DemConf_DemEventParameter_EventParameter_DTC_0xd60629_Event //new U1EF429=0xDEF429
#define DemConf_DemEventParameter_DemEventParameter_CanSpeedSignalMissing                       DemConf_DemEventParameter_EventParameter_DTC_0xd60729_Event //new U1EF529=0xDEF529
#define DemConf_DemEventParameter_DemEventParameter_CanWheelDirectionSignalMissing              DemConf_DemEventParameter_EventParameter_DTC_0xd60829_Event //new U1EF629=0xDEF629

#define DEMMGR__BCM_PERIPHERAL_MASTER_CLOCK_TIMEOUT_MS              ((uint32) 1000U)
#define DEMMGR__ESP_WHEEL_PULSE_STAMPED_TIMEOUT_MS                  ((uint32) 400U)
#define DEMMGR__ESP_WSPEED_FRONT_REAR_BODY_LCAN_TIMEOUT_MS          ((uint32) 3000U)
#define DEMMGR__TMM_STATUS_BODY_LCAN_TIMEOUT_MS                     ((uint32) 30000U)
#define DEMMGR__VEH_STS_BODY_LCAN_TIMEOUT_MS                        ((uint32) 3000U)
#define DEMMGR__VMS_STS_REQ_BODY_LCAN_TIMEOUT_MS                    ((uint32) 30000U)

#define DEMMGR__TASK_CYCLICITY                                      ((uint32) 200U)
#define DEMMGR__TIMEOUT_COUNTER(timeout_ms)                         ((uint16) ((timeout_ms) / DEMMGR__TASK_CYCLICITY))

#define DEMMGR__BCM_PERIPHERAL_MASTER_CLOCK_TIMEOUT                 ((uint16) DEMMGR__TIMEOUT_COUNTER(DEMMGR__BCM_PERIPHERAL_MASTER_CLOCK_TIMEOUT_MS))
#define DEMMGR__ESP_WHEEL_PULSE_STAMPED_TIMEOUT                     ((uint16) DEMMGR__TIMEOUT_COUNTER(DEMMGR__ESP_WHEEL_PULSE_STAMPED_TIMEOUT_MS))
#define DEMMGR__ESP_WSPEED_FRONT_REAR_BODY_LCAN_TIMEOUT             ((uint16) DEMMGR__TIMEOUT_COUNTER(DEMMGR__ESP_WSPEED_FRONT_REAR_BODY_LCAN_TIMEOUT_MS))
#define DEMMGR__TMM_STATUS_BODY_LCAN_TIMEOUT                        ((uint16) DEMMGR__TIMEOUT_COUNTER(DEMMGR__TMM_STATUS_BODY_LCAN_TIMEOUT_MS))
#define DEMMGR__VEH_STS_BODY_LCAN_TIMEOUT                           ((uint16) DEMMGR__TIMEOUT_COUNTER(DEMMGR__VEH_STS_BODY_LCAN_TIMEOUT_MS))
#define DEMMGR__VMS_STS_REQ_BODY_LCAN_TIMEOUT                       ((uint16) DEMMGR__TIMEOUT_COUNTER(DEMMGR__VMS_STS_REQ_BODY_LCAN_TIMEOUT_MS))

#define DEMMGR__MISSING_RX_COUNTER_INIT                             ((uint16) 0U)

#define DEMMGR__ESP_WHEEL_PULSE_STAMPED_MIN_SPEED                   ((uint16) 0U)

#define cECU_UBAT_TIMEOUT 15

#define cDEMMGR_DTC_FIFO_SIZE 20
#define cDEMMGR_DTC_FIFO_EMPTY 0xffu
typedef struct{
  Dem_EventIdType ucEvent;
  Dem_EventStatusType ucStatus;
}sDtcEventFifoBuffer;

static void DemMGR_CheckEcuIdentificationAndApplMemory(void);
// static void DemMGR_CheckModuleProvisioning(void); // moved to DemManagerX.h
static boolean DemMGR__CheckSignalTimeout(DemMGR_Enum_RxMessages EN_RxMessage);
static void DemMGR__BcmPeripheralMasterClockMonitor(void);
static void DemMGR__EspWheelPulseStampedMonitor(void);
static void DemMGR__EspWspeedFrontRearBodyDirectionLCANMonitor(void);
static void DemMGR__EspWspeedFrontRearBodySpeedLCANMonitor(void);
static void DemMGR__TmmStatusBodyLCANMonitor(void);
static void DemMGR__VehStsBodyLCANMonitor(void);

static void DEMMGR_FifoPut(Dem_EventIdType ucDtc, Dem_EventStatusType ucStatus);
static void DEMMGR_FiFoGet(Dem_EventIdType* ucError, Dem_EventStatusType* ucStatus);
#endif
