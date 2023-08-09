

#ifndef CANTP_TYPES_H
#define CANTP_TYPES_H

#include "ComStack_Types.h"
#if (!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

typedef uint16 CanTp_TickType;
typedef uint8 CanTp_SduIdType;
typedef uint8 CanTp_ChannelIdType;
typedef void (*CanTp_GetSduPairType)(CanTp_SduIdType *TxSduId, CanTp_SduIdType *RxSduId, uint8 Address);

struct CanTp_RxPduStructType
{
    const CanTp_SduIdType RxSduId;
    const CanTp_SduIdType TxSduId;
    const CanTp_GetSduPairType GetSduPair;
};

struct CanTp_TxSduStructType
{
    const uint8 TX_DL;
    const uint8 BitFields;
    const uint8 Address;
    const uint8 AddressFormatId;
    const uint8 TimeOutId;
    const CanTp_ChannelIdType ChannelId;
    const PduIdType TxConfirmationId;
    const PduIdType TxPduId;
    const PduIdType PduRPduHandleId;
};

struct CanTp_RxSduStructType
{
    const uint8 BitFields;
    const uint8 Address;
    const uint8 AddressFormatId;
    const uint8 TimeOutId;
    const uint8 ParamId;
    const CanTp_ChannelIdType ChannelId;
    const PduIdType TxConfirmationId;
    const PduIdType TxPduId;
    const PduIdType PduRPduHandleId;
};

struct CanTp_TimeOutStructType
{
    const CanTp_TickType AsArTicks;
    const CanTp_TickType BsBrTicks;
    const CanTp_TickType CsCrTicks;
};

struct CanTp_ParamStructType
{
    const uint8 Param[2];
    const uint16 FcWaitMax;
};

struct CanTp_ConfigStructType
{

    const CanTp_ChannelIdType NumberOfChannels;
    const CanTp_SduIdType NumberOfRxPdus;
    const CanTp_SduIdType NumberOfTxPdus;
    const CanTp_SduIdType NumberOfRxSdus;
    const CanTp_SduIdType NumberOfTxSdus;

    const struct CanTp_RxPduStructType *RxPdu;
    const struct CanTp_TxSduStructType *TxSdu;
    const struct CanTp_RxSduStructType *RxSdu;
    const struct CanTp_TimeOutStructType *TimeOut;
    const struct CanTp_ParamStructType *Param;
};

typedef struct CanTp_SduPairStructType CanTp_SduPairType;
typedef struct CanTp_RxPduStructType CanTp_RxPduType;
typedef struct CanTp_TxSduStructType CanTp_TxSduType;
typedef struct CanTp_RxSduStructType CanTp_RxSduType;
typedef struct CanTp_TimeOutStructType CanTp_TimeOutType;
typedef struct CanTp_ParamStructType CanTp_ParamType;
typedef struct CanTp_SharedFcStructType CanTp_SharedFcType;

#endif
