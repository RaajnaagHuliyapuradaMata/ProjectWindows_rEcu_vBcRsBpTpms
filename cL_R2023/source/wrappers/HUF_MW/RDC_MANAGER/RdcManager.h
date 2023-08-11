

#ifndef RDC_MANAGER_H
#define RDC_MANAGER_H

#include "RdcManagerX.h"

#define RDC__MSB_OF_ID_POS              ((uint8) 1U)            //!< Position of the MSB of the ID within the RF telegram. Sync bytes not present at this time.
#define RDC__VALID_MSB_OF_ID_START      ((uint8) 0x20U)         //!< Start of the valid values of the MSB of the ID.
#define RDC__VALID_MSB_OF_ID_END        ((uint8) 0x2FU)         //!< End of the valid values of the MSB of the ID.

#define RDC__NUMBER_OF_WS               ((uint8) 4U)            //!< Number of WS for which autolearned IDs are checked.
#define RDC__TIMESTAMP_INIT             ((uint32) 0x00000000UL) //!< Timestamp starting value.
#define RDC__WS_ID_INIT                 ((uint32) 0x00000000UL) //!< WS ID starting value.
#define RDC__WS_PCK_ID_INIT             ((uint8) 0xFFU)         //!< Packet ID starting value.
#define RDC__GLOBAL_NVM_INDEX           ((uint8) 26U)           //!< NvM Index where the autolearned IDs are found.
#define RDC__MINIMUM_TIME_DIF_MS        ((uint16) 400U)         //!< Minimum time difference between RF frames to forward (must be <500 because DP telegrams have 0.5s cycle)
#define RDC__PACKET_ID_POS              ((uint8) 0U)            //!< Position of the packet ID within the RF telegram. Sync bytes not present at this time.

#define RDC__CGM_TIMESTAMP_INIT         ((uint64) 0ULL)         //!< CGM timestamp init value.
#define RDC__WHEEL_PULSE_TRAVEL_TIME_MS ((uint32) 12UL)         //!< Travel time of WheelPulse CAN message from ABS ECU to CGM. */
#define RDC__LEARN_TELEGRAM_PACKAGE_ID  ((uint8) 0xE7)

typedef struct{
  uint32 U32_WsId;
  uint32 U32_Timestamp;
  uint8 U8_PacketID;
} Rdc__Struct_WsLastTelegramData;

#endif
