

#ifndef DEM_CFG_ENABLECONDITION_H
#define DEM_CFG_ENABLECONDITION_H

#include "Std_Types.h"

#define DEM_CFG_ENABLECONDITION_ON    STD_ON
#define DEM_CFG_ENABLECONDITION_OFF   STD_OFF
#define DEM_CFG_ENABLECONDITION       DEM_CFG_ENABLECONDITION_OFF

#define DEM_ENABLECONDITION_COUNT         0u
#define DEM_ENABLECONDITION_ARRAYLENGTH   (DEM_ENABLECONDITION_COUNT)

#if (DEM_ENABLECONDITION_ARRAYLENGTH <= 8) \
	|| (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_OFF)
typedef uint8 Dem_EnCoList;
#elif (DEM_ENABLECONDITION_ARRAYLENGTH <= 16)
typedef uint16 Dem_EnCoList;
#elif (DEM_ENABLECONDITION_ARRAYLENGTH <= 32)
typedef uint32 Dem_EnCoList;
#else
#error DEM currently only supports up to 32 EnableConditions
#endif

#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)

#define DEM_ENCO_DemEventParameter_AutolocationFail  (0u)
#define DEM_ENCO_DemEventParameter_CanAbsWheelPulseSignalMissing  (0u)
#define DEM_ENCO_DemEventParameter_CanAtmosphericTemperatureSignalMissing  (0u)
#define DEM_ENCO_DemEventParameter_CanBusoffError  (0u)
#define DEM_ENCO_DemEventParameter_CanClockSyncSignalMissing  (0u)
#define DEM_ENCO_DemEventParameter_CanOffroadSignalMissing  (0u)
#define DEM_ENCO_DemEventParameter_CanSpeedSignalMissing  (0u)
#define DEM_ENCO_DemEventParameter_CanVehicleModeSignalMissing  (0u)
#define DEM_ENCO_DemEventParameter_CanWheelDirectionSignalMissing  (0u)
#define DEM_ENCO_DemEventParameter_CommunicationErrorWithAmp  (0u)
#define DEM_ENCO_DemEventParameter_CommunicationErrorWithBcm  (0u)
#define DEM_ENCO_DemEventParameter_CommunicationErrorWithDcmFL  (0u)
#define DEM_ENCO_DemEventParameter_CommunicationErrorWithDcmRL  (0u)
#define DEM_ENCO_DemEventParameter_CommunicationErrorWithScmFL  (0u)
#define DEM_ENCO_DemEventParameter_DetectedTooManySensors  (0u)
#define DEM_ENCO_DemEventParameter_EcuRfInterference  (0u)
#define DEM_ENCO_DemEventParameter_NoQualifiedSensorSignals  (0u)
#define DEM_ENCO_DemEventParameter_SensorDefectFL  (0u)
#define DEM_ENCO_DemEventParameter_SensorDefectFR  (0u)
#define DEM_ENCO_DemEventParameter_SensorDefectRL  (0u)
#define DEM_ENCO_DemEventParameter_SensorDefectRR  (0u)
#define DEM_ENCO_DemEventParameter_SensorDefectUnknownPosition  (0u)
#define DEM_ENCO_DemEventParameter_SensorLifeTimeCounterLowFL  (0u)
#define DEM_ENCO_DemEventParameter_SensorLifeTimeCounterLowFR  (0u)
#define DEM_ENCO_DemEventParameter_SensorLifeTimeCounterLowRL  (0u)
#define DEM_ENCO_DemEventParameter_SensorLifeTimeCounterLowRR  (0u)
#define DEM_ENCO_DemEventParameter_SensorMissingFL  (0u)
#define DEM_ENCO_DemEventParameter_SensorMissingFR  (0u)
#define DEM_ENCO_DemEventParameter_SensorMissingRL  (0u)
#define DEM_ENCO_DemEventParameter_SensorMissingRR  (0u)
#define DEM_ENCO_DemEventParameter_SensorMissingUnknownPosition  (0u)
#define DEM_ENCO_DemEventParameter_SensorOvertempFL  (0u)
#define DEM_ENCO_DemEventParameter_SensorOvertempFR  (0u)
#define DEM_ENCO_DemEventParameter_SensorOvertempRL  (0u)
#define DEM_ENCO_DemEventParameter_SensorOvertempRR  (0u)
#define DEM_ENCO_DemEventParameter_TpmsNotFunctional  (0u)
#define DEM_ENCO_Event_BatteryVoltageHigh       (0u)
#define DEM_ENCO_Event_BatteryVoltageLow        (0u)
#define DEM_ENCO_Event_FailedMemory             (0u)
#define DEM_ENCO_Event_NoEcuSerialNumber        (0u)
#define DEM_ENCO_Event_NoVin                    (0u)

#define DEM_CFG_ENCO_INITIALSTATE    (   0u \
                                      )

#endif

#endif
