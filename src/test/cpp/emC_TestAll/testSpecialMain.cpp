#include <applstdef_emC.h>
#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC_StringTest/test_StringSpecials_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
//#include <emC_Test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>
#include <emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.h>

#include <emC_Test_C_Cpp/InitComposite_C_CPP_TestemC.h>
#include <emC_Test_C_Cpp/test_Cpp_Tpl.h>
#include <emC_BlockHeapTest/BlockHeapTest_emC.h>

#include <emC_Test_C_Cpp/TestVtblExplicit.h>
#include <emC_Test_C_Cpp/test_stdArray.h>
#include <emC_Exmpl_Ctrl/Test_Ctrl.h>
#include <emC_Test_Ctrl/test_Ctrl_emC.h>
#include <emC_Test_Ctrl/test_OrthOsc.h>

#include "emC_Test_Threads/Test_ThreadMutexNotify_emC.h"
#include <emC_Test_Stacktrc_Exc/TestException.h>
#include <emC_Test_Ipc/test_Ipc.h>

#ifdef DEF_MAIN_emC_TestAll_testSpecialMain

int timeShortStepCycle_priv__ = 0;

int main(int nArgs, char const*const* cmdArgs )
{
  STACKTRC_ROOT_ENTRY("main");
  //test_Ipc();

  //test2_OrthOsc();
  //test_Vtbl_CheckFirstOper();
  //test_Exception();
  //test_stdArray();
  //test_Alloc_ObjectJc();
  //test_ObjectJc();
  //testString_emC();
  //testStringSpecial_emC();
  //testBlockHeap_emC();

  //testVtbl_virtual();
  //test_TestVtblExplicit();
  //test_InitComposite_C_CPP_TestemC();
  //test_Test_Ctrl(20000);
  test_PIDf_Ctrl_emC();
  //testSimple_T1_Ctrl_emC();   //to see how does it works.
  //test_OrthBandpassF_fast();
  //test_OrthBandpass32();
  //test_T1_Ctrl_emC();
  //testAll_ObjectJcpp_emCBase();
  //test_MinTpl();
  //testAll_Stacktrc_Exc_emCBase();
  //testAll_StateM_emCBase();
  //testThreadMutexNotify_emC();
  STACKTRC_RETURN 0;
}

int timeShortStepCycle_emC ( ) { return timeShortStepCycle_priv__; }

#endif
