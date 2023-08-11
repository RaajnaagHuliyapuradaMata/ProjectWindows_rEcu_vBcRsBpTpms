

#include "Dem.h"
#include "Dem_Dcm_Internal.h"
#include "Rte_Dem.h"

#include "Dem_EvMemApi.h"

#include "Dem_EvMem.h"
#include "Dem_Lock.h"
#include "Dem_EnvMain.h"
#include "Dem_Mapping.h"
#include "Dem_DTCs.h"
#include "Dem_Obd.h"
#include "Dem_Client.h"
#include "Dem_Cfg_Events_DataStructures.h"
#include "Dem_ClientMachine_SelectED_FFData.h"

#define DEM_START_SEC_VAR_CLEARED
#include "Dem_MemMap.h"
#define DEM_STOP_SEC_VAR_CLEARED
#include "Dem_MemMap.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
uint16_least Dem_EvMemGetMemoryLocIdOfDtcAndOriginWithVisibility(Dem_DtcIdType DtcId, Dem_DTCOriginType DTCOrigin, Dem_boolean_least ShadowEntriesVisible)
{
	if (DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
	{
		return Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility (DtcId, DEM_CFG_EVMEM_MEMID_PRIMARY, ShadowEntriesVisible);
	}

#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
	if (DTCOrigin == DEM_DTC_ORIGIN_SECONDARY_MEMORY)
	{
		return Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility (DtcId, DEM_CFG_EVMEM_MEMID_SECONDARY, ShadowEntriesVisible);
	}
#endif

#if (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
	if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
	{
		return Dem_EvMemGetEventMemoryLocIdOfDtc (DtcId, DEM_CFG_EVMEM_MEMID_MIRROR);
	}
#elif DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
	if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
	{
		return Dem_EvMemGetShadowMemoryLocIdOfDtc(DtcId, DEM_CFG_EVMEM_MEMID_SHADOW);
	}
#endif

	
	return DEM_EVMEM_INVALID_LOCID;
}

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04 || DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06

Std_ReturnType Dem_DisableDTCRecordUpdate(uint8 ClientId)
{
    Std_ReturnType returnValue;

    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_DISABLEDTCRECORDUPDATE, E_NOT_OK);

    if(Dem_Client_IsDTCRecordUpdateDisabled(ClientId))
    {
        DEM_DET(DEM_DET_APIID_DISABLEDTCRECORDUPDATE, DEM_E_WRONG_CONDITION,0u);
        returnValue = E_NOT_OK;
    }
    else
    {
        returnValue = Dem_Client_Operation(ClientId, DEM_CLIENT_REQUEST_DISABLERECORDUPDATE, DEM_DET_APIID_DISABLEDTCRECORDUPDATE);
        if(returnValue == E_OK)
        {
            Dem_Client_SetDTCRecordUpdateDisabled(ClientId, TRUE);
        }
    }
    return returnValue;
}

Std_ReturnType Dem_EnableDTCRecordUpdate(uint8 ClientId)
{
    Std_ReturnType returnValue;

    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_ENABLEDTCRECORDUPDATE, E_NOT_OK);

    returnValue = Dem_Client_Operation(ClientId, DEM_CLIENT_REQUEST_ENABLERECORDUPDATE, DEM_DET_APIID_ENABLEDTCRECORDUPDATE);
    if(returnValue == E_OK)
    {
        Dem_Client_SetDTCRecordUpdateDisabled(ClientId, FALSE);

        Dem_ClientSetED_FFSelectionPending(ClientId, TRUE);
    }
    return returnValue;
}

#endif

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04 || DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06
static void Dem_EvMemApi_SelectED_FF_InitializeIterators(uint8 ClientId, uint8 RecordNumber, uint8 ApiId)
{
    Dem_EventIdType EventId = Dem_DtcIdGetFirstEventId(Dem_ClientSelectionType_getSelectionDtcIndex(Dem_Client_getClient(ClientId)->selection));

    if(ApiId == DEM_DET_APIID_SELECTEXTENDEDDATARECORD)
    {
        Dem_EnvEDRIteratorNew(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt, RecordNumber, EventId);
    }
    else
    {
        Dem_EnvFFRecIteratorNew(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt, RecordNumber, EventId);
    }
}

static void Dem_EvMemApi_RemapReturnInitialization(uint8 ClientId)
{
    Dem_ClientSetGetNextDataCalled(ClientId, FALSE);
}

static boolean Dem_EvMemApi_IsRemappingOfDemNoSuchElementRequired(uint8 ApiId, Dem_EventIdType EventId, uint8 ClientId, Std_ReturnType retValForRemap)
{
    uint8 ReqFFRecord = Dem_EnvFFRecIteratorRequestedRecNum(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);
    uint8 ReqEDRecord = Dem_EnvEDRIteratorRequestedRecNum(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);
    boolean returnValue = FALSE;

    if((retValForRemap == DEM_NO_SUCH_ELEMENT) && (!Dem_ClientIsGetNextDataCalled(ClientId)))
    {
        switch(ApiId)
            {
                case DEM_DET_APIID_GETNEXTFREEZEFRAMEDATA:
                {
                    if(ReqFFRecord == 0xFF)
                    {
                        returnValue = (Dem_EvtParam_GetMaxNumberFreezeFrameRecords(EventId) != 0);
                    }
                    else
                    {
                        returnValue = TRUE;
                    }
                    break;
                }
                case DEM_DET_APIID_GETNEXTEXTENDEDDATARECORD:
                {
                    if(ReqEDRecord == 0xFF)
                    {
                        returnValue = (Dem_EnvGetTotalNumOfConfEDR_OBDOrAll(EventId, FALSE) != 0);
                    }
                    else if(ReqEDRecord == 0xFE)
                    {
                        returnValue = (Dem_EnvGetTotalNumOfConfEDR_OBDOrAll(EventId, TRUE) != 0);
                    }
                    else
                    {
                        returnValue = TRUE;
                    }
                    break;
                }
                default :
                {

                    break;
                }
            }
    }
    return returnValue;
}

static void Dem_EvMemApi_RemapReturnAsPerAR(uint8 ApiId, Dem_EventIdType EventId, Std_ReturnType* returnValue, uint8 ClientId, uint16* BufSize)
{
    if(*returnValue == DEM_INVALID_RECORDNUMBER)
    {
        *returnValue = DEM_NO_SUCH_ELEMENT;
    }
    else
    {
        if(Dem_EvMemApi_IsRemappingOfDemNoSuchElementRequired(ApiId, EventId, ClientId, *returnValue))
        {
            *BufSize = 0;
            *returnValue = E_OK;
        }
    }
    Dem_ClientSetGetNextDataCalled(ClientId, TRUE);
}

static void Dem_EvMemApi_UpdateSelectED_FFMachineState_OnSelectCall(uint8 ClientId, uint8 ApiId)
{
    if(ApiId == DEM_DET_APIID_SELECTEXTENDEDDATARECORD)
    {
        if(Dem_EnvEDRIteratorIsRequestedRecValid(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt))
        {
            Dem_ClientMachine_SelectED_FFData_SetState(ClientId, DEM_SELECT_ED_ITERATION_IN_PROGRESS);
        }
        else
        {
            Dem_ClientMachine_SelectED_FFData_SetState(ClientId, DEM_SELECT_ED_STATE_SELECTION_INVALID);
        }
    }
    else
    {
        if(Dem_EnvFFRecIteratorIsRequestedRecValid(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt))
        {
            Dem_ClientMachine_SelectED_FFData_SetState(ClientId, DEM_SELECT_FF_ITERATION_IN_PROGRESS);
        }
        else
        {
            Dem_ClientMachine_SelectED_FFData_SetState(ClientId, DEM_SELECT_FF_STATE_SELECTION_INVALID);
        }
    }
}

static void Dem_EvMemApi_UpdateSelectED_FFMachineState_OnGetNextCall(uint8 ClientId, Std_ReturnType returnValue)
{
    if((returnValue == DEM_NO_SUCH_ELEMENT) || (returnValue == DEM_INVALID_RECORDNUMBER))
    {
        Dem_ClientMachine_SelectED_FFData_SetState(ClientId, DEM_SELECT_ED_FF_STATE_INIT);
    }
}

DEM_INLINE boolean Dem_EvMemApi_IsEvMemCopyUsable(uint8 ClientId)
{
    return ((Dem_Client_IsDTCRecordUpdateDisabled(ClientId)) &&
                (! Dem_ClientIsED_FFSelectionPending(ClientId)) );
}

static Std_ReturnType Dem_EvMemApi_SelectED_FF_Data(uint8 ClientId, uint8 RecordNumber, uint8 ApiId)
{
    Std_ReturnType returnValue;

    DEM_STATIC_ASSERT((DEM_DET_APIID_SELECTEXTENDEDDATARECORD != DEM_DET_APIID_SELECTFREEZEFRAMEDATA), DEM_DET_APIIDS_VALUE_SHOULD_NOT_BE_SAME);

    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(ApiId, DEM_E_WRONG_CONFIGURATION,0u);
        return DEM_WRONG_CLIENTID;
    }

    if ((Dem_Client_getClient(ClientId)->client_state == DEM_CLIENT_STATE_PARAMETERS_SET)
        && (Dem_EvMemApi_IsEvMemCopyUsable(ClientId)))
    {
        returnValue = Dem_ClientSelectionType_getSelectionResult(Dem_Client_getClient(ClientId)->selection);
        if((returnValue == E_OK) && (! Dem_ClientSelectionType_isSelectionSingleDTC(Dem_Client_getClient(ClientId)->selection)))
        {
            returnValue = DEM_WRONG_DTC;
        }
    }
    else
    {
        returnValue = Dem_Client_Operation(ClientId, DEM_CLIENT_REQUEST_SELECT_ED_FF_DATA, ApiId);
    }

    if(returnValue == E_OK)
    {
        Dem_EvMemApi_SelectED_FF_InitializeIterators(ClientId, RecordNumber, ApiId);
        Dem_EvMemApi_RemapReturnInitialization(ClientId);

        Dem_EvMemApi_UpdateSelectED_FFMachineState_OnSelectCall(ClientId, ApiId);
    }
    if(returnValue != DEM_PENDING)
    {
        Dem_ClientSetED_FFSelectionPending(ClientId, FALSE);
    }
    return returnValue;
}

static Std_ReturnType Dem_EvMemApi_GetSingleEDRecord(uint8 ClientId, uint8* DestBuffer, uint16* BufSize, Dem_EventIdType EventId, Dem_EvMemEventMemoryType* EvMemPointer)
{
    Std_ReturnType returnValue = DEM_NO_SUCH_ELEMENT;
    if(Dem_ClientSelectED_FFDataType_IsEvMemCopyValid(ClientId))
    {
        while(Dem_EnvEDRIteratorIsValid(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt))
        {
            uint8 CurrentRecordNumber = Dem_EnvEDRIteratorCurrentRecNum(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);
            if(Dem_EnvIsEDRNumberStored(EventId, CurrentRecordNumber, EvMemPointer))
            {
                returnValue = Dem_EnvRetrieveEDR(EventId,CurrentRecordNumber, DestBuffer, BufSize,Dem_EvMemGetEventMemDataByPtr(EvMemPointer), EvMemPointer);
                Dem_EnvEDRIteratorNext(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);
                break;
            }
            Dem_EnvEDRIteratorNext(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);
        }
    }
    return returnValue;
}

static Std_ReturnType Dem_EvMemApi_GetSingleFFRecord(uint8 ClientId, uint8* DestBuffer, uint16* BufSize, Dem_EventIdType EventId, Dem_EvMemEventMemoryType* EvMemPointer )
{
    Std_ReturnType returnValue = DEM_NO_SUCH_ELEMENT;
    if(Dem_ClientSelectED_FFDataType_IsEvMemCopyValid(ClientId))
    {
        while(Dem_EnvFFRecIteratorIsValid(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt))
        {
            uint8 CurrentRecordNumber = Dem_EnvFFRecIteratorCurrentRecNum(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);
            if (Dem_EnvIsFFRecNumStored(EvMemPointer, CurrentRecordNumber))
            {
                uint8 RecordIndex = Dem_EnvGetIndexFromFFRecNum (EventId, CurrentRecordNumber );
                returnValue = Dem_EnvRetrieveFF (EventId, DestBuffer, BufSize, RecordIndex , Dem_EvMemGetEventMemDataByPtr(EvMemPointer), EvMemPointer);
                Dem_EnvFFRecIteratorNext(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);
                break;
            }
            Dem_EnvFFRecIteratorNext(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);
        }
    }
    return returnValue;
}

DEM_INLINE boolean Dem_EvMemApi_IsSelectionFuncCalledForGetNextCall(uint8 ApiId, uint8 ClientId)
{
    boolean returnValue;
    switch(ApiId)
    {
        case DEM_DET_APIID_GETNEXTEXTENDEDDATARECORD:
        {
            returnValue = ((Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_ED_STATE_SELECTION_INVALID) ||
                            (Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_ED_ITERATION_IN_PROGRESS));
            break;
        }
        case DEM_DET_APIID_GETNEXTFREEZEFRAMEDATA:
        {
            returnValue = ((Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_FF_STATE_SELECTION_INVALID) ||
                            (Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_FF_ITERATION_IN_PROGRESS));
            break;
        }
        default :
        {
            returnValue = FALSE;
            break;
        }
    }
    return returnValue;
}

static Std_ReturnType Dem_EvMemApi_GetNextDataRecord(uint8 ClientId, uint8* DestBuffer, uint16* BufSize, uint8 ApiId)
{
    Std_ReturnType returnValue;

    DEM_STATIC_ASSERT((DEM_DET_APIID_GETNEXTEXTENDEDDATARECORD != DEM_DET_APIID_GETNEXTFREEZEFRAMEDATA), DEM_DET_APIIDS_VALUE_SHOULD_NOT_BE_SAME);

    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(ApiId, DEM_E_WRONG_CONFIGURATION,0u);
        return DEM_WRONG_CLIENTID;
    }

    switch(Dem_Client_getClient(ClientId)->client_state)
    {
        case DEM_CLIENT_STATE_INIT:
        {
            DEM_DET(ApiId, DEM_E_WRONG_CONDITION,0u);
            returnValue = E_NOT_OK;
            break;
        }
        case DEM_CLIENT_STATE_PARAMETERS_SET:
        {
            if (! Dem_EvMemApi_IsSelectionFuncCalledForGetNextCall(ApiId, ClientId))
            {
                DEM_DET(ApiId, DEM_E_WRONG_CONDITION,0u);
                returnValue = E_NOT_OK;
            }
            else
            {
                returnValue = Dem_ClientSelectionType_getSelectionResult(Dem_Client_getClient(ClientId)->selection);
                if((returnValue == E_OK) && (! Dem_ClientSelectionType_isSelectionSingleDTC(Dem_Client_getClient(ClientId)->selection)))
                {
                    returnValue = DEM_WRONG_DTC;
                }
                if (returnValue == E_OK)
                {
                    Dem_EventIdType EventId = Dem_DtcIdGetFirstEventId(Dem_ClientSelectionType_getSelectionDtcIndex(Dem_Client_getClient(ClientId)->selection));

                    if((Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_ED_STATE_SELECTION_INVALID) ||
                            (Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_FF_STATE_SELECTION_INVALID))
                    {
                        returnValue = DEM_INVALID_RECORDNUMBER;
                    }
                    else
                    {
                        Dem_EvMemEventMemoryType* EvMemPointer = Dem_ClientSelectED_FFDataType_GetEvMemCopy(ClientId);
                        if(ApiId == DEM_DET_APIID_GETNEXTEXTENDEDDATARECORD)
                        {
                            returnValue = Dem_EvMemApi_GetSingleEDRecord(ClientId, DestBuffer, BufSize, EventId, EvMemPointer);
                        }
                        else
                        {
                            returnValue = Dem_EvMemApi_GetSingleFFRecord(ClientId, DestBuffer, BufSize, EventId, EvMemPointer);
                        }
                    }
                    Dem_EvMemApi_RemapReturnAsPerAR(ApiId, EventId, &returnValue, ClientId, BufSize);
                    Dem_EvMemApi_UpdateSelectED_FFMachineState_OnGetNextCall(ClientId, returnValue);
                }
            }
            break;
        }
        case DEM_CLIENT_STATE_REQUESTED_OPERATION:
        {
            if (Dem_ClientRequestType_getMachineIndex(Dem_Client_getClient(ClientId)->request)
                    != Dem_ClientRequestType_getMachineIndex(DEM_CLIENT_REQUEST_SELECT_ED_FF_DATA))
            {
                DEM_DET(ApiId, DEM_E_WRONG_CONDITION,0u);
                returnValue = E_NOT_OK;
            }
            else
            {
                returnValue = DEM_PENDING;
            }
            break;
        }
        default :
        {
            returnValue = E_NOT_OK;
            break;
        }
    }
    return returnValue;
}

static Std_ReturnType Dem_EvMemApi_GetSizeOfEDDataSelection(uint8 ClientId, Dem_EventIdType EventId, const Dem_EvMemEventMemoryType* EvMemPointer, uint16* SizeOfData)
{
    uint8 RecNumber = Dem_EnvEDRIteratorRequestedRecNum(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);

    if (! Dem_EnvEDRIteratorIsRequestedRecValid(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt))
    {
        return DEM_INVALID_RECORDNUMBER;
    }
    else
    {
        if (RecNumber == 0xFF)
        {
            return Dem_EnvGetSizeOfEDR_AllOrObdStored(EventId, SizeOfData, EvMemPointer, FALSE);
        }
        else if (RecNumber == 0xFE)
        {
            return Dem_EnvGetSizeOfEDR_AllOrObdStored(EventId, SizeOfData, EvMemPointer, TRUE);
        }
        else
        {
            return Dem_EnvGetSizeOfEDR(EventId, RecNumber, SizeOfData);
        }
    }
}

static Std_ReturnType Dem_EvMemApi_GetSizeOfFFDataSelection(uint8 ClientId, Dem_EventIdType EventId, const Dem_EvMemEventMemoryType* EvMemPointer, uint16* SizeOfData)
{
    Std_ReturnType returnValue;
    uint8 RecNumber = Dem_EnvFFRecIteratorRequestedRecNum(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt);

    if (! Dem_EnvFFRecIteratorIsRequestedRecValid(&Dem_Client_getClient(ClientId)->data.standard.SelectED_FFIt))
    {
        returnValue = DEM_INVALID_RECORDNUMBER;
    }
    else
    {
        returnValue = Dem_EnvGetSizeOfFF(EventId, SizeOfData);
        if (RecNumber == 0xFF)
        {
            *SizeOfData = ((*SizeOfData) * (Dem_EnvGetTotalNumberOfStoredFFForEvent(EventId, EvMemPointer)));
        }
    }
    return returnValue;
}

DEM_INLINE boolean Dem_EvMemApi_IsSelectionFuncCalledForGetSizeCall(uint8 ApiId, uint8 ClientId)
{
    boolean returnValue;
    switch(ApiId)
    {
        case DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDSELECTION:

            returnValue = ((Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_ED_STATE_SELECTION_INVALID) ||
                            (Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_ED_ITERATION_IN_PROGRESS));
            break;

        case DEM_DET_APIID_GETSIZEOFFREEZEFRAMESELECTION:

            returnValue = ((Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_FF_STATE_SELECTION_INVALID) ||
                            (Dem_ClientMachine_SelectED_FFData_GetState(ClientId) == DEM_SELECT_FF_ITERATION_IN_PROGRESS));
            break;

        default :
            returnValue = FALSE;
            break;
    }
    return returnValue;
}

static Std_ReturnType Dem_EvMemApi_GetSizeOfDataSelection(uint8 ClientId, uint16* SizeOfData, uint8 ApiId)
{
    Std_ReturnType returnValue;

    DEM_STATIC_ASSERT((DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDSELECTION != DEM_DET_APIID_GETSIZEOFFREEZEFRAMESELECTION), DEM_DET_APIIDS_VALUE_SHOULD_NOT_BE_SAME);

    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(ApiId, DEM_E_WRONG_CONFIGURATION,0u);
        return DEM_WRONG_CLIENTID;
    }

    switch(Dem_Client_getClient(ClientId)->client_state)
    {
        case DEM_CLIENT_STATE_INIT :
        {
            DEM_DET(ApiId, DEM_E_WRONG_CONDITION,0u);
            returnValue = E_NOT_OK;
            break;
        }
        case DEM_CLIENT_STATE_PARAMETERS_SET :
        {
            if(! Dem_EvMemApi_IsSelectionFuncCalledForGetSizeCall(ApiId, ClientId)) // SelectDataRecord function not yet called..
            {
                DEM_DET(ApiId, DEM_E_WRONG_CONDITION,0u);
                returnValue = E_NOT_OK;
            }
            else
            {
                returnValue = Dem_ClientSelectionType_getSelectionResult(Dem_Client_getClient(ClientId)->selection);
                if((returnValue == E_OK) && (! Dem_ClientSelectionType_isSelectionSingleDTC(Dem_Client_getClient(ClientId)->selection)))
                {
                    returnValue = DEM_WRONG_DTC;
                }
                if (returnValue == E_OK)
                {
                    Dem_EventIdType EventId = Dem_DtcIdGetFirstEventId(Dem_ClientSelectionType_getSelectionDtcIndex(Dem_Client_getClient(ClientId)->selection));
                    Dem_EvMemEventMemoryType* EvMemPointer = Dem_ClientSelectED_FFDataType_GetEvMemCopy(ClientId);
                    if(ApiId == DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDSELECTION)
                    {
                        returnValue = Dem_EvMemApi_GetSizeOfEDDataSelection(ClientId, EventId, EvMemPointer, SizeOfData);
                    }
                    else
                    {
                        returnValue = Dem_EvMemApi_GetSizeOfFFDataSelection(ClientId, EventId, EvMemPointer, SizeOfData);
                    }

                    if(returnValue == DEM_INVALID_RECORDNUMBER)
                    {
                        returnValue = DEM_NO_SUCH_ELEMENT;
                    }
                }
            }
            break;
        }
        case DEM_CLIENT_STATE_REQUESTED_OPERATION :
        {
            if (Dem_ClientRequestType_getMachineIndex(Dem_Client_getClient(ClientId)->request) != Dem_ClientRequestType_getMachineIndex(DEM_CLIENT_REQUEST_SELECT_ED_FF_DATA)) // -> Some other Operation is requested before and it is still being processed.
            {
                DEM_DET(ApiId, DEM_E_WRONG_CONDITION,0u);
                returnValue = E_NOT_OK;
            }
            else
            {
                returnValue = DEM_PENDING;
            }
            break;
        }
        default :
        {
            returnValue = E_NOT_OK;
            break;
        }
    }
    return returnValue;
}
#endif

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06

Std_ReturnType Dem_SelectExtendedDataRecord(uint8 ClientId, uint8 ExtendedDataNumber)
{
    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_SELECTEXTENDEDDATARECORD, E_NOT_OK);
    return Dem_EvMemApi_SelectED_FF_Data(ClientId, ExtendedDataNumber, DEM_DET_APIID_SELECTEXTENDEDDATARECORD);
}

Std_ReturnType Dem_GetNextExtendedDataRecord(uint8 ClientId, uint8* DestBuffer, uint16* BufSize)
{
    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_GETNEXTEXTENDEDDATARECORD, E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(DestBuffer, DEM_DET_APIID_GETNEXTEXTENDEDDATARECORD, E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(BufSize, DEM_DET_APIID_GETNEXTEXTENDEDDATARECORD, E_NOT_OK);

    return Dem_EvMemApi_GetNextDataRecord(ClientId, DestBuffer, BufSize, DEM_DET_APIID_GETNEXTEXTENDEDDATARECORD);
}

Std_ReturnType Dem_GetSizeOfExtendedDataRecordSelection(uint8 ClientId, uint16* SizeOfExtendedDataRecord)
{
    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDSELECTION, E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(SizeOfExtendedDataRecord, DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDSELECTION, E_NOT_OK);

    return Dem_EvMemApi_GetSizeOfDataSelection(ClientId, SizeOfExtendedDataRecord, DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDSELECTION);
}
#endif

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04

Std_ReturnType Dem_SelectFreezeFrameData(uint8 ClientId, uint8 RecordNumber)
{
    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_SELECTFREEZEFRAMEDATA, E_NOT_OK);
    return Dem_EvMemApi_SelectED_FF_Data(ClientId, RecordNumber, DEM_DET_APIID_SELECTFREEZEFRAMEDATA);
}

