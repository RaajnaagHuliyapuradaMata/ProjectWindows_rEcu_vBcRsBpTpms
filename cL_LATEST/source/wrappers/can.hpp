#ifndef _CAN_H_
#define _CAN_H_

#include "rscanX.hpp"
#include "Com_Cfg_SymbolicNames.hpp"
#include "Can_GeneralTypes.hpp"

#define CAN_AR_RELEASE_MAJOR_VERSION                                           4
#define CAN_AR_RELEASE_MINOR_VERSION                                           2
#define CanConf_CanController_Can_Network_0_CANNODE_0                         0u

#define CfgEcuabCanIf_dIdCanRx_UdsReqPhy                           (uint16)0x73A
#define CfgEcuabCanIf_dIdCanRx_UdsReqFunc                          (uint16)0x7DF
#define CfgEcuabCanIf_dIdCanRx_VcuPowertrainInfo                   (uint16)0x0C0
#define CfgEcuabCanIf_dIdCanRx_ApplicationReq                      (uint16)0x620
#define CfgEcuabCanIf_dIdCanRx_EspWheelPulses                      (uint16)0x070
#define CfgEcuabCanIf_dIdCanRx_Odo                                 (uint16)0x351
#define CfgEcuabCanIf_dIdCanRx_VcuAmbientInfo                      (uint16)0x300
#define CfgEcuabCanIf_dIdCanRx_VcuWheelSpeed_F                     (uint16)0x341
#define CfgEcuabCanIf_dIdCanRx_EspVehicleSpeed                     (uint16)0x410
#define CfgEcuabCanIf_dIdCanRx_BcmPowerMode                        (uint16)0x107
#define CfgEcuabCanIf_dIdCanRx_EPOCHTime                           (uint16)0x060
#define CfgEcuabCanIf_dIdCanRx_VcuWheelSpeed_R                     (uint16)0x342
#define CfgEcuabCanIf_dIdCanRx_TmpsRdcData                         (uint16)0x400

#define CfgEcuabCanIf_dHrhStdMailBoxTx_01                                      0
#define CfgEcuabCanIf_dHrhStdMailBoxTx_02                                      1
#define CfgEcuabCanIf_dHrhStdMailBoxTx_03                                      2
#define CfgEcuabCanIf_dHrhStdMailBoxTx_04                                      3
#define CfgEcuabCanIf_dHrhStdMailBoxTx_05                                      4
#define cBUSOFFTIMEOUT                                                       200

extern void Can_ForwardMessageToCanIf(
   const Can_FrameType* tCanFrame
);

extern Can_ReturnType Can_Write(
            Can_HwHandleType ucHthRefId
   ,  const Can_PduType*     PduInfo_Write
);

extern Can_ReturnType Can_SetControllerMode(
      uint8                   ucController
   ,  Can_StateTransitionType ucMode
);

#endif
