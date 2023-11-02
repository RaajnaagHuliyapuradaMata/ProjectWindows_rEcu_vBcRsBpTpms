#include "Std_Types.hpp"

#include "iTpms_Interface.hpp"
#include "SwcApplTpms_Rte.hpp"
#define NVMc
#include "SwcApplTpms_NvM.hpp"
#include "SwcApplTpms_NvM_If.hpp"
#include "Tpms_Rte_Data_Type.hpp"
#include "USWarn.hpp"
#include "WallocX.hpp"
#include "SwcApplTpms_DTC_If.hpp"
#include "WnTypePar.hpp"

#define ucHystHiPc (uint8) (350 / ucPResInMBarc)
#define scTemperatureWarningThresholdDefault        ((sint8) 80)

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
#define NVM_START_BLOCK_CAT_01        0U
#define NVM_START_BLOCK_CAT_02        (NVM_START_BLOCK_CAT_01 + NVM_BLOCK_MEMBERS_CATEGORY_01)
#define NVM_START_BLOCK_CAT_03        (NVM_START_BLOCK_CAT_02 + NVM_BLOCK_MEMBERS_CATEGORY_02)
#define NVM_START_BLOCK_CAT_04        (NVM_START_BLOCK_CAT_03 + NVM_BLOCK_MEMBERS_CATEGORY_03)
#define NVM_START_BLOCK_CAT_05        (NVM_START_BLOCK_CAT_04 + NVM_BLOCK_MEMBERS_CATEGORY_04)
#define NVM_START_BLOCK_CAT_06        (NVM_START_BLOCK_CAT_05 + NVM_BLOCK_MEMBERS_CATEGORY_05)
#define NVM_START_BLOCK_CAT_07        (NVM_START_BLOCK_CAT_06 + NVM_BLOCK_MEMBERS_CATEGORY_06)
#define NVM_START_BLOCK_CAT_08        (NVM_START_BLOCK_CAT_07 + NVM_BLOCK_MEMBERS_CATEGORY_07)
#define NVM_START_BLOCK_CAT_09        (NVM_START_BLOCK_CAT_08 + NVM_BLOCK_MEMBERS_CATEGORY_08)
#define NVM_START_BLOCK_CAT_10        (NVM_START_BLOCK_CAT_09 + NVM_BLOCK_MEMBERS_CATEGORY_09)
#define NVM_START_BLOCK_UNKNOWN       0xFFU

struct struct_NvCat01_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_01];
};
struct struct_NvCat02_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_02];
};
struct struct_NvCat03_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_03];
};
struct struct_NvCat04_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_04];
};
struct struct_NvCat05_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_05];
};
struct struct_NvCat06_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_06];
};
struct struct_NvCat07_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_07];
};
struct struct_NvCat08_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_08];
};
struct struct_NvCat09_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_09];
};
struct struct_NvCat10_32Bit
{
  NVM_BLOCK_TYPE ulBlockAccess[NVM_BLOCK_MEMBERS_CATEGORY_10];
};

struct struct_NvCat01
{
  uint8 ucIdx01_WsIdWN                [NVM_CAT01_IDX01_REAL_SIZE];
  uint8 ucIdx02_CdIdWN                [NVM_CAT01_IDX02_REAL_SIZE];
  uint8 ucIdx03_WdIdWN                [NVM_CAT01_IDX03_REAL_SIZE];
  uint8 ucIdx04_TsIdTM                [NVM_CAT01_IDX04_REAL_SIZE];
  uint8 ucIdx05_CbIdTM                [NVM_CAT01_IDX05_REAL_SIZE];
  uint8 ucIdx06_WarnTypeArrayIdWN     [NVM_CAT01_IDX06_REAL_SIZE];
  uint8 ucIdx07_ucResetWarnPressRef   [NVM_CAT01_IDX07_REAL_SIZE];
  uint8 ucIdx08_ucPatmo               [NVM_CAT01_IDX08_REAL_SIZE];
  sint8 scIdx09_scAdaptedTref         [NVM_CAT01_IDX09_REAL_SIZE];
  uint8 ucIdx10_Unused                [NVM_CAT01_IDX10_REAL_SIZE];
};

