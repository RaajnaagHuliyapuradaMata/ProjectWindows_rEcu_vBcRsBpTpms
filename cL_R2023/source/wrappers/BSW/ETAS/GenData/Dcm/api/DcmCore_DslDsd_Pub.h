

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

#if(DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF)
typedef struct{
    uint8  SecurityLevel;
    uint16 DelayCount;
    uint32 ResidualDelay;
}Dcm_Dsp_Seca_t;
#endif

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
#if(DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF)
    uint8 NumOfSecurityLevels;
    Dcm_Dsp_Seca_t SecurityInformation[DCM_CFG_NUM_SECURITY_LEVEL - 1u];
#endif
    uint8 freeForProjectUse[6];
}Dcm_ProgConditionsType;

typedef struct{
    uint8  ConfigSetId;
}Dcm_ConfigType;

typedef uint8 Dcm_EcuStartModeType;
#define DCM_COLD_START   0x0u
#define DCM_WARM_START   0x1u

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

typedef Dcm_MsgItemType * Dcm_MsgType;

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

    PduIdType dcmRxPduId;
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

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))

#define DCM_PRV_DSLD_TYPE1      0x01u
#define DCM_PRV_DSLD_TYPE2      0x02u

typedef struct{
    Dcm_MsgType txbuffer_ptr;
    Dcm_MsgLenType txbuffer_length_u32;
    uint8 premption_level_u8;
    uint8 servicetable_Id_u8;
    uint8   protocolTransType_u8;
}Dcm_ProtocolExtendedInfo_type;
#endif

#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
typedef struct{
    PduIdType txpduid_num_u8;
    Dcm_MsgType txbuffer_ptr;
    boolean   isTxPduId_Busy;
    uint8 cntFreeTxPduRdpi2Cntr_u8;
}Dcm_RdpiTxInfo_type;

#if(DCM_CFG_NUM_RDPITYPE2_TXPDU>0)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
    extern Dcm_RdpiTxInfo_type Dcm_Dsld_RDPIType2tx_table[DCM_CFG_NUM_RDPITYPE2_TXPDU];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#endif

#ifndef     DCM_FUNCTIONAL_REQUEST
#define     DCM_FUNCTIONAL_REQUEST      DCM_PRV_FUNCTIONAL_REQUEST
#endif
#ifndef     DCM_PHYSICAL_REQUEST
#define     DCM_PHYSICAL_REQUEST        DCM_PRV_PHYSICAL_REQUEST
#endif
#ifndef     DCM_MAXNUM_OF_CONFIG
#define     DCM_MAXNUM_OF_CONFIG        DCM_PRV_MAXNUM_OF_CONFIG
#endif
#ifndef     DCM_PAGEBUFFER_TIMEIN_CYCLES
#define     DCM_PAGEBUFFER_TIMEIN_CYCLES DCM_PRV_PAGEBUFFER_TIMEIN_CYCLES
#endif
#ifndef     DCM_DSLD_TYPE1
#define     DCM_DSLD_TYPE1              DCM_PRV_DSLD_TYPE1
#endif
#ifndef     DCM_DSLD_TYPE2
#define     DCM_DSLD_TYPE2              DCM_PRV_DSLD_TYPE2
#endif

typedef struct{
    Dcm_MsgType  tx_buffer_pa;
    Dcm_MsgType  rx_mainBuffer_pa;
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    Dcm_MsgType  rx_reserveBuffer_pa;
#endif
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    const Dcm_ProtocolExtendedInfo_type * roe_info_pcs;
#endif
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
    const Dcm_ProtocolExtendedInfo_type * rdpi_info_pcs;
#endif
    Dcm_MsgLenType tx_buffer_size_u32;
    Dcm_MsgLenType rx_buffer_size_u32;
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    Dcm_MsgLenType maxResponseLength_u32;
#endif
    uint32 dataP2TmrAdjust;
    uint32 dataP2StarTmrAdjust;
    uint8  protocolid_u8;
    uint8  sid_tableid_u8;
    uint8  premption_level_u8;
    uint8  pduinfo_idx_u8;
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    uint8  timings_limit_idx_u8;
    uint8  timings_idx_u8;
#endif
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
    uint8 Config_Mask;
#endif
    uint8   demclientid;
    boolean nrc21_b;
    boolean sendRespPendTransToBoot;
}Dcm_Dsld_protocol_tableType;

typedef void (*Dcm_ConfirmationApiType)(Dcm_IdContextType dataIdContext_u8,PduIdType dataRxPduId_u8, uint16 dataSourceAddress_u16,Dcm_ConfirmationStatusType status_u8);
typedef boolean (*Dcm_ModeRuleType) (uint8* ErrorCode_u8);

typedef struct{
    uint32 allowed_session_b32;
    uint32 allowed_security_b32;
#if((DCM_CFG_DSD_MODERULESUBFNC_ENABLED!=DCM_CFG_OFF))
    Dcm_ModeRuleType moderule_fp;
#endif
    Std_ReturnType (*adrUserSubServiceModeRule_pfct) (Dcm_NegativeResponseCodeType * ErrorCode ,uint8 dataSid_u8 ,uint8 subservice_id_u8);
    Std_ReturnType (*SubFunc_fp) (Dcm_SrvOpStatusType OpStatus ,Dcm_MsgContextType * pMsgContext ,Dcm_NegativeResponseCodeType * dataNegRespCode );
    uint8  subservice_id_u8;
    boolean isDspRDTCSubFnc_b;
}Dcm_Dsld_SubServiceType;

typedef struct{
    uint32 allowed_session_b32;
    uint32 allowed_security_b32;
#if((DCM_CFG_DSD_MODERULESERVICE_ENABLED!=DCM_CFG_OFF))
    Dcm_ModeRuleType moderule_fp;
#endif

    Std_ReturnType (*service_handler_fp) (Dcm_SrvOpStatusType SrvOpStatus ,Dcm_MsgContextType *Dcm_DsldMsgContext_st  ,Dcm_NegativeResponseCodeType *dataNrc  );
    void (*Service_init_fp) (void);
    uint8 sid_u8;
    boolean  subfunction_exist_b;
    boolean servicelocator_b;
    const Dcm_Dsld_SubServiceType * ptr_subservice_table_pcs;
    uint8 num_sf_u8;
    Std_ReturnType (*adrUserServiceModeRule_pfct) (Dcm_NegativeResponseCodeType *ErrorCode,uint8 dataSid_u8 );

    Dcm_ConfirmationApiType Dcm_ConfirmationService;
} Dcm_Dsld_ServiceType;

typedef struct{
    const Dcm_Dsld_ServiceType * ptr_service_table_pcs;
    uint8 num_services_u8;
    uint8 nrc_sessnot_supported_u8;
    uint8 cdtc_index_u8;
} Dcm_Dsld_sid_tableType;

typedef struct{
    uint8 protocol_num_u8;
    PduIdType txpduid_num_u8;
    PduIdType roetype2_txpdu_u8;
    PduIdType rdpitype2_txpdu_u8;
    uint16 testaddr_u16;
 	uint8   channel_idx_u8;						
 	uint8   ConnectionIndex_u8;
 	uint8   NumberOfTxpdu_u8;
} Dcm_Dsld_connType;

typedef struct{
    PduIdType rxpduid_num_u8;
    uint16 testsrcaddr_u16;
} Dcm_Dsld_RoeRxToTestSrcMappingType;

typedef enum
{
    DCM_DSLD_NO_COM_MODE,
    DCM_DSLD_SILENT_COM_MODE,
    DCM_DSLD_FULL_COM_MODE
}Dcm_Dsld_commodeType;

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)

typedef enum
{
    DCM_NONE=0,
    DCM_CAN,
    DCM_KLINE,
    DCM_FLEX,
    DCM_LIN,
    DCM_IP,
    DCM_INTERNAL
}Dcm_DslDsd_MediumType_ten;

#endif

typedef enum
{
    DCM_COMM_ACTIVE,
    DCM_COMM_NOT_ACTIVE
}Dcm_Dsld_activediagnostic_ten;

typedef struct{
    uint8   ComMChannelId;
    Dcm_Dsld_commodeType ComMState;
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    Dcm_DslDsd_MediumType_ten  MediumId;
#endif
}Dcm_Dsld_ComMChannel;

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

typedef struct{
    uint32 P2_max_u32;
    uint32 P3_max_u32;
} Dcm_Dsld_KwpTimerServerType;

typedef enum
{
    DCM_CURRENT,
    DCM_LIMIT
}Dcm_TimerModeType;

#endif

typedef struct{

    const uint8 * ptr_rxtable_pca;

    const PduIdType * ptr_txtable_pca;

    const Dcm_Dsld_connType * ptr_conntable_pcs;

    const Dcm_Dsld_protocol_tableType * protocol_table_pcs;

    const Dcm_Dsld_sid_tableType * sid_table_pcs;

    const uint8 * session_lookup_table_pcau8;

    const uint8 * security_lookup_table_pcau8;
} Dcm_Dsld_confType;

#if(((DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)||(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)) && (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF))

typedef Std_ReturnType (*Dcm_Notification403_ptr) (
                                       uint8 SID,
                                       const uint8 * RequestData,
#if   (DCM_CFG_INDICATION_DATASIZE_UINT32==DCM_CFG_ON)
                                       uint32 DataSize,
#else
                                       uint16 DataSize,
#endif
                                       uint8 ReqType,
                                       uint16 SourceAddress,
                                       Dcm_NegativeResponseCodeType * ErrorCode
                                                             );

