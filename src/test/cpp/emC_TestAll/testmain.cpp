#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
//#include <emC_Test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>
#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.h>
#include <emC_Test_C_Cpp/TestVtblExplicit.h>
#include <emC_BlockHeapTest/BlockHeapTest_emC.h>
#include <emC_Test_C_Cpp/test_stdArray.h>
#include <emC_Exmpl_Ctrl/Test_Ctrl.h>
#include <emC_Test_Stacktrc_Exc/TestException.h>
#include <emC_Test_Ctrl/Test_Ctrl_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testEventQueue.h>
#include <emC_Test_Container/Test_RingBuffer_emC.h>
#include <stdio.h>








#ifdef DEF_TESTALL_emC
int main(int nArgs, char const*const* cmdArgs )
{
  STACKTRC_ROOT_ENTRY("main");
  TRY {
    outTestConditions();
    testRingBufferSimpleOneThread();
    testAll_ObjectJcpp_emCBase();
    testVtbl_virtual();           //It shows standard using of vtable
    test_TestVtblExplicit();      //It is an example of a special vtable with safety
    test_Exception();

    test_stdArray();

    //test_T1_Ctrl_emC();
    //test_Test_Ctrl(20000);
    
    //old? testAll_Stacktrc_Exc_emCBase();
    
    
    testEvQueueSimpleOneThread();
    //testEvQueueAddInterrupted();
  
    //testAll_StateM_emCBase();
    
    //
    //test BlockHeap at last because all other tests would use the BlockHeap
    #ifdef USE_BlockHeap_emC
      testBlockHeap_emC();
    #endif
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_ExceptionJc(exc, _thCxt);
  }
  END_TRY
  STACKTRC_RETURN 0;
}
#endif
