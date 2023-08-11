
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DEM_CFG_SCHM_H
#define DEM_CFG_SCHM_H

#include "SchM_Default.h"

#define SchM_Enter_Dem_Monitoring()		do { SCHM_ENTER_DEFAULT(); } while (0)
#define SchM_Exit_Dem_Monitoring()		do { SCHM_EXIT_DEFAULT(); } while (0)

#define SchM_Enter_Dem_Nvm()      		do { SCHM_ENTER_DEFAULT(); } while (0)
#define SchM_Exit_Dem_Nvm()       		do { SCHM_EXIT_DEFAULT(); } while (0)

#define SchM_Enter_Dem_Dcm()      		do { SCHM_ENTER_DEFAULT(); } while (0)
#define SchM_Exit_Dem_Dcm()       		do { SCHM_EXIT_DEFAULT(); } while (0)

#endif

