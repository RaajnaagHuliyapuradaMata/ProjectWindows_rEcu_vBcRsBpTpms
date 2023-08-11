

#if (!defined NVM_CBK_H_)
#define NVM_CBK_H_

#define NVM_CBK_MAJOR_VERSION    (5u)
#define NVM_CBK_MINOR_VERSION    (7u)
#define NVM_CBK_PATCH_VERSION    (0u)

#define NVM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, NVM_PUBLIC_CODE) NvM_JobEndNotification(void);

extern FUNC(void, NVM_PUBLIC_CODE) NvM_JobErrorNotification(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif

