#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
//#include <emC_Test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>
#include <emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.h>
#include <emC_Test_C_Cpp/TestVtblExplicit.h>
#include <emC_BlockHeapTest/BlockHeapTest_emC.h>
#include <emC_Test_C_Cpp/test_stdArray.h>
#include <emC_Exmpl_Ctrl/Test_Ctrl.h>
#include <emC_Test_Stacktrc_Exc/TestException.h>
#include <stdio.h>








#ifdef DEF_TESTALL_emC
int main(int nArgs, char const*const* cmdArgs )
{
  STACKTRC_ROOT_ENTRY("main");
  outTestConditions();
  testAll_ObjectJcpp_emCBase();
  test_TestVtblExplicit();

  test_Exception();
  test_stdArray();


  //testAll_Stacktrc_Exc_emCBase();
  testAll_StateM_emCBase();
  //test_Test_Ctrl(20000);
  //
  //test BlockHeap at last because all other tests would use the BlockHeap
  #ifdef USE_BlockHeap_emC
    testBlockHeap_emC();
  #endif
  STACKTRC_RETURN 0;
}
#endif
