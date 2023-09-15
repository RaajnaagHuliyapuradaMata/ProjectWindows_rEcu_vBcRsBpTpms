#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

#include "Std_Types.hpp"
#include "ComStack_Cfg.hpp"

#define COMTYPE_VENDOR_ID 0x0006u
#define COMTYPE_MODULE_ID 0x00C4u
#define COMTYPE_SW_MAJOR_VERSION 0x08u
#define COMTYPE_SW_MINOR_VERSION 0x00u
#define COMTYPE_SW_PATCH_VERSION 0x00u
#define COMTYPE_AR_RELEASE_MAJOR_VERSION 0x04u
#define COMTYPE_AR_RELEASE_MINOR_VERSION 0x02u
#define COMTYPE_AR_RELEASE_REVISION_VERSION 0x02u

#define NTFRSLT_OK                     0x00u
#define NTFRSLT_E_NOT_OK               0x01u
#define NTFRSLT_E_TIMEOUT_A            0x02u
#define NTFRSLT_E_TIMEOUT_BS           0x03u
#define NTFRSLT_E_TIMEOUT_CR           0x04u
#define NTFRSLT_E_WRONG_SN             0x05u
#define NTFRSLT_E_INVALID_FS           0x06u
#define NTFRSLT_E_UNEXP_PDU            0x07u
#define NTFRSLT_E_WFT_OVRN             0x08u
#define NTFRSLT_E_ABORT                0x09u
#define NTFRSLT_E_NO_BUFFER            0x0Au
#define NTFRSLT_E_CANCELATION_OK       0x0Bu
#define NTFRSLT_E_CANCELATION_NOT_OK   0x0Cu
#define NTFRSLT_PARAMETER_OK           0x0Du
#define NTFRSLT_E_PARAMETER_NOT_OK     0x0Eu
#define NTFRSLT_E_RX_ON                0x0Fu
#define NTFRSLT_E_VALUE_NOT_OK         0x10u

typedef struct{
   P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) SduDataPtr;
   P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA) MetaDataPtr;
   PduLengthType SduLength;
}PduInfoType;

typedef uint8   PNCHandleType;

typedef enum{
   TP_STMIN = 0x00
   ,  TP_BS    = 0x01
   ,  TP_BC    = 0x02
   ,  TP_BFS   = 0x03
}TPParameterType;

typedef enum{
   BUFREQ_OK       = 0x00
   ,  BUFREQ_E_NOT_OK = 0x01
   ,  BUFREQ_E_BUSY   = 0x02
   ,  BUFREQ_E_OVFL   = 0x03
}BufReq_ReturnType;

typedef uint8   NotifResultType;
typedef uint8   BusTrcvErrorType;

#define BUSTRCV_OK                     0x00
#define BUSTRCV_E_ERROR                0x01

typedef enum{
   TP_DATACONF = 0x00
   ,  TP_DATARETRY = 0x01
   ,  TP_CONFPENDING = 0x02
}TpDataStateType;

typedef struct{
   TpDataStateType TpDataState;
   PduLengthType TxTpDataCnt;
}RetryInfoType;

typedef uint8   NetworkHandleType;
typedef uint8   IcomConfigIdType;

typedef enum{
   ICOM_SWITCH_E_OK
   ,  ICOM_SWITCH_E_FAILED
}IcomSwitch_ErrorType;

#endif

