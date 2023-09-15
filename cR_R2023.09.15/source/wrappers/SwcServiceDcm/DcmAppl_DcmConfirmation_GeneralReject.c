#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation_GeneralReject (
                                                                VAR(Dcm_IdContextType,AUTOMATIC) idContext
   ,     VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) dcmRxPduId
   ,     VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
){
    (void)(status);
    (void)(dcmRxPduId);
    (void)(idContext);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

