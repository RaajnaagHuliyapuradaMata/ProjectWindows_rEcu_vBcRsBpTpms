

#ifndef DEM_CFG_DTCID_H
#define DEM_CFG_DTCID_H

#include "Dem_Cfg_EventId.hpp"

#define DEM_CFG_EVCOMB_DISABLED       1u
#define DEM_CFG_EVCOMB_ONSTORAGE      2u
#define DEM_CFG_EVCOMB_ONRETRIEVAL    3u
#define DEM_CFG_EVCOMB            DEM_CFG_EVCOMB_DISABLED

#define DEM_DTCID_INVALID           0u
#define DEM_DTCID_COUNT             41u
#define DEM_DTCID_ARRAYLENGTH       (DEM_DTCID_COUNT+1u)

#define DemConf_DemDTCClass_DemDTC_CommunicationErrorWithBcm         1u
#define DemConf_DemDTCClass_DemDTC_CommunicationErrorWithAmp         2u
#define DemConf_DemDTCClass_DemDTC_CommunicationErrorWithDcmFL       3u
#define DemConf_DemDTCClass_DemDTC_CommunicationErrorWithDcmRL       4u
#define DemConf_DemDTCClass_DemDTC_CommunicationErrorWithScmFL       5u
#define DemConf_DemDTCClass_DemDTC_CanVehicleModeSignalMissing       6u
#define DemConf_DemDTCClass_DemDTC_CanBusoffError                    7u
#define DemConf_DemDTCClass_DemDTC_CanOffroadSignalMissing           8u
#define DemConf_DemDTCClass_DemDTC_CanAbsWheelPulseSignalMissing     9u
#define DemConf_DemDTCClass_DemDTC_NoQualifiedSensorSignals          10u
#define DemConf_DemDTCClass_DemDTC_DetectedTooManySensors            11u
#define DemConf_DemDTCClass_DemDTC_CanAtmosphericTemperatureSignalMissing  12u
#define DemConf_DemDTCClass_DemDTC_CanSpeedSignalMissing             13u
#define DemConf_DemDTCClass_DemDTC_CanWheelDirectionSignalMissing    14u
#define DemConf_DemDTCClass_DemDTC_CanClockSyncSignalMissing         15u
#define DemConf_DemDTCClass_DemDTC_FailedMemory                      16u
#define DemConf_DemDTCClass_DemDTC_NoVin                             17u
#define DemConf_DemDTCClass_DemDTC_BatteryVoltageLow                 18u
#define DemConf_DemDTCClass_DemDTC_BatteryVoltageHigh                19u
#define DemConf_DemDTCClass_DemDTC_NoEcuSerialNumber                 20u
#define DemConf_DemDTCClass_DemDTC_SensorLifeTimeCounterLowFL        21u
#define DemConf_DemDTCClass_DemDTC_SensorMissingFL                   22u
#define DemConf_DemDTCClass_DemDTC_SensorDefectFL                    23u
#define DemConf_DemDTCClass_DemDTC_SensorOvertempFL                  24u
#define DemConf_DemDTCClass_DemDTC_SensorLifeTimeCounterLowFR        25u
#define DemConf_DemDTCClass_DemDTC_SensorMissingFR                   26u
#define DemConf_DemDTCClass_DemDTC_SensorDefectFR                    27u
#define DemConf_DemDTCClass_DemDTC_SensorOvertempFR                  28u
#define DemConf_DemDTCClass_DemDTC_SensorLifeTimeCounterLowRR        29u
#define DemConf_DemDTCClass_DemDTC_SensorMissingRR                   30u
#define DemConf_DemDTCClass_DemDTC_SensorDefectRR                    31u
#define DemConf_DemDTCClass_DemDTC_SensorOvertempRR                  32u
#define DemConf_DemDTCClass_DemDTC_SensorLifeTimeCounterLowRL        33u
#define DemConf_DemDTCClass_DemDTC_SensorMissingRL                   34u
#define DemConf_DemDTCClass_DemDTC_SensorDefectRL                    35u
#define DemConf_DemDTCClass_DemDTC_SensorOvertempRL                  36u
#define DemConf_DemDTCClass_DemDTC_SensorDefectUnknownPosition       37u
#define DemConf_DemDTCClass_DemDTC_SensorMissingUnknownPosition      38u
#define DemConf_DemDTCClass_DemDTC_AutolocationFail                  39u
#define DemConf_DemDTCClass_DemDTC_TpmsNotFunctional                 40u
#define DemConf_DemDTCClass_DemDTC_EcuRfInterference                 41u

#define DEM_DTCGROUPID_INVALID           0u
#define DEM_DTCGROUPID_COUNT             1u
#define DEM_DTCGROUPID_ARRAYLENGTH       (DEM_DTCGROUPID_COUNT+1u)

