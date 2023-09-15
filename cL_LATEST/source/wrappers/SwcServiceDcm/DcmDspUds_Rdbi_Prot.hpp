#ifndef DCMDSPUDS_RDBI_PROT_H
#define DCMDSPUDS_RDBI_PROT_H

#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_RDBI_SIZE_DID            (0x02u)
typedef enum{
      DCM_RDBI_IDLE
   ,  DCM_RDBI_NEG_RESP
   ,  DCM_RDBI_PROCESS_NEW_DID
   ,  DCM_RDBI_CHECK_READACCESS
   ,  DCM_RDBI_CHECK_CONDITIONS
   ,  DCM_RDBI_GET_LENGTH
   ,  DCM_RDBI_GET_DATA
}Dcm_StRdbi_ten;

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_RdbiReqDidNb_u16;
extern uint16 Dcm_NumOfIndices_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_StRdbi_ten Dcm_stRdbi_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern uint32 Dcm_TotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

typedef enum{
      DCM_LENCALC_RETVAL_OK
   ,  DCM_LENCALC_RETVAL_ERROR
   ,  DCM_LENCALC_RETVAL_PENDING
}Dcm_LenCalcRet_ten;

typedef enum{
      DCM_LENCALC_STATUS_INIT
   ,  DCM_LENCALC_STATUS_GETINDEX
   ,  DCM_LENCALC_STATUS_GETLENGTH
   ,  DCM_LENCALC_STATUS_GETSUPPORT
}Dcm_LenCalc_ten;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_LenCalc_ten Dcm_StLenCalc_en;
extern uint8 * Dcm_IdxList_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern uint32 Dcm_NumberOfBytesInResponse_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_NumberOfProcessedDIDs_u16;
extern uint16 Dcm_NumberOfAcceptedDIDs_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_OpStatusType Dcm_DspReadDidOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Dcm_LenCalcRet_ten Dcm_DspGetTotalLengthOfDIDs_en(
      uint8*                        adrSourceIds_pu8
   ,  uint16                        nrDids_u16
   ,  uint16*                       adrNumOfIndices_pu16
   ,  uint32*                       adrTotalLength_pu32
   ,  Dcm_NegativeResponseCodeType* dataNegRespCode_u8
);
extern void Dcm_Lok_DspRdbiConfirmation(
      Dcm_IdContextType          dataIdContext_u8
   ,  Type_SwcServiceCom_tIdPdu                  dataRxPduId_u8
   ,  uint16                     dataSourceAddress_u16
   ,  Dcm_ConfirmationStatusType status_u8
);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

typedef enum{
      SwcServiceDcm_eRetValGetDataOk
   ,  SwcServiceDcm_eRetValGetDataErrorInternal
   ,  SwcServiceDcm_eRetValGetDataPending
   ,  SwcServiceDcm_eRetValGetDataConditionsInvalid
}Type_SwcServiceDcm_eRetValGetData;

typedef enum{
      SwcServiceDcm_eStatusGetDataInit
   ,  SwcServiceDcm_eStatusGetDataLength
   ,  SwcServiceDcm_eStatusGetDataPayload
}Type_SwcServiceDcm_eStatusGetData;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Type_SwcServiceDcm_eStatusGetData SwcServiceDcm_eStatusGetData;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_GetDataNumOfIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern uint32 Dcm_GetDataTotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Type_SwcServiceDcm_eRetValGetData Dcm_GetData_en(
      const uint8*                        adrIdBuffer_pcu8
   ,        uint8*                        adrTargetBuffer_pu8
   ,        uint16                        nrIndex_u16
   ,        Dcm_NegativeResponseCodeType* dataNegRespCode_u8
   ,        uint32                        adrTotalLength_pu32);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif

#endif

