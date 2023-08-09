

#include "rscan.h"
#include "gpioX.h"

void RS_CAN_Init(void)
{

    protected_write(PROTCMD1,PROTS1,CKSC_ICANOSCD_CTL,0x01u);
    while(CKSC_ICANOSCD_ACT!=0x01);

    protected_write(PROTCMD1,PROTS1,CKSC_ICANS_CTL, 0x03);
    while(CKSC_ICANS_ACT!=0x03);

    GPIO_CanInit();

    while((RSCAN0GSTS & 0x00000008u)) {}

    RSCAN0GCTR &= 0xfffffffbu;
		RSCAN0C0CTR &= 0xfffffffbu;

    RSCAN0GCFG = 0x00000010u;

    RSCAN0C0CFG = 0x023a0001u;
    // RST Info: These settings must be the same for all network participants: bootloader, application, canoe and vFlash!
    // SJW = Sync Jump Width
    // TSEG = Can controller phase segment
    // TQ = Time quantas (this value, e.g. 10 for 10 tq, is set in the configuration tools!),
    // BRP = Baud Rate Prescaler (to be set in DaVinci configurator, Etas does not support this?)
    // The settings in ETAS Isolar B are not relevant because the Can controller is initialzied manually here.
    // Anyway they should be set to the same, so that it's not confusing.

    /* ==== Rx rule setting ==== */
    Can_SetRxRule();

    /* ==== Fifo setting ==== */
    RSCAN0RMNB = 0x00;              /* No RX buffers used. Fifo only. */

    /* FIFO 0 */
    RSCAN0RFCC0 |= 0x1000;          /* RFIM bit:  IRQ on each message reception */
    RSCAN0RFCC0 |= 0x400;           /* RFDC bits: Fifo size 32 messages         */
    RSCAN0RFCC0 |= 0x2;             /* RFIE bit:  RX interrupt enabled          */
    //FIFO 1..4
    //RSCAN0RFCC1 |= 0x1000;
    //RSCAN0RFCC1 |= 0x200;
    //RSCAN0RFCC1 |= 0x2;
    //RSCAN0RFCC2 |= 0x1000;
    //RSCAN0RFCC2 |= 0x200;
    //RSCAN0RFCC2 |= 0x2;
    //RSCAN0RFCC3 |= 0x1000;
    //RSCAN0RFCC3 |= 0x200;
    //RSCAN0RFCC3 |= 0x2;
    //RSCAN0RFCC4 |= 0x1000;
    //RSCAN0RFCC4 |= 0x200;
    //RSCAN0RFCC4 |= 0x2;

    /* RX Fifo activation is done at the end in Global operating mode! */

    /* ==== interrupt settings ==== */
    RSCAN0GCTR &= 0xfffff8ffu;     /* Set THLEIE disabled, MEIE(FIFO Message Lost Interrupt disabled)  */
    //RSCAN0CFCC0 |= 0x00000006u;    /* Set CFTXIE (CANm t/r FIFO tx compl) and CFRXIE (CANm t/r FIFO rx compl) */  //nur für combined fifos
    RSCAN0TMIEC0 = 0x000000ff;     /* Set TMIE (transmit interrupt enable) for TX buffer 0 */

    /* ==== Switch global operation mode ==== */
    /* If GlobalChannel in halt or reset mode */
    if (RSCAN0GSTS & 0x03u)
    {
      RSCAN0GCTR &= 0xfffffffcu;    /*Switch to communication mode */
      while ((RSCAN0GSTS & 0x02u) == 2u) {
          /* While halt mode */
      }
      while ((RSCAN0GSTS & 0x01u) == 1u) {
          /* While reset mode */
      }
    }

    /* ==== Switch channel operation mode ==== */
    /* If Channel0 in halt or reset mode */
    if (RSCAN0C0STS & 0x03u)
    {
      RSCAN0C0CTR &= 0xfffffffcu;    /*Switch to communication mode */
      while ((RSCAN0C0STS & 0x02u) == 2u) {
          /* While halt mode */
      }
      while ((RSCAN0C0STS & 0x01u) == 1u) {
          /* While reset mode */
      }
    }

    /* Enable RX Fifo 0 (RFE bit) */
    RSCAN0RFCC0 |= 0x1;
    //FIFO 1..4
    //RSCAN0RFCC1 |= 0x1;
    //RSCAN0RFCC2 |= 0x1;
    //RSCAN0RFCC3 |= 0x1;
    //RSCAN0RFCC4 |= 0x1;

}

/*****************************************************************************
** Function:    RS_CAN_SetSleepMode
** Description: Sets Can0 to sleep mode (CAN_IF_SLEEP)
** Parameter:   None
** Return:      None
******************************************************************************/
void RS_CAN_SetSleepMode(void)
{
  RSCAN0C0CTR |= 0x2;   // set CSLPR: channel stop mode
  RSCAN0GCTR |= 0x2;    // set GSLPR: global stop mode
}

/*****************************************************************************
** Function:    RS_CAN_SetResetMode
** Description: Sets Can0 to Reset mode (CAN_IF_STOPPED)
** Parameter:   None
** Return:      None
******************************************************************************/
void RS_CAN_SetResetMode(void)
{
  RSCAN0C0CTR &= ~0x2;  // clear CSLPR
  RSCAN0GCTR &= ~0x2;   // clear GSLPR

  RSCAN0C0CTR |= 0x1;   // set CHMDC 01b: channel reset mode
  RSCAN0GCTR |= 0x1;    // set GMCD 01b: global reset mode
}

/*****************************************************************************
** Function:    RS_CAN_SetCommunicationMode
** Description: Sets Can0 to communication mode (CAN_IF_STARTED)
** Parameter:   None
** Return:      None
******************************************************************************/
void RS_CAN_SetCommunicationMode(void)
{
  RSCAN0C0CTR &= ~0x2;  // clear CSLPR
  RSCAN0GCTR &= ~0x2;   // clear GSLPR

  RSCAN0C0CTR &= ~0x1;   // clear CHMDC 01b: channel comm mode
  RSCAN0GCTR &= ~0x1;    // clear GMCD 01b: global comm mode
}

/*****************************************************************************
** Function:    Can_ReadRxFiFo
** Description: Read one message from FiFo 0
** Parameter:   Can_FrameType* pFrame
** Return:      CAN_RTN_BUFFER_EMPTY = no more messages
**              CAN_RTN_OK = more messages to read in FiFo
******************************************************************************/
Can_RtnType Can_ReadRxFiFo(Can_FrameType* pFrame)
{
  Can_RtnType tRetVal;

  if ((RSCAN0RFSTS0 & 0x1) == 0)      /* RFEMP == 0: there are messages to read */
  {
    /* Read message meta data */
    pFrame->IDE   = (RSCAN0RFID0  & 0x80000000) >> 31;
    pFrame->RTR   = (RSCAN0RFID0  & 0x40000000) >> 30;
    pFrame->THLEN = (RSCAN0RFID0  & 0x20000000) >> 29;  // RST: not used. Bit is always default in the register.
    pFrame->ID    = (RSCAN0RFID0  & 0x1fffffff);
    pFrame->DLC   = (RSCAN0RFPTR0 & 0xf0000000) >> 28;
    pFrame->LBL   = (RSCAN0RFPTR0 & 0x0fff0000) >> 16;
    pFrame->TS    = (RSCAN0RFPTR0 & 0x0000ffff);

    /* Read message data bytes */
    pFrame->DB[7] = (RSCAN0RFDF10 & 0xff000000) >> 24;
    pFrame->DB[6] = (RSCAN0RFDF10 & 0x00ff0000) >> 16;
    pFrame->DB[5] = (RSCAN0RFDF10 & 0x0000ff00) >> 8;
    pFrame->DB[4] = (RSCAN0RFDF10 & 0x000000ff) >> 0;
    pFrame->DB[3] = (RSCAN0RFDF00 & 0xff000000) >> 24;
    pFrame->DB[2] = (RSCAN0RFDF00 & 0x00ff0000) >> 16;
    pFrame->DB[1] = (RSCAN0RFDF00 & 0x0000ff00) >> 8;
    pFrame->DB[0] = (RSCAN0RFDF00 & 0x000000ff) >> 0;

    RSCAN0RFPCTR0 = 0xff;             /* Increase FiFo pointer */
  }

  if ((RSCAN0RFSTS0 & 0x1) == 1)      /* RFEMP == 1: FiFo empty */
  {
    tRetVal = CAN_RTN_BUFFER_EMPTY;
  }
  else
  {
    tRetVal = CAN_RTN_OK;
  }

  return tRetVal;
}

/*****************************************************************************
** Function:    Can_SendTxBuffer
** Description: Send a message via Tx buffer 0..15 on CAN0. Function uses all
**              TX buffers in a circle. So there should never be an overflow.
** Parameter:   Can_FrameType* pFrame - Pointer to frame data
** Return:      CAN_RTN_OK  - Frame sent
**              CAN_RTN_ERR - Not sent (all TX buffers in use)
******************************************************************************/
Can_RtnType Can_SendTxBuffer(const Can_FrameType* pFrame)
{
  static uint8 ucTxBufIdx = 0;
  uint8 ucRetVal;
  VU8* pTBSR;
  VU8* pTBCR;
  Can_FrameType* pTxBuffer;

  pTBSR = &(RSCAN0TMSTS0);
  pTBCR = &(RSCAN0TMC0);

  /* ---- Return if Tx Buffer is transmitting -> Buffer overflow! ---- */
  if((pTBSR[ucTxBufIdx] & (VU8)0x01u) == CAN_TBTST_TRANSMITTING)
  {
    ucRetVal = CAN_RTN_ERR;
  }

  else
  {
    /* Store message to tx buffer */
    pTxBuffer = (Can_FrameType*) &(RSCAN0TMID0);
    pTxBuffer[ucTxBufIdx] = *pFrame;

    /* Set transmission request */
    pTBCR[ucTxBufIdx] = CAN_TBCR_TRM;
    ucRetVal = CAN_RTN_OK;

    /* Select next TX buffer */
    ucTxBufIdx++;
    ucTxBufIdx %= CAN_CHNL_TX_BUF_NUM;
  }

  return ucRetVal;
}

/*****************************************************************************
** Function:    Can_ClearRxFiFoInterruptFlag
** Description: Clear interrupt flag for FiFo 0
** Parameter:   none
** Return:      none
******************************************************************************/
void Can_ClearRxFiFoInterruptFlag(void)
{
  RSCAN0RFSTS0 &= ~0x8;    /* Clear RFIF bit */
}

/*****************************************************************************
** Function:    Can_ClearTxInterruptFlag
** Description: Clear TMTRF bits (clears interrupt flags for Tx Buffers)
** Parameter:   none
** Return:      none
******************************************************************************/
void Can_ClearTxBufferInterruptFlag(void)
{
  VU8* pTBSR;
  uint8 ucTxBufIdx;

  pTBSR = &(RSCAN0TMSTS0);
  for (ucTxBufIdx = 0; ucTxBufIdx < CAN_CHNL_TX_BUF_NUM; ucTxBufIdx++)
  {
    pTBSR[ucTxBufIdx] = CAN_CLR;  /* clear flags in all tx buffers, that's the easiest way */
  }
}

