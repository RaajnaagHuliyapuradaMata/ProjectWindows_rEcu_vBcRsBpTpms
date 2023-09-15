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
#define DEM_CFG_TRIGGERFIMREPORTS  DEM_CFG_TRIGGERFIMREPORTS_OFF
#define DEM_CFG_FIM_OFF STD_OFF
#define DEM_CFG_FIM_ON  STD_ON
#define DEM_CFG_FIM_USED DEM_CFG_FIM_OFF
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
#define DEM_CFG_STORAGECONDITIONBLOCKSPASSEDREPORTS         FALSE
#define DEM_CFG_DTC_STATUSCHANGEDCALLBACK_OFF	STD_OFF
#define DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON	STD_ON
#define DEM_CFG_DTC_STATUSCHANGEDCALLBACK       DEM_CFG_DTC_STATUSCHANGEDCALLBACK_OFF
#define DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF	STD_OFF
#define DEM_CFG_EVT_CLEARALLOWEDCALLBACK_ON		STD_ON
#define DEM_CFG_EVT_CLEARALLOWEDCALLBACK       	DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF
#define DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK_OFF		STD_OFF
#define DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK_ON		STD_ON
#define DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK       	DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK_OFF
#define DEM_CFG_EVT_GLOBALINITMONITORINGCALLBACK_OFF   STD_OFF
#define DEM_CFG_EVT_GLOBALINITMONITORINGCALLBACK_ON    STD_ON
#define DEM_CFG_EVT_GLOBALINITMONITORINGCALLBACK       DEM_CFG_EVT_GLOBALINITMONITORINGCALLBACK_OFF
#define DEM_CFG_EVT_DATACHANGEDCALLBACK_OFF    STD_OFF
#define DEM_CFG_EVT_DATACHANGEDCALLBACK_ON     STD_ON
#define DEM_CFG_EVT_DATACHANGEDCALLBACK        DEM_CFG_EVT_DATACHANGEDCALLBACK_OFF
#define DEM_CFG_EVT_PROJECT_EXTENSION  FALSE
#define DEM_CFG_GLOBAL_EVT_ST_CH_CALLBACK_OFF    STD_OFF
#define DEM_CFG_GLOBAL_EVT_ST_CH_CALLBACK_ON     STD_ON
#define DEM_CFG_GLOBAL_EVT_ST_CH_CALLBACK        DEM_CFG_GLOBAL_EVT_ST_CH_CALLBACK_OFF
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
#define DEM_CFG_PROJECTEXTENSION_CLEAR_PENDING_NOTIFICATION  FALSE
#define DEM_CFG_CALLBACK_INIT_MON_FOR_EVENT_SUPPORTED   TRUE
#define DEM_CFG_CALLBACK_INITMFORE_LISTLENGTH  34u
#define DEM_CFG_QUEUEING_UNROBUST_EVENTS_SUPPORTED  FALSE

#define DEM_CFG_CALLBACK_INITMFORE_LIST \
{ \
   { DemConf_DemEventParameter_EventParameter_DTC_0x500042_Event, &DemEvent_FailedMemory_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x5000a2_Event, &DemEvent_BatteryVoltageLow_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x5000a3_Event, &DemEvent_BatteryVoltageHigh_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560116_Event, &DemEvent_SensorLifeTimeCounterLowFL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560131_Event, &DemEvent_SensorMissingFL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560149_Event, &DemEvent_SensorDefectFL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x56014b_Event, &DemEvent_SensorOvertempFL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560216_Event, &DemEvent_SensorLifeTimeCounterLowFR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560231_Event, &DemEvent_SensorMissingFR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560249_Event, &DemEvent_SensorDefectFR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x56024b_Event, &DemEvent_SensorOvertempFR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560316_Event, &DemEvent_SensorLifeTimeCounterLowRR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560331_Event, &DemEvent_SensorMissingRR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560349_Event, &DemEvent_SensorDefectRR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x56034b_Event, &DemEvent_SensorOvertempRR_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560416_Event, &DemEvent_SensorLifeTimeCounterLowRL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560431_Event, &DemEvent_SensorMissingRL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560449_Event, &DemEvent_SensorDefectRL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x56044b_Event, &DemEvent_SensorOvertempRL_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560504_Event, &DemEvent_SensorDefectUnknownPosition_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560531_Event, &DemEvent_SensorMissingUnknownPosition_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x56064a_Event, &DemEvent_AutolocationFail_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560793_Event, &DemEvent_TpmsNotFunctional_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x560929_Event, &DemEvent_EcuRfInterference_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0x9CC055_Event, &DemEvent_ModuleNotProvisioned_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60129_Event, &DemEvent_CanBcmPowerModeSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60188_Event, &DemEvent_CanBusoffError_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60329_Event, &DemEvent_CanAbsWheelPulseSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60429_Event, &DemEvent_DetectedTooManySensors_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60529_Event, &DemEvent_NoQualifiedSensorSignals_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60629_Event, &DemEvent_CanAtmosphericTemperatureSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60729_Event, &DemEvent_CanSpeedSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60829_Event, &DemEvent_CanWheelDirectionSignalMissing_InitMonForEvent }\
   ,{ DemConf_DemEventParameter_EventParameter_DTC_0xd60929_Event, &DemEvent_CanClockSyncSignalMissing_InitMonForEvent }\
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

