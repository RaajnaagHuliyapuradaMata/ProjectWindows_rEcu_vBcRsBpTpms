

#ifndef DCMDSPUDS_UDS_PROT_H
#define DCMDSPUDS_UDS_PROT_H

#define  DCM_DSP_SID_ROUTINECONTROL                     0x31u
#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
extern void Dcm_ControlDtcSettingExit(void);
#endif

#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)          ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)         ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)   ||  \
     (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)                              ||  \
     (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
extern void Dcm_ResetDIDIndexstruct (Dcm_DIDIndexType_tst * idxDidIndexType_st);
#endif

#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF )
Std_ReturnType Dcm_Lok_GetIndexOfDID (
                                                uint16 did,
                                                Dcm_DIDIndexType_tst * idxDidIndexType_st
                                                  );
#endif

#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
extern void Dcm_ResetAsynchFlags(void);
#endif

#if (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
extern void Dcm_ResetAsynchSecaFlag(void);
#endif
#endif

#if ((DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)||(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF ))
extern void Dcm_ConvBitsToBytes(uint32 * DataLenInBits) ;
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define  DCM_DSP_SID_ECURESET                           0x11u
#define  DCM_DSP_SID_TESTERPRESENT                      0x3Eu
#define  DCM_DSP_SID_SECURITYACCESS                     0x27u
#define  DCM_DSP_SID_CONTROLDTCSETTING                  0x85u
#define  DCM_DSP_SID_READDTCINFORMATION                 0x19u
#define  DCM_DSP_SID_COMMUNICATIONCONTROL               0x28u
#define  DCM_DSP_SID_READDATABYIDENTIFIER               0x22u
#define  DCM_DSP_SID_WRITEDATABYIDENTIFIER              0x2Eu
#define  DCM_DSP_SID_DIAGNOSTICSESSIONCONTROL           0x10u
#define  DCM_DSP_SID_CLEARDIAGNOSTICINFORMATION         0x14u
#define  DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER    0x2Cu
#define  DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER     0x2Fu
#define  DCM_DSP_SID_REQUESTDOWNLOAD                    0x34u
#define  DCM_DSP_SID_REQUESTUPLOAD                      0x35u
#define  DCM_DSP_SID_REQUESTTRANSFEREXIT                0x37u
#define  DCM_MINSIZE                                    0x00u
#define  DCM_MAXSIZE                                    0x04u
#define  DCM_IOCBI_INIT                                 0xFFu
#define  DCM_VALUE_NULL                                 0x00u

# define DSP_CONV_2U8_TO_U16(hi,lo)                     ((uint16)((uint16)(((uint16)(hi))<<(uint8)8u)| ((uint16)(lo))))

# define DSP_CONV_4U8_TO_U32(hihi, hilo, lohi, lolo)    ((uint32)((((uint32)(hihi))<<24u)| (((uint32)(hilo))<<16u)| \
                                                (((uint32)(lohi))<<8u) | ((uint32)(lolo))))

# define DSP_GET_MSBU16_TO_U8(var)                     ((uint8)(((uint16)(var))>>8u))

# define DSP_GET_LSBU16_TO_U8(var)                     ((uint8)(var))

# define DSP_CONV_2U16_TO_U32(hi,lo)                    ((uint32)((((uint32)(hi))<<16u)| ((uint32)(lo))))

# define DSP_GET_BYTE3U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>24u))

# define DSP_GET_BYTE2U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>16u))

# define DSP_GET_BYTE1U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>8u))

# define DSP_GET_BYTE0U32_TO_U8(var)                   ((uint8)(var))

# define DSP_GET_MSWU32_TO_U16(var)                    ((uint16)(((uint32)(var))>>16u))

# define DSP_GET_LSWU32_TO_U16(var)                    ((uint16)(var))

#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) ||((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0)) || \
    (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

#define DCM_INFRASTRUCTURE_ERROR 0x80u
#endif

#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))

#define DCM_VIN_DATALEN  17

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern uint8 Dcm_VInData_au8[DCM_VIN_DATALEN];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
extern boolean Dcm_VinReceived_b;
extern boolean Dcm_GetvinConditionCheckRead;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"

#endif

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

#if(DCM_CFG_ATOMICREAD_DID>0)
extern uint16 Dcm_Lok_AtomicReadDid_index(uint16 DID);
#endif

#if(DCM_CFG_ATOMICWRITE_DID>0)
extern uint16 Dcm_Lok_AtomicWriteDid_index(uint16 DID);
#endif

#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

#if(DCM_CFG_ATOMICREAD_DID>0)
typedef struct{
    uint16 dataDid_u16;
    Std_ReturnType (*AtomicRead_pfct)(void* AtomicRead_struct);
    void (*AtomicRead_CopyData_pfct)(uint8* targetBuffer);
}AtomicRead_st;
#endif

#if(DCM_CFG_ATOMICWRITE_DID>0)
typedef struct{
    uint16 dataDid_u16;
    Std_ReturnType (*AtomicWrite_pfct)(void* AtomicWrite_struct);
void (*AtomicWrite_CopyData_pfct)(uint8* requestBuffer);
}AtomicWrite_st;
#endif

typedef enum
{
    DCM_ROE_CLEARED=0,
    DCM_ROE_STOPPED,
    DCM_ROE_STARTED
}Dcm_DspRoeEventState_ten;

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
typedef struct{
    Std_ReturnType (*ROEDID_fp) (Dcm_DspRoeEventState_ten RoeEventStatus );
    uint16 RoeEventDid_u16;
    uint8 RoeEventId_u8;
} DcmDspRoeDidEvents_tst;

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
	Std_ReturnType (*ROEDTC_fp) (Dcm_DspRoeEventState_ten RoeEventStatus );
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

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED!=DCM_CFG_OFF)
extern void Dcm_ResetRoeOnDtcevents(void);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

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

#define USE_ATOMIC_NV_DATA_INTERFACE                        0x09u
#define USE_ATOMIC_SENDER_RECEIVER_INTERFACE                0x0Au
#define USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE     0x0Bu
#define USE_DATA_ELEMENT_SPECIFIC_INTERFACES                0x0Cu

typedef enum
{
    DCM_CONTROLMASK_NO=0,
    DCM_CONTROLMASK_INTERNAL,
    DCM_CONTROLMASK_EXTERNAL
}Dcm_Dsp_IocbiCtrlMask_ten;

typedef struct{
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
  uint32 dataAllowedSessRead_u32;
  uint32 dataAllowedSecRead_u32;
  Std_ReturnType (*adrUserReadModeRule_pfct) (Dcm_NegativeResponseCodeType *dataNrc ,uint16 dataDid_u16,Dcm_Direction_t Dcm_Support_Read );
#if(DCM_CFG_DSP_MODERULEFORDIDREAD != DCM_CFG_OFF )
  boolean (*adrRdbiModeRuleChkFnc_pfct) (Dcm_NegativeResponseCodeType * Nrc_u8);
#endif
#endif
#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
  uint32 dataAllowedSessWrite_u32;
  uint32 dataAllowedSecWrite_u32;
  Std_ReturnType (*adrUserWriteModeRule_pfct) (Dcm_NegativeResponseCodeType *dataNrc ,uint16 dataDid_u16 ,Dcm_Direction_t Dcm_Support_Write);
#if(DCM_CFG_DSP_MODERULEFORDIDWRITE != DCM_CFG_OFF )
  boolean (*adrWdbiModeRuleChkFnc_pfct) (Dcm_NegativeResponseCodeType * Nrc_u8);
#endif
#endif
#if (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
  uint32  dataSessBitMask_u32;
  uint32  dataSecBitMask_u32;
  Std_ReturnType (*adrUserControlModeRule_pfct) (Dcm_NegativeResponseCodeType *dataNrc ,uint16 dataDid_u16,Dcm_Direction_t Dcm_Support_IoControl);
#if(DCM_CFG_DSP_MODERULEFORDIDCONTROL != DCM_CFG_OFF )
  boolean (*adrIocbiModeRuleChkFnc_pfct) (Dcm_NegativeResponseCodeType * Nrc_u8);
#endif
  Dcm_Dsp_IocbiCtrlMask_ten dataCtrlMask_en;
  uint8     dataCtrlMaskSize_u8;
  boolean dataIocbirst_b;
  uint8   statusmaskIOControl_u8;
#endif
} Dcm_ExtendedDIDConfig_tst;

#if ((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
typedef struct{
  void* const ioControlRequest_cpv;
  void* const adrReturnControlEcu_cpv;
  void* const adrResetToDefault_cpv;
  void* const adrFreezeCurrentState_cpv;
  void* const adrShortTermAdjustment_cpv;
#if (DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrResetToDefaultResults_cpv;
  void* const adrFreezeCurrentStateResults_cpv;
  void* const adrShortTermAdjustmentResults_cpv;
#endif
}Dcm_SignalDIDIocbiConfig_tst;
#endif
typedef struct{
  void* const adrCondChkRdFnc_cpv;

  void* const adrReadDataLengthFnc_pfct;
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrCondChkRdFncResults_cpv;
 void* const adrReadDataLengthFncResults_pfct;
#endif
#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
  void* const adrWriteFnc_cpv;
  void* const WriteDataTypeVar;
  void (*GetSignalData_pfct)(void* requestBuffer, uint16 position_u16);
#if (DCM_CFG_DSP_WRITE_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrWriteFncResults_cpv;
#endif
#endif
#if (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
  uint16 idxDcmDspIocbiInfo_u16;
#endif
}Dcm_SignalDIDSubStructConfig_tst;

