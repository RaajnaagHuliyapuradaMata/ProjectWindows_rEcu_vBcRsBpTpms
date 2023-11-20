#include "Std_Types.hpp"

#include "FeeFblBlockInterface.hpp"
#include "rba_DiagLib_MemUtils.hpp"

static const uint8 aucDefaultKey[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   ,     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};

uint8 FEEFBL_GetProgAttemptsCounter(uint8* ucData)
{
  uint8 U8_Counter;

  for(U8_Counter=0; U8_Counter<(kEepSizeProgAttemptsCounter); U8_Counter++)
  {
   ucData[U8_Counter] = 0x00;
  }

  ApplFblNvReadProgAttemptsCounter(&ucData[0]);

  return (kEepSizeProgAttemptsCounter);
}

uint8 FEEFBL_GetMaxProgAttemptsCounter(uint8* ucData)
{
  uint8 U8_Counter;

  for(U8_Counter=0; U8_Counter<(kEepSizeMaxProgAttemptsCounter); U8_Counter++)
  {
   ucData[U8_Counter] = 0x00;
  }

  ApplFblNvReadMaxProgAttemptsCounter(&ucData[0]);

  return (kEepSizeMaxProgAttemptsCounter);
}

uint8 FEEFBL_GetProgrammingDate(uint8* ucData, uint8 ucAppFbl)
{
  uint8 U8_Counter;

  for(U8_Counter=0; U8_Counter<(kEepSizeProgrammingDate); U8_Counter++)
  {
   ucData[U8_Counter] = 0x00;
  }

  ApplFblNvReadProgrammingDate(ucAppFbl, &ucData[0]);

  return (kEepSizeProgrammingDate);
}

uint8 FEEFBL_GetTesterSerialNumber(uint8* ucData, uint8 ucAppFbl)
{
  uint8 U8_Counter;

  for(U8_Counter=0; U8_Counter<(kEepSizeTesterSerialNumber); U8_Counter++)
  {
   ucData[U8_Counter] = 0x00;
  }

  ApplFblNvReadTesterSerialNumber(ucAppFbl, &ucData[0]);

  return (kEepSizeTesterSerialNumber);
}

 uint8 FEEFBL_GetUdsAppKey(uint8* ucData)
 {
  uint8 ucCounter;
  boolean bKeyInitialized = FALSE;

  ApplFblNvReadSecKey_UDSAPPKEY(&ucData[0]);

  for(ucCounter = 0; ucCounter < kEepSizeSecKey_UDSAPPKEY; ucCounter++)
  {
   if(ucData[ucCounter] != 0xff)
   {
      bKeyInitialized = TRUE;
   }
  }

  if(bKeyInitialized == FALSE)
  {
    rba_DiagLib_MemUtils_MemCpy(ucData, aucDefaultKey, kEepSizeSecKey_UDSAPPKEY);
  }

  return (kEepSizeSecKey_UDSAPPKEY);
 }

 uint8 FEEFBL_GetUdsBootKey(uint8* ucData)
 {
  uint8 ucCounter;
  boolean bKeyInitialized = FALSE;

  ApplFblNvReadSecKey_UDSBOOTKEY(&ucData[0]);

  for(ucCounter = 0; ucCounter < kEepSizeSecKey_UDSBOOTKEY; ucCounter++)
  {
   if(ucData[ucCounter] != 0xff)
   {
      bKeyInitialized = TRUE;
   }
  }

  if(bKeyInitialized == FALSE)
  {
    rba_DiagLib_MemUtils_MemCpy(ucData, aucDefaultKey, kEepSizeSecKey_UDSBOOTKEY);
  }

  return (kEepSizeSecKey_UDSBOOTKEY);
 }

 uint8 FEEFBL_GetUdsMsgKey(uint8* ucData)
 {
  uint8 ucCounter;
  boolean bKeyInitialized = FALSE;

  ApplFblNvReadSecKey_UDSMSGKEY(&ucData[0]);

  for(ucCounter = 0; ucCounter < kEepSizeSecKey_UDSMSGKEY; ucCounter++)
  {
   if(ucData[ucCounter] != 0xff)
   {
      bKeyInitialized = TRUE;
   }
  }

  if(bKeyInitialized == FALSE)
  {
    rba_DiagLib_MemUtils_MemCpy(ucData, aucDefaultKey, kEepSizeSecKey_UDSMSGKEY);
  }

  return (kEepSizeSecKey_UDSMSGKEY);
 }

 uint8 FEEFBL_PutUdsAppKey(const uint8* ucData)
 {
  uint8 ucRetVal;
  ucRetVal = ApplFblNvWriteSecKey_UDSAPPKEY(&ucData[0]);
  return ucRetVal;
 }

 uint8 FEEFBL_PutUdsBootKey(const uint8* ucData)
 {
  uint8 ucRetVal;
  ucRetVal = ApplFblNvWriteSecKey_UDSBOOTKEY(&ucData[0]);
  return ucRetVal;
 }

 uint8 FEEFBL_PutUdsMsgKey(const uint8* ucData)
 {
  uint8 ucRetVal;
  ucRetVal = ApplFblNvWriteSecKey_UDSMSGKEY(&ucData[0]);
  return ucRetVal;
 }

 uint8 FEEFBL_PutApplicationSignature(uint8* ucData)
 {
  uint8 ucRetVal;
  ucRetVal = ApplFblNvWriteApplicationSignature(0, &ucData[0]);
  return ucRetVal;
 }

