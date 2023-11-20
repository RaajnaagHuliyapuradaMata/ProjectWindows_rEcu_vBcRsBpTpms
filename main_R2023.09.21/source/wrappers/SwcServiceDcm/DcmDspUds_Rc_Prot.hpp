

#ifndef DCMDSPUDS_RC_PROT_H
#define DCMDSPUDS_RC_PROT_H

#if(DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)

#define 	DCM_RC_STARTROUTINE 		1u
#define 	DCM_RC_STOPROUTINE			2u
#define 	DCM_RC_REQUESTRESULTS		3u

#define 	DCM_RC_INVLDSIGINDEX		0u

#define DSP_RC_MINREQLEN            0x03u
#define DSP_RC_SUBFUNCTION_ONE      0x01u
#define DSP_RC_SUBFUNCTION_THREE    0x03u

typedef enum{
    DCM_RC_IDLE = 1
   ,   DCM_RC_PENDING
   ,   DCM_RC_CANCEL
}Dcm_DspRCStateType_ten;

typedef struct{
   uint16 posnStart_u16;
   uint16 dataLength_u16;
   uint16 idxSignal_u16;
   uint8 dataEndianness_u8;
   uint8 dataType_u8;
}Dcm_DspRoutineSignalInfo_tst;

typedef struct{
   uint32  dataSecBitMask_u32;
   uint32  dataSessBitMask_u32;
   P2FUNC(Std_ReturnType,TYPEDEF,adrUserRidModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint16,AUTOMATIC),VAR(uint8,AUTOMATIC));
#if((DCM_CFG_DSP_MODERULEFORROUTINES !=DCM_CFG_OFF) || (DCM_CFG_DSP_MODERULEFORRCRANGE!=DCM_CFG_OFF))
   P2FUNC(boolean,TYPEDEF,adrModeRuleForStart_pfct) (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA));
   P2FUNC(boolean,TYPEDEF,adrModeRuleForStop_pfct) (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA));
   P2FUNC(boolean,TYPEDEF,adrModeRuleForRequestResult_pfct) (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA));
#endif
   CONSTP2CONST(Dcm_DspRoutineSignalInfo_tst, TYPEDEF, DCM_INTERN_CONST) adrStartInSignalRef_cpcst;
   CONSTP2CONST(Dcm_DspRoutineSignalInfo_tst, TYPEDEF, DCM_INTERN_CONST) adrStopInSignalRef_cpcst;
   CONSTP2CONST(Dcm_DspRoutineSignalInfo_tst, TYPEDEF, DCM_INTERN_CONST) adrReqRslInSignalRef_cpcst;
   CONSTP2CONST(Dcm_DspRoutineSignalInfo_tst, TYPEDEF, DCM_INTERN_CONST) adrStartOutSignalRef_cpcst;
   CONSTP2CONST(Dcm_DspRoutineSignalInfo_tst, TYPEDEF, DCM_INTERN_CONST) adrStopOutSignalRef_cpcst;
   CONSTP2CONST(Dcm_DspRoutineSignalInfo_tst, TYPEDEF, DCM_INTERN_CONST) adrReqRsltOutSignalRef_cpcst;
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
}Dcm_DspRoutineInfoType_tst;

typedef enum{
   DCM_ROUTINE_IDLE
   ,  DCM_ROUTINE_STOP
   ,  DCM_ROUTINE_STARTED
   ,  DCM_ROUTINE_STOP_PENDING
}Dcm_DspRoutineStatusType_ten;

#if(DCM_CFG_RC_NUMRIDS > 0u)
#if(DCM_CFG_DSP_NUMISRIDAVAIL > 0)
typedef P2FUNC(Std_ReturnType,TYPEDEF,IsRIDAvailFnc_pf) (VAR(uint16,AUTOMATIC) RID_u16);
#endif
typedef struct{
   uint16    	dataRId_u16;
   boolean   	dataFixedLen_b;
   boolean   	UsePort;
#if(DCM_CFG_DSP_NUMISRIDAVAIL>0)
   uint16      idxRIDSupportedFnc_u16;
#endif
   CONSTP2CONST(Dcm_DspRoutineInfoType_tst, TYPEDEF, DCM_INTERN_CONST) adrRoutineInfoRef_cpcst;
   P2FUNC(Std_ReturnType, TYPEDEF, adrCallRoutine_pfct) ( VAR(uint8, AUTOMATIC) ) ;
   boolean     flgStartRoutine_b;
   boolean     flgStopRoutine_b;
   boolean     flgStopRoutineOnSessionChange_b;
   boolean     flgReqSequenceErrorSupported_b;
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)

   uint8 		dataConfigMask_u8;
