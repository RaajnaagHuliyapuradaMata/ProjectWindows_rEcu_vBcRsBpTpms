#ifndef CANTP_TYPES_H
#define CANTP_TYPES_H

#include "ComStack_Types.hpp"

#include "CfgSwcServiceCanTp.hpp"

typedef uint16 CanTp_TickType;
typedef uint8 CanTp_SduIdType;
typedef uint8 CanTp_ChannelIdType;
typedef void (*CanTp_GetSduPairType)(CanTp_SduIdType *TxSduId, CanTp_SduIdType *RxSduId, uint8 Address);

struct CanTp_RxPduStructType{
   const CanTp_SduIdType RxSduId;
   const CanTp_SduIdType TxSduId;
   const CanTp_GetSduPairType GetSduPair;
};

struct CanTp_TxSduStructType{
   const uint8 TX_DL;
   const uint8 BitFields;
   const uint8 Address;
   const uint8 AddressFormatId;
   const uint8 TimeOutId;
   const CanTp_ChannelIdType ChannelId;
   const Type_SwcServiceCom_tIdPdu TxConfirmationId;
   const Type_SwcServiceCom_tIdPdu TxPduId;
   const Type_SwcServiceCom_tIdPdu PduRPduHandleId;
};

struct CanTp_RxSduStructType{
   const uint8 BitFields;
   const uint8 Address;
   const uint8 AddressFormatId;
   const uint8 TimeOutId;
   const uint8 ParamId;
   const CanTp_ChannelIdType ChannelId;
   const Type_SwcServiceCom_tIdPdu TxConfirmationId;
   const Type_SwcServiceCom_tIdPdu TxPduId;
   const Type_SwcServiceCom_tIdPdu PduRPduHandleId;
};

struct CanTp_TimeOutStructType{
   const CanTp_TickType AsArTicks;
   const CanTp_TickType BsBrTicks;
   const CanTp_TickType CsCrTicks;
};

struct CanTp_ParamStructType{
   const uint8 Param[2];
   const uint16 FcWaitMax;
};

typedef struct CanTp_SduPairStructType CanTp_SduPairType;
typedef struct CanTp_RxPduStructType CanTp_RxPduType;
typedef struct CanTp_TxSduStructType CanTp_TxSduType;
typedef struct CanTp_RxSduStructType CanTp_RxSduType;
typedef struct CanTp_TimeOutStructType CanTp_TimeOutType;
typedef struct CanTp_ParamStructType CanTp_ParamType;
typedef struct CanTp_SharedFcStructType CanTp_SharedFcType;

#endif
