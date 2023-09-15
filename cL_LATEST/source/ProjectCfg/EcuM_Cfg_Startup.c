#pragma once
/******************************************************************************/
/* File   : EcuM_Cfg_Startup.c                                                */
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
#include "EcuM.hpp"
#include "EcuM_Callout.hpp"
#include "EcuM_RunTime.hpp"

#if(ECUM_INCLUDE_DET == STD_ON)
#include "Det.hpp"
#endif

#include "Dem.hpp"
#include "Can.hpp"
#include "CanIf.hpp"
#include "ComM.hpp"
#include "CanSM.hpp"
#include "PduR.hpp"
#include "Com.hpp"
#include "Dcm.hpp"
#include "CanTp.hpp"
#include "FiM.hpp"
#include "EcuM_Cfg_Startup.hpp"
#include "EcuM_Prv.hpp"

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

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_MemMap.hpp"
#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
void EcuM_AL_DriverRestart(
   const Type_CfgSwcServiceEcuM_st* ConfigPtr
){
   (void)ConfigPtr;
}
#endif
#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_MemMap.hpp"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