#endif
   boolean		dataReqRslt_b;
}Dcm_DspRoutineType_tst;
#endif

#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)

typedef struct{
  boolean RoutineRangeHasGaps_b;
  boolean RoutineRangeUsePort_b;
  boolean flgReqRsltRoutine_b;
  boolean flgStartRoutine_b;
  boolean flgStopRoutine_b;
  boolean dataFixedLen_b;
  boolean flgStopRoutineOnSessionChange_b;
  boolean flgReqSequenceErrorSupported_b;
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
  uint8  dataConfigMask_u8;
#endif
  uint16 RidRangeUpperLimit_u16;
  uint16 RidRangeLowerLimit_u16;
  P2FUNC(Std_ReturnType,TYPEDEF,IsRIDRangeAvailFnc_pf) (VAR(uint16,AUTOMATIC),P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA));
  P2FUNC(Std_ReturnType,TYPEDEF,adrCallRoutine_pfct)(VAR(uint8,AUTOMATIC));
  CONSTP2CONST(Dcm_DspRoutineInfoType_tst, TYPEDEF, DCM_INTERN_CONST) adrRoutineInfoRef_cpcst;
}Dcm_DspRoutineRangeType_tst;
#endif

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RC_NUMRIDS > 0u)
extern VAR(Dcm_DspRoutineStatusType_ten, DCM_VAR) Dcm_RoutineStatus_aen[DCM_CFG_RC_NUMRIDS];
#endif
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
extern VAR(Dcm_DspRoutineStatusType_ten, DCM_VAR) Dcm_RoutineRangeStatus_aen[DCM_CFG_RC_RANGE_NUMRIDS];
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_RC_NUMRIDS > 0u)
#if(DCM_CFG_DSP_NUMISRIDAVAIL>0)
extern CONST (IsRIDAvailFnc_pf,DCM_CONST) Dcm_RIDIsAvail[DCM_CFG_DSP_NUMISRIDAVAIL];
#endif
extern CONST(Dcm_DspRoutineType_tst, DCM_CONST) Dcm_DspRoutine_cast[DCM_CFG_RC_NUMRIDS];
#endif
#if(DCM_CFG_RC_RANGE_NUMRIDS > 0u)
extern CONST(Dcm_DspRoutineRangeType_tst, DCM_CONST) Dcm_DspRoutineRange_cast[DCM_CFG_RC_RANGE_NUMRIDS];
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_NegativeResponseCodeType,DCM_VAR) 						Dcm_RCNegResCode_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(uint16,DCM_VAR) 											Dcm_RCCurrDataLength_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern VAR(Dcm_OpStatusType,DCM_VAR)									Dcm_RCOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern P2VAR(uint8,DCM_VAR,DCM_INTERN_DATA) 							Dcm_RCInPtr_pu8;
extern P2VAR(uint8,DCM_VAR,DCM_INTERN_DATA) 							Dcm_RCOutPtr_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern FUNC(uint32,DCM_CODE) Dcm_RCGetSigVal_u32 ( VAR(uint8,AUTOMATIC) dataSigType_en, VAR(uint16,AUTOMATIC) idxSignalIndex_u16);
extern FUNC(void,DCM_CODE) Dcm_RCSetSigVal ( VAR(uint8,AUTOMATIC) dataSigType_en, VAR(uint16,AUTOMATIC) idxSignalIndex_u16, VAR(uint32,AUTOMATIC) dataSigVal_u32);
extern FUNC(void,DCM_CODE) Dcm_RoutineSetSesCtrlType (VAR(Dcm_SesCtrlType, AUTOMATIC) dataSesCtrlType_u8);
extern FUNC(void, DCM_CODE) Dcm_Lok_DspRCConfirmation(
   VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
   											   );
#if(DCM_CFG_ROUTINEARRAY_INSIG != DCM_CFG_OFF)
extern FUNC(void,DCM_CODE) Dcm_RcSetSignalArray(P2CONST(Dcm_DspRoutineSignalInfo_tst, AUTOMATIC, DCM_INTERN_DATA) adrSignal_pcst,P2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) adrReqBuffer_u8);
#endif
#if(DCM_CFG_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF)
extern FUNC(void,DCM_CODE) Dcm_RcStoreSignalArray(P2CONST(Dcm_DspRoutineSignalInfo_tst, AUTOMATIC, DCM_INTERN_DATA) adrSignal_pcst,P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) adrResBuffer_u8);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

