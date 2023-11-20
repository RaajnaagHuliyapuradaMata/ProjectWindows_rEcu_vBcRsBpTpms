#pragma once
/******************************************************************************/
/* File   : Com_PBcfg.hpp                                                     */
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
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
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
#define CfgSwcServiceCom_dNumSignalsRx                                       54u
#define CfgSwcServiceCom_dNumSignalsTx                                       43u
#define CfgSwcServiceCom_dNumIPduTx                                           5u
#define CfgSwcServiceCom_dNumIPduRx                                           9u
#define COM_NUM_GWSRC_SIGNALS                                                 0u
#define COM_NUM_GWSRC_GRPSIGNALS                                              0u
#define COM_NUM_GWSRC_IPDUS                                                   0u
#define COM_NUM_GRPSIG_NOGW                                                   0u
#define COM_NUM_IPDUS_IN_LAST_IPDUGRP                                         1u
#define COM_UPDATE_MAX                                                      0xFF

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
extern VAR(uint8,  COM_VAR) Com_IpduBuf_ApplicationCyclic_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_IpduBuf_HMIPressure_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_IpduBuf_HMITempAndRefPress_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_IpduBuf_ApplicationResponse_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_IpduBuf_TPMS_Software_ID_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_ApplicationRequest_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_BCM_peripheralMasterClock_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_RdcData_TPM_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_TMM_Status_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_VehSts_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_LocalBuf_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0[];
extern VAR(uint8,  COM_VAR) Com_SigType_u8[];
extern VAR(uint16, COM_VAR) Com_SigType_u16[];

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

