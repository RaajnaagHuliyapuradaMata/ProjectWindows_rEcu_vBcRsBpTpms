
#ifndef PDUR_COM_H
#define PDUR_COM_H

#include "PduR.hpp"

#include "Com.hpp"
#if(PDUR_ENABLE_INTER_MODULE_CHECKS)
#if(!defined(COM_AR_RELEASE_MAJOR_VERSION) || (COM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(COM_AR_RELEASE_MINOR_VERSION) || (COM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#define PduR_RF_Com_TpTxConfirmation_Func        Com_TpTxConfirmation

#define PduR_RF_Com_StartOfReception_Func        Com_StartOfReception

#define PduR_RF_Com_TpRxIndication_Func          Com_TpRxIndication

#define PduR_RF_Com_CopyRxData_Func              Com_CopyRxData

#define PduR_RF_Com_CopyTxData_Func              Com_CopyTxData

#define PduR_RF_Com_TriggerTransmit_Func       Com_TriggerTransmit

#define PduR_RF_Com_RxIndication_Func          Com_RxIndication

#define PduR_RF_Com_TxConfirmation_Func        Com_TxConfirmation

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

extern Std_ReturnType PduR_ComTransmit( PduIdType id, const PduInfoType * ptr );

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"
#endif
