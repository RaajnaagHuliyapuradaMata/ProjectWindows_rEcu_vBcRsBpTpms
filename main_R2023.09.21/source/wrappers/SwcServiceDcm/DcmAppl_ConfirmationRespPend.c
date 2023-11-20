#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_APPL_CODE) DcmAppl_ConfirmationRespPend(
                                                    VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
                                                )
{
(void)status;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
