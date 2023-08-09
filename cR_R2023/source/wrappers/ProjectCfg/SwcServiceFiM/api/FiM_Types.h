

#ifndef FIM_TYPES_H
#define FIM_TYPES_H

#include "Std_Types.h"
#include "Rte_FiM_Type.h"

typedef uint8 FiM_InhibitionMaskType;

typedef uint32 FiM_NumOffsetEventType;

typedef uint32 FiM_NumOffsetComponentType;

typedef struct
{
    const FiM_NumOffsetEventType* FiM_Cfg_NumOffsetEventptr;
    const FiM_FunctionIdType* FiM_CfgInhibitSourceMatrixptr;
    const FiM_InhibitionMaskType* FiM_CfgInhibitMaskMatrixptr;
    const FiM_NumOffsetComponentType* FiM_Cfg_NumOffsetComponentptr;
    const FiM_FunctionIdType* FiM_CfgInhibitSourceMatrixComponentptr;
} Type_CfgSwcServiceFiM_st;

#endif

