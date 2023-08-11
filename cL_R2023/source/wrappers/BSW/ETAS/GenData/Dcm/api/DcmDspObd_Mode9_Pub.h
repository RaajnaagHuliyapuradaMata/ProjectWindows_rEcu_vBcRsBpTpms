

#ifndef DCMDSPOBD_MODE9_PUB_H
#define DCMDSPOBD_MODE9_PUB_H

#if(DCM_CFG_DSP_OBDMODE9_ENABLED != DCM_CFG_OFF)

typedef Std_ReturnType (*GetInfotypeValueData_pf1) (Dcm_OpStatusType OpStatus,uint8 * DataValueBuffer,uint8 * DataValueBufferSize);

typedef struct{
    uint32 BitMask_u32;
    uint8  StartIndex_u8;
    uint8  NumInfotypes_u8;
}Dcm_Dsp_Mode9BitMask_t;

typedef enum
{
    OBD_MODE9_DEM_FNC,
    OBD_MODE9_USE_FNC,
    OBD_MODE9_RTE_FNC
}Dcm_Dsp_Mode9_API_Type;

typedef struct{

    void* const GetInfotypeValueData_pf;
    uint8  Infodatatype_size_u8;
    Dcm_Dsp_Mode9_API_Type InfoType_APIType_e;
}Dcm_Dsp_VehInfoData_t;

typedef struct{

    uint8 Infotype_u8;
    uint8 NumOfInfoData_u8;
    uint16 InfoDatatypeIndex_u16;
    boolean Is_NODI_Enabled_b ;
}Dcm_Dsp_VehInfo_t;
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

extern const Dcm_Dsp_Mode9BitMask_t Dcm_Dsp_Mode9Bitmask_acs[8];

extern const Dcm_Dsp_VehInfo_t Dcm_Dsp_VehInfoArray_acs[DCM_CFG_DSP_NUMINFOTYPESUPP];

extern const Dcm_Dsp_VehInfoData_t Dcm_Dsp_VehInfoData_acs[DCM_CFG_DSP_NUMOFINFOTYPEDATA];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#endif

#endif
