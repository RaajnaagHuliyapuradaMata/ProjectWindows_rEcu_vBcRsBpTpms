#include "Std_Types.hpp"

#include "SwcApplDcm_MsgAuthentication.hpp"
#include "hmac_sha2.hpp"
#include "FeeFblBlockInterfaceX.hpp"
#include "Dcm.hpp"

#define INIT_SID_1 { cSidReadDataByIdent , cDidBootSwFingerprint, cDidApplSwFingerprint, cDidProgImgBL     , cDidProgImgAPP1  , cDidKeyGenCounters, cDidManufSuppMode, cDidEepBlockStatus }
#define INIT_SID_2 { cSidWriteDataByIdent, cDidBootSwFingerprint, cDidApplSwFingerprint, cDidKeyGenCounters, 0, 0, 0, 0 }
#define INIT_SID_3 { cSidRoutineControl  , cRidSelfTest         , cRidKeyExchange      , 0, 0, 0, 0, 0 }
#define INIT_SID_4 { cSidEcuReset        , cSubFuncHardReset    , cSubFuncSoftReset    , cSubFuncHRwoResp  , cSubFuncSRwoResp , cSubFuncResUDSTimer, 0, 0 }

#define INIT_MSG_AUTHENTICATION_LIST { INIT_SID_1,\
                                       INIT_SID_2,\
                                       INIT_SID_3,\
                                       INIT_SID_4 }

static const uint16 aushAuthList[NO_OF_SID][NO_OF_DID_RID] = INIT_MSG_AUTHENTICATION_LIST;

uint8 DcmCheckMessageAuthentication(uint8 ucSid, const uint8* aucMessage, uint16 ushLength){
  uint16 ushSubFunc;
  uint8  au8Hash[cSIZE_OF_HASH];
  uint8  i;
  uint8  ucRetVal = MSG_NO_AUTH_NEEDED;
  uint8  aucKey[kEepSizeSecKey_UDSMSGKEY];
  DcmGetSubFunctionFromMessageBuffer(ucSid, aucMessage, &ushSubFunc);
  if(DcmAuthenticationNeeded(ucSid, ushSubFunc) == TRUE){
   if(DcmHashExist(ucSid, ushSubFunc, (uint32)ushLength) == TRUE){
      FEEFBL_GetUdsMsgKey(aucKey);
      if(DcmKeyExist(aucKey, kEepSizeSecKey_UDSMSGKEY) == TRUE){
        ushLength -= cSIZE_OF_HASH;
        hmac_sha256(aucKey, kEepSizeSecKey_UDSMSGKEY, aucMessage, ushLength, au8Hash, cSIZE_OF_HASH);
        ucRetVal = MSG_AUTH_SUCCESSFUL;
        for(i=0; i<cSIZE_OF_HASH; i++){
          if(aucMessage[ushLength+i] != au8Hash[i]){
            ucRetVal = MSG_REJECTED;
          }
        }
      }
      else{
        ucRetVal = MSG_AUTH_SUCCESSFUL;
      }
   }
  }
  return ucRetVal;
}

uint8 DcmAppendMessageAuthentication(uint8 ucSid, uint8* alptru8DataToAdd, uint32 ushLength, uint8* ucResponseMessage){
  uint16 ushSubFunc;
  uint8 ucRetVal = 0;
  uint8 aucKey[kEepSizeSecKey_UDSMSGKEY];
  if(DcmGetSubFunctionFromMessageBuffer(ucSid, (const uint8*)ucResponseMessage, &ushSubFunc) == TRUE){
   if(DcmAuthenticationNeeded(ucSid, ushSubFunc) == TRUE){
      FEEFBL_GetUdsMsgKey(aucKey);
      if(DcmKeyExist(aucKey, kEepSizeSecKey_UDSMSGKEY) == TRUE){
        hmac_sha256(aucKey, kEepSizeSecKey_UDSMSGKEY, (const uint8*)ucResponseMessage, ushLength, alptru8DataToAdd, cSIZE_OF_HASH);
        ucRetVal = cSIZE_OF_HASH;
      }
   }
  }
  return ucRetVal;
}

static boolean DcmGetSubFunctionFromMessageBuffer(uint8 ucSID, const uint8* aucMessage, uint16* ushSubFunc){
   boolean bRetVal = TRUE;
   switch(ucSID){
      case cSidReadDataByIdent:
      case cSidWriteDataByIdent: *ushSubFunc = (aucMessage[0] << 8) + aucMessage[1]; break;
      case cSidRoutineControl:   *ushSubFunc = (aucMessage[1] << 8) + aucMessage[2]; break;
      case cSidEcuReset:         *ushSubFunc = aucMessage[0] & 0xff;                 break;
      default:                  *ushSubFunc = 0x0;                 bRetVal = FALSE; break;
   }
   return bRetVal;
}

static boolean DcmHashExist(uint8 ucSid, uint16 ushDidRid, uint32 ulServiceLength){
  Dcm_DIDIndexType_tst tIndex;
  uint32 ulDidDataLength;
  boolean bRetVal = FALSE;
  switch(ucSid){
   case cSidReadDataByIdent:
   if(ulServiceLength == 18){
      bRetVal = TRUE;
   }
   break;

   case cSidEcuReset:
   if(ulServiceLength == 17){
      bRetVal = TRUE;
   }
   break;

   case cSidRoutineControl:
   if(ulServiceLength == 19){
      bRetVal = TRUE;
   }
   break;

   case cSidWriteDataByIdent:
   if(Dcm_GetIndexOfDID(ushDidRid, &tIndex) == E_OK){
      Dcm_GetLengthOfDIDIndex(&tIndex, &ulDidDataLength, ushDidRid);
      if((ulServiceLength > 18) && ((ulDidDataLength + 18) == ulServiceLength)){
        bRetVal = TRUE;
      }
   }
   break;

    default:
   break;
  }
  return bRetVal;
}

static boolean DcmAuthenticationNeeded(uint8 ucSid, uint16 ushDidRid){
  uint8 i;
  uint8 j;
  boolean ucRetVal = FALSE;
  for(i=0; i<NO_OF_SID; i++){
   if(ucSid == aushAuthList[i][0]){
      for(j=0; j<NO_OF_DID_RID; j++){
        if(ushDidRid == aushAuthList[i][j]){
          ucRetVal = TRUE;
        }
      }
   }
  }
  return ucRetVal;
}

static boolean DcmKeyExist(uint8* aucKey, uint8 lu8Length){
  uint8 i;
  boolean ucRetVal = FALSE;
  for(i=0; i<lu8Length; i++){
   if(aucKey[i] != 0xff){
      ucRetVal = TRUE;
   }
  }
  return ucRetVal;
}

