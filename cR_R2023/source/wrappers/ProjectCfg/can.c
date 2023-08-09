

#include "can.h"
#include "device.h"
#include "CanIf_RxIndication_Integration.h"
#include "ComStack_Types.h"
#include "can_table.h"
#include "CanIf_Cbk.h"
#include "EcuM_Cbk.h"
#include "Os_ConfigInterrupts.h"
#include "CanTrcv.h"

// Content: mode type
// CANIF_CS_UNINIT = 0,      Default mode of the CAN Driver and all CAN controllers connected to one CAN network after power on. \n
// CANIF_CS_STOPPED,         At least one of all CAN controllers connected to one CAN network is halted and does not operate on the network. \n
// CANIF_CS_STARTED,         All CAN controllers connected to one CAN network are started by the CAN Driver and in full-operational mode. \n  switch (ucMode)
// CANIF_CS_SLEEP,           At least one of all CAN controllers connected to one CAN network are set into the SLEEP mode and can be woken up  {
//                           by request of the CAN Driver or by a network event \n
CanIf_ControllerModeType ucControllerMode = CANIF_CS_UNINIT;

void Can_Init(void)
{

  RS_CAN_Init();
  ucControllerMode = CANIF_CS_STARTED;
}

void Can_SetBaudrate(void)
{

}

Can_ReturnType Can_SetControllerMode(uint8 ucController, Can_StateTransitionType ucMode)
{
  switch (ucControllerMode)
  {
    case CANIF_CS_SLEEP:
      if (ucMode == CAN_T_WAKEUP)
      {
        //switch Can0 to STOPPED Mode (Renesas: global+channel reset)
        RS_CAN_SetResetMode();
        Os_Disable_CAT2ISR_Can0Receive();
        Os_Disable_CAT2ISR_Can0Transmit();
        ucControllerMode = CANIF_CS_STOPPED;
      }
    break;

    case CANIF_CS_STOPPED:
      if (ucMode == CAN_T_START)
      {
        //switch Can0 to Communication mode.  (Renesas: Global+Channel operating mode)
        //RS_CAN_SetCommunicationMode();
        RS_CAN_Init(); // Reset whole CAN (Autosar SWS_Can_00384). -> RST todo: should we do it like this...?
        Os_Enable_CAT2ISR_Can0Receive();
        Os_Enable_CAT2ISR_Can0Transmit();

        TRCV_Normal();
        ucControllerMode = CANIF_CS_STARTED;
      }
      else if (ucMode == CAN_T_SLEEP)
      {
        //switch Can0 to Sleep mode (Renesas: global+channel stop mode, clock off for complete CAN controller)
        RS_CAN_SetSleepMode();
        Os_Disable_CAT2ISR_Can0Receive();
        Os_Disable_CAT2ISR_Can0Transmit();
        TRCV_Standby();
        ucControllerMode = CANIF_CS_SLEEP;
      }
    break;

    case CANIF_CS_STARTED:
      if (ucMode == CAN_T_STOP)
      {
        //switch Can0 to STOPPED Mode (Renesas: global+channel reset)
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

void Can_MainFunction_BusOff(void)
{
  static uint8 ucBusoffTime = 0;

  if (RSCAN0C0STS & 0x10u)
  {
    ucBusoffTime = cBUSOFFTIMEOUT;
  }

  if (ucBusoffTime > 0)
  {
    CanIf_ControllerBusOff(0);
    if (--ucBusoffTime == 0)
    {
      RSCAN0C0CTR |= 0x8;

      if (CanIf_SetPduMode(0, CANIF_ONLINE) == E_NOT_OK)
      {
        Mcu_PerformReset();
      }
    }
  }
}

void Can_ForwardMessageToCanIf(const Can_FrameType *tCanFrame)
{
  Can_HwType tCanMailbox;
  PduInfoType tPduInfo;
  CanIf_ControllerModeType tCanIfControllerMode;

  CanIf_GetControllerMode(0, &tCanIfControllerMode);

  if (tCanIfControllerMode == CANIF_CS_STARTED)
  {

    tCanMailbox.CanId = tCanFrame->ID;

    switch (tCanMailbox.CanId)
    {
      case CanMsgApplicationRequest_TPM:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_1_Config;
      break;

      case CanMsgBCM_peripheralMasterclock:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_2_Config;
      break;

      case CanMsgESP_WSpeed_Front_BodyLCAN:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_3_Config;
      break;

      case CanMsgUDS_Rx_Functional:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_5_Config;
      break;

      case CanMsgUDS_Rx_Physical:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_4_Config;
      break;

      case CanMsgESP_WSpeed_Rear_BodyLCAN:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_6_Config;
      break;

      case CanMsgESP_Wheel_Pulse_Stamped:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_7_Config;
      break;

      case CanMsgTMM_Status_BodyLCAN:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_8_Config;
      break;

      case CanMsgRdcData_TPM:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_9_Config;
      break;

      case CanMsgVehSts_BodyLCAN:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_10_Config;
      break;

      case CanMsgVmsStsReq_BodyLCAN:
        tCanMailbox.Hoh = CanIfConf_CanIfHrhCfg_Can_Network_CANNODE_0_Rx_Std_MailBox_11_Config;
      break;

      default:
      break;
    }

    tCanMailbox.ControllerId = 0;

    tPduInfo.SduLength = tCanFrame->DLC;

    tPduInfo.SduDataPtr = (uint8*)tCanFrame->DB;

    CanIf_RxIndication(&tCanMailbox, &tPduInfo);
  }
}

Can_ReturnType Can_Write(Can_HwHandleType ucHthRefId, const Can_PduType* PduInfo_Write)
{
  Can_FrameType tTxCanFrame;
  uint8 i;

  for (i=0; i<PduInfo_Write->length; i++)
  {
    tTxCanFrame.DB[i] = PduInfo_Write->sdu[i];
  }

  tTxCanFrame.DLC = PduInfo_Write->length;
  tTxCanFrame.ID = PduInfo_Write->id;
  //tTxCanFrame.LBL = PduInfo_Write->swPduHandle; ??

  tTxCanFrame.IDE = 0;
  tTxCanFrame.RTR = 0;
  tTxCanFrame.THLEN = 0;

  Can_SendTxBuffer(&tTxCanFrame);
  CanIf_TxConfirmation(PduInfo_Write->swPduHandle);

  //CanIf_ReadTxNotifStatus(0);//<0,1,2,3, je nach TX PDU!);

  return CAN_OK;
}

//typedef struct
//{
//  uint32 rRSCAN0RMNB;    //set global buffer
//  uint32 rRSCAN0GCTR;    //global control register, irq settings
//  uint32 rRSCAN0TMIEC0;  //transmit buffer irq enable
//  uint32 rRSCAN0GSTS;    //global status register
//  uint32 rRSCAN0C0STS;   //channel status register
//  uint32 rRSCAN0GCFG;    //clock setting
//  uint32 rRSCAN0C0CFG;   //channel baudrate
//  uint32 rRSCAN0C0CTR;   //channel control register, comm mode
//  uint32 rRSCAN0RFCC0;   //rec fifo control reg, fifo enable
//  uint32 rRSCAN0RFSTS0;  //fifo status reg, Bit0 RFEMP==0 -> message received
//  uint32 rRSCAN0GAFLCFG0;  //rec rule config reg, number of used can rules
//  uint32 rRSCAN0GAFLID0; // base address of rules list
//  uint32 rRSCAN0GAFLM;   //compare mask
//  uint32 rRSCAN0GAFLP0;  //
//  uint32 rRSCAN0GAFLP1;  //fifo number
//}register_content;
//
//typedef struct
//{
//  uint32 rCKSC_CPUCLKS_CTL    ;
//  uint32 rCKSC_CPUCLKS_ACT    ;
//  uint32 rCKSC_CPUCLKD_CTL    ;
//  uint32 rCKSC_CPUCLKD_ACT    ;
//  uint32 rCKSC_ICANS_CTL      ;
//  uint32 rCKSC_ICANS_ACT      ;
//  uint32 rCKSC_ICANS_STPM     ;
//  uint32 rCKSC_ICANOSCD_CTL   ;
//  uint32 rCKSC_ICANOSCD_ACT   ;
//  uint32 rCKSC_ICANOSCD_STPM  ;
//
//}clockreg_content;
//
//  #define point_to(x) *((uint32*)(x))
//  #define kCanBaseAdr 0xFFD00000uL
//  #define rCLOCK_BASE_ADDRESS 0xFFF81000
//void CheckRegisters(void);
//void CheckRegisters(void)
//{
//  volatile register_content regs;
//  volatile clockreg_content creg;
//
//   regs.rRSCAN0RMNB =      point_to(kCanBaseAdr + 0xa4);
//   regs.rRSCAN0GCTR =      point_to(kCanBaseAdr + 0x88);
//   regs.rRSCAN0TMIEC0 =    point_to(kCanBaseAdr + 0x390);
//   regs.rRSCAN0GSTS =      point_to(kCanBaseAdr + 0x8c);
//   regs.rRSCAN0C0STS =     point_to(kCanBaseAdr + 0x8);
//   regs.rRSCAN0GCFG =      point_to(kCanBaseAdr + 0x84);
//   regs.rRSCAN0C0CFG =     point_to(kCanBaseAdr + 0x0);
//   regs.rRSCAN0C0CTR =     point_to(kCanBaseAdr + 0x4);
//   regs.rRSCAN0RFCC0 =     point_to(kCanBaseAdr + 0xb8);
//   regs.rRSCAN0RFSTS0 =    point_to(kCanBaseAdr + 0xd8);
//   regs.rRSCAN0GAFLCFG0 =  point_to(kCanBaseAdr + 0x9c);
//   regs.rRSCAN0GAFLID0 =   point_to(kCanBaseAdr + 0x500);
//   regs.rRSCAN0GAFLM =     point_to(kCanBaseAdr + 0x504);
//   regs.rRSCAN0GAFLP0 =    point_to(kCanBaseAdr + 0x508);
//   regs.rRSCAN0GAFLP1 =    point_to(kCanBaseAdr + 0x50c);
//
//   creg.rCKSC_CPUCLKS_CTL   = point_to(rCLOCK_BASE_ADDRESS + 0x9000);
//   creg.rCKSC_CPUCLKS_ACT   = point_to(rCLOCK_BASE_ADDRESS + 0x9008);
//   creg.rCKSC_CPUCLKD_CTL   = point_to(rCLOCK_BASE_ADDRESS + 0x9100);
//   creg.rCKSC_CPUCLKD_ACT   = point_to(rCLOCK_BASE_ADDRESS + 0x9108);
//   creg.rCKSC_ICANS_CTL     = point_to(rCLOCK_BASE_ADDRESS + 0x9900);
//   creg.rCKSC_ICANS_ACT     = point_to(rCLOCK_BASE_ADDRESS + 0x9908);
//   creg.rCKSC_ICANS_STPM    = point_to(rCLOCK_BASE_ADDRESS + 0x9918);
//   creg.rCKSC_ICANOSCD_CTL  = point_to(rCLOCK_BASE_ADDRESS + 0x9A00);
//   creg.rCKSC_ICANOSCD_ACT  = point_to(rCLOCK_BASE_ADDRESS + 0x9A08);
//   creg.rCKSC_ICANOSCD_STPM = point_to(rCLOCK_BASE_ADDRESS + 0x9A18);
//}