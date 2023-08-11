

#include "DcmManager.h"
#include "EnvManagerX.h"
#include "DcmMemCheckX.h"
#include "iTpms_Interface.h"
#include "DcmAppInterfaceX.h"

#include "Dcm.h"
#include "DcmCore_DslDsd_Prot.h"

static boolean bSendPositiveResponse = FALSE;
static eDiagRoutines ucDiagRoutines = NO_DIAG_ROUTINE;
static boolean bDiagRoutineSelfCheckResult = 0;
static uint64 ullNonceCounter;

void DCMMGR_MainFunction(void)
{

  switch (ucDiagRoutines)
  {
    case DIAG_ROUTINE_SELFCHECK:
      bDiagRoutineSelfCheckResult = DcmVerifyApplicationMemory();

      ucDiagRoutines = NO_DIAG_ROUTINE;
    break;

    case NO_DIAG_ROUTINE:
    default:
    break;
  }
}

void DCMMGR_TriggerDiagRoutineSelfCheck(void)
{
  ucDiagRoutines = DIAG_ROUTINE_SELFCHECK;
  bDiagRoutineSelfCheckResult = FALSE;
}

boolean DCMMGR_GetDiagRoutineSelfCheckResult(void)
{
  return bDiagRoutineSelfCheckResult;
}

void DCMMGR_TriggerPositiveResponse(void)
{
  bSendPositiveResponse = TRUE;
}

boolean DCMMGR_GetPositiveResponseTrigger(void)
{
  return bSendPositiveResponse;
}

void DCMMGR_IncNonceCounter(void)
{
  ullNonceCounter++;
}

uint64 DCMMGR_GetNonceCounter(void)
{
  return ullNonceCounter;
}

void ClientIf_Debug_DiagReqCallback(const enum_TPMSDiagnosticRequest eDiagRequest, tsTPMSDiag_Data *spDiag_Data, uint8 ucReturnVal)
{
}

