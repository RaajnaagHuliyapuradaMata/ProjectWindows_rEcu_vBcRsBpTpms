#ifndef DEM_CFG_STORAGECONDITION_H
#define DEM_CFG_STORAGECONDITION_H

#define DEM_CFG_STORAGECONDITION_ON    STD_ON
#define DEM_CFG_STORAGECONDITION_OFF   STD_OFF
#define DEM_CFG_STORAGECONDITION       DEM_CFG_STORAGECONDITION_OFF
#define DEM_STORAGECONDITION_COUNT         0u
#define DEM_STORAGECONDITION_ARRAYLENGTH   (DEM_STORAGECONDITION_COUNT)

#if(DEM_STORAGECONDITION_ARRAYLENGTH <= 8) || (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_OFF)
typedef uint8 Dem_StoCoList;
#elif(DEM_STORAGECONDITION_ARRAYLENGTH <= 16)
typedef uint16 Dem_StoCoList;
#elif(DEM_STORAGECONDITION_ARRAYLENGTH <= 32)
typedef uint32 Dem_StoCoList;
#else
#error DEM currently only supports up to 32 StorageConditions
#endif

#if(DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
#define DEM_STOCO_DemEventParameter_AutolocationFail             (0u)
#define DEM_STOCO_DemEventParameter_CanAbsWheelPulseSignalMissing             (0u)
#define DEM_STOCO_DemEventParameter_CanAtmosphericTemperatureSignalMissing             (0u)
#define DEM_STOCO_DemEventParameter_CanBusoffError             (0u)
#define DEM_STOCO_DemEventParameter_CanClockSyncSignalMissing             (0u)
#define DEM_STOCO_DemEventParameter_CanOffroadSignalMissing             (0u)
#define DEM_STOCO_DemEventParameter_CanSpeedSignalMissing             (0u)
#define DEM_STOCO_DemEventParameter_CanVehicleModeSignalMissing             (0u)
#define DEM_STOCO_DemEventParameter_CanWheelDirectionSignalMissing             (0u)
#define DEM_STOCO_DemEventParameter_CommunicationErrorWithAmp             (0u)
#define DEM_STOCO_DemEventParameter_CommunicationErrorWithBcm             (0u)
#define DEM_STOCO_DemEventParameter_CommunicationErrorWithDcmFL             (0u)
#define DEM_STOCO_DemEventParameter_CommunicationErrorWithDcmRL             (0u)
#define DEM_STOCO_DemEventParameter_CommunicationErrorWithScmFL             (0u)
#define DEM_STOCO_DemEventParameter_DetectedTooManySensors             (0u)
#define DEM_STOCO_DemEventParameter_EcuRfInterference             (0u)
#define DEM_STOCO_DemEventParameter_NoQualifiedSensorSignals             (0u)
#define DEM_STOCO_DemEventParameter_SensorDefectFL             (0u)
#define DEM_STOCO_DemEventParameter_SensorDefectFR             (0u)
#define DEM_STOCO_DemEventParameter_SensorDefectRL             (0u)
#define DEM_STOCO_DemEventParameter_SensorDefectRR             (0u)
#define DEM_STOCO_DemEventParameter_SensorDefectUnknownPosition             (0u)
#define DEM_STOCO_DemEventParameter_SensorLifeTimeCounterLowFL             (0u)
#define DEM_STOCO_DemEventParameter_SensorLifeTimeCounterLowFR             (0u)
#define DEM_STOCO_DemEventParameter_SensorLifeTimeCounterLowRL             (0u)
#define DEM_STOCO_DemEventParameter_SensorLifeTimeCounterLowRR             (0u)
#define DEM_STOCO_DemEventParameter_SensorMissingFL             (0u)
#define DEM_STOCO_DemEventParameter_SensorMissingFR             (0u)
#define DEM_STOCO_DemEventParameter_SensorMissingRL             (0u)
#define DEM_STOCO_DemEventParameter_SensorMissingRR             (0u)
#define DEM_STOCO_DemEventParameter_SensorMissingUnknownPosition             (0u)
#define DEM_STOCO_DemEventParameter_SensorOvertempFL             (0u)
#define DEM_STOCO_DemEventParameter_SensorOvertempFR             (0u)
#define DEM_STOCO_DemEventParameter_SensorOvertempRL             (0u)
#define DEM_STOCO_DemEventParameter_SensorOvertempRR             (0u)
#define DEM_STOCO_DemEventParameter_TpmsNotFunctional             (0u)
#define DEM_STOCO_Event_BatteryVoltageHigh                  (0u)
#define DEM_STOCO_Event_BatteryVoltageLow                   (0u)
#define DEM_STOCO_Event_FailedMemory                        (0u)
#define DEM_STOCO_Event_NoEcuSerialNumber                   (0u)
#define DEM_STOCO_Event_NoVin                               (0u)
#define DEM_CFG_STOCO_INITIALSTATE    (0u)

#define DEM_CFG_STOCO_PARAMS { \
   { \
   }\
}

#endif

#endif

