#ifndef ECUM_CFG_SCHM_H
#define ECUM_CFG_SCHM_H

#include "Device.hpp"

#define SchM_Enter_EcuM(FUNCTIONNAME) SchM_Enter_EcuM_ECUM_SCHM_EXCLSV_AREA()
#define SchM_Exit_EcuM(FUNCTIONNAME) SchM_Exit_EcuM_ECUM_SCHM_EXCLSV_AREA()

LOCAL_INLINE FUNC(void, ECUM_CODE) SchM_Enter_EcuM_ECUM_SCHM_EXCLSV_AREA(void);
LOCAL_INLINE FUNC(void, ECUM_CODE) SchM_Exit_EcuM_ECUM_SCHM_EXCLSV_AREA(void);

LOCAL_INLINE FUNC(void, ECUM_CODE) SchM_Enter_EcuM_ECUM_SCHM_EXCLSV_AREA(void){
     __DI();
}

LOCAL_INLINE FUNC(void, ECUM_CODE) SchM_Exit_EcuM_ECUM_SCHM_EXCLSV_AREA(void){
     __EI();
}

#endif
