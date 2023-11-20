

#ifndef DCMDSPUDS_CC_PUB_H
#define DCMDSPUDS_CC_PUB_H

#if(DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)

typedef struct{
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
   P2FUNC(Std_ReturnType,TYPEDEF,switch_fp)	(VAR(Dcm_CommunicationModeType,AUTOMATIC));
   P2FUNC(boolean,TYPEDEF,checkmode_fp)	(void);
#endif
   NetworkHandleType 						SpecificSubNetId_u8;
   uint8   								SpecificComMChannelId;
}Dcm_Dsld_SpecificSubnetInfo;

typedef struct{
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
   P2FUNC(Std_ReturnType,TYPEDEF,switch_fp)	(VAR(Dcm_CommunicationModeType,AUTOMATIC));
   P2FUNC(boolean,TYPEDEF,checkmode_fp)	(void);
#endif

   uint8   AllComMChannelId;
}Dcm_Dsld_AllChannelsInfoType;

#if( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern CONST (Dcm_Dsld_SpecificSubnetInfo, DCM_CONST) Dcm_specific_subnet_table[DCM_CFG_NUM_SPECIFIC_SUBNETS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern CONST(Dcm_Dsld_AllChannelsInfoType, DCM_CONST) Dcm_AllChannels_ForModeInfo[DCM_CFG_NUM_ALLCHANNELS_MODE_INFO];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_MODERULEFORCC != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern P2FUNC(boolean,DCM_APPL_CODE,Dcm_ComMReEnableModeRuleRef) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8);

#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern P2FUNC(Std_ReturnType,DCM_APPL_CODE,Dcm_ComMUserReEnableModeRuleRef) (void);
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#endif

