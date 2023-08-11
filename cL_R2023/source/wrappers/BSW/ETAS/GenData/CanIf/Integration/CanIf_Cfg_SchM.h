#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef CANIF_CFG_SCHM_H
#define CANIF_CFG_SCHM_H

#include "SchM.h"
#include "SchM_Default.h"
#include "CanIf_Cfg.h"

#include "SchM_CanIf.h"
#include "SchM_Can.h"

#define SCHM_MULTICORE_OPTIMAL STD_OFF

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_TxBufAccessNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_TxBufAccessNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_RxBufAccessNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_RxBufAccessNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_ControllerState(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_ControllerState(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_NewMsgRxWkpEvtNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_NewMsgRxWkpEvtNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_TxRxNotifNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_TxRxNotifNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_DynIdNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_DynIdNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_PNPduStatusNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_PNPduStatusNoNest(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_TxMuxing(void);
LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_TxMuxing(void);

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_TxBufAccessNoNest(void)
{

    __DI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_TxBufAccessNoNest(void)
{

    __EI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_RxBufAccessNoNest(void)
{

    __DI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_RxBufAccessNoNest(void)
{

    __EI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_ControllerState(void)
{

    __DI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_ControllerState(void)
{

    __EI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_NewMsgRxWkpEvtNoNest(void)
{

    __DI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_NewMsgRxWkpEvtNoNest(void)
{

    __EI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_TxRxNotifNoNest(void)
{

    __DI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_TxRxNotifNoNest(void)
{

    __EI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_DynIdNoNest(void)
{

    __DI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_DynIdNoNest(void)
{

    __EI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_PNPduStatusNoNest(void)
{

    __DI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_PNPduStatusNoNest(void)
{

    __EI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Enter_CanIf_TxMuxing(void)
{

     __DI();
}

LOCAL_INLINE FUNC(void, CANIF_CODE) SchM_Exit_CanIf_TxMuxing(void)
{

    __EI();
}

#endif

