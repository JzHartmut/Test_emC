#include "test_PIDi_Ctrl.h"
#include <emC/Ctrl/PIDi_Ctrl_emC.h>

#include <stdio.h>


Par_PIDi_Ctrl_emC_s par = {0};

PIDi_Ctrl_emC_s pid = {0};

int stop(){ return 1; }


void test1_PIDi_Ctrl_emC ( ) {

  PIDi_Ctrl_emC_s* pid1 = &pid;

  int yLim = 5000;  //The maximal controller output should match to the CPU-specific int data type (application decision)
  float Tstep = 0.000060f;
  float kP = 1.2f;
  float Tn = 0.01f;
  float Td = 0.000240f;  //4 * dwx per Sampletime on output
  float Tsd = 0.001f;

  ctor_Par_PIDi_Ctrl_emC(&par.base.obj, Tstep, 12,16);
  set_Par_PIDi_Ctrl_emC(&par, kP, Tn, Td, Tsd, null);
  ctor_PIDi_Ctrl_emC(&pid.base.obj);
  setParam_PIDi_Ctrl_emC(&pid, &par);
  setLim_PIDi_Ctrl_emC(&pid, 5000);


  int y;

  float wx = 100;

  int nCtStop = 30;

  for(int nCt = 0; nCt < 600; ++nCt) {
  
    wx -=0.5f;
    step_PIDi_Ctrl_emC(&pid, (int)wx, &y);
  
    if(nCt == nCtStop) {
      stop();
    }

    printf("%d: wx=%d y= %d, yI=%d yD=%d\n", nCt, pid.wxPs >> 16, y, pid.qI, pid.yD >> 16);
  
  }

  printf("ok\n");

}



#ifdef TESTmain_PIDi_Ctrl_emC
void main(char** args) {
  test1_PIDi_Ctrl_emC();
}
#endif


