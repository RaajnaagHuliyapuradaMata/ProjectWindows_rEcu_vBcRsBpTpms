

#ifndef DCM_CBK_H
#define DCM_CBK_H

#include "Dcm_Cfg_DslDsd.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_TpRxIndication (
                                                VAR(PduIdType, AUTOMATIC) id,
                                                VAR(Std_ReturnType, AUTOMATIC) result
                                             );

extern FUNC(void,DCM_CODE) Dcm_TriggerTransmit(VAR(PduIdType,AUTOMATIC) TxPduId,P2VAR(PduInfoType,AUTOMATIC,DCM_INTERN_DATA) PduInfoPtr );

extern FUNC(void,DCM_CODE) Dcm_TxConfirmation ( VAR(PduIdType,AUTOMATIC) DcmTxPduId);

extern FUNC(void, DCM_CODE) Dcm_TpTxConfirmation (
                                                 VAR(PduIdType, AUTOMATIC) id,
                                                 VAR(Std_ReturnType, AUTOMATIC) result
                                               );

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_StartOfReception(VAR(PduIdType, AUTOMATIC) id,
                P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,VAR(PduLengthType, AUTOMATIC) TpSduLength,
                P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr);

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyRxData
(
	VAR(PduIdType, AUTOMATIC) id,
	P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
	P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr
);

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyTxData
(
	VAR(PduIdType, AUTOMATIC) id,
	P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
	P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) retry,
	P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) availableDataPtr
);

extern FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);

extern FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);

extern FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

