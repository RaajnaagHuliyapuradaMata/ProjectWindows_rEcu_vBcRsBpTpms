/******************************************************************************/
/* File   : FiM_Cfg_PbCfg.c                                                   */
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

#include "FiM_Cfg_PbCfg.hpp"
#include "FiM_Priv_Data.hpp"

#include "CfgSwcServiceFiM.hpp"

#define FIM_START_SEC_ROM_CONST
#include "FiM_MemMap.hpp"
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
static const FiM_NumOffsetEventType FiM_Cfg_NumOffsetEvent_auo[FIM_CFG_NUMBEROFDEMEVENTIDS+2] = {
      0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  1
};

static const FiM_NumOffsetComponentType FiM_Cfg_NumOffsetComponent_auo[FIM_CFG_NUMBEROFDEMCOMPONENTIDS+2] = {
      0
   ,  0
   ,  0
   ,  0
   ,  0
   ,  1
   ,  1
   ,  1
};

#define FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC    (1)
static const FiM_FunctionIdType FiM_CfgInhibitSourceMatrix_au16[FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC] = {
   FiMConf_FiMFID_FiMFID_0
};

static const FiM_InhibitionMaskType FiM_CfgInhibitMaskMatrix_au16[FIM_CFG_MAX_TOTAL_LINKS_EVENT_CALC] = {
   FIM_CFG_LAST_FAILED
};

static const FiM_FunctionIdType FiM_CfgInhibitSourceMatrixComponent_au16[FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC] = {
   FiMConf_FiMFID_FiMFID_0
};

const Type_CfgSwcServiceFiM_st FiMConfigSet = {
      FiM_Cfg_NumOffsetEvent_auo
   ,  FiM_CfgInhibitSourceMatrix_au16
   ,  FiM_CfgInhibitMaskMatrix_au16
   ,  FiM_Cfg_NumOffsetComponent_auo
   ,  FiM_CfgInhibitSourceMatrixComponent_au16
};
#define FIM_STOP_SEC_ROM_CONST
#include "FiM_MemMap.hpp"

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

