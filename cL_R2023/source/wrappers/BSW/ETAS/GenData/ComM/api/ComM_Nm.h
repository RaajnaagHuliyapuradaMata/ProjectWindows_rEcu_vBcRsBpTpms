

#ifndef COMM_NM_H
#define COMM_NM_H

#include "ComM_Cfg.h"
#include "ComStack_Types.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

extern void ComM_Nm_NetworkStartIndication(NetworkHandleType Channel);

extern void ComM_Nm_BusSleepMode(NetworkHandleType Channel);

extern void ComM_Nm_NetworkMode(NetworkHandleType Channel);

extern void ComM_Nm_RestartIndication(NetworkHandleType Channel);

extern void ComM_Nm_PrepareBusSleepMode(NetworkHandleType Channel);

extern void ComM_Nm_TransmissionFailure(NetworkHandleType Channel_tu8);

extern void ComM_Nm_NetworkTimeoutException(NetworkHandleType Channel_tu8);

extern void ComM_Nm_RxIndication(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

