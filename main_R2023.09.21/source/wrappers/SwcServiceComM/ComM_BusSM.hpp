

#ifndef COMM_BUSSM_H
#define COMM_BUSSM_H

#include "ComStack_Types.hpp"
#include "Rte_ComM_Type.hpp"
#include "ComM_Cfg.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

extern FUNC(void,COMM_CODE) ComM_BusSM_ModeIndication
                                        (
                                            VAR(NetworkHandleType,AUTOMATIC ) Channel
   ,     P2VAR(ComM_ModeType,AUTOMATIC,COMM_APPL_DATA) ComMode
                                        );

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif

