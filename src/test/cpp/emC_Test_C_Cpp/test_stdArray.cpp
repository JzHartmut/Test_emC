#include "test_stdArray.h"

#ifdef DEF_Cpp11_supported
#include <array>
#endif

#include <emC/Base/Array_emC.h>
#include <emC/Test/testAssert.h>







float test_stdArray ( ) {
  STACKTRC_ENTRY("test_stdArray");
  TEST_START("test_stdArray");

#if defined(DEF_Cpp11_supported) && defined(DEF_Exception_TRYCpp)
  std::array<float,5> array_Cpp11;
#endif
  float avar_[5];  //may be an array with a variable size.
  //ArrayVarsize_emC<float> arrayVariable = ArrayVarsize_emC<float>(avar_, ARRAYLEN_emC(avar_)); 
  ARRAYVAR_emC(float, arrayVariable, avar_, ARRAYLEN_emC(avar_));
  ARRAY_emC(float, 5, ae);
  float a5 = 0;
  uint ixFaulty = 5;
  MAYBE_UNUSED_emC float* pa5 = &a5;
  bool bHasCatched = false;  
  TRY {
    ae.uncheckedAccess(0) = 234;
    UNCHECKED_ACCESS_Array_emC(ae, 2) = 24.3f;
    arrayVariable.uncheckedAccess(3) = 12;
    arrayVariable[ixFaulty] = 99.9f;
    ae[ixFaulty] = 77;
    #if defined(DEF_Cpp11_supported) && defined(DEF_Exception_TRYCpp)
      float* pa1 = &array_Cpp11[0];
      array_Cpp11[3] = 234.4f;
      array_Cpp11[ixFaulty] = 234.4f;
      #endif
      a5 = 12366.5f;
  } _TRY
  CATCH(Exception, exc) {
    bHasCatched = true;  
    a5 = 7777.7f;
  }
  END_TRY;
  TEST_TRUE(bHasCatched, "Array index error catched. ");
  TEST_END;
  STACKTRC_RETURN a5;
}
