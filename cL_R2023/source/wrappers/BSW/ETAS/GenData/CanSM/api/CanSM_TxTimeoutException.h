
#ifndef  CANSM_TXTIMEOUTEXCEPTION_H
#define  CANSM_TXTIMEOUTEXCEPTION_H

#include "CanSM_Cfg.h"
#include "ComM.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
extern void CanSM_TxTimeoutException(NetworkHandleType Channel);
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

#endif
