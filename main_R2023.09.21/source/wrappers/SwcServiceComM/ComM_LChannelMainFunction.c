#include "Std_Types.hpp"

#include "ComM_Priv.hpp"

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_ModeHandling
                                                    (
                                                         P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs
   ,     VAR(ComM_ModeType,AUTOMATIC) channelMode_e
   ,     boolean entryToMode_b
                                                    );

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_NoComNoPending_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     ComM_StateType previousstate_e
                                                    );

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_NoComPending_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     ComM_StateType previousstate_e
                                                    );

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_FullComReadySleep_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs
   ,     ComM_StateType previousstate_e
   ,     uint8 numStateChanges_u8
                                                    );

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_FullComNetworkReq_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs
   ,     ComM_StateType previousstate_e
                                                    );

#if(COMM_NM_SUPPORT != STD_OFF)
LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_SilentCom_StateHandling
                                                    (
                                                            P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs
   ,     ComM_StateType previousstate_e
                                                    );

#endif

LOCAL_INLINE FUNC(ComM_ModeType,AUTOMATIC) ComM_getMode (VAR(ComM_StateType,AUTOMATIC) channelState_e);

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LNotifyChannelMode (VAR(NetworkHandleType,AUTOMATIC) ChannelIndex);

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LCallRteWrite (VAR(uint8, COMM_VAR) ChannelIndex );
#endif

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"
FUNC(void, COMM_CODE) ComM_LChannelMainFunction
                                                (
                                                    VAR(NetworkHandleType,AUTOMATIC) ChannelIndex
                                                )
{

   VAR(ComM_StateType,AUTOMATIC)  channelState_e;
   VAR(ComM_StateType,AUTOMATIC) previousstate_e;
   VAR(ComM_ModeType,AUTOMATIC) channelMode_e;
   VAR(ComM_ModeType,AUTOMATIC) busSmMode_e;
   VAR(ComM_RequestStructType,COMM_VAR) ComM_RequestStruct;

   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;
   P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps;
   uint8 numStateChanges_u8;
   boolean stateChangePossible_b;
   boolean entryToMode_b;
   boolean userRequestState_b;
   boolean diagnosticRequestState_b;
#if(COMM_PNC_ENABLED != STD_OFF)
   boolean pncRequestState_b;
#endif

#if(COMM_INHIBITION_ENABLED)
   P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
#endif

   stateChangePossible_b = FALSE;
    entryToMode_b = FALSE;
    numStateChanges_u8 = C_ZERO;
#if(COMM_PNC_ENABLED != STD_OFF)
    pncRequestState_b = FALSE;
#endif

   channelRamPtr_ps = &ComM_ChannelStruct[ChannelIndex];
   channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[ChannelIndex]);

    requestStructPtr_ps = &ComM_RequestStruct;

#if(COMM_INHIBITION_ENABLED)
    globalRamPtr_ps = &ComM_GlobalStruct;
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
   if(ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_MAINFNC_APIID,COMM_E_NOT_INITED);
        return;
   }
#endif

   userRequestState_b = (((channelRamPtr_ps->UserRequestCtr_u8) > C_ZERO));

#if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)

   if((COMM_GET_PREVENT_WAKEUP(globalRamPtr_ps->ComM_EcuGroupClassification_u8)))
   {
        if((COMM_GET_PREVENT_WAKEUP(channelRamPtr_ps->InhibitionReqStatus_u8)) &&
                ((channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)|| (channelRamPtr_ps->ChannelMode_u8 == COMM_SILENT_COMMUNICATION)))
        {
            userRequestState_b = FALSE;
        }
   }
#endif
#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

   if(COMM_GET_LIMIT_TO_NO_COM((globalRamPtr_ps->ComM_EcuGroupClassification_u8)))
   {
        if(COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8)))
        {
            userRequestState_b = FALSE;
        }
   }
#endif

    diagnosticRequestState_b = channelRamPtr_ps->DiagnosticRequestState_b;

    requestStructPtr_ps->PassiveRequest_b = ((channelRamPtr_ps->PassiveRequestState_u8) > C_ZERO);

    requestStructPtr_ps->ActiveRequest_b = (userRequestState_b || diagnosticRequestState_b);

#if(COMM_PNC_ENABLED != STD_OFF)

   if(COMM_GET_FEATURE_PNC_ENABLED)
   {
        pncRequestState_b = (channelRamPtr_ps->PncRequestCtr_u8 > C_ZERO);

        requestStructPtr_ps->ActiveRequest_b = (requestStructPtr_ps->ActiveRequest_b) || (pncRequestState_b);
   }
