#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef CANSM_CFG_SCHM_H
#define CANSM_CFG_SCHM_H

#include "SchM.hpp"
#include "Os.hpp"

#include "CanSM_Cfg.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_BOR_Nw_ModesNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_BOR_Nw_ModesNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_BaudModesNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_BaudModesNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_GetMutexNoNest(void);
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_GetMutexNoNest(void);
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_BOR_Nw_ModesNoNest(void){
   __DI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_BOR_Nw_ModesNoNest(void){
   __EI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_BaudModesNoNest(void){
   __DI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_BaudModesNoNest(void){
   __EI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Enter_CanSM_GetMutexNoNest(void){
   __DI();
}

LOCAL_INLINE FUNC(void, CANSM_CODE) SchM_Exit_CanSM_GetMutexNoNest(void){
   __EI();
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#endif

