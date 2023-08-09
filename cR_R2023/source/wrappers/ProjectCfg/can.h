

#ifndef _CAN_H_
#define _CAN_H_

#include "rscanX.h"
#include "Com_Cfg_SymbolicNames.h"
#include "Can_GeneralTypes.h"

#define CAN_AR_RELEASE_MAJOR_VERSION  4
#define CAN_AR_RELEASE_MINOR_VERSION  2

#define CanConf_CanController_Can_Network_CANNODE_0 0u

//#define CanMsgApplicationRequest_TPM    0x620
//#define CanMsgWheelPulseCount_TPM       0x0E9
//#define CanMsgVehicleData               0x409
//#define CanMsgEnvironmentData           0x408
//#define CanMsgRdcData_TPM               0x300
//#define CanMsgUdsRxPhysical             0x73A
//#define CanMsgUdsRxFunctional           0x7DF

//#define CanMsgApplicationRequest_TPM       (uint16)0x620
//#define CanMsgRdcData_TPM                  (uint16)0x300
//#define CanMsgBCM_peripheralMasterclock    (uint16)0x208
//#define CanMsgESP_WSpeed_Front_BodyLCAN    (uint16)0x209
//#define CanMsgUDS_Rx_Functional            (uint16)0x7DF
//#define CanMsgUDS_Rx_Physical              (uint16)0x73A
//#define CanMsgESP_WSpeed_Rear_BodyLCAN     (uint16)0x20A
//#define CanMsgESP_Wheel_Pulse_Stamped      (uint16)0x20B
//#define CanMsgTMM_Status_BodyLCAN          (uint16)0x315
//#define CanMsgVehSts_BodyLCAN              (uint16)0x210
//#define CanMsgVmsStsReq_BodyLCAN           (uint16)0x330

//#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_1  0   // 0x600 Application Cyclic
//#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_2  1   // 0x541 HMI Temp + Ref Pressure
//#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_3  2   // 0x610 Application Response
//#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_4  3   // 0x530 HMI Pressure
//#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_5  4   // 0x77A UDS TX

//#define CanMsgApplicationRequest_TPM       (uint16)0x620
#define CanMsgApplicationRequest_TPM       (uint16)0x63A
#define CanMsgBCM_peripheralMasterclock    (uint16)0x208
#define CanMsgESP_WSpeed_Front_BodyLCAN    (uint16)0x209
#define CanMsgUDS_Rx_Physical              (uint16)0x73A
#define CanMsgUDS_Rx_Functional            (uint16)0x7DF
#define CanMsgESP_WSpeed_Rear_BodyLCAN     (uint16)0x20A
#define CanMsgESP_Wheel_Pulse_Stamped      (uint16)0x20B
#define CanMsgTMM_Status_BodyLCAN          (uint16)0x315
#define CanMsgRdcData_TPM                  (uint16)0x300
#define CanMsgVehSts_BodyLCAN              (uint16)0x210
#define CanMsgVmsStsReq_BodyLCAN           (uint16)0x330

#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_1  0   // 0x6DA Application Cyclic
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_2  1   // 0x541 HMI Temp + Ref Pressure
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_3  2   // 0x67A Application Response
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_4  3   // 0x77A UDS TX
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_5  4   // 0x530 HMI Pressure

#define cBUSOFFTIMEOUT  200

extern void Can_Init(void);
extern void Can_ForwardMessageToCanIf(const Can_FrameType *tCanFrame);
extern Can_ReturnType Can_Write(Can_HwHandleType ucHthRefId, const Can_PduType* PduInfo_Write);
extern void Can_MainFunction_BusOff(void);
extern void Can_MainFunction_Wakeup(void);
extern Can_ReturnType Can_SetControllerMode(uint8 ucController, Can_StateTransitionType ucMode);

#endif
