#include "Std_Types.hpp"

#include "Fls.hpp"
#include "Fls_PBTypes.hpp"
#include "Fls_Cbk.hpp"

#define FLS_PBCFG_C_AR_MAJOR_VERSION  2U
#define FLS_PBCFG_C_AR_MINOR_VERSION  4U
#define FLS_PBCFG_C_AR_PATCH_VERSION  0U
#define FLS_PBCFG_C_SW_MAJOR_VERSION  1U
#define FLS_PBCFG_C_SW_MINOR_VERSION  3U

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

VAR(uint32, AUTOMATIC) Fls_GulTempBuffer[64];
