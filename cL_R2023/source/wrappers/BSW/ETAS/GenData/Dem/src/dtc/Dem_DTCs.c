

#include "Dem.h"
#include "Dem_Dcm_Internal.h"
#include "Rte_Dem.h"

#include "Dem_DTCs.h"

#include "Dem_Deb.h"
#include "Dem_Events.h"
#include "Dem_EventStatus.h"
#include "Dem_Nvm.h"
#include "Dem_Mapping.h"
#include "Dem_Obd.h"
#include "Dem_DTCGroup.h"
#include "Dem_Lok_J1939Dcm.h"
#include "Dem_Cfg_ExtPrototypes.h"
#include "Dem_ClientBaseHandling.h"
#include "Dem_Cfg_Client_DataStructures.h"

#define DEM_START_SEC_VAR_CLEARED
#include "Dem_MemMap.h"

    DEM_ARRAY_DEFINE(Dem_DtcState, Dem_AllDTCsState, DEM_DTCID_ARRAYLENGTH);

#define DEM_STOP_SEC_VAR_CLEARED
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_INIT
#include "Dem_MemMap.h"

    #if (DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
    boolean Dem_AlternativeDTCEnabled = FALSE;
    #endif

#define DEM_STOP_SEC_VAR_INIT
#include "Dem_MemMap.h"

#define DEM_START_SEC_CONST
#include "Dem_MemMap.h"

#if (DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
 DEM_ARRAY_DEFINE_CONST(Dem_DtcAltParam, Dem_AllAlternativeDTCsParam, DEM_ALTERNATIVE_DTCCODE_ARRAYLENGTH, DEM_CFG_ALTERNATIVE_DTCPARAMS);
#endif

#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.h"

#define DEM_START_SEC_VAR_CLEARED
#include "Dem_MemMap.h"
DemControlDtcSettingType Dem_DtcSettingDisabledFlag = FALSE;
#define DEM_STOP_SEC_VAR_CLEARED
#include "Dem_MemMap.h"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.h"

#if (DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
void Dem_SwitchToAlternativeDtc(void)
{
	Dem_AlternativeDTCEnabled = TRUE;
}
#endif

static void Dem_DtcApplyDTCSetting(uint8 ClientId, boolean newDtcSettingState)
{
    Dem_DtcIdIterator dtcIt;
    Dem_DtcIdType LockCounter = 0;

    DEM_UNUSED_PARAM(ClientId);

    DEM_ENTERLOCK_MON();
    for (Dem_DtcIdIteratorNew(&dtcIt); Dem_DtcIdIteratorIsValid(&dtcIt); Dem_DtcIdIteratorNext(&dtcIt))
    {
        Dem_DtcSetDTCSetting(Dem_DtcIdIteratorCurrent(&dtcIt), newDtcSettingState);

        LockCounter++;
        if (LockCounter >= DEM_NUMBER_OF_DTCS_TO_PROCESS_PER_LOCK)
        {
            DEM_EXITLOCK_MON();

            LockCounter = 0;
            DEM_ENTERLOCK_MON();
        }
    }
    DEM_EXITLOCK_MON();

    Dem_SetDtcSettingFlag(newDtcSettingState);
}

Std_ReturnType Dem_EnableDTCSetting (uint8 ClientId)
{
    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(DEM_DET_APIID_ENABLEDTCSETTING, DEM_E_WRONG_CONFIGURATION,0u);
        return E_NOT_OK;
    }

    Dem_DtcApplyDTCSetting(ClientId, DEM_DTC_SETTING_ENABLED);
    return E_OK;
}

Std_ReturnType Dem_DisableDTCSetting (uint8 ClientId)
{
    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(DEM_DET_APIID_DISABLEDTCSETTING, DEM_E_WRONG_CONFIGURATION,0u);
        return E_NOT_OK;
    }

    Dem_DtcApplyDTCSetting(ClientId, DEM_DTC_SETTING_DISABLED);
    return E_OK;
}

