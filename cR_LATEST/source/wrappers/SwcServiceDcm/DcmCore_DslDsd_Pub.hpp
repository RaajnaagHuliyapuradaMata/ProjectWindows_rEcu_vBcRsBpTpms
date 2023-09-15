#ifndef DCMCORE_DSLDSD_PUB_H
#define DCMCORE_DSLDSD_PUB_H

#define DCM_BOOLEAN                     0x00u
#define DCM_UINT8                       0x01u
#define DCM_UINT16                      0x02u
#define DCM_UINT32                      0x03u
#define DCM_SINT8                       0x04u
#define DCM_SINT16                      0x05u
#define DCM_SINT32                      0x06u
#define DCM_VARIABLE_LENGTH             0x07u
#define DCM_UINT8_N                     0x08u
#define DCM_UINT16_N                    0x09u
#define DCM_UINT32_N                    0x0Au
#define DCM_SINT8_N                     0x0Bu
#define DCM_SINT16_N                    0x0Cu
#define DCM_SINT32_N                    0x0Du
#define DCM_RCARRAYINDEX  0x08u
#define DCM_LITTLE_ENDIAN               0x00u
#define DCM_BIG_ENDIAN                  0x01u
#define DCM_OPAQUE                      0x02u

typedef uint8 Dcm_SrvOpStatusType;

#define DsdInternal_SetNegResponse  Dcm_SetNegResponse
#define DsdInternal_ProcessingDone  Dcm_ProcessingDone

typedef struct{
   uint8  ProtocolId;
   uint8  Sid;
   uint8  SubFncId;
   uint8  StoreType;
   uint8  SessionLevel;
   uint8  SecurityLevel;
   uint8  ReqResLen;
   uint8  NumWaitPend;
   uint8  ReqResBuf[8];
   uint16 TesterSourceAddr;
   uint32 ElapsedTime;
   boolean ReprogramingRequest;
   boolean ApplUpdated;
   boolean ResponseRequired;
   uint8 freeForProjectUse[6];
}Dcm_ProgConditionsType;

typedef uint8 Dcm_EcuStartModeType;
#define DCM_COLD_START   0x0u
#define DCM_WARM_START   0x1u
#define DCM_VENDOR_ID                   6u
#define DCM_MODULE_ID                   0x35u
#define DCM_INSTANCE_ID                 0x00u
#define DCM_AR_RELEASE_MAJOR_VERSION    4u
#define DCM_AR_RELEASE_MINOR_VERSION    2u
#define DCM_AR_RELEASE_REVISION_VERSION 2u
#define DCM_SW_MAJOR_VERSION            5u
#define DCM_SW_MINOR_VERSION            0u
#define DCM_SW_PATCH_VERSION            0u
#define DCM_PRV_FUNCTIONAL_REQUEST          1u
#define DCM_PRV_PHYSICAL_REQUEST            0u
#define DCM_PRV_MAXNUM_OF_CONFIG            8u

typedef uint8 Dcm_StatusType;

#define DCM_E_OK                        0u
#define DCM_E_TI_PREPARE_LIMITS         2u
#define DCM_E_TI_PREPARE_INCONSTENT     3u
#define DCM_E_ROE_NOT_ACCEPTED          6u
#define DCM_E_PERIODICID_NOT_ACCEPTED   7u
#define DCM_E_SEED_NOK                   11u
#define DCM_E_MONITORING_REQ             12u
#define DCM_E_MONITORING_NOTREQ          13u
#define DCM_UNUSED_PARAM(P)   ((void)(P))

typedef uint8 Dcm_MsgItemType;
typedef P2VAR(Dcm_MsgItemType,TYPEDEF,DCM_INTERN_DATA)  Dcm_MsgType;
typedef uint32 Dcm_MsgLenType;

typedef struct{
   uint8   reqType;
   boolean   suppressPosResponse;
   uint8   sourceofRequest;
}Dcm_MsgAddInfoType;

typedef uint8 Dcm_IdContextType;

typedef struct{
    Dcm_MsgType resData;
    Dcm_MsgType reqData;
    Dcm_MsgAddInfoType msgAddInfo;
    Dcm_MsgLenType resDataLen;
    Dcm_MsgLenType reqDataLen;
    Dcm_MsgLenType resMaxDataLen;
    Dcm_IdContextType idContext;
   Type_SwcServiceCom_tIdPdu dcmRxPduId;
}Dcm_MsgContextType;

#ifndef DEFAULT_SESSION
#define DEFAULT_SESSION DCM_DEFAULT_SESSION
#endif

#ifndef PROGRAMMING_SESSION
#define PROGRAMMING_SESSION  DCM_PROGRAMMING_SESSION
#endif

#ifndef EXTENDED_DIAGNOSTIC_SESSION
#define EXTENDED_DIAGNOSTIC_SESSION    DCM_EXTENDED_DIAGNOSTIC_SESSION
#endif

#ifndef SAFETY_SYSTEM_DIAGNOSTIC_SESSION
#define SAFETY_SYSTEM_DIAGNOSTIC_SESSION  DCM_SAFETY_SYSTEM_DIAGNOSTICS_SESSION
#endif

#ifndef DCM_ALL_SESSION_LEVEL
#define DCM_ALL_SESSION_LEVEL 0xFFu
#endif

#ifndef DCM_SEC_LEV_LOCKED
#define DCM_SEC_LEV_LOCKED  0x00u
#endif

#ifndef DCM_SEC_LEV_ALL
#define DCM_SEC_LEV_ALL     0xFFu
#endif

#ifndef DCM_RES_POS_OK
#define DCM_RES_POS_OK      0u
#endif

#ifndef DCM_RES_POS_NOT_OK
#define DCM_RES_POS_NOT_OK  1u
#endif

#ifndef DCM_RES_NEG_OK
#define DCM_RES_NEG_OK      2u
#endif

#ifndef DCM_RES_NEG_NOT_OK
#define DCM_RES_NEG_NOT_OK  3u
#endif

#ifndef DCM_UDS_TESTER_SOURCE
#define DCM_UDS_TESTER_SOURCE   0u
#endif

#ifndef DCM_ROE_SOURCE
#define DCM_ROE_SOURCE          1u
#endif

#ifndef DCM_RDPI_SOURCE
#define DCM_RDPI_SOURCE          2u
#endif

#ifndef DCM_RDPI_SID
#define DCM_RDPI_SID        0x2Au
#endif

typedef uint8 Dcm_CommunicationModeType;

#ifndef DCM_ENABLE_RX_TX_NORM
#define DCM_ENABLE_RX_TX_NORM 0x00u
#endif

#ifndef DCM_ENABLE_RX_DISABLE_TX_NORM
#define DCM_ENABLE_RX_DISABLE_TX_NORM 0x01u
#endif

#ifndef DCM_DISABLE_RX_ENABLE_TX_NORM
#define DCM_DISABLE_RX_ENABLE_TX_NORM 0x02u
#endif

#ifndef DCM_DISABLE_RX_TX_NORMAL
#define DCM_DISABLE_RX_TX_NORMAL 0x03u
#endif

#ifndef DCM_ENABLE_RX_TX_NM
#define DCM_ENABLE_RX_TX_NM 0x04u
#endif

#ifndef DCM_ENABLE_RX_DISABLE_TX_NM
#define DCM_ENABLE_RX_DISABLE_TX_NM 0x05u
#endif

#ifndef DCM_DISABLE_RX_ENABLE_TX_NM
#define DCM_DISABLE_RX_ENABLE_TX_NM 0x06u
#endif

#ifndef DCM_DISABLE_RX_TX_NM
#define DCM_DISABLE_RX_TX_NM 0x07u
#endif

#ifndef DCM_ENABLE_RX_TX_NORM_NM
#define DCM_ENABLE_RX_TX_NORM_NM 0x08u
#endif

#ifndef DCM_ENABLE_RX_DISABLE_TX_NORM_NM
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM 0x09u
#endif

#ifndef DCM_DISABLE_RX_ENABLE_TX_NORM_NM
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM 0x0Au
#endif

#ifndef DCM_DISABLE_RX_TX_NORM_NM
#define DCM_DISABLE_RX_TX_NORM_NM 0x0Bu
#endif

#define DCM_PRV_PAGEBUFFER_TIMEIN_CYCLES ((DCM_PAGEDBUFFER_TIMEOUT)/(DCM_CFG_TASK_TIME_US))

