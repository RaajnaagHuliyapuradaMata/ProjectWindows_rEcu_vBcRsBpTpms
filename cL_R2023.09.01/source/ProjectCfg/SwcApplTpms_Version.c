/******************************************************************************/
/* File   : SwcApplTpms_Version.c                                             */
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
#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#pragma PRQA_MESSAGES_OFF 1290,3408
#define APPL_VERSION                    "LMC00003"
#define APPL_VERSION_CST                  "000002"
#define APPL_BUILD_NUMBER                  "00907"
#define APPL_BUILD_TIME_DATE "21.10.2021-14:34:50"
#define APPL_BUILD_CW                          42
#define APPL_BUILD_YEAR                        21
#define APPL_VERSION_CDD                     "21"
#define COMPILER_NAME                        "GHS"
#define COMPILER_VERSION                   "201517"

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
const struct struct_Version g_sHufVersion = {
      APPL_VERSION
   ,  APPL_VERSION_CST
   ,  APPL_VERSION_CDD
   ,  COMPILER_NAME
   ,  COMPILER_VERSION
   ,  APPL_BUILD_TIME_DATE,
};

#define BCM_VERSION                        "Vx.x"
#define BCM_DATE                           "10-Jan-2018"

const struct struct_BCM_Version g_sBCMVersion = {
      BCM_VERSION
   ,  BCM_DATE
};

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void HufIf_GetVersion(struct struct_Version *sVersion){
   *sVersion = g_sHufVersion;
   ClientIf_Debug_GetVersion(sVersion);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

