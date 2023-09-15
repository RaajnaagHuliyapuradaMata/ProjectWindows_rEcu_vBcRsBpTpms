#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_OperationCycle_DataStructures.hpp                         */
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
#include "Dem_Lib.hpp"
#include "Dem_Cfg_OperationCycle.hpp"

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
   Dem_OperationCycleList DependentCycleMask;
   boolean IsAllowedToBeStartedDirectly;
}Dem_Cfg_OperationCycleType;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define DEM_START_SEC_CONST
#include "Dem_MemMap.hpp"
extern const Dem_Cfg_OperationCycleType Dem_Cfg_OperationCycle[3];
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
LOCAL_INLINE Dem_OperationCycleList Dem_Cfg_OperationCycle_GetDependentCycleMask(Dem_OperationCycleIdType indx){
   DEM_ASSERT_RANGECHECK(indx < 3);
   return Dem_Cfg_OperationCycle[indx].DependentCycleMask;
}

LOCAL_INLINE boolean Dem_Cfg_OperationCycle_GetIsAllowedToBeStartedDirectly(Dem_OperationCycleIdType indx){
   DEM_ASSERT_RANGECHECK(indx < 3);
   return Dem_Cfg_OperationCycle[indx].IsAllowedToBeStartedDirectly;
}


/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