// genInfo: for(EvCombination==OFF) the explicit mapping from dtcid to eventId is necessary, because an event may not be assigned to any DTC
#define DEM_MAP_EVENTID_DTCID   \
const Dem_DtcIdType Dem_MapEventIdToDtcId[DEM_EVENTID_ARRAYLENGTH] = \
{ \
   DEM_DTCID_INVALID \
   ,DemConf_DemDTCClass_DemDTC_AutolocationFail   \
   ,DemConf_DemDTCClass_DemDTC_CanAbsWheelPulseSignalMissing   \
   ,DemConf_DemDTCClass_DemDTC_CanAtmosphericTemperatureSignalMissing   \
   ,DemConf_DemDTCClass_DemDTC_CanBusoffError   \
   ,DemConf_DemDTCClass_DemDTC_CanClockSyncSignalMissing   \
   ,DemConf_DemDTCClass_DemDTC_CanOffroadSignalMissing   \
   ,DemConf_DemDTCClass_DemDTC_CanSpeedSignalMissing   \
   ,DemConf_DemDTCClass_DemDTC_CanVehicleModeSignalMissing   \
   ,DemConf_DemDTCClass_DemDTC_CanWheelDirectionSignalMissing   \
   ,DemConf_DemDTCClass_DemDTC_CommunicationErrorWithAmp   \
   ,DemConf_DemDTCClass_DemDTC_CommunicationErrorWithBcm   \
   ,DemConf_DemDTCClass_DemDTC_CommunicationErrorWithDcmFL   \
   ,DemConf_DemDTCClass_DemDTC_CommunicationErrorWithDcmRL   \
   ,DemConf_DemDTCClass_DemDTC_CommunicationErrorWithScmFL   \
   ,DemConf_DemDTCClass_DemDTC_DetectedTooManySensors   \
   ,DemConf_DemDTCClass_DemDTC_EcuRfInterference   \
   ,DemConf_DemDTCClass_DemDTC_NoQualifiedSensorSignals   \
   ,DemConf_DemDTCClass_DemDTC_SensorDefectFL   \
   ,DemConf_DemDTCClass_DemDTC_SensorDefectFR   \
   ,DemConf_DemDTCClass_DemDTC_SensorDefectRL   \
   ,DemConf_DemDTCClass_DemDTC_SensorDefectRR   \
   ,DemConf_DemDTCClass_DemDTC_SensorDefectUnknownPosition   \
   ,DemConf_DemDTCClass_DemDTC_SensorLifeTimeCounterLowFL   \
   ,DemConf_DemDTCClass_DemDTC_SensorLifeTimeCounterLowFR   \
   ,DemConf_DemDTCClass_DemDTC_SensorLifeTimeCounterLowRL   \
   ,DemConf_DemDTCClass_DemDTC_SensorLifeTimeCounterLowRR   \
   ,DemConf_DemDTCClass_DemDTC_SensorMissingFL   \
   ,DemConf_DemDTCClass_DemDTC_SensorMissingFR   \
   ,DemConf_DemDTCClass_DemDTC_SensorMissingRL   \
   ,DemConf_DemDTCClass_DemDTC_SensorMissingRR   \
   ,DemConf_DemDTCClass_DemDTC_SensorMissingUnknownPosition   \
   ,DemConf_DemDTCClass_DemDTC_SensorOvertempFL   \
   ,DemConf_DemDTCClass_DemDTC_SensorOvertempFR   \
   ,DemConf_DemDTCClass_DemDTC_SensorOvertempRL   \
   ,DemConf_DemDTCClass_DemDTC_SensorOvertempRR   \
   ,DemConf_DemDTCClass_DemDTC_TpmsNotFunctional   \
   ,DemConf_DemDTCClass_DemDTC_BatteryVoltageHigh   \
   ,DemConf_DemDTCClass_DemDTC_BatteryVoltageLow   \
   ,DemConf_DemDTCClass_DemDTC_FailedMemory   \
   ,DemConf_DemDTCClass_DemDTC_NoEcuSerialNumber   \
   ,DemConf_DemDTCClass_DemDTC_NoVin         \
};

#define DEM_MAP_DTCGROUPID_DTCID \
{ {0u,0u}\
 ,{DemConf_DemDTCClass_DemDTC_CommunicationErrorWithBcm , DemConf_DemDTCClass_DemDTC_EcuRfInterference}	\
}

#if(DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_DISABLED)

