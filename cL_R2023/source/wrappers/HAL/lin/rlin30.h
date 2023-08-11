

#ifndef _RLIN30_H
#define _RLIN30_H

#include "rlin30X.h"

extern uint8 ucBytes2Send;
extern uint8 * pucByte2Send;

enum RLIN30_status
{
    RLIN30_busy,
    RLIN30_ready
};

void RLIN30_init(void);
void RLIN30_port_init(void);
void RLIN30_send_string(uint8 send_string[] );
enum RLIN30_status RLIN30_get_status(void);
void RLIN30_table_setup(void);

void RLIN31_init(void);
void RLIN31_port_init(void);

void RLIN30_send_integer(uint16 send_integer);
void RLIN30_send_byte(uint8 send_byte);
void WordIn4AsciiBytesToV24 (uint16 ushInteger);
void ByteIn2AsciiToV24(uint8 ucByte);
void SendStringToV24( uint8 send_bytes );

void WordInAsciiToV24 (uint16 ushInteger);

//void ByteInAsciiToV24 (uint8 ucByteValue);
uint16 LowNibbleToAsciiWord (uint8 ucByteValue);
#endif
