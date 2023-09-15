
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

//RST integration code start
#include "DcmManagerX.hpp"
//RST integration code end

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Dcm_EcuStartModeType Dcm_GetProgConditions
                                   (Dcm_ProgConditionsType * ProgConditions)
{
   Dcm_EcuStartModeType retVal = DCM_COLD_START;
  if(DCMMGR_GetPositiveResponseTrigger() == TRUE)
  {
   ProgConditions->ApplUpdated = TRUE;
   ProgConditions->ElapsedTime = 0x0;
   ProgConditions->NumWaitPend = 1;
   ProgConditions->ProtocolId = DCM_UDS_ON_CAN;
   ProgConditions->ReprogramingRequest = TRUE;
   ProgConditions->SessionLevel = DCM_PROGRAMMING_SESSION; //last session
   ProgConditions->Sid = 0x51;                             //send 51 01 which is positive
   ProgConditions->SubFncId = 0x01;                        //response on 11 01

   ProgConditions->ReqResLen = 2;                          //two bytes of response: 0x51 0x01
   ProgConditions->StoreType = DCM_WARMRESPONSE_TYPE;
   ProgConditions->ResponseRequired = TRUE;
   ProgConditions->TesterSourceAddr = 0;                   //this is configured in IsolarB parameter DcmDslProtocolRxTesterSourceAddress
   ProgConditions->SecurityLevel = 0x11;                // from RST, but this cannot be. KF_TODO 24.02.2023
   // ProgConditions->SecurityLevel = 0x0;                   //target security level
   retVal = DCM_WARM_START;
  }
  //RST integration code end

  return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
