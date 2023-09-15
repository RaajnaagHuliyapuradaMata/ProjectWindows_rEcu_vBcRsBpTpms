

#include "Crc.hpp"

#define CRC_START_SEC_CODE
#include "Crc_MemMap.hpp"

void Crc_GetVersionInfo(Std_VersionInfoType * const VersionInfo)
{
   if(VersionInfo != NULL_PTR)
   {

         VersionInfo->vendorID         = CRC_VENDOR_ID;
         VersionInfo->moduleID         = CRC_MODULE_ID;
         VersionInfo->sw_major_version = CRC_SW_MAJOR_VERSION;
         VersionInfo->sw_minor_version = CRC_SW_MINOR_VERSION;
         VersionInfo->sw_patch_version = CRC_SW_PATCH_VERSION;
   }
}

uint16 Crc_CalculateCRC16(const uint8* Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall)
{
   uint32  index;
   uint16  result = Crc_StartValue16;
   uint16  crcTemp;
   if(Crc_DataPtr != NULL_PTR)
   {
        crcTemp = (Crc_IsFirstCall != FALSE) ? ((uint16)CRC_INITIAL_VALUE16) : (Crc_StartValue16^ CRC_XOR_VALUE16);

        for(index = 0U; index < Crc_Length; ++index)
        {

            crcTemp ^= ((uint16)Crc_DataPtr[index]) << CRC_16_JUNKREST;

            crcTemp =  (crcTemp << (CRC_JUNK)) ^ CRC_16_Tbl[(crcTemp >> CRC_16_JUNKREST) & CRC_TABLEMASK];
        }
        result = crcTemp ^ CRC_XOR_VALUE16;
   }

    return (result);
}

uint32 Crc_CalculateCRC32(const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall)
{
   uint32  index;
   uint32  result = Crc_StartValue32;
   uint32  crcTemp;
   if(Crc_DataPtr != NULL_PTR)
   {
        crcTemp = (Crc_IsFirstCall != FALSE) ? ((uint32)CRC_INITIAL_VALUE32) : (Crc_StartValue32^ CRC_XOR_VALUE32);

        for(index = 0U; index < Crc_Length; ++index)
        {

            crcTemp ^= ((uint32)Crc_DataPtr[index]) ;

            crcTemp =  (crcTemp >> (CRC_JUNK)) ^ CRC_32_REV_Tbl[(crcTemp ) & CRC_TABLEMASK];
        }
        result = crcTemp ^ CRC_XOR_VALUE32;
   }

    return (result);
}

uint32 Crc_CalculateCRC32P4(const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall)
{
   uint32  index;
   uint32  result = Crc_StartValue32;
   uint32  crcTemp;
   if(Crc_DataPtr != NULL_PTR)
   {
        crcTemp = (Crc_IsFirstCall != FALSE) ? ((uint32)CRC_INITIAL_VALUE32) : (Crc_StartValue32^ CRC_XOR_VALUE32P4);

        for(index = 0U; index < Crc_Length; ++index)
        {

            crcTemp ^= ((uint32)Crc_DataPtr[index]) ;

            crcTemp =  (crcTemp >> (CRC_JUNK)) ^ CRC_32P4_REV_Tbl[(crcTemp ) & CRC_TABLEMASK];
        }
        result = crcTemp ^ CRC_XOR_VALUE32P4;
   }

    return (result);
}

#define CRC_STOP_SEC_CODE
#include "Crc_MemMap.hpp"

