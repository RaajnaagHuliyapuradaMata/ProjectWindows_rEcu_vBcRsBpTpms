
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

//RST integration code start
#include "DcmManagerX.h"
#include "WrapNv_Cfg.h"
//RST integration code end

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Dcm_EcuStartModeType,DCM_APPL_CODE) Dcm_GetProgConditions
                                   (P2VAR(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions)
{
	VAR(Dcm_EcuStartModeType,AUTOMATIC) retVal = DCM_COLD_START;

	

	

  //RST integration code start
  // Function is called on each startup. Check if this is a cold start (does not require UDS response)
  // or a warm start from FBL that requires sending UDS response, depending on reset response flag (set by FBL).

  uint8 ucResetResponseType;

  ApplFblNvReadResetResponseFlag(&ucResetResponseType);

  if (ucResetResponseType == RESET_RESPONSE_ECURESET_REQUIRED)
  {
    ProgConditions->Sid = 0x51;                             //send 51 01 which is positive
    ProgConditions->SubFncId = 0x01;                        //response on 11 01 (HardReset)

    ProgConditions->ApplUpdated = TRUE;
    ProgConditions->ElapsedTime = 0x0;
    ProgConditions->NumWaitPend = 1;
    ProgConditions->ProtocolId = DCM_UDS_ON_CAN;
    ProgConditions->ReprogramingRequest = TRUE;
    ProgConditions->SessionLevel = DCM_DEFAULT_SESSION;     //start with default session
    ProgConditions->ReqResLen = 2;                          //two bytes of response: 0x51 0x01
    ProgConditions->StoreType = DCM_WARMRESPONSE_TYPE;
    ProgConditions->ResponseRequired = TRUE;
    ProgConditions->TesterSourceAddr = 0;                   //this is configured in IsolarB parameter DcmDslProtocolRxTesterSourceAddress
    ProgConditions->SecurityLevel = 0;                      //target security level

    retVal = DCM_WARM_START;
  }

  else if (ucResetResponseType == RESET_RESPONSE_SDS_REQUIRED)
  {
    ProgConditions->Sid = 0x50;                             //send 50 01 which is positive
    ProgConditions->SubFncId = 0x01;                        //response on 10 01 (DefaultSession)
    ProgConditions->ApplUpdated = TRUE;
    ProgConditions->ElapsedTime = 0x0;
    ProgConditions->NumWaitPend = 1;
    ProgConditions->ProtocolId = DCM_UDS_ON_CAN;
    ProgConditions->ReprogramingRequest = TRUE;
    ProgConditions->SessionLevel = DCM_DEFAULT_SESSION;
    ProgConditions->ReqResLen = 2;                          //two bytes of response: 0x51 0x01
    ProgConditions->StoreType = DCM_WARMRESPONSE_TYPE;
    ProgConditions->ResponseRequired = TRUE;
    ProgConditions->TesterSourceAddr = 0;                   //this is configured in IsolarB parameter DcmDslProtocolRxTesterSourceAddress
    ProgConditions->SecurityLevel = 0;                      //target security level

    retVal = DCM_WARM_START;
  }

  else
  {
    ProgConditions->ApplUpdated = FALSE;
    ProgConditions->ElapsedTime = 0x0;
    ProgConditions->NumWaitPend = 0;
    ProgConditions->ProtocolId = DCM_UDS_ON_CAN;
    ProgConditions->ReprogramingRequest = FALSE;
    ProgConditions->SessionLevel = DCM_DEFAULT_SESSION;
    ProgConditions->ReqResLen = 0;                          //nothing to respond
    ProgConditions->StoreType = DCM_NOTVALID_TYPE;
    ProgConditions->ResponseRequired = FALSE;
    ProgConditions->TesterSourceAddr = 0;                   //this is configured in IsolarB parameter DcmDslProtocolRxTesterSourceAddress
    ProgConditions->SecurityLevel = 0;                      //target security level
    retVal = DCM_COLD_START;
  }

    //if (ucResetResponseType != RESET_RESPONSE_NOT_REQUIRED)
    //{
    //  ProgConditions->ApplUpdated = TRUE;
    //  ProgConditions->ElapsedTime = 0x0;
    //  ProgConditions->NumWaitPend = 1;
    //  ProgConditions->ProtocolId = DCM_UDS_ON_CAN;
    //  ProgConditions->ReprogramingRequest = TRUE;
    //  //ProgConditions->SessionLevel = DCM_PROGRAMMING_SESSION; //last session
    //  ProgConditions->SessionLevel = DCM_DEFAULT_SESSION; //last session
    //  if (ucResetResponseType == RESET_RESPONSE_ECURESET_REQUIRED)
    //  {
    //    ProgConditions->Sid = 0x51;                             //send 51 01 which is positive
    //    ProgConditions->SubFncId = 0x01;                        //response on 11 01 (HardReset)
    //  }
    //  else if (ucResetResponseType == RESET_RESPONSE_SDS_REQUIRED)
    //  {
    //    ProgConditions->Sid = 0x50;                             //send 50 01 which is positive
    //    ProgConditions->SubFncId = 0x01;                        //response on 10 01 (DefaultSession)
    //  }
    //
    //
    //  ProgConditions->ReqResLen = 2;                          //two bytes of response: 0x51 0x01
    //  ProgConditions->StoreType = DCM_WARMRESPONSE_TYPE;
    //  ProgConditions->ResponseRequired = TRUE;
    //  ProgConditions->TesterSourceAddr = 0;                   //this is configured in IsolarB parameter DcmDslProtocolRxTesterSourceAddress
    //  ProgConditions->SecurityLevel = 0x11;                   //target security level
    //  retVal = DCM_WARM_START;
    //}

    ucResetResponseType = RESET_RESPONSE_NOT_REQUIRED;
    ApplFblNvWriteResetResponseFlag(&ucResetResponseType);
  //}
  //RST integration code end
  	
  return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
