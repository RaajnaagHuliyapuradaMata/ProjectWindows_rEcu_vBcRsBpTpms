#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_DTC_DataStructures.hpp                                    */
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
#include "Dem_Cfg_DTCs.hpp"
#include "Dem_Lok_Det.hpp"
#include "Dem_Types.hpp"
#include "Dem_Lib.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   Dem_DtcCodeType     DtcCode;
   Dem_DTCSeverityType Severity;
   uint8               Func_Unit;
   Dem_DTCKindType     Kind;
   boolean             DtcCode_Is_Index;
   boolean             Nv_Storage;
}Dem_Cfg_DtcType;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
extern const Dem_Cfg_DtcType Dem_Cfg_Dtc[42];

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
LOCAL_INLINE Dem_DTCKindType Dem_Cfg_Dtc_GetKind(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
   return Dem_Cfg_Dtc[indx].Kind;
}

LOCAL_INLINE Dem_DTCSeverityType Dem_Cfg_Dtc_GetSeverity(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
   return Dem_Cfg_Dtc[indx].Severity;
}

LOCAL_INLINE boolean Dem_Cfg_Dtc_GetNv_Storage(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
   return Dem_Cfg_Dtc[indx].Nv_Storage;
}

LOCAL_INLINE uint8 Dem_Cfg_Dtc_GetFunc_Unit(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
   return Dem_Cfg_Dtc[indx].Func_Unit;
}

LOCAL_INLINE boolean Dem_Cfg_Dtc_GetDtcCode_Is_Index(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
   return Dem_Cfg_Dtc[indx].DtcCode_Is_Index;
}

LOCAL_INLINE Dem_DtcCodeType Dem_Cfg_Dtc_GetObd_DtcCode(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
   return DEM_INVALID_DTC;
}

LOCAL_INLINE Dem_DtcCodeType Dem_Cfg_Dtc_GetDtcCode(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 42));
   return Dem_Cfg_Dtc[indx].DtcCode;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