typedef struct{
  void* const adrReadFnc_cpv;
  void* const ReadDataVar;
  Std_ReturnType (*StoreSignal_pfct)(void* targetBuffer, uint16 position);
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrReadFncResults_cpv;
#endif
  uint16 dataSize_u16;
#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
  uint16 dataNvmBlockId_u16;
#endif
  uint16 idxDcmDspControlInfo_u16;
  uint8 dataType_u8;
  uint8 usePort_u8;
#if( DCM_CFG_DSP_ALLSIGNAL_OPAQUE !=DCM_CFG_ON)
  uint8 dataEndianness_u8;
#endif
#if(DCM_CFG_DSP_ALLSIGNAL_FIXED_LENGTH!=DCM_CFG_ON)
  boolean dataFixedLength_b;
#endif
#if (DCM_CFG_DSP_DATA_ASYNCHCS_ENABLED != DCM_CFG_OFF)
  boolean UseAsynchronousServerCallPoint_b;
#endif
}Dcm_DataInfoConfig_tst;

typedef struct{
  uint16 posnSigBit_u16;
  uint16 idxDcmDspDatainfo_u16;
  Std_ReturnType (*ReadSenderReceiver_pfct)(void* ReadDataVar);
  Std_ReturnType (*WriteSenderReceiver_pfct)(void* WriteDataTypeVar);
} Dcm_SignalDIDConfig_tst;
#if(DCM_CFG_DSP_NUMISDIDAVAIL > 0)
typedef Std_ReturnType (*IsDIDAvailFnc_pf) (uint16 DID_u16);
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const IsDIDAvailFnc_pf Dcm_DIDIsAvail[DCM_CFG_DSP_NUMISDIDAVAIL];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

typedef struct{
  uint16 dataDid_u16;
  uint8 didUsePort_u8;
  boolean AtomicorNewSRCommunication_b;
  uint16 nrSig_u16;
  uint16 dataMaxDidLen_u16;
  boolean dataFixedLength_b;
  boolean dataDynamicDid_b;
  const Dcm_SignalDIDConfig_tst * adrDidSignalConfig_pcst;
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
  uint8 dataConfigMask_u8;
#endif
#if(DCM_CFG_DSP_NUMISDIDAVAIL > 0)
uint16      idxDIDSupportedFnc_u16;
#endif
   void* const ioControlRequest_cpv;
#if(DCM_CFG_ATOMICREAD_DID>0)
   void* const AtomicRead_var;
#endif
#if(DCM_CFG_ATOMICWRITE_DID>0)
   void* const AtomicWrite_var;
#endif
  const Dcm_ExtendedDIDConfig_tst * adrExtendedConfig_pcst;
} Dcm_DIDConfig_tst;

typedef struct{
  Std_ReturnType (*adrDIDAvailableFnc_pfct) ( uint16 DID, Dcm_OpStatusType OpStatus,
                                                       Dcm_DidSupportedType * supported);
  Std_ReturnType (*adrReadFnc_pfct) ( uint16 DID,
                                             uint8 * const Data,
                                             Dcm_OpStatusType OpStatus,
                                             uint16 * const DataLength,
                                             Dcm_NegativeResponseCodeType * const ErrorCode
                                            );

  void* const adrReadDataLengthFnc_pfct;
  void* const adrWriteFnc_pfct;
  const Dcm_ExtendedDIDConfig_tst * adrExtendedConfig_pcst;
  uint16 nrDidRangeUpperLimit_u16;
  uint16 nrDidRangeLowerLimit_u16;
  uint16 dataMaxDidLen_u16;
  boolean dataRangeHasGaps_b;
  boolean nrRangeUsePort_b;
} Dcm_DIDRangeConfig_tst;

typedef Std_ReturnType (*ReadDataLengthFnc1_pf) (uint16 * DataLength);

typedef Std_ReturnType (*ReadDataLengthFnc4_pf) (Dcm_OpStatusType OpStatus,uint16 * DataLength);

typedef Std_ReturnType (*ReadDataLengthFnc2_pf) (uint32 * DataLength);

typedef Std_ReturnType (*ReaddatalengthFnc3_pf) ( uint16 DID,Dcm_OpStatusType OpStatus,
                                                       uint16 * DataLength);

typedef Std_ReturnType (*ReaddatalengthFnc5_pf) (void);

