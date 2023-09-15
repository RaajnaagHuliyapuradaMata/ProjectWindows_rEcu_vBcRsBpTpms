#pragma once
/******************************************************************************/
/* File   : PduR_Cfg_SymbolicNames.hpp                                        */
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
#define PDUR_VARIANT_PRE_COMPILE    (0)
#define PDUR_VARIANT_POSTBUILD_LOADABLE    (1)

#if !defined(PDUR_CONFIGURATION_VARIANT)
#define PDUR_CONFIGURATION_VARIANT    PDUR_VARIANT_PRE_COMPILE
#endif

#define PduRConf_PduRSrcPdu_BCM_PowerMode_Can_Network_0_CANNODE_0_CanIf2PduR    0
#define CfgSwcServicePduR_PduSrcRxDiagUdsReq_Functional_CanTp2PduR    0
#define PduRConf_PduRDestPdu_CGW_Diag_Func_Req_Can_Network_0_CANNODE_0_PduR2Dcm  0
#define PduRConf_PduRSrcPdu_CGW_EPOCHTime_Can_Network_0_CANNODE_0_CanIf2PduR    1
#define PduRConf_PduRSrcPdu_CGW_ESP_WheelPulses_Can_Network_0_CANNODE_0_CanIf2PduR    2
#define PduRConf_PduRSrcPdu_CGW_ODO_Can_Network_0_CANNODE_0_CanIf2PduR    3
#define PduRConf_PduRSrcPdu_CGW_TPMS_Application_Req_Can_Network_0_CANNODE_0_CanIf2PduR    4
#define CfgSwcServicePduR_PduSrcRxDiagUdsReq_Physical_CanTp2PduR    1
#define PduRConf_PduRDestPdu_CGW_TPMS_Diag_Req_Can_Network_0_CANNODE_0_PduR2Dcm  1
#define PduRConf_PduRSrcPdu_CGW_VCU_Ambient_Info_Can_Network_0_CANNODE_0_CanIf2PduR    5
#define PduRConf_PduRSrcPdu_CGW_VCU_Powertrain_Info_Can_Network_0_CANNODE_0_CanIf2PduR    6
#define PduRConf_PduRSrcPdu_CGW_VCU_WhlSpd_F_Can_Network_0_CANNODE_0_CanIf2PduR    7
#define PduRConf_PduRSrcPdu_CGW_VCU_WhlSpd_R_Can_Network_0_CANNODE_0_CanIf2PduR    8
#define PduRConf_PduRSrcPdu_CGW_VehicleSpeed_Can_Network_0_CANNODE_0_CanIf2PduR    9
#define PduRConf_PduRSrcPdu_CfgEcuabCanIf_dIdCanRx_TmpsRdcData_Can_Network_0_CANNODE_0_CanIf2PduR    10
#define PduRConf_PduRSrcPdu_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0_Com2PduR    0
#define PduRConf_PduRDestPdu_TPMS_ApplicationCyclic_Can_Network_0_CANNODE_0_PduR2CanIf  0
#define PduRConf_PduRSrcPdu_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0_Com2PduR    1
#define PduRConf_PduRDestPdu_TPMS_ApplicationResponse_Can_Network_0_CANNODE_0_PduR2CanIf  1
#define PduRConf_PduRSrcPdu_TPMS_Diag_Resp_Can_Network_0_CANNODE_0_Phys_Dcm2PduR    0
#define CfgSwcServicePduR_PduDestTxDiagUds_Physical_PduR2CanTp  0
#define PduRConf_PduRSrcPdu_TPMS_Status_Can_Network_0_CANNODE_0_Com2PduR    2
#define PduRConf_PduRDestPdu_TPMS_Status_Can_Network_0_CANNODE_0_PduR2CanIf  2
#define PduRConf_PduRSrcPdu_TPMS_TirePT_Can_Network_0_CANNODE_0_Com2PduR    3
#define PduRConf_PduRDestPdu_TPMS_TirePT_Can_Network_0_CANNODE_0_PduR2CanIf  3

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

