

#ifndef DCMDSPOBD_MODE8_PUB_H
#define DCMDSPOBD_MODE8_PUB_H

typedef  P2FUNC(Std_ReturnType,TYPEDEF,RequestControl1_pf)(
                    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Outdata_pu8
   ,     P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Indata_pu8
                     );
typedef  P2FUNC(Std_ReturnType,TYPEDEF,RequestControl2_pf)(
                    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Outdata_pu8
   ,     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Indata_pu8
                     );

#if(DCM_CFG_DSP_OBDMODE8_ENABLED != DCM_CFG_OFF)

typedef struct{
   uint32 BitMask_u32;
   uint8  StartIndex_u8;
   uint8  NumTids_u8;
}Dcm_Dsp_Mode8BitMask_Type;

typedef struct{
   void* const adrRequestControl_cpv;
   uint8 Tid_Id_u8;
   uint8 InBuffer_u8;
   uint8 OutBuffer_u8;
   boolean UsePort_b;
}Dcm_Dsp_Mode8Tid_Type;

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

extern CONST(Dcm_Dsp_Mode8BitMask_Type,DCM_CONST) Dcm_Dsp_Mode8Bitmask_acs[8];

extern CONST(Dcm_Dsp_Mode8Tid_Type,DCM_CONST) Dcm_Dsp_Mode8TidArray_acs[DCM_CFG_DSP_MODE8NUMTIDSUPP];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#endif

#endif
