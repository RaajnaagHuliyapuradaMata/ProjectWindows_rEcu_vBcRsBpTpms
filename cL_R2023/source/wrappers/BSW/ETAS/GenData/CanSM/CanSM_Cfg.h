

#ifndef CANSM_CFG_H
#define CANSM_CFG_H

#define CANSM_VENDOR_ID                                6u

#define CANSM_MODULE_ID                                140u

#define CANSM_AR_RELEASE_MAJOR_VERSION                 4u

#define CANSM_AR_RELEASE_MINOR_VERSION                 2u

#define CANSM_AR_RELEASE_REVISION_VERSION              2u

#define CANSM_SW_MAJOR_VERSION                         9u

#define CANSM_SW_MINOR_VERSION                         0u

#define CANSM_SW_PATCH_VERSION                         0u

 #include "Dem.h"
 #if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != CANSM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define CANSM_DEV_ERROR_DETECT                              (STD_OFF)

#define CANSM_VERSION_INFO_API                              (STD_OFF)

#define CANSM_MAINFUNCTION_CYCLE_TIME                   0.01

#define CANSM_SET_BAUDRATE_API                          STD_OFF

#define CANSM_BOR_TX_CONFIRMATION_POLLING               STD_OFF

#define CANSM_VARIANT_PRE_COMPILE                       1

#define CANSM_VARIANT_POSTBUILD_SELECTABLE              2

#define CANSM_VARIANT_INFO                                CANSM_VARIANT_PRE_COMPILE

#define CANSM_CALIBRATION                         STD_OFF

#define CANSM_ECUC_RB_RTE_IN_USE                         STD_OFF

#define CANSM_TX_OFFLINE_ACTIVE_SUPPORT              STD_OFF

#define CANSM_DSM_REINIT_ENABLED           STD_OFF

#define CANSM_NUM_CAN_NETWORKS    1u

#define CANSM_NUM_CAN_CONTROLLERS  1u

#define CANSM_PN_SUPPORT_CONFIGD             STD_OFF

#define CANSM_CFG_TRCV_CANIF_SUPPORT       STD_OFF

#define CANSM_GETBUSOFFDELAY_SUPPORT         STD_OFF

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"

extern const uint8 CanSM_NetworkId_LUT[1][CANSM_NUM_CAN_NETWORKS];

#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"

#define CanSM_Config CanSM_ConfigSet[0]

#endif
