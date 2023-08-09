#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef COM_CFG_SCHM_H
#define COM_CFG_SCHM_H

#include "SchM.h"

#if ( COM_ECUC_RB_RTE_IN_USE == STD_ON )

#include "SchM_Com.h"
#endif

#define SchM_Enter_Com_TxIpduProtArea(FUNCTIONNAME) SchM_Enter_Com_TxIpduProtArea_##FUNCTIONNAME()
#define SchM_Exit_Com_TxIpduProtArea(FUNCTIONNAME) SchM_Exit_Com_TxIpduProtArea_##FUNCTIONNAME()

#define SchM_Enter_Com_RxSigBuff(FUNCTIONNAME) SchM_Enter_Com_RxSigBuff_##FUNCTIONNAME()
#define SchM_Exit_Com_RxSigBuff(FUNCTIONNAME) SchM_Exit_Com_RxSigBuff_##FUNCTIONNAME()

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_INVALIDATESIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_INVALIDATESIGNAL(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONTX(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONTX(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDDYNSIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDDYNSIGNAL(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_DATA(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_DATA(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNAL(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNALGRP(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNALGRP(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERTRANSMIT(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERTRANSMIT(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SIGTXCHANGEMODE(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SIGTXCHANGEMODE(void);

#if (defined(COM_TxFilters) && defined(COM_TX_SIGNALGROUP))
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SIGGRPTXCHANGEMODE(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SIGGRPTXCHANGEMODE(void);
#endif

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TXCONFIRMATION(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TXCONFIRMATION(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxPduBuffer(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxPduBuffer(void);

#ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxGrpSigBuffer(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxGrpSigBuffer(void);
#endif

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxGrpSigSecBuff (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxGrpSigSecBuff (void);
#endif

#if defined( COM_RX_SIGNALGROUP_ARRAY )
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGrpArrayBuff( void );
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGrpArrayBuff( void );
#endif

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxGrpSigBuff(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxGrpSigBuff (void);
#endif

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_MAINFUNCTIONRX (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_MAINFUNCTIONRX (void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RECEIVESIGNAL (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RECEIVESIGNAL  (void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RXINDICATION (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RXINDICATION (void);

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigDynBuff (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigDynBuff (void);
#endif

#ifdef COM_RxSigUpdateTimeout
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigToTicks (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigToTicks (void);
#endif

#ifdef COM_RxSigGrpUpdateTimeout
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGrpToTicks(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGrpToTicks(void);
#endif

#ifdef COM_SIGNALGATEWAY
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGwQueueProtArea (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGwQueueProtArea (void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGwMcLockProtArea (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGwMcLockProtArea (void);

#endif

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_INVALIDATESIGNAL (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif

}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_INVALIDATESIGNAL (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif

}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif

}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONTX(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONTX(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDDYNSIGNAL(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDDYNSIGNAL(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_DATA(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_DATA(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNAL(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNAL(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNALGRP(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNALGRP(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERTRANSMIT(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERTRANSMIT(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SIGTXCHANGEMODE(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SIGTXCHANGEMODE(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

#if (defined(COM_TxFilters) && defined(COM_TX_SIGNALGROUP))

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SIGGRPTXCHANGEMODE(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SIGGRPTXCHANGEMODE(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}
#endif

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TXCONFIRMATION(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TXCONFIRMATION(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}

#ifdef COM_TX_SIGNALGROUP

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxGrpSigBuffer(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxGrpSigBuffer(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_TX_CFG

#else
     __EI();
#endif
}
#endif

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxPduBuffer(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxPduBuffer(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}

#ifdef COM_RxSigUpdateTimeout

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigToTicks (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigToTicks (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}
#endif

#ifdef COM_RxSigGrpUpdateTimeout

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGrpToTicks (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGrpToTicks (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}
#endif

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_MAINFUNCTIONRX (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_MAINFUNCTIONRX (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RXINDICATION (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RXINDICATION (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RECEIVESIGNAL (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RECEIVESIGNAL  (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigDynBuff (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigDynBuff (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}
#endif

#ifdef COM_RX_SIGNALGROUP

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxGrpSigSecBuff (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxGrpSigSecBuff(void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}
#endif

#if defined( COM_RX_SIGNALGROUP_ARRAY )

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGrpArrayBuff( void )
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGrpArrayBuff( void )
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}
#endif

#ifdef COM_RX_SIGNALGROUP

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxGrpSigBuff (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxGrpSigBuff (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}
#endif

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGwQueueProtArea (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGwQueueProtArea (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGwMcLockProtArea (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __DI();
#endif
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGwMcLockProtArea (void)
{
#ifdef COM_MULTIPLE_MAINFUNCTION_RX_CFG

#else
     __EI();
#endif
}
#endif

#endif

