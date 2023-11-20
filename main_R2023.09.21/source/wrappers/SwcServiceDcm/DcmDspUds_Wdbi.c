#include "Std_Types.hpp"

#include "DcmDspUds_Wdbi_Inf.hpp"
#include "DcmDspUds_Wdbi_Inf.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stDspWdbiOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxwdbiDidIndexType;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint16,DCM_VAR)  s_dataDID_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR(boolean,DCM_VAR) s_loopbreak_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_SupportRet_t,AUTOMATIC) dataRetWriteSupport_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Std_ReturnType,AUTOMATIC)   dataRetWriteFunc_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static FUNC(void,DCM_CODE) Dcm_Lok_WDBIINIT_Pending(
   void){
   VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode;
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc;
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
    ptrWriteFnc=NULL_PTR;
    dataNegResCode = 0x0;
    ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
        ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
        if(ptrSigConfig->idxDcmDspControlInfo_u16 > 0)
        {
            ptrWriteFnc   = ptrControlSigConfig->adrWriteFnc_cpv;

            if((ptrWriteFnc != NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)
            ))
            {
         if(ptrDidConfig->dataFixedLength_b != FALSE){
                    (void)(*(WdbiFnc4_pfct)(ptrWriteFnc))(NULL_PTR,DCM_CANCEL,&dataNegResCode);
                }
                else{
                }
            }
            else{
                (void)dataNegResCode;
            }
        }
        else{
            (void)dataNegResCode;
        }
}

FUNC(void,DCM_CODE) Dcm_Dcm_WDBIInit (void){
    dataRetWriteFunc_u8=0x00;
   if((Dcm_stDspWdbiOpStatus_u8 == DCM_PENDING) && (s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)){
       Dcm_Lok_WDBIINIT_Pending();
   }
   else{
   }
    Dcm_SrvOpstatus_u8 =  DCM_INITIAL;
    Dcm_DidSignalIdx_u16 = 0x0;
    Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
    Dcm_ResetDIDIndexstruct(&s_Dcm_idxwdbiDidIndexType);
}

static FUNC(void,DCM_CODE) Dcm_Lok_WriteASYNCDID
                           (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,

                            P2VAR(void,AUTOMATIC, DCM_INTERN_CONST)  ptrWriteFnc
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,
   VAR (uint16, AUTOMATIC) posnDidSignal_u16){
   if(ptrDidConfig->dataFixedLength_b != FALSE){
         dataRetWriteFunc_u8 = (*(WdbiFnc4_pfct)(ptrWriteFnc))
                               (&pMsgContext->reqData[posnDidSignal_u16],Dcm_stDspWdbiOpStatus_u8,dataNegRespCode_u8);
     }
     else{
     }
 }

static FUNC(void,DCM_CODE) Dcm_Lok_WriteDidUsePort
                           (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2VAR(void,AUTOMATIC, DCM_INTERN_CONST)  ptrWriteFnc
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,
   VAR (uint16, AUTOMATIC) posnDidSignal_u16){
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
    ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
   if((ptrWriteFnc != NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)
    )){
        Dcm_Lok_WriteASYNCDID(dataNegRespCode_u8,pMsgContext,ptrWriteFnc,ptrDidConfig,posnDidSignal_u16);
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_WriteNormalDID(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8,
   P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext){
  P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
  P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
  P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
  P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc;
  VAR (uint16,  AUTOMATIC) posnDidSignal_u16;
  VAR (uint16,  AUTOMATIC) loopIndex_u16 = Dcm_DidSignalIdx_u16;
  VAR(boolean,  AUTOMATIC) Rtn_InfrastureError;
   for(;
         ((loopIndex_u16 < ptrDidConfig->nrSig_u16) && (dataRetWriteFunc_u8 == E_OK));
         loopIndex_u16++){
        Dcm_DidSignalIdx_u16 = loopIndex_u16;
        ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
        posnDidSignal_u16 = (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8u) +2u);
      if(ptrSigConfig->idxDcmDspControlInfo_u16 > 0u){
            ptrWriteFnc = ptrControlSigConfig->adrWriteFnc_cpv;
            Dcm_Lok_WriteDidUsePort(dataNegRespCode_u8,pMsgContext,ptrWriteFnc,ptrDidConfig,posnDidSignal_u16);
         if(dataRetWriteFunc_u8 != E_OK){
                Rtn_InfrastureError=Dcm_IsInfrastructureErrorPresent_b(dataRetWriteFunc_u8);
                 if((((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) ||
                     (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) ||
                      ((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER) || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE)))) && (Rtn_InfrastureError == TRUE)){
                  }
                 s_loopbreak_b =TRUE;
             }
             else{
                  *dataNegRespCode_u8=0x00;
                  Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
             }
        }
        else{
        }
      if(s_loopbreak_b == TRUE){
            s_loopbreak_b = FALSE;
            break;
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_WriteDidMaxLenCheck(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8,
   P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext){
VAR(uint16,AUTOMATIC)  nrLenDataRec_u16;
           nrLenDataRec_u16 = (Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataMaxDidLen_u16+2u);
      if(Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataFixedLength_b != FALSE){
         if(pMsgContext->reqDataLen != nrLenDataRec_u16){
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
           }
           else{
         if(pMsgContext->reqDataLen > nrLenDataRec_u16){
                   *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
               }
         else if(DcmAppl_DcmCheckWDBIReqLen(
            s_dataDID_u16,
            (pMsgContext->reqDataLen - 2u)) != E_OK){
                   *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
               }
               else{
               }
           }
}

static FUNC(void,DCM_CODE) Dcm_Priv_DidWriteSupport(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
){
VAR (uint32,AUTOMATIC) dataSessionMask_u32 = 0;
P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst;
        adrExtendedConfig_pcst = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrExtendedConfig_pcst;
    dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessWrite_u32;
   if(((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)){
        Dcm_Lok_WriteDidMaxLenCheck(dataNegRespCode_u8,pMsgContext);
   }
   else{
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
   if(*dataNegRespCode_u8 == 0){
      dataRetWriteSupport_en = Dcm_GetSupportOfIndex(&s_Dcm_idxwdbiDidIndexType, DCM_SUPPORT_WRITE,dataNegRespCode_u8);
      if(dataRetWriteSupport_en == DCM_SUPPORT_OK){
          Dcm_stDspWdbiOpStatus_u8  = DCM_INITIAL;
          Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
          dataRetWriteFunc_u8 = E_OK;
      }
   }
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Priv_DidWriteFuncAvailableCheck(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8){
VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
VAR(uint16,AUTOMATIC)  idxDidSignal_u16 = 0;
VAR(uint16,AUTOMATIC)  nrDidSignal_u16 = 0;
VAR(uint8,AUTOMATIC)   useDidPort_u8 = 0;
VAR(uint32,AUTOMATIC)  alloweWritedSession_u32 = 0;
P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc = NULL_PTR;
        nrDidSignal_u16 = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].nrSig_u16;
        useDidPort_u8 = Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].\
                        adrDidSignalConfig_pcst[idxDidSignal_u16].idxDcmDspDatainfo_u16].usePort_u8;
        alloweWritedSession_u32 = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].\
                                    adrExtendedConfig_pcst->dataAllowedSessWrite_u32;
        ptrWriteFnc = Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].\
                      adrDidSignalConfig_pcst[idxDidSignal_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrWriteFnc_cpv;
   for(idxDidSignal_u16 = 0x0; idxDidSignal_u16 < nrDidSignal_u16;
         idxDidSignal_u16++){
      if((useDidPort_u8 != USE_BLOCK_ID) && (alloweWritedSession_u32 > 0x00u) && (ptrWriteFnc == NULL_PTR)){
                    break;
            }
        }
   if(idxDidSignal_u16 == nrDidSignal_u16){
            dataRetVal_u8 =E_OK;
        }
        else{
            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            DCM_DET_ERROR(DCM_WDBI_ID , DCM_E_NO_WRITE_ACCESS )
        }
 return dataRetVal_u8;
}

static FUNC(void,DCM_CODE) Dcm_Lok_DidAvailableCheck(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8){
   VAR(Std_ReturnType,AUTOMATIC)   dataRetGetDID_u8 = E_NOT_OK;
    dataRetGetDID_u8 = Dcm_GetIndexOfDID(s_dataDID_u16, &s_Dcm_idxwdbiDidIndexType);
   if(dataRetGetDID_u8 == E_OK){
        dataRetGetDID_u8 = Dcm_Priv_DidWriteFuncAvailableCheck(dataNegRespCode_u8);
      if(dataRetGetDID_u8 == E_OK){
               Dcm_SrvOpstatus_u8 = DCM_CHECKDATA;
            }
   }
   else if(dataRetGetDID_u8 == DCM_E_PENDING){
        dataRetWriteFunc_u8 = DCM_E_PENDING;
   }
   else{
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
}

#define DCM_DSP_WDBI_MINREQLEN 0x03u

static FUNC(void,DCM_CODE) Dcm_Lok_WdbiStateProcessing(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
){
   if(Dcm_SrvOpstatus_u8 == DCM_INITIAL){
      if(pMsgContext->reqDataLen >= DCM_DSP_WDBI_MINREQLEN){
           s_dataDID_u16 = (uint16)(pMsgContext->reqData[0]);
           s_dataDID_u16 = s_dataDID_u16 <<8u;
           s_dataDID_u16 |= (uint16)(pMsgContext->reqData[1]);
            Dcm_Lok_DidAvailableCheck(dataNegRespCode_u8);
       }
       else{
           *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
       }
   }
   if(Dcm_SrvOpstatus_u8 == DCM_CHECKDATA){
      Dcm_Priv_DidWriteSupport(dataNegRespCode_u8, pMsgContext);
   }
   if(Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE){
           Dcm_Lok_WriteNormalDID(dataNegRespCode_u8,pMsgContext);
   }
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_WriteDIDServevice_status(
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
){
VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
   if((dataRetWriteFunc_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00)){
        pMsgContext->resData[0] = pMsgContext->reqData[0];
        pMsgContext->resData[1] = pMsgContext->reqData[1];
        pMsgContext->resDataLen = 0x02;
        Dcm_SrvOpstatus_u8  = DCM_INITIAL;
        Dcm_DidSignalIdx_u16 = 0x0;
        Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
        dataRetVal_u8=E_OK;
   }
   else if((dataRetWriteFunc_u8 == DCM_E_PENDING) || (dataRetWriteSupport_en == DCM_SUPPORT_CONDITION_PENDING)){
        Dcm_stDspWdbiOpStatus_u8 = DCM_PENDING;
        *dataNegRespCode_u8=0x00;
        dataRetVal_u8=DCM_E_PENDING;
   }
   else{
      if(*dataNegRespCode_u8 == 0x00){
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
        Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
        dataRetVal_u8=E_NOT_OK;
   }
   if(*dataNegRespCode_u8 != 0x0){
      dataRetVal_u8=E_NOT_OK;
      Dcm_SrvOpstatus_u8  = DCM_INITIAL;
      Dcm_DidSignalIdx_u16 = 0x0;
      Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
   }
return dataRetVal_u8;
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tWriteDataByIdentifier(
   VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,
   P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8){
   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8;
   s_loopbreak_b = FALSE;
    *dataNegRespCode_u8 = 0x0;
    dataRetWriteFunc_u8 = E_OK;
    dataRetWriteSupport_en = DCM_SUPPORT_OK;
    dataRetVal_u8 = E_NOT_OK;
   if(OpStatus == DCM_CANCEL){
        Dcm_Dcm_WDBIInit();
        dataRetVal_u8 = E_OK;
   }
   else{
        Dcm_Lok_WdbiStateProcessing(dataNegRespCode_u8,pMsgContext);
        dataRetVal_u8  =   Dcm_Lok_WriteDIDServevice_status(dataNegRespCode_u8,pMsgContext);
   }
        return dataRetVal_u8;
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveWDBIDid(
   P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16){
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    dataRetVal_u8 = E_NOT_OK;
   if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE){
        *dataDid_u16 = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataDid_u16;
        dataRetVal_u8 = E_OK;
   }
   else{
   }
    return (dataRetVal_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
