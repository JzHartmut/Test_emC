#include <applstdef_emC.h>
#include <emC_Test_ObjectJc/test_ObjectJcpp.h>
#include <stdio.h>

void testAll_ObjectJcpp_emCBase() {
  #ifndef GCC_TI2000
  #endif
  test_ObjectJcpp();
}


#ifdef DEF_DEVELOPER_TEST
int main(int nArgs, char** cmdArgs) {
  printf("test-debug testAll__ObjectJcpp_emCBase.cpp:");
  STACKTRC_ENTRY("main");
  testAll_ObjectJcpp_emCBase();
  printf("\nEND testAll__ObjectJcpp_emCBase.cpp\n");
  //test_ObjectJcpp();
  STACKTRC_RETURN 3;
}

#endif

