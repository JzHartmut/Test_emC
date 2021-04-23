#include <emC_Test_Ctrl/test_OrthOsc.h>
#include <emC/Test/testAssert.h>
#include <emC/Base/Math_emC.h>
#include <emC/Ctrl/OrthOsc_Ctrl_emC.h>

#include <math.h>
#include <stdio.h>

void test2_OrthOsc(void) {
  TEST_START("test_OrthOsc");

  //Parameter-Instance: 
  Param_OrthOsc2_CtrlemC par1(0, 0.001f, 0.00005f, 1.0f);

  OrthOsc2_CtrlemC osc1(0.1f, -0.1f, 0, 0.00005f);

  float fq = 201.0f;

  osc1.init(&par1);
  par1.setFq(fq); //60 steps, it is 20 kHz/60

  float g = 0.0f;
  uint simCt = 60 * 20;                //simulates 20 periods
  uint ctprintf = 1;
  uint printfPer = 1;
  uint ctTfq = 1;
  uint divTfq = 16;
  float az = 0;          
  float_complex abz;      
  float danglemid = 0;
  while( --simCt >0) {
    float dg = 2 * PI_float_emC * fq * 0.00005f;        //it is 60 points per period
    g += dg;                           //step in angle
    float u = sinf(g);
    float d = u - az;
    osc1.step(d, d, &az, &abz); 
    float dangle = d * (abz.re + abz.im);
    danglemid += 0.05f * (dangle - danglemid);
    if(--ctTfq ==0) {                  // divided step time Tfq:
      fq += 0.1f * danglemid;
      ctTfq = divTfq;                  // reload time Tfq
    }
    if(--ctprintf ==0) {
      printf("%1.3f %1.3f d=%1.3f %1.3f fq=%3.3f\n", u, az, d, danglemid, fq);
      ctprintf = printfPer;
    }
  }


  TEST_END;
}



void test_OrthOsc16(void) {
  TEST_START("test_OrthOsc");

  //Parameter-Instance: 
  Param_OrthOsc16_CtrlemC par1(0, 0.001f, 0.00005f, 1.0f);

  OrthOsc16_CtrlemC osc1(0.1f, -0.1f, 0, 0.00005f);

  float fq = 50.0f;

  osc1.init(&par1);
  par1.setFq(fq); //60 steps, it is 20 kHz/60

  float g = 0.0f;
  uint simCt = 60 * 20;                //simulates 20 periods
  uint ctprintf = 1;
  uint printfPer = 1;
  uint ctTfq = 1;
  uint divTfq = 16;
  //int16 az = 0;          
  //int16_complex abz;      
  float danglemid = 0;
  osc1.yab.im = -20000;
  while( --simCt >0) {
    float dg = 2 * PI_float_emC * fq * 0.00005f;        //it is 60 points per period
    g += dg;                           //step in angle
    int16 u = (int16)(20000 * sinf(g));
    int16 d = u - osc1.yab.re;
    osc1.step(d, d); 
    float af = osc1.yab.re / 20000.0f;
    float bf = osc1.yab.im / 20000.0f;
    float magn = sqrtf(af*af + bf*bf);
    float dangle = (float)(d * (int32)(osc1.yab.re + osc1.yab.im));  //build the abbreviation value
    danglemid += 0.05f * (dangle - danglemid);
    if(--ctTfq ==0) {                  // divided step time Tfq:
      fq += 0.000000002f * danglemid;
      ctTfq = divTfq;                  // reload time Tfq
    }
    if(--ctprintf ==0) {
      printf("%1.3f ab=%1.3f|%1.3f magn=%1.5f d=%1.3f %1.3f fq=%3.3f\n", u/20000.0f, osc1.yab.re/20000.0f, osc1.yab.im/20000.0f, magn, d/20000.0f, danglemid/20000.0f, fq);
      ctprintf = printfPer;
    }
  }


  TEST_END;
}



void test_OrthOsc32(void) {
  TEST_START("test_OrthOsc");

  //Parameter-Instance: 
  Param_OrthOsc32_CtrlemC par1(0, 0.001f, 0.00005f, 1.0f);

  OrthOsc32_CtrlemC osc1(0.1f, -0.1f, 0, 0.00005f);

  float fq = 50.0f;

  osc1.init(&par1);
  par1.setFq(fq); //60 steps, it is 20 kHz/60

  float g = 0.0f;
  uint simCt = 60 * 20;                //simulates 20 periods
  uint ctprintf = 1;
  uint printfPer = 1;
  uint ctTfq = 1;
  uint divTfq = 16;
  //int16 az = 0;          
  //int16_complex abz;      
  float danglemid = 0;
  osc1.yab.im = -1000000000;
  while( --simCt >0) {
    float dg = 2 * PI_float_emC * fq * 0.00005f;        //it is 60 points per period
    float uf = sinf(g);
    int16 u = (int16)(1000000000/65536.0f * uf);
    int16 d = u - (osc1.yab.re>>16);
    //
    osc1.step(d, d); 
    //
    float af = osc1.yab.re / 1000000000.0f;
    float bf = osc1.yab.im / 1000000000.0f;
    float magn = sqrtf(af*af + bf*bf);
    float dangle = (float)(d/10000.0f * (osc1.yab.re/1000000000.0f + osc1.yab.im/1000000000.0f));  //build the abbreviation value
    danglemid += 0.05f * (dangle - danglemid);
    if(--ctTfq ==0) {                  // divided step time Tfq:
      fq += 0.02f * danglemid;
      ctTfq = divTfq;                  // reload time Tfq
    }
    if(--ctprintf ==0) {
      printf("%1.3f ab=%1.3f|%1.3f magn=%1.5f d=%4.4x %1.3f fq=%3.3f\n", uf, osc1.yab.re/1000000000.0f, osc1.yab.im/1000000000.0f, magn, d, danglemid, fq);
      ctprintf = printfPer;
    }
    g += dg;                           //step in angle
  }


  TEST_END;
}
