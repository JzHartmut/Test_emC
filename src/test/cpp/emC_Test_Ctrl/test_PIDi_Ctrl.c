#include "emC_Test_Ctrl/test_Ctrl_emC.h"
#include <emC/Ctrl/PIDi_Ctrl_emC.h>

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
    step_PIDi_Ctrl_emC(pid, (int)wx, &y);
    float wxPs = pid->wxPs / (float)(1L<<(32 - xBits));
    printf("%d: wx=%3.6f y= %d, yI=%d, dwxP = %d, yD=%d\n", nCt, wxPs, y, pid->qI >>(32 - yBits), pid->dwxPs, pid->yD);
  
  }

  printf("ok\n");

}



#ifdef TESTmain_PIDi_Ctrl_emC
void main(char** args) {
  test1_PIDi_Ctrl_emC();
}
#endif


