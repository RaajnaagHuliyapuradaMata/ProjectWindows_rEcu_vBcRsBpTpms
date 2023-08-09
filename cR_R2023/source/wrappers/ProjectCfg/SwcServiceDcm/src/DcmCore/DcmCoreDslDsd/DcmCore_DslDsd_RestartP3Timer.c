

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void, DCM_CODE) Dcm_RestartP3timer(void)
{

    Dcm_Lok_ReloadS3Timer();
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

