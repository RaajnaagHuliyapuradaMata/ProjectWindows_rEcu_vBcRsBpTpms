

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"
#include "Com_Cbk.h"
#include "PduR_Com.h"
#include "Com_PBcfg_InternalId.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void, COM_CODE) Com_MainFunctionRx(void)
{
    Com_InternalMainFunctionRx( (Com_MainFuncType)ComMainFunction_Internal_MainFunctionRx );
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void, COM_CODE) Com_MainFunctionTx(void)
{
    Com_InternalMainFunctionTx( (Com_MainFuncType)ComMainFunction_Internal_MainFunctionTx );
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TxIPduNotification
#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void,COM_CODE) Com_TxNotify_ApplicationResponse_TPM_Can_Network_CANNODE_0(void)
{
    Com_IPdu_NotificationCallback_ApplicationResponse();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

#ifdef COM_TxIPduTimeOutNotify
#endif

#ifdef COM_RxIPduTimeoutNotify

#endif

#define COM_START_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.h"
CONST(Com_TransModeInfo, COM_CONST) Com_NONE_TransModeInfo =
{
    0,
    0,

    0,
    0,

#ifdef COM_MIXEDPHASESHIFT
    COM_TXMODE_NONE,
    COM_FALSE
#else

    COM_TXMODE_NONE

#endif

};
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector;

VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector_DM;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

