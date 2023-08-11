

#ifndef  COMM_CFG_H
#define  COMM_CFG_H

#include "ComM_Types.h"
#include "Rte_ComM_Type.h"

#define COMM_MODULE_ID                 12u

#define COMM_VENDOR_ID                 6u

#define COMM_AR_RELEASE_MAJOR_VERSION             4u

#define COMM_AR_RELEASE_MINOR_VERSION             2u

#define COMM_AR_RELEASE_REVISION_VERSION          2u

#define COMM_SW_MAJOR_VERSION          9u

#define COMM_SW_MINOR_VERSION          0u

#define COMM_SW_PATCH_VERSION          0u

#define COMM_VARIANT_PRECOMPILE                                         0x00

#define COMM_VARIANT_POSTBUILD_LOADABLE                                 0x01

#define COMM_CONFIGURATION_VARIANT                                      COMM_VARIANT_PRECOMPILE

#define COMM_ECUC_RB_RTE_IN_USE                                         STD_OFF

#define         ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel       ((NetworkHandleType)0)

#define     ComMConf_ComMUser_ComMUser_Can_Network_0_Channel        ((ComM_UserHandleType)(0))

#endif
