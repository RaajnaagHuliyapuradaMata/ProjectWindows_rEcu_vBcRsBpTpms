

#include "Dem.hpp"
#include "Rte_Dem.hpp"

#include "Dem_EvMemGen.hpp"

#include "Dem_Main.hpp"
#include "Dem_Client.hpp"
#include "Dem_Obd.hpp"

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"
#if( DEM_CFG_EVMEMGENERIC_SUPPORTED != FALSE )
Std_ReturnType Dem_GetDTCByOccurrenceTime(uint8 ClientId, Dem_DTCRequestType DTCRequest, uint32* DTC)
{
    Dem_DtcIdType DtcId;
    Std_ReturnType retVal = E_NOT_OK;

   if(!Dem_OpMoIsInitialized())
   {
        DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_UNINIT,0u);
   }

   else if(!Dem_isClientIdValid(ClientId))
   {
        DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_WRONG_CONFIGURATION,0u);
   }

   else if((DTCRequest != DEM_FIRST_FAILED_DTC) &&
            (DTCRequest != DEM_MOST_RECENT_FAILED_DTC) &&
            (DTCRequest != DEM_FIRST_DET_CONFIRMED_DTC) &&
            (DTCRequest != DEM_MOST_REC_DET_CONFIRMED_DTC)
#if(DEM_CFG_OBD == DEM_CFG_OBD_ON)
            && (DTCRequest != DEM_FIRST_FAILED_OBD_DTC)
            && (DTCRequest != DEM_MOST_RECENT_FAILED_OBD_DTC)
#endif
            )
   {
        DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_WRONG_CONFIGURATION,0u);
   }

   else{

        DtcId = Dem_EvMemGenGetDtcIdByOccIndex(DTCRequest);

        if(!Dem_isDtcIdValid(DtcId))
        {
            retVal = DEM_NO_SUCH_ELEMENT;
        }
        else{
#if(DEM_CFG_OBD == DEM_CFG_OBD_ON)

            if((DTCRequest == DEM_FIRST_FAILED_OBD_DTC) || (DTCRequest == DEM_MOST_RECENT_FAILED_OBD_DTC))
            {
                *DTC = (uint32) rba_DemObdBasic_Dtc_GetCode(DtcId);
                retVal = E_OK;
            }
            else
#endif
            {

                *DTC = (uint32) Dem_GetDtcCode(DtcId);
                retVal = E_OK;
            }
        }
   }

    return retVal;
}
#endif

Std_ReturnType Dem_GetEventMemoryOverflow(uint8 ClientId, Dem_DTCOriginType DTCOrigin, boolean* OverflowIndication)
{
   if(Dem_LibGetParamBool(DEM_CFG_EVMEMGENERIC_SUPPORTED))
   {

       DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW,E_NOT_OK);
       DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(OverflowIndication,DEM_DET_APIID_GETEVENTMEMORYOVERFLOW,E_NOT_OK);

       if(!Dem_isClientIdValid(ClientId))
       {
           DEM_DET(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW, DEM_E_WRONG_CONFIGURATION,0u);
           return E_NOT_OK;
       }

      if(!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
      {
         DEM_DET(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW, DEM_E_WRONG_CONFIGURATION,0u);
         return E_NOT_OK;
      }

      *OverflowIndication = Dem_EvMemGenIsOverflow(DTCOrigin);
      return E_OK;
   }
   else{
      DEM_DET(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW, DEM_E_WRONG_CONDITION,0u);
      return E_NOT_OK;
   }
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

