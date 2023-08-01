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
#include "CfgEcuabCanIf.h"
#include "CfgSwcServiceBswM.h"
#include "CfgSwcServiceCanSM.h"
#include "CfgSwcServiceCanTp.h"
#include "CfgSwcServiceCom.h"
#include "CfgSwcServiceComM.h"
#include "CfgSwcServiceFiM.h"
#include "CfgSwcServicePduR.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ECUM_NO_WKUP_SRC                                             ((uint32)0)
#define CfgSwcServiceEcuM_dLenHash		                                     (16)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint32 Type_SwcServiceOs_tModeApp; //TBD: Move to Types_SwcServiceOs.h

typedef struct{
   const Type_CfgEcuabCanIf_st*      pcstCfgEcuabCanIf;
   const Type_CfgSwcServiceComM_st*  pcstCfgSwcServiceComM;
   const Type_CfgSwcServiceCanSM_st* pcstCfgSwcServiceCanSM;
   const Type_CfgSwcServicePduR_st*  pcstCfgSwcServicePduR;
   const Type_CfgSwcServiceCom_st*   pcstCfgSwcServiceCom;
   const Type_CfgSwcServiceCanTp_st* pcstCfgSwcServiceCanTp;
   const Type_CfgSwcServiceFiM_st*   pcstCfgSwcServiceFiM;
   const Type_CfgSwcServiceBswM_st*  pcstCfgSwcServiceBswM;
}Type_SwcServiceEcuM_stRefCfgModules;

typedef struct{
         uint8  u8NumRefsPncComM;
   const uint8* pcau8ListRefsPnc;
}Type_SwcServiceEcuM_stListRefsPncWakeup;

typedef struct{
         Type_SwcServiceOs_tModeApp               tModeAppDefault;
         Type_SwcServiceEcuM_stInfoTargetShutdown stInfoTargetShutdownDefault;
         Type_SwcServiceEcuM_stRefCfgModules      stRefCfgModules;
   const Type_SwcServiceEcuM_stListRefsPncWakeup* pcstListRefsPncWakeup;
         uint8                                    au8HashPostBuild[CfgSwcServiceEcuM_dLenHash];
}Type_CfgSwcServiceEcuM_st;

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
