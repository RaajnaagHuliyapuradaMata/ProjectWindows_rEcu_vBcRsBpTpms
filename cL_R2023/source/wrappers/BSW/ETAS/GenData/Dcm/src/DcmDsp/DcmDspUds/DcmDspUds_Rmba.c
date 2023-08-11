

#include "DcmDspUds_Rmba_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Rmba_Priv.h"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
static uint32 Dcm_dataMemoryAddress_u32;
static uint32 Dcm_nrReadMemoryLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
static uint16 Dcm_idxDspRmba_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
static Dcm_OpStatusType Dcm_stRmbaOpstatus_u8;
static uint8 Dcm_dataMemdatasize_u8;
static uint8 Dcm_dataMemaddrsize_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void Dcm_RMBAIni (void)
{

    if(DCM_PENDING == Dcm_stRmbaOpstatus_u8 )
    {
        (void)(DcmAppl_Dcm_ReadMemory(DCM_CANCEL,Dcm_RMBAConfig_cast[Dcm_idxDspRmba_u16].dataMemoryValue_u8,
                                      Dcm_dataMemoryAddress_u32,Dcm_nrReadMemoryLength_u32,NULL_PTR,NULL_PTR));
    }

    Dcm_SrvOpstatus_u8 = DCM_INITIAL;

    Dcm_stRmbaOpstatus_u8 = DCM_INITIAL;
}

static Std_ReturnType Dcm_Lok_GetAddressRangeIndex_u8(uint32 dataMemAddr_u32,
                                                            uint32 nrMemLength_u32,
                                                            uint16 * idxIndex_u16)
{

    uint16 dataSize_u16;
    uint16 idxLoop_u16;
    Std_ReturnType dataRetVal_u8;

    dataRetVal_u8=E_NOT_OK;

    if(0u != nrMemLength_u32)
    {
        dataSize_u16 = Dcm_RmbacalculateTableSize_u16();
        for(idxLoop_u16 = 0;idxLoop_u16<dataSize_u16;idxLoop_u16++)
        {
            if((dataMemAddr_u32 >= Dcm_RMBAConfig_cast[idxLoop_u16].dataReadMemoryRangeLow_u32) &&
                                   ((dataMemAddr_u32 + (nrMemLength_u32-1u))<=
                                   (Dcm_RMBAConfig_cast[idxLoop_u16].dataReadMemoryRangeHigh_u32)))
            {
                *idxIndex_u16 = idxLoop_u16;
                dataRetVal_u8 = E_OK;
                break;
            }
        }
    }
    return (dataRetVal_u8);
}

LOCAL_INLINE void Dcm_Lok_RmbaTotalCheckLength(
                                 const Dcm_MsgContextType * pMsgContext,
                                 Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Std_ReturnType dataRetGetIdxRMBA_u8;
    *dataNegRespCode_u8 = 0x00;

    if((DCM_MINSIZE!=Dcm_dataMemaddrsize_u8)&&(DCM_MINSIZE!=Dcm_dataMemdatasize_u8)&&
      ((Dcm_dataMemdatasize_u8 <=DCM_MAXSIZE)&&(Dcm_dataMemaddrsize_u8<=DCM_MAXSIZE)))
    {

        if(pMsgContext->reqDataLen == (Dcm_dataMemaddrsize_u8 + Dcm_dataMemdatasize_u8 + 1u))
        {

            Dcm_GetMemoryInfo(Dcm_dataMemaddrsize_u8,&(pMsgContext->reqData[1]),&Dcm_dataMemoryAddress_u32);

            Dcm_GetMemoryInfo(Dcm_dataMemdatasize_u8,&(pMsgContext->reqData[Dcm_dataMemaddrsize_u8+1]),
                                                       &Dcm_nrReadMemoryLength_u32);

            dataRetGetIdxRMBA_u8 = Dcm_Lok_GetAddressRangeIndex_u8(Dcm_dataMemoryAddress_u32,
                                                                   Dcm_nrReadMemoryLength_u32,
                                                                   &Dcm_idxDspRmba_u16);

            if(E_OK == dataRetGetIdxRMBA_u8)
            {
                Dcm_SrvOpstatus_u8 = DCM_CHECKDATA;
            }
            else
            {

                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }
        }
        else
        {

            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }

    }
    else
    {

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
    }
}

LOCAL_INLINE Dcm_RmbaSupportRet_t Dcm_Lok_RmbaActiveSecurityLevel (
             uint32 dataSecurityMask_u32,
             const Dcm_RMBAConfig_tst * adrRmbaConfig_pcst,
             Dcm_NegativeResponseCodeType * adrNegRespCode_pu8)
{
    Std_ReturnType dataModeChkRetval_u8;
    Dcm_RmbaSupportRet_t dataRetVal_en;

    *adrNegRespCode_pu8 = 0x00;
    dataRetVal_en = DCM_RMBA_SUPPORT_OK;

           if ((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
           {

               if(adrRmbaConfig_pcst->adrUserMemReadModeRule_pfct!=NULL_PTR)
               {

                   dataModeChkRetval_u8 =(*adrRmbaConfig_pcst->adrUserMemReadModeRule_pfct)
                                         (adrNegRespCode_pu8,Dcm_dataMemoryAddress_u32,Dcm_nrReadMemoryLength_u32,
                                          DCM_SUPPORT_READ);
               }
               else
               {

                   dataModeChkRetval_u8 = DcmAppl_UserMemoryRangeModeRuleService(adrNegRespCode_pu8,
                                                                                 Dcm_dataMemoryAddress_u32,
                                                                                 Dcm_nrReadMemoryLength_u32,
                                                                                 DCM_SUPPORT_READ);
               }

               if((dataModeChkRetval_u8!=E_OK))
               {
                   if(*adrNegRespCode_pu8 ==0x00)
                   {
                       *adrNegRespCode_pu8 = DCM_E_CONDITIONSNOTCORRECT;
                   }
                   dataRetVal_en = DCM_RMBA_SUPPORT_CONDITION_VIOLATED;
               }
               else
               {
                   *adrNegRespCode_pu8=0;
               }

#if (DCM_CFG_DSP_MODERULEFORREADMEMORY != DCM_CFG_OFF)
               if((*adrNegRespCode_pu8==0x00) && (NULL_PTR != adrRmbaConfig_pcst->addrRmbaModeRuleChkFnc_pfct))
               {
                  (void)(*(adrRmbaConfig_pcst->addrRmbaModeRuleChkFnc_pfct))(adrNegRespCode_pu8);
               }

               if(*adrNegRespCode_pu8 !=0x00)
               {
                   dataRetVal_en=DCM_RMBA_SUPPORT_CONDITION_VIOLATED;
               }
#endif

           }

           else
           {
               *adrNegRespCode_pu8 = DCM_E_SECURITYACCESSDENIED;
               dataRetVal_en       = DCM_RMBA_SUPPORT_SECURITY_VIOLATED;
           }
   return dataRetVal_en;
}

static void Dcm_Lok_RmbaAccessCheck_u8 (uint16 idxIndex_u16,
                                     const Dcm_MsgContextType * pMsgContext,
                                     Dcm_NegativeResponseCodeType * adrNegRespCode_pu8)
{

    uint32 dataSessionMask_u32;
    uint32 dataSecurityMask_u32;
    const Dcm_RMBAConfig_tst * adrRmbaConfig_pcst;
    Dcm_RmbaSupportRet_t dataRetVal_en;
    Std_ReturnType stGetMemAccess_u8;

    dataRetVal_en = DCM_RMBA_SUPPORT_OK;
    *adrNegRespCode_pu8     = 0x00;
    adrRmbaConfig_pcst = &Dcm_RMBAConfig_cast[idxIndex_u16];

    dataSessionMask_u32 = adrRmbaConfig_pcst -> dataAllowedSessRead_u32;
    dataSecurityMask_u32 = adrRmbaConfig_pcst -> dataAllowedSecRead_u32;

    if ((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
    {

        stGetMemAccess_u8 = DcmAppl_DcmGetPermissionForMemoryAccess_u8(Dcm_dataMemoryAddress_u32,
                                                                       Dcm_nrReadMemoryLength_u32,DCM_SUPPORT_READ);
        if(stGetMemAccess_u8 != E_OK)
        {
            *adrNegRespCode_pu8 = DCM_E_REQUESTOUTOFRANGE;
            dataRetVal_en = DCM_RMBA_SUPPORT_CONDITION_VIOLATED;
        }
        else
        {

            dataRetVal_en = Dcm_Lok_RmbaActiveSecurityLevel(dataSecurityMask_u32,adrRmbaConfig_pcst,adrNegRespCode_pu8);
        }
    }

    else
    {
        *adrNegRespCode_pu8 = DCM_E_REQUESTOUTOFRANGE;
        dataRetVal_en       = DCM_RMBA_SUPPORT_SESSION_VIOLATED;
    }

    if(dataRetVal_en == DCM_RMBA_SUPPORT_OK)
    {
        if(Dcm_nrReadMemoryLength_u32 <= pMsgContext->resMaxDataLen)
         {
            Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
         }
        else
        {
            *adrNegRespCode_pu8 = DCM_E_RESPONSETOOLONG;
        }
    }
}

LOCAL_INLINE Std_ReturnType Dcm_Lok_RmbaReadMemory(
                                 Dcm_MsgContextType * pMsgContext,
                                 Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Dcm_ReadMemoryRet_t dataReadReturnVal_en;
    Std_ReturnType dataServRet_u8;

    dataReadReturnVal_en = DCM_READ_FAILED;
    dataServRet_u8=DCM_E_PENDING;

    dataReadReturnVal_en = DcmAppl_Dcm_ReadMemory (
                          Dcm_stRmbaOpstatus_u8,Dcm_RMBAConfig_cast[Dcm_idxDspRmba_u16].dataMemoryValue_u8,
                          Dcm_dataMemoryAddress_u32,Dcm_nrReadMemoryLength_u32,pMsgContext->resData,dataNegRespCode_u8);

    if(DCM_READ_OK == dataReadReturnVal_en)
    {

        pMsgContext->resDataLen =  Dcm_nrReadMemoryLength_u32;
        dataServRet_u8=E_OK;

        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        Dcm_stRmbaOpstatus_u8   = DCM_INITIAL;
        *dataNegRespCode_u8=0X00;
    }
    else if(DCM_READ_PENDING==dataReadReturnVal_en)
    {
        Dcm_stRmbaOpstatus_u8=DCM_PENDING;
        *dataNegRespCode_u8=0;
        dataServRet_u8=DCM_E_PENDING;
    }
    else if(DCM_READ_FORCE_RCRRP == dataReadReturnVal_en)
    {
        Dcm_stRmbaOpstatus_u8 = DCM_FORCE_RCRRP_OK;
        *dataNegRespCode_u8=0;
        dataServRet_u8=DCM_E_FORCE_RCRRP;
    }
    else
    {
        if(*dataNegRespCode_u8 == 0)
        {

            *dataNegRespCode_u8 =   DCM_E_GENERALREJECT;
            dataServRet_u8=E_NOT_OK;
        }

        Dcm_stRmbaOpstatus_u8=DCM_INITIAL;
    }
    return dataServRet_u8;
}

Std_ReturnType Dcm_DcmReadMemoryByAddress (Dcm_SrvOpStatusType OpStatus,
                                       Dcm_MsgContextType * pMsgContext,
                                       Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Std_ReturnType dataServRet_u8;

    dataServRet_u8=E_NOT_OK;
    *dataNegRespCode_u8=0x0;

    if(OpStatus == DCM_CANCEL)
    {
        Dcm_RMBAIni();
        dataServRet_u8 = E_OK;
    }
    else
    {

        if (Dcm_SrvOpstatus_u8 == DCM_INITIAL)
        {

            if(pMsgContext->reqDataLen >= DCM_DSP_RMBA_MINREQLEN)
            {

                Dcm_dataMemaddrsize_u8 = ((pMsgContext->reqData[0])& (0xFu));
                Dcm_dataMemdatasize_u8 = (uint8)(((pMsgContext->reqData[0])& (0xF0u))>>4u);

                Dcm_Lok_RmbaTotalCheckLength(pMsgContext, dataNegRespCode_u8);
            }
            else
            {

                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }

        if (Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
        {

            Dcm_Lok_RmbaAccessCheck_u8(Dcm_idxDspRmba_u16,pMsgContext,dataNegRespCode_u8);
        }

        if (Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
        {

            dataServRet_u8 = Dcm_Lok_RmbaReadMemory(pMsgContext, dataNegRespCode_u8);

        }

        if(*dataNegRespCode_u8 != 0)
        {

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
            dataServRet_u8=E_NOT_OK;
        }
    }
    return dataServRet_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
#endif

