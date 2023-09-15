#ifndef PDUR_CANIF_H
#define PDUR_CANIF_H

#include "PduR.hpp"

#include "CanIf.hpp"
#if(PDUR_ENABLE_INTER_MODULE_CHECKS)
#if(!defined(CANIF_AR_RELEASE_MAJOR_VERSION) || (CANIF_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(CANIF_AR_RELEASE_MINOR_VERSION) || (CANIF_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#define PduR_RF_CanIf_Transmit_Func   CanIf_Transmit

extern void PduR_CanIfRxIndication( PduIdType id
   ,                                                     const PduInfoType * ptr );

extern void PduR_CanIfTxConfirmation(PduIdType id);

#endif
