

#include "Std_Types.h"
#include "MemIf.h"

#if ((MEMIF_SW_MAJOR_VERSION != (3U)) \
  || (MEMIF_SW_MINOR_VERSION != (3U)) )
# error "Version numbers of MemIf.c and MemIf.h are inconsistent!"
#endif

#if ((MEMIF_TYPES_SW_MAJOR_VERSION != (3U)) \
  || (MEMIF_TYPES_SW_MINOR_VERSION != (3U)) )
# error "Version numbers of MemIf.c and MemIf_Types.h are inconsistent!"
#endif

#if ((MEMIF_CFG_MAJOR_VERSION != (5U)) \
  || (MEMIF_CFG_MINOR_VERSION != (2U)) )
# error "Version numbers of MemIf.c and MemIf_Cfg.h are inconsistent!"
#endif

#if !defined (MEMIF_LOCAL)
# define MEMIF_LOCAL static
#endif

#if !defined (MEMIF_LOCAL_INLINE)
# define MEMIF_LOCAL_INLINE LOCAL_INLINE
#endif

#define MEMIF_START_SEC_CODE
#include "MemMap.h"

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)

MEMIF_LOCAL_INLINE FUNC(Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_DetChkDeviceIndex(uint8 DeviceIndex);
#endif

MEMIF_LOCAL FUNC(Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_IsBitSet(uint8 Mask, MemIf_StatusType Status);

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)

MEMIF_LOCAL_INLINE FUNC(Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_DetChkDeviceIndex(uint8 DeviceIndex)
{
  return (Std_ReturnType) ((DeviceIndex >= MemIf_NumberOfDevices) ? E_NOT_OK : E_OK);
}
#endif

MEMIF_LOCAL FUNC(Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_IsBitSet(uint8 Mask, MemIf_StatusType Status)
{
  return ((Mask & (1u << (uint8)Status)) > 0) ? E_OK : E_NOT_OK;
}

FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Read(uint8 DeviceIndex, uint16 BlockNumber, uint16 BlockOffset, MemIf_DataPtr_pu8 DataBufferPtr, uint16 Length)
{

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MEMIF_E_NO_ERROR;

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {

    retVal = MemIf_MemHwaApis[DeviceIndex].Read(BlockNumber, BlockOffset, DataBufferPtr, Length);
  }

#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_READ, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
}

FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Write(uint8 DeviceIndex, uint16 BlockNumber, MemIf_DataPtr_pu8 DataBufferPtr)
{

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MEMIF_E_NO_ERROR;

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {

    retVal = MemIf_MemHwaApis[DeviceIndex].Write(BlockNumber, DataBufferPtr);
  }

#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_WRITE, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
}

FUNC(Std_ReturnType, MEMIF_CODE) MemIf_InvalidateBlock(uint8  DeviceIndex, uint16 BlockNumber)
{

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MEMIF_E_NO_ERROR;

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {

    retVal = MemIf_MemHwaApis[DeviceIndex].InvalidateBlock(BlockNumber);
  }

#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_INVALIDATE, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
}

FUNC(Std_ReturnType, MEMIF_CODE) MemIf_EraseImmediateBlock(uint8  DeviceIndex, uint16 BlockNumber)
{

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MEMIF_E_NO_ERROR;

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {

    retVal = MemIf_MemHwaApis[DeviceIndex].EraseImmediateBlock(BlockNumber);
  }

#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_ERASE, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
}

FUNC(void, MEMIF_CODE) MemIf_Cancel(uint8 DeviceIndex)
{

  uint8 errorId = MEMIF_E_NO_ERROR;

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {

    MemIf_MemHwaApis[DeviceIndex].Cancel();
  }

#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_CANCEL, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId);
#endif
}

 FUNC(MemIf_StatusType, MEMIF_CODE) MemIf_GetStatus(uint8 DeviceIndex)
{

  uint8 errorId = MEMIF_E_NO_ERROR;
  MemIf_StatusType retVal = MEMIF_UNINIT;

  uint8 MemIf_LoopCounter;
  uint8 MemIf_StatusMask = 0;

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)

  if ( (DeviceIndex != MEMIF_BROADCAST_ID) && (DeviceIndex >= MemIf_NumberOfDevices) )
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif

  if(MEMIF_BROADCAST_ID == DeviceIndex)
  {

    for (MemIf_LoopCounter = 0; MemIf_LoopCounter < MemIf_NumberOfDevices; MemIf_LoopCounter++)
    {

      MemIf_StatusMask |= (uint8) ((uint8)1u << (uint8) MemIf_MemHwaApis[MemIf_LoopCounter].GetStatus());
    }

    if (MemIf_IsBitSet(MemIf_StatusMask, MEMIF_UNINIT) == E_OK)
    {
      retVal = MEMIF_UNINIT;
    }

    else if (MemIf_IsBitSet(MemIf_StatusMask, MEMIF_BUSY) == E_OK)
    {
      retVal = MEMIF_BUSY;
    }

    else if (MemIf_IsBitSet(MemIf_StatusMask, MEMIF_BUSY_INTERNAL) == E_OK)
    {
      retVal = MEMIF_BUSY_INTERNAL;
    }

    else
    {
      retVal = MEMIF_IDLE;
    }

  }
  else

  {
    retVal = MemIf_MemHwaApis[DeviceIndex].GetStatus();
  }

#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_GET_STATUS, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
}

FUNC(MemIf_JobResultType, MEMIF_CODE) MemIf_GetJobResult(uint8 DeviceIndex)
{

  uint8 errorId = MEMIF_E_NO_ERROR;
  MemIf_JobResultType retVal = MEMIF_JOB_FAILED;

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {

    retVal = MemIf_MemHwaApis[DeviceIndex].GetJobResult();
  }

#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_GET_JOB_RESULT, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
}

#if (MEMIF_VERSION_INFO_API == STD_ON)

void MemIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA) VersionInfoPtr)
{

  uint8 errorId = MEMIF_E_NO_ERROR;

# if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfoPtr == NULL_PTR)
  {
    errorId = MEMIF_E_PARAM_POINTER;
  }
  else
# endif
  {

    VersionInfoPtr->vendorID         = MEMIF_VENDOR_ID;
    VersionInfoPtr->moduleID         = MEMIF_MODULE_ID;
    VersionInfoPtr->sw_major_version = MEMIF_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = MEMIF_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = MEMIF_SW_PATCH_VERSION;
  }

# if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_VERSION_INFO, errorId);
  }
# else
  MEMIF_DUMMY_STATEMENT(errorId);
# endif
}
#endif

FUNC(void, MEMIF_CODE) MemIf_SetMode(MemIf_ModeType Mode)
{
  uint8 MemIf_LoopCounter;

  for(MemIf_LoopCounter = 0; MemIf_LoopCounter < MemIf_NumberOfDevices; MemIf_LoopCounter++)
  {
    MemIf_MemHwaApis[MemIf_LoopCounter].SetMode(Mode);
  }
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

