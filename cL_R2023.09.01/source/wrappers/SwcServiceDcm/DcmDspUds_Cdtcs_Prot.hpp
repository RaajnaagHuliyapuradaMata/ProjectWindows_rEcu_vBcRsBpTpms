

#ifndef DCMDSPUDS_CDTCS_PROT_H
#define DCMDSPUDS_CDTCS_PROT_H

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
#include "Dem.hpp"
#define DCM_START_SEC_VAR_INIT_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern boolean Dcm_DspCDTCStatus_b;
#define DCM_STOP_SEC_VAR_INIT_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

extern boolean Dcm_ControlDtcSettingModecheck_b (Dcm_NegativeResponseCodeType * NegRespCode_u8);
extern void Dcm_Lok_Cdtcs_Mainfunction(void);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
#endif

