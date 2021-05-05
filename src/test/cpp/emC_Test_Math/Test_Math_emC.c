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





int testMult16_Math_emC ( Test_Data16_Math_emC_s*  values, int zValues) {
  STACKTRC_ENTRY("testMult16_Math_emC");
  int err1 = 0, err2=0;
  TEST_TRY("muls16_emC and mulu16_emC: platform depending MACROs are correct") {
    for(int ix=0; ix < zValues; ++ix) {
      int16 as = (int16)values[ix].a;
      int16 bs = (int16)values[ix].b;
      int32 rs; 
      muls16_emC(rs, as, bs);
      uint16 bu = (uint16)values[ix].b;
      uint16 au = (uint16)as;
      uint32 ru; 
      mulu16_emC(ru, au, bu);
      TEST_TRUE(rs == (int32)values[ix].rs, "muls16_emC %8.8X = %4.4X*%4.4X", rs, (int)(as) & 0xffff, (int)bs & 0xffff);
      if(rs != (int32)values[ix].rs) {
        err1 +=1;
        //CHECK_TRUE(false, "muls16_emC fails on %8.8X = %4.4X*%4.4X", rs, as, bs);
      }
      TEST_TRUE(ru == values[ix].ru, "mulu16_emC %8.8X = %4.4X*%4.4X", ru, au, bu);
      if(ru != values[ix].ru) {
        err2 +=1;
      }
    }    
  }_TEST_TRY_END
  int ret = err1 + err2;
  STACKTRC_RETURN ret;
}



int testMult32Lo_Math_emC ( Test_Data16_Math_emC_s*  values, int zValues) {
  STACKTRC_ENTRY("testMult32Lo_Math_emC");
  int err1 = 0, err2=0;
  TEST_TRY("mul32lo_emC: platform depending MACROs are correct") {
    for(int ix=0; ix < zValues; ++ix) {
      int32 as = (int32)(int16)values[ix].a;       // expand given 16 bit to 32 bit with correct sign
      int32 bs = (int32)(int16)values[ix].b;       // necessary firstly to declare as (int16), in the table is uint16
      int32 rs; 
      mul32lo_emC(rs, as, bs);
      int64 rs2 = (int64)(as) * (int64)(bs);       // to compare the result: uses a full 64 bit mults with 32 bit input
      uint32 au = (uint32)values[ix].a;            // expand given 16 bit to 32 bit with hi bits = 0
      uint32 bu = (uint32)values[ix].b;
      uint32 ru; 
      mul32lo_emC(ru, au, bu);
      uint64 ru2 = (uint64)(au) * (uint64)(bu);    // to compare the result: uses a full 64 bit mults with 32 bit input
      TEST_TRUE(rs == (int32)values[ix].rs, "mul32lo_emC   signed %8.8X %8.8X = %8.8X * %8.8X", (int32)(rs2>>32), (int32)(rs2 & 0xffffffff), (int)(as) & 0xffff, (int)bs & 0xffff);
      if(rs != (int32)values[ix].rs) {
        err1 +=1;
        //CHECK_TRUE(false, "muls16_emC fails on %8.8X = %4.4X*%4.4X", rs, as, bs);
      }
      TEST_TRUE(ru == values[ix].ru, "mul32lo_emC unsigned %8.8X %8.8X = %8.8X * %8.8X", (uint32)(ru2>>32), (uint32)(ru2 & 0xffffffff), au, bu);
      if(ru != values[ix].ru) {
        err2 +=1;
      }
    }    
  }_TEST_TRY_END
  int ret = err1 + err2;
  STACKTRC_RETURN ret;
}



static struct XXXTest_Mult32_Math_emC_T {
    uint32 a1;    uint32 a2;  uint32 rss; uint32 rsu; uint32 ruu; } values32[16] = 
{ { 0x40000000, 0xffffffff, 0xffffc000, 0x3fffc000, 0x3fffc000 } //0
, { 0x7fffffff, 0xffffffff, 0xffff8001, 0x7ffe8001, 0x7ffe8001 } //1
, { 0xc0000000, 0xffffffff, 0x00004000, 0xc0004000, 0xbfff4000 } //2
, { 0x80000000, 0xffffffff, 0x00008000, 0x80008000, 0x7fff8000 } //3
, { 0x00000001, 0xffffffff, 0xffffffff, 0x0000ffff, 0x0000ffff } //4
, { 0xffffffff, 0xffffffff, 0x00000001, 0xffff0001, 0xfffe0001 } //5
, { 0x40000000, 0x7fffffff, 0x1fffc000, 0x1fffc000, 0x1fffc000 } //6
, { 0x7fffffff, 0x7fffffff, 0x3fff0001, 0x3fff0001, 0x3fff0001 } //7
, { 0xc0000000, 0x7fffffff, 0xe0004000, 0xe0004000, 0x5fff4000 } //8
, { 0x80000000, 0x7fffffff, 0xc0008000, 0xc0008000, 0x3fff8000 } //9
, { 0x00000001, 0x7fffffff, 0x00007fff, 0x00007fff, 0x00007fff } //10
, { 0xffffffff, 0x7fffffff, 0xffff8001, 0xffff8001, 0x7ffe8001 } //11
, { 0x40000000, 0x00000001, 0x00004000, 0x00004000, 0x00004000 } //12
, { 0xc0000000, 0x40000000, 0xF0000000, 0xF0000000, 0x30000000 } //13
, { 0x40000000, 0xc0000000, 0xF0000000, 0x30000000, 0x30000000 } //14
, { 0x40000000, 0x80000000, 0xE0000000, 0x20000000, 0x20000000 } //15
};


