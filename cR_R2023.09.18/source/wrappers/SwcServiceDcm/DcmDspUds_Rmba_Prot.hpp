

#ifndef DCMDSPUDS_RMBA_PROT_H
#define DCMDSPUDS_RMBA_PROT_H

#if(DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Memaddress_Calc_Prot.hpp"

typedef struct{
   uint32 dataReadMemoryRangeLow_u32;
   uint32 dataReadMemoryRangeHigh_u32;
   uint32 dataAllowedSecRead_u32;
   uint32 dataAllowedSessRead_u32;
   P2FUNC(Std_ReturnType,TYPEDEF,adrUserMemReadModeRule_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8,VAR(uint32,AUTOMATIC) adrMemoryAddress_u32,VAR(uint32,AUTOMATIC) dataDataLength_u32,VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en);
#if(DCM_CFG_DSP_MODERULEFORREADMEMORY != DCM_CFG_OFF)
   P2FUNC(boolean,TYPEDEF,addrRmbaModeRuleChkFnc_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8);
#endif
   uint8 dataMemoryValue_u8;
}Dcm_RMBAConfig_tst;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern CONST(Dcm_RMBAConfig_tst, DCM_CONST) Dcm_RMBAConfig_cast [];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(uint16,DCM_CODE) Dcm_RmbacalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif

#endif

