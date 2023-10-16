#include "Std_Types.hpp"

#include "device.hpp"
#include "ata_dev_5785.hpp"
#include "ata5785_sram.hpp"
#include "ata_Rec_X.hpp"
#include "gpioX.hpp"
#include "rlin30X.hpp"
#include "clocksX.hpp"
#include "Os_ConfigInterrupts.hpp"

struct rfstruct rf;
static void (*fp2IniState) (void) = ataIni1st;

static uint8 rf_tempMeas_cfg[] = {
   0x02,
   0xC3,
   0x01,
   0x4B
};

static uint8 rf_sysConf_rd[] = {
   0x02,
   0xE5,
   0x01,
   0x0C
};

void rf_ata5785_StartInitSM(void){
  fp2IniState = ataIni1st;
  ClearAtaIrqFlag();
}

uint8 rf_ata5785_InitSM(void){
  fp2IniState ();
  if(fp2IniState == ataInitialized)
  {
    return 1;
  }
  else{
    return 0;
  }
}

void SetServNPath( uint8 ui8SrvNPath )
{
   csig0_4ATAinit();
   if(ui8SrvNPath == rf.channel)  // reactivation
   {
        rf.mode = 0x12; // 7.4.8 System Mode: No RF_CAL + No VCO_TUNE necessary + IDLEMode=(XTO)+OperationMode=RXmode
   }
   else{
        rf.mode = 0xB2;  // 7.4.8 System Mode: RF_CAL + VCO_TUNE  + IDLEMode=(XTO)+OperationMode=RXmode
        rf.channel = ui8SrvNPath;
   }
    rf_ata5785_set_mode(rf.mode, rf.channel );
   csig0_disable();
}

void rf_ata5785_get_events( uint8 buf[] )
{
   select_ata5785();
   buf[0] = active_xfer_spi( 0x04 );	// events.system
   buf[1] = active_xfer_spi( 0x00 );	// events.events
   buf[2] = active_xfer_spi( 0x00 );	// events.power
   buf[3] = active_xfer_spi( 0x00 );	// events.config
   release_ata5785();
   return;
}

void rf_ata5785_start_rssi_measurement(uint8 channel)
{
   select_ata5785();
   active_xfer_spi( 0x1B );	// events.system
   active_xfer_spi( channel );	    // events.events
   release_ata5785();
   return;
}

uint8 rf_ata5785_get_rssi_level(void)
{
  uint8 rssav;
  uint8 rsspk;
   select_ata5785();
   active_xfer_spi( 0x1C );	// events.system
   active_xfer_spi( 0x00 );	// events.events
  rssav = active_xfer_spi( 0x00 );	// bytes
   rsspk = active_xfer_spi( 0x00 );	// bytes
  rsspk = rsspk;
   release_ata5785();
   return rssav;
}

void rf_ata5785_read_rx_buf( uint8 buf[], uint8 *len )
{
uint8 i;
   select_ata5785();
   active_xfer_spi( 0x01 );	// events.system
   active_xfer_spi( 0x00 );	// events.events
   *len = active_xfer_spi( 0x00 );	// bytes
   release_ata5785();
   select_ata5785();
   active_xfer_spi( 0x06 );	// events.system
   active_xfer_spi( *len );	// events.events
   active_xfer_spi( 0x00 );	// dummy
   for(i=0; i<*len; i++)
   {
      buf[i] = active_xfer_spi( 0x00 );
   }
   release_ata5785();
   return;
}

void rf_ata5785_read_rssi_buf( uint8 buf[], uint8 *len )
{
  uint8 i;
   select_ata5785();
   active_xfer_spi( 0x03 );	// events.system
   active_xfer_spi( 0x00 );	// events.events
   *len = active_xfer_spi( 0x00 );	// bytes
   release_ata5785();
   select_ata5785();
   active_xfer_spi( 0x05 );	// events.system
   active_xfer_spi( *len );    // events.events
   active_xfer_spi( 0x00 );	// dummy
   for(i=0; i<*len; i++)
   {
   	buf[i] = active_xfer_spi( 0x00 );
   }
   release_ata5785();
}

