

#ifndef DCM_CBK_H
#define DCM_CBK_H

#include "Dcm_Cfg_DslDsd.h"

#define DCM_START_SEC_CODE
//#include "Dcm_Cfg_MemMap.h"
#include "Dcm_MemMap.h"				//RST 2021-09-28, BSW6.0 uses this file instead of Dcm_Cfg_memmap

extern void Dcm_TpRxIndication (PduIdType id,Std_ReturnType result);

extern void Dcm_TriggerTransmit(PduIdType TxPduId,PduInfoType * PduInfoPtr );

extern void Dcm_TxConfirmation (PduIdType DcmTxPduId);

extern void Dcm_TpTxConfirmation (PduIdType id,Std_ReturnType result);

extern BufReq_ReturnType Dcm_StartOfReception(PduIdType id,
                const PduInfoType * info,PduLengthType TpSduLength,
                PduLengthType * bufferSizePtr);

extern BufReq_ReturnType Dcm_CopyRxData
(
	PduIdType id,
	const PduInfoType * PduInfoPtr,
	PduLengthType * bufferSizePtr
);

extern BufReq_ReturnType Dcm_CopyTxData
(
	PduIdType id,
	const PduInfoType * info,
	RetryInfoType * retry,
	PduLengthType * availableDataPtr
);

extern void Dcm_ComM_NoComModeEntered(uint8 NetworkId);

extern void Dcm_ComM_SilentComModeEntered(uint8 NetworkId);

extern void Dcm_ComM_FullComModeEntered(uint8 NetworkId);

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

