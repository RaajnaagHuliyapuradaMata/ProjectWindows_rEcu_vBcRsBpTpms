#include "Std_Types.hpp"

#include "infMcalCanSwcApplEcuM.hpp"
#include "infMcalCanSwcServiceSchM.hpp"

#include "can.hpp"
#include "device.hpp"
#include "CanIf.hpp"
#include "CanIf_Cfg_SymbolicNames.hpp"
#include "ComStack_Types.hpp"
#include "can_table.hpp"
#include "CanIf_Cbk.hpp"
#include "EcuM_Cbk.hpp"
#include "Os_ConfigInterrupts.hpp"
#include "CanTrcv.hpp"

CanIf_ControllerModeType ucControllerMode = CANIF_CS_UNINIT;

void infMcalCanSwcApplEcuM_vInitFunction(void){
  RS_CAN_Init();
  ucControllerMode = CANIF_CS_STARTED;
}

void Can_SetBaudrate(void){
}

Can_ReturnType Can_SetControllerMode(uint8 ucController, Can_StateTransitionType ucMode){
  switch(ucControllerMode){
   case CANIF_CS_SLEEP:
      if(ucMode == CAN_T_WAKEUP){
        RS_CAN_SetResetMode();
        Os_Disable_CAT2ISR_Can0Receive();
        Os_Disable_CAT2ISR_Can0Transmit();
        ucControllerMode = CANIF_CS_STOPPED;
      }
   break;

   case CANIF_CS_STOPPED:
      if(ucMode == CAN_T_START){
        RS_CAN_Init();
        Os_Enable_CAT2ISR_Can0Receive();
        Os_Enable_CAT2ISR_Can0Transmit();
        TRCV_Normal();
        ucControllerMode = CANIF_CS_STARTED;
      }
      else if(ucMode == CAN_T_SLEEP){
        RS_CAN_SetSleepMode();
        Os_Disable_CAT2ISR_Can0Receive();
        Os_Disable_CAT2ISR_Can0Transmit();
        TRCV_Standby();
        ucControllerMode = CANIF_CS_SLEEP;
      }
   break;

   case CANIF_CS_STARTED:
      if(ucMode == CAN_T_STOP){
        RS_CAN_SetResetMode();
        Os_Disable_CAT2ISR_Can0Receive();
        Os_Disable_CAT2ISR_Can0Transmit();
        ucControllerMode = CANIF_CS_STOPPED;
      }
   break;

    default:
   break;
  }

  CanIf_ControllerModeIndication(ucController, ucControllerMode);
  return CAN_OK;
}

void infMcalCanSwcServiceSchM_vMainFunctionBusOff(void){
  static uint8 ucBusoffTime = 0;

  if(RSCAN0C0STS & 0x10u){
   ucBusoffTime = cBUSOFFTIMEOUT;
  }
  if(ucBusoffTime > 0){
   CanIf_ControllerBusOff(0);
   if(--ucBusoffTime == 0){
      RSCAN0C0CTR |= 0x8;
      if(CanIf_SetPduMode(0, CANIF_ONLINE) == E_NOT_OK){
        ApplMcu_vPerformReset();
      }
   }
  }
}

void Can_ForwardMessageToCanIf(
   const Can_FrameType* tCanFrame
){
   Can_HwType                   tCanMailbox;
   Type_SwcServiceCom_stInfoPdu tPduInfo;
   CanIf_ControllerModeType tCanIfControllerMode;

   CanIf_GetControllerMode(
         0
      ,  &tCanIfControllerMode
   );
   if(
         tCanIfControllerMode
      == CANIF_CS_STARTED
   ){
      tCanMailbox.CanId = tCanFrame->ID;
      switch(
         tCanMailbox.CanId
      ){
         case CfgEcuabCanIf_dIdCanRx_ApplicationReq:           tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_1_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_BcmPeripheralMasterclock: tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_2_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_EspWheelSpeed_F:          tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_3_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_UdsReqPhy:                tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_4_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_UdsReqFunc:               tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_5_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_EspWheelSpeed_R:          tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_6_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_EspWheelPulsesStamped:    tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_7_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_TmmStatus:                tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_8_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_TmpsRdcData:              tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_9_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_VehStatus:                tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_10_Config;      break;
         case CfgEcuabCanIf_dIdCanRx_VmsStatusReq:             tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_11_Config;      break;
         default:                                                                                            break;
      }
      tCanMailbox.ControllerId = 0;
      tPduInfo.SduLength       = tCanFrame->DLC;
      tPduInfo.SduDataPtr      = (uint8*)tCanFrame->DB;

      CanIf_RxIndication_Internal(
            &tCanMailbox
         ,  &tPduInfo
      );
   }
}

Can_ReturnType Can_Write(
            Can_HwHandleType ucHthRefId
   ,  const Can_PduType*     PduInfo_Write
){
   Can_FrameType tTxCanFrame;
   uint8         i;
   for(
      i = 0;
      i < PduInfo_Write->length;
      i ++
   ){
      tTxCanFrame.DB[i] = PduInfo_Write->sdu[i];
   }
   tTxCanFrame.DLC   = PduInfo_Write->length;
   tTxCanFrame.ID    = PduInfo_Write->id;
   tTxCanFrame.IDE   = 0;
   tTxCanFrame.RTR   = 0;
   tTxCanFrame.THLEN = 0;
   Can_SendTxBuffer(
      &tTxCanFrame
   );
   CanIf_TxConfirmation(
      PduInfo_Write->swPduHandle
   );
   return CAN_OK;
}
