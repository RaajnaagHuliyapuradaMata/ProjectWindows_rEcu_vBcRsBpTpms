

#include "ata_Rec.h"

#include "rlin30X.h"
#include "ata_dev_5785_X.h"
#include "gpioX.h"

#include "NvmManagerX.h"
#include "Os_ConfigInterrupts.h"

#include "iTpms_Interface.h"
#include "RdcManagerX.h"

#define cRFTelAK            0x00U
#define cRFTelAKLfResponse  0x01U
#define cRFTelLfResponse    0x03U
#define cRFTelStatus        0x83U
#define cRFTelStatusLearn   0xA3U
#define cRFTelApc           0xE7U
#define cRFTelStandstill    0x90U
#define cMaxNumberOfTgs     7U

// RST 02/2020: rf.level contains the real length of the received telegram. HufIf_CheckCrc8 compares this length
// to the expected length according to telegram type. If the received number of bytes is higher than the
// expected, because after the last byte of the telegram there were more bytes "in the air", the HufIf_CheckCrc8
// will fail, even if the telegram is valid.
// Why do we have this problem: in the original implementation of Ata_Rec.c there was a function appBuild8CRC
// that cared for this. This was optimized away together with function PutRB when I took the code over
// to Rivian project. Here we use HufIf_CheckCrc8 from the TPMS library.
// Solution: set PS_TelegramData->level to the expected number of bytes here, according to telegram type.
// PC 05/2020: adjusted the telegram lengths, to account that the sync bytes (0xFFF2) are automatically discarded
// and the final telegram will start from the package ID instead.
static const uint8 Rdc__U8_TgLengthList[cMaxNumberOfTgs][2] = { { cRFTelAK,           8 },
                                                                { cRFTelAKLfResponse, 8 },
                                                                { cRFTelLfResponse,   11 },
                                                                { cRFTelStatus,       10 },
                                                                { cRFTelStatusLearn,  10 },
                                                                { cRFTelApc,          8 },
                                                                //{ cRFTelStandstill,   8 }};
                                                                { cRFTelStandstill,   9 }};  // Rivian OIL#151

static uint8  ucATAinit = cDelay2StartUp;
static uint8  ucATAirq = cATA_NO_IRQ_PENDING;
//static uint8  ucDelayCnt=0;

static uint8 uiErrorCNT = 0;
//static uint8 ui8TelCt = 0;
static uint8 ucCrcPassedTel = 0;
static uint8 ucCrcFailedTel = 0;

extern struct rfstruct rf;

void CheckRfState (void)
{
  switch (ucATAinit)
  {
    case cDelay2StartUp:                    //RST Todo: obsolete? ata init is started when the rest is already running, incl OS. So why additional delay?
//    ucDelayCnt++;
//
//    if( ucDelayCnt >= c50msCnt )
//    {
//      ucATAinit = cRfdStartInit;
//    }
//    break;

    case cRfdStartInit:
    FastPWR_3Pin4_ATA(0);
    GPIO_ChipSelectAta(0);

    rf_ata5785_StartInitSM();
    (void) rf_ata5785_InitSM();
    ucATAinit = cRfdWtIniFini;
    break;

    case cRfdWtIniFini :
    if (rf_ata5785_InitSM() == 1)
    {
      ucATAinit = cRfdProcess;
    }
    break;

    default:

    break;
  }
}

uint8 GetAtaState(void)
{
  return ucATAinit;
}

uint8 GetAtaIrqFlag(void)
{
  return ucATAirq;
}

void SetAtaIrqFlag(void)
{
  ucATAirq = cATA_IRQ_PENDING;
}

void ClearAtaIrqFlag(void)
{
  ucATAirq = cATA_NO_IRQ_PENDING;
}

//static uint8 GetAtaTelegramLength(void)
//{
//  uint8 i = 0;
//  uint8 ucRetVal = 0;
//
//
//  // PC 05/2020: changed the location of the package ID in the rf.buffer array to 0
//  // instead of 3, to account the fact that the sync bytes are not placed in the
//  // buffer.
//  while ((i < cMaxNumberOfTgs) && (rf.buffer[0] != Rdc__U8_TgLengthList[i][0]))
//  {
//    i++;
//  }
//
//
//  if (i < cMaxNumberOfTgs)
//  {
//    ucRetVal = Rdc__U8_TgLengthList[i][1];
//  }
//
//  return ucRetVal;
//}

