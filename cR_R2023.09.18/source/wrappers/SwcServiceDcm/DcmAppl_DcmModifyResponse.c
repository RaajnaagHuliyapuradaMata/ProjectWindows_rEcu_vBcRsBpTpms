#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmMsgAuthenticationX.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void, DCM_APPL_CODE) DcmAppl_DcmModifyResponse(
   VAR(uint8,AUTOMATIC) dataSid_u8
   ,  VAR(uint8,AUTOMATIC) dataNRC_u8
   ,  P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrBufPtr_pu8
   ,  P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) nrBufSize_pu32
){
  uint8 ucNumberOfBytesToAdd;
  ucNumberOfBytesToAdd = DcmAppendMessageAuthentication(dataSid_u8, adrBufPtr_pu8, (uint32)Dcm_DsldMsgContext_st.resDataLen, (uint8*)Dcm_DsldMsgContext_st.resData);
   if(ucNumberOfBytesToAdd == 0){
    *nrBufSize_pu32 = 0;
  }
  else{
    *nrBufSize_pu32 = ucNumberOfBytesToAdd;
  }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
