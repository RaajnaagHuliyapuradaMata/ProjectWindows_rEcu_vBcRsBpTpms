
#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_SetP3MaxMonitoring (boolean active)
{

    Dcm_DsldGlobal_st.flgMonitorP3timer_b = active;

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

   if(((DCM_IS_KWPPROT_ACTIVE() != FALSE) && (active == FALSE)))
   {

        Dcm_DsldGlobal_st.flgCommActive_b = FALSE;
   }
#endif
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
