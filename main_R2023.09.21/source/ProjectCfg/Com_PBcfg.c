/******************************************************************************/
/* File   : Com_PBcfg.c                                                       */
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
#include "Std_Types.hpp"

#define COM_DontUseExternalSymbolicNames
#include "Com_Prv.hpp"
#include "Com_Cbk.hpp"
#include "PduR_Com.hpp"
#include "Com_PBcfg.hpp"
#include "Com_PBcfg_InternalId.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define Com_SigType_u32 NULL_PTR

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"
CONST(Type_CfgSwcServiceCom_stInfoSignalTx, COM_CONST) CfgSwcServiceCom_castListInfoSignalTx[CfgSwcServiceCom_dNumSignalsTx] = {
      {(uint32)(0uL), 0x54, 56, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0x0}
   ,  {(uint32)(0uL), 0x54, 48, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0x0}
   ,  {(uint32)(0uL), 0x54, 40, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0x0}
   ,  {(uint32)(0uL), 0x54, 32, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0x0}
   ,  {(uint32)(0uL), 0x54, 24, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0x0}
   ,  {(uint32)(0uL), 0x54, 16, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0x0}
   ,  {(uint32)(0uL), 0x54,  8, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0x0}
   ,  {(uint32)(0uL), 0x54,  0, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   0x0}
   ,  {(uint32)(0uL), 0x54, 48, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54, 49, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54, 63, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54, 62, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54, 61, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54, 60, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54, 56, 4, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54, 40, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54, 32, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54, 16, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54, 24, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54, 11, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54, 15, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54,  3, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54,  7, 1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x6}
   ,  {(uint32)(0uL), 0x54,  8, 3, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54, 12, 3, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54,  4, 3, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54,  0, 3, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0,         0x0}
   ,  {(uint32)(0uL), 0x54, 56, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  0x0}
   ,  {(uint32)(0uL), 0x54, 48, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  0x0}
   ,  {(uint32)(0uL), 0x54, 40, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  0x0}
   ,  {(uint32)(0uL), 0x54, 32, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  0x0}
   ,  {(uint32)(0uL), 0x54, 24, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  0x0}
   ,  {(uint32)(0uL), 0x54, 16, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  0x0}
   ,  {(uint32)(0uL), 0x54,  8, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  0x0}
   ,  {(uint32)(0uL), 0x54,  0, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  0x0}
   ,  {(uint32)(0uL), 0x54, 56, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0, 0x0}
   ,  {(uint32)(0uL), 0x54, 48, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0, 0x0}
   ,  {(uint32)(0uL), 0x54, 40, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0, 0x0}
   ,  {(uint32)(0uL), 0x54, 32, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0, 0x0}
   ,  {(uint32)(0uL), 0x54, 24, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0, 0x0}
   ,  {(uint32)(0uL), 0x54, 16, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0, 0x0}
   ,  {(uint32)(0uL), 0x54,  8, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0, 0x0}
   ,  {(uint32)(0uL), 0x54,  0, 8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0, 0x0}
};

CONST(Type_CfgSwcServiceCom_stInfoSignalRx, COM_CONST) CfgSwcServiceCom_castListInfoSignalRx[CfgSwcServiceCom_dNumSignalsRx] = {
      {(uint32)(0x0uL), 56,  0,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,     0x00, 0x28}
   ,  {(uint32)(0x0uL), 48,  1,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,     0x00, 0x28}
   ,  {(uint32)(0x0uL), 40,  2,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,     0x00, 0x28}
   ,  {(uint32)(0x0uL), 32,  3,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,     0x00, 0x28}
   ,  {(uint32)(0x0uL), 24,  4,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,     0x00, 0x28}
   ,  {(uint32)(0x0uL), 16,  5,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,     0x00, 0x28}
   ,  {(uint32)(0x0uL),  8,  6,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,     0x00, 0x28}
   ,  {(uint32)(0x0uL),  0,  7,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0,     0x00, 0x28}
   ,  {(uint32)(0x0uL), 45,  8,  1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0,  0x26, 0x28}
   ,  {(uint32)(0x0uL),  0, 48,  5, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0,  0x08, 0x28}
   ,  {(uint32)(0x0uL), 52,  9,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,  0x20, 0x28}
   ,  {(uint32)(0x0uL), 54, 10,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,  0x20, 0x28}
   ,  {(uint32)(0x0uL),  8, 11,  4, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,  0x20, 0x28}
   ,  {(uint32)(0x0uL),  0, 12,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,  0x20, 0x28}
   ,  {(uint32)(0x0uL), 14, 13,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,  0x20, 0x28}
   ,  {(uint32)(0x0uL), 12, 14,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,  0x20, 0x28}
   ,  {(uint32)(0x0uL), 40,  0, 16, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,  0x22, 0x28}
   ,  {(uint32)(0x0uL), 24,  1, 16, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0,  0x22, 0x28}
   ,  {(uint32)(0x0uL),  8, 15,  4, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,   0x20, 0x28}
   ,  {(uint32)(0x0uL),  0, 16,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,   0x20, 0x28}
   ,  {(uint32)(0x0uL), 14, 17,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,   0x20, 0x28}
   ,  {(uint32)(0x0uL), 40,  2, 16, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,   0x22, 0x28}
   ,  {(uint32)(0x0uL), 12, 18,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,   0x20, 0x28}
   ,  {(uint32)(0x0uL), 24,  3, 16, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,   0x22, 0x28}
   ,  {(uint32)(0x0uL), 52, 19,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,   0x20, 0x28}
   ,  {(uint32)(0x0uL), 54, 20,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,   0x20, 0x28}
   ,  {(uint32)(0x0uL),  8, 21,  4, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x20, 0x28}
   ,  {(uint32)(0x0uL),  0, 22,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x20, 0x28}
   ,  {(uint32)(0x0uL), 12, 23,  1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x26, 0x28}
   ,  {(uint32)(0x0uL), 13, 24,  1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x26, 0x28}
   ,  {(uint32)(0x0uL), 14, 25,  1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x26, 0x28}
   ,  {(uint32)(0x0uL), 56,  4, 16, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x22, 0x28}
   ,  {(uint32)(0x0uL), 15, 26,  1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x26, 0x28}
   ,  {(uint32)(0x0uL), 40, 27,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x20, 0x28}
   ,  {(uint32)(0x0uL), 32, 28,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x20, 0x28}
   ,  {(uint32)(0x0uL), 24, 29,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x20, 0x28}
   ,  {(uint32)(0x0uL), 16, 30,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,    0x20, 0x28}
   ,  {(uint32)(0x0uL), 56, 31,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,                0x00, 0x28}
   ,  {(uint32)(0x0uL), 48, 32,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,                0x00, 0x28}
   ,  {(uint32)(0x0uL), 40, 33,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,                0x00, 0x28}
   ,  {(uint32)(0x0uL), 32, 34,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,                0x00, 0x28}
   ,  {(uint32)(0x0uL),  8, 35,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,                0x00, 0x28}
   ,  {(uint32)(0x0uL),  0, 36,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,                0x00, 0x28}
   ,  {(uint32)(0x0uL), 16, 37,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,                0x00, 0x28}
   ,  {(uint32)(0x0uL), 24, 38,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0,                0x00, 0x28}
   ,  {(uint32)(0x0uL),  0, 39,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_TMM_Status_BodyLCAN_Can_Network_CANNODE_0,        0x20, 0x28}
   ,  {(uint32)(0x0uL), 16, 40,  4, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_VehSts_BodyLCAN_Can_Network_CANNODE_0,            0x20, 0x28}
   ,  {(uint32)(0x0uL), 16, 41,  4, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,         0x20, 0x28}
   ,  {(uint32)(0x0uL),  0, 42,  8, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,         0x20, 0x28}
   ,  {(uint32)(0x0uL),  8, 43,  4, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,         0x20, 0x28}
   ,  {(uint32)(0x0uL), 28, 44,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,         0x20, 0x28}
   ,  {(uint32)(0x0uL), 20, 45,  4, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,         0x20, 0x28}
   ,  {(uint32)(0x0uL), 30, 46,  2, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,         0x20, 0x28}
   ,  {(uint32)(0x0uL), 27, 47,  1, (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,         0x26, 0x28}
};

static CONST(Type_CfgSwcServiceCom_stInfoModeTrans, COM_CONST) Com_ApplicationCyclic_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {1, 1, 0, 0, COM_TXMODE_PERIODIC}
   ,  {1, 1, 0, 0, COM_TXMODE_PERIODIC}
};

