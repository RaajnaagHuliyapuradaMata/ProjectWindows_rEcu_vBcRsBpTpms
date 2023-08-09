
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef FIM_CFG_SCHM_H
#define FIM_CFG_SCHM_H

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_FiM_Monitor_NoNest(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_FiM_Monitor_NoNest(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_FiM_Status_NoNest(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_FiM_Status_NoNest(void);

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_FiM_Monitor_NoNest(void)
{
	 __DI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_FiM_Monitor_NoNest(void)
{
	 __EI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_FiM_Status_NoNest(void)
{
	 __DI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_FiM_Status_NoNest(void)
{
	 __EI();
}

#endif

