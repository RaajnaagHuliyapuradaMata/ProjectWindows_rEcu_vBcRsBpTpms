#ifndef _CAN_H_
#define _CAN_H_

#include "rscanX.hpp"
#include "Com_Cfg_SymbolicNames.hpp"
#include "Can_GeneralTypes.hpp"

#define CAN_AR_RELEASE_MAJOR_VERSION                                           4
#define CAN_AR_RELEASE_MINOR_VERSION                                           2
#define CanConf_CanController_Can_Network_CANNODE_0 0u
#define CfgEcuabCanIf_dIdCanRx_UdsReqPhy                           (uint16)0x73A
#define CfgEcuabCanIf_dIdCanRx_UdsReqFunc                          (uint16)0x7DF
#define CfgEcuabCanIf_dIdCanRx_ApplicationReq       (uint16)0x63A
#define CfgEcuabCanIf_dIdCanRx_BcmPeripheralMasterclock    (uint16)0x208
#define CfgEcuabCanIf_dIdCanRx_EspWheelSpeed_F    (uint16)0x209
#define CfgEcuabCanIf_dIdCanRx_EspWheelSpeed_R     (uint16)0x20A
#define CfgEcuabCanIf_dIdCanRx_EspWheelPulsesStamped      (uint16)0x20B
#define CfgEcuabCanIf_dIdCanRx_TmmStatus          (uint16)0x315
#define CfgEcuabCanIf_dIdCanRx_TmpsRdcData                  (uint16)0x300
#define CfgEcuabCanIf_dIdCanRx_VehStatus              (uint16)0x210
#define CfgEcuabCanIf_dIdCanRx_VmsStatusReq           (uint16)0x330

#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_1  0
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_2  1
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_3  2
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_4  3
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_5  4
#define CanConf_CanHardwareObject_Can_Network_CANNODE_0_Tx_Std_MailBox_6  5
#define cBUSOFFTIMEOUT                                                       200

extern void Can_ForwardMessageToCanIf(
   const Can_FrameType* tCanFrame
);

extern Can_ReturnType Can_Write(
            Can_HwHandleType ucHthRefId
   ,  const Can_PduType*     PduInfo_Write
);

extern void Can_MainFunction_Wakeup(void);

extern Can_ReturnType Can_SetControllerMode(
      uint8                   ucController
   ,  Can_StateTransitionType ucMode
);

#endif
