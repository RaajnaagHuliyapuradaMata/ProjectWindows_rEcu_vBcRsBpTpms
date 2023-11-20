

#ifndef DCMDSPUDS_UDS_PROT_H
#define DCMDSPUDS_UDS_PROT_H

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#if(RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED !=  DCM_CFG_OFF)

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveServiceTable(VAR(uint8,AUTOMATIC) Sid_tableid_u8);
#endif

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
extern FUNC(void,DCM_CODE) Dcm_ControlDtcSettingExit(void);
#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)          ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)         ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)   ||  \
     (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)                              ||  \
     (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
extern FUNC(void,DCM_CODE) Dcm_ResetDIDIndexstruct (P2VAR(Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st);
#endif

#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
extern FUNC (void,DCM_CODE) Dcm_ResetAsynchFlags(void);
#endif

#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
extern FUNC (void,DCM_CODE) Dcm_ResetAsynchSecaFlag(void);
#endif

#if((DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)||(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF ))
extern FUNC(void,DCM_CODE) Dcm_ConvBitsToBytes(P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA)DataLenInBits) ;
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_DSP_SID_ECURESET                           0x11u
#define DCM_DSP_SID_TESTERPRESENT                      0x3Eu
#define DCM_DSP_SID_SECURITYACCESS                     0x27u
#define DCM_DSP_SID_ROUTINECONTROL                     0x31u
#define DCM_DSP_SID_CONTROLDTCSETTING                  0x85u
#define DCM_DSP_SID_READDTCINFORMATION                 0x19u
#define DCM_DSP_SID_COMMUNICATIONCONTROL               0x28u
#define DCM_DSP_SID_READDATABYIDENTIFIER               0x22u
#define DCM_DSP_SID_WRITEDATABYIDENTIFIER              0x2Eu
#define DCM_DSP_SID_DIAGNOSTICSESSIONCONTROL           0x10u
#define DCM_DSP_SID_CLEARDIAGNOSTICINFORMATION         0x14u
#define DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER    0x2Cu
#define DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER     0x2Fu
#define DCM_DSP_SID_REQUESTDOWNLOAD                    0x34u
#define DCM_DSP_SID_REQUESTUPLOAD                      0x35u
#define DCM_DSP_SID_REQUESTTRANSFEREXIT                0x37u
#define DCM_MINSIZE                                    0x00u
#define DCM_MAXSIZE                                    0x04u

#define DSP_CONV_2U8_TO_U16(hi,lo)                     ((uint16)((uint16)(((uint16)(hi))<<(uint8)8u)| ((uint16)(lo))))

#define DSP_CONV_4U8_TO_U32(hihi, hilo, lohi, lolo)    ((uint32)((((uint32)(hihi))<<24u)| (((uint32)(hilo))<<16u)| \
                                                (((uint32)(lohi))<<8u) | ((uint32)(lolo))))

#define DSP_GET_MSBU16_TO_U8(var)                     ((uint8)(((uint16)(var))>>8u))

#define DSP_GET_LSBU16_TO_U8(var)                     ((uint8)(var))

#define DSP_CONV_2U16_TO_U32(hi,lo)                    ((uint32)((((uint32)(hi))<<16u)| ((uint32)(lo))))

#define DSP_GET_BYTE3U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>24u))

#define DSP_GET_BYTE2U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>16u))

#define DSP_GET_BYTE1U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>8u))

#define DSP_GET_BYTE0U32_TO_U8(var)                   ((uint8)(var))

#define DSP_GET_MSWU32_TO_U16(var)                    ((uint16)(((uint32)(var))>>16u))

#define DSP_GET_LSWU32_TO_U16(var)                    ((uint16)(var))

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) ||((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0)) || \
    (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

#define DCM_INFRASTRUCTURE_ERROR 0x80u
#endif

#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))

#define DCM_VIN_DATALEN  17

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint8,DCM_VAR) Dcm_VInData_au8[DCM_VIN_DATALEN];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern boolean Dcm_VinReceived_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#endif

typedef enum{
    DCM_ROE_CLEARED=0
   ,   DCM_ROE_STOPPED
   ,   DCM_ROE_STARTED
}Dcm_DspRoeEventState_ten;

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
typedef struct{
   P2FUNC(Std_ReturnType,TYPEDEF,ROEDID_fp)    (VAR(Dcm_DspRoeEventState_ten,AUTOMATIC));
   uint16 RoeEventDid_u16;
   uint8 RoeEventId_u8;
}DcmDspRoeDidEvents_tst;

typedef struct{

   boolean Is_PreConfigured_b;
   boolean stDspRoeCtrlStorageState_b;
   boolean stDspRoeStorageState_b;
   boolean stDspRoeSessionIsDefault_b;
   uint8 stRoeEventWindowTime_u8;
    Dcm_DspRoeEventState_ten RoeEventStatus;
   uint16 SourceAddress_u16;
   uint16 stRoeEventRecord_u16;
   uint16 stSrvToRespDid_u16;
}DcmDspRoeDidStateVariables_tst;

#endif

#endif
typedef struct{
   P2FUNC(Std_ReturnType,TYPEDEF,ROEDTC_fp)    (VAR(Dcm_DspRoeEventState_ten,AUTOMATIC));
   uint8 RoeEventId_u8;
}DcmDspRoeOnDtcStatusChg_tst;

typedef struct{
   boolean Is_PreConfigured_b;
   boolean stDspRoeStorageState_b;
   boolean stDspRoeCtrlStorageState_b;
   boolean stDspRoeSessionIsDefault_b;
    Dcm_DspRoeEventState_ten RoeEventStatus;
   uint8 testerReqDTCStatusMask_u8;
   uint8 stRoeEventWindowTime_u8;
   uint16 SourceAddress_u16;
}DcmDspRoeDtcStateVariable_tst;

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED!=DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE)Dcm_ResetRoeOnDtcevents(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

#define DCM_INVALID_NVDBLOCK    0u

#define USE_BLOCK_ID                                0x00u
#define USE_DATA_ASYNCH_CLIENT_SERVER               0x01u
#define USE_DATA_SENDER_RECEIVER                    0x02u
#define USE_DATA_SENDER_RECEIVER_AS_SERVICE         0x03u
#define USE_DATA_SYNCH_CLIENT_SERVER                0x04u
#define USE_ECU_SIGNAL                              0x05u
#define USE_DATA_SYNCH_FNC                          0x06u
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
#define USE_DATA_RDBI_PAGED_FNC                     0x07u
#endif
#define USE_DATA_ASYNCH_FNC                         0x08u

typedef enum{
    DCM_CONTROLMASK_NO=0
   ,   DCM_CONTROLMASK_INTERNAL
   ,   DCM_CONTROLMASK_EXTERNAL
}Dcm_Dsp_IocbiCtrlMask_ten;

typedef struct{
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
  uint32 dataAllowedSessRead_u32;
  uint32 dataAllowedSecRead_u32;
  P2FUNC(Std_ReturnType,TYPEDEF,adrUserReadModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint16,AUTOMATIC),VAR(Dcm_Direction_t,AUTOMATIC));
#if(DCM_CFG_DSP_MODERULEFORDIDREAD != DCM_CFG_OFF )
  P2FUNC(boolean,TYPEDEF,adrRdbiModeRuleChkFnc_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8);
#endif
#endif
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
  uint32 dataAllowedSessWrite_u32;
  uint32 dataAllowedSecWrite_u32;
  P2FUNC(Std_ReturnType,TYPEDEF,adrUserWriteModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint16,AUTOMATIC),VAR(Dcm_Direction_t,AUTOMATIC));
#if(DCM_CFG_DSP_MODERULEFORDIDWRITE != DCM_CFG_OFF )
  P2FUNC(boolean,TYPEDEF,adrWdbiModeRuleChkFnc_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8);
#endif
#endif
#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
  uint32  dataSessBitMask_u32;
  uint32  dataSecBitMask_u32;
  P2FUNC(Std_ReturnType,TYPEDEF,adrUserControlModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint16,AUTOMATIC),VAR(Dcm_Direction_t,AUTOMATIC));
