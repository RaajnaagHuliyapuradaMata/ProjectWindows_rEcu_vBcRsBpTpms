

#include "FiM_Init.h"
#include "FiM.h"
#include "FiM_Utils.h"
#include "FiM_Status.h"
#include "FiM_Monitor.h"

#define FIM_START_SEC_RAM_INIT
#include "FiM_MemMap.h"

const Type_CfgSwcServiceFiM_st* FiM_ConfigParam_pcs = NULL_PTR;

#define FIM_STOP_SEC_RAM_INIT
#include "FiM_MemMap.h"

#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

boolean FiM_StatusInitialized_b;
boolean FiM_DemInitStatus_b;

#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

void FiM_Init(const Type_CfgSwcServiceFiM_st* FiMConfigPtr)
{
    if (!FiM_Priv_GetStatusInitialized())
    {
        if (FiMConfigPtr != NULL_PTR)
        {
            FiM_ConfigParam_pcs = FiMConfigPtr;
        }
        else
        {
            FiM_ConfigParam_pcs = &FIM_POSTBUILD_CONFIGSET_NAME;
        }

        FiM_Priv_SetDemInitStatus(FALSE);

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
        FiM_Priv_MonitorInit();
#endif
        FiM_Priv_SetStatusInitialized(TRUE);
    }
    else
    {
        FIM_PRIV_DET_ERROR(FIM_INIT_ID, FIM_E_INITIALIZED_ALREADY);
    }
}

void FiM_DemInit(void)
{
    if (FiM_Priv_GetStatusInitialized())
    {
        if (!FiM_Priv_IsDemInitCalled())
        {

            FiM_Priv_SetDemInitStatus(TRUE);

            FiM_Priv_StatusInit();
        }
        else
        {
            FIM_PRIV_DET_ERROR(FIM_DEMINIT_ID, FIM_E_DEMINIT_CALLED_ALREADY);
        }
    }
    else
    {
        FIM_PRIV_DET_ERROR(FIM_DEMINIT_ID, FIM_E_NOT_INITIALIZED);
    }
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

