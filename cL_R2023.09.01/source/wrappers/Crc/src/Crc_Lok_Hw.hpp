

#ifndef CRC_PRV_HW_H
#define CRC_PRV_HW_H

#include "Crc_Cfg.hpp"
#include "rba_BswSrv.hpp"
#if(CRC_ST == CRC_HARDWARE_FAM)
#include "Crc_Lok_ST_CHORUS_C1.hpp"
#elif(CRC_JDP == CRC_HARDWARE_FAM)
#include "Crc_Lok_Jdp_Hw.hpp"
#elif(CRC_IFX == CRC_HARDWARE_FAM)
#include "Crc_Lok_Ifx_Hw.hpp"
#else
#include "Crc_Lok_RH850_Hw.hpp"
#endif

#if((CRC_JDP == CRC_HARDWARE_FAM) || (CRC_IFX == CRC_HARDWARE_FAM))

CRC_INLINE void Crc_Lok_ReverseBytes_Hw(uint32* Crc_data_u32)
{
   uint32 output_u32;

    output_u32  = ((* Crc_data_u32) >> 24U);

    output_u32 ^= (((* Crc_data_u32) & 0x00FF0000UL) >> 8U);

    output_u32 ^= (((* Crc_data_u32) & 0x0000FF00UL) << 8U);

    output_u32 ^= (((* Crc_data_u32) & 0x000000FFUL) << 24U);

    *Crc_data_u32 = output_u32;
}

CRC_INLINE uint32 Crc_Lok_Convert_AU8ToU32_Hw(const uint8 * Crc_data_au8, uint8_least arrayLength_u8)
{
   uint32 output_u32;
   const uint8* data_u8_ptr = Crc_data_au8;
   uint8 i_u8;

    output_u32 =  ((uint32)(*data_u8_ptr));

   for(i_u8 = 1U; i_u8 < arrayLength_u8; i_u8++)
   {

        output_u32  <<= 8U;
        data_u8_ptr ++;
        output_u32  ^= ((uint32)(*data_u8_ptr));
   }

    return (output_u32);
}

CRC_INLINE boolean Crc_Lok_UseSoftware_Hw(void){
   boolean useSoftware_b = FALSE;
   uint8_least physCore_u8 = rba_BswSrv_GetPhysCore();

   if(physCore_u8 > 2U)
   {
        useSoftware_b = TRUE;
   }
   else{
       if(Crc_Core_2_CrcHWTable[physCore_u8].Crc32_HW == CRC_HW_UNDEFINED)
       {
        useSoftware_b = TRUE;
       }
   }

    return (useSoftware_b);
}

CRC_INLINE uint32 Crc_Lok_BytesForSwCount_Hw(const uint32 Crc_Length_u32, uint32 Crc_StartValue_u32)
{
   uint32 bytesForSwCount_u32 = (0U);

   if(Crc_Lok_UseSoftware_Hw() != FALSE)
   {
        bytesForSwCount_u32 = Crc_Length_u32;
   }
   else{
        if((Crc_Length_u32 < (4U)) && (Crc_StartValue_u32 != (0x00000000UL)))
        {
            bytesForSwCount_u32 = Crc_Length_u32;
        }
   }

    return (bytesForSwCount_u32);
}

CRC_INLINE uint32 Crc_Lok_CalculateCrc32_Hw(const uint8* Crc_DataPtr, uint32 Crc_Length_u32, uint32 Crc_StartValue_u32)
{
   uint32 save_registerData_au32 [3];
   uint32 i_u32;
   uint32 result_u32;
   uint32 start_value_u32 = Crc_StartValue_u32;
   uint32 Crc_StartValueForFirstCalc_u32;
   uint32 Crc_StartValueRemaining_u32;
   uint32 data_tmp_u32;
   const uint8* data_u8_ptr = Crc_DataPtr;
   Crc_HwReg_tst* Crc_Address_s_ptr;
   uint32 leftBytes_u32 = Crc_Length_u32 % 4U;

   Crc_Lok_ReverseBytes_Hw(&start_value_u32);

   Crc_StartValueForFirstCalc_u32 = start_value_u32;
   Crc_StartValueRemaining_u32 = start_value_u32;

   Crc_Address_s_ptr = Crc_Lok_DetectCrcEngineToUse_Hw();

   Crc_Lok_GetRegisterValues_Hw(save_registerData_au32, Crc_Address_s_ptr);

   Crc_Lok_Config_Hw (Crc_Address_s_ptr);

   if(leftBytes_u32 > 0U)
   {

        Crc_StartValueForFirstCalc_u32 >>= (32U - (leftBytes_u32 << 3U));

        Crc_StartValueRemaining_u32 <<= (leftBytes_u32 << 3U);

        data_tmp_u32 = Crc_Lok_Convert_AU8ToU32_Hw(data_u8_ptr, leftBytes_u32);

        data_u8_ptr += leftBytes_u32;

        data_tmp_u32 ^= Crc_StartValueForFirstCalc_u32;

        CRC_HARDWARE_FAM_CHECK(&data_tmp_u32);

        Crc_Lok_CalculateCrc_Hw(&data_tmp_u32, Crc_Address_s_ptr);
   }

   if(Crc_Length_u32 >= 4U)
   {
        data_tmp_u32 = Crc_Lok_Convert_AU8ToU32_Hw(data_u8_ptr, 4U);
        data_u8_ptr += 4U;

        data_tmp_u32 ^= Crc_StartValueRemaining_u32;

        CRC_HARDWARE_FAM_CHECK(&data_tmp_u32);

        Crc_Lok_CalculateCrc_Hw(&data_tmp_u32, Crc_Address_s_ptr);
   }

   for(i_u32 = 4U; (i_u32 + 3U) < Crc_Length_u32; i_u32 += 4U)
   {
        data_tmp_u32 = Crc_Lok_Convert_AU8ToU32_Hw(data_u8_ptr, 4U);
        data_u8_ptr += 4U;

        CRC_HARDWARE_FAM_CHECK(&data_tmp_u32);

        Crc_Lok_CalculateCrc_Hw(&data_tmp_u32, Crc_Address_s_ptr);
   }

    result_u32 = Crc_Lok_Result_Hw(Crc_Address_s_ptr);

   Crc_Lok_SetRegisterValues_Hw(save_registerData_au32, Crc_Address_s_ptr);

    return (result_u32);
}

CRC_INLINE uint32 Crc_Lok_CalcCRC32_Hw (const uint8* Crc_DataPtr
   ,                            const uint32 Crc_Length_u32, uint32 Crc_StartValue_u32)
{

   uint32 result_u32          = (Crc_StartValue_u32  ^ (CRC_XOR_VALUE32));
   uint32 leftForSw_u32       = (0U);
   uint32 crcTemp;
   uint32  index;
   const uint8* data_u8_ptr   = Crc_DataPtr;

    leftForSw_u32  = Crc_Lok_BytesForSwCount_Hw(Crc_Length_u32, Crc_StartValue_u32);

   if(leftForSw_u32 < Crc_Length_u32)
   {
        result_u32 = Crc_Lok_CalculateCrc32_Hw(Crc_DataPtr, (Crc_Length_u32 - leftForSw_u32), Crc_StartValue_u32);
   }

    data_u8_ptr += (Crc_Length_u32 - leftForSw_u32);

   crcTemp = result_u32 ^ (CRC_XOR_VALUE32);

   for(index = 0U; index < leftForSw_u32; ++index)
   {

        crcTemp ^= data_u8_ptr[index];

        crcTemp = (crcTemp >> (CRC_JUNK)) ^
                CRC_32_REV_Tbl[crcTemp & (CRC_TABLEMASK)];
   }
    result_u32 = crcTemp ^ (CRC_XOR_VALUE32);

    return (result_u32);
}

#endif

#endif
