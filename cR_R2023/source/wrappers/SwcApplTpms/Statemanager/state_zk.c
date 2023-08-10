

#ifdef IBTCM_SW_ANPASSUNGEN
  #include "iTpms_Interface.h"
  #include "SwcApplTpms_Rte.h"
  #include "state_zk.h"
  #include "state_zkx.h"
  #include "statemanagerX.h"
#else
  #include "state_zk.h"
  #include "state_zkx.h"
  #include "statemanagerX.h"
#endif

static uint16 ushZustandskennung;

void InitZK( void )
{
  ClearBitZustandskennungZK( cZK_ALLE_BITS );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION

void SetBitZustandskennungZK( uint16 ushBitMask )
{
   ushZustandskennung |= ushBitMask;
}
#endif //BUILD_WITH_UNUSED_FUNCTION

void ClearBitZustandskennungZK( uint16 ushBitMask )
{
   ushZustandskennung &= ~ushBitMask;
}

boolean bGetBitZustandskennungZK( uint16 ushBitMask )
{
   return (boolean) ((ushZustandskennung & ushBitMask) != 0 );
}

#ifdef BUILD_WITH_UNUSED_FUNCTION
uint16 ushGetZustandskennungZK( uint16 ushBitMask )
{
   return (ushZustandskennung & ushBitMask);
}
#endif

void SetChangedBit4WP( uint8 ucWP)
{

  switch (ucWP)
  {
    case (uint8) 0:
    {
      ushZustandskennung |= cPOS_CHANGED_VL;
      break;
    }
    case (uint8) 1:
    {
      ushZustandskennung |= cPOS_CHANGED_VR;
      break;
    }
    case (uint8) 2:
    {
      ushZustandskennung |= cPOS_CHANGED_HL;
      break;
    }
    case (uint8) 3:
    {
      ushZustandskennung |= cPOS_CHANGED_HR;
      break;
    }
    default:
    {
      ushZustandskennung |= (cPOS_CHANGED_VL | cPOS_CHANGED_VR | cPOS_CHANGED_HL| cPOS_CHANGED_HR);
      break;
    }
  }

}
