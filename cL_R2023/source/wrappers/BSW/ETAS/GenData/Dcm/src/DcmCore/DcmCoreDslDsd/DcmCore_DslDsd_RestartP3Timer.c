
#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void Dcm_RestartP3timer(void)
{

    Dcm_Lok_ReloadS3Timer();
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