struct struct_NvCat02
{
  uint8 ucIdx01_ucReErrorStatuse    [NVM_CAT02_IDX01_REAL_SIZE];
  uint8 ucIdx02_ucReHeatUpStatuse   [NVM_CAT02_IDX02_REAL_SIZE];
  uint8 ucIdx03_ucFolgeAusfallCnt   [NVM_CAT02_IDX03_REAL_SIZE];
  uint8 ucIdx04_uiGutEmpfCnt        [NVM_CAT02_IDX04_REAL_SIZE];
  uint8 ucIdx05_uiMissedCnt         [NVM_CAT02_IDX05_REAL_SIZE];
  uint8 ucIdx06_bRadwechsel         [NVM_CAT02_IDX06_REAL_SIZE];
  uint8 ucIdx07_bHfIntLatch         [NVM_CAT02_IDX07_REAL_SIZE];
  uint8 ucIdx08_ucStatusEOLRoutine  [NVM_CAT02_IDX08_REAL_SIZE];
  uint8 ucIdx09_ucIsEOLRoutineActive[NVM_CAT02_IDX09_REAL_SIZE];
  uint8 ucIdx10_DTCActiveStatus     [NVM_CAT02_IDX10_REAL_SIZE];
  uint8 ucIdx11_DTCSingleActiveStatus [NVM_CAT02_IDX11_REAL_SIZE];
  uint8 ucIdx12_Unused              [NVM_CAT02_IDX12_REAL_SIZE];
};
struct struct_NvCat03
{
  uint8 ucIdx01_HistoryID                       [NVM_CAT03_IDX01_REAL_SIZE];
  uint8 ucIdx02_HistoryWP                       [NVM_CAT03_IDX02_REAL_SIZE];
  uint8 ucIdx03_WA_Parameter                    [NVM_CAT03_IDX03_REAL_SIZE];
  uint8 ucIdx04_WA_ABSTicksInOneRev             [NVM_CAT03_IDX04_REAL_SIZE];
  uint8 ucIdx05_ucVarAutolocationFailedCounter  [NVM_CAT03_IDX05_REAL_SIZE];
  uint8 ucIdx06_Unused                          [NVM_CAT03_IDX06_REAL_SIZE];
  uint8 ucIdx07_Unused                          [NVM_CAT03_IDX07_REAL_SIZE];
  uint8 ucIdx08_Unused                          [NVM_CAT03_IDX08_REAL_SIZE];
  uint8 ucIdx09_Test                            [NVM_CAT03_IDX09_REAL_SIZE];
  uint8 ucIdx10_Test                            [NVM_CAT03_IDX10_REAL_SIZE];
  uint8 ucIdx11_Test                            [NVM_CAT03_IDX11_REAL_SIZE];
};
struct struct_NvCat04
{
  uint8 ucIdx01_CcpCrcFilter  [NVM_CAT04_IDX01_REAL_SIZE];
  uint8 ucIdx02_CcpIdFilter   [NVM_CAT04_IDX02_REAL_SIZE];
  uint8 ucIdx03_CcpAnzIdFilter[NVM_CAT04_IDX03_REAL_SIZE];
  uint8 ucIdx04_CcpOnOff      [NVM_CAT04_IDX04_REAL_SIZE];
  uint8 ucIdx05_CcpFilterIds  [NVM_CAT04_IDX05_REAL_SIZE];
};
struct struct_NvCat05
{
  uint8 ucIdx01_ucVarCodLegislation             [NVM_CAT05_IDX01_REAL_SIZE];
   uint8 ucIdx02_ucVarCodHighPressResetThres[NVM_CAT05_IDX02_REAL_SIZE];
  uint8 ucIdx03_ucVarCodTemperatureWarningThres [NVM_CAT05_IDX03_REAL_SIZE];
  uint8 ucIdx04_ucVarCodOffroadPlacardPress     [NVM_CAT05_IDX04_REAL_SIZE];
  uint8 ucIdx05_ucVarCodPlacardPress            [NVM_CAT05_IDX05_REAL_SIZE];
  uint8 ucIdx06_ucVarCodMinPressThres           [NVM_CAT05_IDX06_REAL_SIZE];
  uint8 ucIdx07_ucVarCodHighPressThres          [NVM_CAT05_IDX07_REAL_SIZE];
  uint8 ucIdx08_ucVarCodAxImbSetThres           [NVM_CAT05_IDX08_REAL_SIZE];
  uint8 ucIdx09_ucVarCodAxImbResThres           [NVM_CAT05_IDX09_REAL_SIZE];
  uint8 ucReserved                              [NVM_CAT05_IDX10_REAL_SIZE];
};

struct struct_NvCat06
{
  uint8 ucIdx01_PressureFL[NVM_CAT06_IDX01_REAL_SIZE];
  uint8 ucIdx02_PressureFR[NVM_CAT06_IDX02_REAL_SIZE];
  uint8 ucIdx03_PressureRL[NVM_CAT06_IDX03_REAL_SIZE];
  uint8 ucIdx04_PressureRR[NVM_CAT06_IDX04_REAL_SIZE];
  sint8 scIdx05_TemperatureFL[NVM_CAT06_IDX05_REAL_SIZE];
  sint8 scIdx06_TemperatureFR[NVM_CAT06_IDX06_REAL_SIZE];
  sint8 scIdx07_TemperatureRL[NVM_CAT06_IDX07_REAL_SIZE];
  sint8 scIdx08_TemperatureRR[NVM_CAT06_IDX08_REAL_SIZE];
  uint8 ucIdx09_Reserved[NVM_CAT06_IDX09_REAL_SIZE];
};

struct struct_NvCat07
{
  uint8 ucReserved           [NVM_CAT07_IDX01_REAL_SIZE];
};
struct struct_NvCat08
{
  uint8 ucReserved           [NVM_CAT08_IDX01_REAL_SIZE];
};
struct struct_NvCat09
{
  uint8 ucReserved           [NVM_CAT09_IDX01_REAL_SIZE];
};
struct struct_NvCat10
{
  uint8 ucIdx01_NvInitialized[NVM_CAT10_IDX01_REAL_SIZE];
  uint8 ucIdx02_ECUDefect    [NVM_CAT10_IDX02_REAL_SIZE];
  uint8 ucIdx03_Unused       [NVM_CAT10_IDX03_REAL_SIZE];
  uint8 ucIdx04_Unused       [NVM_CAT10_IDX04_REAL_SIZE];
};

#pragma PRQA_MESSAGES_OFF 750

union union_NVM_Cat01
{
  struct struct_NvCat01       sData;
  struct struct_NvCat01_32Bit ulData32Bit;
};
union union_NVM_Cat02
{
  struct struct_NvCat02       sData;
  struct struct_NvCat02_32Bit ulData32Bit;
};
union union_NVM_Cat03
{
  struct struct_NvCat03       sData;
  struct struct_NvCat03_32Bit ulData32Bit;
};
union union_NVM_Cat04
{
  struct struct_NvCat04       sData;
  struct struct_NvCat04_32Bit ulData32Bit;
};
union union_NVM_Cat05
{
  struct struct_NvCat05       sData;
  struct struct_NvCat05_32Bit ulData32Bit;
};
union union_NVM_Cat06
{
  struct struct_NvCat06       sData;
  struct struct_NvCat06_32Bit ulData32Bit;
};
union union_NVM_Cat07
{
  struct struct_NvCat07       sData;
  struct struct_NvCat07_32Bit ulData32Bit;
};
union union_NVM_Cat08
{
  struct struct_NvCat08       sData;
  struct struct_NvCat08_32Bit ulData32Bit;
};
union union_NVM_Cat09
{
  struct struct_NvCat09       sData;
  struct struct_NvCat09_32Bit ulData32Bit;
};
union union_NVM_Cat10
{
  struct struct_NvCat10       sData;
  struct struct_NvCat10_32Bit ulData32Bit;
};
#pragma PRQA_MESSAGES_ON

struct MirrorStruct {
   union union_NVM_Cat01 tCat01;
   union union_NVM_Cat02 tCat02;
   union union_NVM_Cat03 tCat03;
   union union_NVM_Cat04 tCat04;
   union union_NVM_Cat05 tCat05;
   union union_NVM_Cat06 tCat06;
   union union_NVM_Cat07 tCat07;
   union union_NVM_Cat08 tCat08;
   union union_NVM_Cat09 tCat09;
   union union_NVM_Cat10 tCat10;
};

typedef union
{
   struct MirrorStruct tStrAcc;
    NVM_BLOCK_TYPE tBlAcc[NVM_MAX_AMOUNT_BLOCKS];
}MirrorType;

typedef void (*ftInitEECat)(void);

static uintptr ui32GetMemberStartByte(uint8 ui8Cat, uint8 ui8Member);
static uint8 ui8GetMemberSizeInByte(uint8 ui8Cat, uint8 ui8Member);
static uint8 ui8GetCatSizeInBlocks (uint8 ui8Categ);
static void WriteCateg2Blocks(uint8 ui8Categ, NVM_BLOCK_TYPE * p2Target);
static void   InitEECat01(void);
static void   InitEECat02(void);
static void   InitEECat03(void);
static void   InitEECat04(void);
static void   InitEECat05(void);
static void   InitEECat06(void);
static void   InitEECat07(void);
static void   InitEECat08(void);
static void   InitEECat09(void);
static void   InitEECat10(void);

static boolean                   m_bWritingNvdata;

static const ftInitEECat arrInitEECatFunctions[NVM_MAX_CATEGORYS]=
{
    &InitEECat01
   ,   &InitEECat02
   ,   &InitEECat03
   ,   &InitEECat04
   ,   &InitEECat05
   ,   &InitEECat06
   ,   &InitEECat07
   ,   &InitEECat08
   ,   &InitEECat09
   ,   &InitEECat10
};

static uintptr ui32GetMemberStartByte(uint8 ui8Cat, uint8 ui8Member)
{
  const MirrorType * p2Mir = 0;
  const uint8 * p2Member;

  switch(ui8Cat)
  {
  case 1:
      switch(ui8Member)
      {
      case 1:
          p2Member = (const uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      case 2:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx02_CdIdWN ;
          break;
      case 3:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx03_WdIdWN ;
          break;
      case 4:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx04_TsIdTM ;
          break;
      case 5:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx05_CbIdTM ;
          break;
      case 6:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx06_WarnTypeArrayIdWN ;
          break;
      case 7:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx07_ucResetWarnPressRef ;
          break;
      case 8:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx08_ucPatmo ;
          break;
      case 9:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.scIdx09_scAdaptedTref;
          break;
      case 10:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx10_Unused;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 2:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData .ucIdx01_ucReErrorStatuse;
          break;
      case 2:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx02_ucReHeatUpStatuse;
          break;
      case 3:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx03_ucFolgeAusfallCnt ;
          break;
      case 4:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx04_uiGutEmpfCnt ;
          break;
      case 5:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx05_uiMissedCnt ;
          break;
      case 6:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx06_bRadwechsel ;
          break;
      case 7:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx07_bHfIntLatch ;
          break;
      case 8:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx08_ucStatusEOLRoutine  ;
          break;
      case 9:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx09_ucIsEOLRoutineActive ;
          break;
      case 10:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx10_DTCActiveStatus ;
          break;
      case 11:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx11_DTCSingleActiveStatus;
          break;
      case 12:
          p2Member = (uint8 *) p2Mir ->tStrAcc.tCat02.sData.ucIdx12_Unused ;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 3:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx01_HistoryID ;
          break;
      case 2:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx02_HistoryWP ;
          break;
      case 3:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx03_WA_Parameter ;
          break;
      case 4:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx04_WA_ABSTicksInOneRev ;
          break;

      case 5:                                                                                                     //RST NVM ok
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx05_ucVarAutolocationFailedCounter ;
          break;
      case 6:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx06_Unused ;
          break;
      case 7:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx07_Unused ;
          break;
      case 8:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx08_Unused ;
          break;

      case 9:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx09_Test ;
          break;
      case 10:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx10_Test ;
          break;
      case 11:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat03.sData.ucIdx11_Test ;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 4:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat04.sData.ucIdx01_CcpCrcFilter ;
          break;
      case 2:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat04.sData.ucIdx02_CcpIdFilter ;
          break;
      case 3:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat04.sData.ucIdx03_CcpAnzIdFilter ;
          break;
      case 4:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat04.sData.ucIdx04_CcpOnOff ;
          break;
      case 5:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat04.sData.ucIdx05_CcpFilterIds ;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 5:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx01_ucVarCodLegislation;
          break;
      case 2:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx02_ucVarCodHighPressResetThres ;
          break;
      case 3:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx03_ucVarCodTemperatureWarningThres ;
          break;
      case 4:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx04_ucVarCodOffroadPlacardPress ;
          break;
      case 5:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx05_ucVarCodPlacardPress ;
          break;
      case 6:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx06_ucVarCodMinPressThres;
          break;
      case 7:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx07_ucVarCodHighPressThres ;
          break;
      case 8:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx08_ucVarCodAxImbSetThres ;
          break;
      case 9:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucIdx09_ucVarCodAxImbResThres ;
          break;
      case 10:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat05.sData.ucReserved;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 6:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat06.sData.ucIdx01_PressureFL;
          break;
      case 2:
          p2Member = (uint8 *)p2Mir->tStrAcc.tCat06.sData.ucIdx02_PressureFR;
          break;
      case 3:
          p2Member = (uint8 *)p2Mir->tStrAcc.tCat06.sData.ucIdx03_PressureRL;
          break;
      case 4:
          p2Member = (uint8 *)p2Mir->tStrAcc.tCat06.sData.ucIdx04_PressureRR;
          break;
      case 5:
          p2Member = (uint8 *)p2Mir->tStrAcc.tCat06.sData.scIdx05_TemperatureFL;
          break;
      case 6:
          p2Member = (uint8 *)p2Mir->tStrAcc.tCat06.sData.scIdx06_TemperatureFR;
          break;
      case 7:
          p2Member = (uint8 *)p2Mir->tStrAcc.tCat06.sData.scIdx07_TemperatureRL;
          break;
      case 8:
          p2Member = (uint8 *)p2Mir->tStrAcc.tCat06.sData.scIdx08_TemperatureRR;
          break;
      case 9:
          p2Member = (uint8 *)p2Mir->tStrAcc.tCat06.sData.ucIdx09_Reserved;
          break;
      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 7:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat07.sData.ucReserved;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 8:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat08.sData.ucReserved;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 9:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat09.sData.ucReserved;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;
  case 10:
      switch(ui8Member)
      {
      case 1:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat10.sData.ucIdx01_NvInitialized ;
          break;
      case 2:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat10.sData.ucIdx02_ECUDefect ;
          break;
      case 3:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat10.sData.ucIdx03_Unused ;
          break;
      case 4:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat10.sData.ucIdx04_Unused ;
          break;

      default:
          p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
          break;
      }
      break;

  default:
      p2Member = (uint8 *) p2Mir ->tStrAcc .tCat01.sData.ucIdx01_WsIdWN ;
      break;
  }

  return ((uintptr ) p2Member );
}

static uint8 ui8GetMemberSizeInByte(uint8 ui8Cat, uint8 ui8Member)
{
   const uint8 ui8MembersInCat[NVM_MAX_CATEGORYS] = {
      NVM_CAT01_NUMBER_OF_MEMBERS,
                                                       NVM_CAT02_NUMBER_OF_MEMBERS
   ,     NVM_CAT03_NUMBER_OF_MEMBERS
   ,     NVM_CAT04_NUMBER_OF_MEMBERS
   ,     NVM_CAT05_NUMBER_OF_MEMBERS
   ,     NVM_CAT06_NUMBER_OF_MEMBERS
   ,     NVM_CAT07_NUMBER_OF_MEMBERS
   ,     NVM_CAT08_NUMBER_OF_MEMBERS
   ,     NVM_CAT09_NUMBER_OF_MEMBERS
   ,     NVM_CAT10_NUMBER_OF_MEMBERS
   };

   uint8 ui8TmpCat, ui8TmpMember;
   uint32 ui32CurMemberStartByte,ui32PostMemberStartByte;

   if((ui8Cat > sizeof(ui8MembersInCat)) || ((uint8) 0 == ui8Cat) || (ui8Member > ui8MembersInCat[ui8Cat-1]) || ((uint8) 0 == ui8Member))
   {
        return (0);
   }
   if(ui8MembersInCat[ui8Cat - 1] == ui8Member)
   {
      if((uint8)sizeof(ui8MembersInCat) == ui8Cat)
      {
        ui32PostMemberStartByte = sizeof(((MirrorType *) 0)->tBlAcc);
      }
      else{
          ui8TmpCat = ui8Cat + 1;
          ui8TmpMember = (uint8) 1;
          ui32PostMemberStartByte = ui32GetMemberStartByte (ui8TmpCat, ui8TmpMember);
      }
   }
   else{
      ui8TmpCat = ui8Cat;
      ui8TmpMember = ui8Member + 1;
      ui32PostMemberStartByte = ui32GetMemberStartByte (ui8TmpCat, ui8TmpMember);
   }

   ui32CurMemberStartByte = ui32GetMemberStartByte (ui8Cat , ui8Member );

    return ((uint8) ( 0xFF & (ui32PostMemberStartByte - ui32CurMemberStartByte) ) );
}

static uint8 ui8GetCatSizeInBlocks (uint8 ui8Categ)
{
   uint16 ui16CategSizeInByte = 0;

   switch(ui8Categ)
   {
   case 1:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat01);
        break;
   case 2:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat02);
        break;
   case 3:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat03);
        break;
   case 4:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat04);
        break;
   case 5:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat05);
        break;
   case 6:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat06);
        break;
   case 7:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat07);
        break;
   case 8:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat08);
        break;
   case 9:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat09);
        break;
   case 10:
        ui16CategSizeInByte = sizeof(((MirrorType *) 0)->tStrAcc.tCat10);
        break;

    default:
        break;
   }

    return((uint8) (ui16CategSizeInByte>>2));
}

void ReadBlock2Member(uint8 ui8Categ, uint8 ui8Member, uint8 * pui8Target)
{
  union
  {
    NVM_BLOCK_TYPE ulBlock[8];
   uint8 ui8ByteAcc[32];
  }tBuf;
  uint32 ui32StartByteNr = ui32GetMemberStartByte (ui8Categ,ui8Member);
  uint16 ui16BlockStartNr = (uint16) (ui32StartByteNr>>2);
  uint8 ui8ByteSize = ui8GetMemberSizeInByte (ui8Categ,ui8Member);
  uint8 ui8BlockLen = ui8ByteSize>>2;
  uint8 i;

  for(i= 0; i< sizeof(tBuf);i++)
  {
    tBuf.ui8ByteAcc[i] = 0;
  }

  if((ui32StartByteNr & 0x00000003) > 0)
  {
   ui8BlockLen ++;
  }
  else if((ui8ByteSize & ((uint8) 0x03)) > 0)
  {
   ui8BlockLen ++;
  }
  else{
  }

  (void) ClientIf_NvM_ReadBlock( ui16BlockStartNr, (uint16) ui8BlockLen, tBuf.ulBlock);

  if(ui8ByteSize != 0)
  {
    do
   {
      ui8ByteSize--;
      *(pui8Target+ui8ByteSize) = tBuf.ui8ByteAcc [(ui32StartByteNr & 0x00000003)+ui8ByteSize];
   }while(ui8ByteSize>0);
  }
}

void WriteMember2Blocks(uint8 ui8Categ, uint8 ui8Member, uint8 * pui8Target)
{
   union
   {
        NVM_BLOCK_TYPE ulBlock[8];
        uint8 ui8ByteAcc[32];
   }tBuf;
   uint32 ui32StartByteNr = ui32GetMemberStartByte (ui8Categ,ui8Member);
   uint16 ui16BlockStartNr = (uint16) (ui32StartByteNr>>2);
   uint8 ui8ByteSize = ui8GetMemberSizeInByte (ui8Categ,ui8Member);
   uint8 ui8BlockLen = ui8ByteSize>>2;
   uint8 ui8Write = (uint8) 0;
   uint8 i;
   for(i= 0; i< sizeof(tBuf);i++)
   {
      tBuf.ui8ByteAcc[i] = 0;
   }

   if((ui32StartByteNr & 0x00000003) > 0)
   {
      ui8BlockLen ++;
   }
   else if((ui8ByteSize & ((uint8) 0x03)) > 0)
   {
      ui8BlockLen ++;
   }
   else{
   }
    (void) ClientIf_NvM_ReadBlock( ui16BlockStartNr, (uint16) ui8BlockLen, tBuf.ulBlock);

   if(ui8ByteSize != 0)
   {
      do
      {
        ui8ByteSize--;
        if(*(pui8Target+ui8ByteSize) != tBuf.ui8ByteAcc [(ui32StartByteNr & 0x00000003)+ui8ByteSize])
        {
          tBuf.ui8ByteAcc [(ui32StartByteNr & 0x00000003)+ui8ByteSize] = *(pui8Target+ui8ByteSize);
          ui8Write = (uint8) 1;
        }
      }while(ui8ByteSize > 0);
   }

   if(ui8Write > 0)
   {
      (void) ClientIf_NvM_WriteBlock ( ui16BlockStartNr, (uint16) ui8BlockLen, tBuf.ulBlock);
   }
}

static void WriteCateg2Blocks(uint8 ui8Categ, NVM_BLOCK_TYPE * p2Target)
{
   uint32 ui32StartByteNr = ui32GetMemberStartByte (ui8Categ,1);
   uint16 ui16BlockStartNr = (uint16) (ui32StartByteNr>>2);
   uint8 ui8BlockLen = ui8GetCatSizeInBlocks (ui8Categ);

    (void) ClientIf_NvM_WriteBlock ( ui16BlockStartNr, (uint16) ui8BlockLen, p2Target);
}

void InitEEAll(void){
  struct struct_NvCat10 tTmpCat10;
  uint8 ucCateg = 0;

  ReadBlock2Member(10, 1, tTmpCat10.ucIdx01_NvInitialized);

  if(tTmpCat10.ucIdx01_NvInitialized[0] != NVM_INITIALIZED)
  {

   for(ucCateg = 0; ucCateg < NVM_MAX_CATEGORYS; ucCateg++)
   {

      arrInitEECatFunctions[ucCateg]();
   }
  }
}

static void InitEECat01(void){
   union union_NVM_Cat01 tTmpCat1;
   uint8 l_ucLauf;

   for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat1.sData.ucIdx01_WsIdWN);l_ucLauf++)
   {
        tTmpCat1.sData.ucIdx01_WsIdWN[l_ucLauf] = 0U;
   }
   for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat1.sData.ucIdx02_CdIdWN);l_ucLauf++)
   {
        tTmpCat1.sData.ucIdx02_CdIdWN[l_ucLauf] = 0U;
   }
   for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat1.sData.ucIdx03_WdIdWN);l_ucLauf++)
   {
        tTmpCat1.sData.ucIdx03_WdIdWN[l_ucLauf] = 0U;
   }
   for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat1.sData.ucIdx04_TsIdTM);l_ucLauf++)
   {
        tTmpCat1.sData.ucIdx04_TsIdTM[l_ucLauf] = 0U;
   }
   for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat1.sData.ucIdx05_CbIdTM);l_ucLauf++)
   {
        tTmpCat1.sData.ucIdx05_CbIdTM[l_ucLauf] = 0U;
   }
   for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat1.sData.ucIdx06_WarnTypeArrayIdWN);l_ucLauf++)
   {
        tTmpCat1.sData.ucIdx06_WarnTypeArrayIdWN[l_ucLauf] = 0U;
   }
   for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat1.sData.ucIdx07_ucResetWarnPressRef);l_ucLauf++)
   {
        tTmpCat1.sData.ucIdx07_ucResetWarnPressRef[l_ucLauf] = 0xFFU;
   }
   for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat1.sData.ucIdx08_ucPatmo);l_ucLauf++)
   {
        tTmpCat1.sData.ucIdx08_ucPatmo[l_ucLauf] = 40U;
   }

   for( l_ucLauf = 0; l_ucLauf < sizeof(tTmpCat1.sData.scIdx09_scAdaptedTref); l_ucLauf++)
   {
        tTmpCat1.sData.scIdx09_scAdaptedTref[l_ucLauf] = 0x14U;
   }
    WriteCateg2Blocks (1, tTmpCat1 .ulData32Bit .ulBlockAccess);
}

