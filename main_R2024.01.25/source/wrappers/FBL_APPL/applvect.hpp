#ifndef __APPL_VECT_H__
#define __APPL_VECT_H__

#include "Types.hpp"
#include "v_def.hpp"
#include "fbl_def.hpp"

#define FBLVTABAPPL_RH850_VERSION          0x0104
#define FBLVTABAPPL_RH850_RELEASE_VERSION  0x00
#define APPLVECT_FROM_BOOT       0xA5000000UL
#define APPLVECT_FROM_APPL       0xAA000000UL
#define cBootmanHeaderAddress (0x300u)

#define FBL_APPLVECT_START_SEC_CONST
# include "ApplVect_Memmap.hpp"
V_MEMROM0 extern V_MEMROM1 vuint32 V_MEMROM2 ApplIntJmpTable[2];
#define FBL_APPLVECT_STOP_SEC_CONST
#include "ApplVect_Memmap.hpp"

#define FBLBMHDR_MAGIC_FLAG 0xB14E9B4AuL
#define FBLBMHDR_NUM_OF_VERIFICATION_ENTRIES 1uL
#define FBLBMHDR_NUM_OF_TARGETS 3uL
#define FBLBMHDR_ENTRY_ADDRESS_INVALID 0xFFFFFFFFuL

typedef enum {
      FBLBMHDR_TARGET_FBL = 0
   ,     FBLBMHDR_TARGET_FBLUPDATER = 1
   ,     FBLBMHDR_TARGET_APPL = 2
} tFblBmHdrTargetHandle;

typedef struct
   {
       vuint32 address;
       vuint32 length;
} tFblBmHdrVerificationList;

typedef struct
   {
       vuint32                    bmMagicFlag;
       tFblAddress                bmEntryAddress;
       tFblBmHdrTargetHandle      bmTargetHandle;
       tFblAddress                bmBlockStartAddress;
       tFblLength                 bmBlockLength;
       vuint8                     bmVerificationListEntries;
       tFblBmHdrVerificationList  bmVerificationList[FBLBMHDR_NUM_OF_VERIFICATION_ENTRIES];
} tFblBmHdrHeader;

#define FBLBM_MAIN_ENABLE_FBL_START
#define FBLBM_HEADER_MAGIC_VALUE          0x05ECB007u
#define FBLBM_HEADER_MAJOR_VERSION        0x0001u
#define FBLBM_HEADER_MINOR_VERSION        0x0000u
#define FBLBM_HEADER_END_MAGIC_VALUE      0xCEC41160u
#define FBL_HEADER_ADDRESS                0x00000360uL
#define FBL_CALL_TYPE

typedef FBL_CALL_TYPE void (*tFblStrtFct)(
   void);

typedef FBL_CALL_TYPE void (*tApplStrtFct)(
   void);

typedef struct
   {
       vuint32 magic;
       vuint16 majorVersion;
       vuint16 minorVersion;
       tFblAddress fblHeaderAddress;
       tFblStrtFct pFblStartFct;
       tApplStrtFct pApplStartFct;
       vuint32 checksum;
       vuint32 end_magic;
} tFblBmHeader;

extern tFblBmHdrHeader* GetPointerToApplicationHeader(void);

#endif

