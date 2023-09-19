

#ifndef DCMDSPOBD_MODE2_PUB_H
#define DCMDSPOBD_MODE2_PUB_H

#if(DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)

typedef struct{
   uint32 BitMask_u32;
   uint8  StartIndex_u8;
   uint8  NumPids_u8;
}Dcm_Dsp_Mode2BitMask_Type;

typedef struct{
   uint8 Pid_Id_u8;
   uint8 Num_DataSourcePids_u8;
   uint16 DataSourcePid_ArrayIndex_u16;
   uint16 Pid_Size_u8;
}Dcm_Dsp_Mode2Pid_Type;

typedef struct{
   uint16 Length_data_u8;
   uint16 Pos_data_u8;
}Dcm_Dsp_Mode2DataSourcePid_Type;

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern CONST(Dcm_Dsp_Mode2BitMask_Type,DCM_CONST) Dcm_Dsp_Mode2Bitmask_acs[8];

extern CONST(Dcm_Dsp_Mode2Pid_Type,DCM_CONST) Dcm_Dsp_Mode2PidArray_acs[DCM_CFG_DSP_NUMPIDSUPP_MODE2];

extern CONST(Dcm_Dsp_Mode2DataSourcePid_Type,DCM_CONST)  Dcm_Dsp_Mode2DataSourcePid_acs[DCM_CFG_DSP_NUMPIDDATA_MODE2];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
