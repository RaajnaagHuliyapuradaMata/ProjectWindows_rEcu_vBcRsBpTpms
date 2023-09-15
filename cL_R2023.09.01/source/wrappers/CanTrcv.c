#include "CanTrcv.hpp"
#include "types.hpp"
#include "gpioX.hpp"
#include "clocksX.hpp"

void TRCV_Standby(void){
  McalDio_vInitOutputOff(GPIO_EN_TJA);
  WaitHard(20);
  McalDio_vInitOutputOff(GPIO_STB_TJA);
  WaitHard(20);
}

void TRCV_Normal(void){
  GPIO_output_on(GPIO_STB_TJA);
  GPIO_output_on(GPIO_EN_TJA);
}

boolean TRCV_GetWakeupFlag(void){
  boolean bRetVal;
  if(GPIO_input_read(GPIO_ERR_TJA) == 0)
  {
   bRetVal = TRUE;
  }
  else{
   bRetVal = FALSE;
  }
  return bRetVal;
}

