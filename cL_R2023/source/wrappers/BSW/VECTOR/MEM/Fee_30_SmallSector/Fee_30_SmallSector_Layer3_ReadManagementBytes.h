

#ifndef FEE_30_SMALLSECTOR_LAYER3_READ_MANAGEMENT_BYTES_H
# define FEE_30_SMALLSECTOR_LAYER3_READ_MANAGEMENT_BYTES_H

# include "Fee_30_SmallSector.h"
# include "Fee_30_SmallSector_InstanceHandler.h"

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"

FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Init(void);

FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_GetStatus(void);

FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_GetJobResult(void);

FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_StartJob(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Execute(void);

FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Cancel(void);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h"

#endif

