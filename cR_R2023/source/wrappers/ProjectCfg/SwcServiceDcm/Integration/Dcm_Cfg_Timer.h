
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DCM_CFG_TIMER_H
#define DCM_CFG_TIMER_H

#if( DCM_CFG_OSTIMER_USE != FALSE )

#error "configure the Os timer macros according to your project requirements and remove this error code"

#include "ComStack_Types.h"

#include "Os.h"

LOCAL_INLINE FUNC(Std_ReturnType,DCM_APPL_CODE) Dcm_GetCounterValue(VAR(CounterType,AUTOMATIC) CounterId, P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) Value);

LOCAL_INLINE FUNC(Std_ReturnType,DCM_APPL_CODE) Dcm_GetCounterValue(VAR(CounterType,AUTOMATIC) CounterId, P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) Value)
{
    VAR(Std_ReturnType,AUTOMATIC) retval_u8;
    VAR(TickType,AUTOMATIC) timer;
    if(GetCounterValue(CounterId, &timer) == E_OK)
    {
    	retval_u8 = E_OK;
    }
    else
    {
    	retval_u8 = E_NOT_OK;
    }
	*Value=(uint32)timer;

    return (retval_u8);
}

#endif
#endif