typedef Std_ReturnType (*ReadDataLengthFnc6_pf) (Dcm_OpStatusType OpStatus);

typedef Std_ReturnType (*CondChkReadFunc1_pfct) (Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*CondChkReadFunc2_pfct) (Dcm_OpStatusType OpStatus,
                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*CondChkReadFunc3_pfct) (Dcm_OpStatusType OpStatus);

typedef Std_ReturnType (*ReadFunc1_pfct) (uint8 * Data);

typedef Std_ReturnType (*ReadFunc10_pfct) (uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ReadFunc2_ptr) (Dcm_OpStatusType OpStatus,
                                                     uint8 * Data);

typedef Std_ReturnType (*ReadFunc3_pfct) (boolean * Data);
typedef Std_ReturnType (*ReadFunc4_pfct) (uint16 * Data);
typedef Std_ReturnType (*ReadFunc5_pfct) (uint32 * Data);
typedef Std_ReturnType (*ReadFunc6_pfct) (sint8 * Data);
typedef Std_ReturnType (*ReadFunc7_pfct) (sint16 * Data);
typedef Std_ReturnType (*ReadFunc8_pfct) (sint32 * Data);

#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)

typedef Std_ReturnType (*ReadFunc11_ptr) (Dcm_OpStatusType OpStatus);
#endif

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

typedef Std_ReturnType (*ReadFunc9_ptr) (Dcm_OpStatusType OpStatus,      \
                                                     uint8 * Data,   \
                                                     uint32 * BufSize,   \
                                                     Dcm_NegativeResponseCodeType * ErrorCode);
#endif

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern Std_ReturnType Dcm_GetActiveRDBIDid(uint16 * dataDid_u16);
#endif
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern Std_ReturnType Dcm_GetActiveWDBIDid(uint16 * dataDid_u16);
#endif
#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
extern Std_ReturnType Dcm_GetActiveIOCBIDid(uint16 * dataDid_u16);
#endif
#if(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern Std_ReturnType Dcm_RdpiIsDidCondtionChkReadSupported(Dcm_DIDIndexType_tst * idxDidIndexType_st);
#endif
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern Std_ReturnType Dcm_GetActiveDDDid(uint16 * dataDid_u16);
#endif
extern uint16 Dcm_DIDcalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if(DCM_CFG_ATOMICREAD_DID>0)
extern const AtomicRead_st AtomicDidRead_cast[DCM_CFG_ATOMICREAD_DID];
#endif
#if(DCM_CFG_ATOMICWRITE_DID>0)
extern const AtomicWrite_st AtomicDidWrite_cast[DCM_CFG_ATOMICWRITE_DID];
#endif
extern const Dcm_DIDConfig_tst Dcm_DIDConfig [];
extern const Dcm_DataInfoConfig_tst Dcm_DspDataInfo_st[];
extern const Dcm_SignalDIDSubStructConfig_tst Dcm_DspDid_ControlInfo_st[];
#if ((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
extern const Dcm_SignalDIDIocbiConfig_tst Dcm_DspIOControlInfo[];
#endif
extern const Dcm_DIDRangeConfig_tst Dcm_DIDRangeConfig_cast[];
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
extern const DcmDspRoeDidEvents_tst DcmDspRoeDidEvents[DCM_MAX_DIDROEEVENTS];
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
extern const DcmDspRoeOnDtcStatusChg_tst DcmDspRoeDtcEvent;
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
extern DcmDspRoeDidStateVariables_tst DcmDspRoeDidStateVariables[DCM_MAX_DIDROEEVENTS];
#endif
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) &&  (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
extern DcmDspRoeDtcStateVariable_tst DcmDspRoeDtcStateVariable;
#endif
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
extern uint16 Dcm_DidSignalIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"

#if (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern Dcm_OpStatusType Dcm_DspDataOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
extern boolean Dcm_flgDspDidRangePending_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

extern boolean Dcm_PeriodicSchedulerRunning_b;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#endif

#if ((DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_ResetRoeDidevents(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

extern uint8 Dcm_RoeDidIdx_u8;

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#if(( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ) && (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_Dsp_SecaClearSeed (void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ))
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_ResetAccessType (void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern Std_ReturnType Dcm_VinBuffer_Init(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
typedef Std_ReturnType (*IOControlrequest_pfct) ( Dcm_InputOutputControlParameterType IoctrlParam,
                                        const uint8 * RequestData,
                                        uint16 dataSignalLength_u16,
                                        uint8 controlMaskLength_u8,
                                        Dcm_OpStatusType IocbiOpStatus_u8,
                                        Dcm_NegativeResponseCodeType * ErrorCode);
#endif
#endif
#endif

