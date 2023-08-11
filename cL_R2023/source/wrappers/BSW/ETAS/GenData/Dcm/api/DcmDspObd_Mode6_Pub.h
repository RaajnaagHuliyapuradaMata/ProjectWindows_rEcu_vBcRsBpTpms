

#ifndef DCMDSPOBD_MODE6_PUB_H
#define DCMDSPOBD_MODE6_PUB_H

#if(DCM_DSP_OBDMID_DTR_RB_SUPPORT == DCM_CFG_ON)

#ifndef DCM_DTRSTATUS_VISIBLE
#define DCM_DTRSTATUS_VISIBLE     0
#endif
#ifndef DCM_DTRSTATUS_INVISIBLE
#define DCM_DTRSTATUS_INVISIBLE   1
#endif

typedef Std_ReturnType (*GetDTRvalue_pf1) (Dcm_OpStatusType OpStatus,
													   uint16 * Testval,
													   uint16 * Minlimit,
													   uint16 * Maxlimit,
													   uint8 * Status
																);

typedef Std_ReturnType (*GetDTRvalue_pf2) (
														uint16 * Testval,
														uint16 * Minlimit,
														uint16 * Maxlimit,
														uint8 * Status
													   );

#if(DCM_CFG_DSP_OBDMODE6_ENABLED != DCM_CFG_OFF)

typedef struct{
    uint32 BitMask_u32;
    uint8  StartIndex_u8;
    uint8  NumMids_u8;
}Dcm_Dsp_Mode6BitMask_Type;

typedef struct{
    uint16 Tid_ArrayIndex_u16;
    uint8 Mid_Id_u8;
    uint8 Num_Tids_u8;
}Dcm_Dsp_ObdMidArray_Type;

typedef struct{
	void* const GetDTRvalue_pf;
    uint8 UnitScale_u8;
    uint8 Tid_Id_u8;
    boolean Is_UsePort_Enabled_b   ;
}Dcm_Dsp_TidArray_Type;

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

extern const Dcm_Dsp_Mode6BitMask_Type Dcm_Dsp_Mode6Bitmask_acs[8];

extern const Dcm_Dsp_ObdMidArray_Type Dcm_Dsp_ObdMidArray_acs[DCM_CFG_DSP_OBDMIDARRAYSIZE];

extern const Dcm_Dsp_TidArray_Type Dcm_Dsp_TidArray_acs[];

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#endif
#include "Dcm_MemMap.h"
#endif
#endif

