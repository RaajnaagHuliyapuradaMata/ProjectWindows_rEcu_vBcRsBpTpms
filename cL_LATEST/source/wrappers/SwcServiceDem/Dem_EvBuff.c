

#include "Dem.hpp"
#include "Rte_Dem.hpp"

#include "Dem_EvBuff.hpp"

#include "Dem_Bfm.hpp"
#include "Dem_Cfg_EvBuff.hpp"
#include "Dem_Helpers.hpp"
#include "Dem_EnvMain.hpp"
#include "Dem_EventFHandling.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_EventRecheck.hpp"
#include "Dem_Obd.hpp"
#include "Dem_J1939EnvFreezeFrame.hpp"

#include "Dem_Lock.hpp"
#include "Dem_Cfg_Events_DataStructures.hpp"

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
#include "Dem_PrjSpecificFailureMemory.hpp"
#endif

#define DEM_START_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"
Dem_EvtBufferState Dem_EvtBuffer;
#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include "Dem_MemMap.hpp"

#if(DEM_CFG_FFPRESTORAGE_NONVOLATILE == DEM_CFG_FFPRESTORAGE_NONVOLATILE_ON)
#define DEM_START_SEC_CONST
#include "Dem_MemMap.hpp"
DEM_ARRAY_DEFINE_CONST(Dem_NvmBlockIdType, Dem_PreStoredFFNvmId, DEM_CFG_PRESTORED_FF_SIZE, DEM_CFG_PRESTORED_FREEZEFRAME_NVMIDS);
#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.hpp"
#endif

#define DEM_LOCATIONPRIO_NOOVERWRITE     (0u)
#define DEM_LOCATIONPRIO_TYPESHIFT       (12u)
#define DEM_LOCATIONPRIO_EMPTY           (0xFFFFFFu)
#define DEM_LOCATIONPRIO_SAME_EVENTID    (0xFFFFFFu+1u)

#if DEM_CFG_PRESTORED_FF_SIZE > DEM_CFG_EVBUFF_SIZE
#error DEM_CFG_PRESTORED_FF_SIZE must be smaller than DEM_CFG_EVBUFF_SIZE
#endif

DEM_INLINE uint32 Dem_EvBuffGetEventPriority (Dem_EventIdType EventId, Dem_EvBuffEventType eventType)
{
    return ((uint32)eventType << DEM_LOCATIONPRIO_TYPESHIFT) +  (uint32)EventId;
}

DEM_INLINE uint32 Dem_EvBuffGetLocationPriority (const Dem_EvBuffEvent *bufferElement)
{

   if(bufferElement->eventId == DEM_EVENTID_INVALID)
   {
        return DEM_LOCATIONPRIO_EMPTY;
   }

   if(bufferElement->eventType == C_EVENTTYPE_SET)
   {

        return DEM_LOCATIONPRIO_NOOVERWRITE;
   }

    return Dem_EvBuffGetEventPriority (bufferElement->eventId, bufferElement->eventType);
}

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

static void Dem_EvBuffInvalidateLocation(uint32_least locId)
{
    Dem_EvtBuffer.Locations[locId].eventId = DEM_EVENTID_INVALID;
    Dem_EvtBuffer.Locations[locId].IsEnvDataCaptured = FALSE;
}

static uint8_least Dem_EvBuffGetLocationToWrite (Dem_EventIdType EventIdOfNewEvent, Dem_EvBuffEventType *typeOfNewEvent)
{
   uint8_least i = DEM_CFG_EVBUFF_SIZE;
   uint8_least checkLoc;
   uint32_least prioOfNewEvent = Dem_EvBuffGetEventPriority (EventIdOfNewEvent, *typeOfNewEvent);

   uint8_least writeLoc = DEM_CFG_EVBUFF_SIZE;
   uint32_least writeLocPrio = prioOfNewEvent;
   uint32_least tempPrio;

   while(i > 0u)
   {
        i--;

        if(*typeOfNewEvent != C_EVENTTYPE_PRESTORE)
        {

            checkLoc = i;
        }
        else{
#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

            checkLoc = (DEM_CFG_EVBUFF_SIZE - 1u) - i;

            if(checkLoc >= DEM_CFG_PRESTORED_FF_SIZE)
            {
                break;
            }
#else
            break;
#endif
        }

        if(Dem_EvtBuffer.Locations[checkLoc].eventId == EventIdOfNewEvent)
        {

            if(Dem_EvtBuffer.Locations[checkLoc].eventType >= *typeOfNewEvent)
            {
                return checkLoc;
            }

            if(   (Dem_EvtBuffer.Locations[checkLoc].eventType == C_EVENTTYPE_SET)
                    && (*typeOfNewEvent                     == C_EVENTTYPE_RESET))
            {
                *typeOfNewEvent = C_EVENTTYPE_SET_RESET;
                return checkLoc;
            }

            return DEM_CFG_EVBUFF_SIZE;
        }

        tempPrio = Dem_EvBuffGetLocationPriority (&Dem_EvtBuffer.Locations[checkLoc]);
        if(tempPrio > writeLocPrio)
        {
            writeLoc = checkLoc;
            writeLocPrio = tempPrio;
        }
   }

   if(writeLoc == DEM_CFG_EVBUFF_SIZE)
   {
        Dem_EvtBuffer.OverflowCounter++;
        if(*typeOfNewEvent == C_EVENTTYPE_SET)
        {
            Dem_EvtBuffer.OverflowCounterSet++;
        }
   }

    return writeLoc;
}

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)

static void Dem_EvBuffStoreDataToLocation(uint32 indx, const Dem_EvBuffEvent *tmpEvData)
{
   if(!tmpEvData->IsEnvDataCaptured)
   {
        DEM_DET(DEM_DET_APIID_EVENTDATANOTCAPTURED, DEM_E_NODATAAVAILABLE,0u);
        return;
   }

    DEM_MEMCPY(&(Dem_EvtBuffer.Locations[indx].memData.envData), &(tmpEvData->memData.envData), DEM_SIZEOF_VAR(Dem_EvtBuffer.Locations[indx].memData.envData));

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
    DEM_MEMCPY(&Dem_EvtBuffer.Locations[indx].memData.DemRbProjectSpecificFailureMemoryData, &(tmpEvData->memData.DemRbProjectSpecificFailureMemoryData), DEM_SIZEOF_TYPE(DemRbProjectSpecificFailureMemoryType));
#endif

#if(DEM_BFM_ENABLED == DEM_BFM_ON)
    DEM_MEMCPY(&Dem_EvtBuffer.Locations[indx].memData.DemRbBfmFailureMemoryData, &(tmpEvData->memData.DemRbBfmFailureMemoryData), DEM_SIZEOF_TYPE(rba_DemBfm_EnvironmentalData));
#endif

    Dem_EvtBuffer.Locations[indx].IsEnvDataCaptured = TRUE;
}

#endif

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

DEM_INLINE Dem_boolean_least Dem_EvBuffIsPrestoreLocationAvailable (uint32 locationIndex, Dem_EventIdType newEventId)
{

#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

    return (   (Dem_EvtBuffer.Locations[locationIndex].eventId == newEventId)
            && (Dem_EvtBuffer.Locations[locationIndex].eventType == C_EVENTTYPE_PRESTORE));

#else

    DEM_UNUSED_PARAM(locationIndex);
    DEM_UNUSED_PARAM(newEventId);
    return FALSE;

#endif
}

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"
static void Dem_EvBuffHandleElapsedCounter(const Dem_EvBuffEvent *bufferElement)
{

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

   if(   (bufferElement->eventType != C_EVENTTYPE_UNROBUST)
        && (bufferElement->eventType != C_EVENTTYPE_PRESTORE)
        )
   {
        Dem_EvtSetIsRecheckedAndWaitingForMonResult(bufferElement->eventId, FALSE);
   }

#endif

    DEM_UNUSED_PARAM(bufferElement);
}

