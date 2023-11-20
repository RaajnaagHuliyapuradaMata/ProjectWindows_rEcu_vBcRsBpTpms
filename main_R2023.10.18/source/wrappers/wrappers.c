#include "Std_Types.hpp"

#include "infMcalMcuSwcApplEcuM.hpp"
#include "infMcalWdgSwcApplEcuM.hpp"
#include "infSwcServiceNvMSwcApplEcuM.hpp"
#include "infSwcServiceOsSwcApplEcuM.hpp"

void ApplMcu_vReleaseIoBuffers (void){}
void Wdt_InitWD0          (void){}
void Wdt_TriggerWD0       (void){}

     void                      infMcalDioSwcApplEcuM_vInitFunction(void){}
     void                      infMcalAdcSwcApplEcuM_vInitFunction(void){}
     void                      infMcalMcuSwcApplEcuM_InitFunction(void){}
     void                      infMcalWdgSwcApplEcuM_InitFunction(void){}
FUNC(void, SWCSERVICENVM_CODE) infSwcServiceNvMSwcApplEcuM_InitFunction(void){}
     void                      infSwcServiceEcuMSwcServiceStartUp_InitFunction(void){}
