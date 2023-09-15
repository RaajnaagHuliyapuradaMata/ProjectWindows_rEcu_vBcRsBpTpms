

#ifndef DCMDSPUDS_DSC_PROT_H
#define DCMDSPUDS_DSC_PROT_H

#include "Dcm.hpp"

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)

typedef enum{
    DCM_DSP_DSC_INIT = 1
   ,   DCM_DSP_DSC_WAIT
   ,   DCM_DSP_DSC_CHECK_PERMISSION
   ,   DCM_DSP_DSC_SEND_RESP
   ,   DCM_DSP_DSC_ERROR
}Dcm_DscStateType_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_DscStateType_ten Dcm_stDsc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern uint8 Dcm_ctDiaSess_u8;
extern uint8 Dcm_ReqSess_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif

