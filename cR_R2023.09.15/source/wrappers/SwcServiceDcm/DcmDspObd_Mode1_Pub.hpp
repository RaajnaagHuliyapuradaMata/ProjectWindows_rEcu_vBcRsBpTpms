

#ifndef DCMDSPOBD_MODE1_PUB_H
#define DCMDSPOBD_MODE1_PUB_H

#if(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue1_pf)(P2VAR(uint8,  AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue2_pf)(P2VAR(uint16, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue3_pf)(P2VAR(uint32, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue4_pf)(P2VAR(sint8,  AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue5_pf)(P2VAR(sint16, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue6_pf)(P2VAR(sint32, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue7_pf)(P2VAR(boolean, AUTOMATIC,DCM_INTERN_DATA) Data);

typedef enum{
   OBD_USE_DATA_SENDER_RECEIVER
   ,  OBD_USE_DATA_SYNCH_CLIENT_SERVER
   ,  OBD_USE_DATA_SYNCH_FNC
}DcmDspPidDataUsePort;

typedef struct{
   uint32 BitMask_u32;
   uint8  StartIndex_u8;
   uint8  NumPids_u8;
}Dcm_Dsp_Mode1BitMask_Type;

typedef struct{
   uint8 Pid_Id_u8;
   uint8 Num_DataSourcePids_u8;
   uint16 DataSourcePid_ArrayIndex_u16;

#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
   uint8 Config_Mask;
#endif
   uint16 Pid_Size_u8;
}Dcm_Dsp_Mode1Pid_Type;

typedef struct{
   uint8 SupportInfoLen_u8;
   uint8 SupportInfoPos_u8;
}Dcm_Dsp_Mode1SupportInfo_Type;

typedef struct{
   void* const GetPIDvalue_pf;
   P2CONST(Dcm_Dsp_Mode1SupportInfo_Type,TYPEDEF,DCM_INTERN_CONST) ptr_supportinfo_pcs;
    DcmDspPidDataUsePort PidUsePort;
   uint16 Length_data_u16;
   uint16 Pos_data_u16;
   uint8 dataType_u8;
   uint8 dataEndianness_u8;
   uint8 SupportInfoBit_u8;
}Dcm_Dsp_Mode1DataSourcePid_Type;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern CONST(Dcm_Dsp_Mode1BitMask_Type,DCM_CONST) Dcm_Dsp_Mode1Bitmask_acs[8];

extern CONST(Dcm_Dsp_Mode1Pid_Type,DCM_CONST) Dcm_Dsp_Mode1PidArray_acs[DCM_CFG_DSP_NUMPIDSUPP_MODE1];

extern CONST(Dcm_Dsp_Mode1DataSourcePid_Type,DCM_CONST) Dcm_Dsp_Mode1DataSourcePid_acs[DCM_CFG_DSP_NUMPIDDATA_MODE1];
#if(DCM_CFG_DSP_NUMSUPPINFO_MODE1 != 0)

extern CONST(Dcm_Dsp_Mode1SupportInfo_Type,DCM_CONST) Dcm_Dsp_Mode1SupportInfo_acs[DCM_CFG_DSP_NUMSUPPINFO_MODE1];

#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
