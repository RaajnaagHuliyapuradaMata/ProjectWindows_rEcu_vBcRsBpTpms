
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Rmba_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)           ||  \
    (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)    ||  \
    (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)           || \
    (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

 Dcm_ReturnReadMemoryType DcmAppl_Dcm_ReadMemory(Dcm_OpStatusType Rmba_Opstatus,
 														uint8 memoryid,
 														uint32 memoryaddress,
 														uint32 datalength,
 														uint8 * respbuf,
 														Dcm_NegativeResponseCodeType * ErrorCode)
 {

    Dcm_ReturnReadMemoryType retVal = DCM_READ_OK;

   return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
