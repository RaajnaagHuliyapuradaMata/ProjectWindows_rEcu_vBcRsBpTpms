

#include "Dem_Dcm_Internal.h"
#include "Rte_Dem.h"

#include "Dem_Clear.h"

#include "Dem_ClientBaseHandling.h"
#include "Dem_ClientMachine_Clear.h"
#include "Dem_ClientRequestDispatcher.h"
#include "Dem_Events.h"
#include "Dem_EventRecheck.h"
#include "Dem_StorageCondition.h"
#include "Dem_EvMem.h"
#include "Dem_DTCs.h"
#include "Dem_DTCGroup.h"
#include "Dem_DTCStatusByte.h"
#include "Dem_Obd.h"
#include "Dem_EventStatus.h"
#include "Dem_EvMemGen.h"
#include "Dem_Cfg_ExtPrototypes.h"
#include "Dem_Lok_J1939Dcm.h"
#if (DEM_CFG_PROJECTEXTENSION_CLEAR_PENDING_NOTIFICATION == TRUE)
#include "Dem_PrjClearProjectExtension.h"
#endif

#define DEM_START_SEC_VAR_INIT
#include "Dem_MemMap.h"
static Std_ReturnType Dem_ClearResult = DEM_PENDING;
#define DEM_STOP_SEC_VAR_INIT
#include "Dem_MemMap.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

static Std_ReturnType Dem_ClearDTCBody(Dem_ClientSelectionType Selection, Dem_DTCOriginType DTCOrigin)
{
#if(DEM_CFG_CLEAR_DTC_LIMITATION == DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS)
    Dem_DtcIdType dtcId;
    Dem_DTCGroupIdType DTCGroupId;
#endif

    Dem_ClientClearMachine.IsClearInterrupted = FALSE;
    Dem_ClientClearMachine.NumberOfEventsProcessed = 0;

    if (Dem_ClientSelectionType_isSelectionDTCGroupAll(Selection))
    {

        Dem_ClearAllDTCs(DTCOrigin, &Dem_ClientClearMachine);

        if (!Dem_ClientClearMachine.IsClearInterrupted)
        {
            Dem_EvMemGenClearDtcByOccurrenceTime(DTCOrigin);
            Dem_EvMemGenClearOverflow(DTCOrigin);
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
            rba_DemObd_Clear(DTCOrigin);
#endif
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
            Dem_StoCoClearReplacementStoredFlag();
#endif
            return E_OK;
        }
        return DEM_PENDING;
    }

#if(DEM_CFG_CLEAR_DTC_LIMITATION == DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS)

    if (Dem_ClientSelectionType_isSelectionDTCGroup(Selection))
    {
        DTCGroupId = (uint8)Dem_ClientSelectionType_getSelectionDtcIndex (Selection);

        Dem_DtcsClearDtcInGroup(DTCGroupId, DTCOrigin, &Dem_ClientClearMachine);
        if (!Dem_ClientClearMachine.IsClearInterrupted)
        {
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
            Dem_StoCoClearReplacementStoredFlag();
#endif
            return E_OK;
        }
        return DEM_PENDING;
    }
    else if (Dem_ClientSelectionType_isSelectionSingleDTC(Selection))
    {
        dtcId = Dem_ClientSelectionType_getSelectionDtcIndex (Selection);

        Dem_ClearSingleDTC(dtcId, DTCOrigin, &Dem_ClientClearMachine);

        if (!Dem_ClientClearMachine.IsClearInterrupted)
        {
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
            Dem_StoCoClearReplacementStoredFlag();
#endif
            return E_OK;
        }
        return DEM_PENDING;
    }
    else
    {
        return DEM_WRONG_DTC;
    }

#else
    return DEM_WRONG_DTC;
#endif
}

