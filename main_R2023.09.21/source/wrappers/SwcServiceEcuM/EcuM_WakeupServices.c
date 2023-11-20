#include "Std_Types.hpp"

#include "EcuM.hpp"
#include "EcuM_Cfg_SchM.hpp"

#include "BswM_EcuM.hpp"
#if(!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#if(!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "EcuM_Prv.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"

FUNC(void, ECUM_CODE ) EcuM_SetWakeupEvent( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources )
{

    // Variable used to hold the split wakeup events(which is not in pending or in validated wakeup) from the passed sources
   VAR(uint32, AUTOMATIC) EcuM_newWkupEvents_u32 = 0;

    // internal variable used to hold the wakeup validation timeout
   VAR(uint16, AUTOMATIC) EcuM_WkpSrcValidationTimeoutCtr_u16 = 0;

    // internal variable used to hold the wakeup events with no validation timeout
   VAR(uint32, AUTOMATIC) EcuM_dataValidatedWakeupEvents_u32 = 0;

    // internal variable used to hold the wakeup events with validation timeout
   VAR(uint32, AUTOMATIC) EcuM_dataPendingWakeupEvents_u32 = 0;

   VAR(uint8, AUTOMATIC) ctrLoop_u8 = 0;

#if ECUM_SLEEP_SUPPORT_ENABLE

   VAR(EcuM_Lok_SleepType_Enum_ten, AUTOMATIC)     id_RequestedSleepType_en = ECUM_PRV_NO_SLEEP_E;

   VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC) dataSleepModeHandle_u16 = 0xFF;
#endif//ECUM_SLEEP_SUPPORT_ENABLE

   if( EcuM_Lok_hasCheckWakeupSourceGetHandle_b( sources ) == FALSE )
   {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        (void) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SET_WKEVENT_APIID, ECUM_E_UNKNOWN_WAKEUP_SOURCE );
#endif//ECUM_DEV_ERROR_DETECT

   }
   else{

#if ECUM_SLEEP_SUPPORT_ENABLE

        id_RequestedSleepType_en = EcuM_Lok_SleepReqType_en;

        if((ECUM_PRV_GOHALT_E == id_RequestedSleepType_en) ||
   			(ECUM_PRV_GOPOLL_E == id_RequestedSleepType_en))
        {

        dataSleepModeHandle_u16 = EcuM_Lok_SleepMode_u16;

        sources = (sources & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
        }
#endif//ECUM_SLEEP_SUPPORT_ENABLE

        EcuM_newWkupEvents_u32 = ( sources & ( ~SwcServiceEcuM_tSourceWakeup_EventsPending ) & ( ~SwcServiceEcuM_tSourceWakeup_Validated )
                & ( ~EcuM_Lok_dataExpiredWakeupEvents_u32 ) );

        if( EcuM_newWkupEvents_u32 != CfgSwcServiceEcuM_dSourceWakeupNone )
        {

            // Splitting the received wakeup source to filter out the wakeup sources which are not having validation timeout to validated wakeup
            EcuM_dataValidatedWakeupEvents_u32 = ( EcuM_newWkupEvents_u32 & ECUM_WAKEUP_SOURCES_WITHOUT_VALIDATION );

            // Splitting the received wakeup source to filter out the wakeup sources which having validation timeout to pending wakeup
            EcuM_dataPendingWakeupEvents_u32   = ( EcuM_newWkupEvents_u32 & ECUM_WAKEUP_SOURCES_WITH_VALIDATION );

#if ECUM_SLEEP_SUPPORT_ENABLE
            for( ctrLoop_u8 = 0;ctrLoop_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop_u8++ )
            {

                if((EcuM_newWkupEvents_u32 & EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop_u8].WakeupSourceId)!= CfgSwcServiceEcuM_dSourceWakeupNone)

                {

                    EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop_u8].CheckWakeupTimeout = 0x00;

                    EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop_u8].CheckWakeupStatus = ECUM_SET_WAKEUP_EVENT_E;
                }

            }
#endif//ECUM_SLEEP_SUPPORT_ENABLE
        }

        if( EcuM_dataPendingWakeupEvents_u32 != CfgSwcServiceEcuM_dSourceWakeupNone )
        {

            for( ctrLoop_u8 = 0;ctrLoop_u8 < CfgSwcServiceEcuM_dNumSourceWakeup;ctrLoop_u8++ )
            {

                if( ( ( EcuM_dataPendingWakeupEvents_u32 & EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId ) != CfgSwcServiceEcuM_dSourceWakeupNone ) \
                        && ( EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].ValidationTimeout > EcuM_WkpSrcValidationTimeoutCtr_u16 ) )
                {

                    EcuM_WkpSrcValidationTimeoutCtr_u16 = EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].ValidationTimeout;

                }
            }
        }

        SwcServiceEcuM_tSourceWakeup_Validated |= EcuM_dataValidatedWakeupEvents_u32;

        SwcServiceEcuM_tSourceWakeup_ValInd |= EcuM_dataValidatedWakeupEvents_u32;

        SwcServiceEcuM_tSourceWakeup_EventsPending |=EcuM_dataPendingWakeupEvents_u32;

        EcuM_Lok_dataPndWkpEventsInd_u32 |=EcuM_dataPendingWakeupEvents_u32;

        if( EcuM_WkpSrcValidationTimeoutCtr_u16 > EcuM_Lok_WkpSrcValidationTimeoutCtr_u16 )
        {

            EcuM_Lok_WkpSrcValidationTimeoutCtr_u16 = EcuM_WkpSrcValidationTimeoutCtr_u16;

        }

   }
}

FUNC(void, ECUM_CODE ) EcuM_ValidateWakeupEvent( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources )
{

    // Variable used to hold only the wakeup sources with Comm channel reference from the passed sources
   VAR(uint32, AUTOMATIC) EcuM_CommchlWkupEvents_u32 = 0;

    // Variable used to hold only the wakeup sources with Comm channel reference from the passed sources
   VAR( Type_SwcServiceEcuM_tSourceWakeup,AUTOMATIC )  dataPendingWakeupEvents_u32 = 0;

   if( SwcServiceEcuM_bIsInitialised == FALSE )
   {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        (void) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_VAL_WKEVENT_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT

   }

   else if( EcuM_Lok_hasCheckWakeupSourceGetHandle_b( sources ) == FALSE )
   {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        (void) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_VAL_WKEVENT_APIID
   ,     ECUM_E_UNKNOWN_WAKEUP_SOURCE );
#endif//ECUM_DEV_ERROR_DETECT

   }
   else{

        SchM_Enter_EcuM();

        dataPendingWakeupEvents_u32 = SwcServiceEcuM_tSourceWakeup_EventsPending;

        SchM_Exit_EcuM();

        dataPendingWakeupEvents_u32 = dataPendingWakeupEvents_u32 & sources;
   }
   if( dataPendingWakeupEvents_u32 != CfgSwcServiceEcuM_dSourceWakeupNone )
   {

        EcuM_CommchlWkupEvents_u32 = EcuM_Lok_ComMWakeupHandling(dataPendingWakeupEvents_u32);

        if( SwcServiceEcuM_ePhase == SwcServiceEcuM_ePhaseUp )
        {

            dataPendingWakeupEvents_u32 = EcuM_CommchlWkupEvents_u32;

        }
        SchM_Enter_EcuM();

        SwcServiceEcuM_tSourceWakeup_Validated |= dataPendingWakeupEvents_u32;

        SwcServiceEcuM_tSourceWakeup_EventsPending &= ( ~dataPendingWakeupEvents_u32 );

        EcuM_Lok_dataPndWkpEventsInd_u32 &= ( ~dataPendingWakeupEvents_u32 );
        SchM_Exit_EcuM();

   }

   if(dataPendingWakeupEvents_u32 != CfgSwcServiceEcuM_dSourceWakeupNone)
           {

               BswM_EcuM_CurrentWakeup( dataPendingWakeupEvents_u32, ECUM_WKSTATUS_VALIDATED );

           }

    return;
}

FUNC(void, ECUM_CODE )EcuM_ClearWakeupEvent ( VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources )
{

   if( SwcServiceEcuM_bIsInitialised == FALSE )
   {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_CLEAR_WKEVENT_APIID, ECUM_E_UNINIT);
#endif//ECUM_DEV_ERROR_DETECT
   }

   else{

        if(EcuM_Lok_hasCheckWakeupSourceGetHandle_b(sources) == FALSE)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_CLEAR_WKEVENT_APIID
   ,     ECUM_E_UNKNOWN_WAKEUP_SOURCE);
