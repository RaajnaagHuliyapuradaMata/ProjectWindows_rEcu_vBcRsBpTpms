#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_Events.hpp                                                */
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
#define DEM_CFG_EVTDISABLESTATUSUPDATE_OFF  STD_OFF
#define DEM_CFG_EVTDISABLESTATUSUPDATE_ON   STD_ON
#define DEM_CFG_EVTDISABLESTATUSUPDATE  DEM_CFG_EVTDISABLESTATUSUPDATE_OFF

#define DEM_CFG_TRIGGERFIMREPORTS_OFF  STD_OFF
#define DEM_CFG_TRIGGERFIMREPORTS_ON   STD_ON
#define DEM_CFG_TRIGGERFIMREPORTS  DEM_CFG_TRIGGERFIMREPORTS_ON

#define DEM_CFG_FIM_OFF STD_OFF
#define DEM_CFG_FIM_ON  STD_ON
#define DEM_CFG_FIM_USED DEM_CFG_FIM_ON

#define DEM_CFG_TRIGGERDLTREPORTS_OFF  STD_OFF
#define DEM_CFG_TRIGGERDLTREPORTS_ON   STD_ON
#define DEM_CFG_TRIGGERDLTREPORTS  DEM_CFG_TRIGGERDLTREPORTS_OFF

#define DEM_CFG_ALLOW_HISTORY_ON   STD_ON
#define DEM_CFG_ALLOW_HISTORY_OFF  STD_OFF
#define DEM_CFG_ALLOW_HISTORY  DEM_CFG_ALLOW_HISTORY_OFF

#define DEM_CFG_LOCK_ALLFAILUREINFO_ON   STD_ON
#define DEM_CFG_LOCK_ALLFAILUREINFO_OFF  STD_OFF
#define DEM_CFG_LOCK_ALLFAILUREINFO  DEM_CFG_LOCK_ALLFAILUREINFO_OFF

#define DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON   STD_ON
#define DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_OFF  STD_OFF
#define DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD  DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_OFF

#define DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED   FALSE

#define DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION_OFF  STD_OFF
#define DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION_ON   STD_ON

#if(defined DEM_SETEVENTSTATUSCALLNOTIFICATION)
#define DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION  DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION_ON
#else
#define DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION  DEM_CFG_SETEVENTSTATUSCALLNOTIFICATION_OFF
#endif

#define DEM_CFG_SETEVENTSTATUSALLOWEDCALLBACK_OFF  STD_OFF
#define DEM_CFG_SETEVENTSTATUSALLOWEDCALLBACK_ON   STD_ON
#define DEM_CFG_SETEVENTSTATUSALLOWEDCALLBACK  DEM_CFG_SETEVENTSTATUSALLOWEDCALLBACK_OFF

#define DEM_CFG_CUSTOMIZABLEDTCSTATUSBYTE                   FALSE
#define DEM_CFG_CLEARDTCCLEARSALLBITS                       TRUE
#define DEM_CFG_DTCSETTINGBLOCKSREPORTING                   TRUE
#define DEM_CFG_PRJSPECIFICEVENTSTATUSHANDLING              FALSE
#define DEM_CFG_SUPPORT_AGINGCNTR_ONLY_WHEN_AGING_ALLOWED   FALSE

#define DEM_CFG_DTC_STATUSCHANGEDCALLBACK_OFF	STD_OFF
#define DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON	STD_ON
#define DEM_CFG_DTC_STATUSCHANGEDCALLBACK       DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON

#define DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF	STD_OFF
#define DEM_CFG_EVT_CLEARALLOWEDCALLBACK_ON		STD_ON
#define DEM_CFG_EVT_CLEARALLOWEDCALLBACK       	DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF

#define DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK_OFF		STD_OFF
#define DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK_ON		STD_ON
#define DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK       	DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK_OFF

#define DEM_CFG_EVT_DATACHANGEDCALLBACK_OFF    STD_OFF
#define DEM_CFG_EVT_DATACHANGEDCALLBACK_ON     STD_ON
#define DEM_CFG_EVT_DATACHANGEDCALLBACK        DEM_CFG_EVT_DATACHANGEDCALLBACK_ON
#define DEM_CFG_EVT_DATACHANGEDCALLBACK_FUNC  DemEvent_LowBatteryVoltageLow_EventDataChanged

#define DEM_CFG_EVT_PROJECT_EXTENSION  FALSE

#define DEM_CFG_BSWERRORBUFFERSIZE  0u

#define DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS 	0u

#define DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT       FALSE

#define DEM_CFG_EVT_ATTRIBUTE_OFF  STD_OFF
#define DEM_CFG_EVT_ATTRIBUTE_ON  STD_ON
#define DEM_CFG_EVT_ATTRIBUTE DEM_CFG_EVT_ATTRIBUTE_OFF

