#ifndef DCMAPPL_H
#define DCMAPPL_H

#include "DcmDspUds_Cdtcs_Inf.hpp"

#define DCMAPPL_SUPPRESS_NRC(NegRespCode) (0u)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmNotification (
      VAR(uint8,AUTOMATIC) SID
   ,     CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData
   ,     VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC) RequestLength
   ,     VAR(uint8,AUTOMATIC) RequestType
   ,     VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) DcmRxPduId
   ,     VAR(uint16,AUTOMATIC) SourceAddress
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
);
#endif

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmGetNRCForMinLengthCheck(
   	                                       VAR(Dcm_ProtocolType,AUTOMATIC) dataProtocolId_u8
   ,                                         VAR(uint8,AUTOMATIC) dataSid_u8
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataErrorCode_u8
);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation(
   VAR(Dcm_IdContextType,AUTOMATIC) idContext
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) dcmRxPduId
   ,  VAR(uint16,AUTOMATIC) SourceAddress
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
);

extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_ConfirmationRespPend(
   VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
);

FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation_GeneralReject(
   VAR(Dcm_IdContextType,AUTOMATIC) idContext
   ,     VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) dcmRxPduId
   ,     VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
);

extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetRxPermission (VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolId
   ,  VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) info
   ,  VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength
);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmComModeError (VAR(uint8,AUTOMATIC) NetworkId);

#if((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)\
   	|| (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetPermissionForMemoryAccess_u8(VAR(uint32,  AUTOMATIC) adrMemoryAddress_u32
   ,    VAR(uint32,  AUTOMATIC) dataDataLength_u32
   ,    VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en);
#endif

#if((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) 			||	\
   (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)    ||  \
   (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)           || \
   (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
extern FUNC(Dcm_ReturnReadMemoryType,DCM_APPL_CODE) DcmAppl_Dcm_ReadMemory(VAR(Dcm_OpStatusType,  AUTOMATIC) Rmba_Opstatus
   ,    VAR(uint8,  AUTOMATIC) memoryid
   ,    VAR(uint32,  AUTOMATIC) memoryaddress
   ,    VAR(uint32,  AUTOMATIC) datalength
   ,    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) respbuf
   ,    P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmCheckWDBIReqLen(VAR(uint16,AUTOMATIC) nrDID_u16, VAR(uint32,AUTOMATIC) dataReqLen_u32);
#endif

#if((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
extern FUNC(Dcm_ReturnWriteMemoryType,DCM_APPL_CODE) DcmAppl_Dcm_WriteMemory(VAR(Dcm_OpStatusType,  AUTOMATIC) Wmba_Opstatus
   ,  VAR(uint8,  AUTOMATIC) memoryid
   ,  VAR(uint32,  AUTOMATIC) memoryaddress
   ,  VAR(uint32,  AUTOMATIC) datalength
   ,  P2CONST (uint8,AUTOMATIC,DCM_INTERN_DATA) reqbuf
   ,  P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
extern FUNC (void, DCM_APPL_CODE) DcmAppl_DisableDTCSetting (
                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
);
extern FUNC (void, DCM_APPL_CODE) DcmAppl_DcmControlDtcSettingEnableStatus(
   	VAR(boolean,AUTOMATIC) ControlDtcSettingEnableStatus
);

extern FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckCDTCRecord (
                                    P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlOptionRecord
   ,     VAR(uint8,AUTOMATIC) Length
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
);
#endif

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )
extern FUNC (void, DCM_APPL_CODE) DcmAppl_DcmSwitchCommunicationControl( VAR(uint8,DCM_VAR) NetworkID ,Dcm_CommunicationModeType RequestedMode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE)  DcmAppl_DcmCommControlConditionCheck(VAR(uint8,AUTOMATIC) ControlType_u8
   ,     VAR(uint8,AUTOMATIC) DataCommType_u8
   ,     P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) RequestData
   ,     VAR(uint16,AUTOMATIC) RequestLength
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8 );
#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
extern FUNC (boolean, DCM_APPL_CODE) DcmAppl_DcmIsComModeDefault( VAR(uint8,DCM_VAR) NetworkID );
#endif
#endif

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetPermTxWarmResp(void);
extern FUNC(Dcm_EcuStartModeType,DCM_APPL_CODE) Dcm_GetProgConditions
   (P2VAR(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions
);
#endif

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
extern FUNC(uint8,DCM_APPL_CODE) DcmAppl_DcmGetStoreType(VAR(uint8, AUTOMATIC) dataBootType_u8,VAR(uint8, AUTOMATIC) SID);

extern FUNC(Std_ReturnType,DCM_APPL_CODE) Dcm_SetProgConditions(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2CONST(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions);
#endif

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF ) )
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetSesChgPermission(
      VAR(Dcm_SesCtrlType,AUTOMATIC) SesCtrlTypeActive
   ,  VAR(Dcm_SesCtrlType,AUTOMATIC) SesCtrlTypeNew
   ,  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
);
#endif

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) )
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmEcuResetPreparation(
      VAR(uint8,AUTOMATIC) ResetType
   ,  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
);

#endif

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )
#define DCMAPPL_NUMATTGETSEED   0x05
extern FUNC(uint32,DCM_APPL_CODE) DcmAppl_DcmGetUpdatedDelayTime(
   VAR(uint8,AUTOMATIC) SecurityLevel
   ,  VAR(uint8,AUTOMATIC) Delaycount
   ,  VAR(uint32,AUTOMATIC) DelayTime
);

extern FUNC(uint32,DCM_APPL_CODE) DcmAppl_DcmGetUpdatedDelayForPowerOn(
   VAR(uint8,AUTOMATIC) SecurityLevel
   ,  VAR(uint8,AUTOMATIC) Delaycount
   ,  VAR(uint32,AUTOMATIC) DelayTime
);

extern FUNC(Dcm_StatusType,DCM_APPL_CODE) DcmAppl_DcmCheckSeed(
   VAR(uint32,AUTOMATIC) SeedLen
   ,  P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) Seed
);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmSecurityLevelLocked(VAR(uint8,AUTOMATIC) SecTabIdx);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmSecaInvalidKey(VAR(uint8,AUTOMATIC) SecTabIdx);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmSecaValidKey(VAR(uint8,AUTOMATIC) SecTabIdx);
#endif

extern FUNC(void, DCM_APPL_CODE) DcmAppl_DcmModifyResponse (
   								VAR(uint8,AUTOMATIC) dataSid_u8
   ,  VAR(uint8,AUTOMATIC) dataNRC_u8
   ,  P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrBufPtr_pu8
   ,  P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) nrBufSize_pu32
);
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckRoutineControlOptionRecord(VAR(uint16,AUTOMATIC) nrRID_u16
   ,     VAR(uint8,AUTOMATIC) dataSubFunc_u8,P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) adrRoutineCtrlOptRec_pcst,VAR(uint16,AUTOMATIC) dataRoutineCtrlOptRecSize_u16);
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED!= DCM_CFG_OFF)))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_CheckEncryptionCompressionMethod(
        VAR(uint8,AUTOMATIC) Sid_u8
   ,     VAR(uint8,AUTOMATIC) CompressionMethod
   ,     VAR(uint8,AUTOMATIC) EncryptionMethod );
#endif

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestDownload(
        VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) DataFormatIdentifier
   ,     VAR(uint32,AUTOMATIC) MemoryAddress
   ,     VAR(uint32,AUTOMATIC) MemorySize
   ,     P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) BlockLength
   ,     P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode);
#endif

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestTransferExit(
        VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2CONST(uint8,DCM_INTERN_DATA,AUTOMATIC) transferRequestParameterRecord
   ,     VAR(uint32,AUTOMATIC) transferRequestParameterRecordSize
   ,     P2VAR(uint8,DCM_INTERN_DATA,AUTOMATIC) transferResponseParameterRecord
   ,     P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) transferResponseParameterRecordSize
   ,     P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode);
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_CheckPermissionForTransferData(
                                                    VAR(uint8,AUTOMATIC) BlockSequenceCounter
   ,     VAR(uint8,AUTOMATIC) memoryId
   ,     VAR(uint32,AUTOMATIC) memoryAddress
   ,     P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) memorySize
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) TransferRequestParameterRecord
   ,     VAR(uint32,AUTOMATIC) TransferRequestParameterRecordLength
   ,     VAR(Dcm_TrasferDirection_en,AUTOMATIC) dataTransferDirection_ten
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
);
extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmMemSizeCheckForTransferData    (
                                                    VAR(uint8,AUTOMATIC) dataCompressionMethod_u8
   ,     VAR(uint8,AUTOMATIC) dataMemoryId_u8
   ,     VAR(uint32,AUTOMATIC) dataTransferRequestParameterRecordLength_u32
   ,     VAR(Dcm_TrasferDirection_en, AUTOMATIC) dataTransferDirection_ten
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataErrorCode_u8
);
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmCheckRdbiResponseLength(
                                                    VAR(uint32,AUTOMATIC) dataTotalRespLength_u32
   ,     VAR(uint16,AUTOMATIC) dataNumOfDids_u16
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_APPL_DATA) ErrorCode
);
#endif

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
extern FUNC(void,DCM_APPL_CODE) DcmAppl_CopyRxData(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) RxBufferSize
);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_TpRxIndication( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId
   ,     VAR(Std_ReturnType, AUTOMATIC) Result);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
