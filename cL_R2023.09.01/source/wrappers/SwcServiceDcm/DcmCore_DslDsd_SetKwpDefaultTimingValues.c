
#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_SetKwpDefaultTimingValues(void){
   uint8 idxDefaultTmg_u8;

   if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
   {

   	idxDefaultTmg_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_idx_u8;

       SchM_Enter_Dcm_DsldTimer_NoNest();

   	Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxDefaultTmg_u8].P2_max_u32;
   	Dcm_DsldTimer_st.dataTimeoutP3max_u32 = Dcm_Dsld_default_timings_acs[idxDefaultTmg_u8].P3_max_u32;

   	Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;

   	DCM_TimerSetNew(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_DsldTimer_st.dataTimeoutP3max_u32)
       SchM_Exit_Dcm_DsldTimer_NoNest();
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

