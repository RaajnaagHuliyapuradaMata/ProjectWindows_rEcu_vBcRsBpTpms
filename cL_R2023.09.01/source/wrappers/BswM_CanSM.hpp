#ifndef _BSWM_CANSM_H_
#define _BSWM_CANSM_H_

#include "CanSM_Bswm.hpp"

#define BSWM_AR_RELEASE_MAJOR_VERSION  4
#define BSWM_AR_RELEASE_MINOR_VERSION  2

void BswM_CanSM_CurrentState(uint8 ucComM_channelId, CanSM_BswMCurrentStateType eCanSM_BswM_Mode);

#endif