static uint8 GetAtaTelegramLength(uint8 ucTelType)
{
  uint8 i = 0;
  uint8 ucRetVal = RB_DATA_LEN;

  while ((i < cMaxNumberOfTgs) && (ucTelType != Rdc__U8_TgLengthList[i][0]))
  {
    i++;
  }

  if (i < cMaxNumberOfTgs)
  {
    ucRetVal = Rdc__U8_TgLengthList[i][1];
  }

  return ucRetVal;
}

static uint8 appBuild8CRC(const uint8 *pui8Buffer, uint8 ui8MessageLen, uint8 ui8BitsInFirstByte, uint8 ui8Polynom, uint8 ui8CrcStartValue)
{

  uint8 ui8CRC = ui8CrcStartValue;

  do
  {
    uint8 ui8BitNumber = 0x00U;
    uint8 byteContent = (uint8)pui8Buffer[0] << (uint8) 8 - ui8BitsInFirstByte;

    if( 1U < ui8MessageLen )
    {
      byteContent |= ( pui8Buffer[1] >> ( ui8BitsInFirstByte ) );
      ui8BitNumber = 8U;
    }
    else
    {
      ui8BitNumber = ui8BitsInFirstByte;
    }

    ui8CRC ^= byteContent;
    do
    {
      if( (uint8)0 != ( ( 0x80U ) & ( ui8CRC ) ) )
      {
        ui8CRC = (uint8) ( ( ui8CRC << 1U ) ^ ( ui8Polynom ) );
      }
      else
      {
        ui8CRC = (uint8) ( ( ui8CRC << 1U ) );
      }
      ui8BitNumber--;
    }while((uint8)0 != ui8BitNumber );

    pui8Buffer++;
    if (ui8MessageLen > 0)
    {
      ui8MessageLen--;
    }
  }while((uint8)0 != ui8MessageLen );

  return ( ui8CRC );
}

//RST Debug Rx
//uint8  ushSystemFehler = 0;
//uint8 ushRxCounter_TgLenOk= 0 ;
//uint8 ucRxCounter_CrcFailed = 0;
//extern void Debug_GetAtaRecCounters(uint8* Ct1_Systemfehler, uint8* Ct2_TgLen, uint8* Ct3_Crc)
//{
////  *Ct1_Systemfehler = ushSystemFehler;
////  *Ct2_TgLen = ushRxCounter_TgLenOk;
//  *Ct3_Crc = ucRxCounter_CrcFailed;
//}

#include "RdcStandstillDebugX.h"

void CheckAtaRec(void)
{
  uint8 ui8MessageLen;
  uint8 ui8Polynom = 0x2F;
  uint8 ui8CrcStartValue = 0xAA;
  uint8 ui8BitsInFirstByte = 8U;
  uint8 ucTelegramType;
  #ifdef DEBUG_LOST_TELEGRAMS
  uint32 ulId;
  #endif

  #ifdef RFChipTest_Instrument
  static uint8 ui8ReIniAfterXTels = 0;
  #endif

  csig0_4ATAinit();
  rf_ata5785_get_events( rf.events );

  if (((rf.events[3]&rf.channel) == rf.channel) && (((rf.events[1]&0x07) == 0x07) || ((rf.events[1]&0x70) == 0x70))
  #ifdef RFChipTest_Instrument
  && !(ui8ReIniAfterXTels++ == 30)
  #endif
  )  // cfg = activated one && OK events on path B or A
  {
    // PC 05/2020: Added this clearing of the buffer
	  // There were situations when the RF Receiver picked up a telegram with rf.level=0, so no bytes were placed inside
	  // the rf.buffer array. However, since the rf.level is manually adjusted, when the telegram with a default rf.level = 0
	  // was received, it was overwritten to another value and the previous values stored in rf.buffer were used. In this case,
	  // duplicate telegrams were being sent. Now, a telegram with all 0x00 will not pass the filters in the BSW. A different
	  // solution would be to not adjust the rf.level if it is 0 at the start.
    // Note: this was caused by the change from RST 02/2020: GetAtaTelegramLength() => rf.level

    ////////////////uint8 U8_Counter;

    ////////////////for(U8_Counter = 0; U8_Counter < RF_DAT_BUF_LEN; U8_Counter++)
    ////////////////{
    ////////////////  rf.buffer[U8_Counter] = 0x00U;                                            Ändern 1
    ////////////////}

    rf_ata5785_read_rx_buf( rf.buffer, &(rf.level) );
    rf_ata5785_read_rssi_buf( rf.rssibuf, &(rf.rssilvl) );

    //ui8TelCt++;
    //////////////
    //////////////rf.level = GetAtaTelegramLength();  //RST 02/2020
    //////////////                                                                          Ändern 2
    //////////////Rdc_ProcessTelegram(&rf);

    if(rf.level > (uint8)3)
    {

      ucTelegramType = rf.buffer[0];
      ui8MessageLen = GetAtaTelegramLength(ucTelegramType);

      if (appBuild8CRC(rf.buffer, ui8MessageLen - (uint8)1, ui8BitsInFirstByte, ui8Polynom, ui8CrcStartValue) == rf.buffer[ui8MessageLen - (uint8)1])
      {
        Rdc_ProcessTelegram(&rf);
      }
      else
      {

        #ifdef WORKAROUND_RIVIAN_STANDSTILL_TELEGRAM_LENGTH

        if (ucTelegramType == cRFTelStandstill)
        {
          if (appBuild8CRC(rf.buffer, ui8MessageLen - (uint8)2, ui8BitsInFirstByte, ui8Polynom, ui8CrcStartValue) == rf.buffer[ui8MessageLen - (uint8)2])
          {
            Rdc_ProcessTelegram(&rf);
          }
          else
          {
            //ucRxCounter_CrcFailed++; //RST Debug Rx Crc failed!
            #ifdef DEBUG_LOST_TELEGRAMS
            ulId = (rf.buffer[1]<<24) + (rf.buffer[2]<<16) + (rf.buffer[3]<<8) + rf.buffer[4];
            LTGDEBUG_SetEvent(rf.buffer[0], ulId, cTGFILTER_CRC);
            #endif
          }
        }
        else
        {
          //ucRxCounter_CrcFailed++; //RST Debug Rx Crc failed!
          #ifdef DEBUG_LOST_TELEGRAMS
          ulId = (rf.buffer[1]<<24) + (rf.buffer[2]<<16) + (rf.buffer[3]<<8) + rf.buffer[4];
          LTGDEBUG_SetEvent(rf.buffer[0], ulId, cTGFILTER_CRC);
          #endif
        }

        #else
          #ifdef DEBUG_LOST_TELEGRAMS
          ulId = (rf.buffer[1]<<24) + (rf.buffer[2]<<16) + (rf.buffer[3]<<8) + rf.buffer[4];
          LTGDEBUG_SetEvent(rf.buffer[0], ulId, cTGFILTER_CRC);
          #endif
        #endif

      }
    }
    else
    {
      //ushRxCounter_TgLenOk++; //RST Debug Rx TG length failed!
      #ifdef DEBUG_LOST_TELEGRAMS
      ulId = 0;
      LTGDEBUG_SetEvent(rf.buffer[0], ulId, cTGFILTER_LENGTH);
      #endif
    }

    SetServNPath(rf.channel);
  }

  else
  {
    //ushSystemFehler++;  //RST Debug Rx Systemfehler

    if ((rf.events[0] & 0x80)     // sys error ?
    #ifdef  RFChipTest_Instrument
    || (0 < ui8ReIniAfterXTels)   // emulated syserror
    #endif
    )
    {
      #ifdef RFChipTest_Instrument
      ui8ReIniAfterXTels = 0;
      #endif
      if(uiErrorCNT<0xFF)
      {
        uiErrorCNT++;
      }
      ATA_ReInitAfterError();
    }
    else
    {
      SetServNPath(rf.channel);
    }
  }
}

uint8 ATA_MeasureNoiseRssiLevel(void)
{
  uint8 ucRssiNulllevel;

  if ((ucATAinit == cRfdProcess) && (ucATAirq == cATA_NO_IRQ_PENDING))
  {
    Os_Disable_CAT2ISR_TelRec();
    csig0_enable();
    rf_ata5785_start_rssi_measurement(rf.channel);
    ucRssiNulllevel = rf_ata5785_get_rssi_level();

    if ((GPIO_GetAtaIrqPortPinLevel() == 0) || (GPIO_GetAtaIrqPendingFlag() == 1))
    {
      CheckAtaRec();
      ucRssiNulllevel = 0xff;
      Os_Clear_CAT2ISR_TelRec();
    }
    else
    {
      SetServNPath(rf.channel);
    }
    Os_Enable_CAT2ISR_TelRec();
  }

  else
  {
    ucRssiNulllevel = 0xff;
  }

  return ucRssiNulllevel;
}

extern void ATA_ReInitAfterError(void)
{
  ucATAinit = cDelay2StartUp;
}

uint8 ATA_GetCrcPassedTelCounter(void)
{
  return ucCrcPassedTel;

}

uint8 ATA_GetCrcFailedTelCounter(void)
{
  return ucCrcFailedTel;
}