

#include "Com_Prv.h"
#include "Com_Lok_Inl.h"
#include "Com_Cbk.h"
#include "Com_PBcfg_InternalId.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
Com_IpduGroupVector Com_IpduGrpVector;

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
Com_IpduGroupVector Com_IpduGrpVector_DM;
#endif

#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

#define COM_START_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.h"
const Com_TransModeInfo Com_NONE_TransModeInfo =
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

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

void Com_MainFunctionRx(void)
{
#ifdef COM_RX_MAINFUNCTION_PROC
    Com_InternalMainFunctionRx( (Com_MainFuncType)ComMainFunction_Internal_MainFunctionRx );
#endif
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

void Com_MainFunctionTx(void)
{
    Com_InternalMainFunctionTx( (Com_MainFuncType)ComMainFunction_Internal_MainFunctionTx );
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TxIPduNotification
#endif

#ifdef COM_TxIPduTimeOutNotify
#endif

#ifdef COM_RxIPduTimeoutNotify

#endif

