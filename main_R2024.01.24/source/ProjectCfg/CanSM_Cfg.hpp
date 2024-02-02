#pragma once
/******************************************************************************/
/* File   : CanSM_Cfg.hpp                                                     */
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
#define CANSM_VENDOR_ID                                                       1u
#define CANSM_MODULE_ID                                                     140u
#define CANSM_AR_RELEASE_MAJOR_VERSION                                        4u
#define CANSM_AR_RELEASE_MINOR_VERSION                                        2u
#define CANSM_AR_RELEASE_REVISION_VERSION                                     2u
#define CANSM_SW_MAJOR_VERSION                                                9u
#define CANSM_SW_MINOR_VERSION                                                0u
#define CANSM_SW_PATCH_VERSION                                                0u

#include "Dem.hpp"

#define CANSM_DEV_ERROR_DETECT                                           STD_OFF
#define CANSM_VERSION_INFO_API                                           STD_OFF
#define CANSM_MAINFUNCTION_CYCLE_TIME                                       0.01
#define CANSM_SET_BAUDRATE_API                                           STD_OFF
#define CANSM_BOR_TX_CONFIRMATION_POLLING                                STD_OFF
#define CANSM_VARIANT_PRE_COMPILE                                              1
#define CANSM_VARIANT_POSTBUILD_SELECTABLE                                     2
#define CANSM_VARIANT_INFO                             CANSM_VARIANT_PRE_COMPILE
#define CANSM_CALIBRATION                                                STD_OFF
#define CANSM_ECUC_RB_RTE_IN_USE                                         STD_OFF
#define CANSM_TX_OFFLINE_ACTIVE_SUPPORT                                  STD_OFF
#define CANSM_DSM_REINIT_ENABLED                                         STD_OFF
#define CANSM_NUM_CAN_NETWORKS                                                1u
#define CANSM_NUM_CAN_CONTROLLERS                                             1u
#define CANSM_PN_SUPPORT_CONFIGD                                         STD_OFF
#define CANSM_CFG_TRCV_CANIF_SUPPORT                                     STD_OFF
#define CANSM_GETBUSOFFDELAY_SUPPORT                                     STD_OFF

extern CONST(uint8, CANSM_CONST) CanSM_NetworkId_LUT[1][CANSM_NUM_CAN_NETWORKS];


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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

