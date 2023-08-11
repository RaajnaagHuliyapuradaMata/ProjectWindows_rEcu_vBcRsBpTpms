#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef CAN_GENERAL_TYPES_H
#define CAN_GENERAL_TYPES_H

#include "ComStack_Types.h"

typedef uint32 Can_IdType;
typedef uint16 Can_HwHandleType;

typedef struct{
    Can_IdType CanId;
    Can_HwHandleType Hoh;
    uint8      ControllerId;
}Can_HwType;

typedef struct{
    uint8 * sdu;
    Can_IdType id;
    PduIdType  swPduHandle;
    uint8      length;
}Can_PduType;

typedef enum {
    CAN_T_START,
    CAN_T_STOP,
    CAN_T_SLEEP,
    CAN_T_WAKEUP,
    CAN_T_MAXTRANSITION
}Can_StateTransitionType;

typedef enum {
    CAN_OK,
    CAN_NOT_OK,
    CAN_BUSY
}Can_ReturnType;

#if defined(CORE_M4_DME)
#else
#define CANIF_SHARED_SYMBOL (1u)
#endif

typedef enum {
    CANTRCV_TRCVMODE_NORMAL=0,
    CANTRCV_TRCVMODE_SLEEP,
    CANTRCV_TRCVMODE_STANDBY
}CanTrcv_TrcvModeType;

typedef enum {
    CANTRCV_WUMODE_ENABLE=0,
    CANTRCV_WUMODE_DISABLE,
    CANTRCV_WUMODE_CLEAR
}CanTrcv_TrcvWakeupModeType;

typedef enum {
    CANTRCV_WU_ERROR=0,
    CANTRCV_WU_NOT_SUPPORTED,
    CANTRCV_WU_BY_BUS,
    CANTRCV_WU_INTERNALLY,
    CANTRCV_WU_RESET,
    CANTRCV_WU_POWER_ON,
    CANTRCV_WU_BY_PIN
}CanTrcv_TrcvWakeupReasonType;
#endif

