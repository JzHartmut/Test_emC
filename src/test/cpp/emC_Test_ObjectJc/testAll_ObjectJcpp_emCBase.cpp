#include <applstdef_emC.h>
#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC_Test_ObjectJc/test_ObjectJcpp.h>
#include <emC_Test_C_Cpp/test_C_Cpp_TestemC.h>
#include <emC_Test_ObjectJc/test_ObjectJc_Mutex.h>
#include <emC_Test_CalcExpr/Calculator_test.h>

void testAll_ObjectJcpp_emCBase() {
  test_ObjectJc();
  test_ObjectJc_SimpleLock(); 
  //main_test_C_Cpp();
  test_ObjectJcpp();
}


#ifdef DEF_MAIN_testMain_ObjectJc
int main(int nArgs, char** args) {
  
  test_ParseExpr();
  test_CalcExpr();

  testAll_ObjectJcpp_emCBase();
  //test_ObjectJc();
  //test_ObjectJc_SimpleLock(); 
  //main_test_C_Cpp();
  //test_ObjectJcpp();
}

#endif //DEF_MAIN_testMain_ObjectJc



