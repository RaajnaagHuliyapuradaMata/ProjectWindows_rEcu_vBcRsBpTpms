

#ifndef MEMCONVERSION_H
#define MEMCONVERSION_H

#include "types.h"

extern uint32 FblMemGetInteger( uint32 count, const uint8* buffer );
extern void FblMemSetInteger( uint32 count, uint32 input, uint8* buffer );
#endif