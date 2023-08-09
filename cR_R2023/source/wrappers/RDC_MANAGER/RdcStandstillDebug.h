
#ifndef RDC_STANDSTILL_DEBUG_H
#define RDC_STANDSTILL_DEBUG_H

#include "RdcStandstillDebugX.h"

//Size of message fifo for Standstillmonitoring debug messages
#define cSIZE_SSM_MESSAGE_FIFO  15

// report all filter events in the chain, beginning from this event.
// E.g. if this value is cTGFILTER_RBFULL, then the events cTGFILTER_LENGTH to cTGFILTER_NOTINHISTORY will not be reported, no message will be sent on these events.
#define cFILTER_CHAIN_START     cTGFILTER_0x90_WHILE_DRIVING

#endif