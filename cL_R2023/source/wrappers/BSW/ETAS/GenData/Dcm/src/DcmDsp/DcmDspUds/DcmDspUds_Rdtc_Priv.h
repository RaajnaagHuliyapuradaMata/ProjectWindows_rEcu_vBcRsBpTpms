

#ifndef DCMDSPUDS_RDTC_PRIV_H
#define DCMDSPUDS_RDTC_PRIV_H

#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)

#define DSP_RDTC_MINREQLEN                   0x01u
#define DSP_RDTC_POSSUBFUNC                  0x00u
#define DSP_REPDTCBYSTMASK_REQLEN            0x02u
#define DSP_REPDTCBYSEVMASK_REQLEN           0x03u
#define DSP_RDTC_0A_15_REQLEN                0x01u
#define DSP_RDTC_LSH_16BITS                  0x10u
#define DSP_RDTC_LSH_08BITS                  0x08u
#define DSP_REPORT_ALL_DTC                   0x00u

#define DCM_DSP_RDTC_SUBFUNCTION                  0x00u
#define DCM_DSP_RDTC_HIGHBYTE                     0x01u
#define DCM_DSP_RDTC_MIDDLEBYTE                   0x02u
#define DCM_DSP_RDTC_LOWBYTE                      0x03u
#define DCM_DSP_RDTC_EXTENDEDDATARECORDNUMBER     0x04u
#define DCM_DSP_RDTC_MEMORYSELECTION              0x05u
#define DCM_DTC_ORIGIN_MEMORY_SELECTION_VALUE     0x0100u
#define DCM_DSP_RDTC_STATUSOFDTC                  0x04u

#define DSP_REPORT_DTC_PERMANENT_STATUS      0x15u
#define DSP_REPORT_SUPPORTED_DTCS            0x0Au
#define DSP_REPORT_DTC_BY_STATUS_MASK        0x02u
#define DSP_REPORT_DTC_BY_SEVERITY_MASK      0x08u
#define DSP_REPORT_NUM_STATUS_MASK_DTC       0x01u
#define DSP_REPORT_NUM_MIRROR_DTC            0x11u
#define DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK      0x17u

#define DSP_REPORT_NUM_EMISSION_DTC          0x12u

#define DSP_REPORT_NUM_SEVERMASK_DTC         0x07u
#define DSP_REPORT_DTC_SNAPSHOT_RECORD       0x03u
#define DSP_REPORT_MIRROR_MEMORY_DTC         0x0Fu
#define DSP_REPORT_EXTENDED_REC_MIRROR_MEM   0x10u
#define DSP_REPORT_EXTENDED_DATA_RECORD      0x06u
#define DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER     0x19u
#define DSP_REPORT_SNAPSHOT_RECORD_BY_DTC    0x04u
#define DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER    0x18u

#define DSP_REPORT_OBD_DTC_BY_STATUS_MASK    0x13u

#define DSP_REPORT_DTC_FAULT_DETECTION_COUNTER    0x14u
#define DSP_REPORT_FIRST_TEST_FAILED_DTC		  0x0Bu
#define DSP_REPORT_FIRST_CONFIRMED_DTC	          0x0Cu
#define DSP_REPORT_MOST_RECENT_TEST_FAILED_DTC	  0x0Du
#define DSP_REPORT_MOST_RECENT_CONFIRMED_DTC	  0x0Eu
#define DSP_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER  0x05u
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || \
(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))
#define  DSP_RDTC_04_06_10_REQUEST_LENGTH 0x05u
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
#define  DSP_RDTC_18_19_REQUEST_LENGTH 0x06u
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED != DCM_CFG_OFF)
#define  DSP_RDTC_09_REQUEST_LENGTH 0x04u
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
#define  DSP_RDTC_07_REQUEST_LENGTH 0x03u
#endif

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF) || \
		 \
		(DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF) || \
		 \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF))
#define  DSP_RDTC_01_11_12_REQUEST_LENGTH 0x02u
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED != DCM_CFG_OFF)
#define  DSP_RDTC_03_REQUEST_LENGTH 0x01u
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED != DCM_CFG_OFF)
#define DSP_RDTC_14_REQLEN     0x01u
#endif

#if ((DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED != DCM_CFG_OFF) || \
     (DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED != DCM_CFG_OFF) || \
	 (DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED != DCM_CFG_OFF) || \
	 (DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED != DCM_CFG_OFF))
#define DSP_RDTC_B_C_D_E_REQLEN     0x01u
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED != DCM_CFG_OFF)
#define DSP_RDTC_05_REQLEN     0x02u
#endif
#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
#define DSP_RDTC_17_REQLEN     0x03u
#endif

typedef enum
{
    DSP_RDTC_UNINIT,
    DSP_RDTC_INIT,
    DSP_RDTC_CALLSERVICE
}Dcm_DspRDTCStates_ten;

typedef enum
{
    DSP_RDTC_SFUNINIT,
    DSP_RDTC_SFINIT,
    DSP_RDTC_SFCALCNUMDTC,
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
    DSP_RDTC_SFTXPAGE,
    DSP_RDTC_SFFILLZERO,
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF))
    DSP_RDTC_GETFFSIZE,						
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF )||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF ))
    DSP_RDTC_UPDATEDISABLED,						
#endif
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED != DCM_CFG_OFF)
    DSP_RDTC_GETDTCSEVERITY,
#endif
    DSP_RDTC_GETDTCSTATUS,
    DSP_RDTC_SFFILLRESP
}Dcm_DspRDTCSubFuncStates_ten;

#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)
typedef enum
{
    DCM_RDTC_SUBFUNCTION_INITIAL,
    DCM_RDTC_SUBFUNCTION_STATUSOFDTC,
    DCM_RDTC_SUBFUNCTION_DISABLERECORDUPDATE,
    DCM_RDTC_SUBFUNCTION_SELECTRECORDSDATA,
    DCM_RDTC_SUBFUNCTION_GETRECORDSDATASIZE,
    DCM_RDTC_SUBFUNCTION_REPORTDTCRECORDS,
    DCM_RDTC_SUBFUNCTION_ENABLERECORDUPDATE,
    DCM_RDTC_SUBFUNCTION_REENABLERECORDUPDATE
}Dcm_DspRDTCSubFunctionState_en;
#endif

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
extern uint32 Dsp_RdtcDTC_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_DspRDTCStates_ten Dcm_DspRDTCState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_DspRDTCSubFuncStates_ten Dcm_DspRDTCSubFunc_en;
#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)
extern Dcm_DspRDTCSubFunctionState_en RDTCExtendedandSnapshotDataState_en;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern uint8 ClientId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#if(DCM_CFG_DSP_RDTCEXTENDEDDATA_OR_FREEZEFRAME_SUBFUNC_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern uint8 Dcm_DspRDTCRecordNum_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#endif
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
extern Dcm_MsgLenType Dcm_DspRDTCMaxRespLen_u32;
extern Dcm_MsgLenType Dcm_DspRDTCFilledRespLen_u32;
extern Dcm_MsgLenType Dcm_DspTotalRespLenFilled_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
extern uint16 Dcm_DspNumFltDTC_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
extern boolean Dcm_DspFirstPageSent_b;
extern boolean Dcm_DspFillZeroes_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_MsgType Dcm_DspRDTCRespBufPtr_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)|| \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF)|| \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)|| \
	 \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)|| \
	 \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF))

extern Std_ReturnType Dcm_Dsp_ReportSupportedDTC (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
#endif

extern void Dcm_Lok_DspReadDTCInfoConfirmation(
Dcm_IdContextType dataIdContext_u8,
PduIdType dataRxPduId_u8,
uint16 dataSourceAddress_u16,
Dcm_ConfirmationStatusType status_u8
);

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED!=DCM_CFG_OFF) || \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))
extern Std_ReturnType Dcm_Dsp_ReportExtendedDataRecordByDTCNumber (
                                                                Dcm_SrvOpStatusType Opstatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8
                                                                   );
#endif

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF))
extern Std_ReturnType Dcm_Dsp_ReportSnapshotRecordByDTCNumber (
                                                                Dcm_SrvOpStatusType Opstatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8
                                                                   );
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED!=DCM_CFG_OFF)
extern Std_ReturnType Dcm_Dsp_GetFreezeFrameDataByRecord (
        Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8
                                                            );
#endif
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED != DCM_CFG_OFF)
extern Std_ReturnType Dcm_Dsp_ReportSeverityOfDTC (
        Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
#endif

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF) || \
			 \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF) || \
			 \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF))
extern Std_ReturnType Dcm_Dsp_ReportNumberOfDTC (
        Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8
                                                     );
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED != DCM_CFG_OFF)

extern Std_ReturnType Dcm_Dsp_ReportDTCSnapshotRecordIdentification (
        Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8
                                                                          );

#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED!=DCM_CFG_OFF)

extern Std_ReturnType Dcm_Dsp_ReportDTCBySeverityMaskRecord(
        Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8
                                                                );
#endif
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED!=DCM_CFG_OFF)
extern Std_ReturnType Dcm_Dsp_ReportFaultDetectionCounter(
        Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8
                                                                );
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED != DCM_CFG_OFF)|| \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED != DCM_CFG_OFF)|| \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED != DCM_CFG_OFF)|| \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED != DCM_CFG_OFF))
extern Std_ReturnType Dcm_Dsp_ReportFailedDTC (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

#endif

