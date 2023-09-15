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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#if !defined(PDUR_DEV_ERROR_DETECT)
#define PDUR_DEV_ERROR_DETECT                                          (STD_OFF)
#endif

#if !defined(PDUR_VERSION_INFO_API)
#define PDUR_VERSION_INFO_API                                          (STD_OFF)
#endif

#if !defined(PDUR_ZERO_COST_OPERATION)
#define PDUR_ZERO_COST_OPERATION                                       (STD_OFF)
#endif

#if !defined(PDUR_IFGATEWAY_SUPPORT)
#define PDUR_IFGATEWAY_SUPPORT                                         (STD_OFF)
#endif

#if !defined(PDUR_TPGATEWAY_SUPPORT)
#define PDUR_TPGATEWAY_SUPPORT                                         (STD_OFF)
#endif

#define PDUR_RPGID_NULL                                                      (0)

#if !defined(PDUR_DISABLE_MULTICAST_SUPPORT)
#define PDUR_DISABLE_MULTICAST_SUPPORT                                       (1)
#endif

#if !defined(PDUR_MULTICAST_TO_IF_SUPPORT)
#define PDUR_MULTICAST_TO_IF_SUPPORT                                         (0)
#endif

#if !defined(PDUR_MULTICAST_TO_TP_SUPPORT)
#define PDUR_MULTICAST_TO_TP_SUPPORT                                         (0)
#endif

#define PDUR_CONFIGURATION_ID                                                (0)
#define PDUR_FIFO_IF_MAXSIZE                                                 (1)

#if !defined(PDUR_MULTICAST_FROM_TP_SUPPORT)
#define PDUR_MULTICAST_FROM_TP_SUPPORT                                       (0)
#endif

#if !defined(PDUR_MODE_DEPENDENT_ROUTING)
#define PDUR_MODE_DEPENDENT_ROUTING                                          (0)
#endif

#if !defined(PDUR_DEFAULT_VALUE_SUPPORT)
#define PDUR_DEFAULT_VALUE_SUPPORT                                           (0)
#endif

#define COM_PDURBSWMODNAME                                                  (0u)
#define PDUR_NULL_BSWMODNAME                                                 255
#define PDUR_NULL_PDUID                                                        0
#define PDUR_TPTHRESHOLD_DEFVALUE                                        0xFFFFu
#define PDUR_NULL_MOD                                                      FALSE

#if !defined(PDUR_DEM_INIT_FAILED)
#define PDUR_DEM_INIT_FAILED                                                 (0)
#endif

#if !defined(PDUR_DEM_PDU_INSTANCE_LOST)
#define PDUR_DEM_PDU_INSTANCE_LOST                                           (0)
#endif

#define PDUR_DSM_REINT_SUPPORT                                           STD_OFF

#if !defined(PDUR_CANTP_RXIND_BASE)
#define PDUR_CANTP_RXIND_BASE                     (PDUR_BASE_LOTP(0,LoTpRxToUp))
#endif
#if !defined(PDUR_CANTP_TXCONF_BASE)
#define PDUR_CANTP_TXCONF_BASE                    (PDUR_BASE_LOTP(0,LoTpTxToUp))
#endif
#if !defined(PDUR_NR_VALID_CANTPTPRXTOUP_IDS)
#define PDUR_NR_VALID_CANTPTPRXTOUP_IDS (PDUR_BASE_LOTP(0,LoTpRxToUp_NrEntries))
#endif
#if !defined(PDUR_NR_VALID_CANTPTPTXTOUP_IDS)
#define PDUR_NR_VALID_CANTPTPTXTOUP_IDS (PDUR_BASE_LOTP(0,LoTpTxToUp_NrEntries))
#endif

#if !defined(PDUR_CANIF_RXIND_BASE)
#define PDUR_CANIF_RXIND_BASE                    (PDUR_BASE_LOIFD(0,LoIfRxToUp))
#endif
#if !defined(PDUR_CANIF_TXCONF_BASE)
#define PDUR_CANIF_TXCONF_BASE                   (PDUR_BASE_LOIFD(0,LoIfTxToUp))
#endif
#if !defined(PDUR_NR_VALID_CANIFIFRXTOUP_IDS)
#define PDUR_NR_VALID_CANIFIFRXTOUP_IDS (PDUR_BASE_LOIFD(0,LoIfRxToUp_NrEntries))
#endif
#if !defined(PDUR_NR_VALID_CANIFIFTXTOUP_IDS)
#define PDUR_NR_VALID_CANIFIFTXTOUP_IDS (PDUR_BASE_LOIFD(0,LoIfTxToUp_NrEntries))
#endif

#if !defined(PDUR_DCM_TX_BASE)
#define PDUR_DCM_TX_BASE                              (PDUR_BASE_UPTP(0,UpToLo))
#endif

#if !defined(PDUR_DCM_MC_TX_BASE)
#define PDUR_DCM_MC_TX_BASE                         (PDUR_BASE_UPTP(0,UpToLoMc))
#endif

#if !defined(PDUR_NR_VALID_DCM_IDS)
#define PDUR_NR_VALID_DCM_IDS               (PDUR_BASE_UPTP(0,UpToLo_NrEntries))
#endif
#if !defined(PDUR_COM_TX_BASE)
#define PDUR_COM_TX_BASE                              (PDUR_BASE_UPIF(0,UpToLo))
#endif
#if !defined(PDUR_COM_MC_TX_BASE)
#define PDUR_COM_MC_TX_BASE                         (PDUR_BASE_UPIF(0,UpToLoMc))
#endif
#if !defined(PDUR_NR_VALID_COM_IDS)
#define PDUR_NR_VALID_COM_IDS               (PDUR_BASE_UPIF(0,UpToLo_NrEntries))
#endif

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

