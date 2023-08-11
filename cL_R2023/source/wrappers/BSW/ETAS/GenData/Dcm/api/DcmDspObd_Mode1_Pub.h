

#ifndef DCMDSPOBD_MODE1_PUB_H
#define DCMDSPOBD_MODE1_PUB_H

#if(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)

typedef Std_ReturnType (*GetPIDvalue1_pf) (uint8 * Data);
typedef Std_ReturnType (*GetPIDvalue2_pf) (uint16 * Data);
typedef Std_ReturnType (*GetPIDvalue3_pf) (uint32 * Data);
typedef Std_ReturnType (*GetPIDvalue4_pf) (sint8 * Data);
typedef Std_ReturnType (*GetPIDvalue5_pf) (sint16 * Data);
typedef Std_ReturnType (*GetPIDvalue6_pf) (sint32 * Data);
typedef Std_ReturnType (*GetPIDvalue7_pf) (boolean * Data);

typedef enum
{
	OBD_USE_DATA_SENDER_RECEIVER,
	OBD_USE_DATA_SYNCH_CLIENT_SERVER,
	OBD_USE_DATA_SYNCH_FNC
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
	
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
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
    const Dcm_Dsp_Mode1SupportInfo_Type * ptr_supportinfo_pcs;
    DcmDspPidDataUsePort PidUsePort;
    uint16 Length_data_u16;
    uint16 Pos_data_u16;
    uint8 dataType_u8;
    uint8 dataEndianness_u8;
    uint8 SupportInfoBit_u8;
}Dcm_Dsp_Mode1DataSourcePid_Type;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

extern const Dcm_Dsp_Mode1BitMask_Type Dcm_Dsp_Mode1Bitmask_acs[8];

extern const Dcm_Dsp_Mode1Pid_Type Dcm_Dsp_Mode1PidArray_acs[DCM_CFG_DSP_NUMPIDSUPP_MODE1];

extern const Dcm_Dsp_Mode1DataSourcePid_Type Dcm_Dsp_Mode1DataSourcePid_acs[DCM_CFG_DSP_NUMPIDDATA_MODE1];
#if (DCM_CFG_DSP_NUMSUPPINFO_MODE1 != 0)

extern const Dcm_Dsp_Mode1SupportInfo_Type Dcm_Dsp_Mode1SupportInfo_acs[DCM_CFG_DSP_NUMSUPPINFO_MODE1];

#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif
#endif
