#include <emC_Test_Math/Test_Math_emC.h>
#include <emC/Base/Math_emC.h>
#include <applstdef_emC.h>
#include <math.h>
#include <stdio.h>

void test_Q_rsqrt ( ) {

  float x[] = { 0.1f, 0.2f, 1.0f, 2.0f, 4.0f, 9.0f }; 
  float y[ARRAYLEN_emC(x)] = {0};
  float error = 0;
  for(int ix = 0; ix < ARRAYLEN_emC(x); ++ix) {
    float x1 = x[ix];
    float yq = 0; //Q_rsqrt(x1);
    float ye = 1.0f / sqrtf(x1);
    y[ix] = yq;
    float error1 = fabsf(ye - yq) / ye;
    if(error1 > error) {
      error = error1; 
    } 
  }


}





int testMult16_Math_emC ( Test_Mult16_Math_emC_s*  values, int zValues) {
  int err1 = 0, err2=0;
  for(int ix=0; ix < zValues; ++ix) {
    int16 as = (int16)values[ix].a;
    int16 bs = (int16)values[ix].b;
    int32 rs; 
    muls16_emC(rs, as, bs);
    uint16 bu = (uint16)values[ix].b;
    uint16 au = (uint16)as;
    uint32 ru; 
    mulu16_emC(ru, au, bu);
    if(rs != (int32)values[ix].rs) {
      err1 +=1;
    }
    if(ru != values[ix].ru) {
      err2 +=1;
    }
  }    
  int ret = err1 + err2;
  return ret;
}







int test_FixpointMult ( ) {

  
  uint16 f1 = 0xffff; //27648;
  int16 f2 = 0x4000; //(uint16)(0x8000 * 1.05f);
  int32 prod4000 = f1 * f2;

  int32 prob4000 = (int32)f1 * f2;

  uint16 f3 = 0xffff; 
  uint16 f4 = 0x4000;
  int32 prod_c000 = f3 * f4;
  int32 prob_c000 = (int32)f3 * f4;
  int32 pron_c000 = (int32)f3 * (int32)f4;

  uint32 f32a = 0xFFFFffff;
  uint32 f32b = 0xffffffff;
  uint32 pro32d_c000 = f32a * f32b;

  return 0;
}





void test_math16 ( ) {

  
  int16 angle = 0; angle16_degree_emC(45); //45°
  int step = 0;
  float dcosmax = -1.0f;
  float dcosmin = 1.0f;
  float dcosmax32 = -1.0f;
  float dcosmin32 = 1.0f;
  int16 ddcosmax = -0x7fff;
  int16 ddcosmin =  0x7fff;
  int16 cos0 = NOM_i16_Ctrl_emC;
  int16 ddcos0 = 0; 
  do {                                 // check any of 65536 angle values
    int16 cos1 = cos16_emC(angle);
    int32 cos32 = cos32_emC(((int32)angle) <<16);
    int16 ddcos1 = cos1 - cos0;        // difference to value before
    int16 dddcos = ddcos1 - ddcos0;    // difference of the last differences
    if(dddcos > ddcosmax) {            // builds the maximum between diff
      ddcosmax = dddcos; 
    }
    if(dddcos < ddcosmin) {            // and the minimum. 
      ddcosmin = dddcos; 
    }
    cos0 = cos1;
    ddcos0 = ddcos1;
    
    
    float cosfi = (float)cos1 / (float)NOM_i16_Ctrl_emC;
    float cosfi32 = (float)cos32 / (float)NOM_i32_Ctrl_emC;
    float anglef = 180.0f * angle / 0x8000U;
    float cosf1 = cosf(anglef / 180.0f * PI_float_emC);
    float dcos = cosfi - cosf1;
    if(dcos > dcosmax) { 
      dcosmax = dcos; 
    }
    if(dcos < dcosmin) { 
      dcosmin = dcos; 
    }
    float dcos32 = cosfi32 - cosf1;
    if(dcos32 > dcosmax32) { 
      dcosmax32 = dcos32; 
    }
    if(dcos32 < dcosmin32) { 
      dcosmin32 = dcos32; 
    }
    if(dcosmax32 > 0.01f) {
      step +=0;
    }
    if(dcosmin32 < -0.01f) {
      step +=0;
    }
    //printf(" *%d  g=%3.3f %1.5f %1.5f  %1.5f \n", step, anglef, cosfi, cosf1, dcos);    
    angle += 0x13; //angle16_degree_emC(0.1) ;
    step +=1;
  } while(angle !=0);
  
  printf("error range cos16: %1.5f .. %1.5f, error range cos32: %1.5f .. %1.5f, discont %d .. %d\n", dcosmin, dcosmax, dcosmin32, dcosmax32, ddcosmin, ddcosmax);
  step +=0;


}





