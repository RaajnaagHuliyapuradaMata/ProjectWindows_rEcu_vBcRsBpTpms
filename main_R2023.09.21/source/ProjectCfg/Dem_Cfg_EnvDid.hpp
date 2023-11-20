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
   DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLESPEED,     \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_ENGINESPEED,     \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_AMBIENTTEMPERATURE,     \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLEMODE,   DEM_DATAELEM_DEMDATAELEMENTCLASS_HVSOC,   DEM_DATAELEM_DEMDATAELEMENTCLASS_LVBATTERYVOLTAGE,   DEM_DATAELEM_DEMDATAELEMENTCLASS_VEHICLESPEED,   DEM_DATAELEM_DEMDATAELEMENTCLASS_AMBIENTTEMPERATURE,   DEM_DATAELEM_DEMDATAELEMENTCLASS_ECUMODE_ROADMODE_LLSTATUS,   DEM_DATAELEM_DEMDATAELEMENTCLASS_OCCDATE,   DEM_DATAELEM_DEMDATAELEMENTCLASS_OCCTIME,   DEM_DATAELEM_DEMDATAELEMENTCLASS_TIREPRESS,   DEM_DATAELEM_DEMDATAELEMENTCLASS_TIRETEMP,     \
   0 \
}

#define DEM_DID_VEHICLESPEED         1
#define DEM_DID_ENGINESPEED         2
#define DEM_DID_AMBIENTTEMPERATURE         3
#define DEM_DID_DEMDIDCLASS_RIVIANSNAPSHOT         4

#define DEM_CFG_ENVDID \
{ \
   { 0, 0 }\
   ,{ 1, 3329 }\
   ,{ 2, 3328 }\
   ,{ 3, 3327 }\
   ,{ 13, 1 }\
}

#define DEM_CFG_ENVDID_ARRAYLENGTH  (4+1)

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

