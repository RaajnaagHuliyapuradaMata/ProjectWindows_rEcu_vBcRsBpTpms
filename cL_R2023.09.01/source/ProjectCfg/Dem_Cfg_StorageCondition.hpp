#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_StorageCondition.hpp                                      */
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
#define DEM_CFG_STORAGECONDITION_ON    STD_ON
#define DEM_CFG_STORAGECONDITION_OFF   STD_OFF
#define DEM_CFG_STORAGECONDITION       DEM_CFG_STORAGECONDITION_OFF

#define DEM_STORAGECONDITION_COUNT         0u
#define DEM_STORAGECONDITION_ARRAYLENGTH   (DEM_STORAGECONDITION_COUNT)

#if(DEM_STORAGECONDITION_ARRAYLENGTH <= 8) \
   || (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_OFF)
typedef uint8 Dem_StoCoList;
#elif(DEM_STORAGECONDITION_ARRAYLENGTH <= 16)
typedef uint16 Dem_StoCoList;
#elif(DEM_STORAGECONDITION_ARRAYLENGTH <= 32)
typedef uint32 Dem_StoCoList;
#else
#error DEM currently only supports up to 32 StorageConditions
#endif

#if(DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)

#define DEM_STOCO_EventParameter_DTC_0x500042_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x5000a2_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x5000a3_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560116_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560131_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560149_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x56014b_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560216_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560231_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560249_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x56024b_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560316_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560331_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560349_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x56034b_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560416_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560431_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560449_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x56044b_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560504_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560531_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x56064a_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560793_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x560929_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0x9CC055_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60129_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60188_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60329_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60429_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60529_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60629_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60729_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60829_Event             (0u)
#define DEM_STOCO_EventParameter_DTC_0xd60929_Event             (0u)

#define DEM_CFG_STOCO_INITIALSTATE    (   0u \
                                      )

#define DEM_CFG_STOCO_PARAMS \
{ \
   { \
   }\
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

