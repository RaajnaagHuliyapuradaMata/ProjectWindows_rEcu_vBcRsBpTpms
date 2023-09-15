

#ifndef DCMDSPUDS_DSC_PUB_H
#define DCMDSPUDS_DSC_PUB_H

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)

typedef enum{
    DCM_NO_BOOT = 0
   ,   DCM_OEM_BOOT
   ,   DCM_SYS_BOOT
}Dcm_SessionForBootType;

typedef struct{
   uint32                   P2_max_u32;
   uint32                   P2str_max_u32;
    Dcm_SesCtrlType          session_level;
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
   Rte_ModeType_DcmDiagnosticSessionControl SessionMode;
#endif
    Dcm_SessionForBootType   sessionForBoot;
}
Type_CfgSwcServiceDcm_Session;
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

extern void Dcm_Lok_DspDscConfirmation(
   Dcm_IdContextType dataIdContext_u8
   ,  PduIdType dataRxPduId_u8
   ,  uint16 dataSourceAddress_u16
   ,  Dcm_ConfirmationStatusType status_u8
   											   );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern const Type_CfgSwcServiceDcm_Session CfgSwcServiceDcm_astListSession[DCM_CFG_DSP_NUMSESSIONS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

extern void Dcm_GetP2Timings(
                                                uint32 * dP2Timing_pu32
   ,                                               uint32 * dP2StarTiming_pu32
   ,                                               Dcm_SesCtrlType dSessionId
                                            );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
#endif
