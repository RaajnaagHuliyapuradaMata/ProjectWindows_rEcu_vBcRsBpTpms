
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void DcmAppl_DcmCancelPagedBufferProcessing(Dcm_IdContextType idContext)
{

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

   if(idContext == DCM_DSP_SID_READDATABYIDENTIFIER)
   {

        Dcm_Dsp_RdbiIni();
   }

#endif
#if((DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

   if(idContext == DCM_DSP_SID_READDTCINFORMATION)
   {

        Dcm_Dsp_ReadDTCInfo_Ini();
   }
#else
    (void)(idContext);
#endif
#else
    (void)(idContext);
#endif
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

