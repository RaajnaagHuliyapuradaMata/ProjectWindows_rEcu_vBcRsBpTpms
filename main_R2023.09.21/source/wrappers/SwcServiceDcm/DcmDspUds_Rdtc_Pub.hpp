

#ifndef DCMDSPUDS_RDTC_PUB_H
#define DCMDSPUDS_RDTC_PUB_H

#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)

typedef struct{
   P2FUNC(Std_ReturnType,TYPEDEF,SubFunc_fp) (VAR(Dcm_SrvOpStatusType,AUTOMATIC),P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA),P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA));
   uint8    SubFuncLevel_u8;
   boolean isDspRDTCSubFnc_b;				 
}Dcm_Dsp_RDTCInfoType;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern CONST(Dcm_Dsp_RDTCInfoType,DCM_CONST) DcmDspRDTCInfo[DCM_CFG_NUMRDTCSUBFUNC];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
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
#include "Dcm_Cfg_MemMap.hpp"

extern FUNC(void,DCM_CODE) Dcm_Dsp_RDTCUpdatePage(
                                                    VAR(Dcm_MsgType,AUTOMATIC) PageBufPtr
   ,     VAR(Dcm_MsgLenType,AUTOMATIC) PageLen
                                                 );

extern FUNC(void,DCM_CODE) Dcm_Dsp_RDTCFillZero (VAR(Dcm_MsgLenType,AUTOMATIC) RemTotalResLen);
extern FUNC(boolean,DCM_CODE) Dcm_IsProtocolIPCanFD(void);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif

#endif
