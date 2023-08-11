

#ifndef DCM_DSD_PRV_H

#define DCM_DSD_PRV_H

#include "DcmCore_DslDsd_Inf.h"
#include "DcmCore_DslDsd_Pub.h"
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Roe_Inf.h"
#endif

#define DCM_MANUFACTURERNOTIFICATION        TRUE
#define DCM_SUPPLIERNOTIFICATION            FALSE
#define DCM_RESPONSEONEVENT_SID             0x86u
#define DCM_SECURITYACCESS_SID              0x27u
#define DCM_SERVICE_ISO_LOWERLIMIT          0x40u
#define DCM_SERVICE_ISO_MIDLIMIT            0x7Fu
#define DCM_SERVICE_ISO_UPPERLIMIT          0xC0u
#define DCM_RESPONSEBUFFER_INDEX            0x03u
#define DCM_REQUESTBUFFER_INDEX             0x00u
#define DCM_SID_LENGTH                      0x01u
#define DCM_SUPPRESPOSITIVERESP_MASK        0x80u
#define DCM_REMOVESUPPRESSRESPONSEBIT_MASK  0x7Fu

#define DCM_REMOVEEVENTSTORAGEBIT_MASK      0xBFu
#define DCM_DEFAULT_VALUE                   0x00u

#define DCM_DEFAULT_MASKVALUE               0x00000001uL
#define DCM_UINT16_MAXVALUE                 0xFFFFu

LOCAL_INLINE boolean Dcm_Lok_IsSubFunctionSupported(void)
{

    const Dcm_Dsld_ServiceType* adrActiveService_pcst = &(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]);

    return(adrActiveService_pcst->subfunction_exist_b);
}

LOCAL_INLINE void Dcm_Lok_CheckSuppressPositiveResponse(uint8* subfunction)
{

    if(((*Dcm_DsldMsgContext_st.reqData) & (DCM_SUPPRESPOSITIVERESP_MASK)) == DCM_SUPPRESPOSITIVERESP_MASK)
    {
        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;

        (*Dcm_DsldMsgContext_st.reqData) = ((*Dcm_DsldMsgContext_st.reqData) & DCM_REMOVESUPPRESSRESPONSEBIT_MASK);
    }
    else
    {
        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;
    }

    (*subfunction) = (Dcm_DsldGlobal_st.dataSid_u8 != DCM_RESPONSEONEVENT_SID)? (*Dcm_DsldMsgContext_st.reqData)
                                          :((*Dcm_DsldMsgContext_st.reqData) & DCM_REMOVEEVENTSTORAGEBIT_MASK);
}

LOCAL_INLINE boolean Dcm_Lok_DsdObtainSidIndex(uint8* idxIndex_qu8, const uint8 dataSid_cu8)
{
    boolean IsSidAvailable_b = FALSE;

    uint8 nrServices_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].num_services_u8;
    *idxIndex_qu8 = DCM_DEFAULT_VALUE;

    while(*idxIndex_qu8 < nrServices_u8)
    {
        if(Dcm_DsldSrvTable_pcst[*idxIndex_qu8].sid_u8 == dataSid_cu8)
        {
            IsSidAvailable_b = TRUE;
            break;
        }
        (*idxIndex_qu8)++;
    }
    return(IsSidAvailable_b);
}

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
LOCAL_INLINE boolean Dcm_Lok_ObtainSidIndexOfOBD(uint8* idxIndex_qu8, const uint8 dataSid_cu8)
{
    boolean IsSidAvailable_b = FALSE;
    uint8 nrServices_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_OBDGlobal_st.datActiveSrvtable_u8].num_services_u8;
    *idxIndex_qu8 = DCM_DEFAULT_VALUE;

    while(*idxIndex_qu8 < nrServices_u8)
    {
        if(Dcm_OBDSrvTable_pcst[*idxIndex_qu8].sid_u8 == dataSid_cu8)
        {
            IsSidAvailable_b = TRUE;
            break;
        }
        (*idxIndex_qu8)++;
    }
    return(IsSidAvailable_b);
}
#endif