typedef Std_ReturnType (*Dcm_Confirmation403_ptr) (
                                       uint8 SID,
                                       uint8 ReqType,
                                       uint16 SourceAddress,
                                       Dcm_ConfirmationStatusType ConfirmationStatus
                                                             );
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if((DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS !=0))
extern const Dcm_Notification403_ptr Dcm_Rte_SupplierNotification_a[DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS];
extern const Dcm_Confirmation403_ptr Dcm_Rte_SupplierConfirmation_a[DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS];
#endif
#if((DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF) && (DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS != 0))
extern const Dcm_Notification403_ptr Dcm_Rte_ManufacturerNotification_a[DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS];
extern const Dcm_Confirmation403_ptr Dcm_Rte_ManufacturerConfirmation_a[DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS];
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern uint8 Dcm_ActiveConfiguration_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_Dsld_activediagnostic_ten Dcm_ActiveDiagnosticState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_Dsld_confType Dcm_Dsld_Conf_cs;
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_ConfigType * Dcm_ActiveConfigSet_Ptr;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CONST_8
#include "Dcm_MemMap.h"
extern const uint8 Dcm_Dsld_KWPsupported_sessions_acu8[];
#define DCM_STOP_SEC_CONST_8
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_Dsld_KwpTimerServerType Dcm_Dsld_default_timings_acs[];
extern const Dcm_Dsld_KwpTimerServerType Dcm_Dsld_Limit_timings_acs[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#if (DCM_CFG_VERSION_INFO_API != DCM_CFG_OFF )

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
#include "Dcm_MemMap.h"

extern void Dcm_Init(const Dcm_ConfigType * ConfigPtr );

extern void Dcm_SetNegResponse ( const Dcm_MsgContextType * pMsgContext,
                                                Dcm_NegativeResponseCodeType ErrorCode
                                              );

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern void Dcm_Lok_SetOBDNegResponse(const Dcm_MsgContextType* pMsgContext,Dcm_NegativeResponseCodeType ErrorCode);
#endif

extern void Dcm_ProcessingDone (const Dcm_MsgContextType * pMsgContext);

#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
extern void Dcm_OBDProcessingDone(const Dcm_MsgContextType* pMsgContext);
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

extern Dcm_StatusType Dcm_Lok_ResponseOnOneEvent( const Dcm_MsgType MsgPtr,
                                                      Dcm_MsgLenType MsgLen,
                                                      uint16 TesterSrcAddr);

extern Std_ReturnType Dcm_RoeSendFinalResponse ( const Dcm_MsgType MsgPtr,
                                                                Dcm_MsgLenType MsgLen,
                                                                PduIdType DcmRxPduId);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

extern void Dcm_StartPagedProcessing (const Dcm_MsgContextType * pMsgContext);

extern void Dcm_ProcessPage(Dcm_MsgLenType FilledPageLen );
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern void (*Dcm_adrUpdatePage_pfct) (
                                                 Dcm_MsgType PageBufPtr,
                                                 Dcm_MsgLenType PageLen
                                               );
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

extern void Dcm_RestartP3timer(void);

extern void Dcm_GetKwpTimingValues(
                                     Dcm_TimerModeType TimerMode,
                                     Dcm_Dsld_KwpTimerServerType * TimerServerCurrent
                                                 );

extern Dcm_StatusType Dcm_PrepareKwpTimingValues(
                                        const Dcm_Dsld_KwpTimerServerType * TimerServerNew
                                                               );

extern void Dcm_SetKwpTimingValues (void);

extern void Dcm_SetKwpDefaultTimingValues(void);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern void Dcm_SetP3MaxMonitoring (boolean active);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#define Dcm_SetS3MaxMonitoring Dcm_SetP3MaxMonitoring
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

extern void Dcm_GetActiveServiceTable (uint8 * ActiveServiceTable);

extern Std_ReturnType Dcm_GetActiveProtocolRxBufferSize
                            (Dcm_MsgLenType * const rxBufferLength);

extern Std_ReturnType Dcm_ForceRespPend(void);

extern boolean Dcm_IsInfrastructureErrorPresent_b(uint8 dataInfrastrutureCode_u8);

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)

extern Std_ReturnType Dcm_GetMediumOfActiveConnection(Dcm_DslDsd_MediumType_ten * const ActiveMediumId);
#endif

#ifndef CHECK_APICONSISTENCY

extern Std_ReturnType Dcm_TriggerOnEvent( uint8 RoeEventId );

extern Std_ReturnType Dcm_GetActiveProtocol(Dcm_ProtocolType * ActiveProtocol);

extern Std_ReturnType Dcm_GetSesCtrlType(Dcm_SesCtrlType * SesCtrlType);

extern Std_ReturnType Dcm_GetSecurityLevel(Dcm_SecLevelType * SecLevel);

extern Std_ReturnType Dcm_ResetToDefaultSession(void);
#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
extern const Dcm_ConfigType Dcm_Config[DCM_PRV_MAXNUM_OF_CONFIG];
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_Dsld_ComMChannel Dcm_active_commode_e[DCM_NUM_COMM_CHANNEL];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CONST_8
#include "Dcm_MemMap.h"

extern  const uint8 Dcm_Dsld_ComMChannelId_acu8[DCM_NUM_COMM_CHANNEL];
#define DCM_STOP_SEC_CONST_8
#include "Dcm_MemMap.h"
#endif
