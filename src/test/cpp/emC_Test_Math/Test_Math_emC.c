#include <emC_Test_Math/Test_Math_emC.h>
#include <emC/Base/Math_emC.h>
#include <applstdef_emC.h>
#include <math.h>

void test_Q_rsqrt ( ) {

  float x[] = { 0.1f, 0.2f, 1.0f, 2.0f, 4.0f, 9.0f }; 
  float y[ARRAYLEN_emC(x)] = {0};
  float error = 0;
  for(int ix = 0; ix < ARRAYLEN_emC(x); ++ix) {
    float x1 = x[ix];
    float yq = Q_rsqrt(x1);
    float ye = 1.0f / sqrtf(x1);
    y[ix] = yq;
    float error1 = fabsf(ye - yq) / ye;
    if(error1 > error) {
      error = error1; 
    } 
  }


}