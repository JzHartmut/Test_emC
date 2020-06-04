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

void outTestConditions ( ) {
  printf("settings usual for applstdef_emC.h:\n");
  #ifdef DEF_ObjectJc_SIMPLE
  printf("#define DEF_ObjectJc_SIMPLE\n");
  #endif
  #ifdef DEF_ObjectJc_REFLREF
  printf("#define DEF_ObjectJc_REFLREF\n");
  #endif
  #ifdef DEF_ObjectJcpp_REFLECTION
  printf("#define DEF_ObjectJcpp_REFLECTION\n");
  #endif
  #ifdef DEF_ObjectJc_OWNADDRESS
  printf("#define DEF_ObjectJc_OWNADDRESS\n");
  #endif
  #ifdef DEF_ClassJc_Vtbl
  printf("#define DEF_ClassJc_Vtbl\n");
  #endif
  #ifdef DEF_REFLECTION_FULL
  printf("#define DEF_REFLECTION_FULL\n");
  #endif
  #ifdef DEF_REFLECTION_OFFS
  printf("#define DEF_REFLECTION_OFFS\n");
  #endif
  #ifdef DEF_NO_StringJcCapabilities
  printf("#define DEF_NO_StringJcCapabilities\n");
  #endif
  #ifdef USE_BlockHeap_emC
  printf("#define USE_BlockHeap_emC\n");
  #endif
  #ifdef ASSERT_IGNORE_emC
  printf("#define ASSERT_IGNORE_emC\n");
  #endif
  #ifdef DEF_ThreadContext_SIMPLE
  printf("#define DEF_ThreadContext_SIMPLE\n");
  #endif
  #ifdef DEF_Exception_NO
  printf("#define DEF_Exception_NO\n");
  #endif
  #ifdef DEF_Exception_longjmp
  printf("#define DEF_Exception_longjmp\n");
  #endif
  #ifdef DEF_Exception_TRYCpp
  printf("#define DEF_Exception_TRYCpp\n");
  #endif
  #ifdef kMaxPathLength_FileDescription_OSAL
  printf("#define kMaxPathLength_FileDescription_OSAL %d\n", kMaxPathLength_FileDescription_OSAL);
  #endif
  #ifdef sizeSafetyArea_allocMemC
  printf("#define sizeSafetyArea_allocMemC %d\n", sizeSafetyArea_allocMemC);
  #endif

}








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
