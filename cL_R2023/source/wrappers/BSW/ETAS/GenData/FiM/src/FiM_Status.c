

#include "FiM.h"
#include "FiM_Init.h"
#include "FiM_Utils.h"
#include "FiM_Priv_Data.h"
#include "FiM_Status.h"
#include "Dem.h"

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
uint8 FiM_FIdStatusBitArray_au8[2][(FIM_CFG_NUMBEROFFIDS + 1 + 7) / 8];
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)

uint8 FiM_FIdStatusServ07BitArray_au8[2][(FIM_CFG_NUMBEROFFIDS + 1 + 7) / 8];
#endif
#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

#define FIM_START_SEC_RAM_INIT
#include "FiM_MemMap.h"
uint8 FiM_LastIdx = 0;
uint8 FiM_CurrentIdx = 1;
#define FIM_STOP_SEC_RAM_INIT
#include "FiM_MemMap.h"

#else

#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
FiM_FIdStatusCounterType FiM_FIdStatusCounter_auo[FIM_CFG_NUMBEROFFIDS + 1];
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)

FiM_FIdStatusCounterType FiM_FIdServ07StatusCounter_auo[FIM_CFG_NUMBEROFFIDS + 1];
#endif
#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
#endif

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

void FiM_Priv_StatusInit(void)
{
    FiM_FunctionIdType FId_uo;
    Dem_EventIdType eventId_uo;
    Dem_ComponentIdType componentId_uo;
    uint32 idxFidOffset_u32;
    uint32 idxEnd_u32;
    uint8 demExtendedEventStatus_u8;
    boolean demComponentFailed_b;
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
    uint8 inhMaskConfig_uo = 0;
    Dem_DTCKindType dtcKind = DEM_DTC_KIND_ALL_DTCS;
#endif

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)

    FIM_MEMSET(FiM_FIdStatusBitArray_au8[FiM_CurrentIdx], 0, sizeof(FiM_FIdStatusBitArray_au8[FiM_CurrentIdx]));
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
    FIM_MEMSET(FiM_FIdStatusServ07BitArray_au8[FiM_CurrentIdx], 0,
            sizeof(FiM_FIdStatusServ07BitArray_au8[FiM_CurrentIdx]));
#endif
#else
    FIM_PRIV_ENTERLOCK_STATUS();
    FIM_MEMSET(FiM_FIdStatusCounter_auo, 0, (FIM_CFG_NUMBEROFFIDS+1));
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
    FIM_MEMSET(FiM_FIdServ07StatusCounter_auo, 0, (FIM_CFG_NUMBEROFFIDS+1));
#endif
    FIM_PRIV_EXITLOCK_STATUS();
#endif

    for (eventId_uo = 1; eventId_uo <= FIM_CFG_NUMBEROFDEMEVENTIDS; eventId_uo++)
    {
        if (Dem_GetEventStatus(eventId_uo, &demExtendedEventStatus_u8) == E_OK)
        {
            idxEnd_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetEventptr[eventId_uo + 1]);
            idxFidOffset_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetEventptr[eventId_uo]);

            while (idxFidOffset_u32 < idxEnd_u32)
            {
                if (FiM_Priv_IsInhibitionSet(demExtendedEventStatus_u8,
                        (FiM_ConfigParam_pcs->FiM_CfgInhibitMaskMatrixptr[idxFidOffset_u32])))
                {

                    FId_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixptr[idxFidOffset_u32]);

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
                    FiM_Priv_SetInhStatus(FId_uo);
#else
                    FiM_Priv_FIdCountInc(FId_uo);
#endif
                }

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
                if (Dem_GetDtcKindOfEvent(eventId_uo, &dtcKind) == E_OK)
                {
                    if (dtcKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
                    {

                        inhMaskConfig_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitMaskMatrixptr[idxFidOffset_u32]);
                        FId_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixptr[idxFidOffset_u32]);

                        if ((FiM_Priv_IsInhMaskServ07Relevant(inhMaskConfig_uo))
                                && ((demExtendedEventStatus_u8 & FIM_PENDING_BITS_MASK) == FIM_PENDING_BITS_MASK))
                        {
#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
                            FiM_Priv_SetServ07InhStatus(FId_uo);
#else
                            FiM_Priv_FIdServ07CountInc(FId_uo);
#endif
                        }
                    }
                }
#endif
                idxFidOffset_u32++;
            }
        }
    }

    for (componentId_uo = 1; componentId_uo <= FIM_CFG_NUMBEROFDEMCOMPONENTIDS; componentId_uo++)
    {
        if (Dem_GetComponentFailed(componentId_uo, &demComponentFailed_b) == E_OK)
        {
            if (demComponentFailed_b)
            {
                idxEnd_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetComponentptr[componentId_uo + 1]);
                idxFidOffset_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetComponentptr[componentId_uo]);

                while (idxFidOffset_u32 < idxEnd_u32)
                {

                    FId_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixComponentptr[idxFidOffset_u32]);

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
                    FiM_Priv_SetInhStatus(FId_uo);
#else
                    FiM_Priv_FIdCountInc(FId_uo);
#endif
                    idxFidOffset_u32++;
                }
            }
        }
    }

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
    FIM_PRIV_ENTERLOCK_MONITOR();

    FiM_LastIdx = FiM_CurrentIdx;
    FIM_PRIV_EXITLOCK_MONITOR();
#endif
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

