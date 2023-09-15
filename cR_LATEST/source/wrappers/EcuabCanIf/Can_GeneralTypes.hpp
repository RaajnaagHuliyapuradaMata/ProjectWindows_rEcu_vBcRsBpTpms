#ifndef CAN_GENERAL_TYPES_H
#define CAN_GENERAL_TYPES_H

#include "ComStack_Types.hpp"

typedef uint32 Can_IdType;
typedef uint16 Can_HwHandleType;

typedef struct{
   Can_IdType       CanId;
   Can_HwHandleType Hoh;
   uint8            ControllerId;
}Can_HwType;

typedef struct{
   P2VAR(uint8,TYPEDEF,CAN_UPPER_READONLY) sdu;
   Can_IdType                              id;
   Type_SwcServiceCom_tIdPdu               swPduHandle;
   uint8                                   length;
}Can_PduType;

typedef enum{
      CAN_T_START
   ,  CAN_T_STOP
   ,  CAN_T_SLEEP
   ,  CAN_T_WAKEUP
   ,  CAN_T_MAXTRANSITION
}Can_StateTransitionType;

typedef enum{
      CAN_OK
   ,  CAN_NOT_OK
   ,  CAN_BUSY
}Can_ReturnType;

typedef enum{
      CANTRCV_TRCVMODE_NORMAL
   ,  CANTRCV_TRCVMODE_SLEEP
   ,  CANTRCV_TRCVMODE_STANDBY
}CanTrcv_TrcvModeType;

typedef enum{
      CANTRCV_WUMODE_ENABLE
   ,  CANTRCV_WUMODE_DISABLE
   ,  CANTRCV_WUMODE_CLEAR
}CanTrcv_TrcvWakeupModeType;

typedef enum{
      CANTRCV_WU_ERROR
   ,  CANTRCV_WU_NOT_SUPPORTED
   ,  CANTRCV_WU_BY_BUS
   ,  CANTRCV_WU_INTERNALLY
   ,  CANTRCV_WU_RESET
   ,  CANTRCV_WU_POWER_ON
   ,  CANTRCV_WU_BY_PIN
}CanTrcv_TrcvWakeupReasonType;
#endif