#ifndef     DCM_FUNCTIONAL_REQUEST
#define DCM_FUNCTIONAL_REQUEST      DCM_PRV_FUNCTIONAL_REQUEST
#endif
#ifndef     DCM_PHYSICAL_REQUEST
#define DCM_PHYSICAL_REQUEST        DCM_PRV_PHYSICAL_REQUEST
#endif
#ifndef     DCM_MAXNUM_OF_CONFIG
#define DCM_MAXNUM_OF_CONFIG        DCM_PRV_MAXNUM_OF_CONFIG
#endif
#ifndef     DCM_PAGEBUFFER_TIMEIN_CYCLES
#define DCM_PAGEBUFFER_TIMEIN_CYCLES DCM_PRV_PAGEBUFFER_TIMEIN_CYCLES
#endif
#ifndef     DCM_DSLD_TYPE1
#define DCM_DSLD_TYPE1              DCM_PRV_DSLD_TYPE1
#endif
#ifndef     DCM_DSLD_TYPE2
#define DCM_DSLD_TYPE2              DCM_PRV_DSLD_TYPE2
#endif

typedef struct{
    Dcm_MsgType  tx_buffer_pa;
    Dcm_MsgType  rx_mainBuffer_pa;
    Dcm_MsgLenType tx_buffer_size_u32;
    Dcm_MsgLenType rx_buffer_size_u32;
   uint32 dataP2TmrAdjust;
   uint32 dataP2StarTmrAdjust;
   uint8  protocolid_u8;
   uint8  sid_tableid_u8;
   uint8  premption_level_u8;
   uint8  pduinfo_idx_u8;
   boolean nrc21_b;
   boolean sendRespPendTransToBoot;
}Dcm_Dsld_protocol_tableType;

typedef void (*Dcm_ConfirmationApiType)(Dcm_IdContextType dataIdContext_u8,Type_SwcServiceCom_tIdPdu dataRxPduId_u8, uint16 dataSourceAddress_u16,Dcm_ConfirmationStatusType status_u8);
typedef boolean (*Dcm_ModeRuleType) (uint8* ErrorCode_u8);

typedef struct{
   uint32 allowed_session_b32;
   uint32 allowed_security_b32;
   P2FUNC(Std_ReturnType,TYPEDEF,adrUserSubServiceModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint8,AUTOMATIC),VAR(uint8,AUTOMATIC));
   P2FUNC(Std_ReturnType,TYPEDEF,SubFunc_fp) (VAR(Dcm_SrvOpStatusType,AUTOMATIC),P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA),P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA));
   uint8  subservice_id_u8;
   boolean isDspRDTCSubFnc_b;
}Dcm_Dsld_SubServiceType;

typedef struct{
   uint32 allowed_session_b32;
   uint32 allowed_security_b32;
   P2FUNC(Std_ReturnType,TYPEDEF,service_handler_fp) (VAR( Dcm_SrvOpStatusType,AUTOMATIC),P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA),P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA));
   P2FUNC(void,TYPEDEF,Service_init_fp) (void);
   uint8 sid_u8;
   boolean  subfunction_exist_b;
   boolean servicelocator_b;
   P2CONST(Dcm_Dsld_SubServiceType,TYPEDEF,DCM_INTERN_CONST) ptr_subservice_table_pcs;
   uint8 num_sf_u8;
   P2FUNC(Std_ReturnType,TYPEDEF,adrUserServiceModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint8,AUTOMATIC));

    Dcm_ConfirmationApiType Dcm_ConfirmationService;
}Dcm_Dsld_ServiceType;

typedef struct{
   P2CONST(Dcm_Dsld_ServiceType,TYPEDEF,DCM_INTERN_CONST) ptr_service_table_pcs;
   uint8 num_services_u8;
   uint8 nrc_sessnot_supported_u8;
   uint8 cdtc_index_u8;
}Dcm_Dsld_sid_tableType;

typedef struct{
   uint8 protocol_num_u8;
   Type_SwcServiceCom_tIdPdu txpduid_num_u8;
   Type_SwcServiceCom_tIdPdu roetype2_txpdu_u8;
   Type_SwcServiceCom_tIdPdu rdpitype2_txpdu_u8;
   uint16 testaddr_u16;
 	uint8   channel_idx_u8;
 	uint8   ConnectionIndex_u8;
 	uint8   NumberOfTxpdu_u8;
}Dcm_Dsld_connType;

typedef struct{
   Type_SwcServiceCom_tIdPdu rxpduid_num_u8;
   uint16 testsrcaddr_u16;
}Dcm_Dsld_RoeRxToTestSrcMappingType;

