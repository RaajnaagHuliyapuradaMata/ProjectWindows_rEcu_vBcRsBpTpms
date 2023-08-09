

#include "FiM_Init.h"
#include "FiM.h"
#include "FiM_Det.h"
#include "FiM_Status.h"
#include "FiM_Monitor.h"

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

void FiM_MainFunction(void)
{
#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
    if (FiM_Priv_GetStatusInitialized())
    {
        if (FiM_Priv_IsDemInitCalled())
        {
            FiM_Priv_MonitorProc();
        }
        else
        {
            FIM_PRIV_DET_ERROR(FIM_MAINFUNCTION_ID, FIM_E_DEMINIT_NOT_CALLED);
        }
    }
    else
    {
        FIM_PRIV_DET_ERROR(FIM_MAINFUNCTION_ID, FIM_E_NOT_INITIALIZED);
    }
#endif
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