void Dem_ClearMainFunction(void)
{
    Dem_ClientRequestType tempRequest;
    Dem_ClientIdType tempClientId;

    if (Dem_ClientClearMachine_GetMachineState() != DEM_CLEAR_DTC_MACHINE_STATE_IDLE)
    {
        tempClientId = Dem_ClientClearMachine_GetMachineActiveClient();
        tempRequest = Dem_Client_getClient(tempClientId)->request;

        if (!Dem_ClientRequestType_isCancelRequested(tempRequest))
        {
            if (Dem_ClientClearMachine_GetMachineState() == DEM_CLEAR_DTC_MACHINE_STATE_EXEC)
            {
#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
                if (Dem_Client_GetClientType(tempClientId) == DEM_CLIENTTYPE_J1939)
                {
                    Dem_ClearResult = Dem_J1939DcmClearDTCBody(Dem_Client_getClient(tempClientId)->data.j1939.J1939DTCTypeFilter,
                            Dem_Client_getClient(tempClientId)->data.j1939.J1939node);
                }
                else
#endif
                {
                    if (Dem_ClientClearMachine.IsNewClearRequest)
                    {

                        Dem_ClearDtcNotificationStartCallbacks(Dem_Client_getClient(tempClientId)->data.standard.DTC,
                                                               Dem_Client_getClient(tempClientId)->data.standard.DTCFormat,
                                                               Dem_Client_getClient(tempClientId)->data.standard.DTCOrigin);
                    }

                    Dem_ClearResult = Dem_ClearDTCBody(Dem_Client_getClient(tempClientId)->selection,
                            Dem_Client_getClient(tempClientId)->data.standard.DTCOrigin);
                }

                Dem_ClientClearMachine.IsNewClearRequest = FALSE;

                if (Dem_ClearResult != DEM_PENDING)
                {
                    Dem_ClientClearMachine_SetMachineState(DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM);
                }
            }

            if (Dem_ClientClearMachine_GetMachineState() == DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM)
            {

                if (((DEM_CFG_CLEAR_DTC_BEHAVIOR == DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH)
                        && (Dem_ClearResult == E_OK)
                        && (Dem_NvMIsClearPending()
#if (DEM_CFG_PROJECTEXTENSION_CLEAR_PENDING_NOTIFICATION == TRUE)
                        || Dem_ClearProjectExtensionIsClearPending()
#endif
                        )
                )
#if (DEM_CFG_TRIGGERMONITORINITBEFORECLEAROK == TRUE)
                        || Dem_EvtIsAnyInitMonitoringRequestedClear()
#endif
                        )
                {

                }
                else
                {
                    if ((DEM_CFG_CLEAR_DTC_BEHAVIOR == DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH)
                            && (Dem_NvMIsClearFailed()))
                    {
                        Dem_ClearResult = DEM_CLEAR_MEMORY_ERROR;
                    }

                    if (!Dem_ClientClearMachine_isProcessingClient(DEM_CLIENTID_J1939))
                    {

                        Dem_ClearDtcNotificationFinishCallbacks(Dem_Client_getClient(tempClientId)->data.standard.DTC,
                                                                Dem_Client_getClient(tempClientId)->data.standard.DTCFormat,
                                                                Dem_Client_getClient(tempClientId)->data.standard.DTCOrigin);
                    }
                    Dem_ClientResultType_setResult(&Dem_Client_getClient(tempClientId)->result, tempRequest,
                            Dem_ClearResult);
                    Dem_ClientClearMachine_SetMachineState(DEM_CLEAR_DTC_MACHINE_STATE_IDLE);
                }
            }
        }
        else
        {
            Dem_ClientResultType_confirmCancel(&Dem_Client_getClient(tempClientId)->result, tempRequest);
            Dem_ClientClearMachine_SetMachineState(DEM_CLEAR_DTC_MACHINE_STATE_IDLE);
        }
    }
}

boolean Dem_ClearIsInProgress (void)
{
    return (Dem_ClientClearMachine.machine_state == DEM_CLEAR_DTC_MACHINE_STATE_EXEC);
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

