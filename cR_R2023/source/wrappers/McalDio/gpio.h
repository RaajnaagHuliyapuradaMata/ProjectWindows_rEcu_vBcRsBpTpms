#ifndef _GPIO_H
#define _GPIO_H

#include "gpioX.h"

enum AGPIO_Name{
      AGPIO_AP0
   ,  AGPIO_AP1
   ,  AGPIO_AP2
   ,  AGPIO_AP3
   ,  AGPIO_AP4
   ,  AGPIO_AP5
   ,  AGPIO_AP6
   ,  AGPIO_AP7
   ,  AGPIO_AP8
   ,  AGPIO_AP9
};

struct AGPIO_pin{
                  enum AGPIO_Name Name;
                  uint16  PinNumber;
   volatile       uint16* APM_Reg;
   volatile const uint16* APPR_Reg;
   volatile       uint16* APIBC_Reg;
   volatile       uint16* AP_Reg;
};

void  PWR_ATA_P10_14_on    (void);
void  PWR_ATA_P10_14_off   (void);
void  PWR_ATA              (uint8 ucSet);
void  SPI_CLK              (uint8 ucSet);
void  SPI_MOSI             (uint8 ucSet);
void  AMcalDio_vInitOutput (enum AGPIO_Name PortPin);
void  ClearKplAPort        (void);
void  APort0               (uint8 ucSet);
void  APort1               (uint8 ucSet);
void  APort2               (uint8 ucSet);
void  APort3               (uint8 ucSet);
void  APort4               (uint8 ucSet);
void  APort5               (uint8 ucSet);
void  APort6               (uint8 ucSet);
void  APort7               (uint8 ucSet);
uint8 ucGetRF_TP3          (void);
uint8 ucGetRF_TP2          (void);
uint8 ucGetRF_TP1          (void);
uint8 ucGetRF_TP0          (void);
void  Set8Bit2APort        (uint8);
void  LCD_E                (uint8);
void  LCD_RS               (uint8);
void  LCD_RW               (uint8 ucSet);
#endif