#if(DCM_CFG_DSP_MODERULEFORDIDCONTROL != DCM_CFG_OFF )
  P2FUNC(boolean,TYPEDEF,adrIocbiModeRuleChkFnc_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8);
#endif
  Dcm_Dsp_IocbiCtrlMask_ten dataCtrlMask_en;
  uint8     dataCtrlMaskSize_u8;
  boolean dataIocbirst_b;
  uint8   statusmaskIOControl_u8;
#endif
}Dcm_ExtendedDIDConfig_tst;

#if((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
typedef struct{
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
  void* const ioControlRequest_cpv;
#endif
  void* const adrReturnControlEcu_cpv;
  void* const adrResetToDefault_cpv;
  void* const adrFreezeCurrentState_cpv;
  void* const adrShortTermAdjustment_cpv;
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrResetToDefaultResults_cpv;
  void* const adrFreezeCurrentStateResults_cpv;
  void* const adrShortTermAdjustmentResults_cpv;
#endif
}Dcm_SignalDIDIocbiConfig_tst;
#endif
typedef struct{
  void* const adrCondChkRdFnc_cpv;

  void* const adrReadDataLengthFnc_pfct;
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrCondChkRdFncResults_cpv;
 void* const adrReadDataLengthFncResults_pfct;
#endif
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
  void* const adrWriteFnc_cpv;
#if(DCM_CFG_DSP_WRITE_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrWriteFncResults_cpv;
#endif
#endif
#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
  VAR(uint16,AUTOMATIC) idxDcmDspIocbiInfo_u16;
#endif
}Dcm_SignalDIDSubStructConfig_tst;

typedef struct{
  void* const adrReadFnc_cpv;
#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrReadFncResults_cpv;
#endif
  uint16 dataSize_u16;
  uint16 dataNvmBlockId_u16;
  uint16 idxDcmDspControlInfo_u16;
  uint8 dataType_u8;
  uint8 usePort_u8;
  uint8 dataEndianness_u8;
  boolean dataFixedLength_b;
#if(DCM_CFG_DSP_DATA_ASYNCHCS_ENABLED != DCM_CFG_OFF)
  boolean UseAsynchronousServerCallPoint_b;
#endif
}Dcm_DataInfoConfig_tst;

typedef struct{
  uint16 posnSigBit_u16;
  uint16 idxDcmDspDatainfo_u16;
}Dcm_SignalDIDConfig_tst;
#if(DCM_CFG_DSP_NUMISDIDAVAIL > 0)
typedef P2FUNC(Std_ReturnType,TYPEDEF,IsDIDAvailFnc_pf) (VAR(uint16,AUTOMATIC) DID_u16);
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern CONST (IsDIDAvailFnc_pf,DCM_CONST) Dcm_DIDIsAvail[DCM_CFG_DSP_NUMISDIDAVAIL];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

typedef struct{
  uint16 dataDid_u16;
  uint16 nrSig_u16;
  uint16 dataMaxDidLen_u16;
  boolean dataFixedLength_b;
  boolean dataDynamicDid_b;
  P2CONST(Dcm_SignalDIDConfig_tst, DCM_VAR, DCM_INTERN_CONST) adrDidSignalConfig_pcst;
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
  uint8 dataConfigMask_u8;
#endif
#if(DCM_CFG_DSP_NUMISDIDAVAIL > 0)
uint16      idxDIDSupportedFnc_u16;
#endif
  P2CONST(Dcm_ExtendedDIDConfig_tst, DCM_VAR, DCM_INTERN_CONST) adrExtendedConfig_pcst;
}Dcm_DIDConfig_tst;

