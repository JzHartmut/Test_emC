#include <applstdef_emC.h>
#include <emC_Test_ObjectJc/test_ObjectJcpp.h>
#include <stdio.h>

void testAll_ObjectJcpp_emCBase() {
  #ifndef GCC_TI2000
  outTestConditions();
  #endif
  test_ObjectJcpp();
}



