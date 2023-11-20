

#ifndef COMM_TYPES_H
#define COMM_TYPES_H

#include "ComStack_Types.hpp"

typedef enum{
   COMM_GATEWAY_TYPE_ACTIVE = 0
   ,  COMM_GATEWAY_TYPE_PASSIVE
}ComM_PncGatewayType;

#define COMM_TX       0

#define COMM_RX        1

#define COMM_EIRA   0

#define COMM_ERA    1

#define COMM_NO_COMMUNICATION        (uint8)(0)
#define COMM_SILENT_COMMUNICATION    (uint8)(1)
#define COMM_FULL_COMMUNICATION        (uint8)(2)

typedef enum{
  COMM_UNINIT = 0
   ,  COMM_INIT
}ComM_InitStatusType;

typedef enum{
   COMM_BUS_TYPE_CAN
   ,  COMM_BUS_TYPE_ETH
   ,  COMM_BUS_TYPE_FR
   ,  COMM_BUS_TYPE_INTERNAL
   ,  COMM_BUS_TYPE_LIN
}ComM_BusType;

typedef enum{
   FULL
   ,  LIGHT
   ,  NONE
   ,  PASSIVE
}ComM_NMVariantType;

typedef enum{
   COMM_NO_COM_NO_PENDING_REQUEST = 0
   ,  COMM_NO_COM_REQUEST_PENDING
   ,  COMM_FULL_COM_NETWORK_REQUESTED
   ,  COMM_FULL_COM_READY_SLEEP
   ,  COMM_SILENT_COM
}ComM_StateType;

typedef enum{
       COMM_PNC_REQUESTED
   ,     COMM_PNC_READY_SLEEP
   ,     COMM_PNC_PREPARE_SLEEP
   ,     COMM_PNC_NO_COMMUNICATION
}ComM_PncModeType;

#endif

