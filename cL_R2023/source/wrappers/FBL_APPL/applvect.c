

#include "v_cfg_fbl.h"    // RST: renamed this file to _fbl because the same file with different content exist in MEM
#if defined V_GEN_GENERATOR_MSR
# include "FblHal_Cfg.h"  //V_COMP_GHS is defined there
#endif

#include "applvect.h"
#include "compiler.h"

#if ( FBLVTABAPPL_RH850_VERSION != 0x0104 ) || \
    ( FBLVTABAPPL_RH850_RELEASE_VERSION != 0x00 )
# error "Error in applvect.c: Source and header file are inconsistent!"
#endif

#if defined( V_COMP_GHS ) || \
    defined( V_COMP_DIABDATA )
extern void _usr_init( void );
#define RESET_ENTRY_POINT (vuint32)_usr_init
#endif

#if defined( V_COMP_IAR )
extern void _iar_program_start( void );
#define RESET_ENTRY_POINT (vuint32)_iar_program_start
#endif

#if defined( V_COMP_RENESAS )
extern void _start( void );
#define RESET_ENTRY_POINT (vuint32)_start
#endif

// RST Info: this is original applvect.c from demo application
#define FBL_APPLVECT_START_SEC_CONST
#include "ApplVect_Memmap.h"

V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 ApplIntJmpTable[2] = {APPLVECT_FROM_APPL, RESET_ENTRY_POINT};

#define FBL_APPLVECT_STOP_SEC_CONST
#include "ApplVect_Memmap.h"

  // RST Info: this is copied from FblBmHdr_Lcfg.c from demo application -> definition of the application header

  extern uint8 _APPLENTRY[];

  #define FBLBMHDR_BMHEADER_START_SEC_CONST
  #include "ApplVect_Memmap.h"
  CONST(tFblBmHdrHeader, FBLBMHDR_CONST) FblBmHdrHeader =
  {
    FBLBMHDR_MAGIC_FLAG,
    (tFblAddress) &_APPLENTRY,
    FBLBMHDR_TARGET_APPL,
    0x00020000uL,
    //0x00020000uL,
    0x00058000uL,   //RST Note: this is the length of the application. It is defined in FBL logical block table. If the FBL block table is changed, this value must be changed manually!
    1u,
    {
      {
        0x00020000uL,
        //0x00020000uL, RST: new length 0x58000
        0x00058000uL
      }
    }
  };
  #define FBLBMHDR_BMHEADER_STOP_SEC_CONST
  #include "ApplVect_Memmap.h"

  #define FBLBMHDR_START_SEC_CONST
  #include "ApplVect_Memmap.h"

  CONST(uint32, FBLBMHDR_CONST) FblBmHdrTargets[FBLBMHDR_NUM_OF_TARGETS] =
  {
    255uL  ,
    255uL  ,
    255uL
  };

  #define FBLBMHDR_STOP_SEC_CONST
  #include "ApplVect_Memmap.h"

tFblBmHdrHeader* GetPointerToApplicationHeader(void)
{
  return (tFblBmHdrHeader*)&FblBmHdrHeader;
}

