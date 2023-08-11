

#include "Starter.h"

# pragma ghs section rodata=".starter"

const tFblBmHdrHeader* pApplicationHeader;

int __usr_init(void)
{
  pApplicationHeader = (uint32)0x20000;
  JSR(pApplicationHeader->bmEntryAddress);
}

# pragma ghs section rodata=default