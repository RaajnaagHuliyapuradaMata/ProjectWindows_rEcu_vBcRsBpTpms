

#ifndef COMM_BUSSM_H
#define COMM_BUSSM_H

#include "ComStack_Types.h"
#include "Rte_ComM_Type.h"
#include "ComM_Cfg.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

extern void ComM_BusSM_ModeIndication(NetworkHandleType Channel, ComM_ModeType * ComMode);

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