Std_ReturnType Dem_GetNextFreezeFrameData(uint8 ClientId, uint8* DestBuffer, uint16* BufSize)
{
    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_GETNEXTFREEZEFRAMEDATA, E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(DestBuffer, DEM_DET_APIID_GETNEXTFREEZEFRAMEDATA, E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(BufSize, DEM_DET_APIID_GETNEXTFREEZEFRAMEDATA, E_NOT_OK);

    return Dem_EvMemApi_GetNextDataRecord(ClientId, DestBuffer, BufSize, DEM_DET_APIID_GETNEXTFREEZEFRAMEDATA);
}

Std_ReturnType Dem_GetSizeOfFreezeFrameSelection(uint8 ClientId, uint16* SizeOfFreezeFrame)
{
    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_GETSIZEOFFREEZEFRAMESELECTION, E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(SizeOfFreezeFrame, DEM_DET_APIID_GETSIZEOFFREEZEFRAMESELECTION, E_NOT_OK);

    return Dem_EvMemApi_GetSizeOfDataSelection(ClientId, SizeOfFreezeFrame, DEM_DET_APIID_GETSIZEOFFREEZEFRAMESELECTION);
}
#endif

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x03

#define DEM_START_SEC_VAR_CLEARED
#include "Dem_MemMap.h"
DEM_ARRAY_DEFINE(Dem_Client_FF_FilterParamsType, Dem_Client_FF_FilterParams, DEM_CLIENTID_ARRAYLENGTH_TOTAL);
#define DEM_STOP_SEC_VAR_CLEARED
#include "Dem_MemMap.h"

static void Dem_EvMem_MarkLocWithSameDTCAsReportedUnderLock(Dem_Client_FF_FilterParamsType* FilterParam)
{

    Dem_DtcIdType DtcId;
    uint16_least ReaderCopyLocId, CurrLocIdIt;

    DEM_ASSERT_EVMEMREADERCOPIES_ISLOCKED();

    CurrLocIdIt = FilterParam->FilteredRecordLocIdIterator;
    ReaderCopyLocId = Dem_EvMemLocId2ReaderCopyLocId(CurrLocIdIt);

    DtcId = Dem_DtcIdFromEventId(Dem_EvMemGetEventMemEventId(ReaderCopyLocId));

    while (Dem_EvMemEventMemoryLocIteratorIsValid(&CurrLocIdIt, DEM_CFG_EVMEM_MEMID_PRIMARY))
    {
        ReaderCopyLocId = Dem_EvMemLocId2ReaderCopyLocId(CurrLocIdIt);
        if (Dem_DtcIdFromEventId(Dem_EvMemGetEventMemEventId(ReaderCopyLocId)) == DtcId)
        {
            FilterParam->IsFFRecordOfDTCReported[CurrLocIdIt] = TRUE;
        }
        Dem_EvMemEventMemoryLocIteratorNext(&CurrLocIdIt, DEM_CFG_EVMEM_MEMID_PRIMARY);
    }
}

static void Dem_EvMemUpdateLocIdOfDTC(Dem_Client_FF_FilterParamsType* FilterParam, Dem_EventIdType EventId)
{

    if (FilterParam->FilteredRecordFreezeFrameIdIterator == 0u)
    {

        FilterParam->FilteredRecordLocIdOfDTC = Dem_EvMemGetEventMemoryOrReaderCopyLocIdOfDtcWithVisibility(
                Dem_DtcIdFromEventId(EventId),
                DEM_CFG_EVMEM_MEMID_PRIMARY, Dem_EvMemGetShadowVisibility(), TRUE);
    }
}

static boolean Dem_EvMemGetNextFFRecordAndDTC(Dem_Client_FF_FilterParamsType* FilterParam, uint32* DTC, uint8* RecordNumber, Dem_EventIdType EventId)
{
    if(Dem_LibGetParamBool(DEM_CFG_FFRECNUM == DEM_CFG_FFRECNUM_CALCULATED))
    {
        if (FilterParam->FilteredRecordFreezeFrameIdIterator
                < Dem_EvMemGetEventMemFreezeFrameCounter(FilterParam->FilteredRecordLocIdOfDTC))
        {
            *RecordNumber = Dem_EnvGetFFRecNumFromIndex(EventId, FilterParam->FilteredRecordFreezeFrameIdIterator);
            *DTC = Dem_GetDtcCode(Dem_DtcIdFromEventId(EventId));
            FilterParam->FilteredRecordFreezeFrameIdIterator++;
            return TRUE;
        }
    }
    else
    {
        while (FilterParam->FilteredRecordFreezeFrameIdIterator < Dem_EvtParam_GetMaxNumberFreezeFrameRecords(EventId))
        {
            *RecordNumber = Dem_EnvGetFFRecNumFromIndex(EventId, FilterParam->FilteredRecordFreezeFrameIdIterator);

            if (Dem_EnvIsTriggerSet(Dem_EnvGetFFRecordTrigger(*RecordNumber), Dem_EvMemGetEventMemTrigger(FilterParam->FilteredRecordLocIdOfDTC)))
            {
                *DTC = Dem_GetDtcCode(Dem_DtcIdFromEventId(EventId));
                FilterParam->FilteredRecordFreezeFrameIdIterator++;
                return TRUE;
            }
            FilterParam->FilteredRecordFreezeFrameIdIterator++;
        }
    }

    return FALSE;
}

static Std_ReturnType Dem_EvMemGetNextFilteredRecordUnderLock(Dem_Client_FF_FilterParamsType* FilterParam, uint32* DTC, uint8* RecordNumber)
{
    uint16_least Status;
    Dem_EventIdType EventId;
    Std_ReturnType returnValue;

    DEM_ASSERT_EVMEMREADERCOPIES_ISLOCKED();

    returnValue = DEM_NO_SUCH_ELEMENT;

    while (Dem_EvMemEventMemoryLocIteratorIsValid(&FilterParam->FilteredRecordLocIdIterator,DEM_CFG_EVMEM_MEMID_PRIMARY))
    {
        Status = Dem_EvMemGetEventMemStatus(FilterParam->FilteredRecordLocIdOfDTC);
        EventId = Dem_EvMemGetEventMemEventId(FilterParam->FilteredRecordLocIdOfDTC);

        if ( (!FilterParam->IsFFRecordOfDTCReported[FilterParam->FilteredRecordLocIdIterator])
                && Dem_EvMemIsVisible(Status, Dem_EvMemGetShadowVisibility())
                && ((!Dem_isDtcIdValid(FilterParam->CurrentDtcId)) || (Dem_DtcIdFromEventId(EventId) == FilterParam->CurrentDtcId)) )
        {
            FilterParam->CurrentDtcId = Dem_DtcIdFromEventId(EventId);

            if (Dem_LibGetParamBool(DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_ONRETRIEVAL))
            {
                Dem_EvMemUpdateLocIdOfDTC(FilterParam, EventId);
            }

            if(Dem_EvMemGetNextFFRecordAndDTC(FilterParam, DTC, RecordNumber, EventId))
            {
				returnValue = E_OK;
                break;
            }

            FilterParam->FilteredRecordFreezeFrameIdIterator = 0;

            if (Dem_LibGetParamBool(DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_ONRETRIEVAL))
            {
                Dem_EvMem_MarkLocWithSameDTCAsReportedUnderLock(FilterParam);
            }
        }
        Dem_EvMemEventMemoryLocIteratorNext(&FilterParam->FilteredRecordLocIdIterator, DEM_CFG_EVMEM_MEMID_PRIMARY);
        if(Dem_EvMemEventMemoryLocIteratorIsValid(&FilterParam->FilteredRecordLocIdIterator,DEM_CFG_EVMEM_MEMID_PRIMARY))
        {
            FilterParam->FilteredRecordLocIdOfDTC = Dem_EvMemLocId2ReaderCopyLocId(FilterParam->FilteredRecordLocIdIterator);
        }
        FilterParam->CurrentDtcId = DEM_DTCID_INVALID;
    }
    return returnValue;
}

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

Std_ReturnType Dem_SetFreezeFrameRecordFilter(uint8 ClientId, Dem_DTCFormatType DTCFormat, uint16* NumberOfFilteredRecords)
{
	uint16_least LocId;

	DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_SETFREEZEFRAMERECORDFILTER, E_NOT_OK);

	
    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(DEM_DET_APIID_SETFREEZEFRAMERECORDFILTER, DEM_E_WRONG_CONFIGURATION,0u);
        return E_NOT_OK;
    }
    if(NumberOfFilteredRecords == NULL_PTR)
    {

        Dem_Client_FF_FilterParams[ClientId].FilteredRecordLocIdIterator = DEM_EVMEM_INVALID_LOCID;
        DEM_DET(DEM_DET_APIID_SETFREEZEFRAMERECORDFILTER, DEM_E_PARAM_POINTER,0u);
        return E_NOT_OK;
    }
	if(DTCFormat != DEM_DTC_FORMAT_UDS)
	{
	
		Dem_Client_FF_FilterParams[ClientId].FilteredRecordLocIdIterator = DEM_EVMEM_INVALID_LOCID;
		DEM_DET(DEM_DET_APIID_SETFREEZEFRAMERECORDFILTER, DEM_E_PARAM_DATA,0u);
	    return E_NOT_OK;
	}
	

	*NumberOfFilteredRecords = 0;

    Dem_EvMemReaderCopiesEnterLock();
	
	for (Dem_EvMemEventMemoryLocIteratorNew     (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
	     Dem_EvMemEventMemoryLocIteratorIsValid (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
	     Dem_EvMemEventMemoryLocIteratorNext    (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY))
	{
	    uint16_least LocIdIterator = Dem_EvMemLocId2ReaderCopyLocId(LocId);
        if ( Dem_EvMemIsVisible(Dem_EvMemGetEventMemStatus(LocIdIterator), Dem_EvMemGetShadowVisibility()))
        {
            *NumberOfFilteredRecords = *NumberOfFilteredRecords + Dem_EvMemGetEventMemFreezeFrameCounter (LocIdIterator);
        }
		
	    Dem_Client_FF_FilterParams[ClientId].IsFFRecordOfDTCReported[LocId] = FALSE;
	}
	Dem_EvMemReaderCopiesExitLock();

	
	Dem_EvMemEventMemoryLocIteratorNew (&Dem_Client_FF_FilterParams[ClientId].FilteredRecordLocIdIterator, DEM_CFG_EVMEM_MEMID_PRIMARY);
    Dem_Client_FF_FilterParams[ClientId].FilteredRecordLocIdOfDTC = Dem_EvMemLocId2ReaderCopyLocId(Dem_Client_FF_FilterParams[ClientId].FilteredRecordLocIdIterator);
	Dem_Client_FF_FilterParams[ClientId].FilteredRecordFreezeFrameIdIterator = 0;
	Dem_Client_FF_FilterParams[ClientId].CurrentDtcId = DEM_DTCID_INVALID;

	return E_OK;
}

Std_ReturnType Dem_GetNextFilteredRecord(uint8 ClientId, uint32* DTC, uint8* RecordNumber)
{
    Std_ReturnType returnValue;

    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_GETNEXTFILTEREDRECORD, E_NOT_OK);

    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(DEM_DET_APIID_GETNEXTFILTEREDRECORD, DEM_E_WRONG_CONFIGURATION,0u);
        return E_NOT_OK;
    }
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(DTC, DEM_DET_APIID_GETNEXTFILTEREDRECORD, E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(RecordNumber, DEM_DET_APIID_GETNEXTFILTEREDRECORD, E_NOT_OK);

    Dem_EvMemReaderCopiesEnterLock();
    returnValue = Dem_EvMemGetNextFilteredRecordUnderLock(&Dem_Client_FF_FilterParams[ClientId], DTC, RecordNumber); // Instead of passing ClientId, the pointer to structure can be passed.
    Dem_EvMemReaderCopiesExitLock();

    return returnValue;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"
Dem_ReadEventType Dem_ReadEventsFromMemory (Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_DTCOriginType origin)
{
	ReadEventsFromMemoryState->evMemId = Dem_EvMemGetEvMemIdFromOrigin(origin);
	if (Dem_EvMemIsOriginSupported(origin))
	{
		Dem_EvMemEventMemoryLocIteratorNew (&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId);
		return DEM_READEVENT_OK;
	}
	else
	{
		Dem_EvMemEventMemoryLocIteratorInvalidate(&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId);
		return DEM_READEVENT_WRONG_ORIGIN;
	}
}

Dem_ReadEventType Dem_GetNextEventFromMemory (Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_EventIdType* EventId, uint16* LocId)
{
	while (Dem_EvMemEventMemoryLocIteratorIsValid (&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId))
	{
		*EventId = Dem_EvMemGetEventMemEventId (ReadEventsFromMemoryState->locIterator);
		
		*LocId = (uint16)ReadEventsFromMemoryState->locIterator;
		Dem_EvMemEventMemoryLocIteratorNext (&ReadEventsFromMemoryState->locIterator,ReadEventsFromMemoryState->evMemId);

		if (Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus((uint16_least)*LocId)))
		{
			return DEM_READEVENT_OK;
		}
	}
	return DEM_READEVENT_NO_MATCHING_ELEMENT;
}

DEM_INLINE uint8 Dem_EvMemGetNoOfEntries(uint16_least MemId)
{
    uint16_least LocId;
    uint8 counter = 0;

    if (Dem_EvMemIsMemIdValid(MemId))
    {
        for (Dem_EvMemEventMemoryLocIteratorNew(&LocId, MemId); Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
                Dem_EvMemEventMemoryLocIteratorNext(&LocId, MemId))
        {
            if (Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)))
            {
                counter++;
            }
        }
    }
    return counter;
}

Std_ReturnType Dem_GetNumberOfEventMemoryEntries(uint8 ClientId, Dem_DTCOriginType DTCOrigin, uint8* NumberOfEventMemoryEntries)
{
    Std_ReturnType retVal = E_NOT_OK;

    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES,E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(NumberOfEventMemoryEntries,DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES,E_NOT_OK);

    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES, DEM_E_WRONG_CONFIGURATION,0u);
        return E_NOT_OK;
    }

    if (!Dem_EvMemIsDtcOriginValid(&DTCOrigin))
    {
        DEM_DET(DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES, DEM_E_WRONG_CONFIGURATION,0u);
        retVal = E_NOT_OK;
    }

    if (DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
    {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_PRIMARY);
        retVal = E_OK;
    }

#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
    if (DTCOrigin == DEM_DTC_ORIGIN_SECONDARY_MEMORY)
    {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_SECONDARY);
        retVal = E_OK;
    }
#endif

#if (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
    if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
    {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_MIRROR);
        retVal = E_OK;
    }
#elif DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
    if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
    {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_SHADOW);
        retVal = E_OK;
    }
#endif
    return retVal;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"

#endif

