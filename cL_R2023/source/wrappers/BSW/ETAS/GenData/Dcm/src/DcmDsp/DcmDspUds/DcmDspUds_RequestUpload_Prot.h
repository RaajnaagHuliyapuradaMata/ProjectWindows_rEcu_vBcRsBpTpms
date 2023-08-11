

#ifndef DCMDSPUDS_REQUESTUPLOAD_PROT_H
#define DCMDSPUDS_REQUESTUPLOAD_PROT_H

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)

typedef struct{
	uint32 dataRequestUploadMemoryRangeLow_u32;		
	uint32 dataRequestUploadMemoryRangeHigh_u32;	
	uint32 dataAllowedSec_u32;
	uint8  dataMemoryValue_u8;				
} Dcm_RequestUploadConfig_tst;

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_RequestUploadConfig_tst Dcm_RequestUploadConfig_cast [];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern uint16 Dcm_RequestUploadCalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif

#endif
#endif
