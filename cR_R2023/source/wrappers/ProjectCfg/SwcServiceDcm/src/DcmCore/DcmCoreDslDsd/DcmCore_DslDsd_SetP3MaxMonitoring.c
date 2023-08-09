

#include "DcmCore_DslDsd_Inf.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void, DCM_CODE) Dcm_SetP3MaxMonitoring (VAR(boolean,AUTOMATIC) active)
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
#include "Dcm_Cfg_MemMap.h"