#define DEM_EVT_BP_STATE_CAUSALFAULT            0u

#define DEM_EVT_BP_STATE_SUSPICIONLEVEL         1u
#define DEM_EVT_BP_STATE_NOTAVAILABLE           2u
#define DEM_EVT_BP_STATE_INITMONITORING         3u
#define DEM_EVT_BP_STATE_INITMONITORING_MASK    (0x07u)
#define DEM_EVT_BP_STATE_INITMONITORING_SIZE    3u
#define DEM_EVT_BP_STATE_WIRSTATUS_EXTERNAL     6u

#define DEM_EVT_BP_STATE_NXT_REPORT_IS_RELEVANT      7u

typedef uint8 Dem_EvtStateType;
#define DEM_EVTSTATE_ISBITSET      rba_DiagLib_Bit8IsBitSet
#define DEM_EVTSTATE_OVERWRITEBIT  rba_DiagLib_Bit8OverwriteBit
#define DEM_EVTSTATE_OVERWRITEBITS rba_DiagLib_Bit8OverwriteBits
#define DEM_EVTSTATE_CLEARBIT      rba_DiagLib_Bit8ClearBit
#define DEM_EVTSTATE_SETBIT        rba_DiagLib_Bit8SetBit
#define DEM_EVTSTATE_GETBITS       rba_DiagLib_Bit8GetBits
#define DEM_EVTSTATE_CLEARBITS     rba_DiagLib_Bit8ClearBits

#define DEM_CFG_TRIGGERMONITORINITBEFORECLEAROK  TRUE

#define DEM_CFG_CALLBACK_INIT_MON_FOR_EVENT_SUPPORTED   TRUE

#define DEM_CFG_CALLBACK_INITMFORE_LISTLENGTH  40u
#define DEM_CFG_CALLBACK_INITMFORE_LIST \
{ \
   { DemConf_DemEventParameter_DemEventParameter_AutolocationFail, &DemEvent_AutolocationFail_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CanAbsWheelPulseSignalMissing, &DemEvent_CanAbsWheelPulseSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CanAtmosphericTemperatureSignalMissing, &DemEvent_CanAtmosphericTemperatureSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CanBusoffError, &DemEvent_CanBusoffError_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CanClockSyncSignalMissing, &DemEvent_CanClockSyncSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CanOffroadSignalMissing, &DemEvent_CanOffroadSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CanSpeedSignalMissing, &DemEvent_CanSpeedSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CanVehicleModeSignalMissing, &DemEvent_CanVehicleModeSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CanWheelDirectionSignalMissing, &DemEvent_CanWheelDirectionSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithBcm, &DemEvent_CommunicationError_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithDcmFL, &DemEvent_CommunicationError_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithDcmRL, &DemEvent_CommunicationError_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_CommunicationErrorWithScmFL, &DemEvent_CommunicationError_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_DetectedTooManySensors, &DemEvent_DetectedTooManySensors_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_EcuRfInterference, &DemEvent_EcuRfInterference_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_NoQualifiedSensorSignals, &DemEvent_NoQualifiedSensorSignals_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorDefectFL, &DemEvent_SensorDefectFL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorDefectFR, &DemEvent_SensorDefectFR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorDefectRL, &DemEvent_SensorDefectRL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorDefectRR, &DemEvent_SensorDefectRR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorDefectUnknownPosition, &DemEvent_SensorDefectUnknownPosition_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFL, &DemEvent_SensorLifeTimeCounterLowFL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowFR, &DemEvent_SensorLifeTimeCounterLowFR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRL, &DemEvent_SensorLifeTimeCounterLowRL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorLifeTimeCounterLowRR, &DemEvent_SensorLifeTimeCounterLowRR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorMissingFL, &DemEvent_SensorMissingFL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorMissingFR, &DemEvent_SensorMissingFR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorMissingRL, &DemEvent_SensorMissingRL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorMissingRR, &DemEvent_SensorMissingRR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorMissingUnknownPosition, &DemEvent_SensorMissingUnknownPosition_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorOvertempFL, &DemEvent_SensorOvertempFL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorOvertempFR, &DemEvent_SensorOvertempFR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorOvertempRL, &DemEvent_SensorOvertempRL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_SensorOvertempRR, &DemEvent_SensorOvertempRR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_DemEventParameter_TpmsNotFunctional, &DemEvent_TpmsNotFunctional_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_Event_BatteryVoltageHigh, &DemEvent_BatteryVoltageHigh_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_Event_BatteryVoltageLow, &DemEvent_BatteryVoltageLow_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_Event_FailedMemory, &DemEvent_FailedMemory_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_Event_NoEcuSerialNumber, &DemEvent_NoEcuSerialNumber_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_Event_NoVin, &DemEvent_NoVin_InitMonForEvent }\
}

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

