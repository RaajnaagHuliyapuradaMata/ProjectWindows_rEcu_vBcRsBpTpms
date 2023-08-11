#ifndef PDUR_CFG_H
#define PDUR_CFG_H

#include "ComStack_Types.h"
#include "PduR_Cfg_SymbolicNames.h"

#define AUTOSAR_VERSION_AR42                   STD_ON

#define PDUR_VENDOR_ID            6u

#define PDUR_MODULE_ID            51u

#define PDUR_SW_MAJOR_VERSION     9u

#define PDUR_SW_MINOR_VERSION     0u

#define PDUR_SW_PATCH_VERSION     0u

#define PDUR_ENABLE_INTER_MODULE_CHECKS                         FALSE

#if !defined(PDUR_CANIF_SUPPORT)
#define PDUR_CANIF_SUPPORT    (1)
#endif

#if !defined(PDUR_CANNM_SUPPORT)
#define PDUR_CANNM_SUPPORT    (0)
#endif

#if !defined(PDUR_UDPNM_SUPPORT)
#define PDUR_UDPNM_SUPPORT    (0)
#endif

#if !defined(PDUR_CANTP_SUPPORT)
#define PDUR_CANTP_SUPPORT    (1)
#endif

#if !defined(PDUR_FRIF_SUPPORT)
#define PDUR_FRIF_SUPPORT    (0)
#endif

#if !defined(PDUR_FRNM_SUPPORT)
#define PDUR_FRNM_SUPPORT    (0)
#endif

#if !defined(PDUR_FRTP_SUPPORT)
#define PDUR_FRTP_SUPPORT    (0)
#endif

#if !defined(PDUR_FRARTP_SUPPORT)
#define PDUR_FRARTP_SUPPORT    (0)
#endif

#if !defined(PDUR_LINIF_SUPPORT)
#define PDUR_LINIF_SUPPORT    (0)
#endif

#if !defined(PDUR_LINTP_SUPPORT)
#define PDUR_LINTP_SUPPORT    (0)
#endif

#if !defined(PDUR_SOADIF_SUPPORT)
#define PDUR_SOADIF_SUPPORT    (0)
#endif

#if !defined(PDUR_J1939TP_SUPPORT)
#define PDUR_J1939TP_SUPPORT    (0)
#endif

#if !defined(PDUR_SOADTP_SUPPORT)
#define PDUR_SOADTP_SUPPORT    (0)
#endif

#if !defined(PDUR_DOIP_SUPPORT)
#define PDUR_DOIP_SUPPORT    (0)
#endif

#if !defined(PDUR_COM_SUPPORT)
#define PDUR_COM_SUPPORT    (1)
#endif

#if !defined(PDUR_J1939RM_SUPPORT)
#define PDUR_J1939RM_SUPPORT    (0)
#endif

#if !defined(PDUR_J1939DCM_SUPPORT)
#define PDUR_J1939DCM_SUPPORT    (0)
#endif

#if !defined(PDUR_IPDUM_SUPPORT)
#define PDUR_IPDUM_SUPPORT    (0)
#endif

#if !defined(PDUR_SECOC_SUPPORT)
#define PDUR_SECOC_SUPPORT    (0)
#endif

#if !defined(PDUR_SOMEIPTP_SUPPORT)
#define PDUR_SOMEIPTP_SUPPORT    (0)
#endif

#if !defined(PDUR_DCM_SUPPORT)
#define PDUR_DCM_SUPPORT    (1)
#endif

#if !defined(PDUR_DLT_SUPPORT)
#define PDUR_DLT_SUPPORT    (0)
#endif

#if !defined(PDUR_LDCOM_SUPPORT)
#define PDUR_LDCOM_SUPPORT    (0)
#endif

#define PDUR_ECUC_RB_RTE_IN_USE  ( STD_OFF )

#if !defined(PDUR_COM_CANCELRX_SUPPORT)
#define PDUR_COM_CANCELRX_SUPPORT   0
#endif

#define PDUR_MAX_QUEUEDEPTH (1)

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"

    extern const Type_CfgSwcServicePduR_st PduR_Config;

#if ( PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE )
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#else
#define PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#endif

#include "PduR_MemMap.h"
#endif

