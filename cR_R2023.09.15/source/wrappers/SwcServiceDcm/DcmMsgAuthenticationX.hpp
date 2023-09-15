#ifndef _DCM_MSG_AUTH_X_H
#define _DCM_MSG_AUTH_X_H

#include "Types.hpp"

#define MSG_AUTH_SUCCESSFUL 0
#define MSG_REJECTED        1
#define MSG_NO_AUTH_NEEDED  2

#define cSIZE_OF_HASH 16

extern uint8 DcmCheckMessageAuthentication(uint8 ucSid, const uint8* aucMessage, uint16 ushLength);
extern uint8 DcmAppendMessageAuthentication(uint8 ucSid, uint8* aucDataToAdd, uint32 ushLength, uint8* ucResponseMessage);

#endif //_DCM_MSG_AUTH_H