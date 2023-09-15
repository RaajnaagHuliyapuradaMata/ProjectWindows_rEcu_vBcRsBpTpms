

#ifndef DCMDSPOBD_MODE2_PRIV_H
#define DCMDSPOBD_MODE2_PRIV_H

#include "DcmDspObd_Mode2_Inf.hpp"

#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)

#define DCM_DSPMODE02_PID02   0x02u
#define MAX_PID_LENGTH_DATA   0xffu
#define DCM_OBDMODE02_SUPPPID 0x20u

typedef struct{
   boolean flgGetDTCNum_b;
   boolean isPIDFound_b;
   uint8 nrMultiple_u8;
   uint8 idxPID_u8;
   uint8 nrPid_u8;
   uint8 nrPIDValid_qu8;
   uint8 nrPIDChk_qu8;
   uint8 idxPIDStart_qu8;
    Std_ReturnType dataRetGet_u8;
   uint32 dataPIDBitMask_u32;
   uint32 dataCalBitMask_u32;
   uint32 nrDTC_u32;
    Dcm_MsgLenType nrResMaxDataLen_u32;
    Dcm_MsgLenType nrResDataLen_u32;
}Dcm_ObdContextType;

#endif

#endif
#endif
