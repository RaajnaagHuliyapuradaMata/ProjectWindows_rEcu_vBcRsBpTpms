#ifndef BFX_H
#define BFX_H

#include "Bfx_Types.hpp"
#include "Bfx_Cfg.hpp"

#if(!defined(__QACDF__) || (defined(__QACDF__) && defined(SRVLIBS)))
#include "Bfx_Bit_Inl.hpp"
#endif

#define BFX_MODULE_ID                   205
#define BFX_VENDOR_ID                   1
#define BFX_SW_MAJOR_VERSION            5
#define BFX_SW_MINOR_VERSION            0
#define BFX_SW_PATCH_VERSION            0
#define BFX_AR_RELEASE_MAJOR_VERSION    4
#define BFX_AR_RELEASE_MINOR_VERSION    2
#define BFX_AR_RELEASE_REVISION_VERSION 2

#endif