#endif

   channelState_e = channelRamPtr_ps->ChannelState_e ;

   channelMode_e = channelRamPtr_ps->ChannelMode_u8 ;

   busSmMode_e = channelRamPtr_ps->BusSmMode_u8;

    previousstate_e = channelState_e;

    do
   {

        ComM_ModeHandling(channelRamPtr_ps,channelConfigPtr_pcs, channelMode_e, entryToMode_b);

        switch(channelState_e)
        {
            case COMM_NO_COM_NO_PENDING_REQUEST:
            {
                channelState_e = ComM_NoComNoPending_StateHandling(requestStructPtr_ps, previousstate_e);
            }
            break;
            case COMM_NO_COM_REQUEST_PENDING:
            {
                channelState_e = ComM_NoComPending_StateHandling(requestStructPtr_ps, channelRamPtr_ps, previousstate_e);
            }
            break;
            case COMM_FULL_COM_NETWORK_REQUESTED:
            {
                channelState_e = ComM_FullComNetworkReq_StateHandling(requestStructPtr_ps, channelRamPtr_ps
   ,     channelConfigPtr_pcs, previousstate_e);
            }
            break;
            case COMM_FULL_COM_READY_SLEEP:
            {
                channelState_e = ComM_FullComReadySleep_StateHandling(requestStructPtr_ps, channelRamPtr_ps
   ,     channelConfigPtr_pcs, previousstate_e, numStateChanges_u8);
            }
            break;
#if(COMM_NM_SUPPORT != STD_OFF)
            case COMM_SILENT_COM:
            {
                channelState_e = ComM_SilentCom_StateHandling(requestStructPtr_ps, channelRamPtr_ps, channelConfigPtr_pcs, previousstate_e);
            }
            break;
#endif
            default:

            break;
        }

        if(channelRamPtr_ps->ChannelState_e != channelState_e)
        {
            SchM_Enter_ComM_ChannelNoNest();

            previousstate_e = channelRamPtr_ps->ChannelState_e;
            channelRamPtr_ps->ChannelState_e = channelState_e;

            stateChangePossible_b = TRUE;
            numStateChanges_u8++;

            channelMode_e = ComM_getMode (channelState_e);

            if(channelMode_e != channelRamPtr_ps->ChannelMode_u8)
            {

                entryToMode_b = TRUE;
                channelRamPtr_ps->ChannelMode_u8 = channelMode_e;
            }
            else{

                entryToMode_b = FALSE;
            }
            SchM_Exit_ComM_ChannelNoNest();
        }
        else{
            entryToMode_b = FALSE;
            stateChangePossible_b = FALSE;
        }

   }while(stateChangePossible_b != FALSE);

   if(busSmMode_e != channelRamPtr_ps->BusSmMode_u8)
   {

        ComM_LNotifyChannelMode(ChannelIndex);

        ComM_LUpdateChannelModes(ChannelIndex,busSmMode_e,channelRamPtr_ps->BusSmMode_u8);

   }

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
   if(channelRamPtr_ps->ComMFullComReqNotify_b==TRUE)
   {
        ComM_LCallRteWrite(ChannelIndex);
        channelRamPtr_ps->ComMFullComReqNotify_b= FALSE;
   }
#endif
}

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_NoComNoPending_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     ComM_StateType previousstate_e
                                                    )
{
   VAR(ComM_StateType,AUTOMATIC) channelState_e;

   channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;

   if(previousstate_e != COMM_NO_COM_NO_PENDING_REQUEST )
   {

   }

   else{
        if((requestStructPtr_ps->ActiveRequest_b != FALSE) || (requestStructPtr_ps->PassiveRequest_b != FALSE))
        {

            channelState_e = COMM_NO_COM_REQUEST_PENDING;
        }
        else{

        }
   }

    return channelState_e;
}

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_NoComPending_StateHandling
                                                        (
                                                            P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     ComM_StateType previousstate_e
                                                        )
{

   VAR(ComM_StateType,AUTOMATIC) channelState_e;

   channelState_e = COMM_NO_COM_REQUEST_PENDING;

   if(previousstate_e != COMM_NO_COM_REQUEST_PENDING )
   {

        if(channelRamPtr_ps->CommunicationAllowed_b != FALSE)
        {

            channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
        }
   }

   else{

        if((requestStructPtr_ps->ActiveRequest_b || requestStructPtr_ps->PassiveRequest_b))
        {
            if((channelRamPtr_ps->CommunicationAllowed_b) != FALSE)
            {

                channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
            }
            else{

            }
        }
        else{
            channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
        }
   }

   if(channelState_e != COMM_NO_COM_REQUEST_PENDING)
   {

        channelRamPtr_ps->PassiveRequestState_u8 = C_ZERO;
   }
    return channelState_e;
}

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_FullComNetworkReq_StateHandling
                                                        (
                                                            P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs
   ,     ComM_StateType previousstate_e
                                                        )
{

   VAR(ComM_StateType,AUTOMATIC) channelState_e;

   channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;

   if(previousstate_e != COMM_FULL_COM_NETWORK_REQUESTED )
   {

        switch(channelConfigPtr_pcs->ComMNmVariant_e)
        {

#if(COMM_NM_SUPPORT != STD_OFF)
#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)

            case (FULL):
            {
                if(requestStructPtr_ps->ActiveRequest_b)
                {

                    (void)Nm_NetworkRequest(channelConfigPtr_pcs->ComMChannelId_u8);
#if(COMM_PNC_ENABLED != STD_OFF)

                    if(COMM_GET_FEATURE_PNC_ENABLED)
                    {

                        channelRamPtr_ps ->NmNetworkRequestStatus_b = FALSE;
                    }
#endif
                }
                else{

                    channelState_e = COMM_FULL_COM_READY_SLEEP;
                }
            }
            break;
            #elif(COMM_NM_VARIANT == COMM_NM_VARIANT_PASSIVE)

            case (PASSIVE):
            {

                channelState_e = COMM_FULL_COM_READY_SLEEP;
            }
            break;
#endif
#endif

            case LIGHT:
            case NONE:
            {

                (channelRamPtr_ps->MinFullComTimeoutCtr_u16) = (channelConfigPtr_pcs->TMinFullComModeDuration_u16) ;
            }
            break;

            default :

            break;

        }
   }

   else{
        switch(channelConfigPtr_pcs->ComMNmVariant_e)
        {

#if((COMM_NM_SUPPORT != STD_OFF) && (COMM_NM_VARIANT == COMM_NM_VARIANT_FULL))
            case (FULL):
            {

                if((channelRamPtr_ps->NmBusSleepIndicationStatus_b) != FALSE)
                {
                    channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if(requestStructPtr_ps->ActiveRequest_b != FALSE)
                {
#if(COMM_PNC_ENABLED != STD_OFF)

                    if(COMM_GET_FEATURE_PNC_ENABLED)
                    {
                        if((channelRamPtr_ps->NmNetworkRequestStatus_b) != FALSE)
                        {
                            (void)Nm_NetworkRequest(channelConfigPtr_pcs->ComMChannelId_u8);

                            channelRamPtr_ps ->NmNetworkRequestStatus_b = FALSE;
                        }
                    }
#endif

                }
                else{

                    channelState_e = COMM_FULL_COM_READY_SLEEP;
                }
            }
            break;
#endif

            case LIGHT:
            case NONE :
            {

                if((channelRamPtr_ps->MinFullComTimeoutCtr_u16) != C_ZERO)
                {

                    -- (channelRamPtr_ps->MinFullComTimeoutCtr_u16) ;
                }

                if((channelRamPtr_ps->MinFullComTimeoutCtr_u16) == C_ZERO)
                {
                    if(requestStructPtr_ps->ActiveRequest_b != FALSE)
                    {

                    }
                    else
                    {

                        channelState_e = COMM_FULL_COM_READY_SLEEP;
                    }
                }
            }
            break;

            default :

            break;
        }
   }

   if(channelState_e == COMM_NO_COM_NO_PENDING_REQUEST)
   {

#if(COMM_NM_SUPPORT != STD_OFF)
        channelRamPtr_ps->NmBusSleepIndicationStatus_b = FALSE ;
#endif
   }

    return channelState_e;
}

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_FullComReadySleep_StateHandling
                                                (
                                                    P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs
   ,     ComM_StateType previousstate_e
   ,     uint8 numStateChanges_u8
                                                )

{
   VAR(ComM_StateType,AUTOMATIC) channelState_e;

   channelState_e = COMM_FULL_COM_READY_SLEEP;

   if(previousstate_e != COMM_FULL_COM_READY_SLEEP )
   {

        if(previousstate_e == COMM_FULL_COM_NETWORK_REQUESTED)
        {
            switch(channelConfigPtr_pcs->ComMNmVariant_e)
            {
#if(COMM_NM_SUPPORT != STD_OFF)

#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
                case FULL :
                {

                    if(numStateChanges_u8 >=2)
                    {

                        (void)Nm_PassiveStartUp(channelConfigPtr_pcs->ComMChannelId_u8);
                    }
                    else
                    {

                        (void)Nm_NetworkRelease(channelConfigPtr_pcs->ComMChannelId_u8);
                    }
                }
                break;
#endif
#if(COMM_NM_VARIANT == COMM_NM_VARIANT_PASSIVE)
                case PASSIVE :
                {

                    (void)Nm_PassiveStartUp(channelConfigPtr_pcs->ComMChannelId_u8);
                }
                break;
#endif
#endif

                case LIGHT:
                {

                    channelRamPtr_ps->LightTimeoutCtr_u32 = channelConfigPtr_pcs->NmLightTimeout_u32;

                    if(channelRamPtr_ps->LightTimeoutCtr_u32 == C_ZERO)
                    {

                        channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                    }
                }
                break;

                case NONE:
                {
                    if(channelConfigPtr_pcs->BusType_e == COMM_BUS_TYPE_INTERNAL)
                    {

                        channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                    }
                    else
                    {

                    }
                }
                break;

                default:

                break;
            }
        }
   }

   else{
        switch(channelConfigPtr_pcs->ComMNmVariant_e)
        {
#if(COMM_NM_SUPPORT != STD_OFF)

#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
            case FULL :
            {
                if(channelRamPtr_ps->NmBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if(requestStructPtr_ps->ActiveRequest_b)
                {

                    channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
                }
                else if(channelRamPtr_ps->NmPrepareBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_e = COMM_SILENT_COM;
                }
                else{

                }
            }
            break;
#endif

#if(COMM_NM_VARIANT == COMM_NM_VARIANT_PASSIVE)
            case PASSIVE :
            {
                if(channelRamPtr_ps->NmBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if(channelRamPtr_ps->NmPrepareBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_e = COMM_SILENT_COM;
                }
                else{

                }
            }
            break;
#endif
#endif

            case LIGHT :
            {
                if(requestStructPtr_ps->ActiveRequest_b != FALSE)
                {
                    channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
                }
                else{
                    if((channelRamPtr_ps->LightTimeoutCtr_u32) != C_ZERO )
                    {
                        --channelRamPtr_ps->LightTimeoutCtr_u32;
                        if((channelRamPtr_ps->LightTimeoutCtr_u32) == C_ZERO )
                        {
                            channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                        }
                        else
                        {

                        }
                    }
                }
            }
            break;

            case NONE :
            {

            }
            break;

            default:

            break;

        }
   }

   if(channelState_e != COMM_FULL_COM_READY_SLEEP)
   {
        SchM_Enter_ComM_ChannelNoNest();

#if(COMM_NM_SUPPORT != STD_OFF)
        channelRamPtr_ps->NmPrepareBusSleepIndicationStatus_b = FALSE ;

        if(channelState_e == COMM_NO_COM_NO_PENDING_REQUEST)
        {

            channelRamPtr_ps->NmBusSleepIndicationStatus_b = FALSE ;
        }

#endif
        SchM_Exit_ComM_ChannelNoNest();
   }

    return channelState_e;
}

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_SilentCom_StateHandling
                                                (
                                                    P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps
   ,     P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs
   ,     ComM_StateType previousstate_e
                                                )
{
   VAR(ComM_StateType,AUTOMATIC) channelState_e;

   channelState_e = COMM_SILENT_COM;

   if(previousstate_e != COMM_SILENT_COM )
   {

   }

   else{

        if((channelRamPtr_ps->NmBusSleepIndicationStatus_b) != FALSE)
        {
            channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
        }

        else if((channelConfigPtr_pcs->ComMNmVariant_e == FULL) && (requestStructPtr_ps->ActiveRequest_b != FALSE))
        {
            channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
        }
        else if((channelRamPtr_ps->NmNetworkModeStatus_b) != FALSE)
        {
            channelState_e = COMM_FULL_COM_READY_SLEEP;
        }
        else{

        }
   }

   if(channelState_e != COMM_SILENT_COM)
   {
        SchM_Enter_ComM_ChannelNoNest();
        channelRamPtr_ps->NmNetworkModeStatus_b = FALSE;
        channelRamPtr_ps->NmBusSleepIndicationStatus_b = FALSE;
        SchM_Exit_ComM_ChannelNoNest();
   }

    return channelState_e;
}

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_ModeHandling
                                            (
                                                 P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
   ,     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs
   ,     VAR(ComM_ModeType,AUTOMATIC) channelMode_e 
   ,     boolean entryToMode_b
                                            )
{
   boolean requestBusSm_b;
   VAR(ComM_ModeType,AUTOMATIC) busSmMode_e;
   P2CONST(ComM_BusSmApiType,AUTOMATIC,COMM_APPL_CONST) busSm_funcPtr;

   busSmMode_e = channelRamPtr_ps->BusSmMode_u8;
   busSm_funcPtr = &ComM_BusSmApi[channelConfigPtr_pcs->BusType_e];
    requestBusSm_b = FALSE;

   if(entryToMode_b != FALSE)
   {
        requestBusSm_b = TRUE;

        if(channelMode_e == COMM_NO_COMMUNICATION)
        {
#if(COMM_NM_SUPPORT != STD_OFF)
#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
            if(channelConfigPtr_pcs->ComMNmVariant_e == FULL)
            {
                (void)Nm_NetworkRelease(channelConfigPtr_pcs->ComMChannelId_u8);
            }
#endif
#endif
        }
   }

   else{

        (void)(*busSm_funcPtr->BusSm_GetCurrentComMode)(channelConfigPtr_pcs->ComMChannelId_u8, &busSmMode_e);

        channelRamPtr_ps->BusSmMode_u8 = busSmMode_e ;

        if(busSmMode_e != channelMode_e)
        {
            requestBusSm_b = TRUE;
        }

        if(channelMode_e == COMM_NO_COMMUNICATION)
        {

#if((COMM_RESET_AFTER_NO_COM != STD_OFF) && (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF))
            if((COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8)) != FALSE) &&
               (channelRamPtr_ps->BusSmMode_u8 == channelMode_e))
            {
                BswM_ComM_InitiateReset();
            }
#endif
        }
   }

   if(requestBusSm_b)
   {
        Std_ReturnType RetValue;

        RetValue = (*busSm_funcPtr->BusSm_RequestComMode)(channelConfigPtr_pcs->ComMChannelId_u8,channelMode_e);

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
        if(RetValue == E_NOT_OK)
        {
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_MAINFNC_APIID,COMM_E_ERROR_IN_PROV_SERVICE);
        }
#else
        (void)(RetValue);
#endif
   }
}

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LNotifyChannelMode(VAR(NetworkHandleType,AUTOMATIC) ChannelIndex)
{

   P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
   VAR(ComM_ModeType,AUTOMATIC) channelMode_e;

   channelRamPtr_ps = &ComM_ChannelStruct[ChannelIndex];

   channelMode_e = channelRamPtr_ps->ChannelMode_u8;

    BswM_ComM_CurrentMode(ChannelIndex,channelMode_e);

#if(COMM_DCM_SUPPORT != STD_OFF)

   switch(channelMode_e)
   {
        case COMM_NO_COMMUNICATION : Dcm_ComM_NoComModeEntered(ChannelIndex);
            break;
        case COMM_FULL_COMMUNICATION : Dcm_ComM_FullComModeEntered(ChannelIndex);
            break;
        case COMM_SILENT_COMMUNICATION : Dcm_ComM_SilentComModeEntered(ChannelIndex);
            break;
        default:

            break;
   }

#endif
}

