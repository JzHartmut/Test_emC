#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_ObjectJc/test_ObjectJcpp.h>
#include <stdio.h>

void testAll_ObjectJcpp_emCBase() {
  #ifndef GCC_TI2000
  #endif
  test_ObjectJcpp();
}


#ifdef DEF_DEVELOPER_TEST
int main(int nArgs, char** cmdArgs) {
  printf("test AAAAAA\n\n");
  STACKTRC_ENTRY("main");
  printf("test xxxxxxxx\n\n");
  testAll_ObjectJcpp_emCBase();
  printf("\nEND...\n");
  //test_ObjectJcpp();
  STACKTRC_RETURN 3;
}

#endif

