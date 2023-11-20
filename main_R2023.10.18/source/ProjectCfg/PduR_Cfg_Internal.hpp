#pragma once
/******************************************************************************/
/* File   : PduR_Cfg_Internal.hpp                                             */
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
#include "ComStack_Types.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define PDUR_DEV_ERROR_DETECT                                            STD_OFF
#define PDUR_VERSION_INFO_API                                            STD_OFF
#define PDUR_ZERO_COST_OPERATION                                         STD_OFF
#define PDUR_IFGATEWAY_SUPPORT                                           STD_OFF
#define PDUR_TPGATEWAY_SUPPORT                                           STD_OFF
#define PDUR_RPGID_NULL                                                        0
#define PDUR_DISABLE_MULTICAST_SUPPORT                                         1
#define PDUR_MULTICAST_TO_IF_SUPPORT                                           0
#define PDUR_STORE_AND_FORWARD                                                 0
#define PDUR_CONFIGURATION_ID                                                  0
#define PDUR_MULTICAST_FROM_TP_SUPPORT                                         0
#define PDUR_MODE_DEPENDENT_ROUTING                                            0
#define PDUR_DEFAULT_VALUE_SUPPORT                                             0
#define COM_PDURBSWMODNAME                                                    0u
#define PDUR_NULL_BSWMODNAME                                                 255
#define PDUR_NULL_PDUID                                                        0
#define PDUR_TPTHRESHOLD_DEFVALUE                                        0xFFFFu
#define PDUR_NULL_MOD                                                      FALSE
#define PDUR_CANTP_CHANGE_PARAMETER_SUPPORT                                    0
#define PDUR_FRTP_CHANGE_PARAMETER_SUPPORT                                     0
#define PDUR_CHANGE_PARAMETER_SUPPORT                                          0
#define PDUR_DEM_INIT_FAILED                                                   0
#define PDUR_DEM_PDU_INSTANCE_LOST                                             0
#define PDUR_DSM_REINT_SUPPORT                                           STD_OFF
#define PDUR_CANTP_RXIND_BASE           (PDUR_BASE_LOTP(0,LoTpRxToUp))
#define PDUR_CANTP_TXCONF_BASE          (PDUR_BASE_LOTP(0,LoTpTxToUp))
#define PDUR_NR_VALID_CANTPTPRXTOUP_IDS (PDUR_BASE_LOTP(0,LoTpRxToUp_NrEntries))
#define PDUR_NR_VALID_CANTPTPTXTOUP_IDS (PDUR_BASE_LOTP(0,LoTpTxToUp_NrEntries))
#define PDUR_CANIF_RXIND_BASE           (PDUR_BASE_LOIFD(0,LoIfRxToUp))
#define PDUR_CANIF_TXCONF_BASE          (PDUR_BASE_LOIFD(0,LoIfTxToUp))
#define PDUR_DCM_TX_BASE                (PDUR_BASE_UPTP(0,UpToLo))
#define PDUR_COM_TX_BASE                (PDUR_BASE_UPIF(0,UpToLo))
#define PDUR_COM_MC_TX_BASE             (PDUR_BASE_UPIF(0,UpToLoMc))
#define TableSize_PduR_CddCfg                                                  0
#define TableSize_PduR_LoTpRxCfg                                               1
#define TableSize_PduR_LoTpTxCfg                                               1
#define TableSize_PduR_LoIfRxDCfg                                              1
#define TableSize_PduR_LoIfTxDCfg                                              1
#define TableSize_PduR_LoIfRxTTCfg                                             0
#define TableSize_PduR_LoIfTxTTCfg                                             0
#define TableSize_PduR_UpTpCfg                                                 1

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

