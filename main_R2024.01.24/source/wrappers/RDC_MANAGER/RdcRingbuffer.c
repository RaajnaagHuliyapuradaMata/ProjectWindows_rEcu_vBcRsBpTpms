#include "Std_Types.hpp"

#include "RdcRingbuffer.hpp"
#include "CfgSwcServiceStartUp.hpp"

static RdcRb__Struct_Ringbuffer RdcRb__S_RingBuffer;

static void RdcRb__IncrementWritePosition (void);
static void RdcRb__IncrementReadPosition  (void);

void RdcRb_Init(void){
  uint8 U8_Counter = 0U;
  for(U8_Counter = 0; U8_Counter < sizeof(RdcRb__S_RingBuffer.UN_RxData.U8_RxDataBytes); U8_Counter++){
    RdcRb__S_RingBuffer.UN_RxData.U8_RxDataBytes[U8_Counter] = 0U;
  }
  RdcRb__S_RingBuffer.U8_ReadPosition = 0U;
  RdcRb__S_RingBuffer.U8_WritePosition = 0U;
  RdcRb__S_RingBuffer.U8_CurrentBufferLen = 0U;
}

#include "TypesMcalAtaRfd.hpp"
void RdcRb_StoreTelegram(TypeMcalAtaRfd_stTelegram* pstTelegram, uint32* PU32_Timestamp){
  if(RdcRb__S_RingBuffer.U8_CurrentBufferLen < RDCRB__NUMBER_OF_STORED_TELEGRAMS){
   uint8 U8_Counter = 0U;
   uint16 U16_RssiSum = 0U;
   uint8 U8_TelegramBytes = (pstTelegram->level < (MAX_SIZE_WS_TELEGRAM - RDCRB_SYNC_BYTES_NUMBER)) ? (pstTelegram->level + RDCRB_SYNC_BYTES_NUMBER) : (MAX_SIZE_WS_TELEGRAM - RDCRB_SYNC_BYTES_NUMBER);
   static uint16 U16_TempAvgRssi = 0;
   RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ucaTelegram[0] = RDCRB_SYNC_BYTES_MSB;
   RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ucaTelegram[1] = RDCRB_SYNC_BYTES_LSB;
   for(U8_Counter = RDCRB_SYNC_BYTES_NUMBER; U8_Counter < U8_TelegramBytes; U8_Counter++){
      RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ucaTelegram[U8_Counter] = pstTelegram->buffer[U8_Counter - RDCRB_SYNC_BYTES_NUMBER];
   }
   for(U8_Counter = U8_TelegramBytes; U8_Counter < MAX_SIZE_WS_TELEGRAM; U8_Counter++){
      RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ucaTelegram[U8_Counter] = 0U;
   }
    RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].ulRxTimeStamp = (*PU32_Timestamp);
   if(pstTelegram->rssilvl > 0){
      for(U8_Counter = 0; U8_Counter < ((pstTelegram->rssilvl > McalAtaRfd_dLenBufRssiRB) ? McalAtaRfd_dLenBufRssiRB : pstTelegram->rssilvl); U8_Counter++){
        U16_RssiSum += pstTelegram->rssibuf[pstTelegram->rssilvl - U8_Counter - 1];
      }
      U16_TempAvgRssi = (uint16)(U16_RssiSum / ((pstTelegram->rssilvl > McalAtaRfd_dLenBufRssiRB) ? McalAtaRfd_dLenBufRssiRB : pstTelegram->rssilvl));
   }
    RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition].uiRxRSSI = U16_TempAvgRssi;
    RdcRb__IncrementWritePosition();
  }
  else{
  }
}

void RdcRb_StoreSimulatedTelegram(tsWS_RxDataIn* tSimulatedTelegram){
  RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_WritePosition] = *tSimulatedTelegram;
  RdcRb__IncrementWritePosition();
}

tsWS_RxDataIn* RdcRb_ReadTelegram(void){
  tsWS_RxDataIn* PS_RxData = &RdcRb__S_RingBuffer.UN_RxData.AS_RxData[RdcRb__S_RingBuffer.U8_ReadPosition];
  RdcRb__IncrementReadPosition();
  return PS_RxData;
}

boolean RdcRb_IsBufferEmpty(void){
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
