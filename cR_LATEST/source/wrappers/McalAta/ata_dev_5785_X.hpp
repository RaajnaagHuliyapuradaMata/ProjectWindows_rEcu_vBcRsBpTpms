
#ifndef ATA_DEV_5785_X_H
#define ATA_DEV_5785_X_H

#include "types.hpp"

#define cATA_INIT                 0
#define cATA_READY_FOR_TELEGRAMS  1
#define cATA_NOISE_VALUE_IS_VALID 2

extern void rf_ata5785_StartInitSM(void);
extern uint8 rf_ata5785_InitSM(void);

extern void rf_ata5785_get_events(uint8 buf[]);
extern void rf_ata5785_start_rssi_measurement(uint8 channel);
extern uint8 rf_ata5785_get_rssi_level(void);
extern void rf_ata5785_read_rx_buf( uint8 buf[], uint8 *len );
extern void rf_ata5785_read_rssi_buf( uint8 buf[], uint8 *len );
extern void rf_ata5785_off_mode(void);
extern void SetServNPath( uint8 ui8SrvNPath );

#endif
