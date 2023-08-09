

#include "FiM_Init.h"
#include "FiM.h"
#include "Dem.h"
#include "FiM_Det.h"
#include "FiM_Status.h"
#include "FiM_Monitor.h"
#include "FiM_Cfg_SchM.h"

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

static boolean FiM_Dem_IsInitialized(void)
{
    boolean retVal = FALSE;
    if (FiM_Priv_GetStatusInitialized())
    {

        if (FiM_Priv_IsDemInitCalled())
        {
            retVal = TRUE;
        }
        else
        {
            FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_DEMINIT_NOT_CALLED);
        }
    }
    else
    {
        FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_NOT_INITIALIZED);
    }
    return retVal;
}

void FiM_DemTriggerOnEventStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType EventStatusOld,
        Dem_UdsStatusByteType EventStatusNew)
{
    uint32 idxFidOffset_u32 = 0;
    uint32 idxEnd_u32 = 0;
    FiM_FunctionIdType FId_uo = 0;
    FiM_InhibitionMaskType inhMaskConfig_uo = 0;
    boolean inhMaskChanged_b = FALSE;
    boolean inhMaskSet_b = FALSE;
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
    boolean serv07MaskChanged_b = FALSE;
    Dem_DTCKindType dtcKind = DEM_DTC_KIND_ALL_DTCS;
#endif

    if (FiM_Dem_IsInitialized())
    {
        if ((EventId <= FIM_CFG_NUMBEROFDEMEVENTIDS) && (EventId > 0))
        {
            inhMaskChanged_b = (((EventStatusOld & FIM_INHIBITION_BITS_MASK)
                    ^ (EventStatusNew & FIM_INHIBITION_BITS_MASK)) != 0u);

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
            if (Dem_GetDtcKindOfEvent(EventId, &dtcKind) == E_OK)
            {
                if (dtcKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
                {

                    serv07MaskChanged_b = (((EventStatusOld & FIM_PENDING_BITS_MASK)
                            ^ (EventStatusNew & FIM_PENDING_BITS_MASK)) != 0u);
                }
            }
#endif

            if ((inhMaskChanged_b)
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
                    || (serv07MaskChanged_b)
#endif
                    )
            {
                idxEnd_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetEventptr[EventId + 1]);
                idxFidOffset_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetEventptr[EventId]);

                while (idxFidOffset_u32 < idxEnd_u32)
                {
                    FId_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixptr[idxFidOffset_u32]);
                    inhMaskConfig_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitMaskMatrixptr[idxFidOffset_u32]);

                    if (inhMaskChanged_b)
                    {
                        if ((FiM_Priv_IsInhibitionChanged(EventStatusNew, EventStatusOld, inhMaskConfig_uo,
                                &inhMaskSet_b)))
                        {
                            if (inhMaskSet_b)
                            {

                                FiM_Priv_FIdCountInc(FId_uo);
                            }
                            else
                            {

                                FiM_Priv_FIdCountDec(FId_uo);
                            }
                        }
                    }

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
                    if (serv07MaskChanged_b)
                    {
                        if (FiM_Priv_IsInhMaskServ07Relevant(inhMaskConfig_uo))
                        {

                            if ((EventStatusNew & FIM_PENDING_BITS_MASK) == FIM_PENDING_BITS_MASK)
                            {

                                FiM_Priv_FIdServ07CountInc(FId_uo);
                            }
                            else
                            {

                                FiM_Priv_FIdServ07CountDec(FId_uo);
                            }
                        }
                    }
#endif
                    idxFidOffset_u32++;
                }
            }
        }

        else
        {
            FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_EVENTID_OUT_OF_RANGE);
        }
    }
}

void FiM_DemTriggerOnComponentStatus(Dem_ComponentIdType ComponentId, boolean ComponentFailedStatus)
{
#if (FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC == 0)
    FIM_USE_VAR(ComponentId);
    FIM_USE_VAR(ComponentFailedStatus);
#else
    uint32 idxFidOffset_u32 = 0;
    uint32 idxEnd_u32 = 0;
    FiM_FunctionIdType FId_uo = 0;

    if (FiM_Dem_IsInitialized())
    {
        if ((ComponentId <= FIM_CFG_NUMBEROFDEMCOMPONENTIDS) && (ComponentId > 0))
        {
            idxEnd_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetComponentptr[ComponentId + 1]);
            idxFidOffset_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetComponentptr[ComponentId]);

            while (idxFidOffset_u32 < idxEnd_u32)
            {
                FId_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixComponentptr[idxFidOffset_u32]);

                if (ComponentFailedStatus)
                {

                    FiM_Priv_FIdCountInc(FId_uo);
                }
                else
                {

                    FiM_Priv_FIdCountDec(FId_uo);
                }

                idxFidOffset_u32++;
            }
        }

        else
        {
            FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_COMPONENTID_OUT_OF_RANGE);
        }
    }
#endif
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif

