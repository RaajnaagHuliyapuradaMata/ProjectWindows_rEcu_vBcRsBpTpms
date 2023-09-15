

#ifndef CRC_PRV_RH850_HW_H
#define CRC_PRV_RH850_HW_H

#include "Crc_Cfg.hpp"

#define CRC_GENFUNC_CCITT16   (1U)  // 16 bit CCITT CRC polynomial is used

#include "Os.hpp"
#if(OS_NUM_CORES == 1U)
#define Crc_GetCoreId()        (0U)
#else
#define Crc_GetCoreId()       GetCoreID()
#endif
#if(1U == CRC_HW_RH850_R1X)

// Bitmask for CRC variant    : DCRBnPOL = DCRBnCTL[0]
#define CRC_HW_8B_ETHERNET32    (0x04U)    // 8 bit input width, 32-bit Ethernet CRC polynomial
#define CRC_HW_8B_CCITT16       (0x05U)    // 8 bit input width, 16-bit CCITT CRC polynomial
#define CRC_HW_16B_CCITT16      (0x11U)    // 16 bit input width, 16-bit CCITT CRC polynomial
#define CRC_HW_DCRBNPOL_BITMASK (0x01U)
#endif
#if(1U == CRC_HW_RH850_P1X)

#define CRC_HW_8B_ETHERNET32    (0x20U)    // 8 bit input width, 32-bit Ethernet CRC polynomial
#define CRC_HW_8B_CCITT16       (0x21U)    // 8 bit input width, 16-bit CCITT CRC polynomial
#define CRC_HW_16B_CCITT16      (0x11U)    // 16 bit input width, 16-bit CCITT CRC polynomial
#define CRC_HW_8B_SAE8          (0x22U)    // 8 bit input width, 8-bit SAE J1850 CRC polynomial
#define CRC_HW_8B_2F8           (0x23U)    // 8 bit input width, 8-bit 0x2F CRC polynomial
#define CRC_HW_DCRBNPOL_BITMASK (0x03U)
#endif

#if((CRC_HW_RH850_R1X == 1U) || (CRC_HW_RH850_P1X == 1U))

#define CRC_CFG(channel)  (CrcRegs[(channel)]->crcctl)
#define CRC_INP(channel)  (CrcRegs[(channel)]->crcin)
#define CRC_OUT(channel)  (CrcRegs[(channel)]->crcout)

typedef struct{
   const uint8* crc8bitDataPtr;
   const uint16* crc16bitDataPtr;
   uint32 crcLength;
}Crc_DataInfoType;

CRC_INLINE uint32 Crc_Lok_CalcCRC_RH850_Hw(uint8 crcConfig, uint8 crcChannel, const Crc_DataInfoType *InfoPtr
   ,                                          uint32 crcStartValue)
{
   uint32 i;
   uint32 save_cout;
   uint32 result;
   uint8  save_ctl;

   save_ctl = CRC_CFG(crcChannel);
   save_cout = CRC_OUT(crcChannel);
    //If polynomial of interrupted calculation was not CCITT16 - regardless of DCRBnISZ setting.
   if((CRC_GENFUNC_CCITT16) != (save_ctl & CRC_HW_DCRBNPOL_BITMASK))
   {
       // XOR operation done by hardware needs to be reversed - but NOT for any CCITT16 computation
       save_cout ^= CRC_XOR_VALUE32;
   }

   CRC_CFG(crcChannel) = crcConfig;
   CRC_OUT(crcChannel) = crcStartValue;

   if(crcConfig != CRC_HW_16B_CCITT16)
   {
        for(i = 0; i < InfoPtr->crcLength; i++)
        {
            CRC_INP(crcChannel) = InfoPtr->crc8bitDataPtr[i];
        }
   }
   else{
        for(i = 0; i < InfoPtr->crcLength; i++)
        {
            CRC_INP(crcChannel) = InfoPtr->crc16bitDataPtr[i];
        }
   }

    result = CRC_OUT(crcChannel);

   CRC_CFG(crcChannel) = save_ctl;
   CRC_OUT(crcChannel) = save_cout;

    return result;
}

CRC_INLINE uint8 Crc_Lok_CalcCRC8H2F_Hw(const uint8* Crc_DataPtr
   ,                                         uint32 Crc_Length_u32, uint8 Crc_StartValue)
{
   Crc_DataInfoType Info;

    Info.crc8bitDataPtr = Crc_DataPtr;
    Info.crcLength = Crc_Length_u32;
     return (uint8)Crc_Lok_CalcCRC_RH850_Hw(CRC_HW_8B_2F8,Crc_Core_2_CrcHWTable[Crc_GetCoreId()].Crc8H2F_HW
   ,            &Info, Crc_StartValue);
}

CRC_INLINE uint8 Crc_Lok_CalcCRC8_Hw(const uint8* Crc_DataPtr
   ,                                          uint32 Crc_Length_u32, uint8 Crc_StartValue)
{
   Crc_DataInfoType Info;

    Info.crc8bitDataPtr = Crc_DataPtr;
    Info.crcLength = Crc_Length_u32;
    return (uint8)Crc_Lok_CalcCRC_RH850_Hw(CRC_HW_8B_SAE8, Crc_Core_2_CrcHWTable[Crc_GetCoreId()].Crc8_HW
   ,                                               &Info, Crc_StartValue);
}

CRC_INLINE uint16 Crc_Lok_CalcCRC16_Hw(const uint8* Crc_DataPtr
   ,                                             uint32 Crc_Length_u32, uint16 Crc_StartValue_u16)
{
   Crc_DataInfoType Info;

    Info.crc8bitDataPtr = Crc_DataPtr;
    Info.crcLength = Crc_Length_u32;
    return (uint16)Crc_Lok_CalcCRC_RH850_Hw(CRC_HW_8B_CCITT16, Crc_Core_2_CrcHWTable[Crc_GetCoreId()].Crc16_HW
   ,                                               &Info, Crc_StartValue_u16);
}

CRC_INLINE uint16 Crc_Lok_CalcCRC16_Hw16(const uint16* Crc_DataPtr
   ,                                             uint32 Crc_Length_u32, uint16 Crc_StartValue_u16)
{
   Crc_DataInfoType Info;

    Info.crc16bitDataPtr = Crc_DataPtr;
    Info.crcLength = Crc_Length_u32;
    return (uint16)Crc_Lok_CalcCRC_RH850_Hw(CRC_HW_16B_CCITT16, Crc_Core_2_CrcHWTable[Crc_GetCoreId()].Crc16_HW
   ,                                               &Info, Crc_StartValue_u16);
}

CRC_INLINE uint32 Crc_Lok_CalcCRC32_Hw(const uint8* Crc_DataPtr
   ,                                                    uint32 Crc_Length_u32, uint32 Crc_StartValue_u32)
{
   Crc_DataInfoType Info;

    Info.crc8bitDataPtr = Crc_DataPtr;
    Info.crcLength = Crc_Length_u32;
    return Crc_Lok_CalcCRC_RH850_Hw(CRC_HW_8B_ETHERNET32, Crc_Core_2_CrcHWTable[Crc_GetCoreId()].Crc32_HW
   ,                                      &Info, Crc_StartValue_u32);
}
#endif
#endif
