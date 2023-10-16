#include "Std_Types.hpp"

#include "v_cfg_fbl.hpp"
#include "FblHal_Cfg.hpp"
#include "applvect.hpp"
#include "compiler.hpp"

#if defined( V_COMP_GHS ) || defined( V_COMP_DIABDATA )
extern void _usr_init(void);
#define RESET_ENTRY_POINT (vuint32)_usr_init
#endif

#if defined( V_COMP_RENESAS )
extern void _start(void);
#define RESET_ENTRY_POINT (vuint32)_start
#endif

#define FBL_APPLVECT_START_SEC_CONST
#include "ApplVect_Memmap.hpp"

V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 ApplIntJmpTable[2] = {APPLVECT_FROM_APPL, RESET_ENTRY_POINT};

#define FBL_APPLVECT_STOP_SEC_CONST
#include "ApplVect_Memmap.hpp"
extern uint8 _APPLENTRY[];

#define FBLBMHDR_BMHEADER_START_SEC_CONST
#include "ApplVect_Memmap.hpp"
CONST(tFblBmHdrHeader, FBLBMHDR_CONST) FblBmHdrHeader = {
      FBLBMHDR_MAGIC_FLAG
   ,   (tFblAddress) &_APPLENTRY
   ,   FBLBMHDR_TARGET_APPL
   ,   0x00020000uL
   ,   0x00058000uL
   ,   1u
   ,  {
         {
               0x00020000uL
            ,  0x00058000uL
         }
   }
};
#define FBLBMHDR_BMHEADER_STOP_SEC_CONST
#include "ApplVect_Memmap.hpp"

#define FBLBMHDR_START_SEC_CONST
#include "ApplVect_Memmap.hpp"
CONST(uint32, FBLBMHDR_CONST) FblBmHdrTargets[FBLBMHDR_NUM_OF_TARGETS] = {
      255uL
   ,  255uL
   ,  255uL
};

#define FBLBMHDR_STOP_SEC_CONST
#include "ApplVect_Memmap.hpp"

tFblBmHdrHeader* GetPointerToApplicationHeader(void){
   return (tFblBmHdrHeader*)&FblBmHdrHeader;
}

