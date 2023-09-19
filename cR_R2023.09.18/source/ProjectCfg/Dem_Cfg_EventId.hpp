

#ifndef DEM_CFG_EVENTID_H
#define DEM_CFG_EVENTID_H

#define DEM_EVENTID_INVALID                                          0u
#define DEM_EVENTID_COUNT         41u
#define DEM_EVENTID_ARRAYLENGTH   (DEM_EVENTID_COUNT+1u)

#define DemConf_DemEventParameter_DemEventParameter_AutolocationFail  1u
#define DemConf_DemEventParameter_DemEventParameter_CanAbsWheelPulseSignalMissing  2u
#define DemConf_DemEventParameter_DemEventParameter_CanAtmosphericTemperatureSignalMissing  3u
#define DemConf_DemEventParameter_DemEventParameter_CanBusoffError   4u
#define DemConf_DemEventParameter_DemEventParameter_CanClockSyncSignalMissing  5u
#define DemConf_DemEventParameter_DemEventParameter_CanOffroadSignalMissing  6u
#define DemConf_DemEventParameter_DemEventParameter_CanSpeedSignalMissing  7u
#define DemConf_DemEventParameter_DemEventParameter_CanVehicleModeSignalMissing  8u
#define DemConf_DemEventParameter_DemEventParameter_CanWheelDirectionSignalMissing  9u
#define DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithAmp  10u
#define DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithBcm  11u
#define DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithDcmFL  12u
#define DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithDcmRL  13u
#define DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithScmFL  14u
#define DemConf_DemEventParameter_DemEventParameter_DetectedTooManySensors  15u
#define DemConf_DemEventParameter_DemEventParameter_EcuRfInterference  16u
#define DemConf_DemEventParameter_DemEventParameter_NoQualifiedSensorSignals  17u
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectFL   18u
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectFR   19u
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectRL   20u
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectRR   21u
#define DemConf_DemEventParameter_DemEventParameter_SensorDefectUnknownPosition  22u
#define DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFL  23u
#define DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFR  24u
#define DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRL  25u
#define DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRR  26u
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingFL  27u
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingFR  28u
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingRL  29u
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingRR  30u
#define DemConf_DemEventParameter_DemEventParameter_SensorMissingUnknownPosition  31u
#define DemConf_DemEventParameter_DemEventParameter_SensorOvertempFL  32u
#define DemConf_DemEventParameter_DemEventParameter_SensorOvertempFR  33u
#define DemConf_DemEventParameter_DemEventParameter_SensorOvertempRL  34u
#define DemConf_DemEventParameter_DemEventParameter_SensorOvertempRR  35u
#define DemConf_DemEventParameter_DemEventParameter_TpmsNotFunctional  36u
#define DemConf_DemEventParameter_Event_BatteryVoltageHigh           37u
#define DemConf_DemEventParameter_Event_BatteryVoltageLow            38u
#define DemConf_DemEventParameter_Event_FailedMemory                 39u
#define DemConf_DemEventParameter_Event_NoEcuSerialNumber            40u
#define DemConf_DemEventParameter_Event_NoVin                        41u

#endif

