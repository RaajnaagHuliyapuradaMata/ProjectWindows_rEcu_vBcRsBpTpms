#ifndef HUF_NVM_IF_HEADER_
#define HUF_NVM_IF_HEADER_
#include "WallocX.hpp"

#define NVM_INITIALIZED 0xAAU
#define CATEGORY1     1U
#define CATEGORY2     2U
#define CATEGORY3     3U
#define CATEGORY4     4U
#define CATEGORY5     5U
#define CATEGORY6     6U
#define CATEGORY7     7U
#define CATEGORY8     8U
#define CATEGORY9     9U
#define CATEGORY10    10U
#define INDEX1      1U
#define INDEX2      2U
#define INDEX3      3U
#define INDEX4      4U
#define INDEX5      5U
#define INDEX6      6U
#define INDEX7      7U
#define INDEX8      8U
#define INDEX9      9U
#define INDEX10     10U
#define INDEX11     11U
#define INDEX12     12U
#define INDEX13     13U
#define cHistorySet1    1U
#define cHistoryWPSet1  2U
#define cWAParameter    3U
#define cWAABSTicksInOneRevolution 4U

extern uint8  GETucResetWarnPresLimitEE(void);
extern uint8  GETucPSollMinVaEE(void);
extern uint8  GETucPSollMinHaEE(void);
extern uint16 GETushSuppIdentFilterEE(void);
extern uint16 GETusMaxFolgeAusfallEE(void);
extern uint8  GETucTimeTransmitIntervalCompletePeriodEE(void);
extern uint8  GETucMinOffsetGXeEE(void);
extern uint8  GETucOffsetOverlapsGXeEE(void);
extern uint8   GETucResetWarnPressRefEE(uint8 ucIndex);
extern void    PUTucResetWarnPressRefEE(uint8 ucIndex, uint8 ucData);
extern void    PUTucPatmoEE(uint8 ucData);
extern uint8   GETucPatmoEE (void);
extern void    PUTscAdaptedTrefEE(sint8 scData);
extern sint8   GETscAdaptedTrefEE(void);
extern void    PUTucReErrorStatusEE(uint8 ucData);
extern uint8   GETucReErrorStatusEE(void);
extern void    PUTucReHeatUpStatusEE(uint8 ucData);
extern uint8   GETucReHeatUpStatusEE(void);
extern void    PUTusFolgeAusfallCntEE(uint16 ucValue, uint8 ucSlot);
extern uint16  GETusFolgeAusfallCntEE(uint8 ucSlot);
extern void    PUTushGutEmpfCntEE(uint16 uiData, uint8 ucSlot);
extern uint16  GETushGutEmpfCntEE(uint8 ucSlot);
extern void    PUTushMissedCntEE(uint16 uiData, uint8 ucSlot);
extern uint16  GETushMissedCntEE(uint8 ucSlot);
extern void    PUTbHfIntLatchEE(uint8 ucData);
extern boolean GETbHfIntLatchEE(void);
extern void    NvM2_PutEOLRoutineStatusEE(uint8 ucData);
extern uint8   NvM2_GetEOLRoutineStatusEE(void);
extern void    NvM2_PutEOLRoutineActiveEE(uint8 ucData);
extern uint8   NvM2_GetEOLRoutineActiveEE(void);
extern void    NvM2_PutDiagUsedToDeleteDTCEE(uint8 ucData);
extern uint8   NvM2_GetDiagUsedToDeleteDTCEE(void);
extern void    NvM2_PutDTCSingleActiveStatusEE(uint8* u8BufferForStatus);
extern void    NvM2_GetDTCSingleActiveStatusCEE(uint8* u8BufferForStatus);
extern void NvM3_PUTHistoryIdsInEE(uint32 *ulData);
extern void NvM3_GETHistoryIdsFromEE(uint32 *ulData);
extern void NvM3_PUTHistoryWPInEE(uint8 *ucData);
extern void NvM3_GETHistoryWPFromEE(uint8 *ucData);
extern void NvM3_PUTWAParametersInEE(WAParameter sWheelAllocParamData);
extern void NvM3_GETWAParametersFromEE(WAParameter *sWheelAllocParamData);
extern void NvM3_PUTABSTicksInEE(WAABSTicksInOneRevolution sABSTicks);
extern void NvM3_GETABSTicksFromEE(WAABSTicksInOneRevolution *sABSTicks);
extern void NvM3_PUTucAutolocationFailedCounter(uint8 ucCounterValue);
extern uint8 NvM3_GETucAutolocationFailedCounter(void);
extern void GetWADataEE(unsigned char ucId, unsigned char *pRamAdr);
extern void PutWADataEE(unsigned char ucId, unsigned char *pRamAdr);
extern void    PUTucVarCodLegislationEE(uint8 ucData);
extern uint8   GETucVarCodLegislationEE(void);
extern void NvM3_PUTucVarCodHighPressResetThresEE(uint8 ucData);
extern uint8 NvM3_GETucVarCodHighPressResetThresEE(void);
extern void NvM3_PUTucVarCodTemperatureWarningThresEE(sint8 scData);
extern sint8 NvM3_GETucVarCodTemperatureWarningThresEE(void);
extern void NvM3_PUTucVarCodOffroadPlacardPress(uint8 ucData);
extern uint8 NvM3_GETucVarCodOffroadPlacardPress(void);
extern void    PUTucVarCodPlacardPressEE(uint8 ucData);
extern uint8   GETucVarCodPlacardPressEE (void);
extern void    PUTucVarCodMinPressThresEE(uint8 ucData);
extern uint8   GETucVarCodMinPressThresEE(void);
extern void    PUTucVarCodHighPressThresEE(uint8 ucData);
extern uint8   GETucVarCodHighPressThresEE(void);
extern void    PUTucVarCodAxImbSetThresEE(uint8 ucData);
extern uint8   GETucVarCodAxImbSetThresEE(void);
extern void    PUTucVarCodAxImbResThresEE(uint8 ucData);
extern uint8   GETucVarCodAxImbResThresEE(void);
extern void NvM_WriteData_PressureFL(uint8 ucData);
extern void NvM_ReadData_PressureFL(uint8 *ucpData);
extern void NvM_WriteData_PressureFR(uint8 ucData);
extern void NvM_ReadData_PressureFR(uint8 *ucpData);
extern void NvM_WriteData_PressureRL(uint8 ucData);
extern void NvM_ReadData_PressureRL(uint8 *ucpData);
extern void NvM_WriteData_PressureRR(uint8 ucData);
extern void NvM_ReadData_PressureRR(uint8 *ucpData);
extern void NvM_WriteData_TemperatureFL(uint8 ucData);
extern void NvM_ReadData_TemperatureFL(uint8 *ucpData);
extern void NvM_WriteData_TemperatureFR(uint8 ucData);
extern void NvM_ReadData_TemperatureFR(uint8 *ucpData);
extern void NvM_WriteData_TemperatureRL(uint8 ucData);
extern void NvM_ReadData_TemperatureRL(uint8 *ucpData);
extern void NvM_WriteData_TemperatureRR(uint8 ucData);
extern void NvM_ReadData_TemperatureRR(uint8 *ucpData);
extern void    NvM_WriteData_ECUDefect(uint8 ucData);
extern void    NvM_ReadData_ECUDefect(uint8 *ucpData);

#endif