LOCAL_INLINE FUNC(ComM_ModeType,AUTOMATIC) ComM_getMode (VAR(ComM_StateType,AUTOMATIC) channelState_e)
{
   VAR(ComM_ModeType,AUTOMATIC) channelMode_e;
   channelMode_e = COMM_NO_COMMUNICATION;

   switch(channelState_e)
   {
        case COMM_NO_COM_NO_PENDING_REQUEST :
        case COMM_NO_COM_REQUEST_PENDING :
        {
            channelMode_e = COMM_NO_COMMUNICATION;
        }
        break;

        case COMM_FULL_COM_NETWORK_REQUESTED :
        case COMM_FULL_COM_READY_SLEEP :
        {
            channelMode_e = COMM_FULL_COMMUNICATION;
        }
        break;

        case COMM_SILENT_COM :
        {
            channelMode_e = COMM_SILENT_COMMUNICATION;
        }
        break;

        default:
        {
#if(COMM_DEV_ERROR_DETECT != STD_OFF)
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_MAINFNC_APIID,COMM_E_WRONG_PARAMETERS);
#endif
        }
        break;
   }

    return channelMode_e;
}

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LCallRteWrite
                        (
                         VAR(uint8, COMM_VAR) ChannelIndex
                         )
{
   P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;
   channelConfigPtr_pcs= &(COMM_GET_CHANNEL_LIST[ChannelIndex]);
   if(channelConfigPtr_pcs->ComMFullCommRequestNotificationEnabled == TRUE)
   {
      ComM_CurrentChannelRequest_Rte_Write(ChannelIndex,&ComM_FullComRequestors[ChannelIndex]);
   }
   else{
   }
}
#endif
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

