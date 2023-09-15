

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

LOCAL_INLINE void Dcm_Lok_SetComMState(uint8 NetworkId,Dcm_Dsld_commodeType ComManagerState)
{
   uint8 idxNetwork_u8;

   for(idxNetwork_u8 = 0;idxNetwork_u8<DCM_NUM_COMM_CHANNEL;idxNetwork_u8++)
   {
        if(Dcm_active_commode_e[idxNetwork_u8].ComMChannelId == NetworkId)
        {
            break;
        }
   }

   if(idxNetwork_u8 < DCM_NUM_COMM_CHANNEL)
   {
        Dcm_active_commode_e[idxNetwork_u8].ComMState = ComManagerState;
   }
}

void Dcm_ComM_FullComModeEntered(uint8 NetworkId)
{

    Dcm_Lok_SetComMState(NetworkId,DCM_DSLD_FULL_COM_MODE);
}

void Dcm_ComM_NoComModeEntered(uint8 NetworkId)
{

    Dcm_Lok_SetComMState(NetworkId,DCM_DSLD_NO_COM_MODE);
}

void Dcm_ComM_SilentComModeEntered(uint8 NetworkId)
{

    Dcm_Lok_SetComMState(NetworkId,DCM_DSLD_SILENT_COM_MODE);
}

Std_ReturnType Dcm_SetActiveDiagnostic(boolean active)
{

   if(active != FALSE)
   {
       Dcm_ActiveDiagnosticState_en = DCM_COMM_ACTIVE;
   }
   else{
       Dcm_ActiveDiagnosticState_en = DCM_COMM_NOT_ACTIVE;
   }
   return(E_OK);
}

void Dcm_CheckActiveDiagnosticStatus(uint8 dataNetworkId)
{

   if(Dcm_ActiveDiagnosticState_en == DCM_COMM_ACTIVE)
   {
        ComM_DCM_ActiveDiagnostic(dataNetworkId);
   }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
