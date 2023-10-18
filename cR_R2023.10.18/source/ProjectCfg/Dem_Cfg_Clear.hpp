#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_Clear.hpp                                                 */
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
#include "Dem_Types.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH                          1
#define DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_TRIGGER                         2
#define DEM_CFG_CLEAR_DTC_BEHAVIOR_VOLATILE                                    3
#define DEM_CFG_CLEAR_DTC_BEHAVIOR DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH

#define DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS                        1
#define DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS                       2
#define DEM_CFG_CLEAR_DTC_LIMITATION DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS

#define DEM_CFG_CLEAR_MAX_NO_OF_EVENTS_PER_CYCLE                             41u

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
DEM_INLINE void Dem_ClearDtcNotificationStartCallbacks(
      uint32            DTC
   ,  Dem_DTCFormatType DTCFormat
   ,  Dem_DTCOriginType DTCOrigin
){
   DEM_UNUSED_PARAM(DTC);
   DEM_UNUSED_PARAM(DTCFormat);
   DEM_UNUSED_PARAM(DTCOrigin);
}

DEM_INLINE void Dem_ClearDtcNotificationFinishCallbacks(
      uint32            DTC
   ,  Dem_DTCFormatType DTCFormat
   ,  Dem_DTCOriginType DTCOrigin
){
   DEM_UNUSED_PARAM(DTC);
   DEM_UNUSED_PARAM(DTCFormat);
   DEM_UNUSED_PARAM(DTCOrigin);
}

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

