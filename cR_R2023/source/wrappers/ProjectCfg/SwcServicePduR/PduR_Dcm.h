
#ifndef PDUR_DCM_H
#define PDUR_DCM_H

#include "PduR.h"

#include "Dcm.h"
#if (!defined(DCM_AR_RELEASE_MAJOR_VERSION) || (DCM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DCM_AR_RELEASE_MINOR_VERSION) || (DCM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "Dcm_Cbk.h"

#define PduR_RF_Dcm_StartOfReception_Func        Dcm_StartOfReception
#define PduR_RF_Dcm_CopyRxData_Func              Dcm_CopyRxData
#define PduR_RF_Dcm_CopyTxData_Func              Dcm_CopyTxData
#define PduR_RF_Dcm_TpRxIndication_Func          Dcm_TpRxIndication
#define PduR_RF_Dcm_TpTxConfirmation_Func        Dcm_TpTxConfirmation

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmCancelTransmit( VAR(PduIdType,AUTOMATIC) id);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmChangeParameter(VAR(PduIdType, AUTOMATIC) id,
                                                           VAR(TPParameterType, AUTOMATIC) parameter,
                                                           VAR(uint16, AUTOMATIC) value);

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmReadParameter(VAR(PduIdType, AUTOMATIC) id,
                                                          VAR(TPParameterType, AUTOMATIC) parameter,
                                                          P2VAR(uint16, AUTOMATIC, PDUR_APPL_DATA) value);
#endif
