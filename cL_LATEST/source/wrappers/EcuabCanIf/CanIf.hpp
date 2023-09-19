#ifndef CANIF_H
#define CANIF_H

#include "CanIf_Types.hpp"

#include "CanIf_Cfg.hpp"

#if(CANIF_CONFIGURATION_VARIANT == CANIF_CFG_VAR_PBS)
#include "CanIf_Types.hpp"
#endif

#define CANIF_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.hpp"
extern const Type_CfgEcuabCanIf_st * CanIf_Lok_ConfigSet_tpst;
#define CANIF_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_Init(P2CONST (Type_CfgEcuabCanIf_st, AUTOMATIC, CANIF_APPL_CONST) ConfigPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(VAR (uint8,AUTOMATIC) ControllerId
   ,     VAR(CanIf_ControllerModeType,AUTOMATIC) ControllerMode);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerMode(VAR(uint8,AUTOMATIC) ControllerId
   ,     P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) CanIfTxSduId
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_APPL_CONST) CanIfTxInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(STD_ON == CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CancelTransmit(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) CanIfTxSduId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode(VAR(uint8,AUTOMATIC) ControllerId
   ,     VAR(CanIf_PduModeType,AUTOMATIC) PduModeRequest);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_DeInit(P2CONST (Type_CfgEcuabCanIf_st, AUTOMATIC, CANIF_APPL_CONST) ConfigPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(CANIF_DIRECT_HW_WRITE == STD_ON)
#define CANIF_START_SEC_CODE_FAST
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_Get_DirectHw_Info (VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) CanTxPduId
   ,     P2VAR(rba_CanDirectHWInfo_o, AUTOMATIC, CANIF_APPL_DATA) hw_info_po);
#define CANIF_STOP_SEC_CODE_FAST
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE_FAST
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_DirectHw_Write(P2CONST(uint32, AUTOMATIC, CANIF_APPL_DATA) p_tx_data_buff_u32
        , VAR(uint32, AUTOMATIC) data_len_u32, P2CONST(rba_CanDirectHWInfo_o, AUTOMATIC, CANIF_APPL_DATA) hw_info_po);
#define CANIF_STOP_SEC_CODE_FAST
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetPduMode(
                                                         VAR(uint8,AUTOMATIC) ControllerId
   ,     P2VAR(CanIf_PduModeType, AUTOMATIC,CANIF_APPL_DATA) PduModePtr
                                                        );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReadRxPduData(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) CanIfRxSduId
   ,     P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_APPL_CONST)CanIfRxInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadTxNotifStatus(
                                                                      VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) CanIfTxSduId
                                                                      );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadRxNotifStatus(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) CanIfRxSduId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(CANIF_PUBLIC_VERSIONINFO_API != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA) VersionInfo);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#if(CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_SetDynamicTxId(
                                                  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) CanTxPduId
   ,     VAR(Can_IdType,AUTOMATIC) CanId
                                                   );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(void, CANIF_CODE) CanIf_ResetDynamicTxId(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) CanTxPduId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if((CANIF_WAKEUP_SUPPORT != STD_OFF) &&(CANIF_CFG_TRCV_WAKEUP_SUPPORT == STD_ON))
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup (VAR(Type_SwcServiceEcuM_tSourceWakeup, AUTOMATIC) WakeupSource);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT ==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvMode(
                                            VAR(uint8, AUTOMATIC) TransceiverId
   ,     VAR(CanTrcv_TrcvModeType, AUTOMATIC) TransceiverMode
                                                          );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvMode(
                                            P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANIF_APPL_DATA) TransceiverModePtr
   ,     VAR(uint8, AUTOMATIC) TransceiverId
                                                           );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if CANIF_CFG_TRCV_DRV_SUPPORT!=STD_OFF
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason(
                                            VAR(uint8, AUTOMATIC) TransceiverId
   ,     P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_DATA) TrcvWuReasonPtr
                                                                 );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvWakeupMode(
                                                VAR(uint8, AUTOMATIC) TransceiverId
   ,     VAR(CanTrcv_TrcvWakeupModeType, AUTOMATIC) TrcvWakeupMode
);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReturnRxPduId(
                                                     VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) CanIfRxTargetPduId
   ,     P2VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC, CANIF_APPL_CONST) CanIfRxPduIdPtr
                                                    );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReturnTxPduId(
                                                     VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) CanIfTxTargetPduId
   ,     P2VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC, CANIF_APPL_CONST) CanIfTxPduIdPtr
                                                    );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(CANIF_SET_BAUDRATE_API == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetBaudrate(
                                                VAR (uint8,AUTOMATIC) ControllerId
   ,     CONST(uint16,AUTOMATIC) BaudRateConfigID
                                                );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#if(CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_GetTxConfirmationState(
                                       VAR(uint8,AUTOMATIC) ControllerId
                                               );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_Rn_ReadTxPduCanId(
                                                    VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) CanIfTxPduId
   ,     P2VAR(uint32, AUTOMATIC, AUTOMATIC) TxPduCanId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_Rn_ReadRxPduCanId( VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC)CanIfRxPduId
   ,     P2VAR(uint32, AUTOMATIC, CANIF_APPL_DATA)RxPduCanId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif
