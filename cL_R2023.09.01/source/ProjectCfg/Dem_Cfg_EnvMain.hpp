#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_EnvMain.hpp                                               */
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
#define DEM_CFG_ENVMINSIZE_OF_RAWENVDATA           (33u + 0u + 0u)

#define DEM_CFG_ENVMINSIZE_OF_MULTIPLE_RAWENVDATA   (33u + 0u + 0u)

#define DEM_CFG_OFFSET_OBDRAWENVDATA         0u

#define DEM_CFG_ENVEVENTID2ENVDATA \
{ \
   { 0u,0u }                                  \
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X500042_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X5000A2_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X5000A3_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560116_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560131_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560149_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X56014B_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560216_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560231_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560249_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X56024B_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560316_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560331_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560349_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X56034B_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560416_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560431_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560449_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X56044B_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560504_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560531_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X56064A_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560793_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X560929_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0X9CC055_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60129_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60188_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60329_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60429_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60529_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60629_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60729_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60829_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
   ,{  DEM_EXTDATA_DEMEXTENDEDDATACLASS_DTC_0XD60929_EVENT, DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS }\
}

#define DEM_CFG_J1939_ENVEVENTID2ENVDATA \
{ \
   { 0u,0u }                                  \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
   ,{  0u, 0u }                                \
}

#define DEM_CFG_CAPTURE_SYNCHRONOUS_TO_REPORTING         1u
#define DEM_CFG_CAPTURE_ASYNCHRONOUS_TO_REPORTING        2u

#define DEM_CFG_ENVIRONMENT_DATA_CAPTURE                   DEM_CFG_CAPTURE_SYNCHRONOUS_TO_REPORTING

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

