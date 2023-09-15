#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_EnvFreezeFrame.hpp                                        */
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
#define DEM_CFG_ENVFREEZEFRAME2DID \
{ \
   DEM_DID_DEMDIDCLASS_0XFFF,  \
   DEM_DID_DEMDIDCLASS_POWERMODE_B000,   DEM_DID_DEMDIDCLASS_RESERVED_B004,   DEM_DID_DEMDIDCLASS_SUPPLYVOLTAGE_B001,   DEM_DID_DEMDIDCLASS_VEHICLESPEED_B002,   DEM_DID_DEMDIDCLASS_AMBIENTTEMPERATURE_B003,   DEM_DID_DEMDIDCLASS_ECUMODE_LLSTATUS_B009,   DEM_DID_DEMDIDCLASS_OCCDATE_B005,   DEM_DID_DEMDIDCLASS_OCCTIME_B006,   DEM_DID_DEMDIDCLASS_TIREPRESSURES_B007,   DEM_DID_DEMDIDCLASS_TIRETEMPERATURES_B008,  \
   0 \
}

#define DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS         1
#define DEM_FREEZEFRAME_DEMFREEZEFRAMECLASS_TPMS         2

#define DEM_CFG_ENVFREEZEFRAME \
{ \
   { 0,0 }\
   ,{ 1, 1 }\
   ,{ 11, 32 }\
}

#define DEM_CFG_ENVFREEZEFRAME_ARRAYLENGTH  (2+1)

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

