

#include "fbl_def.hpp"

#define JSR(x) (*((void(*)(void))x))()

#define FBLBMHDR_NUM_OF_VERIFICATION_ENTRIES 1uL

typedef enum{
  FBLBMHDR_TARGET_FBL = 0
   ,  FBLBMHDR_TARGET_FBLUPDATER = 1
   ,  FBLBMHDR_TARGET_APPL = 2
}tFblBmHdrTargetHandle;

typedef struct{
  vuint32 address;
  vuint32 length;
}tFblBmHdrVerificationList;

typedef struct{
  vuint32                     bmMagicFlag;
  tFblAddress                bmEntryAddress;
  tFblBmHdrTargetHandle      bmTargetHandle;
  tFblAddress                bmBlockStartAddress;
  tFblLength                 bmBlockLength;
  vuint8                     bmVerificationListEntries;
  tFblBmHdrVerificationList  bmVerificationList[FBLBMHDR_NUM_OF_VERIFICATION_ENTRIES];
}tFblBmHdrHeader;

int __usr_init(void);