void rf_ata5785_off_mode(void)
{
  csig0_4ATAinit();
  select_ata5785();
   (void)active_xfer_spi( 0x18 );	// events.system
   (void)active_xfer_spi( 0x00 );	// events.events
   release_ata5785();
  csig0_disable();
  FastPWR_3Pin4_ATA(0);
}

static void select_ata5785(void){
    GPIO_ChipSelectAta(1);
    WaitHard(47);
}

static void release_ata5785(void){
    WaitHard(36);
    GPIO_ChipSelectAta(0);
    WaitHard(17);
}

static void ataIni1st(void){
  uint8 i;
  Os_Disable_CAT2ISR_TelRec();
  FastPWR_3Pin4_ATA(0);
  rf.rom = 0; // init data struct used for receiver chip communication
  rf.level = 0;
  rf.rssilvl = 0;
  rf.mode = 0;
  rf.channel = 0;
  rf.events[0] = 0;
  rf.events[1] = 0;
  rf.events[2] = 0;
  rf.events[3] = 0;
  for(i=((uint8) 0); i<RF_DAT_BUF_LEN; i++)
  {
    rf.buffer[i] = (uint8) 0;
    rf.rssibuf[i] = (uint8) 0;
  }
  fp2IniState = ataIniPwrOn ;
}

static void ataIniPwrOn(void){
  csig0_4ATAinit();
   FastPWR_3Pin4_ATA(1);
  fp2IniState = ataInitSysRes ;
}

static void ataInitSysRes(void){
  ClearAtaIrqFlag();
  rf_ata5785_system_reset();
  Os_Enable_CAT2ISR_TelRec();
  fp2IniState = ataIniWtResetEvent;
}

static void ataIniWtResetEvent(void){
  static uint8 tOCtIn50msec = (uint8) 3;
  if(0 < tOCtIn50msec)
  {
    tOCtIn50msec--;
   if(GetAtaIrqFlag() == cATA_IRQ_PENDING)
   {
      ClearAtaIrqFlag();
      tOCtIn50msec = (uint8) 3;
      fp2IniState = ataIniSeq1;
      rf_ata5785_get_events( rf.events );
      rf.rom = rf_ata5785_read_version();
      rf_ata5785_write_sram(rf_idCtrl_cfg);
   }
  }
  else{
    tOCtIn50msec = (uint8) 3;
    fp2IniState = ataIni1st;
   csig0_disable();
  }
}

static void ataIniSeq1(void){
  rf_ata5785_write_sram(rf_events_cfg);
  rf_ata5785_set_watchdog(rf_watchdog_cfg);
  rf_ata5785_write_sram(rf_dbgsw_cfg);
  rf_ata5785_write_sram(rf_PORTB_cfg);
  rf_ata5785_write_sram(rf_DDRB_cfg);
  rf_ata5785_write_sram(rf_PORTC_cfg);
  rf_ata5785_write_sram(rf_DDRC_cfg);
  rf_ata5785_write_sram(rf_PCMSK0_cfg);
  rf_ata5785_write_sram(rf_PCMSK1_cfg);
  rf_ata5785_write_sram(rf_PCICR_cfg);
  rf_ata5785_write_sram(rf_MCUCR_cfg);
  fp2IniState = ataIniSeq2;
}

static void ataIniSeq2(void){
  rf_ata5785_write_sram(rf_temperatureCalibration_cfg);
  rf_ata5785_write_sram(rf_trxCalibConfiguration_cfg);
  rf_ata5785_write_sram(rf_sleepModeConfig_cfg);
  rf_ata5785_write_sram(rf_frcCalibrationConfiguration_cfg);
  rf_ata5785_write_sram(rf_pollConfig_cfg);
  rf_ata5785_write_sram(rf_calib_srcRes_cfg);
  rf_ata5785_write_sram(rf_calib_srcCorVal_cfg);
  fp2IniState = ataIniSeq3;
}

static void ataIniSeq3(void){
  rf_ata5785_write_sram(rf_sramService3_cfg);
  fp2IniState = ataIniSeq4;
}

