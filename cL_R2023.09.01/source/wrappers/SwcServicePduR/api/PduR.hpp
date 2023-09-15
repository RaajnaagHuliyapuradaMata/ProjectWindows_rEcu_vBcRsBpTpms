

#ifndef PDUR_H
#define PDUR_H

#define PDUR_AR_RELEASE_MAJOR_VERSION     4u

#define PDUR_AR_RELEASE_MINOR_VERSION     2u

#define PDUR_AR_RELEASE_REVISION_VERSION     2u

#define PDUR_INSTANCE_ID          0u

#include "PduR_Cfg.hpp"
#include "ComStack_Types.hpp"

#include "Dem.hpp"

#if(PDUR_ENABLE_INTER_MODULE_CHECKS)
#if(!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#define PDUR_E_CONFIG_PTR_INVALID      ((uint8)0x00)

#define PDUR_E_INVALID_REQUEST         ((uint8)0x01)

#define PDUR_E_PDU_ID_INVALID          ((uint8)0x02)

#define PDUR_E_TP_TX_REQ_REJECTED      ((uint8)0x03)

#define PDUR_E_DUPLICATE_IPDU_ID ((uint8)0x06)

#define PDUR_E_ROUTING_TABLE_ID_INVALID ((uint8)0x08)

#define PDUR_E_NULL_POINTER ((uint8)0x09)

#define PDUR_E_PDU_INSTANCES_LOST ((uint8)0x0a)

#define PDUR_SID_INIT                   (0)

#define PDUR_SID_GETVERINFO             (1)

#define PDUR_SID_GETCFGID               (2)

#define PDUR_SID_DISABLEROUTING         (7)

#define PDUR_SID_ENABLEROUTING          (8)

#define PDUR_SID_GATEWAYTPTXCONFIRMATION          (9)

typedef  uint16 PduR_RoutingPathGroupIdType;

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.hpp"

extern void PduR_Init( const Type_CfgSwcServicePduR_st * ConfigPtr );

extern void PduR_DisableRouting(PduR_RoutingPathGroupIdType id
   ,       boolean initialize);

extern void PduR_EnableRouting(PduR_RoutingPathGroupIdType id);

extern void PduR_GetVersionInfo( Std_VersionInfoType * versionInfo);

extern uint16 PduR_GetConfigurationId(void);

extern Std_ReturnType PduR_DemInitMonitorForPDUR_E_INIT_FAILED(Dem_InitMonitorReasonType InitMonitorReason);

extern Std_ReturnType PduR_DemInitMonitorForPDUR_E_PDU_INSTANCE_LOST(Dem_InitMonitorReasonType InitMonitorReason);

#if( PDUR_ECUC_RB_RTE_IN_USE == STD_OFF )

extern void PduR_DsmReInitMainFunction(void);
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.hpp"

#endif

