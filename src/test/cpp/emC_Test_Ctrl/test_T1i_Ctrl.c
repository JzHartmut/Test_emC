#include "test_Ctrl_emC.h"
#include <emC/Ctrl/T1_Ctrl_emC.h>
#include <math.h>
#include <emC/Test/testAssert.h>

#include <stdio.h>

typedef struct TestData_T {
  
  T1ish_Ctrl_emC_s t1ish;

  T1ish_Ctrl_emC_s t2ish;

  T1i_Ctrl_emC_s t1i;

  T1f_Ctrl_emC_s t1f;

  float x;

  float Tstep;
  float Ts;
  int xBits;
  int yBits;
  int fsBits;


  /**Check values for max. abbreviation*/
  float abbrTsh1, abbrTsh2, abbrTi, abbrTf;

  /**Check values for reached end value*/
  float endTsh1, endTsh2, endTi, endTf;

  int bPrint;

} TestData;



static int stop(){ return 1; }




void test1_T1_Ctrl_emC (TestData* thiz ) {
  char title[200];
  snprintf(title, sizeof(title), "test1_T1_Ctrl_emC x=%4.1f, Ts=%1.4f", thiz->x, thiz->Ts);

  TEST_START(title);


  ctor_T1i_Ctrl_emC(&thiz->t1i);
  ctor_T1ish_Ctrl_emC(&thiz->t1ish);
  ctor_T1ish_Ctrl_emC(&thiz->t2ish);
  ctor_T1f_Ctrl_emC(&thiz->t1f);
  param_T1i_Ctrl_emC(&thiz->t1i, thiz->Ts, thiz->Tstep);
  param_T1ish_Ctrl_emC(&thiz->t1ish, thiz->Ts, thiz->Tstep, 4, thiz->xBits, thiz->yBits);
  param_T1ish_Ctrl_emC(&thiz->t2ish, thiz->Ts, thiz->Tstep, 8, thiz->xBits, thiz->yBits);
  param_T1f_Ctrl_emC(&thiz->t1f, thiz->Ts, thiz->Tstep);


  int ysh1, ysh2;
  int16 y;
  float yf;

  int nCtStop = 130;

  float limCmp = thiz->x * 0.05f;  //possible abbreviation inside. 
  float limfCmp = thiz->x * 0.01f;  //float is more accurate inside. possible abbreviation inside. 
  float qsh1, qsh2, qi; //internal y-value of T1i

  float dysh1_eMax = 0;  //error respecitvely end value
  float dysh2_eMax = 0;  //error respecitvely end value
  //float dysh_Max = 0;   //error respectively curr value.
  float dyi_eMax = 0;  //error respecitvely end value
  //float dyi_Max = 0;   //error respectively curr value.
  float dyf_eMax = 0;  //error respecitvely end value
  float dyf_Max = 0;   //error respectively curr value.

  int nCt = 0; 
  int qshlast, qlast;
  do {
    qlast = thiz->t1i.q.q32;
    qshlast = thiz->t1ish.q;
    //x -=0.5f;

    float yCmp = thiz->x - thiz->x / expf((nCt+1) / (thiz->Ts / thiz->Tstep));

    if(nCt == nCtStop) {
      stop();
    }
    y= step_T1i_Ctrl_emC(&thiz->t1i, (int16)(thiz->x * 16.0f));  //has 16 instead 12 x-Bits
    ysh1= step_T1ish_Ctrl_emC(&thiz->t1ish, (int)thiz->x);
    ysh2= step_T1ish_Ctrl_emC(&thiz->t2ish, (int)thiz->x);
    yf= step_T1f_Ctrl_emC(&thiz->t1f, thiz->x);
    
    qsh1 = thiz->t1ish.q / (float)(1L<<(32 - thiz->yBits));
    float dysh1Cmp = fabsf(qsh1 - yCmp);
    float dyesh1Rel = dysh1Cmp / fabsf(thiz->x);
    if(dyesh1Rel > dysh1_eMax) { dysh1_eMax = dyesh1Rel; }

    qsh2 = thiz->t2ish.q / (float)(1L<<(32 - thiz->yBits));
    float dysh2Cmp = fabsf(qsh2 - yCmp);
    float dyesh2Rel = dysh2Cmp / fabsf(thiz->x);
    if(dyesh2Rel > dysh2_eMax) { dysh2_eMax = dyesh2Rel; }

    qi = thiz->t1i.q.q32 / 65536.0f;  //It is y as float value, y is anytime the 16 hi bits.
    float dyiCmp = fabsf(qi - 16*yCmp);  //get 16 times more input, uses 16 bit width instead 12 bit
    float dyeiRel = dyiCmp / fabsf(thiz->x);  //relative to end value, it is the input x
    if(dyeiRel > dyi_eMax) { dyi_eMax = dyeiRel; }

    float dyfCmp = yf - yCmp;
    float dyf_eRel = fabsf(dyfCmp) / fabsf(thiz->x);
    if(dyf_eRel > dyf_eMax) { dyf_eMax = dyf_eRel; }
    //printf("%d: dx=%3.6f y= %d = %3.3f, dy=%f ; %f\n", nCt, dx, y, q, dyCmp, dyfCmp);
    nCt +=1;
  } while(nCt < 1000000 && qlast != thiz->t1i.q.q32 && qshlast != thiz->t1ish.q);  //end value reached

  { float dyiEndRel = (qi - 16.0f*thiz->x) / (16.0f * thiz->x);
    float dysh1EndRel = (qsh1 - thiz->x) / thiz->x;
    float dysh2EndRel = (qsh2 - thiz->x) / thiz->x;
    float dyfEndRel = (yf - thiz->x) / thiz->x;
    if(thiz->bPrint) {
      printf("  Ti    abbr=%1.6f, endVal=%1.6f  ...after %d steps\n", dyi_eMax, dyiEndRel, nCt);
      printf("  Tsh1  abbr=%1.6f, endVal=%1.6f (4 bit fTs)\n", dysh1_eMax, dysh1EndRel);
      printf("  Tish2 abbr=%1.6f, endVal=%1.6f (8 bit fTs)\n", dysh2_eMax, dysh2EndRel);
      printf("  Tf    abbr=%1.6f, endVal=%1.6f\n", dyf_eMax, dyfEndRel);
    }
    char checktext[8][100];
    snprintf(checktext[0], 100, "%1.3f < abbreviation of Tsh1 4 Bit fTs", thiz->abbrTsh1);
    snprintf(checktext[1], 100, "%1.3f < abbreviation of Tsh2 8 Bit fTs", thiz->abbrTsh2);
    snprintf(checktext[2], 100, "%1.3f < abbreviation of Ti", thiz->abbrTi);
    snprintf(checktext[3], 100, "%1.3f < abbreviation of Tf", thiz->abbrTf);
    snprintf(checktext[4], 100, "%1.3f < end value of Tsh1 4 Bit fTs", thiz->endTsh1);
    snprintf(checktext[5], 100, "%1.3f < end value of Tsh2 8 Bit fTs", thiz->endTsh2);
    snprintf(checktext[6], 100, "%1.3f < end value of Ti", thiz->endTi);
    snprintf(checktext[7], 100, "%1.3f < end value of Tf", thiz->endTf);

    CHECK_TRUE(dysh1_eMax < thiz->abbrTsh1, checktext[0]); 
    CHECK_TRUE(dysh2_eMax < thiz->abbrTsh2, checktext[1]); 
    CHECK_TRUE(dyi_eMax < thiz->abbrTi, checktext[2]); 
    CHECK_TRUE(dyf_eMax < thiz->abbrTf, checktext[3]); 
    CHECK_TRUE(fabsf(dysh1EndRel) < thiz->endTsh1, checktext[4]); 
    CHECK_TRUE(fabsf(dysh2EndRel) < thiz->endTsh2, checktext[5]); 
    CHECK_TRUE(fabsf(dyiEndRel) < thiz->endTi, checktext[6]); 
    CHECK_TRUE(fabsf(dyfEndRel) < thiz->endTf, checktext[7]); 
  }
  TEST_END;

}


void test_T1_Ctrl_emC(void) {

  TestData data = {0};  //Hint: only for PC, stack local!

  data.Tstep = 0.000050f;
  data.xBits = 12;
  data.yBits = 12;
  data.abbrTf = 0.001f;
  data.abbrTi = 0.01f;
  data.abbrTsh1 = 0.05f;
  data.abbrTsh2 = 0.05f;
  data.endTf = 0.001f;
  data.endTi = 0.001f;
  data.endTsh1 = 0.001f;
  data.endTsh2 = 0.001f;
  data.bPrint = 0;          //<<< activate for debug
  //
  data.Ts = 0.001f;         //50 * Tstep, fT1~= 0.02
  data.x = -2048.0f;        //the maximal admissible value, exterma test
  test1_T1_Ctrl_emC(&data);
  data.x = 100.0f;          //a less value, precision test
  test1_T1_Ctrl_emC(&data);
  //
  data.Ts = 0.01f;          //500 * Tstep, fT1~= 0.002
  data.x = -2048.0f;        //the maximal admissible value, exterma test
  test1_T1_Ctrl_emC(&data);
  data.x = 100.0f;          //a less value, precision test
  test1_T1_Ctrl_emC(&data);
  //
  data.Ts = 0.050f;         //2500 * Tstep
  data.abbrTi = 0.060f;     //more abbreviation, but it should be seen else as accurate enough
  data.x = -2048.0f;        //the maximal admissible value, exterma test
  test1_T1_Ctrl_emC(&data);
  data.x = 100.0f;          //a less value, precision test
  test1_T1_Ctrl_emC(&data);
  //
  data.Ts = 65536 * data.Tstep;          //0x10000*Tstep is accurate for Ti      
  data.abbrTi = 0.006f;    //it is accurate for the long time, but only with dedicated time
  data.abbrTf = 0.002f;    //accurate
  data.abbrTsh1 = 0.01f;
  data.abbrTsh2 = 2.0f;    //does not work
  data.endTsh2 = 2.0f;
  data.endTi = 0.006f;     //for less input
  data.endTf = 0.006f;
  data.x = -2048.0f;        //the maximal admissible value, exterma test
  test1_T1_Ctrl_emC(&data);
  data.x = 100.0f;          //a less value, precision test
  test1_T1_Ctrl_emC(&data);
  //


  //printf("ok\n");

}



#ifdef XXTEST_Special_emC
void main(char** args){
}
#endif
