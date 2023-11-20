#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_DtcId.hpp                                                 */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Dem_Cfg_EventId.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_EVCOMB_DISABLED                                               1u
#define DEM_CFG_EVCOMB_ONSTORAGE                                              2u
#define DEM_CFG_EVCOMB_ONRETRIEVAL                                            3u
#define DEM_CFG_EVCOMB                                   DEM_CFG_EVCOMB_DISABLED

#define DEM_DTCID_INVALID                                                     0u
#define DEM_DTCID_COUNT                                                      41u
#define DEM_DTCID_ARRAYLENGTH                               (DEM_DTCID_COUNT+1u)

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

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

