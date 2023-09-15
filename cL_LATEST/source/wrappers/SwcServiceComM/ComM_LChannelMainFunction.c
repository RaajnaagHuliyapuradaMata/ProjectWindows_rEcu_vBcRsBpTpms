

#include "ComM_Priv.hpp"

LOCAL_INLINE void ComM_Lok_ModeHandling(ComM_ChannelVarType_tst *     channelRamPtr_pst
   ,                                       const ComM_ChannelType_tst *  channelConfigPtr_pcst
   ,                                       ComM_ModeType                 channelMode_tu8
   ,                                       boolean                       entryToMode_b);

LOCAL_INLINE ComM_StateType ComM_Lok_NoComNoPending_StateHandling(ComM_RequestStructType_tst *  requestStructPtr_pst
   ,                                                                 ComM_StateType                previousstate_en);

LOCAL_INLINE ComM_StateType ComM_Lok_NoComPending_StateHandling(ComM_RequestStructType_tst * requestStructPtr_pst
   ,                                                               ComM_ChannelVarType_tst *    channelRamPtr_pst
   ,                                                               ComM_StateType               previousstate_en);

LOCAL_INLINE ComM_StateType ComM_Lok_FullComReadySleep_StateHandling(ComM_RequestStructType_tst * requestStructPtr_pst
   ,                                                                    ComM_ChannelVarType_tst *    channelRamPtr_pst
   ,                                                                    const ComM_ChannelType_tst * channelConfigPtr_pcst
   ,                                                                    ComM_StateType               previousstate_en
   ,                                                                    uint8                        numStateChanges_u8);

LOCAL_INLINE ComM_StateType ComM_Lok_FullComNetworkReq_StateHandling(ComM_RequestStructType_tst * requestStructPtr_pst
   ,                                                                    ComM_ChannelVarType_tst *    channelRamPtr_pst
   ,                                                                    const ComM_ChannelType_tst * channelConfigPtr_pcst
   ,                                                                    ComM_StateType               previousstate_en);

#if(COMM_NM_SUPPORT != STD_OFF)
LOCAL_INLINE ComM_StateType ComM_Lok_SilentCom_StateHandling(ComM_RequestStructType_tst *   requestStructPtr_pst
   ,                                                            ComM_ChannelVarType_tst *      channelRamPtr_pst
   ,                                                            const ComM_ChannelType_tst *   channelConfigPtr_pcst
   ,                                                            ComM_StateType                 previousstate_en);

#endif

LOCAL_INLINE ComM_ModeType ComM_Lok_getMode (ComM_StateType channelState_e);

LOCAL_INLINE void ComM_Lok_NotifyChannelMode (NetworkHandleType ChannelIndex_tu8);

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
LOCAL_INLINE void ComM_Lok_CallRteWrite (uint8 ChannelIndex_u8 );
#endif

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

void ComM_Lok_ChannelMainFunction(NetworkHandleType ChannelIndex_tu8)
{

   ComM_StateType              channelState_en;
   ComM_StateType              previousstate_en;
   ComM_ModeType               channelMode_tu8;
   ComM_ModeType               busSmMode_tu8;
   ComM_RequestStructType_tst  ComM_RequestStruct_st;

   ComM_ChannelVarType_tst *       channelRamPtr_pst;
   const ComM_ChannelType_tst *    channelConfigPtr_pcst;
   ComM_RequestStructType_tst *    requestStructPtr_pst;
   uint8                           numStateChanges_u8;
   boolean                         stateChangePossible_b;
   boolean                         entryToMode_b;
   boolean                         userRequestState_b;
   boolean                         diagnosticRequestState_b;
#if(COMM_PNC_ENABLED != STD_OFF)
   boolean                     pncRequestState_b;
#endif

#if(COMM_INHIBITION_ENABLED)
   ComM_GlobalVarType_tst *        globalRamPtr_pst;
#endif

   stateChangePossible_b = FALSE;
    entryToMode_b = FALSE;
    numStateChanges_u8 = C_ZERO;
#if(COMM_PNC_ENABLED != STD_OFF)
    pncRequestState_b = FALSE;
#endif

   channelRamPtr_pst = &ComM_ChannelStruct[ChannelIndex_tu8];
   channelConfigPtr_pcst = &(COMM_GET_CHANNEL_LIST[ChannelIndex_tu8]);

    requestStructPtr_pst = &ComM_RequestStruct_st;

#if(COMM_INHIBITION_ENABLED)
    globalRamPtr_pst = &ComM_GlobalStruct;
#endif

#if(COMM_DEV_ERROR_DETECT != STD_OFF)
   if(ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
   {

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_MAINFNC_APIID,COMM_E_NOT_INITED);
        return;
   }
#endif

#if CPU_TYPE == CPU_TYPE_8

    SchM_Enter_ComM_UserNoNest();
#endif

   userRequestState_b = (((channelRamPtr_pst->UserRequestCtr_u16) > C_ZERO_U16));
#if CPU_TYPE == CPU_TYPE_8
    SchM_Exit_ComM_UserNoNest();
#endif

#if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)

   if((COMM_GET_PREVENT_WAKEUP(globalRamPtr_pst->ComM_EcuGroupClassification_u8)))
   {
        if((COMM_GET_PREVENT_WAKEUP(channelRamPtr_pst->InhibitionReqStatus_u8)) &&
                ((channelRamPtr_pst->ChannelMode_u8 == COMM_NO_COMMUNICATION)|| (channelRamPtr_pst->ChannelMode_u8 == COMM_SILENT_COMMUNICATION)))
        {
            userRequestState_b = FALSE;
        }
   }
#endif
#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

   if(COMM_GET_LIMIT_TO_NO_COM((globalRamPtr_pst->ComM_EcuGroupClassification_u8)))
   {
        if(COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_pst->InhibitionReqStatus_u8)))
        {
            userRequestState_b = FALSE;
        }
   }
#endif

    diagnosticRequestState_b = channelRamPtr_pst->DiagnosticRequestState_b;

    requestStructPtr_pst->PassiveRequest_b = ((channelRamPtr_pst->PassiveRequestState_u8) > C_ZERO);

    requestStructPtr_pst->ActiveRequest_b = (userRequestState_b || diagnosticRequestState_b);

#if(COMM_PNC_ENABLED != STD_OFF)

   if(COMM_GET_FEATURE_PNC_ENABLED)
   {
        pncRequestState_b = (channelRamPtr_pst->PncRequestCtr_u8 > C_ZERO);

        requestStructPtr_pst->ActiveRequest_b = (requestStructPtr_pst->ActiveRequest_b) || (pncRequestState_b);
   }
