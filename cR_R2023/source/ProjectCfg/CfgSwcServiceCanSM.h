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
//   P2CONST(CanSM_NetworkConf_tst, AUTOMATIC,CANSM_CONST) CanSM_NetworkConf_pcst;
/*
#if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
   P2VAR(CanSM_NetworkConf_DEM_tst, AUTOMATIC, CANSM_CONST ) CanSMNetworkConfDEM_pst;
#endif
*/
   P2CONST (uint8, AUTOMATIC, CANSM_CONST ) CanSM_NetworktoCtrlConf_pcu8;
/*
#if(CANSM_GETBUSOFFDELAY_SUPPORT == STD_ON)
   P2FUNC(void, TYPEDEF, User_GetBusOffDelay)(VAR(NetworkHandleType,AUTOMATIC), P2VAR(uint8,AUTOMATIC,CANSM_APPL_CODE));
#endif
*/
   CONST(uint16, CANSM_CONST) CanSMModeRequestRepetitionTime_u16;
   CONST(uint8,  CANSM_CONST) CanSMModeRequestRepetitionMax_u8;
     VAR(uint8,  CANSM_VAR)   CanSM_SizeOfCanSMNetworks_u8;
     VAR(uint8,  CANSM_VAR)   CanSM_ActiveConfigset_u8;
}Type_CfgSwcServiceCanSM_st;

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