#define DEM_MAP_DTCID_EVENTID        \
const Dem_MapDtcIdToEventIdType  Dem_MapDtcIdToEventId[DEM_DTCID_ARRAYLENGTH] = \
{ \
   DEM_EVENTID_INVALID \
   ,DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithBcm  \
   ,DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithAmp  \
   ,DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithDcmFL  \
   ,DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithDcmRL  \
   ,DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithScmFL  \
   ,DemConf_DemEventParameter_DemEventParameter_CanVehicleModeSignalMissing  \
   ,DemConf_DemEventParameter_DemEventParameter_CanBusoffError  \
   ,DemConf_DemEventParameter_DemEventParameter_CanOffroadSignalMissing  \
   ,DemConf_DemEventParameter_DemEventParameter_CanAbsWheelPulseSignalMissing  \
   ,DemConf_DemEventParameter_DemEventParameter_NoQualifiedSensorSignals  \
   ,DemConf_DemEventParameter_DemEventParameter_DetectedTooManySensors  \
   ,DemConf_DemEventParameter_DemEventParameter_CanAtmosphericTemperatureSignalMissing  \
   ,DemConf_DemEventParameter_DemEventParameter_CanSpeedSignalMissing  \
   ,DemConf_DemEventParameter_DemEventParameter_CanWheelDirectionSignalMissing  \
   ,DemConf_DemEventParameter_DemEventParameter_CanClockSyncSignalMissing  \
   ,DemConf_DemEventParameter_Event_FailedMemory  \
   ,DemConf_DemEventParameter_Event_NoVin  \
   ,DemConf_DemEventParameter_Event_BatteryVoltageLow  \
   ,DemConf_DemEventParameter_Event_BatteryVoltageHigh  \
   ,DemConf_DemEventParameter_Event_NoEcuSerialNumber  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFL  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorMissingFL  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorDefectFL  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorOvertempFL  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFR  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorMissingFR  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorDefectFR  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorOvertempFR  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRR  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorMissingRR  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorDefectRR  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorOvertempRR  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRL  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorMissingRL  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorDefectRL  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorOvertempRL  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorDefectUnknownPosition  \
   ,DemConf_DemEventParameter_DemEventParameter_SensorMissingUnknownPosition  \
   ,DemConf_DemEventParameter_DemEventParameter_AutolocationFail  \
   ,DemConf_DemEventParameter_DemEventParameter_TpmsNotFunctional  \
   ,DemConf_DemEventParameter_DemEventParameter_EcuRfInterference  \
};

#else

