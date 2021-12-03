#include "emC_Test_Ctrl/test_Ctrl_emC.h"
#include <emC/Ctrl/PIDi_Ctrl_emC.h>
#include <emC/Ctrl/PIDf_Ctrl_emC.h>
#include <emC/Base/MemC_emC.h>

#include <stdio.h>


static Par_PIDi_Ctrl_emC_s par_g = {0};

static PIDi_Ctrl_emC_s pid_g = {0};

static int stop(){ return 1; }


void test1_PIDi_Ctrl_emC ( ) {

  PIDi_Ctrl_emC_s* pid = &pid_g;
  Par_PIDi_Ctrl_emC_s* par = &par_g;

  float Tstep = 0.000060f;
  int yLim = 2980;  //The maximal controller output should match to the CPU-specific int data type (application decision)
  float kP = 10.0f;
  float Tn = 0.002f;
  float Td = 0.006f;  //4 * dwx per Sampletime on output
  float Tsd = 0.001f;
  int xBits = 12;
  int yBits = 14;


  ctor_Par_PIDi_Ctrl_emC(&par->base.obj, Tstep, xBits, yBits);
  set_Par_PIDi_Ctrl_emC(par, kP, Tn, Td, Tsd, null);
  ctor_PIDi_Ctrl_emC(&pid->base.obj);
  setParam_PIDi_Ctrl_emC(pid, par);
  setLim_PIDi_Ctrl_emC(pid, yLim);


  int y;

  float wx = 100;

  int nCtStop = 130;

  for(int nCt = 0; nCt < 320; ++nCt) {
  
    wx -=0.5f;
  
    if(nCt == nCtStop) {
      stop();
    }
    step_PIDi_Ctrl_emC(pid, (int)wx, (int)wx);
    y = pid->y;
    float wxPs = pid->wxPs / (float)(1L<<(32 - xBits));
    printf("%d: wx=%3.6f y= %d, yI=%d, dwxP = %d, yD=%d\n", nCt, wxPs, y, pid->qI >>(32 - yBits), pid->dwxPs, pid->yD);
  
  }

  printf("ok\n");

}



void test1_PIDf_Ctrl_emC ( ) {

  PIDf_Ctrl_emC_s* pid = (PIDf_Ctrl_emC_s*)ALLOC_ObjectJc(sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, 0);
  Par_PIDf_Ctrl_emC_s* par = allocDATA_MemC(Par_PIDf_Ctrl_emC_s);
  CTOR_ObjectJc(&par->base.obj, par, sizeof(Par_PIDf_Ctrl_emC), refl_Par_PIDf_Ctrl_emC, 0);

  float Tstep = 0.000050f;
  float yLim = 2.0f;  //The maximal controller output should match to the CPU-specific int data type (application decision)
  float kP = 2.5f;
  float Tn = 0.002f;
  float Td = 0.0026f;  //4 * dwx per Sampletime on output
  float Tsd = 0.00005f;


  ctor_Par_PIDf_Ctrl_emC(&par->base.obj, Tstep);
  init_Par_PIDf_Ctrl_emC(par, Tstep, yLim, kP, Tn, Td, Tsd, true, false);
  ctor_PIDf_Ctrl_emC(&pid->base.obj, Tstep);
  init_PIDf_Ctrl_emC(pid, par);
  setLim_PIDf_Ctrl_emC(pid, yLim);


  float y;

  float wx = 0;

  int nCtStop = 50;
  float dwx=0;

  for(int step = 0; step < 320; ++step) {
    switch( step ) {
      case 2: set_Par_PIDf_Ctrl_emC(par, kP, Tn, Td, Tsd, false); break; //reset <= 0
      case 3: wx = 0.5; break;
      case 10: dwx = -0.01f; break;
      case 60: dwx = 0;
      case 100: setLim_PIDf_Ctrl_emC(pid, 0.6f);  break;
    } //switch
    wx += dwx;
    if(step == nCtStop) {
      stop();
    }
    step_PIDf_Ctrl_emC(pid, wx, wx);
    y = getY_PIDf_Ctrl_emC(pid);
    printf("%d: wx=%3.6f y= %f, yI=%3.6f, dwxP = %f, yD=%8.8X\n", step, wx, y, pid->yIntg, pid->dxP, 0); //pid->wxPD32);
  
  }

  printf("ok\n");

}



typedef struct Data_T {
  PIDi_Ctrl_emC_s pid;
  Par_PIDi_Ctrl_emC_s parPid;
} Data_s;

#define INIZ_Data(THIZ) { \
  INIZ_PIDi_Ctrl_emC(THIZ.pid, 0) \