LOCAL_INLINE void Dcm_Lok_DsdSendNegativeResponse(Dcm_NegativeResponseCodeType ErrorCode)
{

    ErrorCode = (ErrorCode == DCM_DEFAULT_VALUE)?DCM_E_CONDITIONSNOTCORRECT:ErrorCode;

    Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
    Dcm_SetNegResponse(&Dcm_DsldMsgContext_st,ErrorCode);
    Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
}

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
LOCAL_INLINE void Dcm_Lok_OBDDsdSendNegativeResponse(Dcm_NegativeResponseCodeType ErrorCode)
{

    ErrorCode = (ErrorCode == DCM_DEFAULT_VALUE)?DCM_E_CONDITIONSNOTCORRECT:ErrorCode;

    Dcm_OBDGlobal_st.dataResponseByDsd_b = TRUE;
    Dcm_Lok_SetOBDNegResponse(&Dcm_OBDMsgContext_st,ErrorCode);
    Dcm_OBDProcessingDone(&Dcm_OBDMsgContext_st);
}
#endif

LOCAL_INLINE void Dcm_Lok_ProcessServiceNotSupported(void)
{
    Dcm_NegativeResponseCodeType ErrorCode_u8 = DCM_E_SERVICENOTSUPPORTED;

#if(DCM_CFG_RESPOND_ALLREQUEST == DCM_CFG_OFF)
    uint8 SID_u8 = Dcm_DsldGlobal_st.dataSid_u8;

    if((SID_u8 < DCM_SERVICE_ISO_LOWERLIMIT) ||
       ((SID_u8 > DCM_SERVICE_ISO_MIDLIMIT)  && (SID_u8 < DCM_SERVICE_ISO_UPPERLIMIT)))
    {
        Dcm_Lok_DsdSendNegativeResponse(ErrorCode_u8);
    }
    else
    {

        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;
        Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
        Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
    }
#else

    Dcm_Lok_DsdSendNegativeResponse(ErrorCode_u8);
#endif
}

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
LOCAL_INLINE void Dcm_Lok_ProcessOBDServiceNotSupported(void)
{
    Dcm_NegativeResponseCodeType ErrorCode_u8 = DCM_E_SERVICENOTSUPPORTED;

#if(DCM_CFG_RESPOND_ALLREQUEST == DCM_CFG_OFF)
    uint8 SID_u8 = Dcm_OBDGlobal_st.dataSid_u8;

    if((SID_u8 < DCM_SERVICE_ISO_LOWERLIMIT) ||
       ((SID_u8 > DCM_SERVICE_ISO_MIDLIMIT)  && (SID_u8 < DCM_SERVICE_ISO_UPPERLIMIT)))
    {
        Dcm_Lok_OBDDsdSendNegativeResponse(ErrorCode_u8);
    }
    else
    {

        Dcm_OBDMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;
        Dcm_OBDGlobal_st.dataResponseByDsd_b = TRUE;
        Dcm_OBDProcessingDone(&Dcm_OBDMsgContext_st);
    }
#else

    Dcm_Lok_OBDDsdSendNegativeResponse(ErrorCode_u8);
#endif
}
#endif

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdVerifySubFncID(
        uint8* idxSubservice_u8,
        const Dcm_Dsld_ServiceType* service_pcs,
        Dcm_NegativeResponseCodeType* ErrorCode)
{
    const Dcm_Dsld_SubServiceType* adrSubservice_pcst;
    const Dcm_MsgContextType* Msgcontext_s = &Dcm_DsldMsgContext_st;
    Std_ReturnType VerificationResult_u8 = E_NOT_OK;

    uint8 dataSubfunction_u8;
    *idxSubservice_u8 = DCM_DEFAULT_VALUE;
    *ErrorCode = DCM_DEFAULT_VALUE;

    if (Msgcontext_s->reqDataLen > DCM_DEFAULT_VALUE)
    {

        adrSubservice_pcst = service_pcs->ptr_subservice_table_pcs;

        Dcm_Lok_CheckSuppressPositiveResponse(&dataSubfunction_u8);

        while(*idxSubservice_u8 < service_pcs->num_sf_u8)
        {
            if (dataSubfunction_u8 == adrSubservice_pcst[*idxSubservice_u8].subservice_id_u8)
            {
                break;
            }
            (*idxSubservice_u8)++;
        }

        if (*idxSubservice_u8 < service_pcs->num_sf_u8)
        {
            VerificationResult_u8 = E_OK;
        }

        else
        {
            *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
    }
    else
    {

        if (service_pcs->servicelocator_b == FALSE)
        {

            DcmAppl_DcmGetNRCForMinLengthCheck(
                    Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8, service_pcs->sid_u8,
                    ErrorCode);
        }
        if (*ErrorCode == DCM_DEFAULT_VALUE)
        {

            *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
    }
    return VerificationResult_u8;
}

#if((DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)||(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF))
static void Dcm_Lok_ProcessResult(Std_ReturnType Result,boolean Context,Dcm_NegativeResponseCodeType ErrorCode)
{
    if(Result == E_OK)
    {

    }
    else if(Result == DCM_E_REQUEST_NOT_ACCEPTED)
    {
#if ((DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS != 0u) || (DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS !=0u))
        Dcm_Dsd_CallRTEConfirmation((Dcm_ConfirmationStatusType)DCM_RES_POS_NOT_OK,Context);
#endif
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
        if(Context == DCM_OBDCONTEXT)
        {
           Dcm_Lok_SetOBDState((DCM_OBD_IDLE));
        }
        else
#endif
        {
           Dcm_Lok_SetDsdState(DSD_IDLE);
           Dcm_Lok_SetDslState((DSL_STATE_IDLE));
           Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
        }
    }
    else
    {
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
       if(Context == DCM_OBDCONTEXT)
       {
           Dcm_Lok_OBDDsdSendNegativeResponse(ErrorCode);
       }
       else
#endif
       {
           Dcm_Lok_DsdSendNegativeResponse(ErrorCode);
       }
    }
#if ((DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS == 0u) && (DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS ==0u) \
      && (DCM_PARALLELPROCESSING_ENABLED == DCM_CFG_OFF))
        (void)Context;
#endif
}
#endif

#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdManufacturerNotification
                             (Dcm_MsgContextType MsgContext_st,
                               uint8 SID,uint8 RequestType,
                              uint16 SourceAddress,boolean Context)
{
    Std_ReturnType Manufacturer_ReturnValue;
    Dcm_NegativeResponseCodeType ErrorCode = DCM_DEFAULT_VALUE;
    PduLengthType RequestLength = MsgContext_st.reqDataLen;
    PduIdType DcmRxPduId = MsgContext_st.dcmRxPduId;
    const uint8* const RequestData = MsgContext_st.reqData;
#if(DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS !=0)
#if((DCM_CFG_INDICATION_DATASIZE_UINT32==DCM_CFG_OFF))
    uint16 localRequestLength = (uint16)MsgContext_st.reqDataLen;
#else
    PduLengthType localRequestLength = MsgContext_st.reqDataLen;
#endif
#endif
#if(DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS !=0)
    uint32_least index_ui;
    Std_ReturnType ManufacturerNotif_Result = E_OK;
    Dcm_NegativeResponseCodeType dataNegRespCode_u8 = DCM_DEFAULT_VALUE;
#endif

    Manufacturer_ReturnValue = DcmAppl_ManufacturerNotification(SID,RequestData,RequestLength,RequestType,DcmRxPduId,SourceAddress,&Dcm_DsldMsgContext_st,&ErrorCode);

    if(Manufacturer_ReturnValue != DCM_E_PENDING)
    {
#if(DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS !=0)

        for(index_ui=0x00u;index_ui<DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS;index_ui++)
        {
            ManufacturerNotif_Result =(*Dcm_Rte_ManufacturerNotification_a[index_ui])(SID,RequestData,localRequestLength,RequestType,SourceAddress,&dataNegRespCode_u8);
            if( (ManufacturerNotif_Result == E_NOT_OK) && (ErrorCode == DCM_DEFAULT_VALUE) )
            {
                ErrorCode = dataNegRespCode_u8;
            }

            Manufacturer_ReturnValue = (ManufacturerNotif_Result > Manufacturer_ReturnValue)?ManufacturerNotif_Result:Manufacturer_ReturnValue;
        }

#if ((DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_INDICATION_DATASIZE_UINT32==DCM_CFG_OFF))

        if(RequestLength>DCM_UINT16_MAXVALUE)
        {
            DCM_DET_ERROR(DCM_MANUFACTURENOTIFICATION_ID , DCM_E_PARAM )
        }
#endif
#endif
        Dcm_Lok_ProcessResult(Manufacturer_ReturnValue,Context,ErrorCode);
    }
    return Manufacturer_ReturnValue;
}
#endif

#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdSupplierNotification(Dcm_MsgContextType MsgContext_st,
                                                             uint8 SID,uint8 RequestType,
                                                             uint16 SourceAddress, boolean Context)
{
    Std_ReturnType Supplier_ReturnValue;
    Dcm_NegativeResponseCodeType ErrorCode = DCM_DEFAULT_VALUE;
#if(DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS != DCM_DEFAULT_VALUE)
    uint32_least index_ui;
    Std_ReturnType SupplierNotif_Result = E_OK;
    Dcm_NegativeResponseCodeType dataNegRespCode_u8 = DCM_DEFAULT_VALUE;
#endif
    PduLengthType RequestLength = MsgContext_st.reqDataLen;
    PduIdType DcmRxPduId = MsgContext_st.dcmRxPduId;
    const uint8* const RequestData = MsgContext_st.reqData;
#if(DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS != DCM_DEFAULT_VALUE)
#if((DCM_CFG_INDICATION_DATASIZE_UINT32==DCM_CFG_OFF))
    uint16 localRequestLength = (uint16)MsgContext_st.reqDataLen;
#else
    PduLengthType localRequestLength = MsgContext_st.reqDataLen;
#endif
#endif

    Supplier_ReturnValue = DcmAppl_DcmNotification(SID,RequestData,RequestLength,RequestType,DcmRxPduId,SourceAddress,&ErrorCode);
    if(Supplier_ReturnValue != DCM_E_PENDING)
    {

#if(DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS != DCM_DEFAULT_VALUE)

        for(index_ui= DCM_DEFAULT_VALUE;index_ui<DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS; index_ui++)
        {
            SupplierNotif_Result = (*Dcm_Rte_SupplierNotification_a[index_ui])
                                    (SID,RequestData,localRequestLength,RequestType,SourceAddress,&dataNegRespCode_u8);
            if( (SupplierNotif_Result == E_NOT_OK) && (ErrorCode == DCM_DEFAULT_VALUE) )
            {
                ErrorCode = dataNegRespCode_u8;
            }

            Supplier_ReturnValue = (SupplierNotif_Result > Supplier_ReturnValue)?
                                     SupplierNotif_Result:Supplier_ReturnValue;
        }

#if ((DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_INDICATION_DATASIZE_UINT32==DCM_CFG_OFF))

        if(RequestLength>DCM_UINT16_MAXVALUE)
        {
            DCM_DET_ERROR(DCM_SUPPLIERNOTIFICATION_ID , DCM_E_PARAM )
        }
#endif
#endif
        Dcm_Lok_ProcessResult(Supplier_ReturnValue,Context,ErrorCode);
    }
    return Supplier_ReturnValue;
}
#endif

