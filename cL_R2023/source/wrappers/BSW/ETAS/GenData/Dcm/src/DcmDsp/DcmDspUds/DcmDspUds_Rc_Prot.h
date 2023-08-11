

#ifndef DCMDSPUDS_RC_PROT_H
#define DCMDSPUDS_RC_PROT_H

#if (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)

#define 	DCM_RC_STARTROUTINE 		1u
#define 	DCM_RC_STOPROUTINE			2u
#define 	DCM_RC_REQUESTRESULTS		3u

#define 	DCM_RC_INVLDSIGINDEX		0u

#define     DSP_RC_MINREQLEN            0x03u
#define     DSP_RC_SUBFUNCTION_ONE      0x01u
#define     DSP_RC_SUBFUNCTION_THREE    0x03u

typedef enum
{
    DCM_RC_IDLE = 1,
    DCM_RC_PENDING,
    DCM_RC_CANCEL
}Dcm_DspRCStateType_ten;

typedef struct{
    uint16 posnStart_u16;
    uint16 dataLength_u16;
    uint16 idxSignal_u16;
    uint8 dataEndianness_u8;
    uint8 dataType_u8;
} Dcm_DspRoutineSignalInfo_tst;

typedef struct{
    uint32  dataSecBitMask_u32;
    uint32  dataSessBitMask_u32;
    Std_ReturnType (*adrUserRidModeRule_pfct) (Dcm_NegativeResponseCodeType *dataNegRespCode ,uint16 dataRId_u16 ,uint8 dataSubFunc_u8);
#if((DCM_CFG_DSP_MODERULEFORROUTINES !=DCM_CFG_OFF) || (DCM_CFG_DSP_MODERULEFORRCRANGE!=DCM_CFG_OFF))
    boolean (*adrModeRuleForStart_pfct) (uint8 *dataNegRespCode_u8 );
    boolean (*adrModeRuleForStop_pfct) (uint8 *dataNegRespCode_u8 );
    boolean (*adrModeRuleForRequestResult_pfct) (uint8 *dataNegRespCode_u8 );
#endif
	const Dcm_DspRoutineSignalInfo_tst * const adrStartInSignalRef_cpcst;
	const Dcm_DspRoutineSignalInfo_tst * const adrStopInSignalRef_cpcst;
	const Dcm_DspRoutineSignalInfo_tst * const adrReqRslInSignalRef_cpcst;
	const Dcm_DspRoutineSignalInfo_tst * const adrStartOutSignalRef_cpcst;
	const Dcm_DspRoutineSignalInfo_tst * const adrStopOutSignalRef_cpcst;
	const Dcm_DspRoutineSignalInfo_tst * const adrReqRsltOutSignalRef_cpcst;
	uint16   	dataCtrlOptRecSizeStart_u16;
	uint16   	dataCtrlOptRecSizeStop_u16;
	uint16   	dataCtrlOptRecSizeReqRslt_u16;
	uint16   	dataStsOptRecSizeStart_u16;
	uint16   	dataStsOptRecSizeStop_u16;
	uint16   	dataStsOptRecSizeReqRslt_u16;
	uint16  	dataMinCtrlOptRecSizeStart_u16;
	uint16   	dataMinCtrlOptRecSizeStop_u16;
	uint16   	dataMinCtrlOptRecSizeReqRslt_u16;
	uint16  	dataMinStsOptRecSizeStart_u16;
	uint16  	dataMinStsOptRecSizeStop_u16;
	uint16  	dataMinStsOptRecSizeReqRslt_u16;
	uint8		nrStartInSignals_u8;
	uint8		nrStopInSignals_u8;
	uint8		nrReqRslInSignals_u8;
	uint8		nrStartOutSignals_u8;
	uint8		nrStopOutSignals_u8;
	uint8		nrReqRsltOutSignals_u8;
} Dcm_DspRoutineInfoType_tst;

typedef enum {
	DCM_ROUTINE_IDLE,
	DCM_ROUTINE_STOP,
	DCM_ROUTINE_STARTED,
	DCM_ROUTINE_STOP_PENDING
}Dcm_DspRoutineStatusType_ten;

#if (DCM_CFG_RC_NUMRIDS > 0u)
#if(DCM_CFG_DSP_NUMISRIDAVAIL > 0)
typedef Std_ReturnType (*IsRIDAvailFnc_pf) (uint16 RID_u16);
#endif
typedef struct{
    uint16    	dataRId_u16;
	boolean   	dataFixedLen_b;
	boolean   	UsePort;
#if(DCM_CFG_DSP_NUMISRIDAVAIL>0)
	uint16      idxRIDSupportedFnc_u16;
#endif
	const Dcm_DspRoutineInfoType_tst * const adrRoutineInfoRef_cpcst;
	Std_ReturnType (*adrCallRoutine_pfct) ( uint8 Dcm_dataRCSubFunc_u8 ) ;
	boolean     flgStartRoutine_b;
	boolean     flgStopRoutine_b;
	boolean     flgStopRoutineOnSessionChange_b;
	boolean     flgReqSequenceErrorSupported_b;
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)

	uint8 		dataConfigMask_u8;
#endif
	boolean		dataReqRslt_b;
} Dcm_DspRoutineType_tst;
#endif

#if (DCM_CFG_RC_RANGE_NUMRIDS > 0u)

typedef struct{
  boolean RoutineRangeHasGaps_b;
  boolean RoutineRangeUsePort_b;
  boolean flgReqRsltRoutine_b;
  boolean flgStartRoutine_b;
  boolean flgStopRoutine_b;
  boolean dataFixedLen_b;
  boolean flgStopRoutineOnSessionChange_b;
  boolean flgReqSequenceErrorSupported_b;
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
  uint8  dataConfigMask_u8;
#endif
  uint16 RidRangeUpperLimit_u16;
  uint16 RidRangeLowerLimit_u16;
  Std_ReturnType (*IsRIDRangeAvailFnc_pf) (uint16 dataRId_u16 ,Dcm_NegativeResponseCodeType * NRC);
  Std_ReturnType (*adrCallRoutine_pfct) (uint8 Dcm_dataRCSubFunc_u8);
  const Dcm_DspRoutineInfoType_tst * const adrRoutineInfoRef_cpcst;
} Dcm_DspRoutineRangeType_tst;
#endif

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#if (DCM_CFG_RC_NUMRIDS > 0u)
extern Dcm_DspRoutineStatusType_ten Dcm_RoutineStatus_aen[DCM_CFG_RC_NUMRIDS];
#endif
#if (DCM_CFG_RC_RANGE_NUMRIDS > 0u)
extern Dcm_DspRoutineStatusType_ten Dcm_RoutineRangeStatus_aen[DCM_CFG_RC_RANGE_NUMRIDS];
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if (DCM_CFG_RC_NUMRIDS > 0u)
#if(DCM_CFG_DSP_NUMISRIDAVAIL>0)
extern const IsRIDAvailFnc_pf Dcm_RIDIsAvail[DCM_CFG_DSP_NUMISRIDAVAIL];
#endif
extern const Dcm_DspRoutineType_tst Dcm_DspRoutine_cast[DCM_CFG_RC_NUMRIDS];
#endif
#if (DCM_CFG_RC_RANGE_NUMRIDS > 0u)
extern const Dcm_DspRoutineRangeType_tst Dcm_DspRoutineRange_cast[DCM_CFG_RC_RANGE_NUMRIDS];
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern Dcm_NegativeResponseCodeType Dcm_RCNegResCode_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
extern uint16 Dcm_RCCurrDataLength_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern Dcm_OpStatusType Dcm_RCOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern uint8 * Dcm_RCInPtr_pu8;
extern uint8 * Dcm_RCOutPtr_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern uint32 Dcm_RCGetSigVal_u32 ( uint8 dataSigType_en, uint16 idxSignalIndex_u16);
extern void Dcm_RCSetSigVal ( uint8 dataSigType_en, uint16 idxSignalIndex_u16, uint32 dataSigVal_u32);
extern void Dcm_RoutineSetSesCtrlType (Dcm_SesCtrlType dataSesCtrlType_u8);
extern void Dcm_Lok_DspRCConfirmation(
	Dcm_IdContextType dataIdContext_u8,
	PduIdType dataRxPduId_u8,
	uint16 dataSourceAddress_u16,
	Dcm_ConfirmationStatusType status_u8
												   );
#if ((DCM_CFG_ROUTINEARRAY_INSIG != DCM_CFG_OFF) || (DCM_CFG_RCRANGE_ROUTINEARRAY_INSIG != DCM_CFG_OFF))
extern void Dcm_RcSetSignalArray(const Dcm_DspRoutineSignalInfo_tst * adrSignal_pcst,const uint8 * adrReqBuffer_u8);
#endif
#if((DCM_CFG_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF))
extern void Dcm_RcStoreSignalArray(const Dcm_DspRoutineSignalInfo_tst * adrSignal_pcst,uint8 * adrResBuffer_u8);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif

