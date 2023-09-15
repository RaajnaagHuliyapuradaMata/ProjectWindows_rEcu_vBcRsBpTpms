#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef CANTP_TIMER_H
#define CANTP_TIMER_H

#include "Os.hpp"
#include "CanTp.hpp"

#if(CANTP_CYCLE_COUNTER != CANTP_ON)

#define CANTP_MCU_TIMER

#if(defined(CANTP_MCU_TIMER))
#include "types.hpp" //TBD: Remove
#include "CfgMcalMcu.hpp"
#endif

LOCAL_INLINE void CanTp_GetElapsedValue(TickType *Value, TickType *ElapsedValue)
{
#if(!defined(CANTP_MCU_TIMER))

    (void)GetElapsedValue(SystemTimer, Value, ElapsedValue);

#else
   volatile TickType ValueIn = *Value;

    *Value = (TickType)Mcu_Rn_GetSysTicks();

    *ElapsedValue = *Value - ValueIn;

#endif
}
#endif

#endif
