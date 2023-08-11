
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef COMM_CFG_SCHM_H
#define COMM_CFG_SCHM_H

#if ( COMM_ECUC_RB_RTE_IN_USE == STD_ON )

#include "SchM_ComM.h"
#endif

LOCAL_INLINE void SchM_Enter_ComM_UserNoNest(void);
LOCAL_INLINE void SchM_Exit_ComM_UserNoNest(void);

LOCAL_INLINE void SchM_Enter_ComM_ChannelNoNest(void);
LOCAL_INLINE void SchM_Exit_ComM_ChannelNoNest(void);

LOCAL_INLINE void SchM_Enter_ComM_EIRANoNest(void);
LOCAL_INLINE void SchM_Exit_ComM_EIRANoNest(void);

LOCAL_INLINE void SchM_Enter_ComM_ERANoNest(void);
LOCAL_INLINE void SchM_Exit_ComM_ERANoNest(void);

LOCAL_INLINE void SchM_Enter_ComM_PNCNoNest(void);
LOCAL_INLINE void SchM_Exit_ComM_PNCNoNest(void);

LOCAL_INLINE void SchM_Enter_ComM_PNCTxSigNoNest(void);
LOCAL_INLINE void SchM_Exit_ComM_PNCTxSigNoNest(void);

LOCAL_INLINE void SchM_Enter_ComM_PNCWakeUpNoNest(void);
LOCAL_INLINE void SchM_Exit_ComM_PNCWakeUpNoNest(void);

LOCAL_INLINE void SchM_Enter_ComM_LimitationNoNest(void);
LOCAL_INLINE void SchM_Exit_ComM_LimitationNoNest(void);

LOCAL_INLINE void SchM_Enter_ComM_Channel(void);
LOCAL_INLINE void SchM_Exit_ComM_Channel(void);

LOCAL_INLINE void SchM_Enter_ComM_FullComRequestors(void);
LOCAL_INLINE void SchM_Exit_ComM_FullComRequestors(void);

LOCAL_INLINE void SchM_Enter_ComM_PNCTxSigNoNest(void)
{

	 __DI();
}

LOCAL_INLINE void SchM_Exit_ComM_PNCTxSigNoNest(void)
{
	__EI();
}

LOCAL_INLINE void SchM_Enter_ComM_PNCNoNest(void)
{

	 __DI();
}

LOCAL_INLINE void SchM_Exit_ComM_PNCNoNest(void)
{
	__EI();
}

LOCAL_INLINE void SchM_Enter_ComM_EIRANoNest(void)
{

	 __DI();
}

LOCAL_INLINE void SchM_Exit_ComM_EIRANoNest(void)
{
	__EI();
}

LOCAL_INLINE void SchM_Enter_ComM_ERANoNest(void)
{

	 __DI();
}

LOCAL_INLINE void SchM_Exit_ComM_ERANoNest(void)
{
	__EI();
}

LOCAL_INLINE void SchM_Enter_ComM_PNCWakeUpNoNest(void)
{

	 __DI();
}

LOCAL_INLINE void SchM_Exit_ComM_PNCWakeUpNoNest(void)
{
	__EI();
}

LOCAL_INLINE void SchM_Enter_ComM_UserNoNest(void)
{

	__DI();
}

LOCAL_INLINE void SchM_Exit_ComM_UserNoNest(void)
{
	__EI();
}

LOCAL_INLINE void SchM_Enter_ComM_ChannelNoNest(void)
{

	 __DI();
}

LOCAL_INLINE void SchM_Exit_ComM_ChannelNoNest(void)
{
	__EI();
}

LOCAL_INLINE void SchM_Enter_ComM_LimitationNoNest(void)
{

	 __DI();
}
LOCAL_INLINE void SchM_Exit_ComM_LimitationNoNest(void)
{
	__EI();
}
LOCAL_INLINE void SchM_Enter_ComM_Channel(void)
{

	 __DI();
}
LOCAL_INLINE void SchM_Exit_ComM_Channel(void)
{
	__EI();
}
LOCAL_INLINE void SchM_Enter_ComM_FullComRequestors(void)
{

	 __DI();
}
LOCAL_INLINE void SchM_Exit_ComM_FullComRequestors(void)
{
	__EI();
}
#endif

