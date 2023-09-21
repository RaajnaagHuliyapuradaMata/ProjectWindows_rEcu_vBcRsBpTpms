#pragma once
/******************************************************************************/
/* File   : Dcm_Cfg_DslDsd.hpp                                                */
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

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DCM_CFG_ON                                                            1u
#define DCM_CFG_OFF                                                           0u

#define DCM_CFG_DET_SUPPORT_ENABLED                                  DCM_CFG_ON
#define DCM_CFG_KWP_ENABLED                                          DCM_CFG_OFF
#define DCM_CFG_KLINE_ENABLED                                        DCM_CFG_OFF
#define DCM_CFG_RESTORING_ENABLED                                    DCM_CFG_ON
#define DCM_CFG_STORING_ENABLED                                      DCM_CFG_ON
#define DCM_CFG_APPLTXCONF_REQ                                       DCM_CFG_ON
#define DCM_CFG_VERSION_INFO_API                                     DCM_CFG_ON
#define DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED                        DCM_CFG_ON
#define DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED                    DCM_CFG_OFF
#define DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED                        DCM_CFG_OFF
#define DCM_CFG_RBA_DEM_SR_ENABLED                                   DCM_CFG_OFF
#define DCM_CFG_RESPOND_ALLREQUEST                                   DCM_CFG_OFF
#define DCM_CFG_RESPOND_REQ_AFTERECURESET                            DCM_CFG_OFF
#define DCM_PAGEDBUFFER_ENABLED                                      DCM_CFG_OFF
#define DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP               DCM_CFG_OFF
#define DCM_CFG_RTESUPPORT_ENABLED                                   DCM_CFG_OFF
#define DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED                       DCM_CFG_OFF
#define DCM_SEPARATEBUFFERFORTXANDRX_ENABLED                         DCM_CFG_OFF
#define DCM_BUFQUEUE_ENABLED                                         DCM_CFG_OFF
#define DCM_CALLAPPLICATIONONREQRX_ENABLED                           DCM_CFG_ON
#define DCM_ROE_ENABLED                                              DCM_CFG_OFF
#define DCM_CFG_ROETYPE2_ENABLED                                     DCM_CFG_OFF
#define DCM_CFG_RDPI_ENABLED                                         DCM_CFG_OFF
#define DCM_CFG_PROTOCOL_PREMPTION_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSPUDSSUPPORT_ENABLED                                DCM_CFG_ON
#define DCM_CFG_DSD_MODERULESERVICE_ENABLED                          DCM_CFG_OFF
#define DCM_CFG_DSD_MODERULESUBFNC_ENABLED                           DCM_CFG_OFF
#define DCM_CFG_DSPOBDSUPPORT_ENABLED                                DCM_CFG_OFF
#define DCM_CFG_RXPDU_SHARING_ENABLED                                DCM_CFG_OFF
#define DCM_CFG_POSTBUILD_SUPPORT                                    DCM_CFG_OFF
#define DCM_CFG_OSTIMER_USE                                                FALSE

#define DcmConf_DcmDslProtocolRow_DcmDslProtocolRow_UDS           DCM_UDS_ON_CAN

#define DCM_CFG_S3MAX_TIME                                              5000000u
#define DCM_CFG_TASK_TIME_US                                              10000u
#define DCM_CFG_TASK_TIME_MS                                                 10u
#define DCM_CFG_SUPPLIERNOTIFICATION_NUM_PORTS                                 0
#define DCM_CFG_CALL_BACK_NUM_PORTS                                            0
#define DCM_CFG_MANUFACTURERNOTIFICATION_NUM_PORTS                             0
#define DCM_CFG_ECURESET_TIME                                                 0u
#define DCM_CFG_NUM_CONN                                                      1u
#define DCM_NUM_COMM_CHANNEL                                                   1
#define DCM_CFG_NUM_RX_PDUID                                                  2u
#define DCM_INDEX_FUNC_RX_PDUID                                               1u
#define DCM_NUM_TX_PDUID                                                      1u
#define DCM_CFG_SUPPRESS_NRC(NegRespCode) (((NegRespCode) == 0x11) ||((NegRespCode) == 0x12) ||((NegRespCode) == 0x31) ||((NegRespCode) == 0x7E) ||((NegRespCode) == 0x7F))


#define DCM_CFG_NUM_PROTOCOL                                                  1u
#define DCM_CFG_NUM_SID_TABLE                                                 1u
#define DCM_CFG_NUMPDUINFO_STRUCT                                             1u
#define DCM_CFG_MAX_WAITPEND                                                  4u
#define DcmConf_DcmDspSessionRow_DEFAULT_SESSION                             0x1
#define DcmConf_DcmDspSessionRow_PROGRAMMING_SESSION                         0x2
#define DcmConf_DcmDspSessionRow_EXTENDED_DIAGNOSTIC_SESSION                 0x3
#define DcmConf_DcmDspSessionRow_SAFETY_SYSTEM_DIAGNOSTIC_SESSION            0x4
#define DcmConf_DcmDspSessionRow_BH_SENS_EOL_SESSION                        0x60
#define DCM_CFG_DEFAULT_P2MAX_TIME                                        50000u
#define DCM_CFG_DEFAULT_P2STARMAX_TIME                                  2000000u
#define DCM_CFG_NUM_UDS_SESSIONS                                              5u
#define DcmConf_DcmDspSecurityRow_DCM_SEC_LEV_L1                             0x1
#define DcmConf_DcmDspSecurityRow_DCM_SEC_LEV_L2                             0x2
#define DCM_CFG_NUM_SECURITY_LEVEL                                            3u
#define DCM_CFG_IN_PARAM_MAXLEN                                               8u
#define DCM_CFG_MAX_PERIODIC_DID_READ                                         0u
#define DCM_CFG_MAX_DID_SCHEDULER                                             0u
#define DCM_UDS_DCMDSLPROTOCOLROW_UDS                                       0xF0
#define DCM_DCMDSDSERVICETABLE_UDS     0x0

#define DcmConf_DcmDslProtocolRx_UDS_Rx_Physical_Can_Network_CANNODE_0_PduR2Dcm      0x0
#define DcmConf_DcmDslProtocolRx_UDS_Rx_Functional_Can_Network_CANNODE_0_PduR2Dcm    0x1
#define DcmConf_DcmDslProtocolTx_UDS_Tx_Physical_Can_Network_CANNODE_0_Phys_Dcm2PduR 0x0

#define DCM_CFG_DSL_BUFFER__DCMDSLBUFFER_UDS_TX                             1026
#define DCM_CFG_DSL_BUFFER__DCMDSLBUFFER_UDS_RX                             1026
#define DCM_CFG_SIGNAL_DEFAULT_VALUE                                          0u

#define DCM_CFG_CONFIGSET1                                                  0x01
#define DCM_CFG_CONFIGSET2                                                  0x02
#define DCM_CFG_CONFIGSET3                                                  0x04
#define DCM_CFG_CONFIGSET4                                                  0x08
#define DCM_CFG_CONFIGSET5                                                  0x10
#define DCM_CFG_CONFIGSET6                                                  0x20
#define DCM_CFG_CONFIGSET7                                                  0x40
#define DCM_CFG_CONFIGSET8                                                  0x80

#define DCM_VERSION_INFO_API                            DCM_CFG_VERSION_INFO_API
#define DCM_SUPPLIER_NOTIFICATION_ENABLED  DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED
#define DCM_MANUFACTURER_NOTIFICATION_ENABLED DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED
#define DCM_RBA_DIAGADAPT_SUPPORT_ENABLED  DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED
#define DCM_RESPOND_ALLREQUEST                                       DCM_CFG_OFF
#define DCM_RTESUPPORT_ENABLED                        DCM_CFG_RTESUPPORT_ENABLED
#define DCM_NUM_CONN                                            DCM_CFG_NUM_CONN
#define DCM_NUM_RX_PDUID                                    DCM_CFG_NUM_RX_PDUID
#define DCM_NUM_PROTOCOL                                    DCM_CFG_NUM_PROTOCOL
#define DCM_NUM_SID_TABLE                                  DCM_CFG_NUM_SID_TABLE
#define DCM_NUMPDUINFO_STRUCT                          DCM_CFG_NUMPDUINFO_STRUCT
#define DCM_MAX_WAITPEND                                    DCM_CFG_MAX_WAITPEND
#define DCM_DEFAULT_P2MAX_TIME                        DCM_CFG_DEFAULT_P2MAX_TIME
#define DCM_DEFAULT_P2STARMAX_TIME                DCM_CFG_DEFAULT_P2STARMAX_TIME
#define DCM_NUM_UDS_SESSIONS                            DCM_CFG_NUM_UDS_SESSIONS
#define DCM_NUM_SECURITY_LEVEL                        DCM_CFG_NUM_SECURITY_LEVEL
#define DCM_OSTIMER_USE                                      DCM_CFG_OSTIMER_USE
#define DCM_ROETYPE2_ENABLED                            DCM_CFG_ROETYPE2_ENABLED
#define DCM_RDPI_ENABLED                                    DCM_CFG_RDPI_ENABLED
#define DCM_MAX_PERIODIC_DID_READ                  DCM_CFG_MAX_PERIODIC_DID_READ
#define DCM_MAX_DID_SCHEDULER                          DCM_CFG_MAX_DID_SCHEDULER
#define DCM_ROE_INTERMESSAGE_TIME                  DCM_CFG_ROE_INTERMESSAGE_TIME
#define DCM_PROTOCOL_PREMPTION_ENABLED        DCM_CFG_PROTOCOL_PREMPTION_ENABLED
#define DCM_DSL_BUFFER_DCMDSLBUFFER_0         DCM_CFG_DSL_BUFFER__DCMDSLBUFFER_0
#define DCM_DSL_BUFFER_DCMDSLBUFFER_1         DCM_CFG_DSL_BUFFER__DCMDSLBUFFER_1
#define DCM_DSL_BUFFER_DCMDSLBUFFER_2         DCM_CFG_DSL_BUFFER__DCMDSLBUFFER_2
#define DCM_DSL_BUFFER_DCMDSLBUFFER_3         DCM_CFG_DSL_BUFFER__DCMDSLBUFFER_3
#define DCM_DSL_BUFFER_DCMDSLBUFFER_4         DCM_CFG_DSL_BUFFER__DCMDSLBUFFER_4
#define DCM_DSP_UDSSUPPORT_ENABLED                 DCM_CFG_DSPUDSSUPPORT_ENABLED
#define DCM_DSP_OBDSUPPORT_ENABLED                 DCM_CFG_DSPOBDSUPPORT_ENABLED
#define DCM_SIGNAL_DEFAULT_VALUE                    DCM_CFG_SIGNAL_DEFAULT_VALUE
#define DCM_RXPDU_SHARING_ENABLED                  DCM_CFG_RXPDU_SHARING_ENABLED
#define DCM_CONFIGSET1                                        DCM_CFG_CONFIGSET1
#define DCM_CONFIGSET2                                        DCM_CFG_CONFIGSET2
#define DCM_CONFIGSET3                                        DCM_CFG_CONFIGSET3
#define DCM_CONFIGSET4                                        DCM_CFG_CONFIGSET4
#define DCM_CONFIGSET5                                        DCM_CFG_CONFIGSET5
#define DCM_CONFIGSET6                                        DCM_CFG_CONFIGSET6
#define DCM_CONFIGSET7                                        DCM_CFG_CONFIGSET7
#define DCM_CONFIGSET8                                        DCM_CFG_CONFIGSET8
#define DCM_SHARED_RX_PDUID                              DCM_CFG_SHARED_RX_PDUID
#define DCM_POSTBUILD_SUPPORT                          DCM_CFG_POSTBUILD_SUPPORT
#define DCM_ROE_RESUME_RXPDUID                        DCM_CFG_ROE_RESUME_RXPDUID
#define DCM_ROERDPI_TIMEOUT                                  DCM_CFG_GET_TIMEOUT
#define DCM_NUM_RDPITYPE2_TXPDU                      DCM_CFG_NUM_RDPITYPE2_TXPDU
#define DCM_PERIODICTX_SLOWRATE                      DCM_CFG_PERIODICTX_SLOWRATE
#define DCM_PERIODICTX_MEDIUMRATE                  DCM_CFG_PERIODICTX_MEDIUMRATE
#define DCM_PERIODICTX_FASTRATE                      DCM_CFG_PERIODICTX_FASTRATE

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern VAR (uint8, DCM_VAR) Dcm_InParameterBuf_au8 [];
extern VAR (uint8, DCM_VAR) Dcm_DspArraySignal_au8 [];
extern VAR (sint8, DCM_VAR) Dcm_DspArraySignal_as8 [];
extern VAR (uint16, DCM_VAR) Dcm_DspArraySignal_au16[];
extern VAR (sint16, DCM_VAR) Dcm_DspArraySignal_as16[];
extern VAR (uint32, DCM_VAR) Dcm_DspArraySignal_au32[];
extern VAR (sint32, DCM_VAR) Dcm_DspArraySignal_as32[];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

