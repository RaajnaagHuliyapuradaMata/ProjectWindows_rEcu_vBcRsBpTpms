

#ifndef DCMDSPUDS_REQUESTDOWNLOAD_PROT_H
#define DCMDSPUDS_REQUESTDOWNLOAD_PROT_H

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)

typedef struct{
	uint32 dataRequestDownloadMemoryRangeLow_u32;		
	uint32 dataRequestDownloadMemoryRangeHigh_u32;	
	uint32 dataAllowedSec_u32;
	uint8  dataMemoryValue_u8;				
} Dcm_RequestDownloadConfig_tst;

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_RequestDownloadConfig_tst Dcm_RequestDownloadConfig_cast [];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern uint16 Dcm_RequestDownloadCalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif

#endif
#endif
