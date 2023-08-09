#ifndef _RLIN30_X_H
#define _RLIN30_X_H

#include "types.h"

extern void csig0_disable(void);
extern void csig0_enable(void);
extern void csig0_init(void);
extern void csig0_4ATAinit(void);

extern uint8 active_xfer_spi(uint8 ucByteValue);

#endif
