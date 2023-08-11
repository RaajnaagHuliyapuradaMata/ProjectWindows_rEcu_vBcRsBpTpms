

#ifndef COMM_DCM_H
#define COMM_DCM_H

#include "ComM_Cfg.h"
#include "ComStack_Types.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

extern void ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel);

extern void ComM_DCM_InactiveDiagnostic(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

#endif

