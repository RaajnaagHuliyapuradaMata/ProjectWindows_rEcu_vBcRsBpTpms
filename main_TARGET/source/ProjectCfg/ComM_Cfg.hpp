#pragma once
/******************************************************************************/
/* File   : ComM_Cfg.hpp                                                      */
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
#include "ComM_Types.hpp"
#include "Rte_ComM_Type.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define COMM_ECUC_RB_RTE_IN_USE                                          STD_OFF
#define COMM_MODULE_ID                                                       12u
#define COMM_VENDOR_ID                                                        6u
#define COMM_AR_RELEASE_MAJOR_VERSION                                         4u
#define COMM_AR_RELEASE_MINOR_VERSION                                         2u
#define COMM_AR_RELEASE_REVISION_VERSION                                      2u
#define COMM_SW_MAJOR_VERSION                                                 5u
#define COMM_SW_MINOR_VERSION                                                 4u
#define COMM_SW_PATCH_VERSION                                                 0u

#define COMM_VARIANT_PRECOMPILE                                             0x00
#define COMM_VARIANT_POSTBUILD_LOADABLE                                     0x01
#define COMM_CONFIGURATION_VARIANT                       COMM_VARIANT_PRECOMPILE
#define ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel ((NetworkHandleType)0)
#define ComMConf_ComMUser_ComMUser_Can_Network_Channel         ((Type_SwcServiceComM_tUserHandle)(0))

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