static void InitEECat02(void){
  union union_NVM_Cat02 tTmpCat2;
   uint8 l_ucLauf;

  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx01_ucReErrorStatuse);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx01_ucReErrorStatuse[l_ucLauf] = 0x00U;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx02_ucReHeatUpStatuse);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx02_ucReHeatUpStatuse[l_ucLauf] = 0x00U;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx03_ucFolgeAusfallCnt);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx03_ucFolgeAusfallCnt[l_ucLauf] = 0x00U;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx04_uiGutEmpfCnt);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx04_uiGutEmpfCnt[l_ucLauf] = 0x00U;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx05_uiMissedCnt);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx05_uiMissedCnt[l_ucLauf] = 0x00U;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx06_bRadwechsel);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx06_bRadwechsel[l_ucLauf] = FALSE;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx07_bHfIntLatch);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx07_bHfIntLatch[l_ucLauf] = FALSE;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx08_ucStatusEOLRoutine);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx08_ucStatusEOLRoutine[l_ucLauf] = 0xFFU;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx09_ucIsEOLRoutineActive);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx09_ucIsEOLRoutineActive[l_ucLauf] = 0x00;
  }

  tTmpCat2.sData.ucIdx10_DTCActiveStatus[0] = cDTC_IS_CLEARED;

  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx11_DTCSingleActiveStatus);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx11_DTCSingleActiveStatus[l_ucLauf] = cDTC_IS_CLEARED;
  }

  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat2.sData.ucIdx12_Unused);l_ucLauf++)
  {
    tTmpCat2.sData.ucIdx12_Unused[l_ucLauf] = 0x00U;
  }

  WriteCateg2Blocks (2, tTmpCat2.ulData32Bit.ulBlockAccess);
}

static void InitEECat03(void){
  union union_NVM_Cat03 tTmpCat3;
   uint8  l_ucLauf;
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat3.sData.ucIdx01_HistoryID);l_ucLauf++)
  {
    tTmpCat3.sData.ucIdx01_HistoryID[l_ucLauf] = 0x00U;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat3.sData.ucIdx02_HistoryWP);l_ucLauf++)
  {
    tTmpCat3.sData.ucIdx02_HistoryWP[l_ucLauf] = 0x00U;
  }

  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat3.sData.ucIdx03_WA_Parameter);l_ucLauf++)
  {
    tTmpCat3.sData.ucIdx03_WA_Parameter[l_ucLauf] = 0x00U;
  }

  tTmpCat3.sData.ucIdx04_WA_ABSTicksInOneRev[0] = cDefaultABSCountNr;
  tTmpCat3.sData.ucIdx04_WA_ABSTicksInOneRev[1] = cDefaultABSCountNr;
  tTmpCat3.sData.ucIdx05_ucVarAutolocationFailedCounter[0] = ucDefAutolocationFailedCounterInit;
  tTmpCat3.sData.ucIdx06_Unused[0] = 0;
  tTmpCat3.sData.ucIdx07_Unused[0] = 0;
  tTmpCat3.sData.ucIdx08_Unused[0] = 0;

  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat3.sData.ucIdx09_Test);l_ucLauf++)
  {
    tTmpCat3.sData.ucIdx09_Test[l_ucLauf] = 0x00U;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat3.sData.ucIdx10_Test);l_ucLauf++)
  {
    tTmpCat3.sData.ucIdx10_Test[l_ucLauf] = 0x00U;
  }
  for(l_ucLauf = 0U; l_ucLauf < sizeof(tTmpCat3.sData.ucIdx11_Test);l_ucLauf++)
  {
    tTmpCat3.sData.ucIdx11_Test[l_ucLauf] = 0x00U;
  }

  WriteCateg2Blocks (3, tTmpCat3 .ulData32Bit .ulBlockAccess);
}

static void InitEECat04(void){
   union union_NVM_Cat04 tTmpCat4;

    tTmpCat4.sData.ucIdx01_CcpCrcFilter  [ 0] = FALSE;
    tTmpCat4.sData.ucIdx02_CcpIdFilter   [ 0] = FALSE;
    tTmpCat4.sData.ucIdx03_CcpAnzIdFilter[ 0] = 1U;
    tTmpCat4.sData.ucIdx04_CcpOnOff      [ 0] = 1U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 0] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 1] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 2] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 3] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 4] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 5] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 6] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 7] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 8] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [ 9] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [10] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [11] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [12] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [13] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [14] = 0U;
    tTmpCat4.sData.ucIdx05_CcpFilterIds  [15] = 0U;

    WriteCateg2Blocks(4,tTmpCat4.ulData32Bit .ulBlockAccess );
}

