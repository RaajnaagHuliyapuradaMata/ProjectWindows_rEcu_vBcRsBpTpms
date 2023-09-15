#ifndef DCMDSPUDS_UDS_PROT_H
#define DCMDSPUDS_UDS_PROT_H

#define DCM_DSP_SID_ROUTINECONTROL                     0x31u

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
extern void Dcm_ControlDtcSettingExit(void);
#endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)          ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)         ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)   ||  \
     (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)                              ||  \
     (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
extern void Dcm_ResetDIDIndexstruct (Dcm_DIDIndexType_tst * idxDidIndexType_st);
#endif

#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF )
Std_ReturnType Dcm_Lok_GetIndexOfDID(
      uint16                did
   ,  Dcm_DIDIndexType_tst* idxDidIndexType_st
);
#endif

#if((DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)||(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF ))
extern void Dcm_ConvBitsToBytes(uint32 * DataLenInBits) ;
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_DSP_SID_ECURESET                                               0x11u
#define DCM_DSP_SID_TESTERPRESENT                                          0x3Eu
#define DCM_DSP_SID_SECURITYACCESS                                         0x27u
#define DCM_DSP_SID_CONTROLDTCSETTING                                      0x85u
#define DCM_DSP_SID_READDTCINFORMATION                                     0x19u
#define DCM_DSP_SID_COMMUNICATIONCONTROL                                   0x28u
#define DCM_DSP_SID_READDATABYIDENTIFIER                                   0x22u
#define DCM_DSP_SID_WRITEDATABYIDENTIFIER                                  0x2Eu
#define DCM_DSP_SID_DIAGNOSTICSESSIONCONTROL                               0x10u
#define DCM_DSP_SID_CLEARDIAGNOSTICINFORMATION                             0x14u
#define DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER                        0x2Cu
#define DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER                         0x2Fu
#define DCM_DSP_SID_REQUESTDOWNLOAD                                        0x34u
#define DCM_DSP_SID_REQUESTUPLOAD                                          0x35u
#define DCM_DSP_SID_REQUESTTRANSFEREXIT                                    0x37u
#define DCM_MINSIZE                                                        0x00u
#define DCM_MAXSIZE                                                        0x04u
#define DCM_IOCBI_INIT                                                     0xFFu
#define DCM_VALUE_NULL                                                     0x00u
#define DSP_CONV_2U8_TO_U16(hi,lo)                  ((uint16)((uint16)(((uint16)(hi))<<(uint8)8u)| ((uint16)(lo))))
#define DSP_CONV_4U8_TO_U32(hihi, hilo, lohi, lolo) ((uint32)((((uint32)(hihi))<<24u)| (((uint32)(hilo))<<16u)| (((uint32)(lohi))<<8u) | ((uint32)(lolo))))
#define DSP_GET_MSBU16_TO_U8(var)                   ((uint8)(((uint16)(var))>>8u))
#define DSP_GET_LSBU16_TO_U8(var)                   ((uint8)(var))
#define DSP_CONV_2U16_TO_U32(hi,lo)                 ((uint32)((((uint32)(hi))<<16u)| ((uint32)(lo))))
#define DSP_GET_BYTE3U32_TO_U8(var)                 ((uint8)(((uint32)(var))>>24u))
#define DSP_GET_BYTE2U32_TO_U8(var)                 ((uint8)(((uint32)(var))>>16u))
#define DSP_GET_BYTE1U32_TO_U8(var)                 ((uint8)(((uint32)(var))>>8u))
#define DSP_GET_BYTE0U32_TO_U8(var)                 ((uint8)(var))
#define DSP_GET_MSWU32_TO_U16(var)                  ((uint16)(((uint32)(var))>>16u))
#define DSP_GET_LSWU32_TO_U16(var)                  ((uint16)(var))

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) ||((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0)) || \
    (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
#define DCM_INFRASTRUCTURE_ERROR 0x80u
#endif

#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
#define DCM_VIN_DATALEN                                                       17

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern uint8 Dcm_VInData_au8[DCM_VIN_DATALEN];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern boolean Dcm_VinReceived_b;
extern boolean Dcm_GetvinConditionCheckRead;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#endif

typedef enum{
       DCM_ROE_CLEARED
   ,   DCM_ROE_STOPPED
   ,   DCM_ROE_STARTED
}Dcm_DspRoeEventState_ten;

typedef struct{
   Std_ReturnType (*ROEDTC_fp) (Dcm_DspRoeEventState_ten RoeEventStatus);
   uint8 RoeEventId_u8;
}DcmDspRoeOnDtcStatusChg_tst;

typedef struct{
   boolean                  Is_PreConfigured_b;
   boolean                  stDspRoeStorageState_b;
   boolean                  stDspRoeCtrlStorageState_b;
   boolean                  stDspRoeSessionIsDefault_b;
   Dcm_DspRoeEventState_ten RoeEventStatus;
   uint8                    testerReqDTCStatusMask_u8;
   uint8                    stRoeEventWindowTime_u8;
   uint16                   SourceAddress_u16;
}DcmDspRoeDtcStateVariable_tst;

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
#define DCM_INVALID_NVDBLOCK                                                  0u
#define USE_BLOCK_ID                                                       0x00u
#define USE_DATA_ASYNCH_CLIENT_SERVER                                      0x01u
#define USE_DATA_SENDER_RECEIVER                                           0x02u
#define USE_DATA_SENDER_RECEIVER_AS_SERVICE                                0x03u
#define USE_DATA_SYNCH_CLIENT_SERVER                                       0x04u
#define USE_ECU_SIGNAL                                                     0x05u
#define USE_DATA_SYNCH_FNC                                                 0x06u
#define USE_DATA_ASYNCH_FNC                                                0x08u
#define USE_ATOMIC_NV_DATA_INTERFACE                                       0x09u
#define USE_ATOMIC_SENDER_RECEIVER_INTERFACE                               0x0Au
#define USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE                    0x0Bu
#define USE_DATA_ELEMENT_SPECIFIC_INTERFACES                               0x0Cu

typedef enum{
      DCM_CONTROLMASK_NO
   ,  DCM_CONTROLMASK_INTERNAL
   ,  DCM_CONTROLMASK_EXTERNAL
}Dcm_Dsp_IocbiCtrlMask_ten;

typedef struct{
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
   uint32 dataAllowedSessRead_u32;
   uint32 dataAllowedSecRead_u32;
   Std_ReturnType (*adrUserReadModeRule_pfct)(
         Dcm_NegativeResponseCodeType* dataNrc
      ,  uint16                        dataDid_u16
      ,  Dcm_Direction_t               Dcm_Support_Read
   );
#endif
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
   uint32 dataAllowedSessWrite_u32;
   uint32 dataAllowedSecWrite_u32;
   Std_ReturnType (*adrUserWriteModeRule_pfct)(
         Dcm_NegativeResponseCodeType* dataNrc
      ,  uint16                        dataDid_u16
      ,  Dcm_Direction_t               Dcm_Support_Write
   );
#endif
}Type_CfgSwcServiceDcm_stDidExtended;

typedef struct{
  void* const adrCondChkRdFnc_cpv;
  void* const adrReadDataLengthFnc_pfct;
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
  void* const adrWriteFnc_cpv;
  void* const VarDataWrite;
  void (*GetSignalData_pfct)(void* requestBuffer, uint16 position_u16);
#endif
}Type_CfgSwcServiceDcm_stInfoDidWrite;

typedef struct{
  void* const adrReadFnc_cpv;
  void* const VarDataRead;
  Std_ReturnType (*StoreSignal_pfct)(
        void*  targetBuffer
     ,  uint16 position
  );
  uint16 dataSize_u16;
  uint16 idxDcmDspControlInfo_u16;
  uint8  dataType_u8;
  uint8  usePort_u8;
}Dcm_DataInfoConfig_tst;

typedef struct{
   uint16 posnSigBit_u16;
   uint16 idxDcmDspDatainfo_u16;
   Std_ReturnType (*fptrSenderReceiverRead )(void* VarDataRead);
   Std_ReturnType (*fptrSenderReceiverWrite)(void* VarDataWrite);
}Type_CfgSwcServiceDcm_stSignalDid;

typedef struct{
   uint16  dataDid_u16;
   uint8   didUsePort_u8;
   boolean AtomicorNewSRCommunication_b;
   uint16  nrSig_u16;
   uint16  dataMaxDidLen_u16;
   boolean dataFixedLength_b;
   boolean dataDynamicDid_b;
   const Type_CfgSwcServiceDcm_stSignalDid* pcstSignalDid;
   void* const ioControlRequest_cpv;
   const Type_CfgSwcServiceDcm_stDidExtended* pcstDidExtended;
}Type_CfgSwcServiceDcm_stDid;

typedef struct{
   Std_ReturnType (*adrDIDAvailableFnc_pfct) (
         uint16                DID
      ,  Dcm_OpStatusType      OpStatus
      ,  Dcm_DidSupportedType* supported
   );
   Std_ReturnType (*adrReadFnc_pfct) (
         uint16                              DID
      ,  uint8*  const                       Data
      ,  Dcm_OpStatusType                    OpStatus
      ,  uint16* const                       DataLength
      ,  Dcm_NegativeResponseCodeType* const ErrorCode
   );
  void* const                                adrReadDataLengthFnc_pfct;
  void* const                                adrWriteFnc_pfct;
  const Type_CfgSwcServiceDcm_stDidExtended* pcstDidExtended;
  uint16                                     nrDidRangeUpperLimit_u16;
  uint16                                     nrDidRangeLowerLimit_u16;
  uint16                                     dataMaxDidLen_u16;
  boolean                                    dataRangeHasGaps_b;
  boolean                                    nrRangeUsePort_b;
}Dcm_DIDRangeConfig_tst;

typedef Std_ReturnType (*ReadDataLengthFnc1_pf) (uint16* DataLength);
typedef Std_ReturnType (*ReadDataLengthFnc4_pf) (Dcm_OpStatusType OpStatus, uint16* DataLength);
typedef Std_ReturnType (*ReadDataLengthFnc2_pf) (uint32* DataLength);
typedef Std_ReturnType (*ReaddatalengthFnc3_pf) (uint16 DID,Dcm_OpStatusType OpStatus, uint16* DataLength);
typedef Std_ReturnType (*ReaddatalengthFnc5_pf) (void);
typedef Std_ReturnType (*ReadDataLengthFnc6_pf) (Dcm_OpStatusType OpStatus);
typedef Std_ReturnType (*CondChkReadFunc1_pfct) (Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*CondChkReadFunc2_pfct) (Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*CondChkReadFunc3_pfct) (Dcm_OpStatusType OpStatus);
typedef Std_ReturnType (*ReadFunc1_pfct)        (uint8* Data);
typedef Std_ReturnType (*ReadFunc10_pfct)       (uint8* Data,Dcm_NegativeResponseCodeType* ErrorCode);
typedef Std_ReturnType (*ReadFunc2_ptr)         (Dcm_OpStatusType OpStatus, uint8* Data);
typedef Std_ReturnType (*ReadFunc3_pfct)        (boolean* Data);
typedef Std_ReturnType (*ReadFunc4_pfct)        (uint16*  Data);
typedef Std_ReturnType (*ReadFunc5_pfct)        (uint32*  Data);
typedef Std_ReturnType (*ReadFunc6_pfct)        (sint8*   Data);
typedef Std_ReturnType (*ReadFunc7_pfct)        (sint16*  Data);
typedef Std_ReturnType (*ReadFunc8_pfct)        (sint32*  Data);

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern Std_ReturnType Dcm_GetActiveRDBIDid(uint16 * dataDid_u16);
#endif
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern Std_ReturnType Dcm_GetActiveWDBIDid(uint16 * dataDid_u16);
#endif
extern uint16 Dcm_DIDcalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern const Type_CfgSwcServiceDcm_stDid CfgSwcServiceDcm_astListDid [];
extern const Dcm_DataInfoConfig_tst Dcm_DspDataInfo_st[];
extern const Type_CfgSwcServiceDcm_stInfoDidWrite CfgSwcServiceDcm_castListInfoDidWrite[];
extern const Dcm_DIDRangeConfig_tst Dcm_DIDRangeConfig_cast[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_DidSignalIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
extern boolean Dcm_flgDspDidRangePending_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

extern boolean Dcm_PeriodicSchedulerRunning_b;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern uint8 Dcm_RoeDidIdx_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#if( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern void Dcm_ResetAccessType (void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern Std_ReturnType Dcm_VinBuffer_Init(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif
#endif

