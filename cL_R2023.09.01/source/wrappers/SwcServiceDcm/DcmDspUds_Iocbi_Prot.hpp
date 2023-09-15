

#ifndef DCMDSPUDS_IOCBI_PROT_H
#define DCMDSPUDS_IOCBI_PROT_H

#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)

typedef Std_ReturnType (*ReturnControlEcu1_pfct) (Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ReturnControlEcu2_pfct) (Dcm_OpStatusType OpStatus
   ,  	                      Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ReturnControlEcu3_pfct) (uint8 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ReturnControlEcu4_pfct) (uint16 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ReturnControlEcu5_pfct) (uint32 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ReturnControlEcu6_pfct) (Dcm_OpStatusType OpStatus
   ,                                    uint8 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ReturnControlEcu7_pfct) (Dcm_OpStatusType OpStatus
   ,                                    uint16 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ReturnControlEcu8_pfct) (Dcm_OpStatusType OpStatus
   ,                                    uint32 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ResetToDefault1_pfct) (Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ResetToDefault2_pfct) (Dcm_OpStatusType OpStatus
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ResetToDefault3_pfct) (uint8 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ResetToDefault4_pfct) (uint16 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ResetToDefault5_pfct) (uint32 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ResetToDefault6_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint8 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ResetToDefault7_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint16 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ResetToDefault8_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint32 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*FreezeCurrentState1_pfct) (Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*FreezeCurrentState2_pfct) (Dcm_OpStatusType OpStatus
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*FreezeCurrentState3_pfct) (uint8 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*FreezeCurrentState4_pfct) (uint16 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*FreezeCurrentState5_pfct) (uint32 controlMask
   ,                                    Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*FreezeCurrentState6_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint8 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*FreezeCurrentState7_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint16 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*FreezeCurrentState8_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint32 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ShortTermAdjustment1_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ShortTermAdjustment2_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_OpStatusType OpStatus
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ShortTermAdjustment3_pfct) (const uint8 * ControlStateInfo
   ,                             uint8 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ShortTermAdjustment4_pfct) (const uint8 * ControlStateInfo
   ,                             uint16 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ShortTermAdjustment5_pfct) (const uint8 * ControlStateInfo
   ,                             uint32 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ShortTermAdjustment6_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_OpStatusType OpStatus
   ,                             uint8 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ShortTermAdjustment7_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_OpStatusType OpStatus
   ,                             uint16 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
typedef Std_ReturnType (*ShortTermAdjustment8_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_OpStatusType OpStatus
   ,                             uint32 controlMask
   ,                             Dcm_NegativeResponseCodeType * ErrorCode);
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
typedef Std_ReturnType (*ShortTermAdjustment9_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_OpStatusType OpStatus);
typedef Std_ReturnType (*ShortTermAdjustment10_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_OpStatusType OpStatus
   ,                             uint8 controlMask);
typedef Std_ReturnType (*ShortTermAdjustment11_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_OpStatusType OpStatus
   ,                             uint16 controlMask);
typedef Std_ReturnType (*ShortTermAdjustment12_pfct) (const uint8 * ControlStateInfo
   ,                             Dcm_OpStatusType OpStatus
   ,                             uint32 controlMask);
typedef Std_ReturnType (*ShortTermAdjustment13_pfct) (Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*FreezeCurrentState9_pfct) (Dcm_OpStatusType OpStatus);
typedef Std_ReturnType (*FreezeCurrentState10_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint8 controlMask);
typedef Std_ReturnType (*FreezeCurrentState11_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint16 controlMask);
typedef Std_ReturnType (*FreezeCurrentState12_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint32 controlMask);
typedef Std_ReturnType (*FreezeCurrentState13_pfct) (Dcm_NegativeResponseCodeType * ErrorCode);

typedef Std_ReturnType (*ResetToDefault9_pfct) (Dcm_OpStatusType OpStatus);
typedef Std_ReturnType (*ResetToDefault10_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint8 controlMask);
typedef Std_ReturnType (*ResetToDefault11_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint16 controlMask);
typedef Std_ReturnType (*ResetToDefault12_pfct) (Dcm_OpStatusType OpStatus
   ,                             uint32 controlMask);
typedef Std_ReturnType (*ResetToDefault13_pfct) (Dcm_NegativeResponseCodeType * ErrorCode);
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
extern Dcm_Dsp_IocbiStatusType_tst DcmDsp_IocbiStatus_array[DCM_CFG_NUM_IOCBI_DIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern void Dcm_ResetActiveIoCtrl(uint32 dataSessionMask_u32
   ,  											 uint32 dataSecurityMask_u32
   ,  											 boolean flgSessChkReqd_b);
extern void Dcm_Lok_DspIOCBIConfirmation(
   Dcm_IdContextType dataIdContext_u8
   ,  PduIdType dataRxPduId_u8
   ,  uint16 dataSourceAddress_u16
   ,  Dcm_ConfirmationStatusType status_u8
   												    );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

