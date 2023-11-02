#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_EnableCondition.hpp                                       */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_ENABLECONDITION_ON    STD_ON
#define DEM_CFG_ENABLECONDITION_OFF   STD_OFF
#define DEM_CFG_ENABLECONDITION       DEM_CFG_ENABLECONDITION_OFF
#define DEM_ENABLECONDITION_COUNT         0u
#define DEM_ENABLECONDITION_ARRAYLENGTH   (DEM_ENABLECONDITION_COUNT)

typedef uint8 Dem_EnCoList;

#if(DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
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
#define DEM_CFG_ENCO_INITIALSTATE               (0u)
#endif

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

