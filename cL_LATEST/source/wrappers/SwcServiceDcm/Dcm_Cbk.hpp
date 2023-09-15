

#ifndef DCM_CBK_H
#define DCM_CBK_H

#include "Dcm_Cfg_DslDsd.hpp"

#define DCM_START_SEC_CODE
//#include "Dcm_Cfg_MemMap.hpp"
#include "Dcm_Cfg_MemMap.hpp"				//RST 2021-09-28, BSW6.0 uses this file instead of Dcm_Cfg_memmap

extern void Dcm_TpRxIndication (Type_SwcServiceCom_tIdPdu id,Std_ReturnType result);

extern void Dcm_TriggerTransmit(Type_SwcServiceCom_tIdPdu TxPduId,Type_SwcServiceCom_stInfoPdu * PduInfoPtr );

extern void Dcm_TxConfirmation (Type_SwcServiceCom_tIdPdu DcmTxPduId);

extern void Dcm_TpTxConfirmation (Type_SwcServiceCom_tIdPdu id,Std_ReturnType result);

extern BufReq_ReturnType Dcm_StartOfReception(Type_SwcServiceCom_tIdPdu id
   ,               const Type_SwcServiceCom_stInfoPdu * info,Type_SwcServiceCom_tLengthPdu TpSduLength
   ,               Type_SwcServiceCom_tLengthPdu * bufferSizePtr);

extern BufReq_ReturnType Dcm_CopyRxData
(
   Type_SwcServiceCom_tIdPdu id
   ,  const Type_SwcServiceCom_stInfoPdu * PduInfoPtr
   ,  Type_SwcServiceCom_tLengthPdu * bufferSizePtr
);

extern BufReq_ReturnType Dcm_CopyTxData
(
   Type_SwcServiceCom_tIdPdu id
   ,  const Type_SwcServiceCom_stInfoPdu * info
   ,  RetryInfoType * retry
   ,  Type_SwcServiceCom_tLengthPdu * availableDataPtr
);

extern void Dcm_ComM_NoComModeEntered(uint8 NetworkId);

extern void Dcm_ComM_SilentComModeEntered(uint8 NetworkId);

extern void Dcm_ComM_FullComModeEntered(uint8 NetworkId);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

