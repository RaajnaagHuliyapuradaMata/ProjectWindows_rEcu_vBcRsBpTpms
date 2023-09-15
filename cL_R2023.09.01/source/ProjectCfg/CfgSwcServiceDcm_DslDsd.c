/******************************************************************************/
/* File   : CfgSwcServiceDcm_DslDsd.c                                         */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Dcm.hpp"
#include "Dcm_Lcfg_DspUds.hpp"
#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint8, DCM_VAR) Dcm_DspArraySignal_au8 [1];
VAR(sint8, DCM_VAR) Dcm_DspArraySignal_as8 [1];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint16, DCM_VAR) Dcm_DspArraySignal_au16[1];
VAR(sint16, DCM_VAR) Dcm_DspArraySignal_as16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint32, DCM_VAR) Dcm_DspArraySignal_au32[1];
VAR(sint32, DCM_VAR) Dcm_DspArraySignal_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"
static CONST(uint8, DCM_CONST) Dcm_Dsld_rx_table_acu8[DCM_CFG_NUM_RX_PDUID] = {0x0, 0x0};
#define DCM_STOP_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static CONST(PduIdType, DCM_CONST) Dcm_DsldTxTable_cast[DCM_NUM_TX_PDUID] = {PduRConf_PduRSrcPdu_TPMS_Diag_Resp_Can_Network_0_CANNODE_0_Phys_Dcm2PduR};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint8, DCM_VAR) Dcm_DsldDiagBuffer_au8[1026+2];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static CONST(Dcm_Dsld_connType, DCM_CONST) Dcm_DsldConnTable_cast[DCM_CFG_NUM_CONN] = {{0x0, PduRConf_PduRSrcPdu_TPMS_Diag_Resp_Can_Network_0_CANNODE_0_Phys_Dcm2PduR, 0xFF, 0xFF, 0x0, 0x0, 0x00, 0x00}};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_Dsld_ComMChannel, DCM_VAR) Dcm_active_commode_e[DCM_NUM_COMM_CHANNEL] = {{ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel,DCM_DSLD_NO_COM_MODE}};
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"
CONST(uint8, DCM_CONST) Dcm_Dsld_ComMChannelId_acu8[DCM_NUM_COMM_CHANNEL] = {ComMConf_ComMChannel_ComMChannel_Can_Network_0_Channel};
#define DCM_STOP_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static CONST(Dcm_Dsld_protocol_tableType, DCM_CONST) Dcm_DsldProtocol_cast[] = {
   {
         &Dcm_DsldDiagBuffer_au8[0]
      ,  &Dcm_DsldDiagBuffer_au8[0]
      ,  1026
      ,  1026
      ,  10000u
      ,  10000u
      ,  DCM_UDS_ON_CAN
      ,  0
      ,  0
      ,  0
      ,  DemConf_DemClient_DemClient
      ,  FALSE
      ,  TRUE
   }
};

static CONST(Dcm_Dsld_SubServiceType, DCM_CONST) Dcm_SrvTab0_SubSrv0_acs[] = {
      {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, &Dcm_Dsp_ReportNumberOfDTC,               0x1,TRUE}
   ,  {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, &Dcm_Dsp_ReportSupportedDTC,              0x2,TRUE}
   ,  {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, &Dcm_Dsp_ReportSnapshotRecordByDTCNumber, 0x4,TRUE}
};
static CONST(Dcm_Dsld_SubServiceType, DCM_CONST) Dcm_SrvTab0_SubSrv1_acs[] = {
      {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x1, FALSE}
   ,  {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x3, FALSE}
};
static CONST(Dcm_Dsld_SubServiceType, DCM_CONST) Dcm_SrvTab0_SubSrv2_acs[] = {
      {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x1, FALSE}
   ,  {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x2, FALSE}
};
static CONST(Dcm_Dsld_SubServiceType, DCM_CONST) Dcm_SrvTab0_SubSrv4_acs[] = {
      {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x1,  FALSE}
   ,  {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x2,  FALSE}
   ,  {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x3,  FALSE}
   ,  {0xffffffffuL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x60, FALSE}
};
static CONST(Dcm_Dsld_SubServiceType, DCM_CONST) Dcm_SrvTab0_SubSrv5_acs[] = {
      {0x16uL, 0xffffffffuL, &DcmAppl_RequestSeedLevel3ModeRuleCheck, NULL_PTR, 0x3, FALSE}
   ,  {0x16uL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService,  NULL_PTR, 0x4, FALSE}
};
static CONST(Dcm_Dsld_SubServiceType, DCM_CONST) Dcm_SrvTab0_SubSrv8_acs[] = {
      {0x16uL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x0, FALSE}
   ,  {0x16uL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x1, FALSE}
};

