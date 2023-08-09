
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_CFG_SCHM_H
#define DEM_CFG_SCHM_H

#include "SchM_Default.h"

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_Dem_Monitoring(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_Dem_Monitoring(void);

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_Dem_Monitoring(void)
{
	 __DI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_Dem_Monitoring(void)
{
	 __EI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_Dem_Nvm(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_Dem_Nvm(void);

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_Dem_Nvm(void)
{
	 __DI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_Dem_Nvm(void)
{
	 __EI(); //RST Rivian OIL#144 -> here also wrong command. This function is not used, so it's no problem.
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_Dem_Dcm(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_Dem_Dcm(void);

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_Dem_Dcm(void)
{
	 __DI();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_Dem_Dcm(void)
{
	 __EI();
}
#endif

