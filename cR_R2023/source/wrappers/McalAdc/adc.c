#include "adc.h"
#include "device.h"

volatile uint16 ushADCvalueChannel2 = 0;
static uint16 uiKl30_Value4Average[cUBAT_AVG_ARRAY_ELEMENTS] = {0xff, 0xff, 0xff, 0xff};   // Buffer for average calculation

void ADC_Channel2_GetValue(void)
{
  ushADCvalueChannel2 = (uint16)ADCA0DIR02 & 0xffffu;
}

static uint8 ADC_CalcKl30Voltage(void)
{
  static uint8  ucKl30_KazCnt = 0;       // Counter for average calculation -> 0=starting value, 1..3 = pointer to buffer entries 0..2
  uint16 ushTemp;
  uint32 ulTemp;
  uint8  ucRetVal = 0xff;
  uint8  i;

  if (ushADCvalueChannel2 != 0)
  {

    //ushTemp = (((ushADCvalueChannel2 >> 3) - 3) * 100);
    //ushTemp = (ushTemp / 176);
    //ushTemp = ushTemp + (ushTemp / 10);
    //ushTemp = ushTemp + 8;
    //ushTemp = ushTemp - ((ushTemp >> 4) - 3);

    //ulTemp = ushADCvalueChannel2 * 8;
    //ulTemp += 50;
    //
    //
    //ulTemp += 990;
    //ulTemp /= 106;

    ulTemp = ushADCvalueChannel2 * 8;
    ulTemp += 50;
    //ulTemp /= 100;
    //ulTemp *= 100;
    ulTemp += 790;
    ulTemp /= 106;
    ushTemp = (uint16)ulTemp;

    if (ucKl30_KazCnt == 0)
    {

      for (i=0; i<cUBAT_AVG_ARRAY_ELEMENTS; i++)
      {
        uiKl30_Value4Average[i] = ushTemp;
      }

      ucKl30_KazCnt = 1;
    }
    else
    {

      uiKl30_Value4Average[ucKl30_KazCnt - 1] = ushTemp;
      ucKl30_KazCnt++;
      if (ucKl30_KazCnt == cUBAT_AVG_ARRAY_ELEMENTS + 1)
      {
        ucKl30_KazCnt = 1;
      }
    }
  }

  ushADCvalueChannel2 = 0;

  return ucRetVal;
}

void ADC_StartConversionSG1(void){
  ADC_CalcKl30Voltage();
  ADCA0SGSTCR1 = 1u;
}

uint8 ADC_GetKl30Voltage(void)
{
  uint8  ucRetVal = 0xffu;
  uint8  i;
  uint16 ushTemp = 0;

  for (i=0; i<cUBAT_AVG_ARRAY_ELEMENTS; i++)
  {
    ushTemp += uiKl30_Value4Average[i];
  }

  ushTemp /= cUBAT_AVG_ARRAY_ELEMENTS;

  if (ushTemp < 0xffu)
  {
    ucRetVal = (uint8) ushTemp;
  }

  return ucRetVal;
}