Dem_boolean_least Dem_IsEventEnabledByDtcSetting(Dem_EventIdType EventId)
{
    if (Dem_EventIdIsDtcAssigned(EventId))
    {
        if(!Dem_DtcIsDTCSettingEnabled(Dem_DtcIdFromEventId(EventId)))
        {
#if(DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED == DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_ON)
            //invoke the global config callback to get the DTC Disable status
            if(DEM_DTC_CALLBACK_FUNCTION_DISABLE_DTCSETTING_ALLOWED(EventId))
#endif
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

Dem_DtcIdType Dem_DtcIdFromDtcCode (Dem_DtcCodeType dtcCode)
{
	Dem_DtcIdIterator dtcId;

	for (Dem_DtcIdIteratorNew(&dtcId);
			Dem_DtcIdIteratorIsValid(&dtcId);
			Dem_DtcIdIteratorNext(&dtcId))
	{
		if (Dem_GetDtcCode(Dem_DtcIdIteratorCurrent(&dtcId)) == dtcCode)
		{
			return Dem_DtcIdIteratorCurrent(&dtcId);
		}
	}
	return DEM_DTCID_INVALID;
}

Std_ReturnType Dem_GetDTCOfEvent(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent)
{
   Dem_DtcIdType dtcId;

   DEM_ENTRY_CONDITION_CHECK_EVENT_ID_VALID_AVAILABLE(EventId,DEM_DET_APIID_DEM_GETDTCOFEVENT,E_NOT_OK);
   DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR_WITHEVENTID(EventId,DTCOfEvent,DEM_DET_APIID_DEM_GETDTCOFEVENT,E_NOT_OK);

   if (!Dem_EventIdIsDtcAssigned(EventId))
   {
      return DEM_E_NO_DTC_AVAILABLE;
   }

   dtcId = Dem_DtcIdFromEventId(EventId);

   if (DTCFormat == DEM_DTC_FORMAT_UDS)
   {
       *DTCOfEvent = Dem_GetDtcCode(dtcId);
       return E_OK;
   }
   else if (DTCFormat == DEM_DTC_FORMAT_OBD)
   {

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
       *DTCOfEvent = rba_DemObdBasic_Dtc_GetCode(dtcId);
       return E_OK;
#else

       return E_NOT_OK;

#endif

   }
   else if (DTCFormat == DEM_DTC_FORMAT_J1939)
   {

#if (DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)
       *DTCOfEvent = Dem_J1939DtcGetCode(dtcId);
       return E_OK;
#else

       return E_NOT_OK;

#endif

   }
   else
   {
       DEM_ASSERT_ISNOTLOCKED(); //To ensure that early return does not exit from within lock
       DEM_DET(DEM_DET_APIID_DEM_GETDTCOFEVENT,DEM_E_WRONG_CONFIGURATION,EventId);
       return E_NOT_OK;
   }
}

Std_ReturnType Dem_GetDTCOfEvent_GeneralEvtInfo(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent)
{
    return Dem_GetDTCOfEvent(EventId, DTCFormat, DTCOfEvent);
}

Dem_DTCTranslationFormatType Dem_GetTranslationType(uint8 ClientId)
{
    Dem_DTCTranslationFormatType dtcTranslationFormat = DEM_DTC_TRANSLATION_ISO15031_6;

    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(DEM_DET_APIID_GETTRANSLATIONTYPE, DEM_E_WRONG_CONFIGURATION,0u);
    }
    else
    {
        dtcTranslationFormat = Dem_Cfg_ClientParams_GetDTCTranslationFormat(ClientId);
    }
    return dtcTranslationFormat;
}

Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8 ClientId, Dem_UdsStatusByteType* DTCStatusMask)
{
    Std_ReturnType status = E_NOT_OK;

    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(DEM_DET_APIID_GETDTCSTATUSAVAILABILITYMASK, DEM_E_WRONG_CONFIGURATION,0u);
    }

    else
    {
        *DTCStatusMask = Dem_Cfg_ClientParams_GetDTCStatusAvailabilityMask(ClientId);
        status = E_OK;
    }

    return status;
}

Std_ReturnType Dem_GetSeverityOfDTC(uint8 ClientId, Dem_DTCSeverityType* DTCSeverity)
{
    Std_ReturnType operationResult;
    Dem_ClientState *client = Dem_Client_getClient(ClientId);

        operationResult = Dem_Client_Operation(ClientId, DEM_CLIENT_REQUEST_TRIGGERSELECTIONRESULT,
        DEM_DET_APIID_DEM_GETSEVERITYOFDTC);

        if (operationResult == E_OK)
        {
            if (Dem_ClientSelectionType_isSelectionSingleDTC(client->selection))
            {
                *DTCSeverity = Dem_Cfg_Dtc_GetSeverity(Dem_ClientSelectionType_getSelectionDtcIndex(client->selection));
                return E_OK;
            }
            else
            {
                return DEM_WRONG_DTC;
            }
        }

    return operationResult;
}

Std_ReturnType Dem_GetFunctionalUnitOfDTC(uint8 ClientId, uint8* DTCFunctionalUnit)
{
    Std_ReturnType operationResult;
    Dem_ClientState *client = Dem_Client_getClient(ClientId);

    operationResult = Dem_Client_Operation(ClientId, DEM_CLIENT_REQUEST_TRIGGERSELECTIONRESULT,
    DEM_DET_APIID_DEM_GETFUNCTIONAlUNITOFDTC);

    if (operationResult == E_OK)
    {
        if (Dem_ClientSelectionType_isSelectionSingleDTC(client->selection))
        {
            *DTCFunctionalUnit = Dem_Cfg_Dtc_GetFunc_Unit(Dem_ClientSelectionType_getSelectionDtcIndex(client->selection));
            return E_OK;
        }
        else
        {
            return DEM_WRONG_DTC;
        }
    }

    return operationResult;
}

Std_ReturnType Dem_SetDTCSuppression (uint8 ClientId, boolean SuppressionStatus)
{
#if ((DEM_CFG_SUPPRESSION == DEM_DTC_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))

    DEM_ENTRY_CONDITION_CHECK_DEM_PREINITIALIZED(DEM_DET_APIID_DEM_SETDTCSUPPRESSION,E_NOT_OK);

    if (SuppressionStatus == TRUE)
    {
        return Dem_Client_Operation(ClientId, DEM_CLIENT_REQUEST_ENABLE_SUPPRESSION, DEM_DET_APIID_DEM_SETDTCSUPPRESSION);
    }
    else
    {
        return Dem_Client_Operation(ClientId, DEM_CLIENT_REQUEST_DISABLE_SUPPRESSION, DEM_DET_APIID_DEM_SETDTCSUPPRESSION);
    }
#else
    DEM_UNUSED_PARAM(ClientId);
    DEM_UNUSED_PARAM(SuppressionStatus);
    return E_NOT_OK;
#endif
}

Std_ReturnType Dem_GetDTCSuppression (uint8 ClientId, boolean *SuppressionStatus)
{
    Std_ReturnType RetVal = E_NOT_OK;
#if ((DEM_CFG_SUPPRESSION == DEM_DTC_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
    Dem_DtcIdType dtcId = Dem_DtcIdFromDtcCode(Dem_Client_getClient(ClientId)->data.standard.DTC);

    DEM_ENTRY_CONDITION_CHECK_DEM_PREINITIALIZED(DEM_DET_APIID_DEM_GETDTCSUPPRESSION,E_NOT_OK);

    RetVal = Dem_Client_Operation(ClientId, DEM_CLIENT_REQUEST_GET_SUPPRESSION, DEM_DET_APIID_DEM_GETDTCSUPPRESSION);
    if(RetVal == E_OK)
    {
        *SuppressionStatus = Dem_DtcIsSuppressed(dtcId);
    }
#else
    DEM_UNUSED_PARAM(ClientId);
    DEM_UNUSED_PARAM(SuppressionStatus);
#endif
    return RetVal;
}

sint8 Dem_DtcFaultDetectionRetrieve (Dem_DtcIdType dtcId)
{
	Dem_EventIdListIterator eventIt;
	Dem_EventIdType eventId;
	sint8 faultDetectionCtrVal=0;
	sint8 maxFaultDetectionCtrVal = -128;
	sint8 returnValue = 0;

	if (Dem_DtcIsSupported(dtcId))
	{
		for (Dem_EventIdListIteratorNewFromDtcId(&eventIt, dtcId);
				Dem_EventIdListIteratorIsValid(&eventIt);
				Dem_EventIdListIteratorNext(&eventIt))
		{
			eventId = Dem_EventIdListIteratorCurrent(&eventIt);
			if (Dem_GetFaultDetectionCounter(eventId, &faultDetectionCtrVal) == E_OK)
			{
			    DEM_A_MAX_AB(maxFaultDetectionCtrVal, faultDetectionCtrVal);
			                    returnValue=maxFaultDetectionCtrVal;
			}

		}
	}
	return returnValue;
}

Std_ReturnType Dem_GetDtcFaultDetectionCounter(Dem_DtcCodeType dtcCode, sint8* FaultDetectionCounter)
{
    Dem_DtcIdType dtcId;

    if( FaultDetectionCounter != NULL_PTR )
    {
        dtcId = Dem_DtcIdFromDtcCode(dtcCode);

        if( Dem_isDtcIdValid(dtcId) )
        {
            *FaultDetectionCounter = Dem_DtcFaultDetectionRetrieve(dtcId);
            return E_OK;
        }
    }

    return E_NOT_OK;
}

void Dem_DtcSetDTCSetting (Dem_DtcIdType dtcId, Dem_boolean_least setBit)
{
    Dem_EventIdListIterator eventIt;

    DEM_ASSERT_ISLOCKED();

    DEM_DTCSTATE_OVERWRITEBIT (&Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_DTCSETTING_DISABLED, setBit);

    if (!setBit)
    {
        for (Dem_EventIdListIteratorNewFromDtcId(&eventIt, dtcId);
                Dem_EventIdListIteratorIsValid(&eventIt);
                Dem_EventIdListIteratorNext(&eventIt))
        {
            Dem_EvtSt_HandleDTCSettingOn(Dem_EventIdListIteratorCurrent(&eventIt));
            Dem_EvtSetInitMonitoring((Dem_EventIdListIteratorCurrent(&eventIt)), DEM_INIT_MONITOR_REENABLED);
#if(DEM_CFG_DTCSETTINGBLOCKSREPORTING == FALSE)
            if (Dem_ISO14229ByteIsTestFailed(Dem_EvtGetIsoByte((Dem_EventIdListIteratorCurrent(&eventIt)))))
            {
                Dem_EvtSetNextReportRelevantForMemories(Dem_EventIdListIteratorCurrent(&eventIt), TRUE);
            }
#endif
        }
    }
}

Std_ReturnType Dem_GetDTCSeverityAvailabilityMask(uint8 ClientId, Dem_DTCSeverityType* DTCSeverityMask)
{
    Std_ReturnType status = E_NOT_OK;

    if (!Dem_isClientIdValid(ClientId))
    {
        DEM_DET(DEM_DET_APIID_GETDTCSEVERITYAVAILABILITYMASK, DEM_E_WRONG_CONFIGURATION,0u);
    }

    else
    {
        *DTCSeverityMask = Dem_Cfg_ClientParams_GetDTCSeverityAvailabilityMask(ClientId);
        status = E_OK;
    }

    return status;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.h"
