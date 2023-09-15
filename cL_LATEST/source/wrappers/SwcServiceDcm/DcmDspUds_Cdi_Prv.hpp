

#ifndef DCMDSPUDS_CDI_PRV_H
#define DCMDSPUDS_CDI_PRV_H

#include "Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)

#include "DcmCore_DslDsd_Prot.hpp"
#include "DcmDsp_Lib_Prv.hpp"

#define DCM_CDI_REQ_LEN              0x03u
#define DCM_POS_DTC_HIGHBYTE         0x00u
#define DCM_POS_DTC_MIDDLEBYTE       0x01u
#define DCM_POS_DTC_LOWBYTE          0x02u
#define DCM_POS_DTC_BIT16            16u
#define DCM_POS_DTC_BIT8             8u
#define DCM_DTC_GRP_MASK             0x00FFFFFFu

#if(DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED!=DCM_CFG_OFF)
typedef boolean (*Cdi_ModeRuleRef_pf) (Dcm_NegativeResponseCodeType* Nrc_u8);
typedef Std_ReturnType (*CDIUserConditionCheck_pf)(uint32 GoDTC,Dcm_NegativeResponseCodeType* ErrorCode);
#endif

#endif
#endif

#endif

