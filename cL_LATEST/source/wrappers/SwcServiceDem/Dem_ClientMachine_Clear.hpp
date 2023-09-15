

#ifndef DEM_CLIENTCLEARMACHINE_H
#define DEM_CLIENTCLEARMACHINE_H

#include "Dem_ClientHandlingTypes.hpp"
#include "Dem_ClientBaseHandling.hpp"
#include "Dem_Client.hpp"
#include "Dem_Types.hpp"
#include "Dem_Mapping.hpp"
#include "Dem_Nvm.hpp"
#include "Dem_Cfg_Clear.hpp"

#define DEM_CLEAR_DTC_MACHINE_STATE_IDLE            0x00u
#define DEM_CLEAR_DTC_MACHINE_STATE_EXEC            0x01u
#define DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM   0x02u

typedef struct{
  uint8                           activeClient;
  uint8                           machine_state;

  boolean                         IsNewClearRequest;

  boolean                         IsClearInterrupted;

  uint16                          NumberOfEventsProcessed;

  Dem_DtcIdListIterator           DtcIt;
  Dem_EventIdIterator             EvtIt;
  Dem_EventIdListIterator         EvtListIt;
#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
  Dem_DtcIdListIterator2          DtcIt2;
#endif
}Dem_ClientClearMachineType;

#define DEM_START_SEC_VAR_CLEARED
#include "Dem_MemMap.hpp"

extern Dem_ClientClearMachineType Dem_ClientClearMachine;

#define DEM_STOP_SEC_VAR_CLEARED
#include "Dem_MemMap.hpp"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

DEM_INLINE void Dem_ClientClearMachine_SetMachineActiveClient(Dem_ClientIdType ClientId)
{
    Dem_ClientClearMachine.activeClient = ClientId;
}

DEM_INLINE boolean Dem_ClientClearMachine_isProcessingClient(Dem_ClientIdType ClientId)
{
    return (Dem_ClientClearMachine.activeClient == ClientId);
}

DEM_INLINE uint8 Dem_ClientClearMachine_GetMachineActiveClient(void){
    return Dem_ClientClearMachine.activeClient;
}

DEM_INLINE void Dem_ClientClearMachine_SetMachineState(uint8 state)
{
    Dem_ClientClearMachine.machine_state = state;
}

DEM_INLINE uint8 Dem_ClientClearMachine_GetMachineState(void){
    return Dem_ClientClearMachine.machine_state;
}

DEM_INLINE void Dem_ClientMachineClear_SetClientRequest(Dem_ClientIdType ClientId)
{
   if((Dem_Client_GetClientType(ClientId) == DEM_CLIENTTYPE_STANDARD)
            && (Dem_LibGetParamBool(DEM_CFG_CLEAR_DTC_LIMITATION == DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS)
            && (Dem_ClientSelectionType_getTypeOfSelection(Dem_AllClientsState[ClientId].selection) != DEM_CLIENT_SELECTION_TYPE_ALL_DTCS)))
   {
        Dem_ClientResultType_setResult(&Dem_AllClientsState[ClientId].result, Dem_AllClientsState[ClientId].request, DEM_WRONG_DTC);
   }
   else{
        if(Dem_ClientClearMachine_GetMachineState() == DEM_CLEAR_DTC_MACHINE_STATE_IDLE)
        {
            Dem_ClientClearMachine.IsNewClearRequest = TRUE;
            Dem_ClientClearMachine_SetMachineActiveClient(ClientId);
            Dem_NvMStartClear();
            Dem_ClientClearMachine_SetMachineState(DEM_CLEAR_DTC_MACHINE_STATE_EXEC);
        }
        else if(Dem_ClientClearMachine_GetMachineActiveClient() != ClientId)
        {
            Dem_ClientResultType_setResult(&Dem_Client_getClient(ClientId)->result,Dem_Client_getClient(ClientId)->request,DEM_CLEAR_BUSY);
        }
        else{

        }
   }
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

#endif
