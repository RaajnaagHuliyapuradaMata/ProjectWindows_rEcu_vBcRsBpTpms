#ifndef DCM_CBK_H
#define DCM_CBK_H

#include "Dcm_Cfg_DslDsd.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void, DCM_CODE) Dcm_TpRxIndication (
                                                VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     VAR(Std_ReturnType, AUTOMATIC) result
);

extern FUNC(void,DCM_CODE) Dcm_TriggerTransmit(VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) TxPduId,P2VAR(Type_SwcServiceCom_stInfoPdu,AUTOMATIC,DCM_INTERN_DATA) PduInfoPtr );
extern FUNC(void,DCM_CODE) Dcm_TxConfirmation ( VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC) DcmTxPduId);
extern FUNC(void, DCM_CODE) Dcm_TpTxConfirmation (
      VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     VAR(Std_ReturnType, AUTOMATIC) result
);

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_StartOfReception(VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,     P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) info,VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC) TpSduLength
   ,     P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr);

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyRxData
(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr
   ,  P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr
);

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyTxData
(
   VAR(Type_SwcServiceCom_tIdPdu, AUTOMATIC) id
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, DCM_APPL_DATA) info
   ,  P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) retry
   ,  P2VAR(Type_SwcServiceCom_tLengthPdu, AUTOMATIC, DCM_APPL_DATA) availableDataPtr
);

extern FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);
extern FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);
extern FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

