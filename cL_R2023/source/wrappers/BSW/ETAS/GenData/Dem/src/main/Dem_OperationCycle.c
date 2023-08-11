

#include "Dem.h"
#include "Rte_Dem.h"

#include "Dem_OperationCycle.h"
#include "Dem_Events.h"
#include "Dem_Main.h"
#include "Dem_Lock.h"
#include "Dem_Mapping.h"
#include "Dem_EventStatus.h"
#include "Dem_ISO14229Byte.h"
#include "Dem_EvMem.h"
#include "Dem_EventRecheck.h"
#include "Dem_Obd.h"
#include "Dem_GenericNvData.h"

#include "Dem_Bfm.h"

#define DEM_START_SEC_VAR_CLEARED
#include "Dem_MemMap.h"

Dem_OperationCycleList Dem_OperationCycleStates;
static Dem_OperationCycleList Dem_OperationCycleQualified;
static Dem_OperationCycleList Dem_QualifyCycleCollectedTriggers;
static Dem_OperationCycleList Dem_StartOperationCycleCollectedTriggers;

#define DEM_STOP_SEC_VAR_CLEARED
#include "Dem_MemMap.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

static boolean Dem_IsOperationCycleIdValid(Dem_OperationCycleIdType OperationCycleId)
{
    return (OperationCycleId < DEM_OPERATIONCYCLE_COUNT);
}

static void Dem_OperationCycleTriggerNvmStorage(void)
{
    if (Dem_LibGetParamBool(DEM_CFG_OPERATIONCYCLESTATUSSTORAGE))
    {
        DEM_ENTERLOCK_MON();
        Dem_GenericNvData.OperationCycleStates = Dem_OperationCycleStates;
        Dem_GenericNvData.OperationCycleQualified = Dem_OperationCycleQualified;

        Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
        DEM_EXITLOCK_MON();
    }
}

Std_ReturnType Dem_GetCycleQualified(Dem_OperationCycleIdType OperationCycleId, boolean* isQualified)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (!Dem_IsOperationCycleIdValid(OperationCycleId))
    {
        DEM_DET(DEM_DET_APIID_GETCYCLEQUALIFIED, DEM_E_WRONG_CONFIGURATION,0u);
    }
    else
    {
        *isQualified = DEM_OPERATIONCYCLE_ISBITSET(Dem_OperationCycleQualified, OperationCycleId);
        retVal = E_OK;
    }

    return retVal;
}

Std_ReturnType Dem_SetCycleQualified(Dem_OperationCycleIdType OperationCycleId)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (!Dem_IsOperationCycleIdValid(OperationCycleId))
    {
        DEM_DET(DEM_DET_APIID_SETCYCLEQUALIFIED, DEM_E_WRONG_CONFIGURATION,0u);
    }
    else
    {
        DEM_ENTERLOCK_MON();
        DEM_OPERATIONCYCLE_SETBIT(&Dem_OperationCycleQualified, OperationCycleId);
        DEM_OPERATIONCYCLE_SETBIT(&Dem_QualifyCycleCollectedTriggers, OperationCycleId);

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
        rba_DemObdBasic_SetCycleQualified(OperationCycleId);
#endif
        DEM_EXITLOCK_MON();

        retVal = E_OK;
    }

    return retVal;
}

Std_ReturnType Dem_ResetCycleQualified(Dem_OperationCycleIdType OperationCycleId)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (!Dem_IsOperationCycleIdValid(OperationCycleId))
    {
        DEM_DET(DEM_DET_APIID_RESETCYCLEQUALIFIED, DEM_E_WRONG_CONFIGURATION,0u);
    }
    else
    {
        DEM_ENTERLOCK_MON();
        DEM_OPERATIONCYCLE_CLEARBIT(&Dem_OperationCycleQualified, OperationCycleId);
        DEM_OPERATIONCYCLE_CLEARBIT(&Dem_QualifyCycleCollectedTriggers, OperationCycleId);
        DEM_EXITLOCK_MON();

        Dem_OperationCycleTriggerNvmStorage();
        retVal = E_OK;
    }
    return retVal;
}

Std_ReturnType Dem_SetOperationCycleState(Dem_OperationCycleIdType OperationCycleId,
        Dem_OperationCycleStateType CycleState)
{
    Std_ReturnType retVal = E_OK;

    if (!Dem_IsOperationCycleIdValid(OperationCycleId))
    {
        DEM_DET(DEM_DET_APIID_DEM_SETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION,0u);
        DEM_ASSERT_ISNOTLOCKED();
        return E_NOT_OK;
    }

    if (!Dem_Cfg_OperationCycle_GetIsAllowedToBeStartedDirectly(OperationCycleId))
    {

        DEM_ASSERT_ISNOTLOCKED();
        return E_NOT_OK;
    }

    DEM_ENTERLOCK_MON();

    if (CycleState == DEM_CYCLE_STATE_START)
    {
        Dem_OperationCycleList bitMaskOld = 0;
        Dem_OperationCycleList bitMask = 0;
        Dem_OperationCycleList bitMaskDependent = 0;
        Dem_OperationCycleIdType cycleId;

        DEM_OPERATIONCYCLE_SETBIT(&bitMask, OperationCycleId);

        do
        {

            bitMaskOld = bitMask;

            for (cycleId = 0; cycleId < DEM_OPERATIONCYCLE_COUNT; cycleId++)
            {

                if (DEM_OPERATIONCYCLE_ISBITSET(bitMask, cycleId))
                {
                    bitMaskDependent = Dem_Cfg_OperationCycle_GetDependentCycleMask(cycleId);

                    DEM_OPERATIONCYCLE_MERGEBITMASK(&bitMaskDependent, Dem_OperationCycleQualified);

                    DEM_OPERATIONCYCLE_SETBITMASK(&bitMask, bitMaskDependent);
                }
            }

        } while (bitMaskOld != bitMask);

        DEM_OPERATIONCYCLE_SETBITMASK(&Dem_OperationCycleStates, bitMask);
        DEM_OPERATIONCYCLE_SETBITMASK(&Dem_StartOperationCycleCollectedTriggers, bitMask);

        DEM_OPERATIONCYCLE_CLEARBITMASK(&Dem_OperationCycleQualified, bitMask);
        DEM_OPERATIONCYCLE_CLEARBITMASK(&Dem_QualifyCycleCollectedTriggers, bitMask);

    }
    else if (CycleState == DEM_CYCLE_STATE_END)
    {
        DEM_OPERATIONCYCLE_CLEARBIT(&Dem_OperationCycleStates, OperationCycleId);
    }
    else
    {
        DEM_DET(DEM_DET_APIID_DEM_SETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION,0u);
        retVal = E_NOT_OK;
    }

    DEM_EXITLOCK_MON();
    return retVal;
}

Std_ReturnType Dem_GetOperationCycleState(Dem_OperationCycleIdType OperationCycleId,
        Dem_OperationCycleStateType* CycleState)
{

    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(CycleState, DEM_DET_APIID_DEM_GETOPERATIONCYCLESTATE, E_NOT_OK);
    if (!Dem_IsOperationCycleIdValid(OperationCycleId))
    {
        DEM_DET(DEM_DET_APIID_DEM_GETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION,0u);
        return E_NOT_OK;
    }

    if (DEM_OPERATIONCYCLE_ISBITSET(Dem_OperationCycleStates, OperationCycleId))
    {
        *CycleState = DEM_CYCLE_STATE_START;
    }
    else
    {
        *CycleState = DEM_CYCLE_STATE_END;
    }

    return E_OK;
}

boolean Dem_OperationCyclesMainFunction(void)
{
    boolean retVal = FALSE;

    Dem_OperationCycleList opCycleStartTriggers;
    Dem_OperationCycleList opCycleQualifiedTriggers;

    if ((Dem_StartOperationCycleCollectedTriggers != 0) || (Dem_QualifyCycleCollectedTriggers != 0))
    {
        DEM_ENTERLOCK_MON();
        opCycleStartTriggers = Dem_StartOperationCycleCollectedTriggers;
        opCycleQualifiedTriggers = Dem_QualifyCycleCollectedTriggers;
        Dem_StartOperationCycleCollectedTriggers = 0;
        Dem_QualifyCycleCollectedTriggers = 0;
        DEM_EXITLOCK_MON();

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)

        rba_DemObdBasic_StartOperationCycle(opCycleStartTriggers, opCycleQualifiedTriggers);
#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
        rba_DemBfm_CounterAdvanceOperationCycle( opCycleStartTriggers );
#endif

        Dem_EvMemStartOperationCycleAllMem(opCycleStartTriggers);
        Dem_EvtAdvanceOperationCycle(opCycleStartTriggers);
        Dem_RecheckNodeNotRecoverableRequest();

        Dem_OperationCycleTriggerNvmStorage();

        retVal = TRUE;
    }

    return retVal;
}

void Dem_OperationCycleInit(void)
{

    (void) Dem_OperationCyclesMainFunction();
}

void Dem_OperationCycleInitCheckNvm(void)
{
    if (Dem_LibGetParamBool(DEM_CFG_OPERATIONCYCLESTATUSSTORAGE))
    {

        if (DEM_NVM_SUCCESS == Dem_NvmGetStatus (DEM_NVM_ID_DEM_GENERIC_NV_DATA))
        {
            DEM_ENTERLOCK_MON();
            Dem_OperationCycleStates |= Dem_GenericNvData.OperationCycleStates;
            Dem_OperationCycleQualified |= Dem_GenericNvData.OperationCycleQualified;
            DEM_EXITLOCK_MON();
        }
        else
        {
            DEM_ENTERLOCK_MON();
            DEM_OPERATIONCYCLE_SETBITMASK(&Dem_OperationCycleStates, DEM_OPERATIONCYCLE_ALL_BITMASK);
            DEM_OPERATIONCYCLE_CLEARBITMASK(&Dem_OperationCycleQualified, DEM_OPERATIONCYCLE_ALL_BITMASK);
            DEM_EXITLOCK_MON();
        }
    }
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