static void ataIniSeq4(void){
  rf_ata5785_write_sram(rf_sramService4_cfg);
  fp2IniState = ataIniSeq5;
}

static void ataIniSeq5(void){
  rf_ata5785_write_sram(rf_gapMode_cfg);
  rf_ata5785_write_sram(rf_eomConfig_cfg);
  rf_ata5785_write_sram(rf_tempMeas_cfg);
  rf_ata5785_write_sram(rf_sysConf_rd);
  rf_ata5785_write_sram(rf_disableClock_cfg);
  rf_ata5785_write_sram(rf_setClockDivider_cfg);
  rf_ata5785_write_sram(rf_reenableClock_cfg);
  rf.mode = 0x00;
  rf.channel = 0x00;
  rf_ata5785_set_mode( rf.mode, rf.channel );
  fp2IniState = ataIniSeq6;
}

static void ataIniSeq6(void){
  rf_ata5785_get_events( rf.events );
  csig0_disable();
  fp2IniState = ataIniStartService;
}

static void ataIniStartService(void){
  if(GPIO_GetFrequencySetting() == cFREQUENCY_433)
  {
    SetServNPath(0x83);
  }
  else{
    SetServNPath(0x84);
  }
  Os_Enable_CAT2ISR_TelRec();
  fp2IniState = ataInitialized;
}

static void ataInitialized(void){
}

static uint8 rf_ata5785_read_version(void)
{
   uint8 rtn;
   select_ata5785();
   active_xfer_spi( 0x13 );	// events.system
   active_xfer_spi( 0x00 );	// events.events
   rtn = active_xfer_spi( 0x00 );	// ROM version
   active_xfer_spi( 0x00 );	// Flash version high
   active_xfer_spi( 0x00 );	// flash version low
   active_xfer_spi( 0x00 );	// customer version
   release_ata5785();
   return rtn;
}

static void rf_ata5785_set_mode( uint8 mode, uint8 channel )
{
   select_ata5785();
   active_xfer_spi( 0x0D );	// events.system
   active_xfer_spi( mode );	// events.events
   active_xfer_spi( channel );	// dummy
   release_ata5785();
   return;
}

static void rf_ata5785_write_sram(const uint8 data[])
{
   uint8 i;
   uint8 length;
   uint8 offset;
   union
   {
        uint16   ui;
        uint8  uc[2];
   }addr;

#define SRAM_BUFFER_SIZE 32

   addr.ui = (uint16)data[0];
    addr.ui<<= 8;
    addr.ui += (uint16) data[1];
    length = data[2];
    offset = 3;
    do
   {
        if(length <= SRAM_BUFFER_SIZE)
        {
            select_ata5785();
            active_xfer_spi( 0x07 );
            active_xfer_spi( length );      // length
            active_xfer_spi(  (uint8) (addr.ui>>8)  );  // addr high
            active_xfer_spi( (uint8) addr.ui );  // addr low
            for(i=0; i<length; i++) active_xfer_spi( data[i+offset] );
            release_ata5785();
            length = 0;
        }
        else{
            select_ata5785();
            active_xfer_spi( 0x07 );
            active_xfer_spi( SRAM_BUFFER_SIZE );     // length
            active_xfer_spi( (uint8) (addr.ui>>8) );           // addr high
            active_xfer_spi( (uint8) addr.ui );           // addr low
            for(i=0; i<SRAM_BUFFER_SIZE; i++) active_xfer_spi( data[i+offset] );
            release_ata5785();
            addr.ui += SRAM_BUFFER_SIZE;
            length -= SRAM_BUFFER_SIZE;
            offset += SRAM_BUFFER_SIZE;
        }
   }while(length > 0);
    return;
}

static void rf_ata5785_set_watchdog(const uint8 data[] )
{
   select_ata5785();
   active_xfer_spi( 0x10 );	// events.system
   active_xfer_spi( data[0] );	    // events.events
   release_ata5785();
   return;
}

static void rf_ata5785_system_reset(void)
{
  select_ata5785();
  (void)active_xfer_spi( 0x15 );	//  now irq low level events.system
  (void)active_xfer_spi( 0x00 );  // events.events
   release_ata5785();
   return;
}

