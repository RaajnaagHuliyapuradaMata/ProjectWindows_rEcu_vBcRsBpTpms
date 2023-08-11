#include "device.h"
#include "rlin30.h"

#ifdef SPI4MFA

void csig0_disable()
{
  CSIG0CTL0  = 0x01;           // disable CSI SPI
}

void csig0_enable()
{
  CSIG0CTL0 |= 0xE0;           // enable CSIG, receive and transmit mode
}

void csig0_4ATAinit()
{

  CSIG0CTL0  = 0x01;           // SPI Control Register 0 disable CSI
  CSIG0CTL1  =(1<< 17);      // 0x0002 00xx hex SPI Control Register 1 Bit17=CSIGnCKR=1 ->SCLK start L to H
  CSIG0CTL2  = 0x4014;       // SPI Control Register 2 80MHz/((2^4)*2*20) = 0,5 MHz
  CSIG0CFG0  = 0x08010000;     // Bit27= 8Bit Transfer, Bit16=DAP Bit S.610 RH850 F1L data latch at risk edge
  CSIG0STCR0 = 0xff;           // SPI Status Register 0 clear status
  CSIG0CTL0 |= 0xE0;           // SPI Control Register 0 enable CSIG, receive and transmit mode
}

uint8 active_xfer_spi(uint8 ucByteValue)
{

  uint16 timeout=500;
  timeout=(timeout*10)-5;

  CSIG0TX0H = ucByteValue;
  while(((CSIG0STR0 & 0x80) == 0x80) && (timeout-- >0));

  return ((uint8)CSIG0RX0);
 }

#endif
