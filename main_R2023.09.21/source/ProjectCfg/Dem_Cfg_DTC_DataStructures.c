/******************************************************************************/
/* File   : Dem_Cfg_DTC_DataStructures.c                                      */
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

#include "Dem_Cfg_DTC_DataStructures.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"
const Dem_Cfg_DtcType Dem_Cfg_Dtc[42] = {
      {0, 0, 0, 0, 0, 0 }
   ,  {0xC14087, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xC18687, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xC19987, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xC20087, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xC20887, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60129, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60188, DEM_SEVERITY_NO_SEVERITY, 0x8, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60229, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60329, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60429, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x0, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60529, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x0, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60629, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60729, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60829, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0xD60929, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x3, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x500042, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x2, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x500051, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x4, DEM_DTC_KIND_ALL_DTCS, FALSE, FALSE }
   ,  {0x5000A2, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x5, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x5000A3, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x5, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x500151, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x4, DEM_DTC_KIND_ALL_DTCS, FALSE, FALSE }
   ,  {0x560116, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560131, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560149, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x56014B, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560216, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560231, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560249, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x56024B, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560316, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560331, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560349, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x56034B, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560416, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560431, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560449, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x56044B, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560504, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560531, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x1, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x56064A, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x0, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560793, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x2, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
   ,  {0x560929, DEM_SEVERITY_CHECK_AT_NEXT_HALT, 0x0, DEM_DTC_KIND_ALL_DTCS, FALSE, TRUE }
};

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.hpp"

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

