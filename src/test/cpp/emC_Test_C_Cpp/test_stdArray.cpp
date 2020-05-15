#include "test_stdArray.h"

#ifdef DEF_Cpp11_supported
#include <array>
#endif

template<typename T, int n>
class Array_emC {
  T array[n+1];
  public: T& operator[](uint ix) { 
    if(ix < n) return array[ix];
    else {
      THROW_s0n(ArrayIndexOutOfBoundsException, "", ix, n);
      return array[n];
    }
  }
};







float test_stdArray ( ) {
  STACKTRC_ENTRY("test_stdArray");
#ifdef DEF_Cpp11_supported
  std::array<float,5> a1;
#else
  float a1[5];
#endif
  Array_emC<float, 5> ae;
  float a5 = 0;
  int ixFaulty = 5;
  bool bOk = true;
  float* pa1 = &a1[0];
  float* pa5 = &a5;
  TRY {
    ae[0] = 234;
    ae[ixFaulty] = 77;
    a1[3] = 234.4f;
    a1[ixFaulty] = 234.4f;
    a5 = 12366.5f;
  } _TRY;
  CATCH(Exception, exc) {
    bOk = false;
    a5 = 7777.7f;
  }
  END_TRY;
  STACKTRC_RETURN a5;
}