LOCAL_INLINE void Dcm_Lok_UpdateOpStatus(Std_ReturnType ServiceResult_u8)
{
    if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].servicelocator_b != FALSE)
    {
        if((ServiceResult_u8 != DCM_E_PENDING) && (ServiceResult_u8 != DCM_E_FORCE_RCRRP))
        {
            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        }
    }
    else
    {
        if(ServiceResult_u8 == DCM_E_PENDING)
        {
            Dcm_ExtSrvOpStatus_u8 = DCM_PENDING;
        }
        else if(ServiceResult_u8 == DCM_E_FORCE_RCRRP)
        {
            Dcm_ExtSrvOpStatus_u8 = DCM_FORCE_RCRRP_OK;
        }
        else
        {
            Dcm_ExtSrvOpStatus_u8 = DCM_INITIAL;
        }
    }
}

LOCAL_INLINE void Dcm_Lok_DsdInitiateResponseTransmission(Std_ReturnType ServiceResult_u8,
                                    Dcm_NegativeResponseCodeType ErrorCode_u8)
{
    Dcm_Lok_UpdateOpStatus(ServiceResult_u8);
    if (ServiceResult_u8 == E_OK)
    {

        Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
    }
    else if (ServiceResult_u8 == DCM_E_PENDING)
    {

    }
    else if (ServiceResult_u8 == DCM_E_FORCE_RCRRP)
    {
        (void) Dcm_ForceRespPend();
    }
    else
    {

        if (ErrorCode_u8 == DCM_DEFAULT_VALUE)
        {
            ErrorCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }

        Dcm_SetNegResponse(&Dcm_DsldMsgContext_st, ErrorCode_u8);
        Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
    }
}

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdVerifyData(void)
{

    const Dcm_Dsld_ServiceType* adrService_pcst;
    uint32 ActiveMask_u32;
    uint8 idxIndex_qu8;
    Dcm_NegativeResponseCodeType ErrorCode_u8 = DCM_DEFAULT_VALUE;
    Std_ReturnType  VerificationResult_u8 = E_NOT_OK;

    if (Dcm_Lok_DsdObtainSidIndex(&idxIndex_qu8, Dcm_DsldGlobal_st.dataSid_u8))
    {

        Dcm_DsldGlobal_st.idxService_u8 = idxIndex_qu8;

        Dcm_DsldMsgContext_st.idContext = Dcm_DsldGlobal_st.dataSid_u8;

        adrService_pcst = &(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]);

        ActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSession_u8);

        if ((adrService_pcst->allowed_session_b32 & ActiveMask_u32) == (ActiveMask_u32))
        {

            ActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSecurity_u8);

            if ((adrService_pcst->allowed_security_b32 & ActiveMask_u32) == (ActiveMask_u32))
            {

                VerificationResult_u8 = (*adrService_pcst->adrUserServiceModeRule_pfct)
                                        (&ErrorCode_u8, Dcm_DsldGlobal_st.dataSid_u8);
#if(DCM_CFG_DSD_MODERULESERVICE_ENABLED != DCM_CFG_OFF)

                if((adrService_pcst->moderule_fp != ((Dcm_ModeRuleType)NULL_PTR)) && (VerificationResult_u8 == E_OK))
                {

                    VerificationResult_u8 = (adrService_pcst->moderule_fp(&ErrorCode_u8) == TRUE)?E_OK:E_NOT_OK;
                }
#endif
            }
            else
            {
                ErrorCode_u8 = DCM_E_SECURITYACCESSDENIED;
            }
        }
        else
        {

           ErrorCode_u8=Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].nrc_sessnot_supported_u8;
        }

        if (VerificationResult_u8 != E_OK)
        {
            Dcm_Lok_DsdSendNegativeResponse(ErrorCode_u8);
        }
    }
    else
    {
        Dcm_Lok_ProcessServiceNotSupported();
    }
    return VerificationResult_u8;
}

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
LOCAL_INLINE Std_ReturnType Dcm_Lok_OBDVerifyData(void)
{

    const Dcm_Dsld_ServiceType* adrService_pcst;
    uint32 ActiveMask_u32;
    uint8 idxIndex_qu8;
    Dcm_NegativeResponseCodeType ErrorCode_u8 = DCM_DEFAULT_VALUE;
    Std_ReturnType  VerificationResult_u8 = E_NOT_OK;

    if (Dcm_Lok_ObtainSidIndexOfOBD(&idxIndex_qu8,Dcm_OBDGlobal_st.dataSid_u8))
    {

        Dcm_OBDGlobal_st.idxService_u8 = idxIndex_qu8;

        Dcm_OBDMsgContext_st.idContext = Dcm_OBDGlobal_st.dataSid_u8;

        adrService_pcst = &(Dcm_OBDSrvTable_pcst[Dcm_OBDGlobal_st.idxService_u8]);

        ActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSecurity_u8);

        if ((adrService_pcst->allowed_security_b32 & ActiveMask_u32) == (ActiveMask_u32))
        {

            VerificationResult_u8 = (*adrService_pcst->adrUserServiceModeRule_pfct)
                                    (&ErrorCode_u8, Dcm_OBDGlobal_st.dataSid_u8);
#if(DCM_CFG_DSD_MODERULESERVICE_ENABLED != DCM_CFG_OFF)

            if((adrService_pcst->moderule_fp != ((Dcm_ModeRuleType)NULL_PTR)) && (VerificationResult_u8 == E_OK))
            {

                VerificationResult_u8 = (adrService_pcst->moderule_fp(&ErrorCode_u8) == TRUE)?E_OK:E_NOT_OK;
            }
#endif
        }
        else
        {
            ErrorCode_u8 = DCM_E_SECURITYACCESSDENIED;
        }
        if (VerificationResult_u8 != E_OK)
        {
            Dcm_Lok_OBDDsdSendNegativeResponse(ErrorCode_u8);
        }
    }
    else
    {
        Dcm_Lok_ProcessOBDServiceNotSupported();
    }
    return VerificationResult_u8;
}
#endif

LOCAL_INLINE boolean Dcm_Lok_DsdIsServiceRunning(void)
{
    boolean IsServiceRunning_b = FALSE;
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)

    IsServiceRunning_b = ((Dcm_DsdRoe2State_en != DSD_IDLE) &&
                         (Dcm_Roe2MesContext_st.idContext == Dcm_DsldGlobal_st.dataSid_u8));
#endif

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
    if((Dcm_DsldGlobal_st.dataSid_u8 == DCM_SID_DIAGNOSTICSESSIONCONTROL) &&
        (Dcm_Lok_GetOBDState()!= DCM_OBD_IDLE ))
    {
        IsServiceRunning_b = TRUE;
    }
#endif
    return IsServiceRunning_b;
}

LOCAL_INLINE void Dcm_Lok_DsdProcessService(void)
{
    Std_ReturnType ServiceResult_u8;
    const Dcm_Dsld_ServiceType* adrServiceTable_pcst;
    Dcm_NegativeResponseCodeType ErrorCode_u8 = DCM_DEFAULT_VALUE;

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_PagedBufferTimeout();
#endif
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    Dcm_DsldRoeTimeOut();
#endif

    if(Dcm_Lok_DsdIsServiceRunning() == FALSE)
    {
        if(Dcm_Lok_GetDsdState() == DSD_CALL_SERVICE)
        {
            adrServiceTable_pcst = &Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8];

            if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].servicelocator_b != FALSE)
            {
                ServiceResult_u8 = (*(adrServiceTable_pcst)->service_handler_fp)(Dcm_SrvOpstatus_u8,&Dcm_DsldMsgContext_st,
                                                  &ErrorCode_u8);
            }
            else
            {
                ServiceResult_u8 = (*(adrServiceTable_pcst)->service_handler_fp)(Dcm_ExtSrvOpStatus_u8,&Dcm_DsldMsgContext_st,
                                                  &ErrorCode_u8);
            }

            Dcm_Lok_DsdInitiateResponseTransmission(ServiceResult_u8,ErrorCode_u8);
        }
    }
}