static void Can_SetRxRule(void)
{
  U16 RxRuleIdx;
  U8 PageRxRuleIdx;
  volatile CAN_RX_RULE_TYPE* pCRE;

  RSCAN0GAFLCFG0 |= (RX_RULE_NUM_CH0 << 24);

  pCRE = (volatile CAN_RX_RULE_TYPE*)&(RSCAN0GAFLID0);

  RSCAN0GAFLECTR |= 0x00000100u;

  for (RxRuleIdx = 0U; RxRuleIdx < CAN_RX_RULE_NUM; RxRuleIdx++)
  {
    PageRxRuleIdx = (U8) (RxRuleIdx & CAN_PAGE_RX_RULE_IDX_MASK);

    if (PageRxRuleIdx == 0U)
    {
        RSCAN0GAFLECTR |= RxRuleIdx >> CAN_RX_RULE_PAGE_IDX_BIT_POS;
    }

    pCRE[PageRxRuleIdx] = CAN_RX_RULE_TABLE[RxRuleIdx];
  }

  RSCAN0GAFLECTR &= 0xfffffeffu;
}

//
// void RS_CAN_Init_Old(void)
// {
//
//     protected_write(PROTCMD1,PROTS1,CKSC_ICANOSCD_CTL,0x01u);
//     while (PROTS1 == 0x01u){}
//
//
//     GPIO_CanInit();
//
//
//     while((RSCAN0GSTS & 0x00000008u)) {}
//
//
//     RSCAN0GCTR &= 0xfffffffbu;
//
// 		RSCAN0C0CTR &= 0xfffffffbu;
// 		//RSCAN0C3CTR &= 0xfffffffbu;
//     //RSCAN0C4CTR &= 0xfffffffbu;
//
//
//     RSCAN0GCFG = 0x00000010u;
//
//
//
//     RSCAN0C0CFG = 0x023a0001u;
//
// 		//RSCAN0C3CFG = 0x023a0001u;
//
// 		//RSCAN0C4CFG = 0x023a0001u;
//
//
//     Can_SetRxRule();
//
//
//     RSCAN0RMNB = 0x10u;
//
//
//     RSCAN0GCTR &= 0xfffff8ffu;
//     //RSCAN0CFCC0 |= 0x00000006u;      //geht nicht.
//     RSCAN0TMIEC0 = 0x0000000FF;
//
//
//     if (RSCAN0GSTS & 0x03u)
//     {
//       RSCAN0GCTR &= 0xfffffffcu;
//       while ((RSCAN0GSTS & 0x02u) == 2u) {
//
//       }
//       while ((RSCAN0GSTS & 0x01u) == 1u) {
//
//       }
//     }
//
//
//     if (RSCAN0C0STS & 0x03u)
//     {
//       RSCAN0C0CTR &= 0xfffffffcu;
//       while ((RSCAN0C0STS & 0x02u) == 2u) {
//
//       }
//       while ((RSCAN0C0STS & 0x01u) == 1u) {
//
//       }
//     }
//
//
//     GPIO_CanStandby(CAN_DISABLE);
//
//     GPIO_CanEnable(CAN_ENABLE);
//
// }
//
//
//
//
// Can_RtnType Can_ReadRxBuffer(Can_FrameType* pFrame)
// {
//   U8 BufIdx;
//   U8 CRBRCFiBufIdx;
//   U8 OverwrittenFlag;
//   U32 TempCRBRCF0;
//   U32 TempCRBRCF1;
//   //U32 TempCRBRCF2;
//   Can_FrameType* pRxBuffer;
//   VU32* pCRBRCF;
//   Can_RtnType RtnValue;
//
//
//   TempCRBRCF0 = RSCAN0RMND0;
//   TempCRBRCF1 = RSCAN0RMND1;
//   //TempCRBRCF2 = RSCAN0RMND2;
//   if ((TempCRBRCF0 == CAN_CLR) && (TempCRBRCF1 == CAN_CLR)) //&& (TempCRBRCF2 == CAN_CLR))
//   {
//     RtnValue = CAN_RTN_BUFFER_EMPTY;
//   }
//   else
//   {
//
//     if (TempCRBRCF0 != CAN_CLR)
//     {
//       pCRBRCF = &(RSCAN0RMND0);
//       for (BufIdx = 0U; BufIdx < CAN_CRBRCF0_RX_BUF_NUM; ++BufIdx)
//       {
//         if ((TempCRBRCF0 & CAN_1_BIT_MASK) == CAN_SET)
//         {
//           break;
//         }
//         TempCRBRCF0 = TempCRBRCF0 >> CAN_B1_BIT_POS;
//       }
//     }
//     else if (TempCRBRCF1 != CAN_CLR)
//     {
//       pCRBRCF = &(RSCAN0RMND1);
//       for (BufIdx = 0U; BufIdx < CAN_CRBRCF1_RX_BUF_NUM; ++BufIdx)
//       {
//         if ((TempCRBRCF1 & CAN_1_BIT_MASK) == CAN_SET)
//         {
//             break;
//         }
//         TempCRBRCF1 = TempCRBRCF1 >> CAN_B1_BIT_POS;
//       }
//       BufIdx += CAN_CRBRCF0_RX_BUF_NUM;
//     }
//
//
//
//     CRBRCFiBufIdx = BufIdx & CAN_5_BIT_MASK;
//
//     do
//     {
//
//       do
//       {
//         CLR_BIT(*pCRBRCF, CRBRCFiBufIdx);
//       } while (GET_BIT(*pCRBRCF, CRBRCFiBufIdx) == CAN_SET);
//
//
//       pRxBuffer = (Can_FrameType*) &(RSCAN0RMID0);
//       *pFrame = pRxBuffer[BufIdx];
//
//
//       OverwrittenFlag = GET_BIT(*pCRBRCF, CRBRCFiBufIdx);
//
//       if (OverwrittenFlag == CAN_SET)
//       {
//
//       }
//     } while (OverwrittenFlag == CAN_SET);
//
//     RtnValue = CAN_RTN_OK;
//   }
//
//   return RtnValue;
// }
//
//
//
//
// Can_RtnType Can_C0TrmByTxBuf(uint8 TxBufIdx, const Can_FrameType* pFrame)
// {
//     uint8 ucRetVal;
//     VU8* pTBSR;
//     VU8* pTBCR;
//     Can_FrameType* pTxBuffer;
//
//     pTBSR = &(RSCAN0TMSTS0);
//     pTBCR = &(RSCAN0TMC0);
//
//
//     if((pTBSR[TxBufIdx] & (VU8)0x01u) == CAN_TBTST_TRANSMITTING)
//     {
//       ucRetVal = CAN_RTN_ERR;
//     }
//
//     else
//     {
//
//       do
//       {
//         pTBSR[TxBufIdx] = CAN_CLR;
//       } while (pTBSR[TxBufIdx] != CAN_CLR);
//
//
//       pTxBuffer = (Can_FrameType*) &(RSCAN0TMID0);
//       pTxBuffer[TxBufIdx] = *pFrame;
//
//
//       pTBCR[TxBufIdx] = CAN_TBCR_TRM;
//
//       ucRetVal = CAN_RTN_OK;
//     }
//
//   return ucRetVal;
// }

//Can_RtnType Can_C1TrmByTxBuf(U8 TxBufIdx, const Can_FrameType* pFrame)
//{
//    uint8 tmp;
//    VU8* pTBSR;
//    Can_FrameType* pTxBuffer;
//    VU8* pTBCR;
//
//    pTBSR = &(RSCAN0TMSTS16);
//    pTBCR = &(RSCAN0TMC16);
//
//
//    if( (pTBSR[TxBufIdx] & (VU8)0x01u) == CAN_TBTST_TRANSMITTING )
//    {
//
//        tmp= CAN_RTN_ERR;
//    }
//    else
//    {
//
//    do
//    {
//        pTBSR[TxBufIdx] = CAN_CLR;
//    } while (pTBSR[TxBufIdx] != CAN_CLR);
//
//
//    pTxBuffer = (Can_FrameType*) &(RSCAN0TMID16);
//    pTxBuffer[TxBufIdx] = *pFrame;
//
//
//    pTBCR[TxBufIdx] = CAN_TBCR_TRM;
//
//
//      tmp=CAN_RTN_OK;
//    }
//
//  return tmp;
//}

