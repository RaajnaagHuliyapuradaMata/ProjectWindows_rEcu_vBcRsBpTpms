/******************************************************************************/
/* File   : McalCan.c                                                         */
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

#include "infMcalCanSwcApplEcuM.hpp"
#include "infMcalCanSwcServiceSchM.hpp"
#include "infMcalCanEcuabCanIf.hpp"

#include "rscanX.hpp"
#include "Com_Cfg_SymbolicNames.hpp"
#include "Can_GeneralTypes.hpp"

#include "device.hpp"
#include "CanIf.hpp"
#include "CanIf_Cfg_SymbolicNames.hpp"
#include "ComStack_Types.hpp"
#include "can_table.hpp"
#include "CanIf_Cbk.hpp"
#include "EcuM_Cbk.hpp"
#include "Os_ConfigInterrupts.hpp"
#include "CanTrcv.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CAN_AR_RELEASE_MAJOR_VERSION                                           4
#define CAN_AR_RELEASE_MINOR_VERSION                                           2
#define CfgEcuabCanIf_dIdCanRx_UdsReqPhy                           (uint16)0x73A
#define CfgEcuabCanIf_dIdCanRx_UdsReqFunc                          (uint16)0x7DF
#define CfgEcuabCanIf_dIdCanRx_ApplicationReq                      (uint16)0x63A
#define CfgEcuabCanIf_dIdCanRx_BcmPeripheralMasterclock            (uint16)0x208
#define CfgEcuabCanIf_dIdCanRx_EspWheelSpeed_F                     (uint16)0x209
#define CfgEcuabCanIf_dIdCanRx_EspWheelSpeed_R                     (uint16)0x20A
#define CfgEcuabCanIf_dIdCanRx_EspWheelPulsesStamped               (uint16)0x20B
#define CfgEcuabCanIf_dIdCanRx_TmmStatus                           (uint16)0x315
#define CfgEcuabCanIf_dIdCanRx_TmpsRdcData                         (uint16)0x300
#define CfgEcuabCanIf_dIdCanRx_VehStatus                           (uint16)0x210
#define CfgEcuabCanIf_dIdCanRx_VmsStatusReq                        (uint16)0x330
#define cBUSOFFTIMEOUT                                                       200

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
Type_EcuabCanIf_eModeController ucControllerMode = CANIF_CS_UNINIT;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void infMcalCanSwcApplEcuM_vInitFunction(void){
  RS_CAN_Init();
  ucControllerMode = CANIF_CS_STARTED;
}

void Can_SetBaudrate(void){
}

Type_McalCan_eReturn infMcalCanEcuabCanIf_tSetModeController(
      uint8                   ucController
   ,  Type_McalCan_eStateTransition ucMode
){
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

FUNC(void, MCALCAN_CODE) infMcalMcuSwcServiceSchM_vRunnableRx(
   const Type_McalCan_stFrame* tCanFrame
){
   Can_HwType                   tCanMailbox;
   Type_SwcServiceCom_stInfoPdu tPduInfo;
   Type_EcuabCanIf_eModeController tCanIfControllerMode;

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

Type_McalCan_eReturn infMcalCanEcuabCanIf_tWrite(
            Type_McalCan_tHandleHw ucHthRefId
   ,  const Type_McalCan_stPdu*     PduInfo_Write
){
   Type_McalCan_stFrame tTxCanFrame;
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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

