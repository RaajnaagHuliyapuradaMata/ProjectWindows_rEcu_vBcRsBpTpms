#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

#include "ComStack_Types.hpp"
#include "Can_GeneralTypes.hpp"

typedef enum{
      CANIF_OFFLINE
   ,  CANIF_TX_OFFLINE
   ,  CANIF_TX_OFFLINE_ACTIVE
   ,  CANIF_ONLINE
   ,  CANIF_TX_TP_ONLINE
   ,  CANIF_TX_USER_TP_ONLINE
}CanIf_PduModeType;

typedef enum{
      CANIF_CS_UNINIT
   ,  CANIF_CS_SLEEP
   ,  CANIF_CS_STARTED
   ,  CANIF_CS_STOPPED
}CanIf_ControllerModeType;

typedef enum{
      CANIF_NO_NOTIFICATION
   ,  CANIF_TX_RX_NOTIFICATION
}CanIf_NotifStatusType;

#endif
