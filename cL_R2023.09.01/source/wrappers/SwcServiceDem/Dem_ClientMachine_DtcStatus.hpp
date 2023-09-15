

#ifndef DEM_CLIENTMACHINE_DTCSTATUS_H
#define DEM_CLIENTMACHINE_DTCSTATUS_H

#include "Dem_DTCStatusByte.hpp"
#include "Dem_DTCs.hpp"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

DEM_INLINE void  Dem_ClientMachineGetStatus_SetClientRequest(Dem_ClientIdType clientId)
{
   boolean DtcStatusIsValid;
   uint8 newDTCStatus;
    Dem_ClientState *client = Dem_Client_getClient(clientId);

   if(Dem_ClientSelectionType_isSelectionSingleDTC(client->selection)
            && Dem_DtcUsesOrigin(Dem_ClientSelectionType_getSelectionDtcIndex(client->selection), client->data.standard.DTCOrigin))
   {

        newDTCStatus = Dem_DtcStatusByteRetrieveWithOrigin(Dem_ClientSelectionType_getSelectionDtcIndex(client->selection)
   ,               client->data.standard.DTCOrigin, &DtcStatusIsValid) & ((uint8) DEM_CFG_DTCSTATUS_AVAILABILITYMASK);

        if(!DtcStatusIsValid)
        {
            Dem_ClientResultType_setResult(&client->result, client->request, DEM_NO_SUCH_ELEMENT);
        }
        else{
            client->data.standard.DTCStatus = newDTCStatus;

            Dem_ClientResultType_setResult(&client->result, client->request, E_OK);
        }
   }
   else{
        Dem_ClientResultType_setResult(&client->result, client->request, DEM_WRONG_DTC);
   }
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

#endif
