#pragma once
/******************************************************************************/
/* File   : Com_Cfg_SymbolicNames.hpp                                         */
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
#define COM_VARIANT_PRE_COMPILE                                                0
#define COM_VARIANT_LINK_TIME                                                  1
#define COM_VARIANT_POSTBUILD_LOADABLE                                         2
#define COM_VARIANT_POSTBUILD_SELECTABLE                                       3

#define COM_CONFIGURATION_VARIANT                        COM_VARIANT_PRE_COMPILE

#ifndef COM_DontUseExternalSymbolicNames
#define ComConf_ComIPdu_ApplicationCyclic_TPM_Can_Network_CANNODE_0 0
#define ComConf_ComIPdu_HMIPressure_TPM_Can_Network_CANNODE_0 1
#define ComConf_ComIPdu_HMITempAndRefPress_TPM_Can_Network_CANNODE_0 2
#define ComConf_ComIPdu_ApplicationResponse_TPM_Can_Network_CANNODE_0 3
#define ComConf_ComIPdu_ApplicationRequest_TPM_Can_Network_CANNODE_0 0
#define ComConf_ComIPdu_BCM_peripheralMasterClock_Can_Network_CANNODE_0 1
#define ComConf_ComIPdu_ESP_WSpeed_Front_BodyLCAN_Can_Network_CANNODE_0 2
#define ComConf_ComIPdu_ESP_WSpeed_Rear_BodyLCAN_Can_Network_CANNODE_0 3
#define ComConf_ComIPdu_ESP_Wheel_Pulse_Stamped_Can_Network_CANNODE_0 4
#define ComConf_ComIPdu_RdcData_TPM_Can_Network_CANNODE_0 5
#define ComConf_ComIPdu_TMM_Status_BodyLCAN_Can_Network_CANNODE_0 6
#define ComConf_ComIPdu_VehSts_BodyLCAN_Can_Network_CANNODE_0 7
#define ComConf_ComIPdu_VmsStsReq_BodyLCAN_Can_Network_CANNODE_0 8
#define ComConf_ComSignal_AppCyclic_7 0
#define ComConf_ComSignal_AppCyclic_6 1
#define ComConf_ComSignal_AppCyclic_5 2
#define ComConf_ComSignal_AppCyclic_4 3
#define ComConf_ComSignal_AppCyclic_3 4
#define ComConf_ComSignal_AppCyclic_2 5
#define ComConf_ComSignal_AppCyclic_1 6
#define ComConf_ComSignal_AppCyclic_0 7
#define ComConf_ComSignal_TPMS_LOCATE_Status 8
#define ComConf_ComSignal_TPMS_LEARN_Status 9
#define ComConf_ComSignal_TEMP_WARNING_RR 10
#define ComConf_ComSignal_TEMP_WARNING_RL 11
#define ComConf_ComSignal_TEMP_WARNING_FR 12
#define ComConf_ComSignal_TEMP_WARNING_FL 13
#define ComConf_ComSignal_TPMS_MONITOR_Status 14
#define ComConf_ComSignal_TP_RR 15
#define ComConf_ComSignal_TP_RL 16
#define ComConf_ComSignal_TP_FL 17
#define ComConf_ComSignal_TP_FR 18
#define ComConf_ComSignal_TPV_RR 19
#define ComConf_ComSignal_TPV_RL 20
#define ComConf_ComSignal_TPV_FR 21
#define ComConf_ComSignal_TPV_FL 22
#define ComConf_ComSignal_TPS_RR 23
#define ComConf_ComSignal_TPS_RL 24
#define ComConf_ComSignal_TPS_FL 25
#define ComConf_ComSignal_TPS_FR 26
#define ComConf_ComSignal_TIRE_REF_PRESS_RR 27
#define ComConf_ComSignal_TIRE_REF_PRESS_RL 28
#define ComConf_ComSignal_TIRE_REF_PRESS_FR 29
#define ComConf_ComSignal_TIRE_REF_PRESS_FL 30
#define ComConf_ComSignal_TIRE_TEMP_RR 31
#define ComConf_ComSignal_TIRE_TEMP_RL 32
#define ComConf_ComSignal_TIRE_TEMP_FR 33
#define ComConf_ComSignal_TIRE_TEMP_FL 34
#define ComConf_ComSignal_AppResponse_7 35
#define ComConf_ComSignal_AppResponse_6 36
#define ComConf_ComSignal_AppResponse_5 37
#define ComConf_ComSignal_AppResponse_4 38
#define ComConf_ComSignal_AppResponse_3 39
#define ComConf_ComSignal_AppResponse_2 40
#define ComConf_ComSignal_AppResponse_1 41
#define ComConf_ComSignal_AppResponse_0 42
#define ComConf_ComSignal_AppReqCmd_7 0
#define ComConf_ComSignal_AppReqCmd_6 1
#define ComConf_ComSignal_AppReqCmd_5 2
#define ComConf_ComSignal_AppReqCmd_4 3
#define ComConf_ComSignal_AppReqCmd_3 4
#define ComConf_ComSignal_AppReqCmd_2 5
#define ComConf_ComSignal_AppReqCmd_1 6
#define ComConf_ComSignal_AppReqCmd_0 7
#define ComConf_ComSignal_BCM_peripherialMasterClockValid 8
#define ComConf_ComSignal_BCM_peripherialMasterClock 9
#define ComConf_ComSignal_ESP_Wheel_Dir_Right_Front 10
#define ComConf_ComSignal_ESP_Wheel_Dir_Left_Front 11
#define ComConf_ComSignal_ESP_WSpeed_Front_Message_Counter 12
#define ComConf_ComSignal_ESP_WSpeed_Front_CRC 13
#define ComConf_ComSignal_ESP_Wheel_Speed_Right_Front_Q 14
#define ComConf_ComSignal_ESP_Wheel_Speed_Left_Front_Q 15
#define ComConf_ComSignal_ESP_Wheel_Speed_Right_Front 16
#define ComConf_ComSignal_ESP_Wheel_Speed_Left_Front 17
#define ComConf_ComSignal_ESP_WSpeed_Rear_Message_Counter 18
#define ComConf_ComSignal_ESP_WSpeed_Rear_CRC 19
#define ComConf_ComSignal_ESP_Wheel_Speed_Right_Rear_Q 20
#define ComConf_ComSignal_ESP_Wheel_Speed_Right_Rear 21
#define ComConf_ComSignal_ESP_Wheel_Speed_Left_Rear_Q 22
#define ComConf_ComSignal_ESP_Wheel_Speed_Left_Rear 23
#define ComConf_ComSignal_ESP_Wheel_Dir_Right_Rear 24
#define ComConf_ComSignal_ESP_Wheel_Dir_Left_Rear 25
#define ComConf_ComSignal_ESP_Wheel_Pulse_Stamped_MC 26
#define ComConf_ComSignal_ESP_Wheel_Pulse_Stamped_CRC 27
#define ComConf_ComSignal_ESP_Wheel_Pulse_Right_Rear_Q 28
#define ComConf_ComSignal_ESP_Wheel_Pulse_Right_Front_Q 29
#define ComConf_ComSignal_ESP_Wheel_Pulse_Left_Rear_Q 30
#define ComConf_ComSignal_ESP_Wheel_Pulse_RxTs 31
#define ComConf_ComSignal_ESP_Wheel_Pulse_Left_Front_Q 32
#define ComConf_ComSignal_ESP_Wheel_Pulse_Right_Rear 33
#define ComConf_ComSignal_ESP_Wheel_Pulse_Right_Front 34
#define ComConf_ComSignal_ESP_Wheel_Pulse_Left_Rear 35
#define ComConf_ComSignal_ESP_Wheel_Pulse_Left_Front 36
#define ComConf_ComSignal_User_defined_val_5 37
#define ComConf_ComSignal_User_defined_val_4 38
#define ComConf_ComSignal_User_defined_val_3 39
#define ComConf_ComSignal_User_defined_val_2 40
#define ComConf_ComSignal_TyreId_Lo 41
#define ComConf_ComSignal_TyreId_Hi 42
#define ComConf_ComSignal_PackageId 43
#define ComConf_ComSignal_User_defined_val_1 44
#define ComConf_ComSignal_TMM_TempAmb 45
#define ComConf_ComSignal_VehModCurr 46
#define ComConf_ComSignal_VmsStateFdbk 47
#define ComConf_ComSignal_VmsCrc 48
#define ComConf_ComSignal_VmsAliveCntr 49
#define ComConf_ComSignal_SteeringPataModReq 50
#define ComConf_ComSignal_PcmStatesReq 51
#define ComConf_ComSignal_EspPataModReq 52
#define ComConf_ComSignal_DrvModPataOffRoadMod 53
#define ComConf_ComIPduGroup_ComIPduGroup_Rx 0
#define ComConf_ComIPduGroup_ComIPduGroup_Tx 1
#define ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic 2
#define ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse 3
#endif

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

