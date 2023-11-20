#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStartProtocol(
   VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID){
Std_ReturnType retVal;
retVal = E_OK;
    (void)(ProtocolID);
return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

