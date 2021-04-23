#include <emC_Test_Math/Test_Math_emC.h>
#include <emC/Base/Math_emC.h>
#include <emC/Test/testAssert.h>
#include <applstdef_emC.h>
#include <math.h>
#include <stdio.h>


void stop(){}

void test_Q_rsqrt ( ) {

  float x[] = { 0.1f, 0.2f, 1.0f, 2.0f, 4.0f, 9.0f }; 
  float y[ARRAYLEN_emC(x)] = {0};
  float error = 0;
  for(uint ix = 0; ix < ARRAYLEN_emC(x); ++ix) {
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
  MAYBE_UNUSED_emC int32 prod4000 = f1 * f2;

  MAYBE_UNUSED_emC int32 prob4000 = (int32)f1 * f2;

  uint16 f3 = 0xffff; 
  uint16 f4 = 0x4000;
  MAYBE_UNUSED_emC int32 prod_c000 = f3 * f4;
  MAYBE_UNUSED_emC int32 prob_c000 = (int32)f3 * f4;
  MAYBE_UNUSED_emC int32 pron_c000 = (int32)f3 * (int32)f4;

  uint32 f32a = 0xFFFFffff;
  uint32 f32b = 0xffffffff;
  MAYBE_UNUSED_emC uint32 pro32d_c000 = f32a * f32b;

  return 0;
}





void test_cos16 ( bool bprint ) {

  STACKTRC_ENTRY("test_cos16");
  TEST_START("test_cos16");
  int16 angle = 0; //angle16_degree_emC(45); //45�
  int step = 0;
  int dangle = 0x13;
  int32 intg = 0;
  do {                                 // check any of 65536 angle values
    int16 cos1 = cos16_emC(angle);
    //float cosfi = (float)cos1 / (float)(0x8000);
    float angleg = 180.0f * angle / (float)0x8000U;
    float angrad = PI_float_emC * angle / (float)0x8000U;
    int16 cosf16 = (int16)(cosf(angrad)*(float)(0x8000));
    int16 dcos = cos1 - cosf16;
    CHECK_TRUE2(dcos <= 8 && dcos >=-8, 0, "cos16 in range", angle, dcos);
    //
    float sinfi = (intg >>15) * PI_float_emC / 0x8000;  //the integration of int16 cos results is the sin
    float sinf1 = sinf(angrad);                         // compare with calculated sinus
    float dsinf = sinfi - sinf1;
    intg += dangle * cos1;                             // integration valid for the next value
    CHECK_TRUE2(fabsf(dsinf)<0.002f, 0, "integration follows sin", step, angle);
    if(bprint) {
      printf(" *%d  g=%3.3f %4.4X %4.4X %4.4X  %d /I=%8.8X %1.5f %1.5f\n", step, angleg, angle
            , cos1, cosf16, dcos, intg, sinfi, dsinf);
    }
    angle += dangle; //angle16_degree_emC(0.1) ;
    step +=1;
  } while(angle >=dangle || angle <0);
  TEST_END;
  //printf("error range cos16: %1.5f .. %1.5f, error range cos32: %1.5f .. %1.5f, discont %d .. %d\n", dcosmin, dcosmax, dcosmin32, dcosmax32, ddcosmin, ddcosmax);
  step +=0;

  STACKTRC_RETURN;
}




void test_sin16 ( ) {

  STACKTRC_ENTRY("test_sin16");
  TEST_START("test_sin16");
  int16 angle = 0; //angle16_degree_emC(45); //45�
  int step = 0;
  do {                                 // check any of 65536 angle values
    int16 sin1 = sin16_emC(angle);
    //float sinfi = (float)sin1 / (float)(0x8000);
    float anglef = 180.0f * angle / (float)0x8000U;
    int16 sinf16 = (int16)(sinf(anglef / 180.0f * PI_float_emC)*(float)(0x8000));
    int16 dsin = sin1 - sinf16;
    CHECK_TRUE2(dsin <= 8 && dsin >=-8, 0, "sin16 in range", angle, dsin);
    //printf(" *%d  g=%3.3f %4.4X %4.4X %4.4X  %d \n", step, anglef, angle, sin1, sinf16, dsin);
    angle += 0x13; //angle16_degree_emC(0.1) ;
    step +=1;
  } while(angle >=0x13 || angle <0);
  TEST_END;
  //printf("error range sin16: %1.5f .. %1.5f, error range sin32: %1.5f .. %1.5f, discont %d .. %d\n", dsinmin, dsinmax, dsinmin32, dsinmax32, ddsinmin, ddsinmax);
  step +=0;

  STACKTRC_RETURN;
}



int test_atan2nom16_MathemC ( bool bPrint, int16 dangle ) {
  STACKTRC_ENTRY("test_atan2nom16_MathemC");
  TEST_START("test_atan2nom16_MathemC");

  int16 angle = 0;
  int16 emin = 0x7fff, emax = -0x8000;
  do {
    float rad = radf_angle16_emC(angle);
    float re = cosf(rad);       // produce some complex values with given magnitued
    float im = sinf(rad);
    int16_complex x = { (int16)(re * 0x4000), (int16)(im * 0x4000)};
    //
    int16 angley = atan2nom16_emC(x);
    int16 eangle = angley - angle;
    if(eangle > emax) {
      emax = eangle;
    }
    if(eangle < emin) {
      emin = eangle;
    }
    if(bPrint) {
      printf("%4.4X %4.4X %d\n", angle, angley, eangle);
    }
    angle += dangle;
  } while(angle <0 || angle >= dangle);
  TEST_TRUE(emin >= -6 && emax <= 6, "angle error <=6/65536 =^ 0.033� ");
  TEST_END;
  STACKTRC_RETURN emax + emin;  //only to return something to prevent remove by optimizing
}






void test_sqrt16 ( ) {

  STACKTRC_ENTRY("test_sqrt16");
  TEST_START("test_sqrt16");
  uint16 x = 0x600; //angle16_degree_emC(45); //45�
  int step = 0;
  do {                                 // check any of 65536 angle values
    int16 sqrt1 = sqrt16_emC(x);
    //float sqrtfi = (float)sqrt1 / (float)(0x8000);
    float xf = x / (float)0x4000U;
    float yf = sqrtf(xf);
    int16 sqrtf16 = (int16)(yf*0x4000);
    int16 dsqrt = sqrt1 - sqrtf16;
    CHECK_TRUE2(dsqrt <= 9 && dsqrt >=-9, 0, "sqrt16 in range", x, dsqrt);
    printf(" *%d  g=%3.3f %4.4X %4.4X %4.4X  %d \n", step, xf, x, sqrt1, sqrtf16, dsqrt);
    x += 0x13; 
    step +=1;
  } while(x >=0x13 || x <0);
  TEST_END;
  //printf("error range sqrt16: %1.5f .. %1.5f, error range sqrt32: %1.5f .. %1.5f, discont %d .. %d\n", dsqrtmin, dsqrtmax, dsqrtmin32, dsqrtmax32, ddsqrtmin, ddsqrtmax);
  step +=0;

  STACKTRC_RETURN;
}




void test_rsqrt4_32 ( ) {

  STACKTRC_ENTRY("test_rsqrt16");
  TEST_START("test_rsqrt16 from 0x1400 =^0.3125 .. 0xffff, 0x4000 =^ 1.0");
  uint16 x = 0x1400; //if is 0.25
  uint16 x2 = 0x2a00;   //to switch to finer check
  uint16 dx = 0x80;
  int step = 0;
  int errorAdmissible = 144;
  int errormax = -32768, errormin = 0x7fff;
  do {                                 // check any of 65536 angle values
    int16 y1 = rsqrt16_emC(x);
    //float sqrtfi = (float)y1 / (float)(0x8000);
    float xf = x / (float)0x4000U;
    float yf = 1.0f / sqrtf(xf);
    int16 yf16 = (int16)(yf*0x4000);
    int16 dy = y1 - yf16;
    if(dy > errormax) { errormax = dy; }
    if(dy < errormin) { errormin = dy; }
    CHECK_TRUE2(dy <= errorAdmissible && dy >=-errorAdmissible, 0, "rsqrt16 in range", x, dy);
    printf(" *%d  x=%3.3f %4.4X %4.4X %4.4X  %d \n", step, xf, x, y1, yf16, dy);
    if(x >= x2) {
      x2 = 0xffff;
      TEST_TRUE(errormax >=0 && errormax < errorAdmissible && errormin<=0 && errormin > -errorAdmissible, "max error <144 till 0x2A00 =^0.656");
      errorAdmissible = 26;
      errormax = -32768; errormin = 0x7fff;
    }   
    int32 xnew = (int32)(x) + dx;
    if(xnew > 0xffff) break;
    x = (int16)(xnew); 
    step +=1;
  } while(x >=dx || x <0);
  TEST_TRUE(errormax >=0 && errormax < errorAdmissible && errormin<=0 && errormin > -errorAdmissible, "max error <26 from 0x2A00  =^0.656 .. 0xffff");
  TEST_END;
  
  STACKTRC_RETURN;
}





void test_rsqrt2_32 ( ) {

  STACKTRC_ENTRY("test_rsqrt16");
  TEST_START("test_rsqrt2_32 from 0 .. 0x7fff, 0x4000 =^ 1.0");
  uint16 xValues[] =        { 0x0000, 0x1200, 0x14a0, 0x19a0, 0x2900, 0x7fff} ;   //to switch to finer check
  int errorsMaxAdmissible2[] = { 0,       58,     43,     27,   10,      0};
  int errorsMinAdmissible2[] = {-0x7fff,-1000,   -43,    -27,  -10,      0};
  char const* testTxts2[] = {
    "y == 0x7fff for x < 0de0, y lesser as expected from 0x0de0 .. 0x1200 =^ 0.000 .. 0.281"
  , "max error -1000.. 58 from 0x1280 .. 0x14a0 =^ 0.281 .. 0.322"
  , "max error <42 from 0x14A0 .. 0x19a0 =^ 0.322 .. 0.400"
  , "max error <27 from 0x19a0 .. 0x2900 =^ 0.400 .. 0.641"
  , "max error <10 from 0x2700 .. 0x7fff =^ 0.641 .. 1.9993"
  , "???"
  };
  uint16 dx = 0x20;
  int ixx2 = 0;
  int step = 0;
  int errormax = -32768, errormin = 0x7fff;
  int16 x = xValues[ixx2];
  int errorMaxAdmissible = errorsMaxAdmissible2[ixx2];
  int errorMinAdmissible = errorsMinAdmissible2[ixx2];
  int16 x2 = xValues[++ixx2];
  do {                                 // check any of 65536 angle values
    int16 y = rsqrt16_emC(x);
    if(x < 0x0de0) {
      CHECK_TRUE2(y == 0x7fff, 0, testTxts2[ixx2-1], x, y);
      errormax = 0; errormin = 0x7fff;  //do not check errormax >=0 in the first segment
    } else {
      //float sqrtfi = (float)y / (float)(0x8000);
      float xf = x / (float)0x4000U;
      float yf = 1.0f / sqrtf(xf);
      int16 yf16 = (int16)(yf*0x4000);
      int16 dy = y - yf16;
      if(dy > errormax) { errormax = dy; }
      if(dy < errormin) { errormin = dy; }
      //printf(" *%d  x=%3.3f %4.4X %4.4X %4.4X  %d \n", step, xf, x, y, yf16, dy);
      if(!(dy <= errorMaxAdmissible && dy >=errorMinAdmissible)) {
        CHECK_TRUE2(false, 0, testTxts2[ixx2-1], x, dy);
      }
    }
    if(x >= x2) {
      TEST_TRUE(errormax >=0 && errormax <= errorMaxAdmissible && errormin<=0 && errormin >= errorMinAdmissible, testTxts2[ixx2-1]);
      errorMaxAdmissible = errorsMaxAdmissible2[ixx2];
      errorMinAdmissible = errorsMinAdmissible2[ixx2];
      x2 = xValues[++ixx2];
      errormax = -32768; errormin = 0x7fff;
    }   
    int32 xnew = (int32)(x) + dx;
    if(xnew > 0x7fff) break;
    x = (int16)(xnew); 
    step +=1;
  } while(x >=dx || x <0);
  TEST_TRUE(errormax >=0 && errormax <= errorMaxAdmissible && errormin<=0 && errormin >= errorMinAdmissible, testTxts2[ixx2-1]);
  TEST_END;
  
  STACKTRC_RETURN;
}


int test_Nom_int16_complex ( ) {
  STACKTRC_ENTRY("test_Nom_int16_complex");
  TEST_START("test_Nom_int16_complex");

  Nom_int16_complex_s data;
  ctor_Nom_int16_complex(&data);
  int16 angle = 0;
  float magn = 1.993f;
  float magnerr = -9999.0f;
  for(int step = 0; step < 1000; ++step) {
    float rad = radf_angle16_emC(angle);
    float re = magn * cosf(rad);       // produce some complex values with given magnitued
    float im = magn * sinf(rad);
    int16_complex x = { (int16)(re * 0x4000), (int16)(im * 0x4000)};
    //
    step_Nom_int16_complex(&data, x);  // The test object
    //
    float rmagn = data.rmagn / (float)(0x4000);
    float err = fabsf(rmagn * magn - 1.0f);
    if(step >=10) {                    //time to setup, only 10 cycles.
      if(err > magnerr) {               
        magnerr = err;                 // error of magnitude 
      }
      if(err > 0.2f) {
        stop();
      }
    }
    angle += 0x100;
    if(step >=100) {                  // change the magn as smoothing in 100 steps till 37%, it is till 0.37 * (1.993 - 0.6) + 0.6
      magn += 0.01f * (0.6f - magn);  // smoothing the magnitude from 1.993 till 0.5, all should work. 
    }
  }
  TEST_TRUE(magnerr < 0.005f, "Magnitude error < 0.5% though 100 steps ampl change 1.9 => 1.1, then till 0.6");
  TEST_END;
  STACKTRC_RETURN data.rmagn;  //only to return something to prevent remove by optimizing
}






