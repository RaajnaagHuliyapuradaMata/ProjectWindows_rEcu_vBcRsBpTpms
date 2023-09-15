

#ifndef DCMDSPUDS_IOCBI_PRIV_H
#define DCMDSPUDS_IOCBI_PRIV_H

#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)

#define DSP_IOCBI_MINREQLEN            0x03u

typedef enum{
    DCM_IOCBI_IDLE = 1
   ,   DCM_IOCBI_CHKSUPPORT
   ,   DCM_IOCBI_CHKCOND
   ,   DCM_IOCBI_RUNNING
   ,   DCM_IOCBI_READSTREC
}Dcm_DspIOCBIStates_ten;

#define DCM_IOCBI_RETURNCONTROLTOECU  0x0u
#define DCM_IOCBI_RESETTODEFAULT      0x1u
#define DCM_IOCBI_FREEZECURRENTSTATE  0x2u
#define DCM_IOCBI_SHORTTERMADJUSTMENT 0x3u

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_ReadSignalLength_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern Std_ReturnType Dcm_GetLengthOfSignal (uint16 * dataSigLength_u16);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

#endif

#endif
