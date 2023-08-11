#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

typedef enum {
    CANIF_OFFLINE = 0,
    CANIF_TX_OFFLINE = 1,
    CANIF_TX_OFFLINE_ACTIVE = 2,
    CANIF_ONLINE = 3,
    CANIF_TX_TP_ONLINE = 4,
    CANIF_TX_USER_TP_ONLINE = 5
}CanIf_PduModeType;

typedef enum {
    CANIF_CS_UNINIT = 0,
    CANIF_CS_SLEEP,
    CANIF_CS_STARTED,
    CANIF_CS_STOPPED
}CanIf_ControllerModeType;

typedef enum {
    CANIF_NO_NOTIFICATION = 0,
    CANIF_TX_RX_NOTIFICATION
}CanIf_NotifStatusType;

#endif
