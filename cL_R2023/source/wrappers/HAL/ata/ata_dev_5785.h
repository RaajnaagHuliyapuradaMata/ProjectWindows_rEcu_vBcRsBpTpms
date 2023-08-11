

#ifndef ATA_DEV_8515_H
#define ATA_DEV_8515_H

#include "ata_dev_5785_X.h"

// RF Port
#define RF_PORT  PORTD
#define RF_PIN   PIND
#define RF_DDR   DDRD

#define RF_IRQ_CHNL      0
#define RF_NPWRON1_CHNL  5
#define RF_NRES_CHNL     7
#define RF_DAT_BUF_LEN   16
#define RF_RS_BUF_LEN    RF_DAT_BUF_LEN

struct rfstruct{
	uint8 rom;
	uint8 level;
	uint8 rssilvl;
	uint8 events[4];
  uint8 buffer[RF_DAT_BUF_LEN];
	uint8 rssibuf[RF_RS_BUF_LEN];
	uint8 mode;
	uint8 channel;
};

# define _select_ata5785()  do {                               \
								at_io_wr_chan(SPI_PORT, SPI_NSS_CHNL, 0);			 \
								at_io_setto_out(SPI_DDR, SPI_NSS_CHNL);				 \
								_delay_us(47);                                 \
							} while(FALSE)

# define _release_ata5785()  do {                              \
								_delay_us(36);                                 \
								at_io_wr_chan(SPI_PORT, SPI_NSS_CHNL, 1);			 \
								at_io_setto_in(SPI_DDR, SPI_NSS_CHNL);				 \
								_delay_us(17);                                 \
							} while(FALSE)

static void ataIni1st(void);
static void ataIniPwrOn(void);
static void ataInitSysRes(void);
static void ataIniWtResetEvent(void);
static void ataIniSeq1(void);
static void ataIniSeq2(void);
static void ataIniSeq3(void);
static void ataIniSeq4(void);
static void ataIniSeq5(void);
static void ataIniSeq6(void);
static void ataIniStartService(void);
static void ataInitialized(void);

static void  rf_ata5785_system_reset( void );
static uint8 rf_ata5785_read_version( void );
static void  rf_ata5785_set_mode( uint8 mode, uint8 channel );
static void  rf_ata5785_write_sram(const uint8 data[]);
static void  rf_ata5785_set_watchdog(const uint8 data[] );

static void release_ata5785(void);
static void select_ata5785(void);

//static uint8 rf_ata5785_read_rx_level( void );
//static uint8 rf_ata5785_read_rssi_level( void );
//static void rf_ata5785_write_tx_buf( uint8 buf[], uint8 len );
//static uint8 check_sensor_type(void);
//static uint8 rf_ata5785_read_SM_state( void );
//static uint8 rf_ata5785_read_error_code( void );
//static void rf_ata5785_init( void );
//static void rf_ata5785_init_demo( void );
#endif