#if((DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)||(DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF))

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdNotification(boolean Indication_Flag,boolean Context)
{
    Dcm_MsgContextType MsgContext_st;
    uint8 Sid;
    uint8 RequestType;
    uint16 SourceAddress;
    uint8 Result_u8 = E_NOT_OK;

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
    if(Context == DCM_OBDCONTEXT)
    {
        MsgContext_st = Dcm_OBDMsgContext_st;
        Sid = Dcm_OBDGlobal_st.dataSid_u8;
        RequestType = Dcm_OBDMsgContext_st.msgAddInfo.reqType;
        SourceAddress = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_OBDMsgContext_st.dcmRxPduId]].testaddr_u16;
    }
    else
#endif
    {
        MsgContext_st = Dcm_DsldMsgContext_st;
        Sid = Dcm_DsldGlobal_st.dataSid_u8;
        RequestType = Dcm_DsldMsgContext_st.msgAddInfo.reqType;
        SourceAddress = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16;
    }

    if(Indication_Flag == DCM_MANUFACTURERNOTIFICATION)
    {
#if(DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
        Result_u8 =Dcm_Lok_DsdManufacturerNotification(MsgContext_st,Sid,RequestType,SourceAddress,Context);
#endif
    }
#if(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
    else
    {
        Result_u8 = Dcm_Lok_DsdSupplierNotification(MsgContext_st,Sid,RequestType,SourceAddress,Context);
    }
