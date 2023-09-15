#ifndef DCM_DSD_PRV_H
#define DCM_DSD_PRV_H

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmCore_DslDsd_Pub.hpp"

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

LOCAL_INLINE boolean Dcm_Lok_IsSubFunctionSupported(void){
   const Dcm_Dsld_ServiceType* adrActiveService_pcst = &(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]);
    return(adrActiveService_pcst->subfunction_exist_b);
}

LOCAL_INLINE void Dcm_Lok_CheckSuppressPositiveResponse(
   uint8* subfunction){
   if(((*Dcm_DsldMsgContext_st.reqData) & (DCM_SUPPRESPOSITIVERESP_MASK)) == DCM_SUPPRESPOSITIVERESP_MASK){
        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;
        (*Dcm_DsldMsgContext_st.reqData) = ((*Dcm_DsldMsgContext_st.reqData) & DCM_REMOVESUPPRESSRESPONSEBIT_MASK);
   }
   else{
        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;
   }
    (*subfunction) = (Dcm_DsldGlobal_st.dataSid_u8 != DCM_RESPONSEONEVENT_SID)? (*Dcm_DsldMsgContext_st.reqData)
                                          :((*Dcm_DsldMsgContext_st.reqData) & DCM_REMOVEEVENTSTORAGEBIT_MASK);
}

LOCAL_INLINE boolean Dcm_Lok_DsdObtainSidIndex(
   uint8* idxIndex_qu8,
   const uint8 dataSid_cu8){
   boolean IsSidAvailable_b = FALSE;
   uint8 nrServices_u8 = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].num_services_u8;
    *idxIndex_qu8 = DCM_DEFAULT_VALUE;
   while(*idxIndex_qu8 < nrServices_u8){
      if(Dcm_DsldSrvTable_pcst[*idxIndex_qu8].sid_u8 == dataSid_cu8){
            IsSidAvailable_b = TRUE;
            break;
        }
        (*idxIndex_qu8)++;
   }
    return(IsSidAvailable_b);
}

LOCAL_INLINE void Dcm_Lok_DsdSendNegativeResponse(
   Dcm_NegativeResponseCodeType ErrorCode){
    ErrorCode = (ErrorCode == DCM_DEFAULT_VALUE)?DCM_E_CONDITIONSNOTCORRECT:ErrorCode;
    Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
    Dcm_SetNegResponse(&Dcm_DsldMsgContext_st,ErrorCode);
    Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
}

