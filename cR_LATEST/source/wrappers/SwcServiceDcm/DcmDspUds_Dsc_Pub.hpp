

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
Dcm_Dsp_Session_t;
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

extern FUNC(void, DCM_CODE) Dcm_Lok_DspDscConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
   											   );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern CONST(Dcm_Dsp_Session_t, DCM_CONST) Dcm_Dsp_Session[DCM_CFG_DSP_NUMSESSIONS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

extern FUNC(void, DCM_CODE) Dcm_GetP2Timings(
                                                P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) dP2Timing_pu32
   ,     P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) dP2StarTiming_pu32
   ,     VAR(Dcm_SesCtrlType, AUTOMATIC) dSessionId
                                            );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
#endif
