#pragma once
/******************************************************************************/
/* File   : CfgSwcServiceCanSM.h                                              */
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
#include "ComStack_Types.hpp"
#include "CanSM_Cfg.hpp"

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
   P2CONST(uint8,     TYPEDEF, CANSM_APPL_DATA) Cntrl_startidx_pu8;
   VAR(uint16,     TYPEDEF                 ) BorTimeL1_u16;
   VAR(uint16,     TYPEDEF                 ) BorTimeL2_u16;
   VAR(uint16,     TYPEDEF                 ) BorTimeTxEnsured_u16;
   VAR(Dem_EventIdType,   TYPEDEF                 ) BusOffEventId_uo;
   VAR(uint8,     TYPEDEF                 ) Trcv_hndle_u8;
   VAR(uint8,     TYPEDEF                 ) SizeofController_u8;
   VAR(uint8,     TYPEDEF                 ) BorCntL1L2_u8;
   VAR(NetworkHandleType, TYPEDEF                 ) ComM_channelId_uo;
   VAR(boolean,     TYPEDEF                 ) BusOffDelayConfig_b;
   VAR(boolean,     TYPEDEF                 ) TrcvPnConfig_b;
}CanSM_NetworkConf_tst;

typedef struct{
   P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST)           CanSM_NetworkConf_pcst;
   P2CONST(uint8,     AUTOMATIC, SWCSERVICECANSM_CONST) CanSM_NetworktoCtrlConf_pcu8;
     CONST(uint16,     SWCSERVICECANSM_CONST) CanSMModeRequestRepetitionTime_u16;
     CONST(uint8,     SWCSERVICECANSM_CONST) CanSMModeRequestRepetitionMax_u8;
       VAR(uint8,     SWCSERVICECANSM_VAR)   CanSM_SizeOfCanSMNetworks_u8;
       VAR(uint8,     SWCSERVICECANSM_VAR)   CanSM_ActiveConfigset_u8;
}Type_CfgSwcServiceCanSM_st;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
extern CONST(Type_CfgSwcServiceCanSM_st, CANSM_CONST) CfgSwcServiceCanSM_castConfigSet[];

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern P2CONST(Type_CfgSwcServiceCanSM_st, CANSM_VAR, CANSM_APPL_CONST) CfgSwcServiceCanSM_castConfigSet_pcst;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

