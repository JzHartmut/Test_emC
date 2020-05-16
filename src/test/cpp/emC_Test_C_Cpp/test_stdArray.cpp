#include "test_stdArray.h"

#ifdef DEF_Cpp11_supported
#include <array>
#endif

#include <emC/Base/Array_emC.h>







float test_stdArray ( ) {
  STACKTRC_ENTRY("test_stdArray");
#ifdef DEF_Cpp11_supported
  std::array<float,5> a1;
#else
  float a1[5];
#endif
  float avar_[5];  //may be an array with a variable size.
  //ArrayVarsize_emC<float> arrayVariable = ArrayVarsize_emC<float>(avar_, ARRAYLEN_emC(avar_)); 
  ARRAYVAR_emC(float, arrayVariable, avar_, ARRAYLEN_emC(avar_));
  ARRAY_emC(float, 5, ae);
  float a5 = 0;
  int ixFaulty = 4;
  bool bOk = true;
  float* pa1 = &a1[0];
  float* pa5 = &a5;
  TRY {
    ae.uncheckedAccess(0) = 234;
    UNCHECKED_ACCESS_Array_emC(ae, 2) = 24.3f;
    arrayVariable.uncheckedAccess(3) = 12;
    arrayVariable[ixFaulty] = 99.9f;
    ae[ixFaulty] = 77;
    a1[3] = 234.4f;
    a1[ixFaulty] = 234.4f;
    a5 = 12366.5f;
  } _TRY
  CATCH(Exception, exc) {
    bOk = false;
    a5 = 7777.7f;
  }
  END_TRY;
  STACKTRC_RETURN a5;
}
