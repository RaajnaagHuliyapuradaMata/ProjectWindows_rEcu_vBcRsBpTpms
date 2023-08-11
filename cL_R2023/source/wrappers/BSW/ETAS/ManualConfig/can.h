

#ifndef _CAN_H_
#define _CAN_H_

#include "rscanX.h"
#include "Com_Cfg_SymbolicNames.h"
#include "Can_GeneralTypes.h"

#define CAN_AR_RELEASE_MAJOR_VERSION  4
#define CAN_AR_RELEASE_MINOR_VERSION  2

#define CanConf_CanController_Can_Network_0_CANNODE_0 0u

#define CanMsgCGW_VCU_Powertrain_Info  (uint16)0x0C0
#define CanMsgCGW_TPMS_ApplicationReq  (uint16)0x620
#define CanMsgCGW_ESP_Wheel_Pulses     (uint16)0x070
#define CGW_TPMS_UDS_PhyReq            (uint16)0x73A
#define CanMsgCGW_ODO                  (uint16)0x351
#define CanMsgCGW_VCU_Ambient_Info     (uint16)0x300
#define CanMsgCGW_VCU_WheelSpeed_F     (uint16)0x341
#define CanMsgCGW_ESP_VehicleSpeed     (uint16)0x410
#define CanMsgBCM_Power_Mode           (uint16)0x107
#define CanMsgCGW_EPOCHTime            (uint16)0x060
#define CanMsgCGW_VCU_WheelSpeed_R     (uint16)0x342
#define RdcData_TPMS                   (uint16)0x400
#define CGW_TPMS_UDS_FuncReq           (uint16)0x7DF

#define CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_1  0   // 0x77A UDS TX
#define CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_2  1   // 0x610 Application Response
#define CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_3  2   // 0x600 Application Cyclic
#define CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_4  3   // 0x076 TPMS_TirePT
#define CanConf_CanHardwareObject_Can_Network_0_CANNODE_0_Tx_Std_MailBox_5  4   // 0x530 TPMS_Status

#define cBUSOFFTIMEOUT  200

extern void Can_Init(void);
extern void Can_ForwardMessageToCanIf(const Can_FrameType *tCanFrame);
extern Can_ReturnType Can_Write(Can_HwHandleType ucHthRefId, const Can_PduType* PduInfo_Write);
extern void Can_MainFunction_BusOff(void);
extern Can_ReturnType Can_SetControllerMode(uint8 ucController, Can_StateTransitionType ucMode);

#endif
