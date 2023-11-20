

#ifndef  COMM_MAIN_H
#define COMM_MAIN_H

#include "ComM_Cfg.hpp"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#if( COMM_ECUC_RB_RTE_IN_USE != STD_ON )
extern FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Can_Network_Channel(void);
#endif

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.hpp"

#endif
