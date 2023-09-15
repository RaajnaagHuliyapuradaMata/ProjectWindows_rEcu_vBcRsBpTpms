

#ifndef COM_H
#define COM_H

#include "ComStack_Types.hpp"
#include "Com_Cfg.hpp"

#if(COM_ENABLE_INTER_MODULE_CHECKS)

#if(!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#define COM_E_PARAM                                                 0x01

#define COM_E_UNINIT                                                0x02

#define COM_E_PARAM_POINTER                                         0x03

#define COM_SERVICE_NOT_AVAILABLE                                   0x80

#define COM_BUSY                                                    0x81

#define COM_INSTANCE_ID                                             0u

#define COMServiceId_Init                                           0x01

#define COMServiceId_Deinit                                         0x02

#define COMServiceId_IpduGroupControl                               0x03

#define COMServiceId_ReceptionDMControl                             0x06

#define COMServiceId_GetStatus                                      0x07

#define COMServiceId_GetVersionInfo                                 0x09

#define COMServiceId_SendSignal                                     0x0A

#define COMServiceId_ReceiveSignal                                  0x0B

#define COMServiceId_ReceiveDynSignal                               0x22

#define COMServiceId_SendDynSignal                                  0x21

#define COMServiceId_UpdateShadowSignal                             0x0C

#define COMServiceId_SendSignalGroup                                0x0D

#define COMServiceId_ReceiveSignalGroup                             0x0E

#define COMServiceId_ReceiveShadowSignal                            0x0F

#define COMServiceId_InvalidateSignal                               0x10

#define COMServiceId_InvalidateShadowSignal                         0x16

#define COMServiceId_InvalidateSignalGroup                          0x1B

#define COMServiceId_TriggerIpduSend                                0x17

#define COMServiceId_MainFunctionRx                                 0x18

#define COMServiceId_MainFunctionTx                                 0x19

#define COMServiceId_MainFunctionRouteSignals                       0x1A

#define COMServiceId_TxConfirmation                                 0x40

#define COMServiceId_TriggerTransmit                                0x41

#define COMServiceId_RxIndication                                   0x42

#define COMServiceId_ClearIpduGroupVector                           0x1C

#define COMServiceId_SetIpduGroup                                   0x1D

#define COMServiceId_SwitchIpduTxMode                               0x27

#define COMServiceId_StartOfReception                               0x25

#define COMServiceId_CopyRxData                                     0x44

#define COMServiceId_CopyTxData                                     0x43

#define COMServiceId_TpRxIndication                                 0x1E

#define COMServiceId_TpTxConfirmation                               0x26

#define COMServiceId_TriggerIPDUSendWithMetaData                    0x28

#define COMServiceId_SendSignalGroupArray                           0x23

#define COMServiceId_ReceiveSignalGroupArray                        0x24

#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
#define COMServiceId_SetRxIPduControlViaRbaNdsEcuVariant            0x91
#endif

#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
#define COMServiceId_SetTxIPduControlViaRbaNdsEcuVariant            0x92
#endif

#define COMServiceId_ReadRxIPduLength                               0x95u

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_Init(const Type_CfgSwcServiceCom_st * config);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_DeInit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType IpduGroupId, boolean bitval);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern Com_StatusType Com_GetStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_GetVersionInfo(Std_VersionInfoType * versioninfo);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_SendSignal(Com_SignalIdType SignalId, const void * SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void * SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_InvalidateSignal(Com_SignalIdType SignalId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#ifdef COM_TX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_UpdateShadowSignal(Com_SignalIdType SignalId, const void * SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_InvalidateShadowSignal(Com_SignalIdType SignalId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#ifdef COM_RX_SIGNALGROUP

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_ReceiveShadowSignal(Com_SignalIdType SignalId, void * SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"
#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_SendDynSignal(Com_SignalIdType SignalId, const void * SignalDataPtr, uint16 Length);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_ReceiveDynSignal(Com_SignalIdType SignalId, void * SignalDataPtr, uint16 * LengthPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_SendSignalGroupArray(Com_SignalGroupIdType SignalGroupId, const uint8 *SignalGroupArrayPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_ReceiveSignalGroupArray(Com_SignalGroupIdType SignalGroupId, uint8 *SignalGroupArrayPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_TriggerIPDUSend(Type_SwcServiceCom_tIdPdu PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern Std_ReturnType Com_TriggerIPDUSendWithMetaData(Type_SwcServiceCom_tIdPdu PduId, uint8 * MetaData);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern Std_ReturnType Com_TriggerTransmit(Type_SwcServiceCom_tIdPdu TxPduId, Type_SwcServiceCom_stInfoPdu * PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_RxIndication(Type_SwcServiceCom_tIdPdu RxPduId, const Type_SwcServiceCom_stInfoPdu * PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
#ifdef COM_ECUC_AR_RELEASE_AR45
extern void Com_TxConfirmation(Type_SwcServiceCom_tIdPdu TxPduId,Std_ReturnType result);
#else
extern void Com_TxConfirmation(Type_SwcServiceCom_tIdPdu TxPduId);
#endif
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#if( COM_ECUC_RB_RTE_IN_USE == STD_OFF )
#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_MainFunctionRouteSignals(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_ReduceBusload(uint16 CommonPeriod);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_RestoreBusload(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern boolean Com_IsTxScheduled(Type_SwcServiceCom_tIdPdu ComTxPduId, uint16 ComCallerTaskCycle);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern uint8 Com_ReadRxIPduLength(Type_SwcServiceCom_tIdPdu RxPduId, Type_SwcServiceCom_tLengthPdu * RxIPduLengthPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_SwitchIpduTxMode(Type_SwcServiceCom_tIdPdu PduId, boolean Mode);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern boolean Com_ProvideRxIpduStatus(Type_SwcServiceCom_tIdPdu PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern boolean Com_ProvideTxIpduStatus(Type_SwcServiceCom_tIdPdu PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern BufReq_ReturnType Com_StartOfReception(Type_SwcServiceCom_tIdPdu ComRxPduId, const Type_SwcServiceCom_stInfoPdu* PduInfoPtr, Type_SwcServiceCom_tLengthPdu TpSduLength, Type_SwcServiceCom_tLengthPdu* RxBufferSizePtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern BufReq_ReturnType Com_CopyRxData(Type_SwcServiceCom_tIdPdu PduId,const Type_SwcServiceCom_stInfoPdu* PduInfoPtr, Type_SwcServiceCom_tLengthPdu* RxBufferSizePtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern BufReq_ReturnType Com_CopyTxData(Type_SwcServiceCom_tIdPdu PduId, const Type_SwcServiceCom_stInfoPdu* PduInfoPtr, RetryInfoType* RetryInfoPtr, Type_SwcServiceCom_tLengthPdu* availableDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_TpRxIndication(Type_SwcServiceCom_tIdPdu PduId, Std_ReturnType Result);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_TpTxConfirmation(Type_SwcServiceCom_tIdPdu PduId, Std_ReturnType Result);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_SetTxIPduControlViaRbaNdsEcuVariant(Type_SwcServiceCom_tIdPdu IpduId, boolean IpduStatus);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern void Com_SetRxIPduControlViaRbaNdsEcuVariant(Type_SwcServiceCom_tIdPdu IpduId, boolean IpduStatus);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"
extern Std_ReturnType Com_SetRxIPduTimeoutTicks(Type_SwcServiceCom_tIdPdu rxPduId_uo, uint16 timeoutTicks_u16);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

