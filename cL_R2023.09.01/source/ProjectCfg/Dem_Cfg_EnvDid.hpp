#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_EnvDid.hpp                                                */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_ENVDID2DATAELEMENT \
{ \
   DEM_DATAELEM_SR_EDR_RECORD_EXTENDEDDATARECORD0X01_DTCEXTENDEDDATARECORDDATA,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLESPEED,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLEMODE,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_LVBATTERYVOLTAGE,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_AMBIENTTEMPERATURE,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_RESERVED,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_OCCDATE,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_OCCTIME,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_TIREPRESSURES,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_TIRETEMPERATURES,                                       \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_ECUMODE_LLSTATUS,                                       \
   0 \
}

#define DEM_DID_DEMDIDCLASS_0XFFF         1
#define DEM_DID_DEMDIDCLASS_VEHICLESPEED_B002         2
#define DEM_DID_DEMDIDCLASS_POWERMODE_B000         3
#define DEM_DID_DEMDIDCLASS_SUPPLYVOLTAGE_B001         4
#define DEM_DID_DEMDIDCLASS_AMBIENTTEMPERATURE_B003         5
#define DEM_DID_DEMDIDCLASS_RESERVED_B004         6
#define DEM_DID_DEMDIDCLASS_OCCDATE_B005         7
#define DEM_DID_DEMDIDCLASS_OCCTIME_B006         8
#define DEM_DID_DEMDIDCLASS_TIREPRESSURES_B007         9
#define DEM_DID_DEMDIDCLASS_TIRETEMPERATURES_B008         10
#define DEM_DID_DEMDIDCLASS_ECUMODE_LLSTATUS_B009         11

#define DEM_CFG_ENVDID \
{ \
   { 0, 0 }\
   ,{ 1, 4095 }\
   ,{ 2, 45058 }\
   ,{ 3, 45056 }\
   ,{ 4, 45057 }\
   ,{ 5, 45059 }\
   ,{ 6, 45060 }\
   ,{ 7, 45061 }\
   ,{ 8, 45062 }\
   ,{ 9, 45063 }\
   ,{ 10, 45064 }\
   ,{ 11, 45065 }\
}

#define DEM_CFG_ENVDID_ARRAYLENGTH  (11+1)

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

