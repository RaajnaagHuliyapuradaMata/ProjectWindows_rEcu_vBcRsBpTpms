

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.h"
  #include "SwcApplTpms_Rte.h"
  #include "SwcApplTpms_NvM_If.h"
  #include "state_bz.h"
  #include "statemanagerX.h"
  #include "wallocX.h"
  #include "State_BzX.h"
  #include "SwcApplTpms_DevCanMesReqInterfaces.h"
#else
  #include "state_bz.h"
  #include "statemanagerX.h"
  #include "IDOM_X.h"
  #include "errmemX.h"
#endif

static uint16 ushBetriebszustand;

void InitBZ( void )
{
  uint8 ucLocalWAState;

#ifdef IBTCM_SW_ANPASSUNGEN

#else
  CheckDTCInactive();
#endif

#ifdef FILTER_SYMC_CAN_MSGS
  ClearBitBetriebszustandBZ( cER_FINISH  | cTO_MUCH_RE   | cER_LEARNING        | cEIGENRAD  |       \
                             cZUGEORDNET | cWA_FINISH    | cHIST_PRELOAD       | cZO_FINISH |       \
                             cZO_TIMEOUT | cTEILEIGENRAD | cALL_ER_PRESSURE_RX | cSEND_RE_DATA_ON_CAN |   \
                             cWA_STARTED);
#else
  ClearBitBetriebszustandBZ( cER_FINISH | cTO_MUCH_RE | cER_LEARNING | cEIGENRAD | cZUGEORDNET | cWA_FINISH | cHIST_PRELOAD | cZO_FINISH | cZO_TIMEOUT  | cTEILEIGENRAD | cWA_STARTED);
#endif

  ucLocalWAState = WAInit();
  if( (ucLocalWAState & cHiStateZG) == cHiStateZG )
  {
    SetBitBetriebszustandBZ( cEIGENRAD | cZUGEORDNET | cHIST_PRELOAD);
  }
  else
  {
    if( (ucLocalWAState & cHiStateER) == cHiStateER )
    {
      SetBitBetriebszustandBZ( cEIGENRAD | cHIST_PRELOAD);
    }
  }

  SetBitBetriebszustandBZ(cER_LEARNING);
}

void SetBitBetriebszustandBZ( uint16 ushBitMask )
{
   ushBetriebszustand |= ushBitMask;
}

void ClearBitBetriebszustandBZ( uint16 ushBitMask )
{
   ushBetriebszustand &= ~ushBitMask;
}

boolean bGetBitBetriebszustandBZ( uint16 ushBitMask )
{
   return (boolean) ((ushBetriebszustand & ushBitMask) != 0 );
}

uint16 ushGetBetriebszustandBZ( uint16 ushBitMask )
{
   return (ushBetriebszustand & ushBitMask);
}

void EvVehicleSpeedChangedBZ( uint16 ushNewVehicleSpeed)
{
  if(ushNewVehicleSpeed >= (uint16)WALLOC_ucGetMinSpeedAutoLearnStart())
  {
    SetBitBetriebszustandBZ(cWA_STARTED);
  }
  else
  {

  }
}

uint16 DCM_InvIf_TPMSStateGetStatus(void)
{
  return ushGetBetriebszustandBZ(0xFFFF);
}