#endif//ECUM_DEV_ERROR_DETECT
        }

        else{
                SchM_Enter_EcuM();

                if((sources &(SwcServiceEcuM_tSourceWakeup_EventsPending | SwcServiceEcuM_tSourceWakeup_Validated |
                        EcuM_Lok_dataExpiredWakeupEvents_u32 )) == CfgSwcServiceEcuM_dSourceWakeupNone)
                {

                }

                else{

                    EcuM_Lok_dataClrWkpEventsInd_u32 |= (sources &(SwcServiceEcuM_tSourceWakeup_EventsPending |
                            SwcServiceEcuM_tSourceWakeup_Validated | EcuM_Lok_dataExpiredWakeupEvents_u32 ));

                    if((SwcServiceEcuM_tSourceWakeup_EventsPending & sources)!= CfgSwcServiceEcuM_dSourceWakeupNone )
                    {
                        SwcServiceEcuM_tSourceWakeup_EventsPending  ^= (SwcServiceEcuM_tSourceWakeup_EventsPending & sources);

                        EcuM_Lok_dataPndWkpEventsInd_u32 ^= (EcuM_Lok_dataPndWkpEventsInd_u32 & sources);
                    }

                    if((SwcServiceEcuM_tSourceWakeup_Validated & sources)!= CfgSwcServiceEcuM_dSourceWakeupNone)
                    {
                        SwcServiceEcuM_tSourceWakeup_Validated^=(SwcServiceEcuM_tSourceWakeup_Validated & sources);

                        SwcServiceEcuM_tSourceWakeup_ValInd ^= (SwcServiceEcuM_tSourceWakeup_ValInd & sources);
                    }

                    if((EcuM_Lok_dataExpiredWakeupEvents_u32 & sources)!= CfgSwcServiceEcuM_dSourceWakeupNone)
                    {
                        EcuM_Lok_dataExpiredWakeupEvents_u32 ^=(EcuM_Lok_dataExpiredWakeupEvents_u32 & sources);

                        EcuM_Lok_dataExpWkpEventsInd_u32 ^=(EcuM_Lok_dataExpWkpEventsInd_u32 & sources);
                    }
                }

                SchM_Exit_EcuM();

        }
   }
}

FUNC( Type_SwcServiceEcuM_tSourceWakeup, ECUM_CODE ) EcuM_GetPendingWakeupEvents(void)
{

   uint32 PendingWakeupEvents = CfgSwcServiceEcuM_dSourceWakeupNone;

   if( SwcServiceEcuM_bIsInitialised == FALSE )
   {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        (void) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_PEND_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT

        PendingWakeupEvents =  CfgSwcServiceEcuM_dSourceWakeupNone;

   }
   else{

        PendingWakeupEvents = SwcServiceEcuM_tSourceWakeup_EventsPending;

   }

    return PendingWakeupEvents;
}

FUNC( Type_SwcServiceEcuM_tSourceWakeup, ECUM_CODE ) EcuM_GetValidatedWakeupEvents(void)
{

   uint32 ValidatedWakeupEvents = CfgSwcServiceEcuM_dSourceWakeupNone;

   if( SwcServiceEcuM_bIsInitialised == FALSE )
   {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        (void) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_VALIDATE_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT

        ValidatedWakeupEvents = CfgSwcServiceEcuM_dSourceWakeupNone;

   }
   else{

        ValidatedWakeupEvents = SwcServiceEcuM_tSourceWakeup_Validated;

   }

    return ValidatedWakeupEvents;
}

FUNC( Type_SwcServiceEcuM_tSourceWakeup, ECUM_CODE ) EcuM_GetExpiredWakeupEvents(void)
{

       uint32 ExpiredWakeupEvents = CfgSwcServiceEcuM_dSourceWakeupNone;

   if( SwcServiceEcuM_bIsInitialised == FALSE )
   {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        (void) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_EXPIRED_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT

       ExpiredWakeupEvents = CfgSwcServiceEcuM_dSourceWakeupNone;

   }
   else{

     ExpiredWakeupEvents = EcuM_Lok_dataExpiredWakeupEvents_u32;

   }

    return ExpiredWakeupEvents;
}

FUNC(void, ECUM_CODE) EcuM_EndCheckWakeup(VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) sources)
{
#if ECUM_SLEEP_SUPPORT_ENABLE

   VAR(uint8, AUTOMATIC) ctrLoop1_u8 = 0;

   VAR(Type_SwcServiceEcuM_tModeShutdown, AUTOMATIC) dataSleepModeHandle_u16 = 0xFF;

    SchM_Enter_EcuM();

    dataSleepModeHandle_u16 = EcuM_Lok_SleepMode_u16;

    SchM_Exit_EcuM();
   if(EcuM_Lok_hasCheckWakeupSourceGetHandle_b(sources) == FALSE)
   {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        (void) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_END_CHECKWAKEUP_APIID, ECUM_E_UNKNOWN_WAKEUP_SOURCE);
#endif//ECUM_DEV_ERROR_DETECT

   }
   else{

        for(ctrLoop1_u8 = 0; ctrLoop1_u8 < CfgSwcServiceEcuM_dNumSourceWakeup; ctrLoop1_u8++)
        {
            SchM_Enter_EcuM();
            if(((EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].WakeupSourceId & sources) != CfgSwcServiceEcuM_dSourceWakeupNone)
                    && (EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop1_u8].CheckWakeupTimeout != 0)
                    && ((EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].WakeupSourceId
                            & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask) != CfgSwcServiceEcuM_dSourceWakeupNone))
            {
                EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupStatus = ECUM_END_CHECK_WAKEUP_E;
                EcuM_Cfg_CheckWakeupTimer_ast[ctrLoop1_u8].CheckWakeupTimeout = 0;

            }
            SchM_Exit_EcuM();
        }
   }

#endif//ECUM_SLEEP_SUPPORT_ENABLE

(void)sources;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.hpp"

