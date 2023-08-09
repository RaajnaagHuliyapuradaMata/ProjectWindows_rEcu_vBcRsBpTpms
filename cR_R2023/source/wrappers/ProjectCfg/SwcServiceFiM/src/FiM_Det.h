

#ifndef FIM_DET_H
#define FIM_DET_H

#if (FIM_CFG_DEV_ERROR_DETECT != FIM_CFG_OFF)
#include "Det.h"
#endif

#include "FiM_Utils.h"
#include "FiM_Cfg_Version.h"

#define FIM_INIT_ID						0x00
#define FIM_GETFUNCTIONPERMISSION_ID	0x01
#define FIM_DEMTRIGGERONEVENTSTATUS_ID	0x02
#define FIM_DEMINIT_ID					0x03
#define FIM_GETVERSIONINFO_ID			0x04
#define FIM_MAINFUNCTION_ID				0x05

#define FIM_PRIV_STATUSINIT_ID				0xB1
#define FIM_PRIV_MONITOR_ID					0xB2
#define FIM_PRIV_MONITORCOUNTERDEC_ID		0xB3
#define FIM_PRIV_FIDCOUNTDEC_ID				0xB4
#define FIM_PRIV_DEMGETEVENTSTATUS_ID		0xB5

#define FIM_E_UNINIT 					             0x01
#define FIM_E_FID_OUT_OF_RANGE        				 0x02
#define FIM_E_EVENTID_OUT_OF_RANGE 				     0x03
#define FIM_E_PARAM_POINTER     					 0x04
#define FIM_E_INIT_FAILED						     0x05
#define FIM_E_COMPONENTID_OUT_OF_RANGE               0x06

#define FIM_E_FID_COUNTERNEGATIVE				 0xB1
#define FIM_E_FID_MONITORUNPLAUSIBLE			 0xB2
#define FIM_E_MONITORSTATE_INVALID				 0xB3
#define FIM_E_NOT_INITIALIZED					 0xB4
#define FIM_E_DEMGETEVENTSTATUS_NOK				 0xB5
//#define FIM_E_CALL_DURING_DEMINIT				 0xB6
#define FIM_E_DEMINIT_NOT_CALLED				 0xB7
#define FIM_E_DEMINIT_CALLED_ALREADY			 0xB8
#define FIM_E_INITIALIZED_ALREADY				 0xB9

LOCAL_INLINE void FIM_PRIV_DET_ERROR(uint8 FiM_ApiId, uint8 FiM_ErrorId)
{
#if (FIM_CFG_DEV_ERROR_DETECT != FIM_CFG_OFF)
    FIM_USE_VAR(Det_ReportError(FIM_MODULE_ID, FIM_INSTANCE_ID, FiM_ApiId, FiM_ErrorId));
#else
    FIM_USE_VAR(FiM_ApiId);
    FIM_USE_VAR(FiM_ErrorId);
#endif
}

#endif

