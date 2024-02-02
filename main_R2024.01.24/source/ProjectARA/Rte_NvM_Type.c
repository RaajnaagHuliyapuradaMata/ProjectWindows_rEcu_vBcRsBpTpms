#include "Std_Types.hpp"

#include "Rte_NvM_Type.hpp"
#include "EcuabFee.hpp"
#include "Fls.hpp"
#include "NvM.hpp"
#include "Dem_Cfg_AssertionChk.hpp"
#include "iTpms_Interface.hpp"

#if((NVM_CAT01_SIZE_BYTES + NVM_CAT02_SIZE_BYTES + NVM_CAT03_SIZE_BYTES + \
      NVM_CAT04_SIZE_BYTES + NVM_CAT05_SIZE_BYTES + NVM_CAT06_SIZE_BYTES + \
      NVM_CAT07_SIZE_BYTES + NVM_CAT08_SIZE_BYTES + NVM_CAT09_SIZE_BYTES + \
      NVM_CAT10_SIZE_BYTES) != NVM_HUF_DATA_MAX_BYTE_SIZE)
  #error Check NV-Data byte size!
#endif

#define NVM_BLOCK_MEMBERS_CATEGORY_01   (NVM_CAT01_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_02   (NVM_CAT02_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_03   (NVM_CAT03_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_04   (NVM_CAT04_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_05   (NVM_CAT05_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_06   (NVM_CAT06_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_07   (NVM_CAT07_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_08   (NVM_CAT08_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_09   (NVM_CAT09_SIZE_BYTES / NVM_BLOCK_SIZE)
#define NVM_BLOCK_MEMBERS_CATEGORY_10   (NVM_CAT10_SIZE_BYTES / NVM_BLOCK_SIZE)

#define NVM_CUMULATED_BLOCKS_CAT01       NVM_BLOCK_MEMBERS_CATEGORY_01
#define NVM_CUMULATED_BLOCKS_CAT02       (NVM_CUMULATED_BLOCKS_CAT01 + NVM_BLOCK_MEMBERS_CATEGORY_02)
#define NVM_CUMULATED_BLOCKS_CAT03       (NVM_CUMULATED_BLOCKS_CAT02 + NVM_BLOCK_MEMBERS_CATEGORY_03)
#define NVM_CUMULATED_BLOCKS_CAT04       (NVM_CUMULATED_BLOCKS_CAT03 + NVM_BLOCK_MEMBERS_CATEGORY_04)
#define NVM_CUMULATED_BLOCKS_CAT05       (NVM_CUMULATED_BLOCKS_CAT04 + NVM_BLOCK_MEMBERS_CATEGORY_05)
#define NVM_CUMULATED_BLOCKS_CAT06       (NVM_CUMULATED_BLOCKS_CAT05 + NVM_BLOCK_MEMBERS_CATEGORY_06)
#define NVM_CUMULATED_BLOCKS_CAT07       (NVM_CUMULATED_BLOCKS_CAT06 + NVM_BLOCK_MEMBERS_CATEGORY_07)
#define NVM_CUMULATED_BLOCKS_CAT08       (NVM_CUMULATED_BLOCKS_CAT07 + NVM_BLOCK_MEMBERS_CATEGORY_08)
#define NVM_CUMULATED_BLOCKS_CAT09       (NVM_CUMULATED_BLOCKS_CAT08 + NVM_BLOCK_MEMBERS_CATEGORY_09)
#define NVM_CUMULATED_BLOCKS_CAT10       (NVM_CUMULATED_BLOCKS_CAT09 + NVM_BLOCK_MEMBERS_CATEGORY_10)

// determine which block shall be saved on event (1) or on shutdown only (0)

static uint8 ucCatSaveOnEvent   [NVM_MAX_CATEGORYS] = {   1,    0,    1,    0,    1,    0,    0,    0,    0,    1};
static uint8 ucCatRamBlockStatus[NVM_MAX_CATEGORYS] = {   0,    0,    0,    0,    0,    0,    0,    0,    0,    0};

// Miror RAMs
extern uint8 Ram_NvMBlock_CAT01[NVM_CAT01_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT02[NVM_CAT02_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT03[NVM_CAT03_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT04[NVM_CAT04_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT05[NVM_CAT05_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT06[NVM_CAT06_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT07[NVM_CAT07_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT08[NVM_CAT08_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT09[NVM_CAT09_SIZE_BYTES] = {0};
extern uint8 Ram_NvMBlock_CAT10[NVM_CAT10_SIZE_BYTES] = {0};
// RST: Ram mirrors for DEM are defined in DEM
//extern uint8 Ram_NvMBlock_DemNvm_IdEvStatusByte[DEM_NVM_ID_EVT_STATUSBYTE_SIZE] = {0};
//extern uint8 Ram_NvMBlock_DemNvm_IdEvMemLoc0[DEM_NVM_ID_EVMEM_LOC_0_SIZE] = {0};
//extern uint8 Ram_NvMBlock_DemNvm_IdEvMemLoc1[DEM_NVM_ID_EVMEM_LOC_1_SIZE] = {0};
//extern uint8 Ram_NvMBlock_DemNvm_IdEvMemLoc2[DEM_NVM_ID_EVMEM_LOC_2_SIZE] = {0};
//extern uint8 Ram_NvMBlock_DemNvm_IdEvMemLoc3[DEM_NVM_ID_EVMEM_LOC_3_SIZE] = {0};
//extern uint8 Ram_NvMBlock_DemNvm_IdEvMemLoc4[DEM_NVM_ID_EVMEM_LOC_4_SIZE] = {0};
//extern uint8 Ram_NvMBlock_DemNvm_IdEvMemLoc5[DEM_NVM_ID_EVMEM_LOC_5_SIZE] = {0};
//extern uint8 Ram_NvMBlock_DemNvm_IdDemGenericNvData[DEM_NVM_ID_DEM_GENERIC_NV_DATA_SIZE] = {0};
extern uint8 Ram_ECUM_CFG_NVM_BLOCK[20] = {0};
extern uint8 Ram_NvMBlock_BSW_Data[NVM_BLOCK_SIZE_BSW_DATA] = {0};

uint8* pCategoryRamBlock[NVM_MAX_CATEGORYS] = { Ram_NvMBlock_CAT01
   ,     Ram_NvMBlock_CAT02
   ,     Ram_NvMBlock_CAT03
   ,     Ram_NvMBlock_CAT04
   ,     Ram_NvMBlock_CAT05
   ,     Ram_NvMBlock_CAT06
   ,     Ram_NvMBlock_CAT07
   ,     Ram_NvMBlock_CAT08
   ,     Ram_NvMBlock_CAT09
   ,     Ram_NvMBlock_CAT10
                                              };

// Default Rom values RST Todo
extern uint8 Rom_NvMBlock_CAT01[NVM_CAT01_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT02[NVM_CAT02_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT03[NVM_CAT03_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT04[NVM_CAT04_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT05[NVM_CAT05_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT06[NVM_CAT06_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT07[NVM_CAT07_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT08[NVM_CAT08_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT09[NVM_CAT09_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_CAT10[NVM_CAT10_SIZE_BYTES] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvStatusByte[DEM_NVM_ID_EVT_STATUSBYTE_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc0[DEM_NVM_ID_EVMEM_LOC_0_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc1[DEM_NVM_ID_EVMEM_LOC_1_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc2[DEM_NVM_ID_EVMEM_LOC_2_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc3[DEM_NVM_ID_EVMEM_LOC_3_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc4[DEM_NVM_ID_EVMEM_LOC_4_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc5[DEM_NVM_ID_EVMEM_LOC_5_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc6[DEM_NVM_ID_EVMEM_LOC_6_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc7[DEM_NVM_ID_EVMEM_LOC_7_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc8[DEM_NVM_ID_EVMEM_LOC_8_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdEvMemLoc9[DEM_NVM_ID_EVMEM_LOC_9_SIZE] = {0};
extern uint8 Rom_NvMBlock_DemNvm_IdDemGenericNvData[DEM_NVM_ID_DEM_GENERIC_NV_DATA_SIZE] = {0};
extern uint8 Rom_ECUM_CFG_NVM_BLOCK[20] = {0};
extern uint8 Rom_NvMBlock_BSW_Data[NVM_BLOCK_SIZE_BSW_DATA] = {0};

static uint32 ulCurrentNvmConsistence = 0; // all nvm blocks non consistent per default

//static uint8 ucNvMCatSizeCum [11] = {0, 13, 26, 40, 55, 67, 79, 85, 91, 99, 100};
//RST 13.01.2021 replaced plain numbers by macros because the plain numbers in ucNvMCatSizeCum[3] is wrong. Cat03 has 96 bytes / 24 Huf blocks!
//The macros are coming from Huf_Nvm.h and must be identical to the macros in the TPMS lib!
static uint8 ucNvMCatSizeCum [11] = {0
   ,     NVM_CUMULATED_BLOCKS_CAT01
   ,     NVM_CUMULATED_BLOCKS_CAT02
   ,     NVM_CUMULATED_BLOCKS_CAT03
   ,     NVM_CUMULATED_BLOCKS_CAT04
   ,     NVM_CUMULATED_BLOCKS_CAT05
   ,     NVM_CUMULATED_BLOCKS_CAT06
   ,     NVM_CUMULATED_BLOCKS_CAT07
   ,     NVM_CUMULATED_BLOCKS_CAT08
   ,     NVM_CUMULATED_BLOCKS_CAT09
   ,     NVM_CUMULATED_BLOCKS_CAT10 };

extern uint8 Memstack_GetNvmCatFromHufBlockNumber(uint16 ushBlockNr)
{
  uint8 i = 0;

  while(ushBlockNr >= ucNvMCatSizeCum[i + 1])
  {
   i++;
  }

  return i;
}

extern uint8* Memstack_GetNvMRamAdress(uint16 ushBlockNr)
{
  NVM_BLOCK_TYPE* p2BlockAdress = (uint32*)NULL_PTR; // init with invalid value

  volatile uint8 ulTemp;

  if(ushBlockNr < ucNvMCatSizeCum[1])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT01 + ushBlockNr - ucNvMCatSizeCum[0];
  }
  else if(ushBlockNr < ucNvMCatSizeCum[2])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT02 + ushBlockNr - ucNvMCatSizeCum[1];
  }
  else if(ushBlockNr < ucNvMCatSizeCum[3])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT03 + ushBlockNr - ucNvMCatSizeCum[2];

  }
  else if(ushBlockNr < ucNvMCatSizeCum[4])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT04 + ushBlockNr - ucNvMCatSizeCum[3];

  }
  else if(ushBlockNr < ucNvMCatSizeCum[5])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT05 + ushBlockNr - ucNvMCatSizeCum[4];
  }
  else if(ushBlockNr < ucNvMCatSizeCum[6])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT06 + ushBlockNr - ucNvMCatSizeCum[5];
  }
  else if(ushBlockNr < ucNvMCatSizeCum[7])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT07 + ushBlockNr - ucNvMCatSizeCum[6];
  }
  else if(ushBlockNr < ucNvMCatSizeCum[8])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT08 + ushBlockNr - ucNvMCatSizeCum[7];
  }
  else if(ushBlockNr < ucNvMCatSizeCum[9])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT09 + ushBlockNr - ucNvMCatSizeCum[8];
  }
  else if(ushBlockNr < ucNvMCatSizeCum[10])
  {
    p2BlockAdress = (NVM_BLOCK_TYPE*)&Ram_NvMBlock_CAT10 + ushBlockNr - ucNvMCatSizeCum[9];
  }
  else{
    // invalid Block number
  }

  return (uint8*)p2BlockAdress;
}

extern void  Memstack_SetEcuNvMRamBlockStatus(uint16 ushBlockNr)
{

  if(ushBlockNr < ucNvMCatSizeCum[1])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT01, TRUE);
   ucCatRamBlockStatus[0] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[2])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT02, TRUE);
   ucCatRamBlockStatus[1] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[3])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT03, TRUE);
   ucCatRamBlockStatus[2] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[4])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT04, TRUE);
   ucCatRamBlockStatus[3] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[5])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT05, TRUE);
   ucCatRamBlockStatus[4] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[6])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT06, TRUE);
   ucCatRamBlockStatus[5] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[7])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT07, TRUE);
   ucCatRamBlockStatus[6] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[8])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT08, TRUE);
   ucCatRamBlockStatus[7] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[9])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT09, TRUE);
   ucCatRamBlockStatus[8] = 1;
  }
  else if(ushBlockNr < ucNvMCatSizeCum[10])
  {
    NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT10, TRUE);
   ucCatRamBlockStatus[9] = 1;
  }
  else{
  }
}

void infSwcServiceNvMSwcApplEcuM_InitFunction(void){
   NvM_RequestResultType Int_NvMultiBlockStatus;
   Fls_Init(FlsConfigSet);
   EcuabFee_Init();
   NvM_Init();
   NvM_ReadAll();
   do{
      NvM_MainFunction();
      EcuabFee_MainFunction();
      Fls_MainFunction();
      NvM_GetErrorStatus(NvMConf___MultiBlockRequest, &Int_NvMultiBlockStatus);
   }while( Int_NvMultiBlockStatus == NVM_REQ_PENDING );

   NvM_WriteBlock(
         NvMConf_NvMBlockDescriptor_NvMBlock_BSW_Data
      ,  (uint8*)&Ram_NvMBlock_BSW_Data[0]
   );
}

extern void Memstack_Main(void){
    NvM_MainFunction();
    EcuabFee_MainFunction();
    Fls_MainFunction();
}

extern void Memstack_WriteAllBlocks(void){
  NvM_RequestResultType Int_NvMultiBlockStatus;
  NvM_WriteAll();
  do{
    NvM_MainFunction();
    EcuabFee_MainFunction();
    Fls_MainFunction();
    NvM_GetErrorStatus(NvMConf___MultiBlockRequest, &Int_NvMultiBlockStatus);
  }
  while( Int_NvMultiBlockStatus == NVM_REQ_PENDING );
}

extern void Memstack_WriteCategoryOnEvent(void){
  uint8 i;
  for(i=0; i<NVM_MAX_CATEGORYS; i++){
   if(ucCatSaveOnEvent[i] == 1){
      if(ucCatRamBlockStatus[i] == 1){
        NvM_WriteBlock((NvMConf_NvMBlockDescriptor_NvMBlock_CAT01 + i), pCategoryRamBlock[i]);
        ucCatRamBlockStatus[i] = 0;
        break;
      }
   }
  }
}

extern void Memstack_Appl_JobEndCallback_CAT01(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT01, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED){
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT01_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT02(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT02, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED){
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT02_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT03(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT03, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED){
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT03_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT04(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT04, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED){
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT04_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT05(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT05, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED){
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT05_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT06(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT06, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT06_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT07(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT07, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT07_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT08(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT08, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT08_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT09(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT09, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT09_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_CAT10(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_CAT10, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_CAT10_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvStatusByte(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvStatusByte, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvStatusByte_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc0(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc0, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc0_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc1(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc1, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc1_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc2(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc2, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc2_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc3(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc3, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc3_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc4(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc4, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc4_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc5(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc5, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc5_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc6(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc6, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc6_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc7(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc7, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc7_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc8(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc8, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc8_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_DemNvm_IdEvMemLoc9(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdEvMemLoc9, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdEvMemLoc9_Consistent);
  }
}
extern void Memstack_Appl_JobEndCallback_DemNvm_IdDemGenericNvData(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_DemNvm_IdDemGenericNvData, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_DemNvm_IdDemGenericNvData_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_ECUM_CFG_NVM_BLOCK(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_ECUM_CFG_NVM_BLOCK_Consistent);
  }
}

extern void Memstack_Appl_JobEndCallback_BSW_Data(void){
  NvM_RequestResultType ucRequestResult;
  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvMBlock_BSW_Data, &ucRequestResult);
  if(ucRequestResult != NVM_REQ_INTEGRITY_FAILED)
  {
   ulCurrentNvmConsistence = (ulCurrentNvmConsistence | NvMBlock_BSW_Data_Consistent);
  }
}

extern uint32 Memstack_GetCurrentNvMConsistence(void){
  return ulCurrentNvmConsistence;
}

extern void Memstack_ClearCurrentNvMConsistence(void){
  ulCurrentNvmConsistence = 0;
}
