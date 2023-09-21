#ifndef DCMDSPUDS_RDBI_PROT_H
#define DCMDSPUDS_RDBI_PROT_H

#define DCM_RDBI_SIZE_DID            (0x02u)

typedef enum{
      DCM_RDBI_IDLE
   ,  DCM_RDBI_NEG_RESP
   ,  DCM_RDBI_PROCESS_NEW_DID
   ,  DCM_RDBI_CHECK_READACCESS
   ,  DCM_RDBI_CHECK_CONDITIONS
   ,  DCM_RDBI_GET_LENGTH
   ,  DCM_RDBI_GET_DATA
}Dcm_StRdbi_ten;

typedef enum{
      DCM_LENCALC_RETVAL_OK
   ,  DCM_LENCALC_RETVAL_ERROR
   ,  DCM_LENCALC_RETVAL_PENDING
}Dcm_LenCalcRet_ten;

typedef enum{
      DCM_LENCALC_STATUS_INIT
   ,  DCM_LENCALC_STATUS_GETINDEX
   ,  DCM_LENCALC_STATUS_GETLENGTH
   ,  DCM_LENCALC_STATUS_GETSUPPORT
}Dcm_LenCalc_ten;

typedef enum{
      DCM_GETDATA_RETVAL_OK
   ,  DCM_GETDATA_RETVAL_INTERNALERROR
   ,  DCM_GETDATA_RETVAL_PENDING
   ,  DCM_GETDATA_RETVAL_INVALIDCONDITIONS
}Dcm_GetDataRet_ten;

typedef enum{
      DCM_GETDATA_STATUS_INIT
   ,  DCM_GETDATA_STATUS_GETLENGTH
   ,  DCM_GETDATA_STATUS_GETDATA
}Dcm_GetData_ten;

extern   VAR(uint16,           DCM_VAR                 ) Dcm_RdbiReqDidNb_u16;
extern   VAR(uint16,           DCM_VAR                 ) Dcm_NumOfIndices_u16;
extern   VAR(Dcm_StRdbi_ten,   DCM_VAR                 ) Dcm_stRdbi_en;
extern   VAR(uint32,           DCM_VAR                 ) Dcm_TotalLength_u32;
extern   VAR(Dcm_LenCalc_ten,  DCM_VAR                 ) Dcm_StLenCalc_en;
extern P2VAR(uint8,            DCM_VAR, DCM_INTERN_DATA) Dcm_IdxList_pu8;
extern   VAR(uint32,           DCM_VAR                 ) Dcm_NumberOfBytesInResponse_u32;
extern   VAR(uint16,           DCM_VAR                 ) Dcm_NumberOfProcessedDIDs_u16;
extern   VAR(uint16,           DCM_VAR                 ) Dcm_NumberOfAcceptedDIDs_u16;
extern   VAR(Dcm_OpStatusType, DCM_VAR                 ) Dcm_DspReadDidOpStatus_u8;
extern   VAR(Dcm_GetData_ten,  DCM_VAR                 ) Dcm_GetDataState_en;
extern   VAR(uint16,           DCM_VAR                 ) Dcm_GetDataNumOfIndex_u16;
extern   VAR(uint32,           DCM_VAR                 ) Dcm_GetDataTotalLength_u32;

extern FUNC(Dcm_LenCalcRet_ten,DCM_CODE) Dcm_DspGetTotalLengthOfDIDs_en(
      P2VAR(uint8,                        AUTOMATIC, DCM_INTERN_DATA) adrSourceIds_pu8
   ,    VAR(uint16,                       AUTOMATIC                 ) nrDids_u16
   ,  P2VAR(uint16,                       AUTOMATIC, DCM_INTERN_DATA) adrNumOfIndices_pu16
   ,  P2VAR(uint32,                       AUTOMATIC, DCM_INTERN_DATA) adrTotalLength_pu32
   ,  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA) dataNegRespCode_u8
);

extern FUNC(void, DCM_CODE) Dcm_Lok_DspRdbiConfirmation(
      VAR(Dcm_IdContextType,          AUTOMATIC) dataIdContext_u8
   ,  VAR(Type_SwcServiceCom_tIdPdu,  AUTOMATIC) dataRxPduId_u8
   ,  VAR(uint16,                     AUTOMATIC) dataSourceAddress_u16
   ,  VAR(Dcm_ConfirmationStatusType, AUTOMATIC) status_u8
);

extern FUNC(Dcm_GetDataRet_ten,DCM_CODE) Dcm_GetData_en(
     P2CONST(uint8,                        AUTOMATIC, DCM_INTERN_CONST) adrIdBuffer_pcu8
   ,   P2VAR(uint8,                        AUTOMATIC, DCM_INTERN_DATA ) adrTargetBuffer_pu8
   ,     VAR(uint16,                       DCM_INTERN_DATA            ) nrIndex_u16
   ,   P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_INTERN_DATA ) dataNegRespCode_u8
   ,     VAR(uint32,                       DCM_INTERN_DATA            ) adrTotalLength_pu32
);


#endif

