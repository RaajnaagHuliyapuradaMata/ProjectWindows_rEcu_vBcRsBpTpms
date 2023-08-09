

#ifndef DEM_CFG_NODES_H
#define DEM_CFG_NODES_H

#define DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE_OFF  STD_OFF
#define DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE_ON   STD_ON
#define DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE  DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE_OFF

#define DEM_CFG_DEPRECOVERYLIMIT_OFF  STD_OFF
#define DEM_CFG_DEPRECOVERYLIMIT_ON   STD_ON
#define DEM_CFG_DEPRECOVERYLIMIT  DEM_CFG_DEPRECOVERYLIMIT_OFF

#define DEM_CFG_DEPENDENCY_PENDING_ON             FALSE

#define DEM_CFG_FAILUREDEPENDENCY_RECHECK_LIMIT  80u

#define DEM_CFG_NODEPARAMS \
{ \
    DEM_NODES_INIT (DEM_NODE_INFINITE_RECOVERIES, 0,             0                                       ) \
   ,DEM_NODES_INIT (5,                            1,             DEM_CFG_DemCallback_CanBusFailure_IDX   ) \
   ,DEM_NODES_INIT (5,                            1,             DEM_CFG_DemCallback_PowerSystemFailure_IDX) \
   ,DEM_NODES_INIT (5,                            1,             DEM_CFG_DemCallback_TpmsConfigurationFailure_IDX) \
   ,DEM_NODES_INIT (5,                            1,             DEM_CFG_DemCallback_TpmsEcuFailure_IDX  ) \
   ,DEM_NODES_INIT (5,                            1,             DEM_CFG_DemCallback_TpmsSensorsFailure_IDX) \
   ,DEM_NODES_INIT (5,                            1,             DEM_CFG_DemCallback_TpmsStatusFailure_IDX) \
}

#define  DEM_CFG_DemCallback_CanBusFailure_IDX  1
#define  DEM_CFG_DemCallback_PowerSystemFailure_IDX  2
#define  DEM_CFG_DemCallback_TpmsConfigurationFailure_IDX  3
#define  DEM_CFG_DemCallback_TpmsEcuFailure_IDX  4
#define  DEM_CFG_DemCallback_TpmsSensorsFailure_IDX  5
#define  DEM_CFG_DemCallback_TpmsStatusFailure_IDX  6

#define  DEM_CFG_NODEFAILEDCALLBACK_COUNT  6
#define  DEM_CFG_NODEFAILEDCALLBACK_ARRAYLENGTH  (DEM_CFG_NODEFAILEDCALLBACK_COUNT+1)

#define DEM_CFG_NODEFAILEDCALLBACKS \
{ \
	NULL_PTR \
	,&DemCallback_CanBusFailure \
	,&DemCallback_PowerSystemFailure \
	,&DemCallback_TpmsConfigurationFailure \
	,&DemCallback_TpmsEcuFailure \
	,&DemCallback_TpmsSensorsFailure \
	,&DemCallback_TpmsStatusFailure \
}

#endif

