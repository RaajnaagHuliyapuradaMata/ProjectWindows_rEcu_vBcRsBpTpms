

#ifndef DCMDSPUDS_IOCBI_PROT_H
#define DCMDSPUDS_IOCBI_PROT_H

#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu1_pfct)
   	                     (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu2_pfct)
   	                     (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,                        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu3_pfct)
                             (VAR(uint8,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu4_pfct)
                             (VAR(uint16,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu5_pfct)
                             (VAR(uint32,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu6_pfct)
                              (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu7_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint16,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu8_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint32,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault1_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault2_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault3_pfct)
                             (VAR(uint8,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault4_pfct)
                             (VAR(uint16,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault5_pfct)
                             (VAR(uint32,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault6_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault7_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint16,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault8_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint32,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState1_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState2_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState3_pfct)
                             (VAR(uint8,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState4_pfct)
                             (VAR(uint16,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState5_pfct)
                             (VAR(uint32,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState6_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState7_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint16,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState8_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint32,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment1_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment2_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment3_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(uint8,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment4_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(uint16,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment5_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(uint32,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment6_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment7_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint16,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment8_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint32,AUTOMATIC) controlMask
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment9_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment10_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment11_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint16,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment12_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo
   ,     VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint32,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment13_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState9_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState10_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState11_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint16,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState12_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint32,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState13_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault9_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault10_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint8,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault11_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint16,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault12_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus
   ,     VAR(uint32,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault13_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,IOControlrequest_pfct)
                                        ( VAR(Dcm_InputOutputControlParameterType,AUTOMATIC) IoctrlParam
   ,     P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) RequestData
   ,     VAR(uint16,AUTOMATIC)  dataSignalLength_u16
   ,     VAR(uint8,AUTOMATIC)  controlMaskLength_u8
   ,     VAR(Dcm_OpStatusType, AUTOMATIC) IocbiOpStatus_u8
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

typedef enum{
    DCM_IOCBI_IDLESTATE,     
    DCM_IOCBI_FCS_ACTIVE
   ,   DCM_IOCBI_FCS_PENDING
   ,   DCM_IOCBI_RTD_ACTIVE
   ,   DCM_IOCBI_RTD_PENDING,     
    DCM_IOCBI_STA_ACTIVE,     
    DCM_IOCBI_STA_PENDING,     
    DCM_IOCBI_RCE_ACTIVE,     
    DCM_IOCBI_RCE_PENDING             
  }Dcm_Dsp_IocbiDidStatus_ten;

typedef struct{
   uint16    	idxindex_u16;
   Dcm_Dsp_IocbiDidStatus_ten IocbiStatus_en;
}Dcm_Dsp_IocbiStatusType_tst;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_Dsp_IocbiStatusType_tst,DCM_VAR) DcmDsp_IocbiStatus_array[DCM_CFG_NUM_IOCBI_DIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_ResetActiveIoCtrl(VAR (uint32,AUTOMATIC) dataSessionMask_u32
   ,   VAR (uint32,AUTOMATIC) dataSecurityMask_u32
   ,   VAR (boolean,AUTOMATIC) flgSessChkReqd_b);
extern FUNC(void, DCM_CODE) Dcm_Lok_DspIOCBIConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
   												    );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

