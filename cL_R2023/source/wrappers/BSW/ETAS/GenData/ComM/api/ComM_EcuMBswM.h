

#ifndef COMM_ECUMBSWM_H
#define COMM_ECUMBSWM_H

#include "ComStack_Types.h"
#include "ComM_Cfg.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

extern void ComM_EcuM_WakeUpIndication(NetworkHandleType Channel);

extern void ComM_EcuM_PNCWakeUpIndication(PNCHandleType PNCid);

extern void ComM_CommunicationAllowed(NetworkHandleType Channel, boolean Allowed);

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