typedef enum{
    DCM_DSLD_NO_COM_MODE
   ,   DCM_DSLD_SILENT_COM_MODE
   ,   DCM_DSLD_FULL_COM_MODE
}Dcm_Dsld_commodeType;

typedef enum{
    DCM_COMM_ACTIVE
   ,   DCM_COMM_NOT_ACTIVE
}Dcm_Dsld_activediagnostic_ten;

typedef struct{
   uint8   ComMChannelId;
   Dcm_Dsld_commodeType ComMState;
}Dcm_Dsld_ComMChannel;

typedef struct{
   P2CONST(uint8,     TYPEDEF,  DCM_INTERN_CONST)        ptr_rxtable_pca;
   P2CONST(Type_SwcServiceCom_tIdPdu,     TYPEDEF,  DCM_INTERN_CONST)        ptr_txtable_pca;
   P2CONST(Dcm_Dsld_connType,     TYPEDEF,  DCM_INTERN_CONST)        ptr_conntable_pcs;
   P2CONST(Dcm_Dsld_protocol_tableType,TYPEDEF,  DCM_INTERN_CONST)        protocol_table_pcs;
   P2CONST(Dcm_Dsld_sid_tableType,     TYPEDEF,  DCM_INTERN_CONST)        sid_table_pcs;
   P2CONST(uint8,     TYPEDEF,  DCM_INTERN_CONST)        session_lookup_table_pcau8;
   P2CONST(uint8                      ,TYPEDEF,  DCM_INTERN_CONST)        security_lookup_table_pcau8;
}Type_CfgSwcServiceDcm_Dsld;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_Dsld_activediagnostic_ten, DCM_VAR) Dcm_ActiveDiagnosticState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern CONST(Type_CfgSwcServiceDcm_Dsld, DCM_CONST) CfgSwcServiceDcm_stDsld;
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_VERSION_INFO_API != DCM_CFG_OFF )
#define Dcm_GetVersionInfo(DcmVerInfoPtr)                       \
do                        \
{                                                               \
   if(DcmVerInfoPtr != NULL_PTR)                               \
   {                                                           \
    (DcmVerInfoPtr)->vendorID = DCM_VENDOR_ID;                  \
    (DcmVerInfoPtr)->moduleID = DCM_MODULE_ID;                  \
    (DcmVerInfoPtr)->sw_major_version = DCM_SW_MAJOR_VERSION;   \
    (DcmVerInfoPtr)->sw_minor_version = DCM_SW_MINOR_VERSION;   \
    (DcmVerInfoPtr)->sw_patch_version = DCM_SW_PATCH_VERSION;   \
   }                                                           \
}                                                               \
while(0)                                                        \

#endif
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_SetNegResponse ( P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) ErrorCode
                                              );

extern FUNC(void,DCM_CODE) Dcm_ProcessingDone (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void, DCM_CODE) Dcm_SetP3MaxMonitoring (VAR(boolean,AUTOMATIC) active);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define Dcm_SetS3MaxMonitoring Dcm_SetP3MaxMonitoring
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(void,DCM_CODE) Dcm_GetActiveServiceTable (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ActiveServiceTable);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocolRxBufferSize
                            (CONSTP2VAR(Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA) rxBufferLength);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_ForceRespPend(void);
extern FUNC(boolean,DCM_CODE) Dcm_IsInfrastructureErrorPresent_b(VAR(uint8,AUTOMATIC) dataInfrastrutureCode_u8);

#if((DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF))

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_TriggerOnEvent( VAR(uint8,AUTOMATIC) RoeEventId );
#endif

#if(DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED==DCM_CFG_OFF)
#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetActiveProtocol(P2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_APPL_DATA) ActiveProtocol);
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSesCtrlType(P2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_APPL_DATA) SesCtrlType);
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSecurityLevel(P2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_APPL_DATA) SecLevel);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_ResetToDefaultSession(void);
#endif
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_Dsld_ComMChannel, DCM_VAR) Dcm_active_commode_e[DCM_NUM_COMM_CHANNEL];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"
extern  CONST(uint8, DCM_CONST) Dcm_Dsld_ComMChannelId_acu8[DCM_NUM_COMM_CHANNEL];
#define DCM_STOP_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"
#endif
