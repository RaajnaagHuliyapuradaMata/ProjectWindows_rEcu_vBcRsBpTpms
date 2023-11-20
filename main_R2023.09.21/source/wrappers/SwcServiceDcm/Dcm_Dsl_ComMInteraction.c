#include "Std_Types.hpp"

#include "DcmCore_DslDsd_Inf.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_Lok_SetComMState(
   VAR(uint8, AUTOMATIC) NetworkId,
   VAR(Dcm_Dsld_commodeType,AUTOMATIC) ComManagerState){
   VAR(uint8,AUTOMATIC)idxNetwork_u8;
   for(idxNetwork_u8 = 0; idxNetwork_u8 < DCM_NUM_COMM_CHANNEL;
         idxNetwork_u8++){
      if(Dcm_active_commode_e[idxNetwork_u8].ComMChannelId == NetworkId){
            break;
        }
   }
   if(idxNetwork_u8 < DCM_NUM_COMM_CHANNEL){
        Dcm_active_commode_e[idxNetwork_u8].ComMState = ComManagerState;
   }
}

FUNC(void,DCM_CODE) Dcm_ComM_FullComModeEntered(
   VAR(uint8, AUTOMATIC) NetworkId){
    Dcm_Lok_SetComMState(NetworkId,DCM_DSLD_FULL_COM_MODE);
}

FUNC(void,DCM_CODE) Dcm_ComM_NoComModeEntered(
   VAR(uint8, AUTOMATIC) NetworkId){
    Dcm_Lok_SetComMState(NetworkId,DCM_DSLD_NO_COM_MODE);
}

FUNC(void,DCM_CODE) Dcm_ComM_SilentComModeEntered(
   VAR(uint8, AUTOMATIC) NetworkId){
    Dcm_Lok_SetComMState(NetworkId,DCM_DSLD_SILENT_COM_MODE);
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveDiagnostic(
   VAR(boolean, AUTOMATIC) active){
   if(active != FALSE){
       Dcm_ActiveDiagnosticState_en = DCM_COMM_ACTIVE;
   }
   else{
       Dcm_ActiveDiagnosticState_en = DCM_COMM_NOT_ACTIVE;
   }
   return(E_OK);
}

FUNC(void,DCM_CODE) Dcm_CheckActiveDiagnosticStatus(
   VAR(uint8,AUTOMATIC) dataNetworkId){
   if(Dcm_ActiveDiagnosticState_en == DCM_COMM_ACTIVE){
        ComM_DCM_ActiveDiagnostic(dataNetworkId);
   }
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
