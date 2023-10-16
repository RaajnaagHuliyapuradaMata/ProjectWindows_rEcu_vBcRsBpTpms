#pragma once
/******************************************************************************/
/* File   : CfgSwcServiceEcuM.h                                               */
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
#include "CompilerCfg_SwcServiceEcuM.hpp"
#include "Types_SwcServiceEcuM.hpp"

#include "CfgEcuabCanIf.hpp"
#include "CfgSwcServiceBswM.hpp"
#include "CfgSwcServiceCanSM.hpp"
#include "CfgSwcServiceCanTp.hpp"
#include "CfgSwcServiceCom.hpp"
#include "CfgSwcServiceComM.hpp"
#include "CfgSwcServiceFiM.hpp"
#include "CfgSwcServiceOs.hpp"
#include "CfgSwcServicePduR.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CfgSwcServiceEcuM_dLenHash                                          (16)
#define CfgSwcServiceEcuM_dSourceWakeupNone ((Type_SwcServiceEcuM_tSourceWakeup) 0x0000u) //TBD: enum
#define CfgSwcServiceEcuM_dPOWER            ((Type_SwcServiceEcuM_tSourceWakeup) 0x0001u)
#define CfgSwcServiceEcuM_dRESET            ((Type_SwcServiceEcuM_tSourceWakeup) 0x0002u)
#define CfgSwcServiceEcuM_dINTERNAL_RESET   ((Type_SwcServiceEcuM_tSourceWakeup) 0x0004u)
#define CfgSwcServiceEcuM_dINTERNAL_WDG     ((Type_SwcServiceEcuM_tSourceWakeup) 0x0008u)
#define CfgSwcServiceEcuM_dEXTERNAL_WDG     ((Type_SwcServiceEcuM_tSourceWakeup) 0x1000u)
#define CfgSwcServiceEcuM_dNumConfigSet                                        1

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   const Type_CfgEcuabCanIf_st*      pcstCfgEcuabCanIf;
   const Type_CfgSwcServiceComM_st*  pcstCfgSwcServiceComM;
   const Type_CfgSwcServiceCanSM_st* pcstCfgSwcServiceCanSM;
   const Type_CfgSwcServicePduR_st*  pcstCfgSwcServicePduR;
   const Type_CfgSwcServiceCom_st*   pcstCfgSwcServiceCom;
   const Type_CfgSwcServiceCanTp_st* pcstCfgSwcServiceCanTp;
   const Type_CfgSwcServiceFiM_st*   pcstCfgSwcServiceFiM;
   const Type_CfgSwcServiceBswM_st*  pcstCfgSwcServiceBswM;
}Type_CfgSwcServiceEcuM_stRefCfgModules;

typedef struct{
         uint8  u8NumRefsPncComM;
   const uint8* pcau8ListRefsPnc;
}Type_CfgSwcServiceEcuM_stListRefsPncWakeup;

typedef struct{
         Type_SwcServiceOs_tModeApp                  tModeAppDefault;
         Type_SwcServiceEcuM_stInfoTargetShutdown    stInfoTargetShutdownDefault;
         Type_CfgSwcServiceEcuM_stRefCfgModules      stRefCfgModules;
   const Type_CfgSwcServiceEcuM_stListRefsPncWakeup* pcstListRefsPncWakeup;
         uint8                                       au8HashPostBuild[CfgSwcServiceEcuM_dLenHash];
}Type_CfgSwcServiceEcuM_st;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/
extern CONSTP2CONST(Type_CfgSwcServiceEcuM_st, AUTOMATIC,ECUM_CONST) CfgSwcServiceEcuM_capst[CfgSwcServiceEcuM_dNumConfigSet];

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern P2CONST(Type_CfgSwcServiceEcuM_st, SWCSERVICEECUM_VAR, SWCSERVICEECUM_CONFIG_DATA) SwcServiceEcuM_pcstCfg; //TBD: Move to right header

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

