#ifndef PDUR_CFG_H
#define PDUR_CFG_H

#include "ComStack_Types.hpp"
#include "PduR_Cfg_SymbolicNames.hpp"
#include "CfgSwcServicePduR.hpp"

#define PDUR_VENDOR_ID            1u
#define PDUR_MODULE_ID            51u
#define PDUR_SW_MAJOR_VERSION     6u
#define PDUR_SW_MINOR_VERSION     0u
#define PDUR_SW_PATCH_VERSION     0u
#define PDUR_CANIF_SUPPORT    (1)
#define PDUR_CANNM_SUPPORT    (0)
#define PDUR_UDPNM_SUPPORT    (0)
#define PDUR_CANTP_SUPPORT    (1)
#define PDUR_FRIF_SUPPORT    (0)
#define PDUR_FRNM_SUPPORT    (0)
#define PDUR_FRTP_SUPPORT    (0)
#define PDUR_LINIF_SUPPORT    (0)
#define PDUR_LINTP_SUPPORT    (0)
#define PDUR_SOADIF_SUPPORT    (0)
#define PDUR_J1939TP_SUPPORT    (0)
#define PDUR_SOADTP_SUPPORT    (0)
#define PDUR_DOIP_SUPPORT    (0)
#define PDUR_COM_SUPPORT    (1)
#define PDUR_J1939RM_SUPPORT    (0)
#define PDUR_J1939DCM_SUPPORT    (0)
#define PDUR_IPDUM_SUPPORT    (0)
#define PDUR_SECOC_SUPPORT    (0)
#define PDUR_DCM_SUPPORT    (1)
#define PDUR_DLT_SUPPORT    (0)
#define PDUR_LDCOM_SUPPORT    (0)
#define PDUR_ECUC_RB_RTE_IN_USE  ( STD_OFF )
#define PDUR_COM_CANCELRX_SUPPORT   0

extern CONST( Type_CfgSwcServicePduR_st, PDUR_CONST) CfgSwcServicePduR_cst;

#endif

