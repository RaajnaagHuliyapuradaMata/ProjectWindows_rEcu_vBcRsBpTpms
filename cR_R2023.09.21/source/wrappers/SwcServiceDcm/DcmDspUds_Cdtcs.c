#include "Std_Types.hpp"

#include "DcmDspUds_Cdtcs_Inf.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
VAR( boolean, DCM_VAR)  Dcm_DspCDTCStatus_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
FUNC(void,DCM_CODE) Dcm_Dsp_CDTCSIni(void){
    Dcm_DspCDTCStatus_b = TRUE;
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tControlDTCSetting(
        VAR(Dcm_SrvOpStatusType,          AUTOMATIC                 ) OpStatus
   ,  P2VAR(Dcm_MsgContextType,           AUTOMATIC, DCM_INTERN_DATA) pMsgContext
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8
){
   VAR(Dem_ReturnControlDTCSettingType, AUTOMATIC) dataDemRetVal_u8           = DEM_CONTROL_DTC_SETTING_N_OK;
   VAR(uint8,                           AUTOMATIC) dataDtcSettingType_u8      = pMsgContext->reqData[DCM_PRV_CDTC_POSITION_SUBFUNC];
   VAR(Std_ReturnType,                  AUTOMATIC) dataRetSetCtrlOpRectype_u8 = E_OK;
   VAR(uint16,                          AUTOMATIC) nrReqLen_u16               = DCM_PRV_CDTC_REQUEST_LENGTH;
   VAR(uint32,                          AUTOMATIC) dataDTC_u32                = DEM_DTC_GROUP_ALL_DTCS;
   VAR(Std_ReturnType,                  AUTOMATIC) dataServRetval_u8          = E_NOT_OK;
                                                   *dataNegRespCode_u8        = 0;
   if(
         OpStatus
      == DCM_CANCEL
   ){
      Dcm_Dsp_CDTCSIni();
      dataServRetval_u8 = E_OK;
   }
   else{
      if(
            (dataDtcSettingType_u8 == DCM_PRV_CDTC_OFF)
         || (dataDtcSettingType_u8 == DCM_PRV_CDTC_ON)
      ){
         if(
               pMsgContext->reqDataLen
            == nrReqLen_u16
         ){
            if(
                  nrReqLen_u16
               >  DCM_PRV_CDTC_REQUEST_LENGTH
            ){
               dataRetSetCtrlOpRectype_u8 = DcmAppl_DcmCheckCDTCRecord(
                     &pMsgContext->reqData[1]
                  ,  DCM_PRV_CDTC_RECORD_LENGTH
                  ,  dataNegRespCode_u8
               );
            }
            if(
                  dataRetSetCtrlOpRectype_u8
               == E_OK
            ){
               *dataNegRespCode_u8 = 0x00;
               if(
                     dataDtcSettingType_u8
                  == DCM_PRV_CDTC_OFF
               ){
                  DcmAppl_DisableDTCSetting(
                     dataNegRespCode_u8
                  );
                  if(
                        *dataNegRespCode_u8
                     == 0x00
                  ){
                     dataDemRetVal_u8 = Dem_DisableDTCSetting(
                           dataDTC_u32
                        ,  DEM_DTC_KIND_ALL_DTCS
                     );
                     if(
                           dataDemRetVal_u8
                        == DEM_CONTROL_DTC_SETTING_OK
                     ){
                        Dcm_DspCDTCStatus_b = FALSE;
                        DcmAppl_DcmControlDtcSettingEnableStatus(
                           Dcm_DspCDTCStatus_b
                        );
                     }
                     else if(
                           dataDemRetVal_u8
                        == DEM_CONTROL_DTC_WRONG_DTCGROUP
                     ){
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        dataServRetval_u8   = E_NOT_OK;
                     }
                     else{
                        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                        dataServRetval_u8   = E_NOT_OK;
                     }
                  }
               }
               else{
                  dataDemRetVal_u8 = Dem_EnableDTCSetting(
                        dataDTC_u32
                     ,  DEM_DTC_KIND_ALL_DTCS
                  );
                  if(
                        dataDemRetVal_u8
                     == DEM_CONTROL_DTC_SETTING_OK
                  ){
                     Dcm_DspCDTCStatus_b = TRUE;
                     DcmAppl_DcmControlDtcSettingEnableStatus(
                        Dcm_DspCDTCStatus_b
                     );
                  }
                  else if(
                        dataDemRetVal_u8
                     == DEM_CONTROL_DTC_WRONG_DTCGROUP
                  ){
                     *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                     dataServRetval_u8   = E_NOT_OK;
                  }
                  else{
                     *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                     dataServRetval_u8   = E_NOT_OK;
                  }
               }
            }
            else{
               if(
                     *dataNegRespCode_u8
                  == 0x00
               ){
                  *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                  dataServRetval_u8   = E_NOT_OK;
               }
            }
         }
         else{
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataServRetval_u8   = E_NOT_OK;
         }
      }
      else{
         *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
         dataServRetval_u8   = E_NOT_OK;
      }
      if(
            *dataNegRespCode_u8
         == 0
      ){
         pMsgContext->resDataLen                             = 0x01;
         pMsgContext->resData[DCM_PRV_CDTC_POSITION_SUBFUNC] = dataDtcSettingType_u8;
         dataServRetval_u8                                   = E_OK;
      }
      else{
         dataServRetval_u8 = E_NOT_OK;
      }
   }
   return dataServRetval_u8;
}

FUNC(boolean,DCM_CODE) Dcm_GetControlDTCSetting_EnableStatus(void){
   return Dcm_DspCDTCStatus_b;
}

FUNC(void, DCM_CODE) Dcm_ControlDtcSettingExit(void){
   VAR(uint8,                           AUTOMATIC) idxCdtc_u8;
   VAR(Dem_ReturnControlDTCSettingType, AUTOMATIC) dataDemRetVal_u8;
   VAR(uint32,                          AUTOMATIC) session_active_u32;
   VAR(uint32,                          AUTOMATIC) allowed_session_u32;

   idxCdtc_u8 = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].cdtc_index_u8;

   if(
         idxCdtc_u8
      != 0xFFu
   )   {allowed_session_u32 = CfgSwcServiceDcm_stDsld.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxCdtc_u8].allowed_session_b32;}
   else{allowed_session_u32 = 0xffffffffu;}

   session_active_u32 = (uint32)(0x00000001uL << Dcm_DsldGlobal_st.idxActiveSession_u8);

   if(
         (
               session_active_u32
            == (uint32)DCM_DEFAULT_SESSION
         )
      || (
               (
                     allowed_session_u32
                  &  session_active_u32
               )
            != session_active_u32
         )
   ){
      if(
            Dcm_DspCDTCStatus_b
         == FALSE
      ){
         dataDemRetVal_u8 = Dem_EnableDTCSetting(
               DEM_DTC_GROUP_ALL_DTCS
            ,  DEM_DTC_KIND_ALL_DTCS
         );
         if(
               dataDemRetVal_u8
            == DEM_CONTROL_DTC_SETTING_OK
         ){
            Dcm_DspCDTCStatus_b = TRUE;
            DcmAppl_DcmControlDtcSettingEnableStatus(
               Dcm_DspCDTCStatus_b
            );
         }
      }
   }
}

FUNC(void,DCM_CODE) Dcm_CDTCModeStatusCheck(void){
   VAR(uint8,                           AUTOMATIC) dataNegRespCode_u8;
   VAR(Dem_ReturnControlDTCSettingType, AUTOMATIC) dataDemRetVal_u8;
   dataNegRespCode_u8 = 0x00;
   if(
         Dcm_DspCDTCStatus_b
      == FALSE
   ){
      if(
            dataNegRespCode_u8
         != 0u
      ){
         dataDemRetVal_u8 = Dem_EnableDTCSetting(
               DEM_DTC_GROUP_ALL_DTCS
            ,  DEM_DTC_KIND_ALL_DTCS
         );
         if(
               dataDemRetVal_u8
            == DEM_CONTROL_DTC_SETTING_OK
         ){
            Dcm_DspCDTCStatus_b = TRUE;
            DcmAppl_DcmControlDtcSettingEnableStatus(
               Dcm_DspCDTCStatus_b
            );
         }
      }
   }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
