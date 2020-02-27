#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_ObjectJc/test_ObjectJcpp.h>


void testAll_ObjectJcpp_emCBase() {
  #ifndef GCC_TI2000
  #endif
  test_ObjectJcpp();
}


#ifdef DEF_DEVELOPER_TEST
void main(char** cmdArgs) {
  STACKTRC_ENTRY("main");
  //testAll_ObjectJcpp_emCBase();
  
  test_ObjectJcpp();
  STACKTRC_LEAVE;
}
#endif
