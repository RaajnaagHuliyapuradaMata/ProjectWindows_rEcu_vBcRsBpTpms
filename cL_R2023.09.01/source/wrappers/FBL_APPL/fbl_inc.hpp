

#ifndef __FBL_INC_H__
#define __FBL_INC_H__

#define FBLINC_VERSION          0x0317u
#define FBLINC_RELEASE_VERSION  0x00u

#include "v_ver.hpp"
#include "v_cfg.hpp"
#if defined( VGEN_GENY )
#include "v_inc.hpp"
#endif

#include "SecM.hpp"

#include "fbl_def.hpp"

# if defined( V_GEN_GENERATOR_MSR )
#  include "Fbl_Lbt.hpp"
# else
#  include "fbl_mtab.hpp"
# endif

#include "flashdrv.hpp"

#if defined( FBL_DIAG_ENABLE_FLASHDRV_ROM )
#include "FlashRom.hpp"
#endif

#include "fbl_wd.hpp"
#include "iotypes.hpp"

#if defined( V_GEN_GENERATOR_MSR )
#include "Fbl_Fbt.hpp"
#else

#endif
#include "fbl_mio.hpp"
#include "fbl_flio.hpp"
//#include "EepInc.hpp" @@GL
//#include "EepIO.hpp" @@GL

#include "applvect.hpp"

#include "fbl_cw.hpp"

#include "fbl_hw.hpp"

#if defined( FBL_ENABLE_WRAPPER_NV )
//#include "WrapNv_inc.hpp"@@GL
#endif

#include "fbl_apnv_fee.hpp"

#if defined( V_GEN_GENERATOR_MSR )

#else
#include "fbl_apfb.hpp"
#endif

#if defined( kMioDeviceRam )

#include "fbl_ramio_inc.hpp"
#endif

#include "fbl_diag.hpp"

#include "fbl_mem.hpp"

#if defined( FBL_ENABLE_COMMON_DATA )
#  include "comdat.hpp"
#endif
#include "fbl_ap.hpp"
#include "fbl_apwd.hpp"
#include "fbl_apdi.hpp"
#  include "fbl_apnv.hpp"

#if defined( FBL_DEF_ENABLE_NON_KB_MAIN )
#include "fbl_main.hpp"
#endif

#endif

