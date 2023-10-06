/******************************************************************************/
/* File   : CanSM_PBcfg.c                                                     */
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
#include "Std_Types.hpp"

#include "Types_SwcServiceComM.hpp"

#include "CanSM_Prv.hpp"

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
#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.hpp"
       CONST(uint8, CANSM_CONST) CanSM_NetworkId_LUT[1][CANSM_NUM_CAN_NETWORKS] = {{0}};
       CONST(uint8, CANSM_CONST) CanSM_NetworktoCtrl_Config_acu8[] = {0};
static CONST(uint8, CANSM_VAR)   CanSM_Ctrl_CanSMManagerNetwork_Can_Network_Config_au8[] = {
   CanIfConf_CanIfCtrlCfg_Can_Network_CANNODE_0
};
#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.hpp"
CONST(CanSM_NetworkConf_tst, CANSM_CONST) CanSM_Network_Config_acst[] = {
   {
         CanSM_Ctrl_CanSMManagerNetwork_Can_Network_Config_au8
      ,  4u
      ,  10u
      ,  2u
      ,  DemConf_DemEventParameter_DemEventParameter_CanBusoffError
      ,  255
      ,  1
      ,  0
      ,  0
      ,  FALSE
      ,  FALSE 
   }
};

CONST(Type_CfgSwcServiceCanSM_st, CANSM_CONST) CfgSwcServiceCanSM_castConfigSet[] = {
   {
         CanSM_Network_Config_acst
      ,  CanSM_NetworktoCtrl_Config_acu8
      ,  7
      ,  5
      ,  CANSM_NUM_CAN_NETWORKS
      ,  0
   }
};

#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.hpp"

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
