#include "test_Ctrl_emC.h"
#include <emC/Ctrl/PIDf_Ctrl_emC.h>
#include <stdio.h>


template<class PIDxCtrl> class Test_PIDxCtrl {

  PIDxCtrl pid = 0;
};


#define INIZ_DEFemC(NAME) INIZ_##NAME

#define PIDx_Ctrl_emC PIDf_Ctrl_emC
#define PIDx_Ctrl_emC_s PIDf_Ctrl_emC_s 
#define INIZ_PIDx_Ctrl_emC INIZ_DEFemC(PIDf_Ctrl_emC)


typedef struct Data_T {
  PIDf_Ctrl_emC_s pid;
  Par_PIDf_Ctrl_emC_s parPid;

  /**A delay FBlock. Note: The float array should follow immediately. See ctor_Delayf_Ctrl_emC. */
  Delayf_Ctrl_emC_s delayx; float _delayxValues[18];

} Data_s;

#define INIZ_Data(THIZ) { \
  INIZ_PIDf_Ctrl_emC(THIZ.pid, 0) \
, INIZ_Par_PIDf_Ctrl_emC(THIZ.parPid, 0) \
}

static Data_s* ctor_Data(void* ram, int size) {
  ASSERT_emC(size >= sizeof(Data_s), "size faulty", size, sizeof(Data_s));
  Data_s* thiz = C_CAST(Data_s* ,ram);          //== Initialize the members:
  CTOR_ObjectJc( &thiz->parPid.base.obj, &thiz->parPid, sizeof(thiz->parPid), refl_Par_PIDf_Ctrl_emC, 0);
  CTOR_ObjectJc( &thiz->pid.base.obj, &thiz->pid, sizeof(thiz->pid), refl_PIDf_Ctrl_emC, 0);
  return thiz;
}


static void testLim_PIDf ( ) {

  FILE* fval = fopen("d:\\vishia\\Java\\cmpnJava_vishiaGui\\src\\appl\\CurveView\\data2.csv", "wb");
  fprintf(fval, "timesh; time_ms; x; y; yp; yi; yd;\n");
  //Data_s datalocal = INIZ_Data(datalocal);
  //Data_s* thiz = &datalocal;
  int sizeData = sizeof(Data_s);
  Data_s* thiz = ctor_Data(alloc_MemC(sizeData), sizeData);
  ASSERTs_emC(sizeof(thiz->pid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
  ASSERTs_emC(sizeof(thiz->parPid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
  ctor_Par_PIDf_Ctrl_emC(&thiz->parPid.base.obj, 0.002f);
  ctor_PIDf_Ctrl_emC(&thiz->pid.base.obj, 0.000050f);
  ctor_Delayf_Ctrl_emC(&thiz->delayx, 20, sizeof(thiz->delayx) + sizeof(thiz->_delayxValues));
  float valrange = 1000.0f;
  float kP = 8.0f, Tn = 0.008f, Tsd1 = 0.000200f, Tsd2 = 0.000200f, Td = 0.001500f;
  //float kP = 4.0f, Tn = 0.004f, Tsd1 = 0, Tsd2 = 0, Td = 0;
  float fT1 = 0.01f, fT2 = 0.05f, fT3 = 0.1f;  
  Td /=12;
  init_Par_PIDf_Ctrl_emC(&thiz->parPid, 0.000050f, valrange, kP, Tn, Td, Tsd1, Tsd2, false, false);
  init_PIDf_Ctrl_emC(&thiz->pid, &thiz->parPid);
  thiz->parPid.f->setD0onPlimit = 0;
  setLim_PIDf_Ctrl_emC(&thiz->pid, valrange);
  int nStep = 0;
  float xEnv1=0, xEnv2=0, xEnv = 0;
  float ypid;
  float wCtrl = 0; 
  while(++nStep <800) {
    //float wx = 0.1f; 
    if(nStep == 50) { 
      wCtrl = 500; 
    }
    else if(nStep == 400) { 
      wCtrl = 400; 
    }
    float xquant = 2000.0f;                   // build input signal with ADC resolution (quantization)
    float xEnvADC = ((int)(xquant*(xEnv)/valrange + 0.5f ) / xquant ) * valrange;
    float wx = wCtrl - xEnvADC;
    float wxz = delay_Ctrl_emC(&thiz->delayx, 12, wx);
    ypid = step_dxavg_PIDf_Ctrl_emC(&thiz->pid, wx, wx, wxz);
    //ypid = step_dxs_PIDf_Ctrl_emC(&thiz->pid, wx, wx);
    //ypid = step_PIDf_Ctrl_emC(&thiz->pid, wx, -xEnvADC);
    xEnv1 += fT1 * (ypid - xEnv1);
    xEnv2 += fT2 * (xEnv1 - xEnv2);
    xEnv += fT3 * (xEnv2 - xEnv);
    printf("%d y=%1.5f yp=%1.5f yi=%1.5f yd=%1.5f\n"
    , nStep, ypid
    , thiz->pid.wxP
    , thiz->pid.yIntg
    , thiz->pid.dxP);  
    fprintf(fval, "%5d; %2.3f; %1.5f; %1.5f; %1.5f; %1.5f; %1.5f; \n"
    , nStep, nStep*0.05f, xEnv, ypid
    , thiz->pid.wxP
    , thiz->pid.yIntg
    , thiz->pid.dxP);
  }
  fclose(fval);
  free_MemC(thiz);
}

PIDf_Ctrl_emC pid(0, 0.000050f);


class DataCpp {
  PIDf_Ctrl_emC pid;
  Par_PIDf_Ctrl_emC parPid;

  public: DataCpp(); 
};


DataCpp::DataCpp() 
: pid(123, 0.000050f)
, parPid(122, 0.001f, 12.0f)
{
}

DataCpp myDataCpp();

DataCpp* myDataRef;




void testCpp ( ) {

  myDataRef = new DataCpp();
}




void test_PIDf_Ctrl_emC ( ) {
  testLim_PIDf();

}
