

#ifndef DCMDSPUDS_CDTCS_PROT_H
#define DCMDSPUDS_CDTCS_PROT_H

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
#include "Dem.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.h"
extern VAR( boolean, DCM_VAR )  Dcm_DspCDTCStatus_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

extern FUNC(boolean,DCM_CODE) Dcm_ControlDtcSettingModecheck_b (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) NegRespCode_u8);
extern FUNC(void,DCM_CODE) Dcm_CDTCModeStatusCheck(void);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
#endif

