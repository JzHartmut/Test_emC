#include <emC_Test_Ctrl/test_OrthOsc.h>
#include <emC/Test/testAssert.h>
#include <emC/Base/Math_emC.h>
#include <emC/Ctrl/OrthBandpass_Ctrl_emC.h>

#include <math.h>
#include <stdio.h>

void test_OrthBandpassF_fast(void) {
  TEST_START("test_OrthBandpassF_fast");

  float m_nom = 0.1f;
  //Parameter-Instance: 
  Param_OrthBandpassF_Ctrl_emC par1(0, 0.001f, 0.00005f, m_nom);

  OrthBandpassF_Ctrl_emC osc1(0.1f, -0.0f, 0, 0.00005f);

  float fq = 350.0f;

  osc1.init(&par1);
  par1.setFq(fq); //60 steps, it is 20 kHz/60

  float g = 0.0f;
  uint simCt = 60 * 20;                //simulates 20 periods
  uint ctprintf = 1;
  uint printfPer = 1;
  uint ctTfq = 1;
  uint divTfq = 16;
  float danglemid = 0;
  while( --simCt >0) {
    float dg = 2 * PI_float_emC * fq * 0.00005f;        //it is 60 points per period
    g += dg;                           //step in angle
    float u = m_nom * sinf(g);
    float d = u - osc1.yab.re;
    osc1.step(d, d); 
    float mx = sqrtf(osc1.yab.re * osc1.yab.re + osc1.yab.im * osc1.yab.im);
    float m;
    calcMagn_OrthBandpassF_Ctrl_emC(&osc1, &m);
    if(--ctprintf ==0) {
      printf("% 1.3f ab=% 1.3f,% 1.3f d=% 1.3f %1.3f %1.3f fq=%3.3f\n", u, osc1.yab.re, osc1.yab.im, d, mx, m, fq);
      ctprintf = printfPer;
    }
  }


  TEST_END;
}



void test_OrthBandpass16(void) {
  TEST_START("test_OrthBandpass");

  //Parameter-Instance: 
  Param_OrthBandpass16_Ctrl_emC par1(0, 0.001f, 0.00005f);

  OrthBandpass16_Ctrl_emC osc1(0.1f, -0.1f, 0, 0.00005f);

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


class Test_OrthBandpass
{

  Param_OrthBandpass32_Ctrl_emC par1;
  OrthBandpass32_Ctrl_emC osc1;

  Param_OrthBandpass16_Ctrl_emC par16;
  OrthBandpass16_Ctrl_emC osc16;

  float fq = 50.0f;
  float g = 0.0f;
  uint simCt = 0;                //simulates 20 periods
  uint ctprintf = 1;
  uint printfPer = 1;
  uint ctTfq = 1;
  uint divTfq = 16;
  //int16 az = 0;          
  //int16_complex abz;      
  float danglemid = 0;

  public: Test_OrthBandpass();

  private: void testStep_OrthBandpass ( );

  public: void test ( );
};


Test_OrthBandpass::Test_OrthBandpass()
: par1(0, 0.001f, 0.00005f)
, osc1(0.1f, -0.1f, 0, 0.00005f)
, par16(0, 0.001f, 0.00005f)
, osc16(0.1f, -0.1f, 0, 0.00005f)
{
}


void Test_OrthBandpass::testStep_OrthBandpass (  )
{

  double ud = sin(g);
  int32 u = (int32)(0x40000000 * ud);
  int32 d = u - osc1.yab.re;
  int16 u16 = (int16)(0x4000 * ud);
  int16 d16 = (int16)(u16 - (int16)((osc16.yab.re >>16) & 0xffff));
  //
  if(simCt == 99) {
    simCt +=0;
  }
  osc1.step(d, 0); 
  osc16.step(d16, 0);
  //
  double af = osc1.yab.re / (double)(0x40000000);
  double bf = osc1.yab.im / (double)(0x40000000);
  double magn = sqrt(af*af + bf*bf);
  float dangle = (float)(d/10000.0f * (osc1.yab.re/1000000000.0f + osc1.yab.im/1000000000.0f));  //build the abbreviation value
  danglemid += 0.05f * (dangle - danglemid);
  if(--ctTfq ==0) {                  // divided step time Tfq:
    fq += 0.000f * danglemid;
    ctTfq = divTfq;                  // reload time Tfq
  }
  if(--ctprintf ==0) {
    printf("%d: %1.3f ab=%1.7f|%1.7f ab=%1.4f|%1.4f magn=%1.10f d=%8.8x d16=%4.4x %1.3f fq=%3.3f\n"
          , simCt, ud
          , osc1.yab.re/(float)(0x40000000), osc1.yab.im/(float)(0x40000000)
          , osc16.yab.re/(float)(0x40000000), osc16.yab.im/(float)(0x40000000)
          , magn, d, d16, danglemid, fq);
    ctprintf = printfPer;
  }

} 



void test_OrthBandpass32(void) {

  Test_OrthBandpass thiz;  //executes default ctor
  thiz.test();

}

void Test_OrthBandpass::test ( )
{
  TEST_START("test_OrthBandpass");
  //Parameter-Instance: 

  osc1.init(&par1);
  par1.setFq(fq); //60 steps, it is 20 kHz/60
  osc16.init(&par16);
  par16.setFq(fq); //60 steps, it is 20 kHz/60

  //int16 az = 0;          
  //int16_complex abz;      
  osc1.yab.im = -0x00000000;           // initial it with {-1, 0}, => without transition in
  osc16.yab.im = -0x40000000;           // initial it with {-1, 0}, => without transition in
  g = 0;
  float dg = 2 * PI_float_emC * fq * 0.00005f;        //it is 60 points per period
  this->simCt = 0;
  while( simCt < 800) {
    this->testStep_OrthBandpass();
    g += dg;                           //step in angle
    simCt +=1;
  }

  osc1.yab.re = osc1.yab.im = 0;           // initial it with {-1, 0}, => without transition in
  osc16.yab.re = osc16.yab.im = 0;           // initial it with {-1, 0}, => without transition in
  osc1.setkAB(1.0f, -1.0f);
  osc16.setkAB(1.0f, -1.0f);
  g = 0;
  dg = 2 * PI_float_emC * fq * 0.00005f;        //it is 60 points per period
  this->simCt = 0;
  while( simCt < 800) {
    this->testStep_OrthBandpass();
    g += dg;                           //step in angle
    simCt +=1;
  }

  TEST_END;

}
