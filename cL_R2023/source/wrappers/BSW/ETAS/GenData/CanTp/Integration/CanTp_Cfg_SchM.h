
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef CANTP_CFG_SCHM_H
#define CANTP_CFG_SCHM_H

LOCAL_INLINE void SchM_Enter_CanTp_EXCLUSIVE_AREA(void);
LOCAL_INLINE void SchM_Exit_CanTp_EXCLUSIVE_AREA(void);

LOCAL_INLINE void SchM_Enter_CanTp_EXCLUSIVE_AREA(void)
{
	
    __DI();
}

LOCAL_INLINE void SchM_Exit_CanTp_EXCLUSIVE_AREA(void)
{
	
    __EI();
}

#endif

