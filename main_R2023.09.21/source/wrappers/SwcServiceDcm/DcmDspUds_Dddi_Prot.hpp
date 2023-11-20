

#ifndef DCMDSPUDS_DDDI_PROT_H
#define DCMDSPUDS_DDDI_PROT_H

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

#define DCM_DEFINITION_BY_ID                (0x01u)
#define DCM_DEFINITION_BY_MEMORYADDRESS     (0x02u)
#define DCM_DDDI_CLEAR_DYNAMIC_IDENTIFIER   (0x03u)

#define DCM_DDDI_MEMADDR_MINLEN             (0x06u)

#define DCM_STACK_BUFFER  0u
#define DCM_RAM_BUFFER    1u

typedef struct{
      uint32 sigPosnBit_u32;
      uint32 sigDataSize_u32;
}Dcm_DynamicSignalConfig_tst;

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_OpStatusType, DCM_VAR) Dcm_DspDataOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern CONST(Dcm_DddiMainConfig_tst, DCM_CONST) Dcm_DDDIBaseConfig_cast[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DynamicSignalConfig_tst, DCM_VAR) Dcm_DynamicSignalConfig_cast[];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(uint16,DCM_CODE) Dcm_DddiCalculateTableSize_u16(void);
FUNC(void,DCM_CODE) Dcm_DddiResetCompleteContext(P2VAR(Dcm_DddiIdContext_tst, AUTOMATIC,DCM_INTERN_DATA) adrContext_pst);
FUNC(void,DCM_CODE) Dcm_DddiResetProcessingInfoInContext(P2VAR(Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrPtrToContext_pst);

FUNC(Std_ReturnType,DCM_CODE) Dcm_DddiReadById_u8(P2CONST(Dcm_DddiDefId_tst,AUTOMATIC,DCM_INTERN_CONST) adrRecord_pst
   ,     P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) adrLength_pu16
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8);

FUNC(Std_ReturnType,DCM_CODE) Dcm_DddiRead_u8(P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);

FUNC(Std_ReturnType,DCM_CODE) Dcm_DddiGetLen_u8(P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst
   ,     P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) adrLen_pu32);

FUNC(Std_ReturnType,DCM_CODE) Dcm_DddiGetCondition_u8(P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);

FUNC(Std_ReturnType,DCM_CODE) Dcm_DspGetIndexOfDDDI_u8(VAR(uint16,AUTOMATIC) dataDid_u16, P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) idxIndex_u16);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_DDDI_MIN_LENGTH (1u)

typedef enum{
    DCM_DDDI_IDLE
   ,   DCM_DDDI_NEGRESP
   ,   DCM_DDDI_GETLENGTH
   ,   DCM_DDDI_GETSUPPORT
   ,   DCM_DDDI_SENDRESP
  }
Dcm_DddiServiceStatus_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DddiServiceStatus_ten ,DCM_VAR)   Dcm_DspStDddi_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspDddidOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
typedef enum{
    DCM_DDDI_DEFINE_BY_ID_INIT
   ,   DCM_DDDI_DEFINE_BY_ID_GETINDEX
   ,   DCM_DDDI_DEFINE_BY_ID_GETSUPPORT
   ,   DCM_DDDI_DEFINE_BY_ID_GETLENGTH
  }Dcm_DddiDefineById_ten;

#define DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH (4u)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DddiDefineById_ten,DCM_VAR) Dcm_stAddIdRecords_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint16 ,DCM_VAR) Dcm_AddIdCurrentBlockIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern VAR (uint32,DCM_VAR) Dcm_AddIdCurrentLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmDddiAddIdRecords_u8( VAR(uint16,AUTOMATIC)nrBlocks_u16
   ,     VAR(uint16,AUTOMATIC)nrCurrentlyDefinedRecords_u16
   ,     P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8
   ,     P2VAR(Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     VAR (uint16,AUTOMATIC) idxIndex_u16
   ,     VAR (Dcm_MsgLenType,AUTOMATIC) nrResponseBufferLen_u32
                                                       );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

typedef enum{
    DCM_DDDI_DEFINE_BY_MEM_INIT
   ,   DCM_DDDI_DEFINE_BY_MEM_GETSUPPORT
  }Dcm_DddiDefineByMem_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_DddiDefineByMem_ten,DCM_VAR) Dcm_stAddMemRecords_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint16 ,DCM_VAR) Dcm_AddMemCurrentBlockIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmDddiAddMemRecords_u8(VAR(uint16,AUTOMATIC)nrBlocks_u16
   ,     VAR(uint16,AUTOMATIC)nrCurrentlyDefinedRecords_u16
   ,     P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8
   ,     P2VAR(Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst
   ,     P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     VAR(uint8,AUTOMATIC)nrBytesForAddress_u8
   ,     VAR(uint8,AUTOMATIC)nrBytesForLength_u8
   ,     VAR (uint16,AUTOMATIC) idxIndex_u16
   ,     VAR (Dcm_MsgLenType,AUTOMATIC) nrResponseBufferLen_u32);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

