/******************************************************************************/
/* File   : CfgMcalDio.c                                                      */
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

#include "Types_McalDio.hpp"
#include "uC_Dio.hpp"
#include "CfgMcalDio.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

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
CONST(Type_McalDio_stPin, MCALDIO_CONFIG_DATA) CfgMcalDio_castListInfoPins[] = {
      {GPIO_LED1      , 3u,  &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_LCD_E     , 6u,  &PMC8 , &PM8 , &PPR8,  &PIBC8,  &P8}
   ,  {GPIO_LCD_RW    , 5u,  &PMC8 , &PM8 , &PPR8,  &PIBC8,  &P8}
   ,  {GPIO_LCD_RS    , 4u,  &PMC8 , &PM8 , &PPR8,  &PIBC8,  &P8}
   ,  {GPIO_RES_OUT   , 0u,  &PMC0 , &PM0 , &PPR0,  &PIBC0,  &P0}
   ,  {GPIO_DIN       , 1u,  &PMC8 , &PM8 , &PPR8,  &PIBC8,  &P8}
   ,  {GPIO_SELDP0    , 4u,  &PMC0 , &PM0 , &PPR0,  &PIBC0,  &P0}
   ,  {GPIO_SELDP1    , 5u,  &PMC0 , &PM0 , &PPR0,  &PIBC0,  &P0}
   ,  {GPIO_SELDP2    , 6u,  &PMC0 , &PM0 , &PPR0,  &PIBC0,  &P0}
   ,  {GPIO_INTP      , 9u,  &PMC0 , &PM0 , &PPR0,  &PIBC0,  &P0}
   ,  {GPIO_EN_TJA    , 1u,  &PMC0 , &PM0 , &PPR0,  &PIBC0,  &P0}
   ,  {GPIO_ERR_TJA   , 2u,  &PMC0 , &PM0 , &PPR0,  &PIBC0,  &P0}
   ,  {GPIO_STB_TJA   , 3u,  &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_CS_ATA    , 5u,  &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_SPI_MOSI  , 6u,  &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_SPI_CLK   , 7u,  &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_SPI_MISO  , 8u,  &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_CHK_FREQ  , 9u,  &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_PWR_ATA   , 14u, &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_PWR_B1ATA , 13u, &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_PWR_B2ATA , 12u, &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_IRQ_ATA   , 11u, &PMC10, &PM10, &PPR10, &PIBC10, &P10}
   ,  {GPIO_TP0       , 0u , &PMC9,  &PM9 , &PPR9,  &PIBC9,  &P9}
   ,  {GPIO_TP1       , 1u , &PMC9,  &PM9 , &PPR9,  &PIBC9,  &P9}
   ,  {GPIO_TP2       , 2u , &PMC9,  &PM9 , &PPR9,  &PIBC9,  &P9}
   ,  {GPIO_TP3       , 3u , &PMC9,  &PM9 , &PPR9,  &PIBC9,  &P9}
};

const Type_CfgMcalDio_stInfoPin ACfgMcalDio_castListPins[] = {
      {CfgMcalDio_ePinName_AP0, 0u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP1, 1u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP2, 2u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP3, 3u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP4, 4u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP5, 5u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP6, 6u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP7, 7u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP8, 8u, &APM0, &APPR0, &APIBC0, &AP0}
   ,  {CfgMcalDio_ePinName_AP9, 9u, &APM0, &APPR0, &APIBC0, &AP0}
};

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
