#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC_Test_ObjectJc/test_ObjectJcpp.h>
#include <emC_Test_C_Cpp/test_C_Cpp_TestemC.h>

#ifdef DEF_MAIN_testMain_ObjectJc
int main(int nArgs, char** args) {
  test_ObjectJc();
  //main_test_C_Cpp();
  test_ObjectJcpp();
}

#endif //DEF_MAIN_testMain_ObjectJc