static CONST(Dcm_Dsld_SubServiceType, DCM_CONST) Dcm_SrvTab0_SubSrv10_acs[] = {
      {0x5uL, 0xffffffffuL, &DcmAppl_UserSubServiceModeRuleService, NULL_PTR, 0x0, FALSE}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static CONST(Dcm_Dsld_ServiceType, DCM_CONST) Dcm_Dsld_sid_table0_acs[] = {
      {0xffffffffuL, 0xffffffffuL, &SwcServiceDcm_tDiagnosticSessionControl,     &Dcm_Dsp_DscIni,                  0x10, TRUE,  TRUE, Dcm_SrvTab0_SubSrv4_acs,  4, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspDscConfirmation}
   ,  {0xffffffffuL, 0xffffffffuL, &SwcServiceDcm_tEcuReset,                     &Dcm_Dsp_EcuReset_Ini,            0x11, TRUE,  TRUE, Dcm_SrvTab0_SubSrv1_acs,  2, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspEcuResetConfirmation}
   ,  {0xffffffffuL, 0xffffffffuL, &SwcServiceDcm_tClearDiagnosticInformation,   NULL_PTR,                         0x14, FALSE, TRUE, NULL_PTR,                 0, &DcmAppl_UserServiceModeRuleService, &DcmAppl_DcmConfirmation}
   ,  {0xffffffffuL, 0xffffffffuL, &SwcServiceDcm_tReadDTCInformation,           &Dcm_Dsp_ReadDTCInfo_Ini,         0x19, TRUE,  TRUE, Dcm_SrvTab0_SubSrv0_acs,  3, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspReadDTCInfoConfirmation}
   ,  {0xffffffffuL, 0xffffffffuL, &SwcServiceDcm_tReadDataByIdentifier,         &Dcm_Dsp_RdbiIni,                 0x22, FALSE, TRUE, NULL_PTR,                 0, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspRdbiConfirmation}
   ,  {0x16uL,       0xffffffffuL, &SwcServiceDcm_tSecurityAccess,               &Dcm_Dsp_SecaIni,                 0x27, TRUE,  TRUE, Dcm_SrvTab0_SubSrv5_acs,  2, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspSecurityConfirmation}
   ,  {0x16uL,       0xffffffffuL, &SwcServiceDcm_tCommunicationControl,         NULL_PTR,                         0x28, TRUE,  TRUE, Dcm_SrvTab0_SubSrv8_acs,  2, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspCommCntrlConfirmation}
   ,  {0xffffffffuL, 0xffffffffuL, &SwcServiceDcm_tWriteDataByIdentifier,        &Dcm_Dcm_WDBIInit,                0x2E, FALSE, TRUE, NULL_PTR,                 0, &DcmAppl_UserServiceModeRuleService, &DcmAppl_DcmConfirmation}
   ,  {0xffffffffuL, 0xffffffffuL, &SwcServiceDcm_tRoutineControl,               &Dcm_Dsp_RC_Ini,                  0x31, FALSE, TRUE, NULL_PTR,                 0, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspRCConfirmation}
   ,  {0x2uL,        0xffffffffuL, &SwcServiceDcm_tRequestDownload,              &Dcm_Dsp_RequestDownload_Ini,     0x34, FALSE, TRUE, NULL_PTR,                 0, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspReqDownloadConfirmation}
   ,  {0x2uL,        0xffffffffuL, &SwcServiceDcm_tTransferData,                 &Dcm_Dsp_TransferDataIni,         0x36, FALSE, TRUE, NULL_PTR,                 0, &DcmAppl_UserServiceModeRuleService, &DcmAppl_DcmConfirmation}
   ,  {0x2uL,        0xffffffffuL, &SwcServiceDcm_tRequestTransferExit,          &Dcm_Dsp_RequestTransferExit_Ini, 0x37, FALSE, TRUE, NULL_PTR,                 0, &DcmAppl_UserServiceModeRuleService, &Dcm_Lok_DspReqTrfExitConfirmation}
   ,  {0x5uL,        0xffffffffuL, &SwcServiceDcm_tTesterPresent,                NULL_PTR,                         0x3E, TRUE,  TRUE, Dcm_SrvTab0_SubSrv10_acs, 1, &DcmAppl_UserServiceModeRuleService, &DcmAppl_DcmConfirmation}
   ,  {0xffffffffuL, 0xffffffffuL, &SwcServiceDcm_tControlDTCSetting,            &Dcm_Dsp_CDTCSIni,                0x85, TRUE,  TRUE, Dcm_SrvTab0_SubSrv2_acs,  2, &DcmAppl_UserServiceModeRuleService, &DcmAppl_DcmConfirmation}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static CONST(Dcm_Dsld_sid_tableType, DCM_CONST) Dcm_DsldServiceTables_cast[] = {{Dcm_Dsld_sid_table0_acs, 14, 0x7F, 5}};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"
static CONST(uint8, DCM_CONST) Dcm_DsldSupportedSessions_cau8[] = {0x1, 0x2, 0x3, 0x4, 0x60};
#define DCM_STOP_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
CONST(Dcm_Dsld_RoeRxToTestSrcMappingType, DCM_CONST) Dcm_Dsld_RoeRxToTestSrcMappingTable[DCM_CFG_NUM_RX_PDUID] = {
      {1, 0}
   ,  {0, 0}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"
static CONST(uint8, DCM_CONST) Dcm_Dsld_supported_security_acu8[] = {0x0, 0x1, 0x2};
#define DCM_STOP_SEC_CONST_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
CONST(Type_CfgSwcServiceDcm_Dsld, DCM_CONST) CfgSwcServiceDcm_stDsld = {
      Dcm_Dsld_rx_table_acu8
   ,  Dcm_DsldTxTable_cast
   ,  Dcm_DsldConnTable_cast
   ,  Dcm_DsldProtocol_cast
   ,  Dcm_DsldServiceTables_cast
   ,  Dcm_DsldSupportedSessions_cau8
   ,  Dcm_Dsld_supported_security_acu8
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