LOCAL_INLINE void Dcm_Lok_ProcessServiceNotSupported(
   Dcm_NegativeResponseCodeType ErrorCode_u8){
   uint8 SID_u8 = Dcm_DsldGlobal_st.dataSid_u8;
   if((SID_u8 < DCM_SERVICE_ISO_LOWERLIMIT) ||
       ((SID_u8 > DCM_SERVICE_ISO_MIDLIMIT) && (SID_u8 < DCM_SERVICE_ISO_UPPERLIMIT))){
        ErrorCode_u8 = DCM_E_SERVICENOTSUPPORTED;
        Dcm_Lok_DsdSendNegativeResponse(ErrorCode_u8);
   }
   else{
        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;
        Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
        Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
   }
}

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdVerifySubFncID(
        uint8* idxSubservice_u8
   ,     const Dcm_Dsld_ServiceType* service_pcs
   ,
   Dcm_NegativeResponseCodeType* ErrorCode){
   const Dcm_Dsld_SubServiceType* adrSubservice_pcst;
   const Dcm_MsgContextType* Msgcontext_s = &Dcm_DsldMsgContext_st;
    Std_ReturnType VerificationResult_u8 = E_NOT_OK;
   uint8 dataSubfunction_u8;
    *idxSubservice_u8 = DCM_DEFAULT_VALUE;
    *ErrorCode = DCM_DEFAULT_VALUE;
   if(Msgcontext_s->reqDataLen > DCM_DEFAULT_VALUE){
        adrSubservice_pcst = service_pcs->ptr_subservice_table_pcs;
        Dcm_Lok_CheckSuppressPositiveResponse(&dataSubfunction_u8);
      while(*idxSubservice_u8 < service_pcs->num_sf_u8){
         if(dataSubfunction_u8 == adrSubservice_pcst[*idxSubservice_u8].subservice_id_u8){
                break;
            }
            (*idxSubservice_u8)++;
        }
      if(*idxSubservice_u8 < service_pcs->num_sf_u8){
            VerificationResult_u8 = E_OK;
        }
        else{
            *ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
   }
   else{
      if(service_pcs->servicelocator_b == FALSE){
            DcmAppl_DcmGetNRCForMinLengthCheck(
                    Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8, service_pcs->sid_u8
   ,     ErrorCode);
        }
      if(*ErrorCode == DCM_DEFAULT_VALUE){
            *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
   }
    return VerificationResult_u8;
}

#if(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdSupplierNotification(const uint8* const RequestData
   ,     Type_SwcServiceCom_tLengthPdu RequestLength,uint8 RequestType
   ,
   Type_SwcServiceCom_tIdPdu DcmRxPduId,
   uint16 SourceAddress){
   Std_ReturnType Supplier_ReturnValue;
   Dcm_NegativeResponseCodeType ErrorCode = DCM_DEFAULT_VALUE;
   uint8 SID = Dcm_DsldGlobal_st.dataSid_u8;
   Supplier_ReturnValue = DcmAppl_DcmNotification(
      SID,
      RequestData,
      RequestLength,
      RequestType,
      DcmRxPduId,
      SourceAddress,
      &ErrorCode);
   if(Supplier_ReturnValue != DCM_E_PENDING){
      if(Supplier_ReturnValue == E_OK){
        }
      else if(Supplier_ReturnValue == DCM_E_REQUEST_NOT_ACCEPTED){
            Dcm_Lok_SetDsdState(DSD_IDLE);
            Dcm_Lok_SetDslState(DSL_STATE_IDLE);
            Dcm_Lok_SetDslSubState(DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING);
        }
        else{
            Dcm_Lok_DsdSendNegativeResponse(ErrorCode);
        }
   }
    return Supplier_ReturnValue;
}
#endif

LOCAL_INLINE void Dcm_Lok_DsdInitiateResponseTransmission(Std_ReturnType ServiceResult_u8
   ,
   Dcm_NegativeResponseCodeType ErrorCode_u8){
   if(ServiceResult_u8 == E_OK){
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
   }
   else if(ServiceResult_u8 == DCM_E_PENDING){
   }
   else if(ServiceResult_u8 == DCM_E_FORCE_RCRRP){
        (void) Dcm_ForceRespPend();
   }
   else{
      if(ErrorCode_u8 == DCM_DEFAULT_VALUE){
            ErrorCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        Dcm_SetNegResponse(&Dcm_DsldMsgContext_st, ErrorCode_u8);
        Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
   }
}

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdVerifyData(void){
   const Dcm_Dsld_ServiceType* adrService_pcst;
   uint32 ActiveMask_u32;
   uint8 idxIndex_qu8;
    Dcm_NegativeResponseCodeType ErrorCode_u8 = DCM_DEFAULT_VALUE;
    Std_ReturnType  VerificationResult_u8 = E_NOT_OK;
   if(Dcm_Lok_DsdObtainSidIndex(
      &idxIndex_qu8,
      Dcm_DsldGlobal_st.dataSid_u8)){
        Dcm_DsldGlobal_st.idxService_u8 = idxIndex_qu8;
        Dcm_DsldMsgContext_st.idContext = Dcm_DsldGlobal_st.dataSid_u8;
        adrService_pcst = &(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]);
        ActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSession_u8);
      if((adrService_pcst->allowed_session_b32 & ActiveMask_u32) == (ActiveMask_u32)){
            ActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSecurity_u8);
         if((adrService_pcst->allowed_security_b32 & ActiveMask_u32) == (ActiveMask_u32)){
                VerificationResult_u8 = (*adrService_pcst->adrUserServiceModeRule_pfct)
                                        (&ErrorCode_u8, Dcm_DsldGlobal_st.dataSid_u8);
            }
            else{
                ErrorCode_u8 = DCM_E_SECURITYACCESSDENIED;
            }
        }
        else{
           ErrorCode_u8=CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].nrc_sessnot_supported_u8;
        }
      if(VerificationResult_u8 != E_OK){
            Dcm_Lok_DsdSendNegativeResponse(ErrorCode_u8);
        }
   }
   else{
        Dcm_Lok_ProcessServiceNotSupported(ErrorCode_u8);
   }
    return VerificationResult_u8;
}

LOCAL_INLINE boolean Dcm_Lok_DsdIsServiceRunning(void){
   boolean IsServiceRunning_b = FALSE;
    return IsServiceRunning_b;
}

LOCAL_INLINE void Dcm_Lok_DsdProcessService(void){
    Std_ReturnType ServiceResult_u8;
   const Dcm_Dsld_ServiceType* adrServiceTable_pcst;
    Dcm_NegativeResponseCodeType ErrorCode_u8 = DCM_DEFAULT_VALUE;
   if(Dcm_Lok_DsdIsServiceRunning() == FALSE){
      if(Dcm_Lok_GetDsdState() == DSD_CALL_SERVICE){
            adrServiceTable_pcst = &Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8];
            ServiceResult_u8 = (*(adrServiceTable_pcst)->service_handler_fp)(Dcm_SrvOpstatus_u8, &Dcm_DsldMsgContext_st
   ,     &ErrorCode_u8);
            Dcm_Lok_DsdInitiateResponseTransmission(ServiceResult_u8,ErrorCode_u8);
        }
   }
}

#if((DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)||(DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF))
LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdNotification(
   boolean Indication_Flag){
   Type_SwcServiceCom_tLengthPdu RequestLength = (Type_SwcServiceCom_tLengthPdu)Dcm_DsldMsgContext_st.reqDataLen;
   uint8 RequestType = Dcm_DsldMsgContext_st.msgAddInfo.reqType;
   Type_SwcServiceCom_tIdPdu DcmRxPduId = Dcm_DsldMsgContext_st.dcmRxPduId;
   uint16 SourceAddress = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16;
   const uint8* const RequestData = Dcm_DsldMsgContext_st.reqData;
   uint8 Result_u8 = E_NOT_OK;
   if(Indication_Flag == DCM_MANUFACTURERNOTIFICATION){
   }
#if(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
   else{
        Result_u8 = Dcm_Lok_DsdSupplierNotification(RequestData,RequestLength,RequestType,DcmRxPduId,SourceAddress);
   }
#endif
    return Result_u8;
}
#endif

LOCAL_INLINE Std_ReturnType Dcm_Lok_DsdCheckSubFunction(void){
   uint8 idxSubservice_u8;
   uint32 dataActiveMask_u32;
    Dcm_NegativeResponseCodeType ErrorCode = DCM_DEFAULT_VALUE;
   const Dcm_Dsld_ServiceType* service_pcs = &(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]);
    Std_ReturnType VerificationResult_u8 = Dcm_Lok_DsdVerifySubFncID(&idxSubservice_u8,service_pcs,&ErrorCode);
   const Dcm_Dsld_SubServiceType *adrSubservice_pcst = (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]).ptr_subservice_table_pcs;
   if(VerificationResult_u8 == E_OK){
        VerificationResult_u8 = E_NOT_OK;
        dataActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSession_u8);
      if((adrSubservice_pcst[idxSubservice_u8].allowed_session_b32 & dataActiveMask_u32) == (dataActiveMask_u32)){
            dataActiveMask_u32 = (uint32) (DCM_DEFAULT_MASKVALUE << Dcm_DsldGlobal_st.idxActiveSecurity_u8);
         if((adrSubservice_pcst[idxSubservice_u8].allowed_security_b32 & dataActiveMask_u32) == (dataActiveMask_u32)){
                VerificationResult_u8 = (*adrSubservice_pcst[idxSubservice_u8].adrUserSubServiceModeRule_pfct)
                      (&ErrorCode,Dcm_DsldGlobal_st.dataSid_u8, adrSubservice_pcst[idxSubservice_u8].subservice_id_u8);
            ErrorCode =
                  ((VerificationResult_u8 != E_OK) && (ErrorCode == 0x00)) ? DCM_E_CONDITIONSNOTCORRECT : ErrorCode;
            }
            else{
                ErrorCode = DCM_E_SECURITYACCESSDENIED;
            }
        }
        else{
            ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
        }
   }
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ))
   if((ErrorCode != 0x00u) && (service_pcs->sid_u8 == DCM_SECURITYACCESS_SID) && (service_pcs->servicelocator_b != FALSE)){
        Dcm_ResetAccessType();
   }
#endif
   if(VerificationResult_u8 != E_OK){
        Dcm_Lok_DsdSendNegativeResponse(ErrorCode);
   }
    return VerificationResult_u8;
}

LOCAL_INLINE void Dcm_Lok_DsdServiceTableInit(void){
    Dcm_MsgItemType* adrRxBuffer_pu8;
   const Dcm_Dsld_protocol_tableType* adrActiveProtocolTable_pcst;
        adrActiveProtocolTable_pcst = &(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8]);
        Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = adrActiveProtocolTable_pcst->tx_buffer_pa;
        Dcm_DsldMsgContext_st.resMaxDataLen = adrActiveProtocolTable_pcst->tx_buffer_size_u32 - DCM_SID_LENGTH;
        Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_UDS_TESTER_SOURCE;
        adrRxBuffer_pu8 = Dcm_GetActiveBuffer();
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
}
#endif
