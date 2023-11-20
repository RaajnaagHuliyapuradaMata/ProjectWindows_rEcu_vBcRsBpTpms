#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"
#include "DcmManagerX.hpp"
#include "CanIf.hpp"

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetPermTxWarmResp(void){
   VAR(Std_ReturnType,AUTOMATIC)   retVal;
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
