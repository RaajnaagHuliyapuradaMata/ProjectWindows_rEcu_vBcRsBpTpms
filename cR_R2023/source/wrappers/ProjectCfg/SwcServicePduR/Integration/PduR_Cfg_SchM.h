
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef PDUR_CFG_SCHM_H
#define PDUR_CFG_SCHM_H

#include "SchM.h"
#include "rba_BswSrv.h"
#include "Os.h"

#if ( PDUR_ECUC_RB_RTE_IN_USE == STD_ON )

#include "SchM_PduR.h"
#endif

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockTpGatewayBuffer(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockTpGatewayBuffer(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockDisableRoutingNoNest(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockDisableRoutingNoNest(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockEnableRoutingNoNest(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockEnableRoutingNoNest(void);

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockIFGatewayTx(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockIFGatewayTx(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockIFGatewayTxConf(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockIFGatewayTxConf(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockTpGatewayCopyRxData(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockTpGatewayCopyRxData(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockTpGatewayCopyTxDataNoNest(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockTpGatewayCopyTxDataNoNest(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockIFGatewayTriggerTxConf(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockIFGatewayTriggerTxConf(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockMcTpTxCopyTxData(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockMcTpTxCopyTxData(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockMcTpTxConf(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockMcTpTxConf(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockMCTxConfNoNest(void);
LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockMCTxConfNoNest(void);

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockIFGatewayTx(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockIFGatewayTx(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockIFGatewayTxConf(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockIFGatewayTxConf(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockIFGatewayTriggerTxConf(void)
{
      __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockIFGatewayTriggerTxConf(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockEnableRoutingNoNest(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockDisableRoutingNoNest(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockDisableRoutingNoNest(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockMCTxConfNoNest(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockMCTxConfNoNest(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockEnableRoutingNoNest(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockTpGatewayBuffer(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockTpGatewayBuffer(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockTpGatewayCopyRxData(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockTpGatewayCopyRxData(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockMcTpTxCopyTxData(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockMcTpTxCopyTxData(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockMcTpTxConf(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockMcTpTxConf(void)
{
     __EI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Enter_PduR_LockTpGatewayCopyTxDataNoNest(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, PDUR_CODE) SchM_Exit_PduR_LockTpGatewayCopyTxDataNoNest(void)
{
     __EI();
}

#endif

