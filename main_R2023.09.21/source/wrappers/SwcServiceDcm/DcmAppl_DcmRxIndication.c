#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_APPL_CODE) DcmAppl_TpRxIndication(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) DcmRxPduId,
   VAR(Std_ReturnType, AUTOMATIC) Result){
    (void)DcmRxPduId;
    (void)Result;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

