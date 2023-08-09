

#include "Det.h"
#include "Rte_Det.h"
#include "Det_Cfg_SchM.h"
#include "Det_Prv.h"

#if (DET_CFG_FORWARDTODLT_SUPPORTED)
#include "Dlt_Det.h"
#endif

#define DET_START_SEC_RAM_CLEARED
#include "Det_MemMap.h"

boolean Det_Initialized_b;

#if (DET_CFG_ERRORBUFFER_ENABLED)
static uint16 Det_BufferIndex_u16;
Det_ErrorEntryBufferType Det_ErrorEntryBuffer[DET_CFG_ERRORBUFFERSIZE];
#endif

#define DET_STOP_SEC_RAM_CLEARED
#include "Det_MemMap.h"

#define DET_START_SEC_ROM_CODE
#include "Det_MemMap.h"

#if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED)
Std_ReturnType Det_GetLastBufferIndex(Det_BufferIndexType* buffIdx)
{
    Std_ReturnType retval = E_NOT_OK;

    if (buffIdx == NULL_PTR)
    {

        retval = DET_E_PARAM_POINTER;
    }
    else if (!(Det_Initialized_b))
    {

        retval = DET_E_UNAVAILABLE;
    }
    else if (Det_BufferIndex_u16 == 0)
    {

        retval = E_NOT_OK;
    }
    else
    {

        *buffIdx = Det_BufferIndex_u16 - 1;
        retval = E_OK;
    }
    return retval;
}
#endif

