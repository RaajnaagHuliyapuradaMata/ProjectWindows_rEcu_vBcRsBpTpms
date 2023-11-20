#pragma once
/******************************************************************************/
/* File   : CfgMcalMcu.h                                                      */
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
#define CFGMCALMCU_AR_RELEASE_MAJOR_VERSION                                    4
#define CFGMCALMCU_AR_RELEASE_MINOR_VERSION                                    2

#define CFGMCALMCU_RESF_SOFT_RESET                                        (1<<0)
#define CFGMCALMCU_RESF_WD0_RESET                                         (1<<1)
#define CFGMCALMCU_RESF_WD1_RESET                                         (1<<2)
#define CFGMCALMCU_WUP_FACTOR_CAN                                         (1<<5)
#define CFGMCALMCU_WUP_FACTOR_TJA_ERR                                     (1<<6)
#define CFGMCALMCU_RESF_POWER_ON_RESET                                    (1<<9)
#define CFGMCALMCU_RESF_DEEPSTOP_RESET                                   (1<<10)
#define CFGMCALMCU_WUP_FACTOR_TAUJ00                                     (1<<15)
#define CFGMCALMCU_WUP_FACTOR_TAUJ01                                     (1<<16)
#define CFGMCALMCU_WUP_FACTOR_TAUJ02                                     (1<<17)
#define CFGMCALMCU_WUP_FACTOR_TAUJ03                                     (1<<18)

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
extern void ApplMcu_vDeepStop          (void);
extern void ApplMcu_vShutdown          (void);
extern void ApplMcu_vCheckWakeupSource (void);
extern void ApplMcu_vPerformReset      (void);
extern void ApplMcu_vReleaseIoBuffers  (void);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

