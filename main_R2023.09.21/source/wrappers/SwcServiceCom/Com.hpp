#ifndef COM_H
#define COM_H

#include "ComStack_Types.hpp"
#include "Com_Cfg.hpp"

#if(!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define COM_E_PARAM         0x01

#define COM_E_UNINIT        0x02

#define COM_E_PARAM_POINTER    0x03

#define COM_SERVICE_NOT_AVAILABLE   0x80

#define COM_BUSY                    0x81

#define COM_INSTANCE_ID  0u

#define COMServiceId_Init                       0x01

#define COMServiceId_Deinit                     0x02

#define COMServiceId_IpduGroupControl           0x03

#define COMServiceId_ReceptionDMControl            0x06

#define COMServiceId_GetStatus                  0x07

#define COMServiceId_GetVersionInfo             0x09

#define COMServiceId_SendSignal                 0x0a

#define COMServiceId_ReceiveSignal              0x0b

#define COMServiceId_ReceiveDynSignal           0x22

#define COMServiceId_SendDynSignal              0x21

#define COMServiceId_UpdateShadowSignal         0x0c

#define COMServiceId_SendSignalGroup            0x0d

#define COMServiceId_ReceiveSignalGroup         0x0e

#define COMServiceId_ReceiveShadowSignal        0x0f

#define COMServiceId_InvalidateSignal           0x10

#define COMServiceId_InvalidateShadowSignal     0x16

#define COMServiceId_InvalidateSignalGroup      0x1b

#define COMServiceId_TriggerIpduSend            0x17

#define COMServiceId_MainFunctionRx             0x18

#define COMServiceId_MainFunctionTx             0x19

#define COMServiceId_MainFunctionRouteSignals   0x1a

#define COMServiceId_TxConfirmation             0x40

#define COMServiceId_TriggerTransmit            0x41

#define COMServiceId_RxIndication               0x42

#define COMServiceId_ClearIpduGroupVector        0x1C

#define COMServiceId_SetIpduGroup               0x1D

#define COMServiceId_SwitchIpduTxMode           0x27

#define COMServiceId_StartOfReception           0x25

#define COMServiceId_CopyRxData                 0x44

#define COMServiceId_CopyTxData                 0x43

#define COMServiceId_TpRxIndication             0x1E

#define COMServiceId_TpTxConfirmation           0x26

#define COMServiceId_TriggerIPDUSendWithMetaData    0x28

#define COMServiceId_SendSignalGroupArray       0x23

#define COMServiceId_ReceiveSignalGroupArray    0x24

#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

#define COMServiceId_SetRxIPduControlViaRbaNdsEcuVariant       0x91
#endif
#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT

#define COMServiceId_SetTxIPduControlViaRbaNdsEcuVariant    0x92
#endif

#include "CfgSwcServiceCom.hpp"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"
extern CONST(Type_CfgSwcServiceCom_st, COM_CONST) ComConfig;
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_Init(P2CONST(Type_CfgSwcServiceCom_st, AUTOMATIC, COM_APPL_CONST) config);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_DeInit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_IpduGroupControl(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector, VAR(boolean, AUTOMATIC) initialize );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_ClearIpduGroupVector(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_SetIpduGroup(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector, VAR(Com_IpduGroupIdType, AUTOMATIC) IpduGroupId, VAR(boolean, AUTOMATIC) bitval );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_ReceptionDMControl(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COM_APPL_DATA) versioninfo);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_SendSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId,P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_InvalidateSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_UpdateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId,P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_SendSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_InvalidateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif
#ifdef COM_RX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_ReceiveShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId,P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_SendDynSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     VAR(uint16, AUTOMATIC) Length);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_ReceiveDynSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId,P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
   ,     P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) LengthPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
# include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_SendSignalGroupArray( Com_SignalGroupIdType  SignalGroupId
   ,     const uint8 *SignalGroupArrayPtr );
#define COM_STOP_SEC_CODE
# include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
# include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray( Com_SignalGroupIdType  SignalGroupId
   ,     uint8 *SignalGroupArrayPtr );
#define COM_STOP_SEC_CODE
# include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_TriggerIPDUSend(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

extern FUNC(Std_ReturnType, COM_CODE ) Com_TriggerIPDUSendWithMetaData( VAR( Type_SwcServiceCom_tIdPdu, AUTOMATIC ) PduId
   ,     P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) MetaData );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) TxPduId,P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_RxIndication(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) RxPduId,P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_TxConfirmation(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) TxPduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#if( COM_ECUC_RB_RTE_IN_USE == STD_OFF )
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_MainFunctionRouteSignals(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_ReduceBusload(VAR(uint16, AUTOMATIC) CommonPeriod);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_RestoreBusload (void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(boolean, COM_CODE) Com_IsTxScheduled(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) ComTxPduId, VAR(uint16, AUTOMATIC)ComCallerTaskCycle);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(uint8, COM_CODE) Com_ReadRxIPduLength(
                                      VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)                     RxPduId
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu,AUTOMATIC,COM_APPL_DATA) RxIPduLengthPtr
                                                 );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void,COM_CODE) Com_SwitchIpduTxMode(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) PduId, VAR(boolean, AUTOMATIC)  Mode);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(boolean,COM_CODE) Com_ProvideRxIpduStatus(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(boolean,COM_CODE) Com_ProvideTxIpduStatus(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(BufReq_ReturnType, COM_CODE) Com_StartOfReception(Type_SwcServiceCom_tIdPdu ComRxPduId,const Type_SwcServiceCom_stInfoPdu* TpSduInfoPtr, Type_SwcServiceCom_tLengthPdu TpSduLength, Type_SwcServiceCom_tLengthPdu* RxBufferSizePtr );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData( Type_SwcServiceCom_tIdPdu PduId,const Type_SwcServiceCom_stInfoPdu* PduInfoPointer, Type_SwcServiceCom_tLengthPdu* RxBufferSizePtr );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(BufReq_ReturnType, COM_CODE) Com_CopyTxData( Type_SwcServiceCom_tIdPdu PduId, const Type_SwcServiceCom_stInfoPdu* PduInfoPtr, RetryInfoType* RetryInfoPtr, Type_SwcServiceCom_tLengthPdu* TxDataCntPtr );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_TpRxIndication( Type_SwcServiceCom_tIdPdu PduId, Std_ReturnType Result );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_TpTxConfirmation( Type_SwcServiceCom_tIdPdu PduId, Std_ReturnType Result );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_SetTxIPduControlViaRbaNdsEcuVariant(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) IpduId, VAR(boolean, AUTOMATIC) IpduStatus);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern FUNC(void, COM_CODE) Com_SetRxIPduControlViaRbaNdsEcuVariant(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) IpduId, VAR(boolean, AUTOMATIC) IpduStatus);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

