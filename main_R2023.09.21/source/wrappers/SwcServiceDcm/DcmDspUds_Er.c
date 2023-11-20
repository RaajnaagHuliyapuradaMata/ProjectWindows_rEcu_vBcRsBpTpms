#include "Std_Types.hpp"

#include "DcmDspUds_Er_Inf.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) )
#include "DcmDspUds_Er_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF))
static VAR(uint8,     DCM_VAR) Dcm_idxReset_u8;
#endif

#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
VAR(Dcm_EcuResetStateType_ten,     DCM_VAR  ) Dcm_stEcuResetState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
VAR(uint8            ,     DCM_VAR  ) Dcm_dataEcuRType_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

FUNC(void,DCM_CODE) Dcm_Dsp_EcuReset_Ini (void){
    Dcm_stEcuResetState_en = DCM_ECURESET_IDLE;
    Dcm_dataEcuRType_u8 = DCM_NO_RESET;

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
    Dcm_ResetBootLoader();
#endif
}

FUNC(void, DCM_CODE) Dcm_Lok_DspEcuResetConfirmation(
  VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,AUTOMATIC)dataRxPduId_u8
   ,  VAR(uint16,AUTOMATIC)dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8){
        if((status_u8 == DCM_RES_POS_OK)||(status_u8 == DCM_RES_POS_NOT_OK)){
#if(DCM_CFG_APPLTXCONF_REQ != DCM_CFG_OFF)
   		DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8
   ,                          dataSourceAddress_u16,status_u8);
#else
   		(void)dataIdContext_u8;
   		(void)dataRxPduId_u8;
   		(void)dataSourceAddress_u16;
#endif

#if(DCM_CFG_RESPOND_REQ_AFTERECURESET == DCM_CFG_OFF)
   		Dcm_acceptRequests_b = FALSE;
#endif

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
   		if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT){
   			Dcm_ResetBootLoader();
   		}
#endif

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
   		(void)SchM_Switch_SwcServiceDcm_tEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
#endif
   		(void)DcmAppl_Switch_DcmExecuteEcuReset(Dcm_dataEcuRType_u8);
        }
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tEcuReset (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8){
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
   VAR(uint8_least,AUTOMATIC) idxIndex_qu8;
    *dataNegRespCode_u8 = 0x00;
    dataRetVal_u8=E_OK;
   if(OpStatus == DCM_CANCEL){
        Dcm_Dsp_EcuReset_Ini();
        dataRetVal_u8 = E_OK;
   }
   else{
        if(Dcm_stEcuResetState_en == DCM_ECURESET_IDLE){
            Dcm_dataEcuRType_u8 = pMsgContext->reqData[0];
            for(idxIndex_qu8 = 0; idxIndex_qu8 < DCM_CFG_DSP_NUMRESETTYPE; idxIndex_qu8++){
                if(Dcm_dataEcuRType_u8 == Dcm_DspEcuResetType_cast[idxIndex_qu8].dataResetLevel_u8){
                    break;
                }
            }
            if(idxIndex_qu8 < DCM_CFG_DSP_NUMRESETTYPE){
                if(pMsgContext->reqDataLen == DCM_ECUR_REQ_LEN){

#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF))
                    Dcm_idxReset_u8 = (uint8)idxIndex_qu8 ;
#endif
                    Dcm_stEcuResetState_en = DCM_ECURESET_REQPERMISSION;
                }
                else{
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
            }
            else{
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }
            if(*dataNegRespCode_u8 != 0x0){
                Dcm_stEcuResetState_en = DCM_ECURESET_ERROR;
                dataRetVal_u8=E_NOT_OK;
            }
        }
        if(Dcm_stEcuResetState_en == DCM_ECURESET_REQPERMISSION){
            dataRetVal_u8 = DcmAppl_DcmEcuResetPreparation(Dcm_dataEcuRType_u8,dataNegRespCode_u8);
            if(E_OK == dataRetVal_u8){
                *dataNegRespCode_u8=0x00;

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
                if((Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_OEM_BOOT)||
                   (Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_SYS_BOOT)||
                   (Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_DRIVE_TO_DRIVE)){
                    Dcm_stEcuResetState_en = DCM_ECURESET_WAIT;
                }
                else
#endif
                {
                   Dcm_stEcuResetState_en = DCM_ECURESET_SENDRESPONSE;
                }
            }
            else if(dataRetVal_u8 == DCM_E_PENDING){
                *dataNegRespCode_u8=0x00;
            }
            else{
                if(*dataNegRespCode_u8 == 0x00){
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                }
                Dcm_stEcuResetState_en = DCM_ECURESET_ERROR;
                dataRetVal_u8=E_NOT_OK;
            }
        }

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
        if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT){
            if(Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_OEM_BOOT ){
                Dcm_JumpToBootLoader(DCM_JUMPTOOEMBOOTLOADER,dataNegRespCode_u8);
            }
            else if(Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_SYS_BOOT){
                Dcm_JumpToBootLoader(DCM_JUMPTOSYSSUPPLIERBOOTLOADER,dataNegRespCode_u8);
            }
            else{
                Dcm_JumpToBootLoader(DCM_JUMPDRIVETODRIVE,dataNegRespCode_u8);
            }
           dataRetVal_u8=DCM_E_PENDING;
        }
#endif

        if(Dcm_stEcuResetState_en == DCM_ECURESET_SENDRESPONSE){

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            if((Dcm_dataEcuRType_u8 != DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET) &&
               (Dcm_dataEcuRType_u8 != DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET)){
                (void)SchM_Switch_SwcServiceDcm_tEcuReset(Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].dataResetMode_u8);
            }
#if(DCM_CFG_RAPIDPOWERSHUTDOWNRESET!=DCM_CFG_OFF)
            else{
                (void)SchM_Switch_Dcm_DcmModeRapidPowerShutDown(Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].dataResetMode_u8);
            }
#endif
#endif

            pMsgContext->resData[0] = Dcm_dataEcuRType_u8;
            if(Dcm_dataEcuRType_u8 != DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET){
                pMsgContext->resDataLen = 1;
            }
            else{
                pMsgContext->resData[1] = DCM_CFG_DSP_POWER_DOWN_TIME;
                pMsgContext->resDataLen = 2;
            }

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (void)Dcm_idxReset_u8;
#endif

            Dcm_stEcuResetState_en = DCM_ECURESET_IDLE;
            dataRetVal_u8=E_OK;
        }
        if(Dcm_stEcuResetState_en == DCM_ECURESET_ERROR){
            if(*dataNegRespCode_u8==0x00){
                *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
            }

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (void)Dcm_idxReset_u8;
#endif

            Dcm_stEcuResetState_en = DCM_ECURESET_IDLE;
            dataRetVal_u8=E_NOT_OK;
        }
   }
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