, INIZ_Par_PIDi_Ctrl_emC(THIZ.parPid, 0) \
}

static Data_s* ctor_Data(void* ram, int size) {
  ASSERT_emC(size >= sizeof(Data_s), "size faulty", size, sizeof(Data_s));
  Data_s* thiz = C_CAST(Data_s* ,ram);          //== Initialize the members:
  CTOR_ObjectJc( &thiz->parPid.base.obj, &thiz->parPid, sizeof(thiz->parPid), refl_Par_PIDi_Ctrl_emC, 0);
  CTOR_ObjectJc( &thiz->pid.base.obj, &thiz->pid, sizeof(thiz->pid), refl_PIDi_Ctrl_emC, 0);
  return thiz;
}



extern_C void testLim_PIDi ( );

void testLim_PIDi ( ) {

  FILE* fval = fopen("d:\\vishia\\Java\\cmpnJava_vishiaGui\\src\\appl\\CurveView\\datai.csv", "wb");
  fprintf(fval, "timesh; time_ms; x; y; yp; yi; yd;\n");
  //Data_s datalocal = INIZ_Data(datalocal);
  //Data_s* thiz = &datalocal;
  int sizeData = sizeof(Data_s);
  Data_s* thiz = ctor_Data(alloc_MemC(sizeData), sizeData);
  ASSERTs_emC(sizeof(thiz->pid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
  ASSERTs_emC(sizeof(thiz->parPid) % sizeof(int64)==0, "size should be modulo long size for 8-byte-boundary", 0, 0); 
  ctor_Par_PIDi_Ctrl_emC(&thiz->parPid.base.obj, 0.002f, 11, 12);
  ctor_PIDi_Ctrl_emC(&thiz->pid.base.obj);
  float Tctrl = 0.000050f;
  //float kP = 8.0f, Tn = 0.003f, Tsd = 0.0005f, Td = 0.0015f;
  float kP = 4.0f, Tn = 0.004f, Tsd = 0.0005f, Td = 0;
  float fT1 = 0.01f, fT2 = 0.05f, fT3 = 0.1f;  
  init_Par_PIDi_Ctrl_emC(&thiz->parPid, Tctrl, kP, Tn, Td, Tsd, false, false);
  init_PIDi_Ctrl_emC(&thiz->pid, &thiz->parPid);

  ParFactors_PIDi_Ctrl_emC_s* parf = thiz->parPid.f;
  parf->nSh32y = 4;
  parf->kPi = (int)(4.0f * (1 <<parf->nSh32y)); // 70;  // with 6 bits after dot, ~ 3.9
  parf->wxlim = 30000 / parf->kPi; // 100;
  parf->fI = 0x0000300;
  parf->fI = (int32)(Tctrl/Tn * 0x10000LL);

  setLim_PIDi_Ctrl_emC(&thiz->pid, 1000);
  thiz->pid.yLim = 1000 <<parf->nSh32y;
  int nStep = 0;
  float xEnv1=0, xEnv2=0, xEnv = 0;
  int ypid;
  int wCtrl = 0; 
  while(++nStep <800) {
    //float wx = 0.1f; 
    if(nStep == 50) { 
      wCtrl = 500; 
    }
    else if(nStep == 999400) { 
      wCtrl = 400; 
    }
    int wx = wCtrl - (int)(xEnv);
    step_PIDi_Ctrl_emC(&thiz->pid, wx, (int)(-xEnv));
    ypid = getY_PIDi_Ctrl_emC(&thiz->pid);
    //step_PIDf_Ctrl_emC(&thiz->pid, wx, wx, &ypid);
    xEnv1 += fT1 * (ypid - xEnv1);
    xEnv2 += fT2 * (xEnv1 - xEnv2);
    xEnv += fT3 * (xEnv2 - xEnv);
    printf("%d wx=%d, y=%5d yp=%5d yi=%8.8x yd=%df\n"
    , nStep
    , wx
    , ypid
    , thiz->pid.wxP
    , thiz->pid.qI
    , thiz->pid.dwxPs);  
    fprintf(fval, "%5d; %2.3f; %4.1f; %5d; %5d; %5d; %5d; \n"
    , nStep, nStep*0.05f
    , xEnv
    , ypid
    , thiz->pid.wxP >> parf->nSh32y
    , thiz->pid.qI >> (parf->nSh32y +16)
    , thiz->pid.dwxPs);
  }
  fclose(fval);
  free_MemC(thiz);
}




void test_PIDi_Ctrl_emC ( ) {
  testLim_PIDi();

}



#ifdef TESTmain_PIDi_Ctrl_emC
void main(char** args) {
  test1_PIDi_Ctrl_emC();
}
#endif


