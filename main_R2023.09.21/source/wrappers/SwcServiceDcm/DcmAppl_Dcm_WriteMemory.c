#include "Std_Types.hpp"

#include "DcmDspUds_Wmba_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Dcm_ReturnWriteMemoryType,DCM_APPL_CODE) DcmAppl_Dcm_WriteMemory(
   VAR(Dcm_OpStatusType, AUTOMATIC) Wmba_Opstatus,
 													VAR(uint8,  AUTOMATIC) memoryid,
 													VAR(uint32,  AUTOMATIC) memoryaddress,
 													VAR(uint32,  AUTOMATIC) datalength,
 													P2CONST (uint8,AUTOMATIC,DCM_INTERN_DATA) reqbuf,
   P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode){
   VAR(Dcm_ReturnWriteMemoryType,AUTOMATIC) retVal = DCM_WRITE_OK;
    (void)(Wmba_Opstatus);
    (void)(memoryid);
    (void)(memoryaddress);
    (void)(datalength);
    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
