

#ifndef CANTP_PRV_H
#define CANTP_PRV_H

#include "CanTp.h"
#if(CANTP_CYCLE_COUNTER != CANTP_ON)
#include "CanTp_Timer.h"
#endif
#include "CanTp_Types.h"
#if(CANTP_SCHM_SUPPORT != CANTP_ON)
#include "CanTp_SchM.h"
#else
#include "SchM_CanTp.h"
#endif
#include "PduR_CanTp.h"
#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "CanIf.h"
#if (!defined(CANIF_AR_RELEASE_MAJOR_VERSION) || (CANIF_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANIF_AR_RELEASE_MINOR_VERSION) || (CANIF_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#define CANTP_SF_HIGHNIBBLE                          (0x00u)
#define CANTP_FF_HIGHNIBBLE                          (0x10u)
#define CANTP_CF_HIGHNIBBLE                          (0x20u)
#define CANTP_FC_HIGHNIBBLE                          (0x30u)

#define CANTP_DEFAULT_CAN_DL                         (8u)
#define CANTP_DLCERROR                               (0xFFu)
#define CANTP_NO_ERROR                               (0u)

#define CANTP_CF_PCISIZE                             (1u)
#define CANTP_FC_PCISIZE                             (3u)

#define CANTP_NPCI_SFCAN                             (0u)
#define CANTP_NPCI_SFCANFD                           (1u)
#define CANTP_NPCI_FFCAN                             (2u)
#define CANTP_NPCI_FFCANFD                           (3u)
#define CANTP_NPCI_CF                                (4u)
#define CANTP_NPCI_FC                                (5u)
#define CANTP_NPCI_INVALID                           (6u)

#define CANTP_MAXFFDL                                (0xFFFu)
#define CANTP_MAXFDFFDL                              (0xFFFFu)
#define CANTP_MAXBLOCKSIZE                           (0xFFu)

#define CANTP_CANDL_ARRAY_SIZE                       (65u)
#define CANTP_PCI_ARRAY_SIZE                         (6u)
#define CANTP_ADDRESS_ARRAY_SIZE                     (5u)

#define CANTP_STANDARD                               (0u)
#define CANTP_EXTENDED                               (1u)
#define CANTP_MIXED                                  (2u)

#define CANTP_MILLISEC_MAX_RANGE                     (0x7Fu)
#define CANTP_MICROSEC_MIN_RANGE                     (0xF1u)
#define CANTP_MICROSEC_MAX_RANGE                     (0xF9u)
#define CANTP_MAX_BS_VALUE                           (0xFFu)

#define CANTP_TC_DISABLED                            (0x10u)
#define CANTP_PADDINGON                              (0x08u)
#define CANTP_FUNCTIONAL                             (0x04u)
#define CANTP_FC_DISABLED                            (0x02u)
#define CANTP_FD_ENABLED                             (0x01u)

#define CANTP_SINGLE_FRAME                           (0x00u)
#define CANTP_FIRST_FRAME                            (0x01u)
#define CANTP_CONSECUTIVE_FRAME                      (0x02u)
#define CANTP_FLOWCONTROL_FRAME                      (0x03u)
#define CANTP_NUMBER_OF_FRAME_TYPES                  (0x04u)
#define CANTP_FRAMETYPE_OFFSET                       (0x04u)
#define CANTP_LOWERNIBBLE_MASK                       (0x0Fu)

#define CANTP_INVALID_DL                             (0xFFu)
#define CANTP_INVALID_NOTIFY_VALUE                   (0xFFu)
#define CANTP_INVALID_CHANNEL                        (CANTP_MAX_CHANNEL_SIZE)

#define CANTP_IDLE                                   (0u)

#define CANTP_TRANSMISSION                           (1u)
#define CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED       (1u)
#define CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION      (2u)
#define CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME          (3u)
#define CANTP_TX_SEND_CONSECUTIVE_FRAME              (4u)

#define CANTP_RECEPTION                              (2u)
#define CANTP_RX_RECEPTION_REQUEST_ACCEPTED          (5u)
#define CANTP_RX_SEND_FC                             (6u)
#define CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION    (7u)
#define CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME          (8u)

#define CANTP_NUMBER_OF_SUBSTATES                    (9u)

#define CANTP_TX_PDUR_CONFIRMATION                   (0u)
#define CANTP_RX_PDUR_CONFIRMATION                   (1u)
#define CANTP_NUMBER_OF_PDUR_CONFIRMATION_TYPES      (2u)

#define CANTP_TRIGGER_TX_CONFIRMATION                (0u)
#define CANTP_TRIGGER_RX_INDICATION                  (1u)
#define CANTP_NUMBER_OF_TRIGGER_POINTS               (2u)

#define CANTP_FC_CTS                                 (0u)
#define CANTP_FC_WAIT                                (1u)
#define CANTP_FC_OVERFLOW                            (2u)

#define CanTp_Lok_PduRConfirmation(Api, id, result)  CanTp_PduRConfirmationApis[Api](id, result)
#define CanTp_Lok_ActivateMainFunction(TriggerPoint) CanTp_SchMTriggerApis[TriggerPoint]()
#define CanTp_Lok_ProcessFrame(Context, PduInfoPtr)  CanTp_ProcessFrame[(Context)->FrameType](Context, PduInfoPtr)
#define CanTp_Lok_FrameType(id)                      CanTp_PciFrameType[CanTp_Channel[id].PciId]
#define CanTp_Lok_CreateFrame(id, PduInfoPtr)        CanTp_CreateFrame[CanTp_Lok_FrameType(id)](id, PduInfoPtr)
#define CanTp_Lok_ExecuteState(ChannelId)            CanTp_StateFunctions[CanTp_SubState[ChannelId]](ChannelId)
#define CanTp_Lok_GetTxChannelId(id)                 CanTp_CfgPtr->TxSdu[id].ChannelId
#define CanTp_Lok_GetRxChannelId(id)                 CanTp_CfgPtr->RxSdu[id].ChannelId
#define CanTp_Lok_GetState(ChannelId)           	 CanTp_State[CanTp_SubState[ChannelId]]
#define CanTp_Lok_GetRxCfgParam(id, param)           CanTp_CfgPtr->Param[CanTp_CfgPtr->RxSdu[id].ParamId].Param[param]
#define CanTp_Lok_GetRxCfgFcWaitMax(id)              CanTp_CfgPtr->Param[CanTp_CfgPtr->RxSdu[id].ParamId].FcWaitMax
#define CanTp_Lok_GetCfgAsArTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].AsArTicks
#define CanTp_Lok_GetCfgBsBrTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].BsBrTicks
#define CanTp_Lok_GetCfgCsCrTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].CsCrTicks
#define CanTp_Lok_GetTxActiveBits(id)                CanTp_CfgPtr->TxSdu[CanTp_Channel[id].ActiveSduId].BitFields
#define CanTp_Lok_GetRxActiveBits(id)                CanTp_CfgPtr->RxSdu[CanTp_Channel[id].ActiveSduId].BitFields
#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
#define CanTp_Lok_ReportError(Api, Err)              (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID, Api, Err)
#define CanTp_Lok_ReportRunTimeError(Api, Err)       (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID, \
                                                      Api, Err)
#else
#define CanTp_Lok_ReportError(Api, Err)
#define CanTp_Lok_ReportRunTimeError(Api, Err)
#endif
#if(CANTP_CHANGE_PARAMETER_API != STD_ON)
#define CanTp_Lok_RxParamInit()
#endif
#if(CANTP_CANFD_SUPPORT == CANTP_ON)
#define CanTp_Lok_GetTxDl(Connection)                ((Connection)->TX_DL)
#define CanTp_Lok_GetCanDl(FrameLength)              (CanTp_CanDlTable[FrameLength])
#define CanTp_Lok_GetRxDl(ChannelId)                 (CanTp_Channel[ChannelId].RX_DL)
#define CanTp_Lok_SetRxDl(ChannelId, Value)          (CanTp_Channel[ChannelId].RX_DL = (Value))
#define CanTp_Lok_IsRxDlInValid(RX_DL)               (((RX_DL) != 0x08) && ((RX_DL) != 0x0C) && ((RX_DL) != 0x10) &&\
                                                      ((RX_DL) != 0x14) && ((RX_DL) != 0x18) && ((RX_DL) != 0x20) &&\
                                                      ((RX_DL) != 0x30) && ((RX_DL) != 0x40))
#else
#define CanTp_Lok_GetTxDl(Connection)                (CANTP_DEFAULT_CAN_DL)
#define CanTp_Lok_GetCanDl(FrameLength)              (CANTP_DEFAULT_CAN_DL)
#define CanTp_Lok_GetRxDl(ChannelId)                 (CANTP_DEFAULT_CAN_DL)
#define CanTp_Lok_SetRxDl(ChannelId, Value)
#define CanTp_Lok_IsRxDlInValid(RX_DL)               (((RX_DL) != 0x08))
#endif
#if(CANTP_TX_BURST_MODE != CANTP_ON)
#define CanTp_Lok_QInit()
#define CanTp_Lok_PutInQ(ChannelId)
#define CanTp_Lok_GetFromQ(ChannelId)
#define CanTp_Lok_BurstMainFunction(Id, Point)
#endif
#if(CANTP_CYCLE_COUNTER == CANTP_ON)
#define CanTp_IncrementCounter()                      (CanTp_MainFunctionTicks++)
#else
#define CanTp_IncrementCounter()
#endif
#define CanTp_Lok_BuildBugOn(condition)              ((void)sizeof(char[1 - 2*!!(condition)]))

typedef Std_ReturnType (*CanTp_CreateFrameType)(CanTp_ChannelIdType ChannelId, PduInfoType *PduInfoPtr);

typedef struct
{
	boolean IsFunctional;
	boolean IsPaddingOn;
	boolean IsFdEnabled;
    uint8 Address;
    uint8 FrameType;
	uint8 FlowStatus;
	uint8 SN;
    uint8 DataOffset;
	uint8 AddressFormatId;
	uint8 AddressSize;
	uint8 CAN_DL;
    CanTp_ChannelIdType ChannelId;
	CanTp_SduIdType SduId;
    PduIdType PduId;
    PduIdType PduRPduHandleId;
    PduLengthType SduLength;
}CanTp_RxContextType;

typedef struct
{
    uint8 PduRApiId;
    uint8 PayLoadLength;
    CanTp_ChannelIdType ChannelId;
    PduIdType TxConfirmationId;
    PduIdType PduId;
    PduIdType PduRPduHandleId;
    PduLengthType RemBufSize;
    CanTp_TickType Value;
    CanTp_TickType ElapsedValue;
    CanTp_TickType CsTicks;
}CanTp_TxContextType;

typedef void (*CanTp_ProcessFrameType)(const CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr);

#if(CANTP_TX_BURST_MODE == CANTP_ON)
typedef struct
{
    uint8 Head_u8;
    uint8 Tail_u8;
    CanTp_ChannelIdType Queue[CANTP_BURST_QUEUE_SIZE];
}CanTp_QType;
#endif

typedef struct
{
    uint8 Param[2];
}CanTp_ParamPairType;

typedef void (*CanTp_StateFuncType)(CanTp_ChannelIdType ChannelId);

typedef struct
{
    #if(CANTP_CANFD_SUPPORT == CANTP_ON)
    uint8 RX_DL;
    #endif
    uint8 PciId;
    uint8 FlowStatus;
    uint8 SN;
    uint8 BS;
    CanTp_SduIdType ActiveSduId;
    uint16 FcWait;
    PduLengthType BlockCfsRemaining;
    PduLengthType SduLengthRemaining;
    PduLengthType SduLength;
    CanTp_TickType InitialTicks;
    CanTp_TickType STminTicks;
}CanTp_ChannelType;

typedef CanTp_ChannelType *CanTp_ChannelPtrType;
typedef void (*CanTp_PduRConfirmationApiType)(PduIdType id, Std_ReturnType result);
typedef void (*CanTp_SchMTriggerApiType)(void);
typedef Std_ReturnType (*CanTp_CanIfTransmitApiType)(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"
extern CanTp_ChannelType CanTp_Channel[CANTP_MAX_CHANNEL_SIZE];
extern CanTp_ChannelIdType CanTp_TxConfirmationChannel[CANTP_MAX_TX_NPDU_SIZE];
#if(CANTP_TX_BURST_MODE == CANTP_ON)
extern CanTp_QType CanTp_BurstQ;
#endif
#if(CANTP_CHANGE_PARAMETER_API == STD_ON)
extern CanTp_ParamPairType CanTp_ParamPair[CANTP_MAX_RX_CONNECTION_SIZE];
#endif
#if(CANTP_CYCLE_COUNTER == CANTP_ON)
extern volatile CanTp_TickType CanTp_MainFunctionTicks;
#endif
extern const Type_CfgSwcServiceCanTp_st *CanTp_CfgPtr;
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"
extern uint8 CanTp_SubState[CANTP_MAX_CHANNEL_SIZE];
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "CanTp_MemMap.h"
extern const uint8 CanTp_State[CANTP_NUMBER_OF_SUBSTATES];
extern const uint8 CanTp_AddressSize[CANTP_ADDRESS_ARRAY_SIZE];
extern const uint8 CanTp_PciFrameType[CANTP_PCI_ARRAY_SIZE];
extern const uint8 CanTp_PciSize[CANTP_PCI_ARRAY_SIZE];
#if(CANTP_CANFD_SUPPORT == CANTP_ON)
extern const uint8 CanTp_CanDlTable[CANTP_CANDL_ARRAY_SIZE];
#endif
#define CANTP_STOP_SEC_CONST_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
extern const CanTp_ProcessFrameType CanTp_ProcessFrame[CANTP_NUMBER_OF_FRAME_TYPES];
extern const CanTp_CreateFrameType CanTp_CreateFrame[CANTP_NUMBER_OF_FRAME_TYPES];
extern const CanTp_StateFuncType CanTp_StateFunctions[CANTP_NUMBER_OF_SUBSTATES];
extern const CanTp_PduRConfirmationApiType  CanTp_PduRConfirmationApis[CANTP_NUMBER_OF_PDUR_CONFIRMATION_TYPES];
#if((CANTP_SCHM_SUPPORT == CANTP_ON) && (CANTP_TX_BURST_MODE == CANTP_ON))
extern const CanTp_SchMTriggerApiType  CanTp_SchMTriggerApis[CANTP_NUMBER_OF_TRIGGER_POINTS];
#endif
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.h"

#if(CANTP_TX_BURST_MODE == CANTP_ON)
extern void CanTp_Lok_BurstMainFunction(CanTp_ChannelIdType ChannelId, uint8 TriggerPoint);
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.h"

#if(CANTP_CYCLE_COUNTER == CANTP_ON)

LOCAL_INLINE void CanTp_GetElapsedValue(CanTp_TickType *Value, CanTp_TickType *ElapsedValue)
{
    CanTp_TickType ValueIn = *Value;

    *Value = CanTp_MainFunctionTicks;

    *ElapsedValue = *Value - ValueIn;

}
#endif

LOCAL_INLINE boolean CanTp_Lok_GetBit(uint8 Value, uint8 Mask)
{
    return ((Value & Mask) == Mask) ? TRUE : FALSE;
}

LOCAL_INLINE void CanTp_Lok_ArrayInit(uint8 *ArrayPtr, uint32 Length, uint8 Item)
{
    uint32 i;

    for(i = 0; i < Length; i++)
    {
        ArrayPtr[i] = Item;
    }
}

LOCAL_INLINE boolean CanTp_Lok_IsNoDevError(uint32 id, uint8 ApiId, uint8 CanTpEInvalidId)
{
    uint8 ErrorId;
    uint32 TotalIds = 0;
    boolean Status = TRUE;

    if(CanTp_MainState != CANTP_ON)
    {
        ErrorId = CANTP_E_UNINIT;
    }
    else
    {
        switch(ApiId)
        {
            case CANTP_CHANGEPARAMETER:
			case CANTP_READPARAMETER:
            case CANTP_CANCELRECEIVE:
                TotalIds = CanTp_CfgPtr->NumberOfRxSdus;
                break;
            case CANTP_TRANSMIT:
            case CANTP_CANCELTRANSMIT:
                TotalIds = CanTp_CfgPtr->NumberOfTxSdus;
                break;
			case CANTP_TXCONFIRMATION:
			case CANTP_TRIGGERTRANSMIT:
                TotalIds = CanTp_CfgPtr->NumberOfTxPdus;
				break;
			case CANTP_RXINDICATION:
                TotalIds = CanTp_CfgPtr->NumberOfRxPdus;
				break;
            default:
                break;
        }

        if(id >= TotalIds)
        {
            ErrorId = CanTpEInvalidId;
        }
        else
        {
            ErrorId = CANTP_NO_ERROR;
        }
    }

    if(ErrorId != CANTP_NO_ERROR)
    {
        CanTp_Lok_ReportError(ApiId, ErrorId);
        Status = FALSE;
    }

    return Status;
}

#if(CANTP_CHANGE_PARAMETER_API == STD_ON)

LOCAL_INLINE boolean CanTp_Lok_IsChangeParameterOk(TPParameterType parameter, uint16 value)
{
    uint8 ErrorId;
    boolean Status = TRUE;

    if((parameter != TP_BS) && (parameter != TP_STMIN))
    {
        ErrorId = CANTP_E_PARAM_ID;
    }
    else if((parameter == TP_STMIN) && (!(( value <= CANTP_MILLISEC_MAX_RANGE) || ((value >= CANTP_MICROSEC_MIN_RANGE)
            && ( value <= CANTP_MICROSEC_MAX_RANGE)))))
    {
        ErrorId = CANTP_E_PARAM_CONFIG;
    }
    else if((parameter == TP_BS) && (value > CANTP_MAX_BS_VALUE))
    {
        ErrorId = CANTP_E_PARAM_CONFIG;
    }
    else
    {
        ErrorId = CANTP_NO_ERROR;
    }

    if(ErrorId != CANTP_NO_ERROR)
    {
        CanTp_Lok_ReportRunTimeError(CANTP_CHANGEPARAMETER, ErrorId);
        Status = FALSE;
    }

    return Status;
}

LOCAL_INLINE void CanTp_Lok_RxParamInit(void)
{
    CanTp_SduIdType SduId;

    for(SduId = 0; SduId < CanTp_CfgPtr->NumberOfRxSdus; SduId++)
    {
        CanTp_ParamPair[SduId].Param[0] = CanTp_Lok_GetRxCfgParam(SduId, 0);
        CanTp_ParamPair[SduId].Param[1] = CanTp_Lok_GetRxCfgParam(SduId, 1);
    }
}
#endif

LOCAL_INLINE PduLengthType CanTp_Lok_GetTxBlockCfs(CanTp_ChannelIdType ChannelId)
{
    uint8 PayLoadLength;
	const CanTp_TxSduType *Connection = CanTp_CfgPtr->TxSdu + CanTp_Channel[ChannelId].ActiveSduId;
    uint8 TX_DL = CanTp_Lok_GetTxDl(Connection);
    uint8 AddressSize = CanTp_AddressSize[Connection->AddressFormatId];
    PduLengthType SduLength = CanTp_Channel[ChannelId].SduLengthRemaining;

    PayLoadLength = TX_DL - CANTP_CF_PCISIZE - AddressSize;
    return ((SduLength % PayLoadLength) == 0) ? (SduLength / PayLoadLength) : ((SduLength / PayLoadLength) + 1);
}

LOCAL_INLINE PduLengthType CanTp_Lok_GetRxBlockCfs(CanTp_ChannelIdType ChannelId)
{
    uint8 PayLoadLength;
	const CanTp_RxSduType *Connection = CanTp_CfgPtr->RxSdu + CanTp_Channel[ChannelId].ActiveSduId;
    uint8 RX_DL = CanTp_Lok_GetRxDl(ChannelId);
    uint8 AddressSize = CanTp_AddressSize[Connection->AddressFormatId];
    PduLengthType SduLength = CanTp_Channel[ChannelId].SduLengthRemaining;

    PayLoadLength = RX_DL - CANTP_CF_PCISIZE - AddressSize;
    return ((SduLength % PayLoadLength) == 0) ? (SduLength / PayLoadLength) : ((SduLength / PayLoadLength) + 1);
}

#if(CANTP_TX_BURST_MODE == CANTP_ON)

LOCAL_INLINE void CanTp_Lok_QInit(void)
{
    CanTp_BurstQ.Tail_u8 = 0;
    CanTp_BurstQ.Head_u8 = 0;
}

LOCAL_INLINE Std_ReturnType CanTp_Lok_PutInQ(CanTp_ChannelIdType ChannelId)
{
    Std_ReturnType Status = E_NOT_OK;

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

    if((CanTp_BurstQ.Tail_u8 - CanTp_BurstQ.Head_u8) != CANTP_BURST_QUEUE_SIZE)
    {
        Status = E_OK;
        CanTp_BurstQ.Tail_u8++;
        CanTp_BurstQ.Queue[CanTp_BurstQ.Tail_u8 % CANTP_BURST_QUEUE_SIZE] = ChannelId;
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();

    return Status;
}

LOCAL_INLINE Std_ReturnType CanTp_Lok_GetFromQ(CanTp_ChannelIdType *ChannelId)
{
    Std_ReturnType Status = E_NOT_OK;

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

    if((CanTp_BurstQ.Tail_u8 - CanTp_BurstQ.Head_u8) != 0)
    {
        Status = E_OK;
        CanTp_BurstQ.Head_u8++;
        *ChannelId = CanTp_BurstQ.Queue[CanTp_BurstQ.Head_u8 % CANTP_BURST_QUEUE_SIZE];
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();

    return Status;
}
#endif

LOCAL_INLINE void CanTp_Lok_TxPciInit(uint8 *PciId, PduIdType CanTpTxSduId, const PduInfoType *CanTpTxInfoPtr)
{
    const CanTp_TxSduType *Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
    uint8 AddressLength;
    #if(CANTP_CANFD_SUPPORT == CANTP_ON)
    uint8 TX_DL = CanTp_Lok_GetTxDl(Connection);
    #endif

    AddressLength = CanTp_AddressSize[Connection->AddressFormatId];

    if((CanTpTxInfoPtr->SduLength + AddressLength + 1u) <= CANTP_DEFAULT_CAN_DL)
    {
        *PciId = CANTP_NPCI_SFCAN;
    }
    #if(CANTP_CANFD_SUPPORT == CANTP_ON)
    else if((TX_DL > CANTP_DEFAULT_CAN_DL) && ((CanTpTxInfoPtr->SduLength + AddressLength + 2u) <= TX_DL))
    {
        *PciId = CANTP_NPCI_SFCANFD;
    }
    else if((TX_DL > CANTP_DEFAULT_CAN_DL) && (CanTpTxInfoPtr->SduLength > CANTP_MAXFFDL))
    {
        *PciId = CANTP_NPCI_FFCANFD;
    }
    #endif
    else
    {
        *PciId = CANTP_NPCI_FFCAN;
    }
}

LOCAL_INLINE void CanTp_Lok_CanIfTransmit(const CanTp_TxContextType *Context, const PduInfoType *CanIfTxInfoPtr)
{
    PduInfoType CanIfTxInfo;
    #if(CANTP_TRIGGER_TRANSMIT_API != CANTP_ON)
    uint8 SduBuffer[CANTP_MAX_NPDU_LENGTH];
    #endif

    CanIfTxInfo.SduLength = CanIfTxInfoPtr->SduLength;
    CanIfTxInfo.SduDataPtr = CanIfTxInfoPtr->SduDataPtr;

    #if(CANTP_TRIGGER_TRANSMIT_API != CANTP_ON)
    CanIfTxInfo.SduDataPtr = SduBuffer;
    if(CanTp_Lok_CreateFrame(Context->ChannelId, &CanIfTxInfo) == E_OK)
    #endif
    {
        CanTp_TxConfirmationChannel[Context->TxConfirmationId] = Context->ChannelId;
        if(CanIf_Transmit(Context->PduId, &CanIfTxInfo) != E_OK)
        {
            CanTp_Lok_PduRConfirmation(Context->PduRApiId, Context->PduRPduHandleId, E_NOT_OK);
            CanTp_Lok_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_COM);
            CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
            CanTp_TxConfirmationChannel[Context->TxConfirmationId] = CANTP_INVALID_CHANNEL;
        }
    }
}

LOCAL_INLINE void CanTp_Lok_FcTransmit(const CanTp_TxContextType *Context, const PduInfoType* CanIfTxInfoPtr,
                                       boolean IsFcTransmitReady, CanTp_TickType Value)
{
    if(IsFcTransmitReady && (CanTp_SubState[Context->ChannelId] == CANTP_RX_SEND_FC))
    {
        CanTp_Channel[Context->ChannelId].InitialTicks = Value;
        CanTp_Channel[Context->ChannelId].PciId = CANTP_NPCI_FC;
        CanTp_SubState[Context->ChannelId] = CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION;

        #if(CANTP_FC_DISABLE_SUPPORT == CANTP_ON)
        if(CanTp_Lok_GetBit(CanTp_Lok_GetRxActiveBits(Context->ChannelId), CANTP_FC_DISABLED))
        {
            if((CanTp_Channel[Context->ChannelId].FlowStatus != CANTP_FC_OVERFLOW) &&
               (CanTp_Channel[Context->ChannelId].SduLengthRemaining <= Context->RemBufSize))
            {
                CanTp_Channel[Context->ChannelId].BlockCfsRemaining = CanTp_Lok_GetRxBlockCfs(Context->ChannelId);
                CanTp_Channel[Context->ChannelId].STminTicks = CANTP_DEFAULT_STMIN_TICKS;
                CanTp_SubState[Context->ChannelId] = CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME;
            }
            else
            {
                CanTp_Lok_PduRConfirmation(Context->PduRApiId, Context->PduRPduHandleId, E_NOT_OK);
                CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
            }
        }
        else
        #endif
        {
            CanTp_Lok_CanIfTransmit(Context, CanIfTxInfoPtr);
        }
    }
}

LOCAL_INLINE Std_ReturnType CanTp_Lok_GetFcActiveChannel(CanTp_RxContextType *Context)
{
    Std_ReturnType Status = E_NOT_OK;
    const CanTp_TxSduType *TxConnection;

    if(Context->SduId < CanTp_CfgPtr->NumberOfTxSdus)
    {
        TxConnection = CanTp_CfgPtr->TxSdu + Context->SduId;

        if(CanTp_SubState[TxConnection->ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME)
        {
            Context->ChannelId = TxConnection->ChannelId;
            Status = E_OK;
        }
    }

    #if(CANTP_LEGACY_SHARED_FC_SUPPORT == STD_ON)
    if(Status == E_NOT_OK)
    {
        uint8 i;
        CanTp_ChannelIdType ChannelId;
        CanTp_SduIdType SduId;
        const CanTp_SharedFcType *SharedFc = CanTp_CfgPtr->SharedFc;

        for(i = 0; i < CanTp_CfgPtr->NumberOfSharedFc; i++)
        {
            if((SharedFc[i].RxFcPduId == Context->PduId) && (SharedFc[i].TxSduId != Context->SduId))
            {
                ChannelId = CanTp_Lok_GetTxChannelId(SharedFc[i].TxSduId);

                SduId = CanTp_Channel[ChannelId].ActiveSduId;
                if((CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME) && (SharedFc[i].TxSduId == SduId))
                {
                    Context->ChannelId = ChannelId;
                    Context->SduId = SduId;
                    Status = E_OK;
                    break;
                }
            }
        }

    }
    #endif

    return Status;
}

LOCAL_INLINE uint8 CanTp_Lok_GetRxContext(CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
    uint8 ErrorId = CANTP_E_PARAM_CONFIG;
    CanTp_SduIdType TxSduId;
    CanTp_SduIdType RxSduId;
    uint8 FrameType;
    uint8 *SduDataPtr;
	const CanTp_TxSduType *TxConnection;
	const CanTp_RxSduType *RxConnection;
    const CanTp_RxPduType *RxPdu = CanTp_CfgPtr->RxPdu + Context->PduId;

    if(PduInfoPtr->SduDataPtr == NULL_PTR)
    {
        ErrorId = CANTP_E_PARAM_POINTER;
    }
    else
    {
        SduDataPtr = PduInfoPtr->SduDataPtr;
        Context->Address = 0;
        RxSduId = RxPdu->RxSduId;
        TxSduId = RxPdu->TxSduId;

        if(RxPdu->GetSduPair != NULL_PTR)
        {
            Context->Address = *SduDataPtr;
            SduDataPtr++;
            RxPdu->GetSduPair(&TxSduId, &RxSduId, Context->Address);
        }

        FrameType = *SduDataPtr >> CANTP_FRAMETYPE_OFFSET;

        if(FrameType < CANTP_NUMBER_OF_FRAME_TYPES)
        {
            Context->FrameType = FrameType;

            if(FrameType == CANTP_FLOWCONTROL_FRAME)
            {
                Context->SduId = TxSduId;
                if(CanTp_Lok_GetFcActiveChannel(Context) == E_OK)
                {
                    TxConnection = CanTp_CfgPtr->TxSdu + Context->SduId;
                    Context->PduRPduHandleId = TxConnection->PduRPduHandleId;
                    Context->AddressSize = CanTp_AddressSize[TxConnection->AddressFormatId];
                    Context->IsPaddingOn = CanTp_Lok_GetBit(TxConnection->BitFields, CANTP_PADDINGON);
                    ErrorId = CANTP_NO_ERROR;
                }
            }
            else
            {
                Context->SduId = RxSduId;
                if(Context->SduId < CanTp_CfgPtr->NumberOfRxSdus)
                {
                    RxConnection = CanTp_CfgPtr->RxSdu + RxSduId;
                    Context->ChannelId = RxConnection->ChannelId;
                    Context->PduRPduHandleId = RxConnection->PduRPduHandleId;
                    Context->AddressSize = CanTp_AddressSize[RxConnection->AddressFormatId];
                    Context->IsPaddingOn = CanTp_Lok_GetBit(RxConnection->BitFields, CANTP_PADDINGON);
                    Context->IsFdEnabled = CanTp_Lok_GetBit(RxConnection->BitFields, CANTP_FD_ENABLED);
                    Context->IsFunctional = CanTp_Lok_GetBit(RxConnection->BitFields, CANTP_FUNCTIONAL);
                    ErrorId = ((Context->IsFunctional) && (FrameType != CANTP_SINGLE_FRAME)) ?
                            CANTP_E_INVALID_TATYPE : CANTP_NO_ERROR;
                }
            }
        }
    }

    return ErrorId;
}

LOCAL_INLINE Std_ReturnType CanTp_Lok_RxSduLengthCheck(CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
    uint8 CAN_DL = CANTP_INVALID_DL;
    uint8 PciLowerNibble;
    uint8 *Data;
    uint8 DataOffset = 0;
    uint8 SF_DL = 0;
    uint32 FF_DL = 0;
    PduLengthType FF_DLmin;
    PduLengthType FfDlValue12bit;
	uint8 MaxCfSduLength;
	PduLengthType SduLengthRemaining;
	uint8 RX_DL;

	Data = PduInfoPtr->SduDataPtr + Context->AddressSize;
	PciLowerNibble = Data[0] & CANTP_LOWERNIBBLE_MASK;

	switch(Context->FrameType)
	{
		case CANTP_SINGLE_FRAME:
			if(PduInfoPtr->SduLength <= CANTP_DEFAULT_CAN_DL)
			{
				DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_SFCAN];
				SF_DL = PciLowerNibble;

				if((PciLowerNibble != 0u) && ((PciLowerNibble <= (CANTP_DEFAULT_CAN_DL - DataOffset))))
				{
					CAN_DL = ((Context->IsPaddingOn)) ? CANTP_DEFAULT_CAN_DL : (DataOffset + (uint8)PciLowerNibble);
				}
			}
			else
			{
                #if(CANTP_CANFD_SUPPORT == CANTP_ON)
				DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_SFCANFD];
				SF_DL = Data[1];

				if((PciLowerNibble == 0u) &&
				   (SF_DL > (7u - Context->AddressSize)) &&
				   (SF_DL <=  (PduInfoPtr->SduLength - DataOffset)) &&
				   ((Context->AddressSize + 2u + SF_DL) <= CANTP_MAX_NPDU_LENGTH))
				{
					CAN_DL = ((Context->IsPaddingOn)) ? CanTp_Lok_GetCanDl(DataOffset + SF_DL) : (DataOffset + SF_DL);
				}
                #endif
			}
			break;

		case CANTP_FIRST_FRAME:
			CAN_DL = (uint8)(PduInfoPtr->SduLength);
			RX_DL = CanTp_Lok_IsRxDlInValid(CAN_DL) ? CANTP_INVALID_DL : CAN_DL;
			
			FF_DLmin = RX_DL - Context->AddressSize - ((CAN_DL > CANTP_DEFAULT_CAN_DL) ? 1u : 0u);

			FfDlValue12bit = ((Data[0] & CANTP_LOWERNIBBLE_MASK) * 0x100u) + Data[1];

            if(FfDlValue12bit == 0)
            {
                FF_DL = (Data[2] * 0x1000000u) + (Data[3] * 0x10000u) + (Data[4] * 0x100u) + Data[5];
                DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_FFCANFD];
                RX_DL = ((FF_DL > CANTP_MAXFDFFDL) || (FF_DL <= CANTP_MAXFFDL)) ? CANTP_INVALID_DL : RX_DL;
            }
            else
            {
                FF_DL = FfDlValue12bit;
                DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_FFCAN];
            }

			
			RX_DL = ((Context->IsFunctional) || (FF_DL < FF_DLmin)) ? CANTP_INVALID_DL : RX_DL;
			CAN_DL = RX_DL;
			break;

		case CANTP_CONSECUTIVE_FRAME:
			SduLengthRemaining = CanTp_Channel[Context->ChannelId].SduLengthRemaining;
			Context->SN = PciLowerNibble;
			RX_DL = CanTp_Lok_GetRxDl(Context->ChannelId);
			DataOffset = Context->AddressSize + CANTP_CF_PCISIZE;
			MaxCfSduLength = RX_DL - DataOffset;
			CAN_DL = (SduLengthRemaining < MaxCfSduLength) ? (uint8)(SduLengthRemaining + DataOffset) : RX_DL;
			CAN_DL = (Context->IsPaddingOn) ? CanTp_Lok_GetCanDl(CAN_DL) : CAN_DL;
			break;

		case CANTP_FLOWCONTROL_FRAME:
			Context->FlowStatus = PciLowerNibble;
            DataOffset = Context->AddressSize + 1;
			CAN_DL = (Context->IsPaddingOn) ? CANTP_DEFAULT_CAN_DL : (CANTP_FC_PCISIZE  + Context->AddressSize);
			break;

		default:
			break;
	}

	Context->CAN_DL = CAN_DL;
	Context->DataOffset = DataOffset;
	Context->SduLength = (Context->FrameType == CANTP_SINGLE_FRAME) ? SF_DL : (PduLengthType)FF_DL;

	return CanTp_Cfg_DlcCheck(PduInfoPtr->SduLength, Context->CAN_DL);
}

LOCAL_INLINE Std_ReturnType CanTp_Lok_GetConnectionAcceptance(const CanTp_RxContextType *Context,
                                                              const PduInfoType *PduInfoPtr)
{
    Std_ReturnType RetValue = E_NOT_OK;
    uint8 NewChannelState = CANTP_IDLE;
    uint8 OldChannelState = CanTp_Lok_GetState(Context->ChannelId);

    #if(CANTP_FD_CALLOUT_SUPPORT == STD_ON)
    if((CanTp_FdCallOut(Context->PduId, PduInfoPtr, Context->IsFdEnabled)) == E_OK)
    #else
    (void)PduInfoPtr;
    #endif
    {
        if(OldChannelState == CANTP_IDLE)
        {
            NewChannelState = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
        }
        else
        {
            if((OldChannelState == CANTP_RECEPTION)&&(CanTp_Channel[Context->ChannelId].ActiveSduId == Context->SduId))
            {
                NewChannelState = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
                CanTp_Lok_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
            }
        }

        if(NewChannelState == CANTP_RX_RECEPTION_REQUEST_ACCEPTED)
        {
            CanTp_SubState[Context->ChannelId] = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
            RetValue = E_OK;
        }
    }

    return RetValue;
}

LOCAL_INLINE void CanTp_Lok_SetTxBlockInfo(const CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
    uint8 *SduDataPtr;
    CanTp_ChannelPtrType Channel = &CanTp_Channel[Context->ChannelId];
    PduLengthType BlockCfsRemaining;

    SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset;

    #if(CANTP_DYNAMIC_FC_SUPPORT != CANTP_ON)
    if(Channel->STminTicks == CANTP_INVALID_STMIN_TICKS)
    #endif
    {

        Channel->BS = *SduDataPtr;
        SduDataPtr++;

        if(*SduDataPtr <= CANTP_MILLISEC_MAX_RANGE)
        {
            Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks(*SduDataPtr * 1000u);
        }
        else if((*SduDataPtr < CANTP_MICROSEC_MIN_RANGE) || (*SduDataPtr > CANTP_MICROSEC_MAX_RANGE))
        {
            Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks(127000u);
        }
        else
        {
            Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks((*SduDataPtr & CANTP_LOWERNIBBLE_MASK) * 100u);
        }
    }

    BlockCfsRemaining = CanTp_Lok_GetTxBlockCfs(Context->ChannelId);

    if((Channel->BS == 0u) || (Channel->BS > BlockCfsRemaining))
    {
        Channel->BlockCfsRemaining = BlockCfsRemaining;
    }
    else
    {
        Channel->BlockCfsRemaining = (uint16)Channel->BS;
    }
}

LOCAL_INLINE uint8 CanTp_Lok_GetRxParam(CanTp_SduIdType id, TPParameterType parameter)
{
    uint8 value;

    value = (parameter == TP_STMIN)? (0u) : (1u);

    #if(CANTP_CHANGE_PARAMETER_API != STD_ON)
    return CanTp_Lok_GetRxCfgParam(id, value);
    #else
    return CanTp_ParamPair[id].Param[value];
    #endif
}

LOCAL_INLINE void CanTp_Lok_SetRxBlockInfo(CanTp_ChannelIdType ChannelId, const PduLengthType RemBufSize)
{
    uint8 BSMax;
    PduLengthType BlockCfsRemaining;
	CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
    uint8 BS = Channel->BS;
    const CanTp_RxSduType *Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
    PduLengthType OneFramePayloadLength = CanTp_Lok_GetRxDl(ChannelId) -
                                          CanTp_AddressSize[Connection->AddressFormatId] - CANTP_CF_PCISIZE;

    #if(CANTP_DYNAMIC_FC_SUPPORT != CANTP_ON)
    if(Channel->STminTicks == CANTP_INVALID_STMIN_TICKS)
    #endif
    {
        BSMax = CanTp_Lok_GetRxParam(Channel->ActiveSduId, TP_BS);

        if(RemBufSize >= Channel->SduLengthRemaining)
        {
            BS = BSMax;
        }
        else
        {
            BS = (uint8)(RemBufSize/OneFramePayloadLength);
            BS = ((BSMax != 0u) && (BS > BSMax)) ? BSMax : BS;
        }
    }

    if(((BS == 0) && (RemBufSize < Channel->SduLengthRemaining)) ||
	   ((BS != 0) && (RemBufSize < (BS * OneFramePayloadLength)) && (RemBufSize < Channel->SduLengthRemaining)))
    {
        Channel->FlowStatus = CANTP_FC_WAIT;
    }
    else
    {
		BlockCfsRemaining = CanTp_Lok_GetRxBlockCfs(ChannelId);
        Channel->BlockCfsRemaining = (BS != 0u) ? BS : BlockCfsRemaining;
	    Channel->FlowStatus = CANTP_FC_CTS;
        #if(CANTP_DYNAMIC_FC_SUPPORT != CANTP_ON)
        Channel->STminTicks = 0;
        #endif
    }

    Channel->BS = BS;
}

LOCAL_INLINE void CanTp_Lok_FcTxConfirmation(CanTp_ChannelIdType ChannelId)
{
    const CanTp_ChannelType *Channel = CanTp_Channel + ChannelId;
    const CanTp_RxSduType *RxConnection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;

    switch(Channel->FlowStatus)
    {
        case CANTP_FC_CTS:
            CanTp_SubState[ChannelId] = CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME;
            break;
        case CANTP_FC_WAIT:
            CanTp_SubState[ChannelId] = (Channel->SduLengthRemaining > 0) ? CANTP_RX_SEND_FC : CANTP_IDLE;
            break;
        case CANTP_FC_OVERFLOW:
            CanTp_Lok_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, RxConnection->PduRPduHandleId, E_NOT_OK);
            CanTp_SubState[ChannelId] = CANTP_IDLE;
            break;
        default:
            break;
    }
}

LOCAL_INLINE void CanTp_Lok_PrepareFcTransmit(CanTp_ChannelIdType ChannelId)
{
    if(CanTp_Channel[ChannelId].BlockCfsRemaining == 0)
    {
        CanTp_Channel[ChannelId].FcWait = 0;
        CanTp_Channel[ChannelId].FlowStatus = CANTP_FC_WAIT;
        CanTp_SubState[ChannelId] = CANTP_RX_SEND_FC;
    }
}

LOCAL_INLINE void CanTp_Lok_PrepareFcRecieve(CanTp_ChannelIdType ChannelId)
{
	#if(CANTP_FC_DISABLE_SUPPORT == CANTP_ON)
    if(CanTp_Lok_GetBit(CanTp_Lok_GetTxActiveBits(ChannelId), CANTP_FC_DISABLED))
    {
        CanTp_Channel[ChannelId].BlockCfsRemaining = CanTp_Lok_GetTxBlockCfs(ChannelId);
        CanTp_Channel[ChannelId].STminTicks = CANTP_DEFAULT_STMIN_TICKS;
        CanTp_SubState[ChannelId] = CANTP_TX_SEND_CONSECUTIVE_FRAME;
    }
    else
    #endif
    {
        CanTp_SubState[ChannelId] = CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME;
    }

	CanTp_Channel[ChannelId].PciId = CANTP_NPCI_FC;
}

LOCAL_INLINE void CanTp_Lok_LengthError(const CanTp_RxContextType *Context)
{
    uint8 Api;

    Api = (Context->FrameType == CANTP_FLOWCONTROL_FRAME) ? CANTP_TX_PDUR_CONFIRMATION : CANTP_RX_PDUR_CONFIRMATION;
    SchM_Enter_CanTp_EXCLUSIVE_AREA();
    if((CanTp_SubState[Context->ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME) ||
       (CanTp_SubState[Context->ChannelId] == CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME))
    {
        CanTp_Lok_PduRConfirmation(Api, Context->PduRPduHandleId, E_NOT_OK);
        CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
    }
    SchM_Exit_CanTp_EXCLUSIVE_AREA();

    if(Context->IsPaddingOn)
    {
        CanTp_Lok_ReportError(CANTP_RXINDICATION, CANTP_E_PADDING);
    }
    else
    {
        CanTp_Lok_ReportRunTimeError(CANTP_RXINDICATION, CANTP_E_COM);
    }

}

#if((CANTP_DEV_ERROR_DETECT == CANTP_ON) && (CANTP_VARIANT == CANTP_POST_BUILD_SELECTABLE))

LOCAL_INLINE Std_ReturnType CanTp_Lok_PbCfgCheck(const Type_CfgSwcServiceCanTp_st *CfgPtr)
{
    Std_ReturnType retval = E_NOT_OK;
    uint8 ConfigId;

    for(ConfigId = 0; ConfigId < CANTP_NO_OF_CANTPCONFIGSETS; ConfigId++)
    {
        if(CanTp_CfgPtrs[ConfigId] == CfgPtr)
        {
            retval = E_OK;
            break;
        }
    }

    return retval;
}
#endif

#endif
