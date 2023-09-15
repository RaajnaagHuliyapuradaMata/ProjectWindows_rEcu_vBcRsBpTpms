#ifndef CRC_PRV_IFX_HW_H
#define CRC_PRV_IFX_HW_H

#include "types.hpp" //TBD: Remove
#include "CfgMcalMcu.hpp"
#include "rba_BswSrv.hpp"
#include RBA_REG_FCE_H

#define CRC_PRV_IFX_CORE_0        (0U)
#define CRC_PRV_IFX_CORE_1        (1U)
#define CRC_PRV_IFX_CORE_2        (2U)

#define CRC_PRV_IFX_CFG(X)          ((*(X)).CFG)
#define CRC_PRV_IFX_INP(X)          ((*(X)).IR)
#define CRC_PRV_IFX_INTRES(X)       ((*(X)).CRC)
#define CRC_PRV_IFX_RES(X)          ((*(X)).RES)

typedef rba_Reg_FCE_Input_CRC_tst Crc_HwReg_tst;

CRC_INLINE rba_Reg_FCE_Input_CRC_tst* Crc_Lok_DetectCrcEngineToUse_Hw(void){
    rba_Reg_FCE_Input_CRC_tst *Crc_Lok_Engine_u32;

   Crc_Lok_Engine_u32 = (&(FCE.CRC[Crc_Core_2_CrcHWTable[rba_BswSrv_GetPhysCore()].Crc32_HW]));

    return (Crc_Lok_Engine_u32);
}

CRC_INLINE void Crc_Lok_GetRegisterValues_Hw(uint32* registerValues_au32, const rba_Reg_FCE_Input_CRC_tst* const Crc_Address_s_ptr)
{

     registerValues_au32[0] = CRC_PRV_IFX_INP(Crc_Address_s_ptr);
     registerValues_au32[1] = CRC_PRV_IFX_INTRES(Crc_Address_s_ptr);
}

CRC_INLINE void Crc_Lok_SetRegisterValues_Hw(const uint32* const registerValues_au32, rba_Reg_FCE_Input_CRC_tst * Crc_Address_s_ptr )
{

   CRC_PRV_IFX_INP(Crc_Address_s_ptr)  = registerValues_au32[0];
   CRC_PRV_IFX_INTRES(Crc_Address_s_ptr) = registerValues_au32[1];
}

CRC_INLINE void Crc_Lok_Config_Hw(rba_Reg_FCE_Input_CRC_tst *Crc_Address_s_ptr)
{

   if(FCE.CLC != 0U)
   {
    	Mcu_Rn_ResetEndInit();
        FCE.CLC = 0U;
        Mcu_Rn_SetEndInit();
   }

   CRC_PRV_IFX_INTRES(Crc_Address_s_ptr) = (0U);
}

CRC_INLINE void Crc_Lok_CalculateCrc_Hw(uint32 const* Crc_data_u32, rba_Reg_FCE_Input_CRC_tst *Crc_Address_s_ptr)
{
   CRC_PRV_IFX_INP(Crc_Address_s_ptr) = ((*Crc_data_u32));
}

CRC_INLINE uint32 Crc_Lok_Result_Hw(rba_Reg_FCE_Input_CRC_tst const* Crc_Address_s_ptr)
{
    return CRC_PRV_IFX_RES(Crc_Address_s_ptr);
}

#endif
