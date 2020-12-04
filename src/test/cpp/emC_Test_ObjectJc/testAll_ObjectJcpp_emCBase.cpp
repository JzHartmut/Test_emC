#include <applstdef_emC.h>
#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC_Test_ObjectJc/test_ObjectJcpp.h>
#include <emC_Test_C_Cpp/test_C_Cpp_TestemC.h>
#include <emC_Test_ObjectJc/test_ObjectJc_Mutex.h>
#include <emC_Test_CalcExpr/Calculator_test.h>
#include "emC_Test_C_Cpp/TestVtblExplicit.h"

void testAll_ObjectJcpp_emCBase() {
  test_ObjectJc();              //All tests with ObjectJc
  test_ObjectJc_SimpleLock();   //It shows a lock mechanism
  test_ObjectJcpp();            //All tests with ObjectJcpp
}


#ifdef DEF_MAIN_testMain_ObjectJc
int main(int nArgs, char** args) {
  
  test_ParseExpr();
  test_CalcExpr();

  testAll_ObjectJcpp_emCBase();
  main_test_C_Cpp();
}

#endif //DEF_MAIN_testMain_ObjectJc



