

#ifndef COMM_BUSSM_H
#define COMM_BUSSM_H

#include "ComStack_Types.hpp"
#include "Rte_ComM_Type.hpp"
#include "ComM_Cfg.hpp"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

extern void ComM_BusSM_ModeIndication(NetworkHandleType Channel, ComM_ModeType * ComMode);

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

