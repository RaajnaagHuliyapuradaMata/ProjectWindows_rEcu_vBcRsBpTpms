
#ifndef PDUR_DCM_H
#define PDUR_DCM_H

#include "PduR.hpp"

#include "Dcm.hpp"
#if(PDUR_ENABLE_INTER_MODULE_CHECKS)
#if(!defined(DCM_AR_RELEASE_MAJOR_VERSION) || (DCM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(DCM_AR_RELEASE_MINOR_VERSION) || (DCM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif
#include "Dcm_Cbk.hpp"

#define PduR_RF_Dcm_StartOfReception_Func        Dcm_StartOfReception
#define PduR_RF_Dcm_CopyRxData_Func              Dcm_CopyRxData
#define PduR_RF_Dcm_CopyTxData_Func              Dcm_CopyTxData
#define PduR_RF_Dcm_TpRxIndication_Func          Dcm_TpRxIndication
#define PduR_RF_Dcm_TpTxConfirmation_Func        Dcm_TpTxConfirmation

extern Std_ReturnType PduR_DcmTransmit( PduIdType id, const PduInfoType * ptr );

#endif
