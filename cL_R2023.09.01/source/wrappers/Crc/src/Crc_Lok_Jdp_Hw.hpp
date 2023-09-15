#ifndef CRC_PRV_JDP_HW_H
#define CRC_PRV_JDP_HW_H

#include "types.hpp" //TBD: Remove
#include "CfgMcalMcu.hpp"
#include "rba_BswSrv.hpp"
#include RBA_REG_CRC_H

typedef rba_Reg_CRC_tst Crc_HwReg_tst;

#if(CRC_MCU_RB_MACHINE_DEV == MCU_RB_ST_UC1_DEV3_40NM_ALL)

#define CRC_PRV_JDP_CFG(X)          ((*(X)).CFG1)
#define CRC_PRV_JDP_INP(X)          ((*(X)).INP1)
#define CRC_PRV_JDP_INTRES(X)       ((*(X)).CSTAT1)
#define CRC_PRV_JDP_RES(X)          ((*(X)).OUTP1)
#else

#define CRC_PRV_JDP_CFG(X)          ((*(X)).CFG)
#define CRC_PRV_JDP_INP(X)          ((*(X)).INP)
#define CRC_PRV_JDP_INTRES(X)       ((*(X)).CSTAT)
#define CRC_PRV_JDP_RES(X)          ((*(X)).OUTP)
#endif

CRC_INLINE rba_Reg_CRC_tst* Crc_Lok_DetectCrcEngineToUse_Hw(void){
    rba_Reg_CRC_tst *Crc_Lok_Engine_u32;

   if(Crc_Core_2_CrcHWTable[rba_BswSrv_GetPhysCore()].Crc32_HW == 0U)
   {
        Crc_Lok_Engine_u32 = (&CRC_0);
   }
   else{
        Crc_Lok_Engine_u32 = (&CRC_1);
   }

    return (Crc_Lok_Engine_u32);
}

CRC_INLINE void Crc_Lok_GetRegisterValues_Hw(uint32* registerValues_au32, const rba_Reg_CRC_tst* const Crc_Address_s_ptr)
{

     registerValues_au32[0] = CRC_PRV_JDP_CFG(Crc_Address_s_ptr);
     registerValues_au32[1] = CRC_PRV_JDP_INP(Crc_Address_s_ptr);
     registerValues_au32[2] = CRC_PRV_JDP_INTRES(Crc_Address_s_ptr);
}

CRC_INLINE void Crc_Lok_SetRegisterValues_Hw(const uint32* const registerValues_au32, rba_Reg_CRC_tst* Crc_Address_s_ptr )
{

     CRC_PRV_JDP_CFG(Crc_Address_s_ptr)    = registerValues_au32[0];
     CRC_PRV_JDP_INP(Crc_Address_s_ptr)    = registerValues_au32[1];
     CRC_PRV_JDP_INTRES(Crc_Address_s_ptr) = registerValues_au32[2];
}

CRC_INLINE void Crc_Lok_Config_Hw(rba_Reg_CRC_tst *Crc_Address_s_ptr)
{

   CRC_PRV_JDP_CFG(Crc_Address_s_ptr) = CONF_CRC32_FOR_SWAP_AND_INVERSION;
   CRC_PRV_JDP_INTRES(Crc_Address_s_ptr) = (0U);
}

CRC_INLINE void Crc_Lok_CalculateCrc_Hw(uint32 const* Crc_data_u32, rba_Reg_CRC_tst *Crc_Address_s_ptr)
{
   CRC_PRV_JDP_INP(Crc_Address_s_ptr) = ((*Crc_data_u32));
}

CRC_INLINE uint32 Crc_Lok_Result_Hw(rba_Reg_CRC_tst const* Crc_Address_s_ptr)
{
    return CRC_PRV_JDP_RES(Crc_Address_s_ptr);
}

#endif