typedef struct{
  P2FUNC(Std_ReturnType,TYPEDEF,adrDIDAvailableFnc_pfct)( VAR(uint16,AUTOMATIC) DID, VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_DidSupportedType,AUTOMATIC,DCM_INTERN_DATA) supported);
  P2FUNC(Std_ReturnType,TYPEDEF,adrReadFnc_pfct)( VAR(uint16,AUTOMATIC) DID
   ,     CONSTP2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     CONSTP2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) DataLength
   ,     CONSTP2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                            );

  void* const adrReadDataLengthFnc_pfct;
  void* const adrWriteFnc_pfct;
  P2CONST(Dcm_ExtendedDIDConfig_tst, DCM_VAR, DCM_INTERN_CONST) adrExtendedConfig_pcst;
  uint16 nrDidRangeUpperLimit_u16;
  uint16 nrDidRangeLowerLimit_u16;
  uint16 dataMaxDidLen_u16;
  boolean dataRangeHasGaps_b;
  boolean nrRangeUsePort_b;
}Dcm_DIDRangeConfig_tst;

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadDataLengthFnc1_pf) (P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) DataLength);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadDataLengthFnc4_pf) (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) DataLength);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadDataLengthFnc2_pf) (P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) DataLength);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReaddatalengthFnc3_pf)( VAR(uint16,AUTOMATIC) DID,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) DataLength);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReaddatalengthFnc5_pf)(void);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadDataLengthFnc6_pf) (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);

typedef P2FUNC(Std_ReturnType,TYPEDEF,CondChkReadFunc1_pfct)
                                   (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF,CondChkReadFunc2_pfct)
                                   (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF,CondChkReadFunc3_pfct)
                                   (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc1_pfct)(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc10_pfct)(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc2_ptr)(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc3_pfct)(P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc4_pfct)(P2VAR(uint16, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc5_pfct)(P2VAR(uint32, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc6_pfct)(P2VAR(sint8,  AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc7_pfct)(P2VAR(sint16, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc8_pfct)(P2VAR(sint32, AUTOMATIC,DCM_INTERN_DATA) Data);

#if(DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc11_ptr)(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
#endif

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc9_ptr)(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,     \
                                                     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,   \
                                                     P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) BufSize,   \
                                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveRDBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveWDBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveIOCBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_RdpiIsDidCondtionChkReadSupported(P2VAR(Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveDDDid(P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(uint16,DCM_CODE) Dcm_DIDcalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern CONST(Dcm_DIDConfig_tst, DCM_CONST) Dcm_DIDConfig [];
extern CONST(Dcm_DataInfoConfig_tst, DCM_CONST)  Dcm_DspDataInfo_st[];
extern CONST(Dcm_SignalDIDSubStructConfig_tst, DCM_CONST)  Dcm_DspDid_ControlInfo_st[];
#if((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
extern CONST(Dcm_SignalDIDIocbiConfig_tst, DCM_CONST)  Dcm_DspIOControlInfo[];
#endif
extern CONST (Dcm_DIDRangeConfig_tst, DCM_CONST) Dcm_DIDRangeConfig_cast[];
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
extern CONST(DcmDspRoeDidEvents_tst, DCM_CONST) DcmDspRoeDidEvents[DCM_MAX_DIDROEEVENTS];
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
extern CONST(DcmDspRoeOnDtcStatusChg_tst,DCM_CONST) DcmDspRoeDtcEvent;
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
extern VAR(DcmDspRoeDidStateVariables_tst, DCM_VAR) DcmDspRoeDidStateVariables[DCM_MAX_DIDROEEVENTS];
#endif
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) &&  (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
extern VAR(DcmDspRoeDtcStateVariable_tst, DCM_VAR) DcmDspRoeDtcStateVariable;
#endif
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern VAR (uint16,DCM_VAR) Dcm_DidSignalIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern VAR (boolean   ,DCM_VAR) Dcm_flgDspDidRangePending_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

extern VAR(boolean ,DCM_VAR) Dcm_PeriodicSchedulerRunning_b;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif

#if((DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_ResetRoeDidevents(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

extern VAR (uint8,DCM_VAR) Dcm_RoeDidIdx_u8;

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#if(( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ) && (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC (void,DCM_CODE) Dcm_Dsp_SecaClearSeed (void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_ResetAccessType (void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(Std_ReturnType ,DCM_CODE)  Dcm_VinBuffer_Init(void);
extern FUNC(Std_ReturnType ,DCM_CODE)  Dcm_ReadVinBuffer(P2VAR(uint8, AUTOMATIC, DCM_VAR) Data);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

