#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_Client_DataStructures.hpp                                 */
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
#include "Dem_Lok_Det.hpp"
#include "Dem_Types.hpp"
#include "Dem_Lib.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_DTCSEVERITY_AVAILABILITY_MASK_CLIENTID_1    (DEM_SEVERITY_NO_SEVERITY)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8 data1;
   uint8 data2;
   uint8 data3;
}Dem_Cfg_ClientParams_8Type;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define DEM_START_SEC_CONST
#include "Dem_MemMap.hpp"
extern const Dem_Cfg_ClientParams_8Type Dem_Cfg_ClientParams_8[2];

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
LOCAL_INLINE Dem_UdsStatusByteType Dem_Cfg_ClientParams_GetDTCStatusAvailabilityMask(uint8 indx){ //TBD: Move to Macros section?
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 2));
   return Dem_Cfg_ClientParams_8[indx].data3;
}

LOCAL_INLINE Dem_DTCTranslationFormatType Dem_Cfg_ClientParams_GetDTCTranslationFormat(uint8 indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 2));
   return Dem_Cfg_ClientParams_8[indx].data2;
}

LOCAL_INLINE uint8 Dem_Cfg_ClientParams_GetDTCSeverityAvailabilityMask(uint8 indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 2));
   return Dem_Cfg_ClientParams_8[indx].data1;
}
#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

