#include <applstdef_emC.h>
#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.h>
#include <emC_Test_C_Cpp/TestVtblExplicit.h>
#ifdef USE_BlockHeap_emC
  #include <emC_BlockHeapTest/BlockHeapTest_emC.h>
#endif
#include <emC_Test_Stacktrc_Exc/TestException.h>








#ifdef DEF_TESTBasics_emC
int main(int nArgs, char const*const* cmdArgs )
{
  STACKTRC_ROOT_ENTRY("main");
  TRY {
    //test_ObjectJc();
    testAll_ObjectJcpp_emCBase();
    testVtbl_virtual();           //It shows standard using of vtable
    test_TestVtblExplicit();      //It is an example of a special vtable with safety
    test_Exception();
    //testAll_Stacktrc_Exc_emCBase();
    //
    //test BlockHeap at last because all other tests would use the BlockHeap
    #ifdef USE_BlockHeap_emC
      testBlockHeap_emC();
    #endif
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_Exception_emC(exc, _thCxt);
  }
  END_TRY
  STACKTRC_RETURN 0;
}
#endif