#endif

   channelState_en = channelRamPtr_pst->ChannelState_e ;

   channelMode_tu8 = channelRamPtr_pst->ChannelMode_u8 ;

   busSmMode_tu8 = channelRamPtr_pst->BusSmMode_u8;

    previousstate_en = channelState_en;

    do
   {

        ComM_Lok_ModeHandling(channelRamPtr_pst,channelConfigPtr_pcst, channelMode_tu8, entryToMode_b);

        switch(channelState_en)
        {
            case COMM_NO_COM_NO_PENDING_REQUEST:
            {
                channelState_en = ComM_Lok_NoComNoPending_StateHandling(requestStructPtr_pst, previousstate_en);
            }
            break;
            case COMM_NO_COM_REQUEST_PENDING:
            {
                channelState_en = ComM_Lok_NoComPending_StateHandling(requestStructPtr_pst, channelRamPtr_pst, previousstate_en);
            }
            break;
            case COMM_FULL_COM_NETWORK_REQUESTED:
            {
                channelState_en = ComM_Lok_FullComNetworkReq_StateHandling(requestStructPtr_pst, channelRamPtr_pst
   ,                                                                                channelConfigPtr_pcst, previousstate_en);
            }
            break;
            case COMM_FULL_COM_READY_SLEEP:
            {
                channelState_en = ComM_Lok_FullComReadySleep_StateHandling(requestStructPtr_pst, channelRamPtr_pst
   ,                                       channelConfigPtr_pcst, previousstate_en, numStateChanges_u8);
            }
            break;
#if(COMM_NM_SUPPORT != STD_OFF)
            case COMM_SILENT_COM:
            {
                channelState_en = ComM_Lok_SilentCom_StateHandling(requestStructPtr_pst, channelRamPtr_pst, channelConfigPtr_pcst, previousstate_en);
            }
            break;
#endif
            default:

            break;
        }

        if(channelRamPtr_pst->ChannelState_e != channelState_en)
        {
            SchM_Enter_ComM_ChannelNoNest();

            previousstate_en = channelRamPtr_pst->ChannelState_e;
            channelRamPtr_pst->ChannelState_e = channelState_en;

            stateChangePossible_b = TRUE;
            numStateChanges_u8++;

            channelMode_tu8 = ComM_Lok_getMode (channelState_en);

            if(channelMode_tu8 != channelRamPtr_pst->ChannelMode_u8)
            {

                entryToMode_b = TRUE;
                channelRamPtr_pst->ChannelMode_u8 = channelMode_tu8;
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

   if(busSmMode_tu8 != channelRamPtr_pst->BusSmMode_u8)
   {

        ComM_Lok_NotifyChannelMode(ChannelIndex_tu8);

        ComM_Lok_UpdateChannelModes(ChannelIndex_tu8,busSmMode_tu8,channelRamPtr_pst->BusSmMode_u8);

   }

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
   if(channelRamPtr_pst->ComMFullComReqNotify_b==TRUE)
   {
        ComM_Lok_CallRteWrite(ChannelIndex_tu8);
        channelRamPtr_pst->ComMFullComReqNotify_b= FALSE;
   }
#endif
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

LOCAL_INLINE ComM_StateType ComM_Lok_NoComNoPending_StateHandling(ComM_RequestStructType_tst *  requestStructPtr_pst
   ,                                                                 ComM_StateType                previousstate_en)
{
   ComM_StateType channelState_en;

   channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;

   if(previousstate_en != COMM_NO_COM_NO_PENDING_REQUEST )
   {

   }

   else{
        if((requestStructPtr_pst->ActiveRequest_b != FALSE) || (requestStructPtr_pst->PassiveRequest_b != FALSE))
        {

            channelState_en = COMM_NO_COM_REQUEST_PENDING;
        }
        else{

        }
   }

    return channelState_en;
}

LOCAL_INLINE ComM_StateType ComM_Lok_NoComPending_StateHandling(ComM_RequestStructType_tst * requestStructPtr_pst
   ,                                                               ComM_ChannelVarType_tst *    channelRamPtr_pst
   ,                                                               ComM_StateType               previousstate_en)
{

   ComM_StateType channelState_en;

   channelState_en = COMM_NO_COM_REQUEST_PENDING;

   if(previousstate_en != COMM_NO_COM_REQUEST_PENDING )
   {

        if(channelRamPtr_pst->CommunicationAllowed_b != FALSE)
        {

            channelState_en = COMM_FULL_COM_NETWORK_REQUESTED;
        }
   }

   else{

        if((requestStructPtr_pst->ActiveRequest_b || requestStructPtr_pst->PassiveRequest_b))
        {
            if((channelRamPtr_pst->CommunicationAllowed_b) != FALSE)
            {

                channelState_en = COMM_FULL_COM_NETWORK_REQUESTED;
            }
            else{

            }
        }
        else{
            channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;
        }
   }

   if(channelState_en != COMM_NO_COM_REQUEST_PENDING)
   {

        channelRamPtr_pst->PassiveRequestState_u8 = C_ZERO;
   }
    return channelState_en;
}

LOCAL_INLINE ComM_StateType ComM_Lok_FullComNetworkReq_StateHandling(ComM_RequestStructType_tst * requestStructPtr_pst
   ,                                                                    ComM_ChannelVarType_tst *    channelRamPtr_pst
   ,                                                                    const ComM_ChannelType_tst * channelConfigPtr_pcst
   ,                                                                    ComM_StateType               previousstate_en)
{

   ComM_StateType channelState_en;

   channelState_en = COMM_FULL_COM_NETWORK_REQUESTED;

   if(previousstate_en != COMM_FULL_COM_NETWORK_REQUESTED )
   {

        switch(channelConfigPtr_pcst->ComMNmVariant_en)
        {

#if(COMM_NM_SUPPORT != STD_OFF)
#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)

            case (FULL):
            {
                if(requestStructPtr_pst->ActiveRequest_b)
                {

                    (void)Nm_NetworkRequest(channelConfigPtr_pcst->ComMChannelId_u8);
#if(COMM_PNC_ENABLED != STD_OFF)

                    if(COMM_GET_FEATURE_PNC_ENABLED)
                    {

                        channelRamPtr_pst ->NmNetworkRequestStatus_b = FALSE;
                    }
#endif
                }
                else{

                    channelState_en = COMM_FULL_COM_READY_SLEEP;
                }
            }
            break;
#endif

            case (PASSIVE):
            {

                channelState_en = COMM_FULL_COM_READY_SLEEP;
            }
            break;
#endif

            case LIGHT:
            case NONE:
            {

                (channelRamPtr_pst->MinFullComTimeoutCtr_u16) = (channelConfigPtr_pcst->TMinFullComModeDuration_u16) ;
            }
            break;

            default :

            break;

        }
   }

   else{
        switch(channelConfigPtr_pcst->ComMNmVariant_en)
        {

#if((COMM_NM_SUPPORT != STD_OFF) && (COMM_NM_VARIANT == COMM_NM_VARIANT_FULL))
            case (FULL):
            {

                if((channelRamPtr_pst->NmBusSleepIndicationStatus_b) != FALSE)
                {
                    channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if(requestStructPtr_pst->ActiveRequest_b != FALSE)
                {
#if(COMM_PNC_ENABLED != STD_OFF)

                    if(COMM_GET_FEATURE_PNC_ENABLED)
                    {
                        if((channelRamPtr_pst->NmNetworkRequestStatus_b) != FALSE)
                        {
                            (void)Nm_NetworkRequest(channelConfigPtr_pcst->ComMChannelId_u8);

                            channelRamPtr_pst ->NmNetworkRequestStatus_b = FALSE;
                        }
                    }
#endif

                }
                else{

                    channelState_en = COMM_FULL_COM_READY_SLEEP;
                }
            }
            break;
#endif

            case LIGHT:
            case NONE :
            {

                if((channelRamPtr_pst->MinFullComTimeoutCtr_u16) != C_ZERO)
                {

                    -- (channelRamPtr_pst->MinFullComTimeoutCtr_u16) ;
                }

                if((channelRamPtr_pst->MinFullComTimeoutCtr_u16) == C_ZERO)
                {
                    if(requestStructPtr_pst->ActiveRequest_b != FALSE)
                    {

                    }
                    else
                    {

                        channelState_en = COMM_FULL_COM_READY_SLEEP;
                    }
                }
            }
            break;

            default :

            break;
        }
   }

   if(channelState_en == COMM_NO_COM_NO_PENDING_REQUEST)
   {

#if(COMM_NM_SUPPORT != STD_OFF)
        channelRamPtr_pst->NmBusSleepIndicationStatus_b = FALSE ;
#endif
   }

    return channelState_en;
}

LOCAL_INLINE ComM_StateType ComM_Lok_FullComReadySleep_StateHandling(ComM_RequestStructType_tst * requestStructPtr_pst
   ,                                                                    ComM_ChannelVarType_tst *    channelRamPtr_pst
   ,                                                                    const ComM_ChannelType_tst * channelConfigPtr_pcst
   ,                                                                    ComM_StateType               previousstate_en
   ,                                                                    uint8                        numStateChanges_u8)

{
   ComM_StateType channelState_en;

   channelState_en = COMM_FULL_COM_READY_SLEEP;

   if(previousstate_en != COMM_FULL_COM_READY_SLEEP )
   {

        if(previousstate_en == COMM_FULL_COM_NETWORK_REQUESTED)
        {
            switch(channelConfigPtr_pcst->ComMNmVariant_en)
            {
#if(COMM_NM_SUPPORT != STD_OFF)

#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
                case FULL :
                {

                    if(numStateChanges_u8 >=2)
                    {

                        (void)Nm_PassiveStartUp(channelConfigPtr_pcst->ComMChannelId_u8);
                    }
                    else
                    {

                        (void)Nm_NetworkRelease(channelConfigPtr_pcst->ComMChannelId_u8);
                    }
                }
                break;
#endif
                case PASSIVE :
                {

                    (void)Nm_PassiveStartUp(channelConfigPtr_pcst->ComMChannelId_u8);
                }
                break;
#endif

                case LIGHT:
                {

                    channelRamPtr_pst->LightTimeoutCtr_u32 = channelConfigPtr_pcst->NmLightTimeout_u32;

                    if(channelRamPtr_pst->LightTimeoutCtr_u32 == C_ZERO)
                    {

                        channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;
                    }
                }
                break;

                case NONE:
                {
                    if(channelConfigPtr_pcst->BusType_en == COMM_BUS_TYPE_INTERNAL)
                    {

                        channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;
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
        switch(channelConfigPtr_pcst->ComMNmVariant_en)
        {
#if(COMM_NM_SUPPORT != STD_OFF)

#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
            case FULL :
            {
                if(channelRamPtr_pst->NmBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if(requestStructPtr_pst->ActiveRequest_b)
                {

                    channelState_en = COMM_FULL_COM_NETWORK_REQUESTED;
                }
                else if(channelRamPtr_pst->NmPrepareBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_en = COMM_SILENT_COM;
                }
                else{

                }
            }
            break;
#endif

            case PASSIVE :
            {
                if(channelRamPtr_pst->NmBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if(channelRamPtr_pst->NmPrepareBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_en = COMM_SILENT_COM;
                }
                else{

                }
            }
            break;
#endif

            case LIGHT :
            {
                if(requestStructPtr_pst->ActiveRequest_b != FALSE)
                {
                    channelState_en = COMM_FULL_COM_NETWORK_REQUESTED;
                }
                else{
                    if((channelRamPtr_pst->LightTimeoutCtr_u32) != C_ZERO )
                    {
                        --channelRamPtr_pst->LightTimeoutCtr_u32;
                        if((channelRamPtr_pst->LightTimeoutCtr_u32) == C_ZERO )
                        {
                            channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;
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

   if(channelState_en != COMM_FULL_COM_READY_SLEEP)
   {
        SchM_Enter_ComM_ChannelNoNest();

#if(COMM_NM_SUPPORT != STD_OFF)
        channelRamPtr_pst->NmPrepareBusSleepIndicationStatus_b = FALSE ;

        if(channelState_en == COMM_NO_COM_NO_PENDING_REQUEST)
        {

            channelRamPtr_pst->NmBusSleepIndicationStatus_b = FALSE ;
        }

#endif
        SchM_Exit_ComM_ChannelNoNest();
   }

    return channelState_en;
}

LOCAL_INLINE ComM_StateType ComM_Lok_SilentCom_StateHandling(ComM_RequestStructType_tst *   requestStructPtr_pst
   ,                                                            ComM_ChannelVarType_tst *      channelRamPtr_pst
   ,                                                            const ComM_ChannelType_tst *   channelConfigPtr_pcst
   ,                                                            ComM_StateType                 previousstate_en)
{
   ComM_StateType channelState_en;

   channelState_en = COMM_SILENT_COM;

   if(previousstate_en != COMM_SILENT_COM )
   {

   }

   else{

        if((channelRamPtr_pst->NmBusSleepIndicationStatus_b) != FALSE)
        {
            channelState_en = COMM_NO_COM_NO_PENDING_REQUEST;
        }

        else if((channelConfigPtr_pcst->ComMNmVariant_en == FULL) && (requestStructPtr_pst->ActiveRequest_b != FALSE))
        {
            channelState_en = COMM_FULL_COM_NETWORK_REQUESTED;
        }
        else if((channelRamPtr_pst->NmNetworkModeStatus_b) != FALSE)
        {
            channelState_en = COMM_FULL_COM_READY_SLEEP;
        }
        else{

        }
   }

   if(channelState_en != COMM_SILENT_COM)
   {
        SchM_Enter_ComM_ChannelNoNest();
        channelRamPtr_pst->NmNetworkModeStatus_b = FALSE;
        channelRamPtr_pst->NmBusSleepIndicationStatus_b = FALSE;
        SchM_Exit_ComM_ChannelNoNest();
   }

    return channelState_en;
}

LOCAL_INLINE void ComM_Lok_ModeHandling(ComM_ChannelVarType_tst *    channelRamPtr_pst
   ,                                       const ComM_ChannelType_tst * channelConfigPtr_pcst
   ,                                       ComM_ModeType                channelMode_tu8 
   ,                                       boolean                      entryToMode_b)
{
   boolean                         requestBusSm_b;
   ComM_ModeType                   busSmMode_tu8;
   const ComM_BusSmApiType_tst *   busSm_funcPtr;

   busSmMode_tu8 = channelRamPtr_pst->BusSmMode_u8;
   busSm_funcPtr = &ComM_BusSmApi_acst[channelConfigPtr_pcst->BusType_en];
    requestBusSm_b = FALSE;

   if(entryToMode_b != FALSE)
   {
        requestBusSm_b = TRUE;

        if(channelMode_tu8 == COMM_NO_COMMUNICATION)
        {
#if(COMM_NM_SUPPORT != STD_OFF)
#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
            if(channelConfigPtr_pcst->ComMNmVariant_en == FULL)
            {
                (void)Nm_NetworkRelease(channelConfigPtr_pcst->ComMChannelId_u8);
            }
#endif
#endif
        }
   }

   else{

        (void)(*busSm_funcPtr->BusSm_GetCurrentComMode)(channelConfigPtr_pcst->ComMChannelId_u8, &busSmMode_tu8);

        channelRamPtr_pst->BusSmMode_u8 = busSmMode_tu8 ;

        if(busSmMode_tu8 != channelMode_tu8)
        {
            requestBusSm_b = TRUE;
        }

        if(channelMode_tu8 == COMM_NO_COMMUNICATION)
        {

#if((COMM_RESET_AFTER_NO_COM != STD_OFF) && (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF))
            if((COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_pst->InhibitionReqStatus_u8)) != FALSE) &&
               (channelRamPtr_pst->BusSmMode_u8 == channelMode_tu8))
            {
                BswM_ComM_InitiateReset();
            }
#endif
        }
   }

   if(requestBusSm_b)
   {
        Std_ReturnType RetValue;

        RetValue = (*busSm_funcPtr->BusSm_RequestComMode)(channelConfigPtr_pcst->ComMChannelId_u8,channelMode_tu8);

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

LOCAL_INLINE void ComM_Lok_NotifyChannelMode(NetworkHandleType ChannelIndex_tu8)
{

   ComM_ChannelVarType_tst *   channelRamPtr_pst;
   ComM_ModeType               channelMode_tu8;

   channelRamPtr_pst = &ComM_ChannelStruct[ChannelIndex_tu8];

   channelMode_tu8 = channelRamPtr_pst->BusSmMode_u8;

    BswM_ComM_CurrentMode(ChannelIndex_tu8,channelMode_tu8);

#if(COMM_DCM_SUPPORT != STD_OFF)

   switch(channelMode_tu8)
   {
        case COMM_NO_COMMUNICATION : Dcm_ComM_NoComModeEntered(ChannelIndex_tu8);
            break;
        case COMM_FULL_COMMUNICATION : Dcm_ComM_FullComModeEntered(ChannelIndex_tu8);
            break;
        case COMM_SILENT_COMMUNICATION : Dcm_ComM_SilentComModeEntered(ChannelIndex_tu8);
            break;
        default:

            break;
   }

#endif
}

LOCAL_INLINE ComM_ModeType ComM_Lok_getMode (ComM_StateType channelState_e)
{
   ComM_ModeType channelMode_tu8;
   channelMode_tu8 = COMM_NO_COMMUNICATION;

   switch(channelState_e)
   {
        case COMM_NO_COM_NO_PENDING_REQUEST :
        case COMM_NO_COM_REQUEST_PENDING :
        {
            channelMode_tu8 = COMM_NO_COMMUNICATION;
        }
        break;

        case COMM_FULL_COM_NETWORK_REQUESTED :
        case COMM_FULL_COM_READY_SLEEP :
        {
            channelMode_tu8 = COMM_FULL_COMMUNICATION;
        }
        break;

        case COMM_SILENT_COM :
        {
            channelMode_tu8 = COMM_SILENT_COMMUNICATION;
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

    return channelMode_tu8;
}

#if((COMM_FULLCOMREQ_NOTIF != STD_OFF)&&(COMM_RTE_SUPPORT != STD_OFF))
LOCAL_INLINE void ComM_Lok_CallRteWrite(uint8 ChannelIndex_u8)
{
   const ComM_ChannelType_tst * channelConfigPtr_pcs;
   channelConfigPtr_pcs= &(COMM_GET_CHANNEL_LIST[ChannelIndex_u8]);
   if(channelConfigPtr_pcs->ComMFullCommRequestNotificationEnabled_b == TRUE)
   {
      ComM_CurrentChannelRequest_Rte_Write(ChannelIndex_u8,&ComM_FullComRequestors[ChannelIndex_u8]);
   }
   else{
   }
}
#endif

