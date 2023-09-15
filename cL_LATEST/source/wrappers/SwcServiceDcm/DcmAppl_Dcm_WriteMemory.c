
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Wmba_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

 Dcm_ReturnWriteMemoryType DcmAppl_Dcm_WriteMemory(Dcm_OpStatusType Wmba_Opstatus,
 													uint8 memoryid,
 													uint32 memoryaddress,
 													uint32 datalength,
 													const uint8 * reqbuf,
 													Dcm_NegativeResponseCodeType * ErrorCode)
 {
    Dcm_ReturnWriteMemoryType retVal = DCM_WRITE_OK;

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
