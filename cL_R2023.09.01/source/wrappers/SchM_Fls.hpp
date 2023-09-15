

#ifndef SCHM_FLS_H
#define SCHM_FLS_H

#include "Os.hpp"

#define SchM_Enter_Fls(Exclusive_Area) SchM_Enter_Fls_##Exclusive_Area();
#define SchM_Exit_Fls(Exclusive_Area) SchM_Exit_Fls_##Exclusive_Area();

LOCAL_INLINE FUNC(void, FLS_CODE) SchM_Enter_Fls_DRIVERSTATE_DATA_PROTECTION(void){
   __DI();
}

LOCAL_INLINE FUNC(void, FLS_CODE) SchM_Exit_Fls_DRIVERSTATE_DATA_PROTECTION(void){
   __EI();
}

#endif

