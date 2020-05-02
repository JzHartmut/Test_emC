#include "test_stdArray.h"
#include <array>



void test_stdArray ( ) {
  STACKTRC_ENTRY("test_stdArray");
  std::array<float,5> a1;
  bool bOk = true;
  TRY {
    a1[3] = 234.4f;
    a1[5] = 234.4f;
  } _TRY;
  CATCH(Exception, exc) {
    bOk = false;
  }
  END_TRY;
  STACKTRC_LEAVE;
}