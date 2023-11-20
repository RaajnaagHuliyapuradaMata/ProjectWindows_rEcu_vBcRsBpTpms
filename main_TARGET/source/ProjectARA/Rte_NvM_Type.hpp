#ifndef _RTE_NVM_TYPE_H
#define _RTE_NVM_TYPE_H

#include "Types.hpp"
#include "Dem_NvmCallbacks.hpp"
#include "SwcApplTpms_NvM.hpp"
#include "iTpms_Interface.hpp"

#define NVM_BLOCK_SIZE_BSW_DATA     (uint16)64
#define Appl_JobEndCallback_CAT01                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT01
#define Appl_JobEndCallback_CAT02                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT02
#define Appl_JobEndCallback_CAT03                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT03
#define Appl_JobEndCallback_CAT04                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT04
#define Appl_JobEndCallback_CAT05                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT05
#define Appl_JobEndCallback_CAT06                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT06
#define Appl_JobEndCallback_CAT07                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT07
#define Appl_JobEndCallback_CAT08                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT08
#define Appl_JobEndCallback_CAT09                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT09
#define Appl_JobEndCallback_CAT10                     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_CAT10
#define Appl_JobEndCallback_DemNvm_IdEvStatusByte     (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvStatusByte
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc0        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc0
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc1        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc1
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc2        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc2
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc3        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc3
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc4        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc4
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc5        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc5
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc6        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc6
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc7        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc7
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc8        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc8
#define Appl_JobEndCallback_DemNvm_IdEvMemLoc9        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc9
#define Appl_JobEndCallback_DemNvm_IdDemGenericNvData (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_DemNvm_IdDemGenericNvData
#define Appl_JobEndCallback_ECUM_CFG_NVM_BLOCK        (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_ECUM_CFG_NVM_BLOCK
#define Appl_JobEndCallback_BSW_Data                  (NvM_AsyncCbkPtrType)Memstack_Appl_JobEndCallback_BSW_Data
#define NvMBlock_CAT01_Consistent                     0x000001
#define NvMBlock_CAT02_Consistent                     0x000002
#define NvMBlock_CAT03_Consistent                     0x000004
#define NvMBlock_CAT04_Consistent                     0x000008
#define NvMBlock_CAT05_Consistent                     0x000010
#define NvMBlock_CAT06_Consistent                     0x000020
#define NvMBlock_CAT07_Consistent                     0x000040
#define NvMBlock_CAT08_Consistent                     0x000080
#define NvMBlock_CAT09_Consistent                     0x000100
#define NvMBlock_CAT10_Consistent                     0x000200
#define NvMBlock_DemNvm_IdEvStatusByte_Consistent     0x000400
#define NvMBlock_DemNvm_IdEvMemLoc0_Consistent        0x000800
#define NvMBlock_DemNvm_IdEvMemLoc1_Consistent        0x001000
#define NvMBlock_DemNvm_IdEvMemLoc2_Consistent        0x002000
#define NvMBlock_DemNvm_IdEvMemLoc3_Consistent        0x004000
#define NvMBlock_DemNvm_IdEvMemLoc4_Consistent        0x008000
#define NvMBlock_DemNvm_IdEvMemLoc5_Consistent        0x010000
#define NvMBlock_DemNvm_IdEvMemLoc6_Consistent        0x020000
#define NvMBlock_DemNvm_IdEvMemLoc7_Consistent        0x040000
#define NvMBlock_DemNvm_IdEvMemLoc8_Consistent        0x080000
#define NvMBlock_DemNvm_IdEvMemLoc9_Consistent        0x100000
#define NvMBlock_DemNvm_IdDemGenericNvData_Consistent 0x200000
#define NvMBlock_ECUM_CFG_NVM_BLOCK_Consistent        0x400000
#define NvMBlock_BSW_Data_Consistent                  0x800000
#define CU16_NVM_ALL_CATEG_CONSISTENT       (uint16)(((uint16)1<<NVM_MAX_CATEGORYS)-1)

extern uint8 Rom_NvMBlock_CAT01[];
extern uint8 Rom_NvMBlock_CAT02[];
extern uint8 Rom_NvMBlock_CAT03[];
extern uint8 Rom_NvMBlock_CAT04[];
extern uint8 Rom_NvMBlock_CAT05[];
extern uint8 Rom_NvMBlock_CAT06[];
extern uint8 Rom_NvMBlock_CAT07[];
extern uint8 Rom_NvMBlock_CAT08[];
extern uint8 Rom_NvMBlock_CAT09[];
extern uint8 Rom_NvMBlock_CAT10[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvStatusByte[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc0[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc1[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc2[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc3[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc4[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc5[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc6[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc7[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc8[];
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc9[];
extern uint8 Rom_NvMBlock_DemNvm_IdDemGenericNvData[];
extern uint8 Rom_ECUM_CFG_NVM_BLOCK[];
extern uint8 Rom_NvMBlock_BSW_Data[];
extern uint8 Ram_NvMBlock_CAT01[];
extern uint8 Ram_NvMBlock_CAT02[];
extern uint8 Ram_NvMBlock_CAT03[];
extern uint8 Ram_NvMBlock_CAT04[];
extern uint8 Ram_NvMBlock_CAT05[];
extern uint8 Ram_NvMBlock_CAT06[];
extern uint8 Ram_NvMBlock_CAT07[];
extern uint8 Ram_NvMBlock_CAT08[];
extern uint8 Ram_NvMBlock_CAT09[];
extern uint8 Ram_NvMBlock_CAT10[];
extern uint8 Ram_ECUM_CFG_NVM_BLOCK[];
extern uint8 Ram_NvMBlock_BSW_Data[];

extern void Memstack_Main(void);
extern uint32 Memstack_GetCurrentNvMConsistence(void);
extern void Memstack_ClearCurrentNvMConsistence(void);
extern uint8 Memstack_GetNvmCatFromHufBlockNumber(uint16 ushBlockNr);
extern uint8* Memstack_GetNvMRamAdress(uint16 ushBlockNr);
extern void  Memstack_SetEcuNvMRamBlockStatus(uint16 ushBlockNr);
extern void Memstack_WriteAllBlocks(void);
extern void Memstack_WriteCategoryOnEvent(void);
extern void Memstack_Appl_JobEndCallback_CAT01(void);
extern void Memstack_Appl_JobEndCallback_CAT02(void);
extern void Memstack_Appl_JobEndCallback_CAT03(void);
extern void Memstack_Appl_JobEndCallback_CAT04(void);
extern void Memstack_Appl_JobEndCallback_CAT05(void);
extern void Memstack_Appl_JobEndCallback_CAT06(void);
extern void Memstack_Appl_JobEndCallback_CAT07(void);
extern void Memstack_Appl_JobEndCallback_CAT08(void);
extern void Memstack_Appl_JobEndCallback_CAT09(void);
extern void Memstack_Appl_JobEndCallback_CAT10(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdDemGenericNvData(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc0(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc1(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc2(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc3(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc4(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc5(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc6(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc7(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc8(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc9(void);
extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvStatusByte(void);
extern void Memstack_Appl_JobEndCallback_ECUM_CFG_NVM_BLOCK(void);
extern void Memstack_Appl_JobEndCallback_BSW_Data(void);

#endif
