#include "Std_Types.hpp"

#include "infSwcServiceComSwcServiceSchM.hpp"

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"
#include "Com_Cbk.hpp"
#include "PduR_Com.hpp"
#include "Com_PBcfg_InternalId.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
FUNC(void, COM_CODE) infSwcServiceComSwcServiceSchM_vMainFunctionRx(void){
   Com_InternalMainFunctionRx((Com_MainFuncType)ComMainFunction_Internal_MainFunctionRx);
}

FUNC(void, COM_CODE) infSwcServiceComSwcServiceSchM_vMainFunctionTx(void){
   Com_InternalMainFunctionTx((Com_MainFuncType)ComMainFunction_Internal_MainFunctionTx);
}
#ifdef COM_TxIPduNotification
FUNC(void,COM_CODE) Com_TxNotify_ApplicationResponse_TPM_Can_Network_CANNODE_0(void){
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#define COM_START_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.hpp"
CONST(Com_TransModeInfo, COM_CONST) Com_NONE_TransModeInfo = {
   0, 0, 0, 0, COM_TXMODE_NONE
#ifdef COM_MIXEDPHASESHIFT
   ,  COM_FALSE
#endif
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"
VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector;
VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector_DM;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.hpp"

