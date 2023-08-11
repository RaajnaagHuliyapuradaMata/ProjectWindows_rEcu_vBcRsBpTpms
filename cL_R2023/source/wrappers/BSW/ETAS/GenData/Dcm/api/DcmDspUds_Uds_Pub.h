

#ifndef DCMDSPUDS_UDS_PUB_H
#define DCMDSPUDS_UDS_PUB_H

#if (DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Pub.h"
#endif

#if (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Seca_Pub.h"
#endif

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dsc_Pub.h"
#endif

#if(DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_CC_Pub.h"
#endif

#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Cdtcs_Pub.h"
#endif

#if(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Wmba_Pub.h"
#endif

#if(DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rmba_Pub.h"
#endif

#if(DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Cdi_Pub.h"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

extern Std_ReturnType Dcm_DemTriggerOnDTCStatus( uint32 Dtc, uint8 DTCStatusOld, uint8 DTCStatusNew );
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))

typedef enum
{
    DCM_DDDI_CLEAR = 0,
    DCM_DDDI_CLEARALL,
    DCM_DDDI_WRITE
}Dcm_DddiWriteOrClear_ten;

typedef enum
{
    DCM_DDDI_READ_OK = 0,
    DCM_DDDI_READ_NOT_OK,
    DCM_DDDI_READ_NOTAVAILABLE
}Dcm_RestoreDddiReturn_ten;
#endif

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

typedef struct{
  uint32 adrDddiMem_u32;
  uint32 dataMemLength_u32;
} Dcm_DDDI_DEF_MEM_t;

typedef struct{
  uint16 dataSrcDid_u16;
  uint16 idxOfDid_u16;
  uint8  posnInSourceDataRecord_u8;
  uint8  dataMemorySize_u8;
  boolean stCurrentDidRangeStatus_b;
} Dcm_DddiDefId_tst;

typedef union
{
  Dcm_DDDI_DEF_MEM_t dataMemAccess_st;
  Dcm_DddiDefId_tst  dataIdAccess_st;
} Dcm_DddiDef_tst;

typedef struct{
  Dcm_DddiDef_tst dataDddi_st;
  uint8 dataDefinitionType_u8;
} Dcm_DddiRecord_tst;

typedef struct{

  uint16 nrCurrentlyDefinedRecords_u16;

  uint16 posnCurrentPosInDataBuffer_u16;
  uint16 idxCurrentRecord_u16;
} Dcm_DddiIdContext_tst;

typedef struct{
  Dcm_DddiRecord_tst * addrRecord_pst;
  Dcm_DddiIdContext_tst * dataDDDIRecordContext_pst;
  Dcm_DddiIdContext_tst * dataPDIRecordContext_pst;
  uint16 dataDddId_u16;
  uint16 nrMaxNumOfRecords_u16;
} Dcm_DddiMainConfig_tst;

#endif

#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)       ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)      ||  \
     (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)                      ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)||  \
     (DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)        ||  \
     (DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF))

typedef enum
{
    DCM_SUPPORT_READ,
    DCM_SUPPORT_WRITE,
    DCM_SUPPORT_IOCONTROL
} Dcm_Direction_t;

#endif
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)		||	\
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) 	||	\
	 (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) 					|| 	\
	 (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

typedef enum
{
    DCM_SUPPORT_OK,
    DCM_SUPPORT_SESSION_VIOLATED,
    DCM_SUPPORT_SECURITY_VIOLATED,
    DCM_SUPPORT_CONDITION_VIOLATED,
    DCM_SUPPORT_CONDITION_PENDING
} Dcm_SupportRet_t;

typedef struct{
	uint32 dataSignalLengthInfo_u32;
	uint16  nrNumofSignalsRead_u16;
	uint16  idxIndex_u16;
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
	uint16 dataRangeDid_16;
#endif
	Dcm_NegativeResponseCodeType dataNegRespCode_u8;
	boolean dataRange_b;
	boolean flgNvmReadPending_b;
	Dcm_OpStatusType dataopstatus_b;
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
	boolean flagPageddid_b;		
#endif
} Dcm_DIDIndexType_tst;

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

extern Std_ReturnType Dcm_GetIndexOfDID (
														uint16 did,
														Dcm_DIDIndexType_tst * idxDidIndexType_st
														 );

#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)				||		\
	 (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)				||		\
	 (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

extern Dcm_SupportRet_t Dcm_GetSupportOfIndex( Dcm_DIDIndexType_tst * idxDidIndexType_st,
															   Dcm_Direction_t direction,
															   Dcm_NegativeResponseCodeType * dataNegRespCode_u8);

#endif

#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)          ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)         ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

extern Std_ReturnType Dcm_GetDIDRangeStatus (
                                                            uint16 did,
                                                            Dcm_DIDIndexType_tst * idxDidIndexType_st
                                                            );
#endif

extern 	Std_ReturnType Dcm_GetLengthOfDIDIndex(Dcm_DIDIndexType_tst * idxDidIndexType_st,
        													   uint32 * length_u32,
        													   uint16 did_u16);

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)|| (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))

extern Std_ReturnType Dcm_GetActiveDid(uint16 * dataDid_u16);

extern Std_ReturnType Dcm_GetActiveSourceDataId(uint16 * dataSrcDid_u16,uint8 * posnSrcDataRec_u8, uint8 * adrMemSize_u8);

#endif

#if ((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)							||		    \
	 (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)	||		    \
			 (DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) ||   \
			 (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))

extern Std_ReturnType Dcm_GetDIDData (Dcm_DIDIndexType_tst * idxDidIndexType_st,
 	  	   	   	   	   	   	   	   	   	   	   	   	  uint8 * targetBuffer);
#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
#if(DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
extern Std_ReturnType Dcm_GetActiveRid(uint16 * dataRid_u16);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

#if ((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) || \
     (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
typedef enum
{
    DCM_READ_OK,
    DCM_READ_FAILED,
    DCM_READ_PENDING,
    DCM_READ_FORCE_RCRRP,
    DCM_READ_NOT_AVAILABLE
} Dcm_ReadMemoryRet_t;

typedef Dcm_ReadMemoryRet_t Dcm_ReturnReadMemoryType;
#endif

#if((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))

typedef enum
{
    DCM_WRITE_OK,
    DCM_WRITE_FAILED,
    DCM_WRITE_PENDING,
    DCM_WRITE_FORCE_RCRRP,
    DCM_WRITE_NOT_AVAILABLE
} Dcm_WriteMemoryRet_t;

typedef Dcm_WriteMemoryRet_t Dcm_ReturnWriteMemoryType;
#endif

#if(DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF)
typedef enum
{
    DCM_UPLOAD = 0,
    DCM_DOWNLOAD,
    DCM_TRANSFER_NOT_AVAILABLE
} Dcm_TrasferDirection_en;
#endif
#endif
