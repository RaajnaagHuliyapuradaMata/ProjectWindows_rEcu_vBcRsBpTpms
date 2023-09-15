

#ifndef DCMDSPUDS_RMBA_PROT_H
#define DCMDSPUDS_RMBA_PROT_H

#if(DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Memaddress_Calc_Prot.hpp"

typedef struct{
   uint32 dataReadMemoryRangeLow_u32;
   uint32 dataReadMemoryRangeHigh_u32;
   uint32 dataAllowedSecRead_u32;
   uint32 dataAllowedSessRead_u32;
   Std_ReturnType (*adrUserMemReadModeRule_pfct) (Dcm_NegativeResponseCodeType * Nrc_u8,uint32 adrMemoryAddress_u32,uint32 dataDataLength_u32,Dcm_Direction_t dataDirection_en);
#if(DCM_CFG_DSP_MODERULEFORREADMEMORY != DCM_CFG_OFF)
   boolean (*addrRmbaModeRuleChkFnc_pfct) (Dcm_NegativeResponseCodeType * Nrc_u8);
#endif
   uint8 dataMemoryValue_u8;
}Dcm_RMBAConfig_tst;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern const Dcm_RMBAConfig_tst Dcm_RMBAConfig_cast [];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_RmbacalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif

#endif

