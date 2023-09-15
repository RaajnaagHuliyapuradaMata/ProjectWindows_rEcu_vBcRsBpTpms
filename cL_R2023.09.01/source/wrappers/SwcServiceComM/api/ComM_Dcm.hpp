

#ifndef COMM_DCM_H
#define COMM_DCM_H

#include "ComM_Cfg.hpp"
#include "ComStack_Types.hpp"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

extern void ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel);

extern void ComM_DCM_InactiveDiagnostic(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

