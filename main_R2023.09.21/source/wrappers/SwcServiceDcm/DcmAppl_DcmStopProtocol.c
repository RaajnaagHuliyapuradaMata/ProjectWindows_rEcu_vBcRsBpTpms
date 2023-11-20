#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStopProtocol(
   VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID){
    (void)(ProtocolID);
   return E_OK;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