void Dem_EvBuffMainFunction(void){

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)

   uint32_least i = DEM_CFG_EVBUFF_SIZE;
    Dem_EvBuffEvent tmpEvBuffLocation;

    DEM_ENTERLOCK_MON();

   while(i > 0u)
   {
        i--;

        if(Dem_EvtBuffer.Locations[i].eventId != DEM_EVENTID_INVALID)
        {
            if(!Dem_EvtBuffer.Locations[i].IsEnvDataCaptured)
            {
                tmpEvBuffLocation.eventId = Dem_EvtBuffer.Locations[i].eventId;
                tmpEvBuffLocation.eventType = Dem_EvtBuffer.Locations[i].eventType;
                tmpEvBuffLocation.IsEnvDataCaptured = FALSE;
#if(DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
                tmpEvBuffLocation.debug0 = Dem_EvtBuffer.Locations[i].debug0;
                tmpEvBuffLocation.debug1 = Dem_EvtBuffer.Locations[i].debug1;
#endif

                DEM_EXITLOCK_MON();

                Dem_EvBuffCaptureAllEnvData(&tmpEvBuffLocation, &tmpEvBuffLocation.memData);

               DEM_ENTERLOCK_MON();
                if((tmpEvBuffLocation.eventId == Dem_EvtBuffer.Locations[i].eventId) && (!Dem_EvtBuffer.Locations[i].IsEnvDataCaptured))
                {
                    Dem_EvBuffStoreDataToLocation(i, &tmpEvBuffLocation);
                }
            }
#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

            if(Dem_EvtBuffer.Locations[i].counter > 0)
            {
                Dem_EvtBuffer.Locations[i].counter--;

                if(Dem_EvtBuffer.Locations[i].counter == 0)
                {
                    Dem_EvBuffHandleElapsedCounter (&Dem_EvtBuffer.Locations[i]);
                }
            }
#endif
        }
   }

    DEM_EXITLOCK_MON();

#endif
}

void Dem_EvBuffClear(Dem_EventIdType EventId)
{
   uint32_least i = DEM_CFG_EVBUFF_SIZE;

    DEM_ENTERLOCK_MON();

   while(i > 0u)
   {
        i--;
        if(Dem_EvtBuffer.Locations[i].eventId == EventId)
        {
            Dem_EvtSetIsRecheckedAndWaitingForMonResult(EventId, FALSE);
            Dem_EvBuffInvalidateLocation(i);
            break;
        }
   }

    DEM_EXITLOCK_MON();
}

const Dem_EvBuffEvent* Dem_EvBuffGetEvent (uint32* locationIndex)
{
    Dem_EvBuffEvent* fEvent = NULL_PTR;
   uint16_least i = DEM_CFG_EVBUFF_SIZE;

   while(i > 0u)
   {
        i--;

        if(Dem_EvtBuffer.Locations[i].eventId != DEM_EVENTID_INVALID)
        {
            if(   (Dem_EvBuffGetCounter(&(Dem_EvtBuffer.Locations[i])) == 0)
#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
                    && (Dem_EvtBuffer.Locations[i].eventType != C_EVENTTYPE_PRESTORE)
#endif
            )
            {
                *locationIndex = i;
                fEvent = &(Dem_EvtBuffer.Locations[i]);
                break;
            }
        }
   }
    return fEvent;
}

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
uint8_least Dem_EvBuffClearSequentialFailures (Dem_EventIdType EventId, Dem_ComponentIdType nodeID, uint8 counterInit)
{
   uint8_least i = DEM_CFG_EVBUFF_SIZE;
   uint8_least minCounter = counterInit;

    DEM_ENTERLOCK_MON();

   while(i > 0u)
   {
        i--;

        if(   (Dem_EvtBuffer.Locations[i].eventId != DEM_EVENTID_INVALID)
                && (   (Dem_EvtBuffer.Locations[i].eventType == C_EVENTTYPE_SET)
                        || (Dem_EvtBuffer.Locations[i].eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
                )
                && (Dem_EvtBuffer.Locations[i].counter > 0)
        )
        {

            if(   (Dem_NodeAreAncestorsFailed(Dem_FailureEvent_getNodeId(&Dem_EvtBuffer.Locations[i])))
                    || (   (Dem_FailureEvent_getNodeId(&Dem_EvtBuffer.Locations[i]) == nodeID)
                            && (Dem_EvtBuffer.Locations[i].eventId > EventId)
                            && (!Dem_NodeIgnorePriority(nodeID))
                    )
            )
            {

                Dem_EvtSetCausal (Dem_EvtBuffer.Locations[i].eventId, FALSE);
                Dem_EvtSetIsRecheckedAndWaitingForMonResult(Dem_EvtBuffer.Locations[i].eventId, FALSE);

                DEM_A_MIN_AB (minCounter, Dem_EvtBuffer.Locations[i].counter);

                Dem_EvBuffInvalidateLocation(i);
            }
        }
   }

    DEM_EXITLOCK_MON();

    return minCounter;
}
#endif

void Dem_EvBuffEnvCaptureData(
    Dem_EventIdType EventId
   ,  uint8 *EnvData
    DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0,Dem_DebugDataType debug1))
{

    Dem_EnvCaptureED(EventId, EnvData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(debug0,debug1));
    Dem_EnvCaptureFF(EventId, EnvData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(debug0,debug1));

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
    rba_DemObdBasic_FF_CaptureFF(EventId, EnvData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA);
#endif

#if(DEM_CFG_J1939DCM_FREEZEFRAME_SUPPORT)
    Dem_J1939EnvCaptureFF(EventId, EnvData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(debug0,debug1));
#endif
#if(DEM_CFG_J1939DCM_EXPANDED_FREEZEFRAME_SUPPORT)
    Dem_J1939EnvCaptureExpFF(EventId, EnvData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(debug0,debug1));
#endif
}

Dem_boolean_least Dem_EvBuffInsert (Dem_EvBuffEventType eventType
   ,       Dem_EventIdType eventId
        DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0,Dem_DebugDataType debug1))
{

    Dem_boolean_least eventInserted = FALSE;
   uint8_least counter = 0;
    Dem_boolean_least skipCausalCheck_flag = FALSE;
   uint8_least storeLoc;

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)
    Dem_EvBuffEvent tmpEvBuffLocation;
    tmpEvBuffLocation.IsEnvDataCaptured = FALSE;
#endif

    DEM_ASSERT_ISNOTLOCKED();

   if(   (eventType == C_EVENTTYPE_SET)
            || (eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
    )
   {
        counter = Dem_EvBuffClearSequentialFailures (eventId, Dem_NodeIdFromEventId(eventId)
   ,               Dem_EvtParam_GetBufferTimeSFB(eventId));
   }

   if(eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
   {
        counter = DEM_CFG_EVBUFF_DELAY_SET_WAITINGFORMONITORING;
   }

   if(eventType == C_EVENTTYPE_SET_RECONFIRMED)
   {
            eventType = C_EVENTTYPE_SET;
            counter = 0;
            skipCausalCheck_flag = TRUE;
   }

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)
   if((Dem_LibGetParamBool(DEM_CFG_ENVIRONMENT_DATA_CAPTURE == DEM_CFG_CAPTURE_SYNCHRONOUS_TO_REPORTING))
#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
            || (eventType == C_EVENTTYPE_PRESTORE)
#endif
       )
   {
        tmpEvBuffLocation.eventId = eventId;
        tmpEvBuffLocation.eventType = eventType;
#if(DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
        tmpEvBuffLocation.debug0 = debug0;
        tmpEvBuffLocation.debug1 = debug1;
#endif
        Dem_EvBuffCaptureAllEnvData(&tmpEvBuffLocation, &tmpEvBuffLocation.memData);
   }
#endif

    DEM_ENTERLOCK_MON();

        if((!skipCausalCheck_flag) &&  ((eventType == C_EVENTTYPE_SET)
                || (eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
                || (eventType == C_EVENTTYPE_UNROBUST))
            )
        {

                if(!Dem_Dependencies_CheckEventIsCausal(eventId, Dem_NodeIdFromEventId(eventId)) )
                {

                    DEM_EXITLOCK_MON();
                    return FALSE;
                }
        }

   storeLoc = Dem_EvBuffGetLocationToWrite(eventId, &eventType);

   if(storeLoc != DEM_CFG_EVBUFF_SIZE)
   {
        if(        (Dem_EvtBuffer.Locations[storeLoc].eventId != DEM_EVENTID_INVALID)
                && (Dem_EvtBuffer.Locations[storeLoc].eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
            )
        {
            if(Dem_EvtBuffer.Locations[storeLoc].eventId != eventId)
            {
                Dem_EvtBuffer.OverflowCounter++;
                Dem_EvtSetIsRecheckedAndWaitingForMonResult(Dem_EvtBuffer.Locations[storeLoc].eventId, FALSE);
                Dem_EvtSetCausal (Dem_EvtBuffer.Locations[storeLoc].eventId, FALSE);
                if(eventType == C_EVENTTYPE_RESET)
                {
                    Dem_EvtSetPassedWasReported (eventId, TRUE);
                }
            }

            if(    (eventId == Dem_EvtBuffer.Locations[storeLoc].eventId)
                 && (eventType == C_EVENTTYPE_RESET)
                 && (!Dem_EvtIsNextReportRelevantForMemories(eventId))
               )
            {
                Dem_EvBuffInvalidateLocation(storeLoc);

                DEM_EXITLOCK_MON();
                return FALSE;
            }
        }

        if(   !( Dem_EvBuffIsPrestoreLocationAvailable(storeLoc, eventId)
                  && (   (eventType == C_EVENTTYPE_SET)
                      || (eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
                     )
                 )
             && (eventType != C_EVENTTYPE_SET_RESET)
           )
        {

            Dem_EvtBuffer.Locations[storeLoc].eventId = eventId;

#if(DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
            Dem_EvtBuffer.Locations[storeLoc].debug0 = debug0;
            Dem_EvtBuffer.Locations[storeLoc].debug1 = debug1;
#endif

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)
            if(tmpEvBuffLocation.IsEnvDataCaptured)
            {
                Dem_EvBuffStoreDataToLocation(storeLoc, &tmpEvBuffLocation);
            }

#endif

        }

        Dem_EvtBuffer.Locations[storeLoc].eventType = eventType;
        Dem_EvBuffSetCounter(&(Dem_EvtBuffer.Locations[storeLoc]), (uint8)counter);

        eventInserted = TRUE;

        if(counter == 0u)
        {
            Dem_EvBuffHandleElapsedCounter (&Dem_EvtBuffer.Locations[storeLoc]);
        }
   }

    DEM_EXITLOCK_MON();
    return eventInserted;
}

void Dem_EvBuffRemoveEvent (uint32 locationIndex)
{
    DEM_ASSERT_ISLOCKED();
   if(locationIndex < DEM_CFG_EVBUFF_SIZE)
   {
        Dem_EvBuffInvalidateLocation(locationIndex);
   }
}

#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

static void Dem_EvBuffRemovePrestored (Dem_EventIdType EventId)
{
   uint8_least i;

    DEM_ENTERLOCK_MON();

   for(i=0; i < DEM_CFG_PRESTORED_FF_SIZE; i++)
   {

        if(    (   (Dem_EvtBuffer.Locations[i].eventId == EventId)
                || (EventId == DEM_EVENTID_INVALID))
                && (Dem_EvtBuffer.Locations[i].eventType == C_EVENTTYPE_PRESTORE)
        )
        {
            Dem_EvBuffInvalidateLocation(i);
        }
   }

    DEM_EXITLOCK_MON();
}

void Dem_EvBuffRemoveAllPrestored (void){
    Dem_EvBuffRemovePrestored (DEM_EVENTID_INVALID);
}

#endif

Dem_boolean_least Dem_EvBuffIsEventPending (Dem_EventIdType EventId)
{
    Dem_boolean_least EventFound = FALSE;
   uint8_least i = DEM_CFG_EVBUFF_SIZE;

    DEM_ENTERLOCK_MON();

   while(i > 0u)
   {
        i--;

        if(   ((Dem_EvtBuffer.Locations[i].eventId == EventId) || (DEM_EVENTID_INVALID == EventId))

#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
                && (Dem_EvtBuffer.Locations[i].eventType != C_EVENTTYPE_PRESTORE)
#endif
        )
        {
            EventFound = TRUE;
            i = 0u;
        }
   }

    DEM_EXITLOCK_MON();

    return EventFound;
}

Std_ReturnType Dem_PrestoreFreezeFrameWithEnvData( Dem_EventIdType EventId ,Dem_DebugDataType debug0 ,Dem_DebugDataType debug1 )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

#if(DEM_CFG_DEBUGDATA == DEM_CFG_DEBUGDATA_OFF)
    DEM_UNUSED_PARAM(debug0);
    DEM_UNUSED_PARAM(debug1);
#endif

#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

    DEM_ENTRY_CONDITION_CHECK_EVENT_ID_VALID_AVAILABLE(EventId,DEM_DET_APIID_PRESTOREFREEZEFRAME,E_NOT_OK);

   if(Dem_EvtParam_GetIsEventOBDRelevant(EventId))
   {
        DEM_ENTRY_CONDITION_CHECK_EVENT_ID_SUPPORT_FF_PRESTORAGE(EventId,DEM_DET_APIID_PRESTOREFREEZEFRAME,E_NOT_OK);
   }

   if(Dem_EvBuffInsert(C_EVENTTYPE_PRESTORE, EventId DEM_DEBUGDATA_PARAM(debug0, debug1)))
   {
        ReturnValue = E_OK;
   }

#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(debug0);
    DEM_UNUSED_PARAM(debug1);
#endif

    return ReturnValue;
}

Std_ReturnType Dem_PrestoreFreezeFrame(Dem_EventIdType EventId)
{
    return Dem_PrestoreFreezeFrameWithEnvData(EventId,0,0);
}

Std_ReturnType Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId)
{

#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
    DEM_ENTRY_CONDITION_CHECK_EVENT_ID_VALID_AVAILABLE(EventId,DEM_DET_APIID_DEM_CLEARPRESTOREDFREEZEFRAME,E_NOT_OK);

    Dem_EvBuffRemovePrestored(EventId);
    return E_OK;

#else
    DEM_UNUSED_PARAM(EventId);
    return E_NOT_OK;
#endif
}

#if(DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

void Dem_PreStoredFFInitCheckNvM(void){
#if(DEM_CFG_FFPRESTORAGE_NONVOLATILE == DEM_CFG_FFPRESTORAGE_NONVOLATILE_ON)
   uint8 i;
    Dem_NvmResultType NvmResult;

   for(i = 0; i < DEM_CFG_PRESTORED_FF_SIZE; i++)
   {
        if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
        {

            DEM_MEMSET(&Dem_EvtBuffer.Locations[i], 0, DEM_SIZEOF_VAR(Dem_EvtBuffer.Locations[i]));
            Dem_NvMClearBlockByInvalidate(Dem_PreStoredFFNvmId[i]);
        }
        else{

            NvmResult = Dem_NvmGetStatus (Dem_PreStoredFFNvmId[i]);

            if(NvmResult == DEM_NVM_SUCCESS)
            {

                if(!Dem_isEventIdValid(Dem_EvtBuffer.Locations[i].eventId))
                {
                    NvmResult = DEM_NVM_FAILED;
                }
            }

            if(NvmResult != DEM_NVM_SUCCESS)
            {

                DEM_MEMSET(&Dem_EvtBuffer.Locations[i], 0, DEM_SIZEOF_VAR(Dem_EvtBuffer.Locations[i]));
                Dem_NvMWriteBlockOnShutdown(Dem_PreStoredFFNvmId[i]);
            }
        }
   }

    //to avoid problems with "saved zone" feature the rest has to be initialized to zero
   for(i = DEM_CFG_PRESTORED_FF_SIZE; i < DEM_CFG_EVBUFF_SIZE; i++)
   {

        DEM_MEMSET(&Dem_EvtBuffer.Locations[i], 0, DEM_SIZEOF_VAR(Dem_EvtBuffer.Locations[i]));
   }

#endif
}

void Dem_PreStoredFFShutdown(void){
#if(DEM_CFG_FFPRESTORAGE_NONVOLATILE == DEM_CFG_FFPRESTORAGE_NONVOLATILE_ON)
   uint8 i;

   for(i = 0; i < DEM_CFG_PRESTORED_FF_SIZE; i++)
   {
        Dem_NvMWriteBlockOnShutdown(Dem_PreStoredFFNvmId[i]);
   }
#endif
}
#endif

void Dem_EvBuffCaptureAllEnvData(Dem_EvBuffEvent *evBuffEvent, Dem_EvBuffEvent_MemData *memData)
{

   if((evBuffEvent->eventType == C_EVENTTYPE_RESET) && Dem_LibGetParamBool(DEM_CFG_EVMEM_EXTENDED_DATA_ON_PASSED_SUPPORTED))
   {
        Dem_EnvCaptureED(evBuffEvent->eventId, memData->envData.Buffer, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(evBuffEvent->debug0,evBuffEvent->debug1));
   }
   else{
        Dem_EvBuffEnvCaptureData(evBuffEvent->eventId, memData->envData.Buffer  DEM_DEBUGDATA_PARAM(evBuffEvent->debug0, evBuffEvent->debug1));
   }

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
    rba_DemBfm_EnvCaptureBFM(evBuffEvent->eventId, &(memData->DemRbBfmFailureMemoryData) DEM_DEBUGDATA_PARAM(evBuffEvent->debug0, evBuffEvent->debug1));
#endif

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
    Dem_ProjectSpecificFailureMemoryCapture(evBuffEvent->eventId, evBuffEvent->eventType, &(memData->DemRbProjectSpecificFailureMemoryData));
#endif

    evBuffEvent->IsEnvDataCaptured = TRUE;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"
