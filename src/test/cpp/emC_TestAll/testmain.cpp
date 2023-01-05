#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
//#include <emC_Test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>
#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC_Test_ObjectJc/testAll_ObjectJcpp_emCBase.h>
#include <emC_Test_C_Cpp/TestVtblExplicit.h>
#include <emC_BlockHeapTest/BlockHeapTest_emC.h>
#include <emC_Test_C_Cpp/test_stdArray.h>
#include <emC_Exmpl_Ctrl/Test_Ctrl_Main.h>
#include <emC_Test_Stacktrc_Exc/TestException.h>
#include <emC_Test_Ctrl/test_Ctrl_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testEventQueue.h>
#include <emC_Test_Container/Test_RingBuffer_emC.h>
#include "emC_Test_Threads/Test_ThreadMutexNotify_emC.h"
#include <emC_Test_Math/Test_Math_emC.h>
#include <emC_StringTest/test_StringBase_emC.h>

typedef struct MyStruct_T { float x; int y; } MyStruct;


extern MyStruct myStruct2;

 
static MyStruct myStruct  = { 4.5f, 34};
MyStruct myStruct2 = { 3.5f, 20};



void usePointer(MyStruct** pData, int which) {

  switch(which) {
    case 1: *pData = &myStruct; break;
    case 2: *pData = &myStruct2; break;
    default: *pData = NULL; 
  }

}



void testPointer2Ref(){

  MyStruct* pMyStruct = null;

  usePointer(&pMyStruct, 2);
  pMyStruct->x = 4.6f; 
}



void testPointer(){

  MyStruct const* pMyStruct = &myStruct;

  float a = pMyStruct->x;

  MyStruct * pMyStructAcc = (MyStruct*) pMyStruct;
  pMyStructAcc->x = 4.7f;



}



float procArray(float* array){

  float mid = 0;
  int ix;
  for(ix = 0; ix < 10; ++ix) {
  
    mid += array[ix];
  }

  mid = 0;
  ix = 0;
  while (++ix < 10) {
    mid += *array;
    array +=1; 
  } 


  return mid;
}




void testArray(){

  float farray[10] = { 2.4f, 2.4f, 2.4f, 2.4f, 2.4f, 2.4f, 2.4f, 2.4f, 2.4f, 2.4f };

  procArray(farray);


}



#include <string.h>


#ifdef DEF_TESTALL_emC

int timeShortStepCycle_priv__ = 0;

int main(int nArgs, char const* const cmdArgs[]) //char const*const* cmdArgs )
{



  testArray();

  STACKTRC_ROOT_ENTRY("main");
  TRY {
    //test_Q_rsqrt();
    testAll_ObjectJcpp_emCBase();
    testVtbl_virtual();           //It shows standard using of vtable
    test_TestVtblExplicit();      //It is an example of a special vtable with safety
    test_Exception();

    test_stdArray();

    test_StringBase_emC();
    test_Math_emC();

    test_T1_Ctrl_emC();
    test_Test_Ctrl(20000, 0);
    
    //old? testAll_Stacktrc_Exc_emCBase();
    
    
    testRingBufferSimpleOneThread();
    testRingBufferMultiThread(10);     //delay in CmpAndSwap-Loop
    //testEvQueueSimpleOneThread();
    //testEvQueueAddInterrupted();
  
    //testAll_StateM_emCBase();

    testThreadMutexNotify_emC();
    
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

int timeShortStepCycle_emC ( ) { return timeShortStepCycle_priv__; }

#endif

