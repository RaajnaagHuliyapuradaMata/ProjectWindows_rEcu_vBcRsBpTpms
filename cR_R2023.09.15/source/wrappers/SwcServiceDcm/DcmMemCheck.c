#include "Std_Types.hpp"

#include "DcmMemCheck.hpp"
#include "crc.hpp"
#include "version.hpp"

extern boolean DcmVerifyApplicationMemory(void){
  tDescriptorBlock* pApplMetaData;
  uint32 ulCrc32Calculated;
  uint32 ulCrcRom;
  boolean bRetVal = FALSE;

  ulCrc32Calculated = Crc_CalculateCRC32((const uint8*)0x20100U, 0x57ae0U, CRC_INITIAL_VALUE32, TRUE);

  pApplMetaData = VERSION_GetPointerToDescriptorBlock(cAPP);
  ulCrcRom = *((uint32*)&(pApplMetaData->ucHash));

  if(ulCrcRom == ulCrc32Calculated)
  {
   bRetVal = TRUE;
  }

  return bRetVal;
}