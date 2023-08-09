
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

 #define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void,DCM_APPL_CODE) DcmAppl_DcmStoreRespForJump
                                   (P2VAR(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions)
{

	

     //RST Info: nothing to do here. Application is configured to send "resp pending" on a programming session request.
     //Bootloader FBL will then send the positive response.
     //If DID "Reset" is executed, currently the positive response is sent immediately. This still is to be changed.
     //DID shall also answer with response pending
     //The bootmanager will directly start the application again and the application must then send the positive response.

    (void)ProgConditions;

}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif

