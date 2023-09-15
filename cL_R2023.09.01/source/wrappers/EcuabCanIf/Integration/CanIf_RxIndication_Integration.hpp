
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef CANIF_RX_INDICATION_MCAL_VERSION_H
#define CANIF_RX_INDICATION_MCAL_VERSION_H

#define CANIF_RX_INDICATION_VERSION (2U)

#include "CanIf.hpp"

#include "CanIf_Cfg_SymbolicNames.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"

#if(CANIF_RX_INDICATION_VERSION < 1)
extern FUNC(void, CANIF_CODE) CanIf_RxIndication(
                                                 VAR(Can_HwHandleType, AUTOMATIC) Hrh
   ,                                                VAR(Can_IdType, AUTOMATIC) CanId
   ,                                                VAR(uint8, AUTOMATIC) CanDlc
   ,                                                P2CONST (uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr
                                                );
#elif(CANIF_RX_INDICATION_VERSION >= 1)
extern FUNC(void, CANIF_CODE) CanIf_RxIndication(
                                            P2CONST (Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox
   ,                                           P2CONST (PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
                                         );
#endif

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif
