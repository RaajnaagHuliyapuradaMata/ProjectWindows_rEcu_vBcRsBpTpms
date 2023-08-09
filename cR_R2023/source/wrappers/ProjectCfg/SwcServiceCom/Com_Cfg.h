#ifndef COM_CFG_H
#define COM_CFG_H

#include "Com_Cfg_SymbolicNames.h"
#include "CfgSwcServiceCom.h"

#define COM_MODULE_ID                                                   50u
#define COM_VENDOR_ID                                                   6u
#define COM_AR_RELEASE_MAJOR_VERSION                                    4u
#define COM_AR_RELEASE_MINOR_VERSION                                    2u
#define COM_AR_RELEASE_REVISION_VERSION                                 2u
#define COM_SW_MAJOR_VERSION                                            6u
#define COM_SW_MINOR_VERSION                                            0u
#define COM_SW_PATCH_VERSION                                            0u
#define COM_NUM_ARR_IPDUGRPVECT    1u
#define COM_ECUC_RB_RTE_IN_USE  ( STD_OFF )

typedef uint16 Com_SignalIdType;
typedef uint16 Com_SignalGroupIdType;
typedef uint16 Com_IpduGroupIdType;
typedef uint8  Com_IpduGroupVector[COM_NUM_ARR_IPDUGRPVECT];
typedef uint8  Com_IpduIdType;
typedef uint8  Com_GrpSignalIdType;

typedef enum{
      COM_UNINIT
   ,  COM_INIT
}Com_StatusType;

#endif