#if (DET_CFG_ERRORBUFFER_ENABLED)
static void Det_StoreErrorEntryInBuffer(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{

    SchM_Enter_Det_Monitoring();

    if(Det_BufferIndex_u16 < (DET_CFG_ERRORBUFFERSIZE))
    {
        Det_ErrorEntryBuffer[Det_BufferIndex_u16].ModuleId = ModuleId;
        Det_ErrorEntryBuffer[Det_BufferIndex_u16].InstanceId = InstanceId;
        Det_ErrorEntryBuffer[Det_BufferIndex_u16].ApiId = ApiId;
        Det_ErrorEntryBuffer[Det_BufferIndex_u16].ErrorId = ErrorId;
        Det_BufferIndex_u16++;
    }

    SchM_Exit_Det_Monitoring();
}
#endif

#if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED)
Std_ReturnType Det_GetBufferEntry(Det_BufferIndexType buffIdx, Det_ErrorEntryBufferType* buffEntry)
{
    Std_ReturnType retval = E_NOT_OK;

    if (buffEntry == NULL_PTR)
    {

        retval = DET_E_PARAM_POINTER;
    }
    else if ((!Det_Initialized_b))
    {

        retval = DET_E_UNAVAILABLE;
    }
    else if (Det_BufferIndex_u16 == 0)
    {

        retval = E_NOT_OK;
    }
    else if (buffIdx >= Det_BufferIndex_u16)
    {

        retval = E_NOT_OK;
    }
    else
    {

        *buffEntry = Det_ErrorEntryBuffer[buffIdx];
        retval = E_OK;
    }
    return retval;
}
#endif

void Det_Init(const Det_ConfigType* ConfigPtr)
{
    if (ConfigPtr != NULL_PTR)
    {

        return;
    }

    SchM_Enter_Det_Monitoring()
    ;

#if (DET_CFG_ERRORBUFFER_ENABLED)
    DET_MEMSET(&Det_ErrorEntryBuffer[0], 0x00, sizeof(Det_ErrorEntryBuffer));
    Det_BufferIndex_u16 = 0;
#endif
    Det_Initialized_b = TRUE;

    SchM_Exit_Det_Monitoring()
    ;
}

void Det_Start(void)
{
#if (DET_CFG_ERRORBUFFER_ENABLED)

    SchM_Enter_Det_Monitoring();

    Det_BufferIndex_u16 = 0;

    SchM_Exit_Det_Monitoring();
#endif
}

#if (DET_CFG_VERSIONINFO_SUPPORTED)
void Det_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    if (versioninfo != NULL_PTR)
    {
        versioninfo->vendorID = DET_VENDOR_ID;
        versioninfo->moduleID = DET_MODULE_ID;
        versioninfo->sw_major_version = DET_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = DET_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = DET_SW_PATCH_VERSION;
    }
    else
    {

        (void) Det_ReportError(DET_MODULE_ID, DET_INSTANCE_ID, DET_APIID_GETVERSIONINFO, DET_E_PARAM_POINTER);
    }
}
#endif

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{

    if (!Det_Initialized_b)
    {
        DET_UNUSED_PARAM(ModuleId);
        DET_UNUSED_PARAM(InstanceId);
        DET_UNUSED_PARAM(ApiId);
        DET_UNUSED_PARAM(ErrorId);
    }
    else
    {
#if (DET_CFG_HOOKCOUNT > 0)
        DET_CFG_CALLERRORHOOKS(ModuleId, InstanceId, ApiId, ErrorId);
#endif

#if (DET_CFG_ERRORBUFFER_ENABLED)

        if (Det_BufferIndex_u16 < (DET_CFG_ERRORBUFFERSIZE))
        {

#if (DET_CFG_ERRORBUFFER_FILTER_DUPLICATES)
            boolean isErrorEntryStoreNeeded = TRUE;
            uint16 errorCount;

            for(errorCount= 0; errorCount<Det_BufferIndex_u16; errorCount++)
            {
                if((Det_ErrorEntryBuffer[errorCount].ModuleId == ModuleId) &&
                   (Det_ErrorEntryBuffer[errorCount].InstanceId == InstanceId) &&
                   (Det_ErrorEntryBuffer[errorCount].ApiId == ApiId) &&
                   (Det_ErrorEntryBuffer[errorCount].ErrorId == ErrorId))
                {
                    isErrorEntryStoreNeeded = FALSE;
                    break;
                }
            }
            if(isErrorEntryStoreNeeded)
            {
#endif
            	Det_StoreErrorEntryInBuffer(ModuleId, InstanceId, ApiId, ErrorId);
#if (DET_CFG_ERRORBUFFER_FILTER_DUPLICATES)
            }
#endif
        }
#endif

#if (DET_CFG_FORWARDTODLT_SUPPORTED)
        Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, ErrorId);
#endif
    }
    return E_OK;
}

Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{

    if (!Det_Initialized_b)
    {
        DET_UNUSED_PARAM(ModuleId);
        DET_UNUSED_PARAM(InstanceId);
        DET_UNUSED_PARAM(ApiId);
        DET_UNUSED_PARAM(ErrorId);
    }
    else
    {
#if (DET_CFG_RUNTIMECALLOUT_SUPPORTED)
        DET_CFG_CALLRUNTIMECALLOUT(ModuleId, InstanceId, ApiId, ErrorId);
#endif

#if (DET_CFG_FORWARDTODLT_SUPPORTED)
        Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, ErrorId);
#endif
    }
    return E_OK;
}

Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId)
{
    Std_ReturnType retval = E_OK;

    if (!Det_Initialized_b)
    {
        DET_UNUSED_PARAM(ModuleId);
        DET_UNUSED_PARAM(InstanceId);
        DET_UNUSED_PARAM(ApiId);
        DET_UNUSED_PARAM(FaultId);
    }
    else
    {
#if (DET_CFG_TRANSIENTCALLOUT_SUPPORTED)
        retval = DET_CFG_CALLTRANSIENTCALLOUT(ModuleId, InstanceId, ApiId, FaultId);
#endif

#if (DET_CFG_FORWARDTODLT_SUPPORTED)
        Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, FaultId);
#endif
    }
    return retval;
}

#define DET_STOP_SEC_ROM_CODE
#include "Det_MemMap.h"

