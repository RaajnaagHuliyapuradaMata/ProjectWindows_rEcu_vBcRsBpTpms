
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

#include "CanManagerX.h"

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE)  DcmAppl_DcmCommControlConditionCheck(VAR(uint8,AUTOMATIC) ControlType_u8,
                                                                 VAR(uint8,AUTOMATIC) DataCommType_u8,
                                                                 P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) RequestData,
                                                                 VAR(uint16,AUTOMATIC) RequestLength,
                                                                 P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8 )
{
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8 = E_OK;

    switch (ControlType_u8)
    {
      case DCM_ENABLE_RX_DISABLE_TX_NORM:
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
      *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
      break;
    }

    return (retVal_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