#endif
    return Result_u8;
}
#endif

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdCheckSubFunction(void)
{

    uint8 idxSubservice_u8;
    uint32 dataActiveMask_u32;
    Dcm_NegativeResponseCodeType ErrorCode = DCM_DEFAULT_VALUE;
    const Dcm_Dsld_ServiceType* service_pcs = &(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]);
    Std_ReturnType VerificationResult_u8 = Dcm_Lok_DsdVerifySubFncID(&idxSubservice_u8,service_pcs,&ErrorCode);

    const Dcm_Dsld_SubServiceType* adrSubservice_pcst =
            (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]).ptr_subservice_table_pcs;

    if(VerificationResult_u8 == E_OK)
    {
        VerificationResult_u8 = E_NOT_OK;

        dataActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSession_u8);

        if ((adrSubservice_pcst[idxSubservice_u8].allowed_session_b32 & dataActiveMask_u32) == (dataActiveMask_u32))
        {

            dataActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSecurity_u8);

            if ((adrSubservice_pcst[idxSubservice_u8].allowed_security_b32 & dataActiveMask_u32)
                    == (dataActiveMask_u32))
            {

                VerificationResult_u8 = (*adrSubservice_pcst[idxSubservice_u8].adrUserSubServiceModeRule_pfct)
                      (&ErrorCode,Dcm_DsldGlobal_st.dataSid_u8, adrSubservice_pcst[idxSubservice_u8].subservice_id_u8);

                ErrorCode=((VerificationResult_u8 != E_OK) && (ErrorCode == 0x00))?DCM_E_CONDITIONSNOTCORRECT:ErrorCode;
#if(DCM_CFG_DSD_MODERULESUBFNC_ENABLED != DCM_CFG_OFF)

                if((adrSubservice_pcst[idxSubservice_u8].moderule_fp != (Dcm_ModeRuleType)NULL_PTR) &&
                   (VerificationResult_u8==E_OK))
                {

                    VerificationResult_u8 = ((*adrSubservice_pcst[idxSubservice_u8].moderule_fp)
                                            (&ErrorCode) == TRUE)?E_OK:E_NOT_OK;
                }
#endif
            }

            else
            {
                ErrorCode = DCM_E_SECURITYACCESSDENIED;
            }
        }

        else
        {
            ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
        }
    }
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ))

    if((ErrorCode!=0x00u) && (service_pcs->sid_u8==DCM_SECURITYACCESS_SID) && (service_pcs->servicelocator_b!=FALSE))
    {

        Dcm_ResetAccessType();

    }
#endif
    if(VerificationResult_u8 != E_OK)
    {
        Dcm_Lok_DsdSendNegativeResponse(ErrorCode);
    }
    return VerificationResult_u8;
}

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
LOCAL_INLINE void Dcm_Lok_OBDServiceTableInit(void)
{
    Dcm_MsgItemType* adrRxBuffer_pu8;
    const Dcm_Dsld_protocol_tableType* adrActiveProtocolTable_pcst =
            &(Dcm_DsldProtocol_pcst[Dcm_OBDGlobal_st.idxCurrentProtocol_u8]);

    Dcm_OBDGlobal_st.adrActiveTxBuffer_tpu8 = adrActiveProtocolTable_pcst->tx_buffer_pa;

    Dcm_OBDMsgContext_st.resMaxDataLen = adrActiveProtocolTable_pcst->tx_buffer_size_u32 - DCM_SID_LENGTH;
    adrRxBuffer_pu8 = Dcm_DsldProtocol_pcst[Dcm_OBDGlobal_st.idxCurrentProtocol_u8].rx_mainBuffer_pa;

    Dcm_OBDGlobal_st.dataResponseByDsd_b = FALSE;

    Dcm_OBDGlobal_st.dataSid_u8 = adrRxBuffer_pu8[DCM_REQUESTBUFFER_INDEX];

    Dcm_OBDGlobal_st.idxService_u8 = DCM_DEFAULT_VALUE;

    Dcm_OBDGlobal_st.stResponseType_en = DCM_DSLD_POS_RESPONSE;

    Dcm_OBDMsgContext_st.resDataLen = DCM_DEFAULT_VALUE;
    Dcm_OBDTransmit_st.TxResponseLength_u32 = DCM_DEFAULT_VALUE;
    Dcm_OBDMsgContext_st.dcmRxPduId = Dcm_OBDGlobal_st.dataActiveRxPduId_u8;

    Dcm_OBDMsgContext_st.msgAddInfo.reqType = (Dcm_OBDGlobal_st.dataActiveRxPduId_u8 >= DCM_INDEX_FUNC_RX_PDUID)?
                                                DCM_PRV_FUNCTIONAL_REQUEST : DCM_PRV_PHYSICAL_REQUEST;

    Dcm_OBDMsgContext_st.reqDataLen = (Dcm_MsgLenType) Dcm_OBDGlobal_st.dataRequestLength_u16 - DCM_SID_LENGTH;

    Dcm_OBDMsgContext_st.reqData = &(adrRxBuffer_pu8[DCM_REQUESTBUFFER_INDEX+DCM_SID_LENGTH]);

    Dcm_OBDMsgContext_st.resData = &(Dcm_OBDGlobal_st.adrActiveTxBuffer_tpu8[DCM_RESPONSEBUFFER_INDEX]);
}
#endif

LOCAL_INLINE void Dcm_Lok_DsdServiceTableInit(void)
{
    Dcm_MsgItemType* adrRxBuffer_pu8;
    const Dcm_Dsld_protocol_tableType* adrActiveProtocolTable_pcst;

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

    if(Dcm_Lok_GetDslState() == DSL_STATE_ROETYPE1_RECEIVED)
    {

        Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = Dcm_DsldRoe_pcst->txbuffer_ptr;

        Dcm_DsldMsgContext_st.resMaxDataLen = Dcm_DsldRoe_pcst->txbuffer_length_u32 - DCM_SID_LENGTH;

        adrRxBuffer_pu8 = Dcm_DsldRoe_pcst->txbuffer_ptr;

        DCM_TimerStart(Dcm_DsldGlobal_st.dataTimerTimeout_u32,DCM_CFG_GET_TIMEOUT,          \
                        Dcm_TimerStartTick_u32,Dcm_CounterValueTimerStatus_uchr)
    }
    else
#endif
    {

        adrActiveProtocolTable_pcst = &(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8]);

        Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = adrActiveProtocolTable_pcst->tx_buffer_pa;

        Dcm_DsldMsgContext_st.resMaxDataLen = adrActiveProtocolTable_pcst->tx_buffer_size_u32 - DCM_SID_LENGTH;

        Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_UDS_TESTER_SOURCE;

        adrRxBuffer_pu8 = Dcm_GetActiveBuffer();
    }

    Dcm_DsldGlobal_st.dataResponseByDsd_b = FALSE;

    Dcm_DsldGlobal_st.dataSid_u8 = adrRxBuffer_pu8[DCM_REQUESTBUFFER_INDEX];

    Dcm_DsldGlobal_st.idxService_u8 = DCM_DEFAULT_VALUE;

    Dcm_DsldGlobal_st.stResponseType_en = DCM_DSLD_POS_RESPONSE;

    Dcm_DsldMsgContext_st.resDataLen = DCM_DEFAULT_VALUE;
    Dcm_DslTransmit_st.TxResponseLength_u32 = DCM_DEFAULT_VALUE;

    Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

    Dcm_DsldMsgContext_st.msgAddInfo.reqType = (Dcm_DsldGlobal_st.dataActiveRxPduId_u8 >= DCM_INDEX_FUNC_RX_PDUID) ?
                                                DCM_PRV_FUNCTIONAL_REQUEST : DCM_PRV_PHYSICAL_REQUEST;

    Dcm_DsldMsgContext_st.reqDataLen = (Dcm_MsgLenType) Dcm_DsldGlobal_st.dataRequestLength_u16 - DCM_SID_LENGTH;

    Dcm_DsldMsgContext_st.reqData = &(adrRxBuffer_pu8[DCM_REQUESTBUFFER_INDEX+DCM_SID_LENGTH]);

    Dcm_DsldMsgContext_st.resData = &(Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[DCM_RESPONSEBUFFER_INDEX]);

    Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;
}

LOCAL_INLINE void Dcm_Lok_CheckSuppressPositiveResponseforRC(void)
{
    if(Dcm_DsldGlobal_st.dataSid_u8==DCM_DSP_SID_ROUTINECONTROL)
    {

        if(((*Dcm_DsldMsgContext_st.reqData) & (DCM_SUPPRESPOSITIVERESP_MASK)) == DCM_SUPPRESPOSITIVERESP_MASK)
        {
            Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;

            (*Dcm_DsldMsgContext_st.reqData) = ((*Dcm_DsldMsgContext_st.reqData) & DCM_REMOVESUPPRESSRESPONSEBIT_MASK);
        }

    }
}
#endif

