
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

 #define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void DcmAppl_DcmStoreRespForJump
                                   (Dcm_ProgConditionsType * ProgConditions)
{

	

     //RST Info: nothing to do here. Application is configured to send "resp pending" on a bootloader reset 11 4c
     //Bootloader FBL will then send the positive response.

    (void)ProgConditions;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif

