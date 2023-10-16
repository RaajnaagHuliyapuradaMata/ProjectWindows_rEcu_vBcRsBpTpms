/******************************************************************************/
/* File   : EcuM_PBcfg.c                                                      */
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

#include "Types_SwcServiceComM.hpp"

#include "EcuM.hpp"
#include "EcuM_Cfg_Startup.hpp"

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
#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
CONST(Type_CfgSwcServiceEcuM_stListRefsPncWakeup, ECUM_CONST) CfgSwcServiceEcuM_castListRefsPncWakeup[CfgSwcServiceEcuM_dNumSourceWakeup] = {
      {0, NULL_PTR}
   ,  {0, NULL_PTR}
   ,  {0, NULL_PTR}
   ,  {0, NULL_PTR}
   ,  {0, NULL_PTR}
};
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

#define ECUM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"
CONST(Type_CfgSwcServiceEcuM_st, ECUM_CONST) CfgSwcServiceEcuM_cst = {
      OSDEFAULTAPPMODE
   ,  {
            SwcServiceEcuM_eTargetShutdown_OFF
         ,  0
         ,  0
      }
   ,  {
            &CfgEcuabCanIf_st
         ,  NULL_PTR
         ,  &CfgSwcServiceCanSM_castConfigSet[0]
         ,  &CfgSwcServicePduR_cst
         ,  NULL_PTR
         ,  &CfgSwcServiceCanTp_cst
         ,  NULL_PTR
         ,  &CfgSwcServiceBswM_cst
      }
   ,  &CfgSwcServiceEcuM_castListRefsPncWakeup[0]
   ,  {
            0xD4
         ,  0x1D
         ,  0x8C
         ,  0xD9
         ,  0x8F
         ,  0x00
         ,  0xB2
         ,  0x04
         ,  0xE9
         ,  0x80
         ,  0x09
         ,  0x98
         ,  0xEC
         ,  0xF8
         ,  0x42
         ,  0x7E
      }
};

CONSTP2CONST(Type_CfgSwcServiceEcuM_st, AUTOMATIC,ECUM_CONST) CfgSwcServiceEcuM_capst[CfgSwcServiceEcuM_dNumConfigSet] = {
   &CfgSwcServiceEcuM_cst
};
#define ECUM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_Cfg_MemMap.hpp"

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

