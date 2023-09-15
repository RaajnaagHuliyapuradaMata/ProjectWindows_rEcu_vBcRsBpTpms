#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_EventCategory.hpp                                         */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_EVTCATEGORY_OFF  STD_OFF
#define DEM_CFG_EVTCATEGORY_ON   STD_ON

#define DEM_CFG_EVTCATEGORY  DEM_CFG_EVTCATEGORY_OFF

#if(DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)

typedef uint8 Dem_EvtCategoryPrioType;

#define DemConf_DemEventCategory_INVALIDCATEGORY                      0u
#define DEM_CFG_CATEGORY_COUNT 0
#define DEM_EVENTCATPRIO_ARRAYLENGTH   (DEM_CFG_CATEGORY_COUNT+1u)

#define DemConf_DemEventCategoryPriority_INVALIDPRIO                  0u

//generate the table index is category
#define DEM_CFG_EVTCATEGORYPRIO \
{\
{DemConf_DemEventCategoryPriority_INVALIDPRIO                },\
}
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

