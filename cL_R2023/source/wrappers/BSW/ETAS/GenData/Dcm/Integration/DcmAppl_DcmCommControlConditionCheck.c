
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#include "CanManagerX.h"
#include "SysManagerX.h"

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType DcmAppl_DcmCommControlConditionCheck(uint8 ControlType_u8,
                                                                 uint8 DataCommType_u8,
                                                                 const uint8 * RequestData,
                                                                 uint16 RequestLength,
                                                                 Dcm_NegativeResponseCodeType * dataNegRespCode_u8 )
{
    Std_ReturnType retVal_u8;
	uint8 ucEcuMode;

	retVal_u8 = E_OK;
    (void)(ControlType_u8);
    (void)(DataCommType_u8);
    (void)(dataNegRespCode_u8);
    (void)(RequestData);
    (void)(RequestLength);

	ucEcuMode = SYSMGR_GetEcuMode();
	
	switch (ControlType_u8)
	{
		case DCM_ENABLE_RX_TX_NORM:
			CANMGR_CommControlStatus(ControlType_u8);
			CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Rx);
			CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse);
			if (ucEcuMode != cECUMODE_QUIET)
			{
				CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic);
				CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx);
			}

			break;

		case DCM_DISABLE_RX_ENABLE_TX_NORM:
			CANMGR_CommControlStatus(DCM_ENABLE_RX_TX_NORM);
			CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Rx);
			CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse);
			if (ucEcuMode != cECUMODE_QUIET)
			{
				CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic);
				CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Tx);
			}

			CANMGR_CommControlStatus(ControlType_u8);

			break;

		case DCM_ENABLE_RX_DISABLE_TX_NORM:
			CANMGR_CommControlStatus(DCM_ENABLE_RX_TX_NORM);
			CANMGR_PduGroupStart(ComConf_ComIPduGroup_ComIPduGroup_Rx);
			CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic);
			CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse);
			CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx);

			CANMGR_CommControlStatus(ControlType_u8);

			break;

		case DCM_DISABLE_RX_TX_NORMAL:
			CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppCyclic);
			CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx_AppResponse);
			CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Tx);
			CANMGR_PduGroupStop(ComConf_ComIPduGroup_ComIPduGroup_Rx);

			CANMGR_CommControlStatus(ControlType_u8);

			break;

		default:
			retVal_u8 = E_NOT_OK;
			*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE; // unknown input
			break;
	}
    return (retVal_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
