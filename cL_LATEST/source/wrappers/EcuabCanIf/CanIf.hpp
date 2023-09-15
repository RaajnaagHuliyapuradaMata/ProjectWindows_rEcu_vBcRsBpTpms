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
extern void CanIf_Init(const Type_CfgEcuabCanIf_st * ConfigPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId
   ,       CanIf_ControllerModeType ControllerMode);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId
   ,       CanIf_ControllerModeType * ControllerModePtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_Transmit(Type_SwcServiceCom_tIdPdu CanIfTxSduId
   ,       const Type_SwcServiceCom_stInfoPdu * CanIfTxInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(STD_ON == CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_CancelTransmit(Type_SwcServiceCom_tIdPdu CanIfTxSduId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_SetPduMode(uint8 ControllerId
   ,       CanIf_PduModeType PduModeRequest);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_DeInit(const Type_CfgEcuabCanIf_st * ConfigPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(CANIF_DIRECT_HW_WRITE == STD_ON)
#define CANIF_START_SEC_CODE_FAST
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_Get_DirectHw_Info (Type_SwcServiceCom_tIdPdu CanTxPduId
   ,       rba_CanDirectHWInfo_o * hw_info_po);
#define CANIF_STOP_SEC_CODE_FAST
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE_FAST
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_DirectHw_Write(const uint32 * p_tx_data_buff_u32
        , uint32 data_len_u32, const rba_CanDirectHWInfo_o * hw_info_po);
#define CANIF_STOP_SEC_CODE_FAST
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_GetPduMode(
                                                         uint8 ControllerId
   ,                                                        CanIf_PduModeType * PduModePtr
                                                        );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_ReadRxPduData(Type_SwcServiceCom_tIdPdu CanIfRxSduId
   ,                                                       Type_SwcServiceCom_stInfoPdu * CanIfRxInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern CanIf_NotifStatusType CanIf_ReadTxNotifStatus(
                                                                      Type_SwcServiceCom_tIdPdu CanIfTxSduId
                                                                      );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern CanIf_NotifStatusType CanIf_ReadRxNotifStatus(Type_SwcServiceCom_tIdPdu CanIfRxSduId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(CANIF_PUBLIC_VERSIONINFO_API != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_GetVersionInfo (Std_VersionInfoType * VersionInfo);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#if(CANIF_PUBLIC_SETDYNAMICTXID_API != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_SetDynamicTxId(
                                                  Type_SwcServiceCom_tIdPdu CanTxPduId
   ,                                                 Can_IdType CanId
                                                   );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern void CanIf_ResetDynamicTxId(Type_SwcServiceCom_tIdPdu CanTxPduId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if((CANIF_WAKEUP_SUPPORT != STD_OFF) &&(CANIF_CFG_TRCV_WAKEUP_SUPPORT == STD_ON))
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_CheckWakeup (Type_SwcServiceEcuM_tSourceWakeup WakeupSource);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#if CANIF_CFG_TRCV_DRV_SUPPORT ==STD_ON
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_SetTrcvMode(
                                            uint8 TransceiverId
   ,                                           CanTrcv_TrcvModeType TransceiverMode
                                                          );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_GetTrcvMode(
                                            CanTrcv_TrcvModeType * TransceiverModePtr
   ,                                           uint8 TransceiverId
                                                           );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if CANIF_CFG_TRCV_DRV_SUPPORT!=STD_OFF
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_GetTrcvWakeupReason(
                                            uint8 TransceiverId
   ,                                           CanTrcv_TrcvWakeupReasonType * TrcvWuReasonPtr
                                                                 );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_SetTrcvWakeupMode(
                                                uint8 TransceiverId
   ,                                               CanTrcv_TrcvWakeupModeType TrcvWakeupMode
);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_ReturnRxPduId(
                                                     Type_SwcServiceCom_tIdPdu CanIfRxTargetPduId
   ,                                                   Type_SwcServiceCom_tIdPdu * CanIfRxPduIdPtr
                                                    );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_ReturnTxPduId(
                                                     Type_SwcServiceCom_tIdPdu CanIfTxTargetPduId
   ,                                                   Type_SwcServiceCom_tIdPdu * CanIfTxPduIdPtr
                                                    );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(CANIF_SET_BAUDRATE_API == STD_ON)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_SetBaudrate(
                                                uint8 ControllerId
   ,                                               const uint16 BaudRateConfigID
                                                );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#if(CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT != STD_OFF)
#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern CanIf_NotifStatusType CanIf_GetTxConfirmationState(
                                       uint8 ControllerId
                                               );
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
#endif

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_Rn_ReadTxPduCanId(
                                                    Type_SwcServiceCom_tIdPdu CanIfTxPduId
   ,                                                   uint32 * TxPduCanId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
extern Std_ReturnType CanIf_Rn_ReadRxPduCanId( Type_SwcServiceCom_tIdPdu CanIfRxPduId
   ,       uint32 * RxPduCanId);
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif
