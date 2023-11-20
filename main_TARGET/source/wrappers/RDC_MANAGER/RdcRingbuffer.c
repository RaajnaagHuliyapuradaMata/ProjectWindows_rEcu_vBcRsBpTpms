#include "Std_Types.hpp"

#include "RdcRingbuffer.hpp"
#include "ata_Rec_X.hpp"

static RdcRb__Struct_Ringbuffer RdcRb__S_RingBuffer;
static void RdcRb__IncrementWritePosition(void);
static void RdcRb__IncrementReadPosition(void);

extern void RdcRb_Init(void){
  uint8 U8_Counter = 0U;
  for(U8_Counter = 0; U8_Counter < sizeof(RdcRb__S_RingBuffer.UN_RxData.U8_RxDataBytes); U8_Counter++){
    RdcRb__S_RingBuffer.UN_RxData.U8_RxDataBytes[U8_Counter] = 0U;
  }
  RdcRb__S_RingBuffer.U8_ReadPosition = 0U;
  RdcRb__S_RingBuffer.U8_WritePosition = 0U;
  RdcRb__S_RingBuffer.U8_CurrentBufferLen = 0U;
}

extern void RdcRb_StoreTelegram(struct rfstruct* PS_TelegramData, uint32* PU32_Timestamp){
  if(RdcRb__S_RingBuffer.U8_CurrentBufferLen < RDCRB__NUMBER_OF_STORED_TELEGRAMS){
   uint8 U8_Counter = 0U;
   uint16 U16_RssiSum = 0U;
   uint8 U8_TelegramBytes = (PS_TelegramData->level < (MAX_SIZE_WS_TELEGRAM - RDCRB_SYNC_BYTES_NUMBER)) ? (PS_TelegramData->level + RDCRB_SYNC_BYTES_NUMBER) : (MAX_SIZE_WS_TELEGRAM - RDCRB_SYNC_BYTES_NUMBER);
   static uint16 U16_TempAvgRssi = 0;
    RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ucaTelegram[0] = RDCRB_SYNC_BYTES_MSB;
    RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ucaTelegram[1] = RDCRB_SYNC_BYTES_LSB;
   for(U8_Counter = RDCRB_SYNC_BYTES_NUMBER; U8_Counter < U8_TelegramBytes; U8_Counter++){
      RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ucaTelegram[U8_Counter] = PS_TelegramData->buffer[U8_Counter - RDCRB_SYNC_BYTES_NUMBER];
   }
   for(U8_Counter = U8_TelegramBytes; U8_Counter < MAX_SIZE_WS_TELEGRAM; U8_Counter++){
      RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ucaTelegram[U8_Counter] = 0U;
   }
    RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ulRxTimeStamp = (*PU32_Timestamp);
   if(PS_TelegramData->rssilvl > 0){
      for(U8_Counter = 0; U8_Counter < ((PS_TelegramData->rssilvl > RB_RS_BUF_LEN) ? RB_RS_BUF_LEN : PS_TelegramData->rssilvl); U8_Counter++){
        U16_RssiSum += PS_TelegramData->rssibuf[PS_TelegramData->rssilvl - U8_Counter - 1];
      }
      U16_TempAvgRssi = (uint16)(U16_RssiSum / ((PS_TelegramData->rssilvl > RB_RS_BUF_LEN) ? RB_RS_BUF_LEN : PS_TelegramData->rssilvl));
   }
    RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].uiRxRSSI = U16_TempAvgRssi;
    RdcRb__IncrementWritePosition();
  }
  else{
  }
}

extern void RdcRb_StoreSimulatedTelegram(Type_SwcApplTpms_stTelegramWS* tSimulatedTelegram){
  RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition] = *tSimulatedTelegram;
  RdcRb__IncrementWritePosition();
}

extern Type_SwcApplTpms_stTelegramWS* RdcRb_ReadTelegram(void){
  Type_SwcApplTpms_stTelegramWS* PS_RxData = &RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_ReadPosition];
  RdcRb__IncrementReadPosition();
  return PS_RxData;
}

extern boolean RdcRb_IsBufferEmpty(void){
  boolean BO_IsBufferEmpty = FALSE;
  if(RdcRb__S_RingBuffer.U8_CurrentBufferLen == 0U){
    BO_IsBufferEmpty = TRUE;
  }
  else{
  }
  return BO_IsBufferEmpty;
}

static void RdcRb__IncrementWritePosition(void){
  if(RdcRb__S_RingBuffer.U8_CurrentBufferLen < RDCRB__NUMBER_OF_STORED_TELEGRAMS){
    RdcRb__S_RingBuffer.U8_CurrentBufferLen++;
  }
  else{
  }
  RdcRb__S_RingBuffer.U8_WritePosition++;
  if(RdcRb__S_RingBuffer.U8_WritePosition >= RDCRB__NUMBER_OF_STORED_TELEGRAMS){
    RdcRb__S_RingBuffer.U8_WritePosition = 0U;
  }
  else{
  }
}

static void RdcRb__IncrementReadPosition(void){
  if(RdcRb__S_RingBuffer.U8_CurrentBufferLen != 0U){
    RdcRb__S_RingBuffer.U8_CurrentBufferLen--;
  }
  else{
  }
  RdcRb__S_RingBuffer.U8_ReadPosition++;
  if(RdcRb__S_RingBuffer.U8_ReadPosition >= RDCRB__NUMBER_OF_STORED_TELEGRAMS){
    RdcRb__S_RingBuffer.U8_ReadPosition = 0U;
  }
  else{
  }
}
