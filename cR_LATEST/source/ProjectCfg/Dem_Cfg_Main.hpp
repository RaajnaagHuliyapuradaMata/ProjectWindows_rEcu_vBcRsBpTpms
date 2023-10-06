#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_Main.hpp                                                  */
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
#define DEM_CFG_BUILDTARGET_ECU             1
#define DEM_CFG_BUILDTARGET_DEMTESTSUITE    2
#define DEM_CFG_BUILDTARGET_DIAGNOSISBUILD  3
#define DEM_CFG_BUILDTARGET  DEM_CFG_BUILDTARGET_ECU
#define DEM_MAIN_CYCLETIME  10
#define DEM_CFG_DEVERRORDETECT_OFF          STD_OFF
#define DEM_CFG_DEVERRORDETECT_ON           STD_ON
#define DEM_CFG_DEVERRORDETECT              DEM_CFG_DEVERRORDETECT_ON
#define DEM_NO_SUPPRESSION						      STD_OFF
#define DEM_EVENT_SUPPRESSION				          STD_ON
#define DEM_DTC_SUPPRESSION 					      (STD_ON+STD_OFF+1)
#define DEM_EVENT_AND_DTC_SUPPRESSION			      (DEM_DTC_SUPPRESSION+1)
#define DEM_CFG_SUPPRESSION                           DEM_EVENT_SUPPRESSION
#define DEM_CFG_ADVANCEOPERATIONCYCLE_EVENTSPERLOCK      16u

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

