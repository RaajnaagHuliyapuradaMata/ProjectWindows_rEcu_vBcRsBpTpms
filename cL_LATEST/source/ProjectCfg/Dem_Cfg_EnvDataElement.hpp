#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_EnvDataElement.hpp                                        */
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
#include "Std_Types.hpp"
#include "Dem_Cfg_EnvDataElement_DataSize.hpp"
#include "Dcm_Dem.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_ENV_DATAELEMENTS_EXTERN_AVAILABILITY   STD_ON
#define DEM_CFG_ENV_DATAELEMENTS_INTERN_AVAILABILITY  STD_OFF
#define DEM_CFG_READDEM_AGINGCTR_UPCNT_SUPPORTED                         FALSE
#define DEM_CFG_READDEM_AGINGCTR_DOWNCNT_SUPPORTED                       FALSE
#define DEM_CFG_READDEM_OCCCTR_SUPPORTED                                 FALSE
#define DEM_CFG_READDEM_OVFLIND_SUPPORTED                                FALSE
#define DEM_CFG_READDEM_SIGNIFICANCE_SUPPORTED                           FALSE
#define DEM_CFG_READDEM_DEBUG0_SUPPORTED                                 FALSE
#define DEM_CFG_READDEM_DEBUG1_SUPPORTED                                 FALSE
#define DEM_CFG_READDEM_EVENT_ID_SUPPORTED                               FALSE
#define DEM_CFG_READDEM_CURRENT_FDC_SUPPORTED                            FALSE
#define DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED           FALSE
#define DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED               FALSE
#define DEM_CFG_READDEM_CYCLES_SINCE_FIRST_FAILED_SUPPORTED              FALSE
#define DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_SUPPORTED               FALSE
#define DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_EXCLUDING_TNC_SUPPORTED   FALSE
#define DEM_CFG_READDEM_FAILED_CYCLES_SUPPORTED                          FALSE
#define DEM_CFG_READDEM_PRJ_SPECIFIC_DATA_ON_RETRIEVE_SUPPORTED          FALSE
#define DEM_CFG_READDEM_PRJ_SPECIFIC_DATA_ON_REPORT_SUPPORTED            FALSE
#define DEM_CFG_DATAELEMENT_LASTFAILEDSINCELASTFAILEDEXCLUDINGTNC_INCLUDESFAILEDCYCLE    TRUE
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLESPEED  1
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_AMBIENTTEMPERATURE  2
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLEMODE  3
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_RESERVED  4
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_LVBATTERYVOLTAGE  5
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_OCCDATE  6
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_OCCTIME  7
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_TIREPRESSURES  8
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_TIRETEMPERATURES  9
#define DEM_DATAELEM_DEMDATAELEMENTCLASS_ECUMODE_LLSTATUS  10
#define DEM_DATAELEM_SR_EDR_RECORD_EXTENDEDDATARECORD0X01_DTCEXTENDEDDATARECORDDATA  11

#define DEM_CFG_ENV_DATAELEMENTS \
{ \
   { DEM_ENV_DATAELEMENTS_EXTCS_INIT(NULL_PTR) DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) 0, FALSE }\
   ,{ &Dem_GetData_VehicleSpeed, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLESPEED , FALSE }\
   ,{ &Dem_GetData_AmbientTemperature, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_AMBIENTTEMPERATURE , FALSE }\
   ,{ &Dem_GetData_VehicleMode, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLEMODE , FALSE }\
   ,{ &Dem_GetData_Reserved, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_RESERVED , FALSE }\
   ,{ &Dem_GetData_LVBatteryVoltage, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_LVBATTERYVOLTAGE , FALSE }\
   ,{ &Dem_GetData_OccDate, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_OCCDATE , FALSE }\
   ,{ &Dem_GetData_OccTime, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_OCCTIME , FALSE }\
   ,{ &Dem_GetData_TirePressures, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_TIREPRESSURES , FALSE }\
   ,{ &Dem_GetData_TireTemperatures, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_TIRETEMPERATURES , FALSE }\
   ,{ &Dem_GetData_EcuMode_LLStatus, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR) DataSize_DEM_DATAELEM_DEMDATAELEMENTCLASS_ECUMODE_LLSTATUS , FALSE }\
   ,{ &Dcm_DemGetSRData_SR_EDR_Record_ExtendedDataRecord0x01_DTCExtendedDataRecordData, DEM_ENV_DATAELEMENTS_INTERN_INIT(NULL_PTR)DataSize_DEM_DATAELEM_SR_EDR_RECORD_EXTENDEDDATARECORD0X01_DTCEXTENDEDDATARECORDDATA , FALSE }\
}

#define DEM_CFG_ENV_DATAELEMENTS_ARRAYLENGTH      (11+1)

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