static CONST(Type_CfgSwcServiceCom_stInfoModeTrans, COM_CONST) Com_HMIPressure_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {100, 1, 0, 0, COM_TXMODE_PERIODIC}
   ,  {100, 1, 0, 0, COM_TXMODE_PERIODIC}
};

static CONST(Type_CfgSwcServiceCom_stInfoModeTrans, COM_CONST) Com_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {100, 1, 0, 0, COM_TXMODE_PERIODIC}
   ,  {100, 1, 0, 0, COM_TXMODE_PERIODIC}
};

static CONST(Type_CfgSwcServiceCom_stInfoModeTrans, COM_CONST) Com_ApplicationResponse_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {0, 1, 0, 0, COM_TXMODE_DIRECT}
   ,  {0, 1, 0, 0, COM_TXMODE_DIRECT}
};

static CONST(Type_CfgSwcServiceCom_stInfoModeTrans, COM_CONST) Com_TPMS_Software_ID_TPM_Can_Network_CANNODE_0_TransModeInfo[] = {
      {1000, 1, 0, 0, COM_TXMODE_PERIODIC}
   ,  {1000, 1, 0, 0, COM_TXMODE_PERIODIC}
};

CONST(Type_CfgSwcServiceCom_stInfoIpduTx, COM_CONST) CfgSwcServiceCom_castListInfoIpduTx[CfgSwcServiceCom_dNumIPduTx] = {
      {Com_IpduBuf_ApplicationCyclic_TPM_Can_Network_CANNODE_0,   Com_ApplicationCyclic_TPM_Can_Network_CANNODE_0_TransModeInfo,   &Com_IPdu_Callout_ApplicationCyclic_TPM,   NULL_PTR,                                                    8,   1, 0,  8, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_ApplicationCyclic_TPM_Can_Network_CANNODE_0_Com2PduR,   (Com_TxIntSignalIdType)ComSignal_Internal_AppCyclic_7,        0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}
   ,  {Com_IpduBuf_HMIPressure_TPM_Can_Network_CANNODE_0,         Com_HMIPressure_TPM_Can_Network_CANNODE_0_TransModeInfo,         &Com_IPdu_Callout_HMIPressure_TPM,         NULL_PTR,                                                    8, 100, 0, 19, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_HMIPressure_TPM_Can_Network_CANNODE_0_Com2PduR,         (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_LOCATE_Status, 0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}
   ,  {Com_IpduBuf_HMITempAndRefPress_TPM_Can_Network_CANNODE_0,  Com_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_TransModeInfo,  &Com_IPdu_Callout_HMITempAndRefPress_TPM,  NULL_PTR,                                                    8, 100, 0,  8, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_HMITempAndRefPress_TPM_Can_Network_CANNODE_0_Com2PduR,  (Com_TxIntSignalIdType)ComSignal_Internal_TIRE_REF_PRESS_RR,  0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}
   ,  {Com_IpduBuf_ApplicationResponse_TPM_Can_Network_CANNODE_0, Com_ApplicationResponse_TPM_Can_Network_CANNODE_0_TransModeInfo, &Com_IPdu_Callout_ApplicationResponse_TPM, &Com_TxNotify_ApplicationResponse_TPM_Can_Network_CANNODE_0, 8,   0, 0,  8, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_ApplicationResponse_TPM_Can_Network_CANNODE_0_Com2PduR, (Com_TxIntSignalIdType)ComSignal_Internal_AppResponse_7,      0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}
   ,  {Com_IpduBuf_TPMS_Software_ID_TPM_Can_Network_CANNODE_0,    Com_TPMS_Software_ID_TPM_Can_Network_CANNODE_0_TransModeInfo,    &Com_IPdu_Callout_TPMS_Software_ID_TPM,    NULL_PTR,                                                    8, 100, 0, 19, (Type_SwcServiceCom_tIdPdu)PduRConf_PduRSrcPdu_TPMS_Software_ID_TPM_Can_Network_CANNODE_0_Com2PduR,    (Com_TxIntSignalIdType)ComSignal_Internal_TPMS_LOCATE_Status, 0x4000, ComMainFunction_Internal_MainFunctionTx, 0xFF}
};

CONST(Type_CfgSwcServiceCom_stInfoIpduRx, COM_CONST) CfgSwcServiceCom_castListInfoIpduRx[CfgSwcServiceCom_dNumIPduRx] = {
      {Com_LocalBuf_ApplicationRequest_TPM_Can_Network_CANNODE_0,    &Com_IPdu_Callout_ApplicationRequest,        8,  8, (Com_RxIntSignalIdType)ComSignal_Internal_AppReqCmd_7,                     ComMainFunction_Internal_MainFunctionRx, 0x0}
   ,  {Com_LocalBuf_BCM_peripheralMasterClock_Can_Network_CANNODE_0, &Com_IPdu_Callout_BCM_peripheralMasterClock, 8,  2, (Com_RxIntSignalIdType)ComSignal_Internal_BCM_peripherialMasterClockValid, ComMainFunction_Internal_MainFunctionRx, 0x0}
   ,  {Com_LocalBuf_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0, &Com_IPdu_Callout_ESP_WSpeed_Front_BodyLCAN, 8,  8, (Com_RxIntSignalIdType)ComSignal_Internal_ESP_Wheel_Dir_Right_Front,       ComMainFunction_Internal_MainFunctionRx, 0x0}
   ,  {Com_LocalBuf_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0,  &Com_IPdu_Callout_ESP_WSpeed_Rear_BodyLCAN,  8,  8, (Com_RxIntSignalIdType)ComSignal_Internal_ESP_WSpeed_Rear_Message_Counter, ComMainFunction_Internal_MainFunctionRx, 0x0}
   ,  {Com_LocalBuf_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0,   &Com_IPdu_Callout_ESP_Wheel_Pulse_Stamped,   8, 11, (Com_RxIntSignalIdType)ComSignal_Internal_ESP_Wheel_Pulse_Stamped_MC,      ComMainFunction_Internal_MainFunctionRx, 0x0}
   ,  {Com_LocalBuf_RdcData_TPM_Can_Network_CANNODE_0,               &Com_IPdu_Callout_RdcData_TPM,               8,  8, (Com_RxIntSignalIdType)ComSignal_Internal_User_defined_val_5,              ComMainFunction_Internal_MainFunctionRx, 0x0}
   ,  {Com_LocalBuf_TMM_Status_BodyLCAN_Can_Network_CANNODE_0,       &Com_IPdu_Callout_TMM_Status_BodyLCAN,       8,  1, (Com_RxIntSignalIdType)ComSignal_Internal_TMM_TempAmb,                     ComMainFunction_Internal_MainFunctionRx, 0x0}
   ,  {Com_LocalBuf_VehSts_BodyLCAN_Can_Network_CANNODE_0,           &Com_IPdu_Callout_VehSts_BodyLCAN,           8,  1, (Com_RxIntSignalIdType)ComSignal_Internal_VehModCurr,                      ComMainFunction_Internal_MainFunctionRx, 0x0}
   ,  {Com_LocalBuf_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0,        &Com_IPdu_Callout_VmsStsReq_BodyLCAN,        8,  7, (Com_RxIntSignalIdType)ComSignal_Internal_VmsStateFdbk,                    ComMainFunction_Internal_MainFunctionRx, 0x0}
};

CONST(Type_CfgSwcServiceCom_stInfoIpduGrp, COM_CONST) CfgSwcServiceCom_castListInfoIpduGrp[4] = {
      { 0, 9}
   ,  { 9, 0}
   ,  {14, 0}
   ,  {15, 0}
};

CONST(Type_CfgSwcServiceCom_tIdIPdu, COM_CONST) CfgSwcServiceCom_catListIdIPdu[16] = {
      ComConf_ComIPdu_Internal_ApplicationRequest_TPM_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_BCM_peripheralMasterClock_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_RdcData_TPM_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_TMM_Status_BodyLCAN_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_VehSts_BodyLCAN_Can_Network_CANNODE_0
   ,  ComConf_ComIPdu_Internal_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0
   ,  (CfgSwcServiceCom_dNumIPduRx + (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0)
   ,  (CfgSwcServiceCom_dNumIPduRx + (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMIPressure_TPM_Can_Network_CANNODE_0)
   ,  (CfgSwcServiceCom_dNumIPduRx + (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_HMITempAndRefPress_TPM_Can_Network_CANNODE_0)
   ,  (CfgSwcServiceCom_dNumIPduRx + (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0)
   ,  (CfgSwcServiceCom_dNumIPduRx + (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_TPMS_Software_ID_TPM_Can_Network_CANNODE_0)
   ,  (CfgSwcServiceCom_dNumIPduRx + (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationCyclic_TPM_Can_Network_CANNODE_0)
   ,  (CfgSwcServiceCom_dNumIPduRx + (Type_CfgSwcServiceCom_tIdIPdu)ComConf_ComIPdu_Internal_ApplicationResponse_TPM_Can_Network_CANNODE_0)
};
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"
VAR(uint8,COM_VAR) Com_IpduBuf_ApplicationCyclic_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_IpduBuf_HMIPressure_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_IpduBuf_HMITempAndRefPress_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_IpduBuf_ApplicationResponse_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_IpduBuf_TPMS_Software_ID_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_ApplicationRequest_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_BCM_peripheralMasterClock_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_RdcData_TPM_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_TMM_Status_BodyLCAN_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_VehSts_BodyLCAN_Can_Network_CANNODE_0[8];
VAR(uint8,COM_VAR) Com_LocalBuf_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0[8];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"
VAR(Com_TxIpduRamData,COM_VAR)      Com_TxIpduRam_s[CfgSwcServiceCom_dNumIPduTx];
VAR(Com_RxIpduRamData,COM_VAR)      Com_RxIpduRam_s[CfgSwcServiceCom_dNumIPduRx];
VAR(Com_TxSignalFlagType,COM_VAR)   Com_TxSignalFlag[CfgSwcServiceCom_dNumSignalsTx];
VAR(Com_RxSignalFlagType,COM_VAR)   Com_RxSignalFlag[CfgSwcServiceCom_dNumSignalsRx];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"
VAR(uint8,COM_VAR)    Com_IpduCounter_s[CfgSwcServiceCom_dNumIPduTx + CfgSwcServiceCom_dNumIPduRx];
VAR(uint8,COM_VAR)    Com_IpduCounter_DM[CfgSwcServiceCom_dNumIPduRx];
VAR(uint8,COM_VAR) Com_SigType_u8[53];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.hpp"

#define COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.hpp"
VAR(uint16,COM_VAR) Com_SigType_u16[5];
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.hpp"

#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"
CONST(Type_CfgSwcServiceCom_stBufferRamRx, COM_CONST) Com_Lok_xRxRamBuf_acst[1u] = {
   {
         (P2VAR(uint8,  TYPEDEF, COM_APPL_DATA)) Com_SigType_u8
      ,  (P2VAR(uint16, TYPEDEF, COM_APPL_DATA)) Com_SigType_u16
      ,  (P2VAR(uint32, TYPEDEF, COM_APPL_DATA)) Com_SigType_u32
   }
};

CONST(Type_CfgSwcServiceCom_stMainFunction, COM_CONST) Com_MainFunctionCfg[COM_NUM_OF_MAINFUNCTION] = {
      {0u, 9u, 10u}
   ,  {0u, 5u, 10u}
};
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.hpp"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

