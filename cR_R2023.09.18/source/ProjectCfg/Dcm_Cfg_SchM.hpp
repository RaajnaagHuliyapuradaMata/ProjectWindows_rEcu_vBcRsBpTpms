
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#ifndef DCM_CFG_SCHM_H
#define DCM_CFG_SCHM_H

LOCAL_INLINE FUNC(void,DCM_CODE) SchM_Enter_Dcm_Global_NoNest(void){
    __DI(); //RST Rivian OIL#144

    //__EI();
}

LOCAL_INLINE FUNC(void,DCM_CODE) SchM_Exit_Dcm_Global_NoNest(void){
     __EI();

    //__DI();
}

LOCAL_INLINE FUNC(void,DCM_CODE) SchM_Enter_Dcm_DsldTimer_NoNest(void){
     __DI();

   //__EI();
}

LOCAL_INLINE FUNC(void,DCM_CODE) SchM_Exit_Dcm_DsldTimer_NoNest(void){
     __EI();

    //__DI();
}

#endif
