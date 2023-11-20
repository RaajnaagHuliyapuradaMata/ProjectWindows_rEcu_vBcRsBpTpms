#include "Std_Types.hpp"

#include "Fls.hpp"
#include "Fls_PBTypes.hpp"
#include "Fls_Cbk.hpp"

#define FLS_PBCFG_C_AR_MAJOR_VERSION  2U
#define FLS_PBCFG_C_AR_MINOR_VERSION  4U
#define FLS_PBCFG_C_AR_PATCH_VERSION  0U
#define FLS_PBCFG_C_SW_MAJOR_VERSION  1U
#define FLS_PBCFG_C_SW_MINOR_VERSION  3U

#define FLS_START_SEC_DBTOC_DATA_UNSPECIFIED
#include "MemMap.hpp"
CONST(Fls_ConfigType, FLS_CONST) Fls_GstConfiguration[] =
{
  {
    0x0ED70118UL,
    Fee_30_SmallSector_JobEndNotification,
    Fee_30_SmallSector_JobErrorNotification,
    NULL_PTR,
    NULL_PTR,
    0x00000100UL,
    0x0003E801UL,
    0x00004291UL,
    0x00000FA1UL
  }
};
#define FLS_STOP_SEC_DBTOC_DATA_UNSPECIFIED
#include "MemMap.hpp"

#define FLS_START_SEC_BUFFER_CODE
#include "MemMap.hpp"
 VAR(uint32, AUTOMATIC) Fls_GulTempBuffer[64];
#define FLS_STOP_SEC_BUFFER_CODE
#include "MemMap.hpp"
