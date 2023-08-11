

#ifndef _RSCAN_X_H_
#define _RSCAN_X_H_

#include "types.h"

#define CAN_RTN_OK                          0U
#define CAN_RTN_FIFO_FULL                   1U
#define CAN_RTN_BUFFER_EMPTY                2U
#define CAN_RTN_ERR                         255U

typedef struct{
    uint32 ID    :29;
    uint32 THLEN :1;        // RST: this is not used in RSCAN. This bit is reserved in the RMID register.
    uint32 RTR   :1;
    uint32 IDE   :1;
    uint32 TS    :16;
    uint32 LBL   :12;
    uint32 DLC   :4;
    uint8  DB[8];
} Can_FrameType;

typedef uint8 Can_RtnType;

extern void RS_CAN_Init(void);
extern void RS_CAN_SetCommunicationMode(void);
extern void RS_CAN_SetResetMode(void);
extern void RS_CAN_SetSleepMode(void);

extern Can_RtnType Can_ReadRxFiFo(Can_FrameType* pFrame);
extern Can_RtnType Can_SendTxBuffer(const Can_FrameType* pFrame);

extern void Can_ClearRxFiFoInterruptFlag(void);
extern void Can_ClearTxBufferInterruptFlag(void);

//extern void RS_CAN_InitForRxFifoUsage(void);
//extern Can_RtnType Can_C0TrmByTxBuf(uint8 TxBufIdx, const Can_FrameType* pFrame);
//extern Can_RtnType Can_ReadRxBuffer(Can_FrameType* pFrame);

#endif

