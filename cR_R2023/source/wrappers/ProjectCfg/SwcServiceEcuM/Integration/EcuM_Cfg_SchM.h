
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef ECUM_CFG_SCHM_H
#define ECUM_CFG_SCHM_H

// ---- Includes --------------------------------------------------------------

// The integrator shall implement the particular services SchM_Enter and SchM_Exit.
//#define SchM_Enter_EcuM(ECUM_RESOURCE)
//#define SchM_Exit_EcuM(ECUM_RESOURCE)

// RST Integration code
#include "Device.h"

#define SchM_Enter_EcuM(FUNCTIONNAME) SchM_Enter_EcuM_ECUM_SCHM_EXCLSV_AREA()
#define SchM_Exit_EcuM(FUNCTIONNAME) SchM_Exit_EcuM_ECUM_SCHM_EXCLSV_AREA()

LOCAL_INLINE FUNC(void, ECUM_CODE) SchM_Enter_EcuM_ECUM_SCHM_EXCLSV_AREA(void);
LOCAL_INLINE FUNC(void, ECUM_CODE) SchM_Exit_EcuM_ECUM_SCHM_EXCLSV_AREA(void);

LOCAL_INLINE FUNC(void, ECUM_CODE) SchM_Enter_EcuM_ECUM_SCHM_EXCLSV_AREA(void)
{
     __DI();
}

LOCAL_INLINE FUNC(void, ECUM_CODE) SchM_Exit_EcuM_ECUM_SCHM_EXCLSV_AREA(void)
{
     __EI();
}
#endif

// -------- END OF FILE -------------------------------------------------------
