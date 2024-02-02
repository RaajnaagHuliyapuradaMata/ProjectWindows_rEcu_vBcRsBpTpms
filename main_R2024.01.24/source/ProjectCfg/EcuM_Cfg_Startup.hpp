#ifndef ECUM_CFG_STARTUP_H
#define ECUM_CFG_STARTUP_H

#include "Os.hpp"
#if(!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
   #error "AUTOSAR major version undefined or mismatched"
#endif
#if(!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
   #error "AUTOSAR minor version undefined or mismatched"
#endif

//TBD: Delete this file?

#include "CanIf.hpp"
#include "ComM.hpp"
#include "CanSM.hpp"
#include "PduR.hpp"
#include "Com.hpp"
#include "CanTp.hpp"
#include "FiM.hpp"
#include "BswM.hpp"

#endif

