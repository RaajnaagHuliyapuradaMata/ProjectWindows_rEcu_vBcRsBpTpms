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
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
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
#include "rba_DiagLib.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_INVALID_DTC                 0xAA000000u

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   uint8 data2;  // Severity
}Dem_Cfg_Dtc_8Type;

typedef struct{
   uint32 data1;  // Kind, Nv_Storage, Func_Unit, DtcCode_Is_Index, DtcCode
}Dem_Cfg_Dtc_32Type;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define DEM_START_SEC_CONST
#include "Dem_MemMap.hpp"
extern const Dem_Cfg_Dtc_8Type Dem_Cfg_Dtc_8[35];
extern const Dem_Cfg_Dtc_32Type Dem_Cfg_Dtc_32[35];

LOCAL_INLINE Dem_DTCKindType Dem_Cfg_Dtc_GetKind(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
   return (Dem_DTCKindType)(RBA_DIAGLIB_GETBITS32(Dem_Cfg_Dtc_32[indx].data1, 0, 2));
}

LOCAL_INLINE Dem_DTCSeverityType Dem_Cfg_Dtc_GetSeverity(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
   return Dem_Cfg_Dtc_8[indx].data2;
}

LOCAL_INLINE boolean Dem_Cfg_Dtc_GetNv_Storage(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
   return RBA_DIAGLIB_ISBITSET32(Dem_Cfg_Dtc_32[indx].data1, 2);
}

LOCAL_INLINE uint8 Dem_Cfg_Dtc_GetFunc_Unit(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
   return (uint8)(RBA_DIAGLIB_GETSINGLEBIT32(Dem_Cfg_Dtc_32[indx].data1, 3));
}

LOCAL_INLINE boolean Dem_Cfg_Dtc_GetDtcCode_Is_Index(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
   return RBA_DIAGLIB_ISBITSET32(Dem_Cfg_Dtc_32[indx].data1, 4);
}

LOCAL_INLINE Dem_DtcCodeType Dem_Cfg_Dtc_GetObd_DtcCode(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
   return DEM_INVALID_DTC;
}

LOCAL_INLINE Dem_DtcCodeType Dem_Cfg_Dtc_GetDtcCode(Dem_DtcIdType indx){
   DEM_ASSERT_RANGECHECK((0 < indx) && (indx < 35));
   return (Dem_DtcCodeType)(RBA_DIAGLIB_GETBITS32(Dem_Cfg_Dtc_32[indx].data1, 5, 24));
}
#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.hpp"

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

