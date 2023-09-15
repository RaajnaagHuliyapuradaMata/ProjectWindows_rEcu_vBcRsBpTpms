

#ifndef DCMDSPOBD_MODE9_PUB_H
#define DCMDSPOBD_MODE9_PUB_H

#if(DCM_CFG_DSP_OBDMODE9_ENABLED != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,GetInfotypeValueData_pf1)(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) DataValueBuffer,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) DataValueBufferSize);

typedef struct{
   uint32 BitMask_u32;
   uint8  StartIndex_u8;
   uint8  NumInfotypes_u8;
}Dcm_Dsp_Mode9BitMask_t;

typedef enum{
    OBD_MODE9_DEM_FNC
   ,   OBD_MODE9_USE_FNC
   ,   OBD_MODE9_RTE_FNC
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
#include "Dcm_Cfg_MemMap.hpp"

extern CONST(Dcm_Dsp_Mode9BitMask_t,DCM_CONST) Dcm_Dsp_Mode9Bitmask_acs[8];

extern CONST(Dcm_Dsp_VehInfo_t,     DCM_CONST) Dcm_Dsp_VehInfoArray_acs[DCM_CFG_DSP_NUMINFOTYPESUPP];

extern CONST(Dcm_Dsp_VehInfoData_t, DCM_CONST) Dcm_Dsp_VehInfoData_acs[DCM_CFG_DSP_NUMOFINFOTYPEDATA];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif
