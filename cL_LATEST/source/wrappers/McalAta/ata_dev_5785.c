

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

// Pre-Load temp value with T=25°C (val=25+50=75)
static uint8 rf_tempMeas_cfg[] = {
   0x02,     // addr_h
   0xC3,     // addr_l
   0x01,     // length
   0x4B      // tempMeas
};

// set systemConfig; disable SFIFI interrupts (IRQs for Buffer underrun/overrun)
static uint8 rf_sysConf_rd[] = {
   0x02,     // addr_h
   0xE5,     // addr_l
   0x01,     // length
   //0x08      // systemConfig: SFIFI interrupt disable
  0x0C      // systemConfig: SFIFI and DFIFI interrupts disable
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  LNAEN: Low Noise Amplifier Enable @as  CR_0850_000_007
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//uint8_t rf_feen_cfg[] = {
//    0x01,     // addr_h
//    0x01,     // addr_l
//    0x01,     // length
//    0x08      // FEEN: Bit3=1 LNAEN=1
//};

void rf_ata5785_StartInitSM(void){
  fp2IniState = ataIni1st;
  ClearAtaIrqFlag();
}

// rf_ata5785_InitSM purpose:
// ata 5785 receiver chip initialization via spi and control signals:
// set port pins:  PB5:   RF NSS       out high (PB5)  (P0_11)    (P10_5)
//                 PD3:   PWRON        out low  (PB4)  (P11_11)   (P10_14)
//                 PB2:   SPI MOSI     out ---  (PB2)  (P0_12)    (P10_6)
//                 PB3:   SPI MISO     in  ---  (PB3)  (P0_13)    (P10_8)
//                 PB1:   SPI SCK      out ---  (PB1)  (P0_14)    (P10_7)
//                 PD0:   RF IRQ       in  low  (PB6)  (P11_9)    (P10_11)
// implementation as fine SM called in defined time cycles
// timing: max cycle runtime < 5msec, complete init scenario app. 500msec
// returns > 0 if initialization is sucessfully finished

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
    //InitSPIExtRec ();
    //csig0_init();
   csig0_4ATAinit();

   if(ui8SrvNPath == rf.channel)  // reactivation
   {
        //MFA2: CR_0850_000_002
        rf.mode = 0x12; // 7.4.8 System Mode: No RF_CAL + No VCO_TUNE necessary + IDLEMode=(XTO)+OperationMode=RXmode
        //rf.mode = 0x02; // 7.4.8 System Mode: No RF_CAL + No VCO_TUNE necessary + IDLEMode=(RC)+OperationMode=RXmode
   }
   else{
        //MFA2: CR_0850_000_002
        rf.mode = 0xB2;  // 7.4.8 System Mode: RF_CAL + VCO_TUNE  + IDLEMode=(XTO)+OperationMode=RXmode
        //rf.mode = 0xA2;  // 7.4.8 System Mode: RF_CAL + VCO_TUNE + IDLEMode =(RC)+OperationMode=RXmode
        rf.channel = ui8SrvNPath;
   }

    rf_ata5785_set_mode(rf.mode, rf.channel );
    //DisableSPI();
   csig0_disable();
}

void rf_ata5785_get_events( uint8 buf[] )
{
   // set NSS for ata5785
   select_ata5785();

   buf[0] = active_xfer_spi( 0x04 );	// events.system
   buf[1] = active_xfer_spi( 0x00 );	// events.events
   buf[2] = active_xfer_spi( 0x00 );	// events.power
   buf[3] = active_xfer_spi( 0x00 );	// events.config

   // release NSS for ata5785
   release_ata5785();

   return;
}

void rf_ata5785_start_rssi_measurement(uint8 channel)
{
   // set NSS for ata5785
   select_ata5785();

   active_xfer_spi( 0x1B );	// events.system
   active_xfer_spi( channel );	    // events.events

   // release NSS for ata5785
   release_ata5785();

   return;
}

uint8 rf_ata5785_get_rssi_level(void)
{
  uint8 rssav;
  uint8 rsspk;

  // set NSS for ata5785
   select_ata5785();

   active_xfer_spi( 0x1C );	// events.system
   active_xfer_spi( 0x00 );	// events.events
  rssav = active_xfer_spi( 0x00 );	// bytes
   rsspk = active_xfer_spi( 0x00 );	// bytes
  rsspk = rsspk;
  //(void)active_xfer_spi( 0x00 );	// bytes

   // release NSS for ata5785
   release_ata5785();

   return rssav;
}

void rf_ata5785_read_rx_buf( uint8 buf[], uint8 *len )
{
uint8 i;

   // set NSS for ata5785
   select_ata5785();
   active_xfer_spi( 0x01 );	// events.system
   active_xfer_spi( 0x00 );	// events.events
   *len = active_xfer_spi( 0x00 );	// bytes
   // release NSS for ata5785
   release_ata5785();

   select_ata5785();
   active_xfer_spi( 0x06 );	// events.system
   active_xfer_spi( *len );	// events.events
   active_xfer_spi( 0x00 );	// dummy

   for(i=0; i<*len; i++)
   {
      buf[i] = active_xfer_spi( 0x00 );
   }
   // release NSS for ata5785
   release_ata5785();

   return;
}

void rf_ata5785_read_rssi_buf( uint8 buf[], uint8 *len )
{
  uint8 i;

   // set NSS for ata5785
   select_ata5785();
   active_xfer_spi( 0x03 );	// events.system
   active_xfer_spi( 0x00 );	// events.events
   *len = active_xfer_spi( 0x00 );	// bytes
   // release NSS for ata5785
   release_ata5785();

   // set NSS for ata5785
   select_ata5785();
   active_xfer_spi( 0x05 );	// events.system
   active_xfer_spi( *len );    // events.events
   active_xfer_spi( 0x00 );	// dummy
   for(i=0; i<*len; i++)
   {
   	buf[i] = active_xfer_spi( 0x00 );
   }

   // release NSS for ata5785
   release_ata5785();
}

void rf_ata5785_off_mode(void)
{
   //Send OFF command
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
  // set watchdog
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
  // set temperature measurement value to 25°C
  rf_ata5785_write_sram(rf_tempMeas_cfg);
  // set systemConfig: disable SFIFO interrupts
  rf_ata5785_write_sram(rf_sysConf_rd);

  rf_ata5785_write_sram(rf_disableClock_cfg);
  rf_ata5785_write_sram(rf_setClockDivider_cfg);
  rf_ata5785_write_sram(rf_reenableClock_cfg);

  // set idle mode
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

   // set NSS for ata5785
   select_ata5785();

   active_xfer_spi( 0x13 );	// events.system
   active_xfer_spi( 0x00 );	// events.events
   rtn = active_xfer_spi( 0x00 );	// ROM version
   active_xfer_spi( 0x00 );	// Flash version high
   active_xfer_spi( 0x00 );	// flash version low
   active_xfer_spi( 0x00 );	// customer version

   // release NSS for ata5785
   release_ata5785();

   return rtn;
}

static void rf_ata5785_set_mode( uint8 mode, uint8 channel )
{
   // set NSS for ata5785
   select_ata5785();

   active_xfer_spi( 0x0D );	// events.system
   active_xfer_spi( mode );	// events.events
   active_xfer_spi( channel );	// dummy

   // release NSS for ata5785
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

    // write to SRAM or register:
    // TX = <0x07>, <length>, <addr high>, <addr low>, <data>, ...
    // RX = <ev1>,  <ev2>,    <dum>,       <dum>,      <0x00>
#define SRAM_BUFFER_SIZE 32

    addr.ui = (uint16) data[0];
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
   // set NSS for ata5785
   select_ata5785();

   active_xfer_spi( 0x10 );	// events.system
   active_xfer_spi( data[0] );	    // events.events

   // release NSS for ata5785
   release_ata5785();

   return;
}

static void rf_ata5785_system_reset(void)
{
   //uint8 ucMISOdata[4];

  select_ata5785();
  //ucMISOdata[0]=active_xfer_spi( 0x15 );	//  now irq low level events.system
   //ucMISOdata[1]=active_xfer_spi( 0x00 );  // events.events
  //ucMISOdata[3]=0x01;
  (void)active_xfer_spi( 0x15 );	//  now irq low level events.system
  (void)active_xfer_spi( 0x00 );  // events.events
   release_ata5785();

   return;
}

//  static uint8 rf_ata5785_read_error_code(void)
//  {
//      uint8 rtn;
//      select_ata5785();
//
//      active_xfer_spi( 0x08 );	// events.system
//      active_xfer_spi( 0x01 );	// events.events
//      active_xfer_spi( 0x02 );	// hi-byte adr
//      active_xfer_spi( 0xF4 );	// lo-byte adr
//      rtn = active_xfer_spi( 0x00 );	// error code
//
//      release_ata5785();
//
//      return rtn;
//  }
//
//  static uint8 rf_ata5785_read_SM_state(void)
//  {
//      uint8 rtn;
//      select_ata5785();
//
//      active_xfer_spi( 0x08 );	// events.system
//      active_xfer_spi( 0x01 );	// events.events
//      active_xfer_spi( 0x02 );	// hi-byte adr
//      active_xfer_spi( 0xF5 );	// lo-byte adr
//      rtn = active_xfer_spi( 0x00 );	// error code
//
//      release_ata5785();
//
//      return rtn;
//  }
//
//
//  static uint8 check_sensor_type(void)
//  {
//  	uint16 tcount;
//    uint8 tmp=0;
//
//  	// check for 433MHz RX mode
//  	rf.mode = 0xA2;
//  	rf.channel = 0x83;
//  	//InitSPIExtRec ();
//          //csig0_init();
//  	csig0_4ATAinit();
//  	rf_ata5785_set_mode( rf.mode, rf.channel );
//  	//DisableSPI();
//  	csig0_disable();
//
//    tcount = 0;
//  	do
//  	{
//  	  //WaitHard(cWAIT_10_MS);
//  	  WaitHard(10000);
//  	  //if(ucGetRF_IRQ_ExtRec () == 0) break;
//  	  if(ucGetRF_IRQ_ATA() == 0) break;
//  	}while(tcount++ < 500);
//
//          //InitSPIExtRec ();
//  	//csig0_init();
//  	csig0_4ATAinit();
//  	rf_ata5785_get_events( rf.events );
//  	//WaitHard(cWAIT_1_MSEC);
//  	WaitHard(1000);
//  	// set idle mode
//  	rf.mode = 0x00;
//  	rf.channel = 0x00;
//  	rf_ata5785_set_mode( rf.mode, rf.channel );
//  	//WaitHard(cWAIT_2_MSEC);
//  	WaitHard(2000);
//  	//DisableSPI();
//  	csig0_disable();
//  	if(((rf.events[3]&0x83) == 0x83) && ((rf.events[1]&0x07) == 0x07))
//     {
//       tmp=1;
//     }
//     else
//     {
//  	// check for 315MHz RX mode
//  	rf.mode = 0xA2;
//  	rf.channel = 0x84;
//  	//InitSPIExtRec();
//  	//csig0_init();
//  	csig0_4ATAinit();
//  	rf_ata5785_set_mode( rf.mode, rf.channel );
//  	//DisableSPI();
//  	csig0_disable();
//  	tcount = 0;
//  	do
//  	{
//  		//WaitHard(cWAIT_10_MS);
//  		WaitHard(10000);
//  		//if(ucGetRF_IRQ_ExtRec () == 0) break;
//  		if(ucGetRF_IRQ_ATA() == 0) break;
//  	}while(tcount++ < 500);
//  	//InitSPIExtRec();
//  	//csig0_init();
//  	csig0_4ATAinit();
//  	rf_ata5785_get_events( rf.events );
//  	//WaitHard(cWAIT_1_MSEC);
//  	WaitHard(1000);
//  	// set idle mode
//  	rf.mode = 0x00;
//  	rf.channel = 0x00;
//  	rf_ata5785_set_mode( rf.mode, rf.channel );
//  	//WaitHard(cWAIT_2_MSEC);
//  	WaitHard(2000);
//  	//DisableSPI();
//  	csig0_disable();
//       if(((rf.events[3]&0x84) == 0x84) && ((rf.events[1]&0x07) == 0x07))
//       {
//          tmp=2;
//       }
//
//     }
//  	// tmp=0 --> set default polling mode
//  	return (tmp);
//  }
//
//
//
//  static uint8 rf_ata5785_read_rx_level(void)
//  {
//  uint8 rtn;
//
//  	// set NSS for ata5785
//  	select_ata5785();
//
//  	active_xfer_spi( 0x01 );	// events.system
//  	active_xfer_spi( 0x00 );	// events.events
//  	rtn = active_xfer_spi( 0x00 );	// bytes
//
//  	// release NSS for ata5785
//  	release_ata5785();
//
//  	return rtn;
//  }
//
//
//
//  static uint8 rf_ata5785_read_rssi_level(void)
//  {
//  uint8 rtn;
//
//  	// set NSS for ata5785
//  	select_ata5785();
//
//  	active_xfer_spi( 0x03 );	// events.system
//  	active_xfer_spi( 0x00 );	// events.events
//  	rtn = active_xfer_spi( 0x00 );	// bytes
//
//  	// release NSS for ata5785
//  	release_ata5785();
//
//  	return rtn;
//  }
//
//
//
//  static void rf_ata5785_write_tx_buf( uint8 buf[], uint8 len )
//  {
//  	uint8 i;
//
//  	// set NSS for ata5785
//  	select_ata5785();
//
//  	active_xfer_spi( 0x06 );	// events.system
//  	active_xfer_spi( len );	    // events.events
//  	active_xfer_spi( 0x00 );	// dummy
//
//  	for(i=0; i<len; i++)
//  	{
//  		active_xfer_spi( buf[i] );
//  	}
//
//  	// release NSS for ata5785
//  	release_ata5785();
//
//  	return;
//  }

//
//void rf_ata5785_init(void)
//{
//    uint8 i;
//    uint16 ushTO = 60000;
//
//    //SetPWRON_ExtRec (0);
//    //PWR_ATA(0);
//    //PWR_3Pin4_ATA(0);
//    FastPWR_3Pin4_ATA(0);
//    //WaitHard(cWAIT_10_MS);
//    WaitHard(10000);
//    //Setup rf structure
//    rf.rom = 0;
//    rf.level = 0;
//    rf.rssilvl = 0;
//    rf.mode = 0;
//    rf.channel = 0;
//    rf.events[0] = 0;
//    rf.events[1] = 0;
//    rf.events[2] = 0;
//    rf.events[3] = 0;
//    // RF_DAT_BUF_LEN=24// alt error: rf.buffer hat 24 Bytes -> for(i=0; i<32; i++)
//    for(i=0; i<RF_DAT_BUF_LEN; i++)
//    {
//        rf.buffer[i] = 0;
//        rf.rssibuf[i] = 0;
//    }
//
//    //DisableSPI ();
//    //InitSPIExtRec ();
//    csig0_4ATAinit();
//    //csig0_disable();
//
//    //SetPWRON_ExtRec (1);
//    //PWR_ATA(1);
//    //PWR_3Pin4_ATA(1);
//    FastPWR_3Pin4_ATA(1);
//    // wait until device initialized
//    //WaitHard(cWAIT_1_MSEC);
//    WaitHard(1000);
//
//
//
//		rf_ata5785_system_reset();
//
//    //while(ucGetRF_IRQ_ExtRec () && ushTO--);   //IRQ = 0 --> event active
//
//#ifdef PIN56_PORT10_11_IRQ
//    //while(ucPort10Pin11IntSet == 0 && ushTO--);
//    while((GPIO_GetP11IrqPending() == cATA_IRQ_NOT_PENDING) && ushTO--);
//#else
//    while(GPIO_input_read(GPIO_IRQ_ATA) && ushTO--);   //IRQ = 0 --> event active ATA4MFA
//#endif
//    WaitHard(1000);
//    //ucPort10Pin11IntSet=0;
//    GPIO_SetP11IrqPending(cATA_IRQ_NOT_PENDING);
//
//
//    //csig0_4ATAinit();
//
//
//    rf_ata5785_get_events( rf.events );
//    rf.rom = rf_ata5785_read_version();
//
//    // configure device
//    rf_ata5785_write_sram(rf_idCtrl_cfg);
//    rf_ata5785_write_sram(rf_events_cfg);
//    // set watchdog
//    rf_ata5785_set_watchdog(rf_watchdog_cfg);
//    rf_ata5785_write_sram(rf_dbgsw_cfg);
//
//    //rf_ata5785_write_sram(rf_feen_cfg);
//    rf_ata5785_write_sram(rf_PORTB_cfg);
//    rf_ata5785_write_sram(rf_DDRB_cfg);
//    rf_ata5785_write_sram(rf_PORTC_cfg);
//    rf_ata5785_write_sram(rf_DDRC_cfg);
//    rf_ata5785_write_sram(rf_PCMSK0_cfg);
//    rf_ata5785_write_sram(rf_PCMSK1_cfg);
//    rf_ata5785_write_sram(rf_PCICR_cfg);
//    rf_ata5785_write_sram(rf_MCUCR_cfg);
//    rf_ata5785_write_sram(rf_temperatureCalibration_cfg);
//    rf_ata5785_write_sram(rf_trxCalibConfiguration_cfg);
//    rf_ata5785_write_sram(rf_sleepModeConfig_cfg);
//    rf_ata5785_write_sram(rf_frcCalibrationConfiguration_cfg);
//    rf_ata5785_write_sram(rf_pollConfig_cfg);
//    rf_ata5785_write_sram(rf_calib_srcRes_cfg);
//    rf_ata5785_write_sram(rf_calib_srcCorVal_cfg);
//    rf_ata5785_write_sram(rf_sramService3_cfg);
//    rf_ata5785_write_sram(rf_sramService4_cfg);
//    rf_ata5785_write_sram(rf_gapMode_cfg);
//    rf_ata5785_write_sram(rf_eomConfig_cfg);
//    // set temperature measurement value to 25°C
//    rf_ata5785_write_sram(rf_tempMeas_cfg);
//    // set systemConfig: disable SFIFO interrupts
//    rf_ata5785_write_sram(rf_sysConf_rd);
//
//    // CR_0850_000_001 Atmel 19.05.2015 JB set CKL_OUT to PortB0
//    // CR_0850_000_010 for DVI/EMV test without CKL_OUT necessary!
//    //rf_ata5785_write_sram(rf_disableClock_cfg);
//    //rf_ata5785_write_sram(rf_setClockDivider_cfg);
//    //rf_ata5785_write_sram(rf_reenableClock_cfg);
//
//
//
//    //rf.rom = rf_ata5785_read_version();
//    //rf_ata5785_get_events( rf.events );
//
//    // set idle mode
//    rf.mode = 0x00;
//    rf.channel = 0x00;
//    rf_ata5785_set_mode( rf.mode, rf.channel );
//    //WaitHard(cWAIT_5_MSEC);
//    WaitHard(5000);
//    rf_ata5785_get_events( rf.events );
//
//
//    rf_ata5785_write_sram(rf_feen_cfg);
//
//    // Fkt im ATMEL EVAL Board! set polling mode
//
//
//
//    //rf.channel = 0x83;
//    //rf_ata5785_start_rssi_measurement( rf.channel );
//    //ucRssiNulllevel = rf_ata5785_get_rssi_level();
//
//    //DisableSPI ();
//    csig0_disable();
//}

//void rf_ata5785_init_demo(void)
//{
//    uint8 i;
//    uint16 ushTO = 60000;
//
//    //SetPWRON_ExtRec (0);
//    //PWR_ATA(0);
//    //PWR_3Pin4_ATA(0);
//    FastPWR_3Pin4_ATA(0);
//    //WaitHard(cWAIT_10_MS);
//    WaitHard(10000);
//    //Setup rf structure
//    rf.rom = 0;
//    rf.level = 0;
//    rf.rssilvl = 0;
//    rf.mode = 0;
//    rf.channel = 0;
//    rf.events[0] = 0;
//    rf.events[1] = 0;
//    rf.events[2] = 0;
//    rf.events[3] = 0;
//    for(i=0; i<32; i++)
//    {
//        rf.buffer[i] = 0;
//        rf.rssibuf[i] = 0;
//    }
//
//    //DisableSPI ();
//    //InitSPIExtRec ();
//    csig0_4ATAinit();
//    //csig0_disable();
//
//    //SetPWRON_ExtRec (1);
//    //PWR_ATA(1);
//    PWR_3Pin4_ATA(1);
//    FastPWR_3Pin4_ATA(1);
//    // wait until device initialized
//    //WaitHard(cWAIT_1_MSEC);
//    WaitHard(1000);
//
//
//
//		//rf_ata5785_system_reset();
//
//    //while(ucGetRF_IRQ_ExtRec () && ushTO--);   //IRQ = 0 --> event active
//    //while(GPIO_input_read(GPIO_IRQ_ATA) && ushTO--);   //IRQ = 0 --> event active ATA4MFA
//#ifdef PORT_IRQ
//    //while(ucPort10Pin11IntSet == 0 && ushTO--);
//    while((GPIO_GetP11IrqPending() == 0) && (ushTO--));
//#else
//    //while(GPIO_input_read(GPIO_IRQ_ATA) && ushTO--);   //IRQ = 0 --> event active ATA4MFA
//    while(GPIO_input_read(GPIO_IRQ_ATA) && ushTO--);   //IRQ = 0 --> event active ATA4MFA
//#endif
//    WaitHard(1000);
//    //ucPort10Pin11IntSet=0;
//    GPIO_SetP11IrqPending(cATA_IRQ_NOT_PENDING);
//
//
//    //csig0_4ATAinit();
//
//
//    //rf_ata5785_get_events( rf.events );
//    //rf.rom = rf_ata5785_read_version();
//
// // configure device
//	rf_ata5785_write_sram(rf_sramService3_cfg);
//	rf_ata5785_write_sram(rf_sramService4_cfg);
//	rf_ata5785_write_sram(rf_idCtrl_cfg);
//	rf_ata5785_write_sram(rf_sleepModeConfig_cfg);
//	rf_ata5785_write_sram(rf_events_cfg);
//	rf_ata5785_write_sram(rf_dbgsw_cfg);
//	rf_ata5785_write_sram(rf_PORTB_cfg);
//	rf_ata5785_write_sram(rf_PORTC_cfg);
//	rf_ata5785_write_sram(rf_DDRB_cfg);
//	rf_ata5785_write_sram(rf_DDRC_cfg);
//	rf_ata5785_write_sram(rf_PCICR_cfg);
//	rf_ata5785_write_sram(rf_PCMSK0_cfg);
//	rf_ata5785_write_sram(rf_PCMSK1_cfg);
//	rf_ata5785_write_sram(rf_MCUCR_cfg);
//	rf_ata5785_write_sram(rf_temperatureCalibration_cfg);
//	rf_ata5785_write_sram(rf_trxCalibConfiguration_cfg);
//	rf_ata5785_write_sram(rf_pollConfig_cfg);
//	rf_ata5785_write_sram(rf_calib_srcRes_cfg);
//	rf_ata5785_write_sram(rf_calib_srcCorVal_cfg);
//	rf_ata5785_write_sram(rf_frcCalibrationConfiguration_cfg);
//	rf_ata5785_write_sram(rf_gapMode_cfg);
//	rf_ata5785_write_sram(rf_eomConfig_cfg);
//	// set watchdog
//	rf_ata5785_set_watchdog(rf_watchdog_cfg);
//    // set temperature measurement value to 25°C
//   rf_ata5785_write_sram(rf_tempMeas_cfg);
//    // set systemConfig: disable SFIFO interrupts
//   rf_ata5785_write_sram(rf_sysConf_rd);
//
//
//    rf.rom = rf_ata5785_read_version();
//    rf_ata5785_get_events( rf.events );
//
//    // set idle mode
//    rf.mode = 0x00;
//    rf.channel = 0x00;
//    rf_ata5785_set_mode( rf.mode, rf.channel );
//    //WaitHard(cWAIT_5_MSEC);
//    WaitHard(5000);
//    rf_ata5785_get_events( rf.events );
//
//    // Fkt im ATMEL EVAL Board! set polling mode
//    rf.mode = 0x23;
//    rf.channel = 0x00;
//    rf_ata5785_set_mode( rf.mode, rf.channel );
//    //_delay_ms(5);
//    WaitHard(5000);
//    rf_ata5785_get_events( rf.events );
//
//    //DisableSPI ();
//    csig0_disable();
//}

