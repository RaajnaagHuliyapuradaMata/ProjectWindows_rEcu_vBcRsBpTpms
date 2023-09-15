//TBD: Remove duplicate headers

#ifndef _SCHM_DEFAULT_H_
#define _SCHM_DEFAULT_H_

#include "Device.hpp"

LOCAL_INLINE FUNC(void, DET_CODE) SCHM_ENTER_DEFAULT(void);
LOCAL_INLINE FUNC(void, DET_CODE) SCHM_EXIT_DEFAULT(void);

LOCAL_INLINE FUNC(void, DET_CODE) SCHM_ENTER_DEFAULT(void){
  __DI();
}

LOCAL_INLINE FUNC(void, DET_CODE) SCHM_EXIT_DEFAULT(void){
  __EI();
}

#endif