int testMult32_Math_emC ( Test_Data16_Math_emC_s*  values, int zValues ) {
  STACKTRC_ENTRY("testMult32_Math_emC");
  int err1 = 0, err2=0, err3=0;
  TEST_TRY("muls32hi_emC and mulu32hi_emC: platform depending MACROs are correct") {
    for(uint ix=0; ix < ARRAYLEN_emC(values32); ++ix) {
      //int32 as = values32[ix].a1;
      //int32 bs = values32[ix].a2;
      int32 as = ((int32)(int16)values[ix].a)<<16;
      int32 bs = ((int32)(int16)values[ix].b)<<16;
      int32 rs;  muls32hi_emC(rs, as, bs);
      int64 rs2 = (int64)(as) * (int64)(bs);       // to compare the result: uses a full 64 bit mults with 32 bit input
      //uint32 au = (uint32)as;
      //uint32 bu = (uint32)bs;
      int32 au = ((uint32)values[ix].a)<<16;
      int32 bu = ((uint32)values[ix].b)<<16;
      uint32 ru; mulu32hi_emC(ru, au, bu);
      int64 ru2 = (uint64)(au) * (uint64)(bu);     // to compare the result: uses a full 64 bit mults with 32 bit input
      TEST_TRUE((uint32)(rs) == values[ix].rs, "muls32hi_emC %8.8X %8.8X = %8.8X * %8.8X", (int32)(rs2>>32), (int32)(rs2 & 0xffffffff), as, bs);
      if((uint32)(rs) != values[ix].rs) {
        err1 +=1;
      }
      TEST_TRUE((uint32)(ru) == values[ix].ru, "mulu32hi_emC %8.8X %8.8X = %8.8X * %8.8X", (uint32)(ru2>>32), (uint32)(ru2 & 0xffffffff), as, bu);
      if((uint32)(ru) != values[ix].ru) {
        err2 +=1;
      }
    }
  } _TEST_TRY_END    
  int ret = err1 + err2 + err3;
  STACKTRC_RETURN ret;
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


int test_AddSat_Math_emC ( Test_Data16_Math_emC_T* data, int zData) {
  STACKTRC_ENTRY("test_AddSat_Math_emC");
  int ret = 0;
  TEST_TRY("adds16sat_emC and addu16sat_emC: platform depending MACROs are correct") {
    for(int ixData = 0; ixData< zData; ++ixData) {
      DEFsatCheck_emC;
      char const* isSat;
      int16 as = (int16)data[ixData].a;
      int16 bs = (int16)data[ixData].b;
      uint16 au = data[ixData].a;
      uint16 bu = data[ixData].b;
      int16 rs;
      uint16 ru, su;
      /* expanded macro, to find errors ....
      { int16 a = (as); int16 b = (bs); rs = a + b; \
        if(((a^b) &0x8000)==0) { if((a ^ rs)&0x8000) { rs = a & 0x8000 ? (int16)(0x8000): 0x7FFF; }} \
      }
      */
      clearSatCheck_emC();       
      adds16sat_emC(rs, as, bs);
      int16 rsCmp = (int16)data[ixData].rs;
      isSat = satCheck_emC() ? "sat" : "";
      TEST_TRUE(rs == rsCmp, "adds16sat_emC: %4.4x + %d  => %4.4X %s", as & 0xffff, bs, rs & 0xffff, isSat);
      //  
      /* expanded macro, to find errors ....
      { uint16 a = (au); uint16 b = (bu);  ru = (uint16)((a + b) & 0xffff); \
        if(ru < a || ru < b) { ru = 0xFFFF; } \
      } 
      */  
      clearSatCheck_emC();       
      addu16sat_emC(ru, au, bu);
      uint16 ruCmp = (uint16)data[ixData].ru;
      isSat = satCheck_emC() ? "sat" : "";
      TEST_TRUE(ru == ruCmp, "addu16sat_emC: %4.4x + %4.4X => %4.4X %s", au, bu, ru & 0xffff, isSat);
      //
      clearSatCheck_emC();       
      subu16sat_emC(su, au, bu);
      uint16 suCmp = (uint16)data[ixData].su;
      isSat = satCheck_emC() ? "sat" : "";
      TEST_TRUE(su == suCmp, "subu16sat_emC: %4.4x - %4.4X => %4.4X %s", au, bu, su & 0xffff, isSat);
      ret += rs + ru + su;
    }
  }_TEST_TRY_END
  STACKTRC_RETURN ret;
}


int test_cos16 ( bool bprint ) {

  STACKTRC_ENTRY("test_cos16");
  int ret = 0;                         // only given to prevent optimization because unused code
  int step = 0;
  TEST_TRY("test_cos16") {
    int16 angle = 0; //angle16_degree_emC(45); //45�
    int dangle = 0x13;
    int32 intg = 0;
    do {                                 // check any of 65536 angle values
      int16 cos1 = cos16_emC(angle);
      ret += cos1;
      //float cosfi = (float)cos1 / (float)(0x8000);
      float angleg = 180.0f * angle / (float)0x8000U;
      float angrad = PI_float_emC * angle / (float)0x8000U;
      int16 cosf16 = (int16)(cosf(angrad)*(float)(0x8000));
      int16 dcos = cos1 - cosf16;
      CHECK_TRUE(dcos <= 8 && dcos >=-8, "cos16 in range angle=%d dcos=%d", angle, dcos);
      //
      float sinfi = (intg >>15) * PI_float_emC / 0x8000;  //the integration of int16 cos results is the sin
      float sinf1 = sinf(angrad);                         // compare with calculated sinus
      float dsinf = sinfi - sinf1;
      intg += dangle * cos1;                             // integration valid for the next value
      CHECK_TRUE(fabsf(dsinf)<0.002f, "integration follows sin  step=%d, angle=%d", step, angle);
      if(bprint) {
        printf(" *%d  g=%3.3f %4.4X %4.4X %4.4X  %d /I=%8.8X %1.5f %1.5f\n", step, angleg, angle
              , cos1, cosf16, dcos, intg, sinfi, dsinf);
      }
      angle += dangle; //angle16_degree_emC(0.1) ;
      step +=1;
    } while(angle >=dangle || angle <0);
  }_TEST_TRY_END
  //printf("error range cos16: %1.5f .. %1.5f, error range cos32: %1.5f .. %1.5f, discont %d .. %d\n", dcosmin, dcosmax, dcosmin32, dcosmax32, ddcosmin, ddcosmax);
  step +=0;

  STACKTRC_RETURN ret;
}




int test_sin16 ( ) {
  STACKTRC_ENTRY("test_sin16");
  int step = 0;
  int ret = 0;                         // only given to prevent optimization because unused code
  TEST_TRY("test_sin16") {
    int16 angle = 0; //angle16_degree_emC(45); //45�
    do {                                 // check any of 65536 angle values
      int16 sin1 = sin16_emC(angle);
      ret += sin1;
      //float sinfi = (float)sin1 / (float)(0x8000);
      float anglef = 180.0f * angle / (float)0x8000U;
      int16 sinf16 = (int16)(sinf(anglef / 180.0f * PI_float_emC)*(float)(0x8000));
      int16 dsin = sin1 - sinf16;
      CHECK_TRUE(dsin <= 8 && dsin >=-8, "sin16 in range, angle=%d dsin=%d", angle, dsin);
      //printf(" *%d  g=%3.3f %4.4X %4.4X %4.4X  %d \n", step, anglef, angle, sin1, sinf16, dsin);
      angle += 0x13; //angle16_degree_emC(0.1) ;
      step +=1;
    } while(angle >=0x13 || angle <0);
  }_TEST_TRY_END
  //printf("error range sin16: %1.5f .. %1.5f, error range sin32: %1.5f .. %1.5f, discont %d .. %d\n", dsinmin, dsinmax, dsinmin32, dsinmax32, ddsinmin, ddsinmax);
  step +=0;

  STACKTRC_RETURN ret;
}



int test_atan2nom16_MathemC ( bool bPrint, int16 dangle ) {
  STACKTRC_ENTRY("test_atan2nom16_MathemC");
  int16 angle = 0;
  int16 emin = 0x7fff, emax = -0x8000;
  TEST_TRY("test_atan2nom16_MathemC") {

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
  } _TEST_TRY_END
  STACKTRC_RETURN emax + emin;  //only to return something to prevent remove by optimizing
}






int test_sqrt16 ( bool bPrint ) {

  STACKTRC_ENTRY("test_sqrt16");
  int ret = 0;                         // only given to prevent optimization because unused code
  int step = 0;
  TEST_TRY("test_sqrt16") {
    uint16 xz = 0;
    uint16 x = 0x0;                      // Start with this value, ~ 0.1, for lesser values the algorithm is inaccurate.
    int yerrMax = 0;
    uint16 xd = bPrint? 0x13 : 1;        // step width for test, 1: checks all values.
    int yerrLim = 0x3e8;
    do { 
      if(x >= 0x2400) { if(yerrLim !=9) { 
        TEST_TRUE(yerrMax <= yerrLim, "sqrt16 ... 0x2400 in range +-%d max abbr=%d", yerrLim, yerrMax);
        yerrLim = 9;      // accuracy depends on x, better for x >= 0xb00
        yerrMax = 0;
        }
      } else if(x >= 0x1000) { 
        if(yerrLim !=33) { 
          TEST_TRUE(yerrMax <= yerrLim, "sqrt16 ... 0x1000 in range +-%d max abbr=%d", yerrLim, yerrMax);
          yerrLim = 33; 
          yerrMax = 0;
        }
      }else if(x >= 0x0400) { if( yerrLim !=0x6c) { 
        TEST_TRUE(yerrMax <= yerrLim, "sqrt16 ... 0x0400 in range +-%d max abbr=%d", yerrLim, yerrMax);
        yerrLim = 0x6c; 
        yerrMax = 0;
      } }
      //
      int16 sqrt1 = sqrt16_emC(x);       // the test
      ret += sqrt1;
      //
      //float sqrtfi = (float)sqrt1 / (float)(0x8000);
      float xf = x / (float)0x4000U;
      float yf = sqrtf(xf);              // comparison with known floating calculation
      int16 sqrtf16 = (int16)(yf*0x4000);// float result in uint16
      int16 yerr = sqrt1 - sqrtf16;
      if(yerr <0) { yerr = -yerr; }
      if(yerrMax < yerr) { yerrMax = yerr; }
      CHECK_TRUE(yerr <= yerrLim, "sqrt16 in range x=%d, yerr=%d", x, yerr);
      if(bPrint) { printf(" *%d  g=%3.3f %4.4X %4.4X %4.4X  %d \n", step, xf, x, sqrt1, sqrtf16, yerr); }
      xz = x;
      x = (uint16)((x+xd) & 0xffff);  // 
      step +=1;
    } while(x > xz);                     // finish on overflow
    TEST_TRUE(yerrMax <= yerrLim, "sqrt16 0x2400 ... in range +-%d max abbr=%d", yerrLim, yerrMax);
  }_TEST_TRY_END
  //printf("error range sqrt16: %1.5f .. %1.5f, error range sqrt32: %1.5f .. %1.5f, discont %d .. %d\n", dsqrtmin, dsqrtmax, dsqrtmin32, dsqrtmax32, ddsqrtmin, ddsqrtmax);
  step +=0;

  STACKTRC_RETURN ret;
}




void test_rsqrt4_32 ( ) {

  STACKTRC_ENTRY("test_rsqrt4_32");
  TEST_TRY("test_rsqrt16 from 0x1400 =^0.3125 .. 0xffff, 0x4000 =^ 1.0") {
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
      CHECK_TRUE(dy <= errorAdmissible && dy >=-errorAdmissible, "rsqrt16 in range x=%d dy=%d", x, dy);
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
  }_TEST_TRY_END
  
  STACKTRC_RETURN;
}





int test_rsqrt2_32 ( bool bPrint ) {

  STACKTRC_ENTRY("test_rsqrt2_32");
  int ret = 0;                         // only given to prevent optimization because unused code
  TEST_TRY("test_rsqrt2_32 from 0 .. 0x7fff, 0x4000 =^ 1.0") {
    uint16 xValues[] =        { 0x0000, 0x1200, 0x14a0, 0x19a0, 0x2900, 0x7fff} ;   //to switch to finer check
    int errorsMaxAdmissible2[] = { 0,       58,     43,     27,   10,      0};
    int errorsMinAdmissible2[] = {-0x7fff,-1000,   -43,    -27,  -10,      0};
    char const* testTxts2[] = {
      "y == 0x7fff for x < 0de0, y lesser as expected from 0x0de0 .. 0x1200 =^ 0.000 .. 0.281"
    , "max error -1000.. 58 from 0x1280 .. 0x14a0 =^ 0.281 .. 0.322 x=%d y=%d"
    , "max error <42 from 0x14A0 .. 0x19a0 =^ 0.322 .. 0.400 x=%d y=%d"
    , "max error <27 from 0x19a0 .. 0x2900 =^ 0.400 .. 0.641 x=%d y=%d"
    , "max error <10 from 0x2700 .. 0x7fff =^ 0.641 .. 1.9993 x=%d y=%d"
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
      ret += y;
      if(x < 0x0de0) {
        CHECK_TRUE(y == 0x7fff, testTxts2[ixx2-1], x, y);
        errormax = 0; errormin = 0x7fff;  //do not check errormax >=0 in the first segment
      } else {
        //float sqrtfi = (float)y / (float)(0x8000);
        float xf = x / (float)0x4000U;
        float yf = 1.0f / sqrtf(xf);
        int16 yf16 = (int16)(yf*0x4000);
        int16 dy = y - yf16;
        if(dy > errormax) { errormax = dy; }
        if(dy < errormin) { errormin = dy; }
        if(bPrint) { printf(" *%d  x=%3.3f %4.4X %4.4X %4.4X  %d \n", step, xf, x, y, yf16, dy); }
        if(!(dy <= errorMaxAdmissible && dy >=errorMinAdmissible)) {
          CHECK_TRUE(false, testTxts2[ixx2-1], x, dy);
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
  }_TEST_TRY_END
  
  STACKTRC_RETURN ret;
}


int test_Nom_int16_complex ( ) {
  STACKTRC_ENTRY("test_Nom_int16_complex");
  Nom_int16_complex_s data;
  TEST_TRY("test_Nom_int16_complex") {

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
    TEST_TRUE(magnerr < 0.005f, "Magnitude error < 0.5%% though 100 steps ampl change 1.9 => 1.1, then till 0.6");
  }_TEST_TRY_END;

  STACKTRC_RETURN data.rmagn;  //only to return something to prevent remove by optimizing
}






