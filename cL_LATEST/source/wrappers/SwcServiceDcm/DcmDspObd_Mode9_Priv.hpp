

#ifndef DCMDSPOBD_MODE9_PRIV_H
#define DCMDSPOBD_MODE9_PRIV_H

#include "DcmDspObd_Mode9_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE9_ENABLED != DCM_CFG_OFF)

#define DCM_OBDMODE09_REQ_LEN_MIN   0x00u
#define DCM_OBDMODE09_REQ_LEN       0x01u
#define DCM_OBDMODE09_REQ_LEN_MAX   0x07u
#define DCM_OBDMODE09_SUPPINFOTYPE  0x20u
#define DCM_OBDMODE09_INFOTYPE16    0x16u
#define DCM_OBDMODE09_INFOTYPE29    0x29u
#define DCM_OBDMODE09_NODIITID16_29 0x01u

typedef enum{
    DCM_DSP_MODE09_UNINIT
   ,   DCM_DSP_MODE09_INIT
   ,   DCM_DSP_MODE09_RUNNING
}Dcm_DspMode09Type_ten;

typedef struct{
   uint8 idxInfoType_u8;
   uint8_least  nrInfoTypeChk_qu8;
   uint8 adrTmpBuf_au8[DCM_OBDMODE09_REQ_LEN_MAX];
    Std_ReturnType dataInfotypeFnResult_u8;
    Dcm_MsgLenType nrReqDataLen_u32;
   uint32 dataInfoTypeMaskVal_u32;
}Dcm_ObdMode9ContextType;
#endif

#endif
#endif
