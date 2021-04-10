#include "Test_Ctrl_Main.h"
#include "Test_Ctrl.h"
#include <emC_Test_Ctrl/test_Ctrl_emC.h>
#include <emC_Test_Ctrl/test_OrthOsc.h>
#include <emC_Test_Math/Test_Math_emC.h>
#include <emC/Test/testAssert.h>

#include <stdio.h>

#if defined(__cplusplus) && defined(DEF_cplusplus_emC)
  #define DEF_CPP_Test_Ctrl_Main
#endif

#include <emC/OSAL/os_time.h>

//This part of the source is only compiled if this is the main application. Set in applstdef_emC.h or as compiler DEF argument.

#ifdef DEF_CPP_Test_Ctrl_Main
  //Creates a static instance for the whole application in C++:
  //Note: The static instance for C is not used!
  //Note: The constructor of the class is executed before main() entry is reached. 
  //Set a breakpoint in the constructor to step it, breakpoint in main entry is not sufficient. 
  //The argument of the instance is the ctor argument. Because the ObjectJc part should not initialized here,
  //  (possible with CTOR_ObjectJc(...), the argument is null, the ctor does the instance initialization.  
  Test_Ctrl_Main maindataCpp_TestCtrl(null);
#else 
  //Creates a static instance for the whole application in C:
  //Hint: INIZ_Test_Ctrl is a define which follows with { { ....} ...} the typedef of Mydata.
  Test_Ctrl_s maindata_TestCtrl = INIZ_Test_Ctrl(maindata_TestCtrl, 0);
#endif


#if defined(DEF_REFLECTION_OFFS)
  //Always use the targetProxy.
  #define DEF_TargetProxySharedMem
  #ifdef DEF_TargetProxySharedMem
    #include <emC/InspcTargetSimple/Target2ProxySharedMem_Inspc.h>
    Target2ProxySharedMem_Inspc inspcComm = {0};
  #else
    //other targetProxy, TODO
  #endif
#elif defined(XXX_DEF_REFLECTION_FULL)
  //The inspector service, it is a part of the runtime environment.
  Inspector_Inspc_s theInspector = { 0 };
#endif //__Use_Inspector__



/**Calculates y = a*b; with 1 ms delay in the main thread.
 * It ends if bRun is set to 0 via external reflection access.
 * @arg maxSteps 0 then runs till bRun=0 from Inspector, >0 then runs this number of steps. 
 */
//extern_CCpp 
extern_C void calculateInLoop_Test_Ctrl ( uint maxSteps, uint stepusec);




#ifdef DEF_MAIN_TestCtrl_emC
int main(int nArgs, char** sArgs) {
  STACKTRC_ROOT_ENTRY("main");
  #ifdef DEF_Inspector_FULL
  ctorO_Inspector_Inspc(&theInspector.base.object, s0_StringJc("UDP:0.0.0.0:60094"), _thCxt);
  start_Inspector_Inspc_F(&theInspector, &maindata.base.object, _thCxt);
  #elif defined(DEF_REFLECTION_OFFS)
  #ifdef DEF_TargetProxySharedMem
  ctor_Target2ProxySharedMem_Inspc(&inspcComm, "emC_Exmpl_TestCtrl");
  #endif
  #endif //__Use_Inspector__
  ////test_Comm_new();
  //test_Test_Ctrl(0, 100);  //100 us sleep for ctrl-loop
  //testSimple_T1_Ctrl_emC();
  test_Math_emC();
  //test2_OrthOsc();
  //test_OrthOsc16();
  #ifdef DEF_TargetProxySharedMem
  dtor_Target2ProxySharedMem_Inspc(&inspcComm);
  #endif
  STACKTRC_LEAVE; return 0;
}
#endif //DEF_MAIN_TestCtrl_emC




void test_Test_Ctrl(uint maxStep, uint stepusec) {
  STACKTRC_ENTRY("test_Test_Ctrl");
  TEST_START("test_Test_Ctrl");

  //Test_Ctrl_s* thiz = &maindata_TestCtrl;
  ObjectJc const* dataObj;
  #ifdef DEF_CPP_Test_Ctrl_Main
    //The ctor of the data instance is complete already with static ctor.
    maindataCpp_TestCtrl.init();       //but init is done in start of runtime
    dataObj = maindataCpp_TestCtrl.object();
    //C++: because of protected/private a check of internallies nees an own operation:
    TEST_TRUE(maindataCpp_TestCtrl.test_Initialized(), "controller initialized");
  #else
    ctor_Test_Ctrl(&maindata_TestCtrl.base.object, _thCxt);  //initializes the C instance, not used for C++
    init_Test_Ctrl(&maindata_TestCtrl);
    dataObj = &maindata_TestCtrl.base.object;
    //C-struct-solution: access to any data, which are protected/private in C++
    Test_Ctrl_s* thiz = &maindata_TestCtrl;
    TEST_TRUE(isInitialized_ObjectJc(&thiz->pid.base.obj) && thiz->pid.f.kP == 1.0f, "controller initialized");
  #endif

  #if defined(DEF_ObjectJc_REFLREF) && !defined(DEF_REFLECTION_OFFS)  
    //else: Base class cannot be checked.
    //TODO the reflection generator should regard the base class, yet not implemented. Hence do not test.
    //check whether the base class is recognize via reflection, secondary topic here.
    CALLINE; bool bOkBase = INSTANCEOF_ObjectJc(dataObj, refl_Base_Test_Ctrl);
    TEST_TRUE(bOkBase, "base class of Test_Ctrl");
  #endif

  TRY{
    calculateInLoop_Test_Ctrl(maxStep, stepusec);    //to test reflection access via inspector.
    float s;
    #ifdef DEF_CPP_Test_Ctrl_Main
      s = maindataCpp_TestCtrl.get_s();
    #else
      s = maindata_TestCtrl.s;
    #endif
    TEST_TRUE(s > 0.6f, "controller has endvalue");
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_Exception_emC(exc, _thCxt);
  } 
  FINALLY {
    //maindata_TestCtrl.base.super.bRun = 0;  //because loop broken
  }
  END_TRY;
  TEST_END;
  STACKTRC_LEAVE;

}







void calculateInLoop_Test_Ctrl(uint maxSteps, uint stepusec) {
  int ctSlow = 0;
  uint ctStep = maxSteps == 0 ? 1 : maxSteps;
  void* rootObj;
  #ifdef DEF_CPP_Test_Ctrl_Main
    Test_Ctrl* dataCpp = &maindataCpp_TestCtrl;
    rootObj = dataCpp;
  #else
    Test_Ctrl_s* thiz = &maindata_TestCtrl;
    rootObj = thiz;
  #endif
  bool bCont = true;
  while (ctStep >0 && bCont) {                  //run given maxSteps
    if(maxSteps >0) { ctStep -=1; }  //to end the loop 
    if (--ctSlow < 0) {
      ctSlow = 0x100;                                           //Reduced step time: 1/256
      #ifdef DEF_CPP_Test_Ctrl_Main
        dataCpp->stepSlow();
      #else
        stepSlow_Test_Ctrl(&maindata_TestCtrl);
      #endif
    }
    #ifdef DEF_CPP_Test_Ctrl_Main
      dataCpp->step();
      bCont = dataCpp->run();
    #else
      step_Test_Ctrl(&maindata_TestCtrl);
      bCont = thiz->base.super.bRun !=0;
    #endif
    #if defined(DEF_TargetProxySharedMem) && defined(DEF_REFLECTION_OFFS) && defined(ADDR_HAS32BIT)
    //                                                          //allow access to data using inspector.
      step_Target2Proxy_Inspc(&inspcComm.super, rootObj, refl_Test_Ctrl.reflOffs, reflectionOffsetArrays);
    #endif
    if(stepusec >0) {  //only if longer realtime, else fast as possible
      sleepMicroSec_Time_emC(stepusec);
    }
  }

}


#ifdef DEF_CPP_Test_Ctrl_Main
Test_Ctrl_Main::Test_Ctrl_Main ( ObjectJc* othiz ) 
: Test_Ctrl(othiz)
{

}
#endif
