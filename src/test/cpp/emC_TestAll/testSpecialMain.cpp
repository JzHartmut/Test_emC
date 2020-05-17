#include <applstdef_emC.h>
#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC_StringTest/StringTest_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
//#include <emC_Test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>
#include <emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.h>

#include <emC_Test_C_Cpp/InitComposite_C_CPP_TestemC.h>
#include <emC_BlockHeapTest/BlockHeapTest_emC.h>

#include <emC_Test_C_Cpp/TestVtblExplicit.h>
#include <emC_Test_C_Cpp/test_stdArray.h>
#include <emC_Exmpl_Ctrl/Test_Ctrl.h>
#include <emC_Test_Stacktrc_Exc/TestException.h>


#ifdef DEF_MAIN_emC_TestAll_testSpecialMain
int main(int nArgs, char const*const* cmdArgs )
{
  STACKTRC_ROOT_ENTRY("main");
  test_Exception();
  test_stdArray();
  //test_Alloc_ObjectJc();
  test_ObjectJc();
  //testString_emC();
  //testBlockHeap_emC();

  //testVtbl_virtual();
  //test_TestVtblExplicit();
  //test_InitComposite_C_CPP_TestemC();
  test_Test_Ctrl(20000);

  testAll_ObjectJcpp_emCBase();
  //testAll_Stacktrc_Exc_emCBase();
  //testAll_StateM_emCBase();
  STACKTRC_RETURN 0;
}
#endif
