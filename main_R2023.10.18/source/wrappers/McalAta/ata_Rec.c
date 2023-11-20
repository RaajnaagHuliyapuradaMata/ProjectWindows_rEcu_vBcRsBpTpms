#include "Std_Types.hpp"

#include "ata_Rec.hpp"
#include "rlin30X.hpp"
#include "ata_dev_5785_X.hpp"
#include "gpioX.hpp"
#include "NvmManagerX.hpp"
#include "Os_ConfigInterrupts.hpp"
#include "iTpms_Interface.hpp"
#include "RdcManagerX.hpp"

#define cRFTelAK            0x00U
#define cRFTelAKLfResponse  0x01U
#define cRFTelLfResponse    0x03U
#define cRFTelStatus        0x83U
#define cRFTelStatusLearn   0xA3U
#define cRFTelApc           0xE7U
#define cRFTelStandstill    0x90U
#define cMaxNumberOfTgs     7U

static const uint8 Rdc__U8_TgLengthList[cMaxNumberOfTgs][2] = {
      {cRFTelAK,            8}
   ,  {cRFTelAKLfResponse,  8}
   ,  {cRFTelLfResponse,   11}
   ,  {cRFTelStatus,       10}
   ,  {cRFTelStatusLearn,  10}
   ,  {cRFTelApc,           8}
   ,  {cRFTelStandstill,    1}
};

static uint8 ucATAinit = cDelay2StartUp;
static uint8 ucATAirq = cATA_NO_IRQ_PENDING;
static uint8 uiErrorCNT = 0;
static uint8 ucCrcPassedTel = 0;
static uint8 ucCrcFailedTel = 0;

extern struct rfstruct rf;

void CheckRfState(void){
   switch(
      ucATAinit
   ){
      case cDelay2StartUp:
      case cRfdStartInit:
         FastPWR_3Pin4_ATA(0);
         GPIO_ChipSelectAta(0);
         rf_ata5785_StartInitSM();
         (void) rf_ata5785_InitSM();
         ucATAinit = cRfdWtIniFini;
         break;

      case cRfdWtIniFini :
         if(
               rf_ata5785_InitSM()
            == 1
         ){
            ucATAinit = cRfdProcess;
         }
         break;

      default:
      break;
   }
}

uint8 GetAtaState(void){
  return ucATAinit;
}

uint8 GetAtaIrqFlag(void){
  return ucATAirq;
}

void SetAtaIrqFlag(void){
  ucATAirq = cATA_IRQ_PENDING;
}

void ClearAtaIrqFlag(void){
  ucATAirq = cATA_NO_IRQ_PENDING;
}

static uint8 GetAtaTelegramLength(
   uint8 ucTelType
){
   uint8 i = 0;
   uint8 ucRetVal = RB_DATA_LEN;
   while(
         (i < cMaxNumberOfTgs)
      && (ucTelType != Rdc__U8_TgLengthList[i][0])
   ){
      i++;
   }
   if(
         i
      <  cMaxNumberOfTgs
   ){
      ucRetVal = Rdc__U8_TgLengthList[i][1];
   }
   return ucRetVal;
}

static uint8 appBuild8CRC(
      const uint8* pui8Buffer
   ,        uint8  ui8MessageLen
   ,        uint8  ui8BitsInFirstByte
   ,        uint8  ui8Polynom
   ,        uint8  ui8CrcStartValue
){
   uint8 ui8CRC = ui8CrcStartValue;
   do{
      uint8 ui8BitNumber = 0x00U;
      uint8 byteContent = (uint8)pui8Buffer[0] << (uint8) 8 - ui8BitsInFirstByte;
      if(
            1U
         <  ui8MessageLen
      ){
         byteContent |= ( pui8Buffer[1] >> ( ui8BitsInFirstByte ) );
         ui8BitNumber = 8U;
      }
      else{
         ui8BitNumber = ui8BitsInFirstByte;
      }
      ui8CRC ^= byteContent;
      do{
         if(
               (uint8)0
            != (
                     0x80U
                  &  ui8CRC
               )
         ){
            ui8CRC = (uint8) ( ( ui8CRC << 1U ) ^ ( ui8Polynom ) );
         }
         else{
            ui8CRC = (uint8) ( ( ui8CRC << 1U ) );
         }
         ui8BitNumber--;
      }while(
            (uint8)0
         != ui8BitNumber
      );
      pui8Buffer++;
      if(ui8MessageLen > 0){
         ui8MessageLen--;
      }
   }while(
         (uint8)0
      != ui8MessageLen
   );
   return ui8CRC;
}

void CheckAtaRec(void){
   uint8 ui8MessageLen;
   uint8 ui8Polynom         = 0x2F;
   uint8 ui8CrcStartValue   = 0xAA;
   uint8 ui8BitsInFirstByte = 8U;
   uint8 ucTelegramType;
   csig0_4ATAinit();
   rf_ata5785_get_events(
      rf.events
   );
   if(
         (
               (
                     rf.events[3]
                  &  rf.channel
               )
            == rf.channel
         )
      && (
               ((rf.events[1] & 0x07) == 0x07)
            || ((rf.events[1] & 0x70) == 0x70)
         )
   ){
      rf_ata5785_read_rx_buf(
            rf.buffer
         ,  &(rf.level)
      );
      rf_ata5785_read_rssi_buf(
            rf.rssibuf
         ,  &(rf.rssilvl)
      );
      if(
            rf.level
         >  (uint8)3
      ){
         ucTelegramType = rf.buffer[0];
         ui8MessageLen = GetAtaTelegramLength(ucTelegramType);
         if(
               appBuild8CRC(
                     rf.buffer
                  ,  ui8MessageLen - (uint8)1
                  ,  ui8BitsInFirstByte
                  ,  ui8Polynom
                  ,  ui8CrcStartValue
               )
            == rf.buffer[ui8MessageLen - (uint8)1]
         ){
            Rdc_ProcessTelegram(
               &rf
            );
         }
         else{
         }
      }
      else{
      }
      SetServNPath(rf.channel);
   }
   else{
      if(
            rf.events[0]
         &  0x80
      ){
         if(
               uiErrorCNT
            <  0xFF
         ){
            uiErrorCNT++;
         }
         ATA_ReInitAfterError();
      }
      else{
         SetServNPath(rf.channel);
      }
   }
}

uint8 ATA_MeasureNoiseRssiLevel(void){
  uint8 ucRssiNulllevel;

  if((ucATAinit == cRfdProcess) && (ucATAirq == cATA_NO_IRQ_PENDING))
  {
    Os_Disable_CAT2ISR_TelRec();
   csig0_enable();
    rf_ata5785_start_rssi_measurement(rf.channel);
   ucRssiNulllevel = rf_ata5785_get_rssi_level();

   if((GPIO_GetAtaIrqPortPinLevel() == 0) || (GPIO_GetAtaIrqPendingFlag() == 1))
   {
      CheckAtaRec();
      ucRssiNulllevel = 0xff;
      Os_Clear_CAT2ISR_TelRec();
   }
   else{
      SetServNPath(rf.channel);
   }
    Os_Enable_CAT2ISR_TelRec();
  }

  else{
   ucRssiNulllevel = 0xff;
  }

  return ucRssiNulllevel;
}

extern void ATA_ReInitAfterError(void){
  ucATAinit = cDelay2StartUp;
}

uint8 ATA_GetCrcPassedTelCounter(void){
  return ucCrcPassedTel;
}

uint8 ATA_GetCrcFailedTelCounter(void){
  return ucCrcFailedTel;
}
