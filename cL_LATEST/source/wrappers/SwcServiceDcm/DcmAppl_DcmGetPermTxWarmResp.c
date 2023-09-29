
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"
// RST integration code start
#include "DcmManagerX.hpp"
#include "CanIf.hpp"
// RST integration code end

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_DcmGetPermTxWarmResp(void){
    Std_ReturnType retVal;

    // RST: function returns always 0 if not used - commented this
    //retVal = E_OK;

    //return (retVal);

   Type_EcuabCanIf_eModeController tCanIfControllerMode;
    retVal = E_NOT_OK;

   CanIf_GetControllerMode(0, &tCanIfControllerMode);
   if(tCanIfControllerMode == CANIF_CS_STARTED)
   {
      retVal = E_OK;
   }

    return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif
