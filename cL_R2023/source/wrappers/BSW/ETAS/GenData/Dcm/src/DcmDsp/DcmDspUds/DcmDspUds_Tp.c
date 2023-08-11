
#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Tp_Inf.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Tp_Priv.h"

#if(DCM_CFG_DSP_TESTERPRESENT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType Dcm_DcmTesterPresent (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Std_ReturnType retVal_u8;
    retVal_u8=E_NOT_OK;
    *dataNegRespCode_u8=0;

    DCM_UNUSED_PARAM(OpStatus);

    if(pMsgContext->reqDataLen > 0uL)
    {
       if(pMsgContext->reqData[DCM_TPR_POSITION_SUBFUNC] == DCM_TPR_RESP_REQUIRED)
       {

           if(pMsgContext->reqDataLen == DCM_TPR_REQ_LEN)
            {
              pMsgContext->resDataLen = DCM_TPR_POSITIVE_RESP_LEN;
              pMsgContext->resData[DCM_TPR_POSITION_SUBFUNC] = 0x00u;
              retVal_u8=E_OK;
            }

            else
            {

              *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
       }

       else
       {

               *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
       }
    }
    else
    {
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if(*dataNegRespCode_u8 != 0x0u)
    {

        retVal_u8=E_NOT_OK;
    }
    return retVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#if(DCM_CFG_DSP_TESTERPRESENTSB_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

Std_ReturnType Dcm_DcmTesterPresentSB (Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Std_ReturnType retVal_u8;
    retVal_u8=E_NOT_OK;

    DCM_UNUSED_PARAM(OpStatus);

    if(pMsgContext->reqDataLen == DCM_TPR_REQ_LEN)
    {

        if(pMsgContext->reqData[DCM_TPR_POSITION_SUBFUNC] == DCM_TPR_RESP_REQUIRED)
        {

            pMsgContext->resDataLen = DCM_TPR_POSITIVE_RESP_LEN;
            pMsgContext->resData[DCM_TPR_POSITION_SUBFUNC] = 0x00u;
            retVal_u8=E_OK;
        }

        else
        {

            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
    }

    else if(pMsgContext->reqDataLen == 0x00u)
    {

        pMsgContext->resDataLen = 0x00u;
        retVal_u8=E_OK;
    }
    else
    {

        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if(*dataNegRespCode_u8 != 0x0u)
    {

        retVal_u8=E_NOT_OK;
    }

    return retVal_u8;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif
#endif

