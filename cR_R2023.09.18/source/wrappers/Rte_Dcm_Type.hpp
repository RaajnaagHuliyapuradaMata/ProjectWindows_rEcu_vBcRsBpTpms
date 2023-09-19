

#ifndef _RTE_DCM_TYPE_H_
#define _RTE_DCM_TYPE_H_

#include "types.hpp"

typedef enum{
  DCM_OBD_ON_CAN                = 0x00, //OBD on CAN (ISO15765-4; ISO15031-5)
  DCM_OBD_ON_FLEXRAY            = 0x01, //(OBD on Flexray (Manufacturer specific; ISO15031-5))
  DCM_OBD_ON_IP                 = 0x02, //(OBD on Internet Protocol (Manufacturer specific; ISO15031-5))
  DCM_UDS_ON_CAN                = 0x03, //UDS on CAN (ISO15765-3; ISO14229-1)
  DCM_UDS_ON_FLEXRAY            = 0x04, //UDS on FlexRay (Manufacturer specific; ISO14229-1)
  DCM_UDS_ON_IP                 = 0x05, //(UDS on Internet Protocol (Manufacturer specific; ISO14229-1))
  DCM_ROE_ON_CAN                = 0x06, //Response On Event on CAN
  DCM_ROE_ON_FLEXRAY            = 0x07, //Response On Event on FlexRay
  DCM_ROE_ON_IP                 = 0x08, //(Response on Event on Internet Protocol)
  DCM_PERIODICTRANS_ON_CAN      = 0x09, //Periodic Transmission on CAN
  DCM_PERIODICTRANS_ON_FLEXRAY  = 0x0A, //Periodic Transmission on FlexRay
  DCM_PERIODICTRANS_ON_IP       = 0x0B,   //(Periodic Transmission on Internet Protocol)
  DCM_NO_ACTIVE_PROTOCOL        = 0x0C
}Dcm_ProtocolType;

typedef enum{
  DCM_DID_SUPPORTED     = 0x00
   ,  DCM_DID_NOT_SUPPORTED = 0x01
}
Dcm_DidSupportedType;

typedef enum{
  DCM_DEFAULT_SESSION                   = 0x01
   ,  DCM_PROGRAMMING_SESSION               = 0x02
   ,  DCM_EXTENDED_DIAGNOSTIC_SESSION       = 0x03
   ,  //0x40...0x7E  configuration dependent
  DCM_BH_SENS_EOL_SESSION               = 0x60
}Dcm_SesCtrlType;

typedef uint8 Dcm_ConfirmationStatusType;
typedef uint8 Dcm_OpStatusType;
typedef uint8 Dcm_NegativeResponseCodeType; //Negativ response codes: Dcm_Types.h or see AUTOSAR_SWS_DiagnosticCommunicationManager.pdf Chapter 8.8.1.6
typedef uint8 Dcm_SecLevelType;

#endif
