

#ifndef DCMDSPUDS_RDTC_PUB_H
#define DCMDSPUDS_RDTC_PUB_H

#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)

typedef struct{
    Std_ReturnType (*SubFunc_fp) (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType *pMsgContext ,Dcm_NegativeResponseCodeType *dataNegRespCode );
    uint8    SubFuncLevel_u8;
    boolean isDspRDTCSubFnc_b;				 	
}Dcm_Dsp_RDTCInfoType;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
extern const Dcm_Dsp_RDTCInfoType DcmDspRDTCInfo[DCM_CFG_NUMRDTCSUBFUNC];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF) &&\
    ((DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF) ||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED != DCM_CFG_OFF) ||\
	 \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)||\
	 \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)))
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

extern void Dcm_Dsp_RDTCUpdatePage(
                                                    Dcm_MsgType PageBufPtr,
                                                    Dcm_MsgLenType PageLen
                                                 );

extern void Dcm_Dsp_RDTCFillZero (Dcm_MsgLenType RemTotalResLen);
extern boolean Dcm_IsProtocolIPCanFD(void);

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

#endif

#endif
