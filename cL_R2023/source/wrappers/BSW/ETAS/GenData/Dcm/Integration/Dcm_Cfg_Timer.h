
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DCM_CFG_TIMER_H
#define DCM_CFG_TIMER_H

#if( DCM_CFG_OSTIMER_USE != FALSE )

#error "configure the Os timer macros according to your project requirements and remove this error code"

#include "ComStack_Types.h"

#include "Os.h"

LOCAL_INLINE Std_ReturnType Dcm_GetCounterValue(CounterType CounterId, uint32 * Value);

LOCAL_INLINE Std_ReturnType Dcm_GetCounterValue(CounterType CounterId, uint32 * Value)
{
    Std_ReturnType retval_u8;
    TickType timer;
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
