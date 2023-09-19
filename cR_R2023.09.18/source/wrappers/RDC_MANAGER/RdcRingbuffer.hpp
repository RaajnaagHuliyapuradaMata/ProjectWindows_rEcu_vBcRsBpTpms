

#ifndef RDC_RINGBUFFER_H
#define RDC_RINGBUFFER_H

#include "RdcRingbufferX.hpp"

#include "iTpms_Interface.hpp"

#define RDCRB__NUMBER_OF_STORED_TELEGRAMS           ((uint8) 10U)        //!< Buffer size.

#define RDCRB_SYNC_BYTES_NUMBER                     ((uint8) 0x02U)     //!< Number of sync bytes which have to be added.
#define RDCRB_SYNC_BYTES_MSB                        ((uint8) 0xFFU)     //!< MSB of the sync bytes.
#define RDCRB_SYNC_BYTES_LSB                        ((uint8) 0xF2U)     //!< LSB of the sync bytes.

typedef struct{
  union
  {
    tsWS_RxDataIn AS_RxData[RDCRB__NUMBER_OF_STORED_TELEGRAMS];
   uint8 U8_RxDataBytes[RDCRB__NUMBER_OF_STORED_TELEGRAMS * sizeof(tsWS_RxDataIn)];
  }UN_RxData;
  uint8 U8_ReadPosition;
  uint8 U8_WritePosition;
  uint8 U8_CurrentBufferLen;
}RdcRb__Struct_Ringbuffer;

#endif
