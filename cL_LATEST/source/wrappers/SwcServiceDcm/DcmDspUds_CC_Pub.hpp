

#ifndef DCMDSPUDS_CC_PUB_H
#define DCMDSPUDS_CC_PUB_H

#if(DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)

typedef struct{
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
   Std_ReturnType (*switch_fp) (Dcm_CommunicationModeType Dcm_stCommunicationMode );
   boolean (*checkmode_fp) (void);
#endif
   NetworkHandleType 						SpecificSubNetId_u8;
   uint8   								SpecificComMChannelId;
}Dcm_Dsld_SpecificSubnetInfo;

typedef struct{
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
   Std_ReturnType (*switch_fp) (Dcm_CommunicationModeType Dcm_stCommunicationMode );
   boolean (*checkmode_fp) (void);
#endif

   uint8   AllComMChannelId;
}Dcm_Dsld_AllChannelsInfoType;

#if( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern const Dcm_Dsld_SpecificSubnetInfo Dcm_specific_subnet_table[DCM_CFG_NUM_SPECIFIC_SUBNETS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern const Dcm_Dsld_AllChannelsInfoType Dcm_AllChannels_ForModeInfo[DCM_CFG_NUM_ALLCHANNELS_MODE_INFO];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_MODERULEFORCC != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern boolean (*Dcm_ComMReEnableModeRuleRef) (Dcm_NegativeResponseCodeType * Nrc_u8);

#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern Std_ReturnType (*Dcm_ComMUserReEnableModeRuleRef) (void);
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#endif