#define DEM_MAP_DTCID_EVENTID        \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithBcm[] = { \
   DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithBcm \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithAmp[] = { \
   DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithAmp \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithDcmFL[] = { \
   DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithDcmFL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithDcmRL[] = { \
   DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithDcmRL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithScmFL[] = { \
   DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithScmFL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CanVehicleModeSignalMissing[] = { \
   DemConf_DemEventParameter_DemEventParameter_CanVehicleModeSignalMissing \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CanBusoffError[] = { \
   DemConf_DemEventParameter_DemEventParameter_CanBusoffError \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CanOffroadSignalMissing[] = { \
   DemConf_DemEventParameter_DemEventParameter_CanOffroadSignalMissing \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CanAbsWheelPulseSignalMissing[] = { \
   DemConf_DemEventParameter_DemEventParameter_CanAbsWheelPulseSignalMissing \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_NoQualifiedSensorSignals[] = { \
   DemConf_DemEventParameter_DemEventParameter_NoQualifiedSensorSignals \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_DetectedTooManySensors[] = { \
   DemConf_DemEventParameter_DemEventParameter_DetectedTooManySensors \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CanAtmosphericTemperatureSignalMissing[] = { \
   DemConf_DemEventParameter_DemEventParameter_CanAtmosphericTemperatureSignalMissing \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CanSpeedSignalMissing[] = { \
   DemConf_DemEventParameter_DemEventParameter_CanSpeedSignalMissing \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CanWheelDirectionSignalMissing[] = { \
   DemConf_DemEventParameter_DemEventParameter_CanWheelDirectionSignalMissing \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_CanClockSyncSignalMissing[] = { \
   DemConf_DemEventParameter_DemEventParameter_CanClockSyncSignalMissing \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_FailedMemory[] = { \
   DemConf_DemEventParameter_Event_FailedMemory \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_NoVin[] = { \
   DemConf_DemEventParameter_Event_NoVin \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_BatteryVoltageLow[] = { \
   DemConf_DemEventParameter_Event_BatteryVoltageLow \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_BatteryVoltageHigh[] = { \
   DemConf_DemEventParameter_Event_BatteryVoltageHigh \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_NoEcuSerialNumber[] = { \
   DemConf_DemEventParameter_Event_NoEcuSerialNumber \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowFL[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorMissingFL[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorMissingFL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorDefectFL[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorDefectFL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorOvertempFL[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorOvertempFL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowFR[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFR \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorMissingFR[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorMissingFR \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorDefectFR[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorDefectFR \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorOvertempFR[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorOvertempFR \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowRR[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRR \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorMissingRR[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorMissingRR \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorDefectRR[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorDefectRR \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorOvertempRR[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorOvertempRR \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowRL[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorMissingRL[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorMissingRL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorDefectRL[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorDefectRL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorOvertempRL[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorOvertempRL \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorDefectUnknownPosition[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorDefectUnknownPosition \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_SensorMissingUnknownPosition[] = { \
   DemConf_DemEventParameter_DemEventParameter_SensorMissingUnknownPosition \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_AutolocationFail[] = { \
   DemConf_DemEventParameter_DemEventParameter_AutolocationFail \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_TpmsNotFunctional[] = { \
   DemConf_DemEventParameter_DemEventParameter_TpmsNotFunctional \
}; \
 \
 \
static const  Dem_EventIdType  Dem_MapDtcIdToEventId_DemDTC_EcuRfInterference[] = { \
   DemConf_DemEventParameter_DemEventParameter_EcuRfInterference \
}; \
 \
 \
 \
const Dem_MapDtcIdToEventIdType  Dem_MapDtcIdToEventId[DEM_DTCID_ARRAYLENGTH] = \
{ \
   { \
      NULL_PTR, \
      0u \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithBcm[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithBcm)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithBcm[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithAmp[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithAmp)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithAmp[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithDcmFL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithDcmFL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithDcmFL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithDcmRL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithDcmRL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithDcmRL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithScmFL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithScmFL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CommunicationErrorWithScmFL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CanVehicleModeSignalMissing[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanVehicleModeSignalMissing)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanVehicleModeSignalMissing[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CanBusoffError[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanBusoffError)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanBusoffError[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CanOffroadSignalMissing[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanOffroadSignalMissing)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanOffroadSignalMissing[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CanAbsWheelPulseSignalMissing[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanAbsWheelPulseSignalMissing)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanAbsWheelPulseSignalMissing[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_NoQualifiedSensorSignals[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_NoQualifiedSensorSignals)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_NoQualifiedSensorSignals[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_DetectedTooManySensors[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DetectedTooManySensors)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_DetectedTooManySensors[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CanAtmosphericTemperatureSignalMissing[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanAtmosphericTemperatureSignalMissing)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanAtmosphericTemperatureSignalMissing[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CanSpeedSignalMissing[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanSpeedSignalMissing)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanSpeedSignalMissing[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CanWheelDirectionSignalMissing[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanWheelDirectionSignalMissing)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanWheelDirectionSignalMissing[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_CanClockSyncSignalMissing[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanClockSyncSignalMissing)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_CanClockSyncSignalMissing[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_FailedMemory[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_FailedMemory)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_FailedMemory[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_NoVin[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_NoVin)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_NoVin[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_BatteryVoltageLow[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_BatteryVoltageLow)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_BatteryVoltageLow[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_BatteryVoltageHigh[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_BatteryVoltageHigh)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_BatteryVoltageHigh[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_NoEcuSerialNumber[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_NoEcuSerialNumber)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_NoEcuSerialNumber[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowFL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowFL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowFL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorMissingFL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingFL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingFL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorDefectFL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectFL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectFL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorOvertempFL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorOvertempFL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorOvertempFL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowFR[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowFR)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowFR[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorMissingFR[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingFR)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingFR[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorDefectFR[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectFR)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectFR[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorOvertempFR[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorOvertempFR)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorOvertempFR[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowRR[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowRR)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowRR[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorMissingRR[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingRR)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingRR[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorDefectRR[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectRR)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectRR[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorOvertempRR[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorOvertempRR)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorOvertempRR[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowRL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowRL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorLifeTimeCounterLowRL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorMissingRL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingRL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingRL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorDefectRL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectRL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectRL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorOvertempRL[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorOvertempRL)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorOvertempRL[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorDefectUnknownPosition[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectUnknownPosition)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorDefectUnknownPosition[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_SensorMissingUnknownPosition[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingUnknownPosition)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_SensorMissingUnknownPosition[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_AutolocationFail[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_AutolocationFail)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_AutolocationFail[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_TpmsNotFunctional[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_TpmsNotFunctional)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_TpmsNotFunctional[0])) \
   }\
   ,{ \
      &Dem_MapDtcIdToEventId_DemDTC_EcuRfInterference[0], \
      (uint16)(DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_EcuRfInterference)/DEM_SIZEOF_VAR(Dem_MapDtcIdToEventId_DemDTC_EcuRfInterference[0])) \
   }\
};

#endif

#endif

