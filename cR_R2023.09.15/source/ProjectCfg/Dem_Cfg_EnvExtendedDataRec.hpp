

#ifndef DEM_CFG_ENVEXTENDEDDATAREC_H
#define DEM_CFG_ENVEXTENDEDDATAREC_H

#define DEM_CFG_ENVEXTDATA2DATAELEMENT \
{ \
   DEM_DATAELEM_DEMDATAELEMENTCLASS_AGING_COUNTER,     \
   0 \
}

#define DEM_EXTDATAREC_EXT_AGINGCOUNTER               1

#define DEM_CFG_ENVEXTDATAREC \
{ \
 \
    { 0,     DEM_TRIGGER_NONE,     FALSE,0    }\
   ,{ 1,     DEM_TRIGGER_ON_TEST_FAILED,   FALSE,1    }\
}

#define DEM_CFG_ENVEXTDATAREC_ARRAYLENGTH  (1+1)

#endif
