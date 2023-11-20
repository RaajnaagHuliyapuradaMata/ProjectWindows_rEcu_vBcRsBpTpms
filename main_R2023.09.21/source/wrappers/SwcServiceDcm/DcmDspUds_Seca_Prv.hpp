

#ifndef DCMDSPUDS_SECA_PRIV_H
#define DCMDSPUDS_SECA_PRIV_H

#if( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ) )

typedef enum{
    DCM_DSP_SECA_GENSEED
   ,   DCM_DSP_SECA_COMPAREKEY 
   ,   DCM_DSP_SECA_PENDING
}Dcm_Dsp_SecaStates_ten;

#define DCM_START_SEC_VAR_CLEARED_8 
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)

extern VAR(uint8,AUTOMATIC) Dcm_GetattemptCounterWaitCycle_u8;
#endif
extern VAR(uint8,  DCM_VAR) Dcm_DspSecTabIdx_u8;
extern VAR(uint8,  DCM_VAR) Dcm_DspSecAccType_u8;
extern VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspSecaOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_Dsp_SecaStates_ten,DCM_VAR) Dcm_DspSecaStatus_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(boolean, DCM_VAR) Dcm_DspChgSecLevel_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void, DCM_CODE) Dcm_Lok_DspSecurityConfirmation(
   	VAR(Dcm_IdContextType,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
   													);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif

