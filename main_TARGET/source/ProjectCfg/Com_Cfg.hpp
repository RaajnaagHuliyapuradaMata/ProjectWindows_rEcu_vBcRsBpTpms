#pragma once
/******************************************************************************/
/* File   : Com_Cfg.hpp                                                       */
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
#include "Com_Cfg_SymbolicNames.hpp"
#include "CfgSwcServiceCom.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define COM_MODULE_ID                                                        50u
#define COM_VENDOR_ID                                                         6u
#define COM_AR_RELEASE_MAJOR_VERSION                                          4u
#define COM_AR_RELEASE_MINOR_VERSION                                          2u
#define COM_AR_RELEASE_REVISION_VERSION                                       2u
#define COM_SW_MAJOR_VERSION                                                  6u
#define COM_SW_MINOR_VERSION                                                  0u
#define COM_SW_PATCH_VERSION                                                  0u
#define COM_NUM_ARR_IPDUGRPVECT                                               1u
#define COM_ECUC_RB_RTE_IN_USE                                           STD_OFF

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint16 Com_SignalIdType;
typedef uint16 Com_SignalGroupIdType;
typedef uint16 Com_IpduGroupIdType;
typedef uint8  Com_IpduGroupVector[COM_NUM_ARR_IPDUGRPVECT];
typedef uint8  Type_CfgSwcServiceCom_tIdIPdu;
typedef uint8  Com_GrpSignalIdType;

typedef enum{
      COM_UNINIT
   ,  COM_INIT
}Com_StatusType;

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