static void InitEECat05(void){
   union union_NVM_Cat05 tTmpCat5;
   uint8 i;

  for( i = 0; i < sizeof(tTmpCat5 .sData.ucIdx01_ucVarCodLegislation); i++)
  {
        tTmpCat5 .sData.ucIdx01_ucVarCodLegislation[i] = (uint8) E_US_LEG_NON_EXTRA_LOAD_TIRES;
  }

  tTmpCat5.sData.ucIdx02_ucVarCodHighPressResetThres[0] = ucHystHiPc;
  tTmpCat5.sData.ucIdx03_ucVarCodTemperatureWarningThres[0] = (uint8) scTemperatureWarningThresholdDefault;
  tTmpCat5.sData.ucIdx04_ucVarCodOffroadPlacardPress[0] = u8_Us_NonExtra_Offroad_Press_digits;

  for(i = 0U; i < sizeof(tTmpCat5.sData.ucIdx05_ucVarCodPlacardPress);i++)
  {
      tTmpCat5.sData.ucIdx05_ucVarCodPlacardPress[i] = 0x84U;
  }
  for(i = 0U; i < sizeof(tTmpCat5.sData.ucIdx06_ucVarCodMinPressThres);i++)
  {
      tTmpCat5.sData.ucIdx06_ucVarCodMinPressThres[i] = u8_US_NonExtra_MinPrs_digits;
  }
  for(i = 0U; i < sizeof(tTmpCat5.sData.ucIdx07_ucVarCodHighPressThres);i++)
  {
      tTmpCat5.sData.ucIdx07_ucVarCodHighPressThres[i] = 0x86U;
  }
  for(i = 0U; i < sizeof(tTmpCat5.sData.ucIdx08_ucVarCodAxImbSetThres);i++)
  {
      tTmpCat5.sData.ucIdx08_ucVarCodAxImbSetThres[i] = 0x0EU;
  }
  for(i = 0U; i < sizeof(tTmpCat5.sData.ucIdx09_ucVarCodAxImbResThres);i++)
  {
      tTmpCat5.sData.ucIdx09_ucVarCodAxImbResThres[i] = 0x08U;
  }
  for( i = 0; i < sizeof(tTmpCat5 .sData.ucReserved); i++)
  {
        tTmpCat5 .sData.ucReserved[i] = 0x05U;
  }

    WriteCateg2Blocks(5,tTmpCat5.ulData32Bit .ulBlockAccess );
}

static void InitEECat06(void){
   union union_NVM_Cat06 tTmpCat6;
   uint8 i;

    tTmpCat6.sData.ucIdx01_PressureFL[0] = 0xff;
    tTmpCat6.sData.ucIdx02_PressureFR[0] = 0xff;
    tTmpCat6.sData.ucIdx03_PressureRL[0] = 0xff;
    tTmpCat6.sData.ucIdx04_PressureRR[0] = 0xff;
    tTmpCat6.sData.scIdx05_TemperatureFL[0] = 0xff;
    tTmpCat6.sData.scIdx06_TemperatureFR[0] = 0xff;
    tTmpCat6.sData.scIdx07_TemperatureRL[0] = 0xff;
    tTmpCat6.sData.scIdx08_TemperatureRR[0] = 0xff;

   for( i = 0; i < sizeof(tTmpCat6 .sData.ucIdx09_Reserved); i++)
   {
        tTmpCat6.sData.ucIdx09_Reserved[i] = 0x06U;
   }

    WriteCateg2Blocks(6,tTmpCat6.ulData32Bit .ulBlockAccess );
}

static void InitEECat07(void){
   union union_NVM_Cat07 tTmpCat7;
   uint8 i;

   for( i = 0; i < sizeof(tTmpCat7 .sData.ucReserved); i++)
   {
        tTmpCat7.sData.ucReserved[i] = 0x07U;
   }

    WriteCateg2Blocks(7,tTmpCat7.ulData32Bit .ulBlockAccess );
}

static void InitEECat08(void){
   union union_NVM_Cat08 tTmpCat8;
   uint8 i;

   for( i = 0; i < sizeof(tTmpCat8 .sData.ucReserved); i++)
   {
        tTmpCat8.sData.ucReserved[i] = 0x08U;
   }

    WriteCateg2Blocks(8,tTmpCat8.ulData32Bit .ulBlockAccess );
}

static void InitEECat09(void){
   union union_NVM_Cat09 tTmpCat9;
   uint8 i;

   for( i = 0; i < sizeof(tTmpCat9 .sData.ucReserved); i++)
   {
        tTmpCat9.sData.ucReserved[i] = 0x09U;
   }

    WriteCateg2Blocks(9,tTmpCat9.ulData32Bit .ulBlockAccess );
}

static void InitEECat10(void){
   union union_NVM_Cat10 tTmpCat10;

    tTmpCat10.sData .ucIdx02_ECUDefect[0] = 0x00U;
    tTmpCat10.sData .ucIdx03_Unused[0] = 0x00U;
    tTmpCat10.sData .ucIdx04_Unused[0] = 0x00U;
    tTmpCat10.sData .ucIdx01_NvInitialized[0] = NVM_INITIALIZED ;

    WriteCateg2Blocks(10,tTmpCat10.ulData32Bit .ulBlockAccess );
}

void EE_InconsistencyHandling(uint16 uiNvmCategoryConsistence)
{
  uint8 ucCateg = 0;

  for(ucCateg = 0; ucCateg < NVM_MAX_CATEGORYS; ucCateg++)
  {
   if(0 == (uiNvmCategoryConsistence & ((uint16)1<<ucCateg)))
   {

      arrInitEECatFunctions[ucCateg]();
   }
  }
}
