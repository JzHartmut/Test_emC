#include "emC_Exmpl_Ctrl/Test_Ctrl.h"

#include <emC/OSAL/os_time.h>
#include <emC/Test/testAssert.h>

#include <stdio.h>


#ifdef DEF_REFLECTION_FULL
  #include "genRefl/Test_Ctrl.crefl"
  #if !defined(__DONOTUSE_INSPECTOR__) && !defined(DEF_REFLECTION_NO)
    #define __Use_Inspector__
    #include <emC/Inspc/Srv/Service_Inspc.h>
  #endif

#elif !defined(DEFINED_refl_Test_Ctrl) && !defined(DEF_REFLECTION_NO)  //may defined in the *.refloffs.c file
  ClassJc const refl_Base_Test_Ctrl = INIZ_ClassJc(refl_Base_Test_Ctrl, "Base_Test_Ctrl");
  ClassJc const refl_Test_Ctrl = INIZsuper_ClassJc(refl_Test_Ctrl, "Test_Ctrl", &refl_Base_Test_Ctrl);
#endif


#if defined(DEF_REFLECTION_OFFS)
  #ifdef DEF_TargetProxySharedMem
    #include <emC/InspcTargetSimple/Target2ProxySharedMem_Inspc.h>
    Target2ProxySharedMem_Inspc inspcComm = {0};
  #else
    //other targetProxy, TODO
  #endif
#endif


//Hint: CONST_MyData is a define which follows with { { ....} ...} the typedef of Mydata.
//The using of the macor of user level should present only the important things.
  //Test_Ctrl maindata = { { { ((0)<<16) + (((int16_t)(intptr_t)(&reflection_Test_Ctrl)) /*& 0xffff*/) }}};
  Test_Ctrl maindata = INIZ_Test_Ctrl(maindata, 0);


#ifdef __Use_Inspector__
//The inspector service, it is a part of the runtime environment.
Inspector_Inspc_s theInspector = { 0 };
#endif //__Use_Inspector__



//int test_Comm_new();
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
  //test_Comm_new();
  test_Test_Ctrl(0, 100);  //100 us sleep for ctrl-loop
  #ifdef DEF_TargetProxySharedMem
  dtor_Target2ProxySharedMem_Inspc(&inspcComm);
  #endif
  STACKTRC_LEAVE; return 0;
}
#endif //DEF_MAIN_TestCtrl_emC



void test_Test_Ctrl(uint maxStep, uint stepusec) {
  STACKTRC_ENTRY("test_Test_Ctrl");
  TEST_START("test_Test_Ctrl");

  Test_Ctrl* thiz = &maindata;
  ctor_Test_Ctrl(&thiz->base.object, _thCxt);
  #ifdef DEF_ObjectJc_REFLREF  //else: Base class cannot be checked.
    CALLINE; bool bOkBase = INSTANCEOF_ObjectJc(&thiz->base.object, refl_Base_Test_Ctrl);
    TEST_TRUE(bOkBase, "base class of Test_Ctrl");
  #endif
  TEST_TRUE(isInitialized_ObjectJc(&thiz->pid.base.obj) && thiz->pid.f.kP == 1.0f, "controller initialized");
  TRY{
    calculateInLoop_Test_Ctrl(&maindata, maxStep, stepusec);    //to test reflection access via inspector.
    TEST_TRUE(thiz->s > 0.6f, "controller has endvalue");
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_ExceptionJc(exc, _thCxt);
  } 
  FINALLY {
    maindata.base.super.bRun = 0;  //because loop broken
  }
  END_TRY;
  TEST_END;
  STACKTRC_LEAVE;

}










Test_Ctrl* ctor_Test_Ctrl(ObjectJc* othiz, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_Test_Ctrl");
  Test_Ctrl* thiz = (Test_Ctrl*) othiz;
  bool ok = CHECKstrict_ObjectJc(&thiz->base.object, sizeof(*thiz), refl_Test_Ctrl, 0);
  if(ok) {
    //iniz_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz), &refl_Test_Ctrl, 0);
    //the inner ObjectJc based instances should be initialized here:
    CTOR_ObjectJc(&thiz->par.base.obj, &thiz->par, sizeof(thiz->par), refl_Par_PIDf_Ctrl_emC, 0);
    CTOR_ObjectJc(&thiz->pid.base.obj, &thiz->pid, sizeof(thiz->pid), refl_PIDf_Ctrl_emC, 0);
    ctor_Par_PIDf_Ctrl_emC(&thiz->par.base.obj, 0.001f);
    ctor_PIDf_Ctrl_emC(&thiz->pid.base.obj, 0.001f);
    float kP = 1.0f;
    float Tn = 0.01f;
    float Td = 0.001f;
    float Tsd = 0.001f;
    ParFactors_PIDf_Ctrl_emC_s* parFactors = null;
    init_Par_PIDf_Ctrl_emC(&thiz->par, 0.001f, 1.2f, kP, Tn, Td, Tsd, &parFactors);
    init_PIDf_Ctrl_emC(&thiz->pid, parFactors);
    //
    thiz->ws = 0.63f;
    thiz->fT1 = 0.001f;
    thiz->fs = 0.0001f;
    thiz->par.kP = 10.0f;
  }
  STACKTRC_RETURN thiz;
}


                                                                //calculate a controlling algorithm
void calculateInLoop_Test_Ctrl(Test_Ctrl* thiz, uint maxSteps, uint stepusec) {
  thiz->base.super.bRun = 1;
  int ctSlow = 0;
  uint ctStep = maxSteps == 0 ? 1 : maxSteps;
  ParFactors_PIDf_Ctrl_emC_s* parFactors = null;
  while (thiz->base.super.bRun && ctStep >0) {                  //run given maxSteps
    if(maxSteps >0) { ctStep -=1; }  //to end the loop 
    if (--ctSlow < 0) {
      ctSlow = 0x100;                                           //Reduced step time: 1/256
      set_Par_PIDf_Ctrl_emC(&thiz->par, thiz->par.kP, thiz->par.Tn, thiz->par.Td, thiz->par.T1d, &parFactors );
      param_PIDf_Ctrl_emC(&thiz->pid, parFactors);
    }
    float ds;                                                   //PIDctrl
    step_PIDf_Ctrl_emC(&thiz->pid, thiz->ws - thiz->s, &ds);
    
    thiz->sT1 += thiz->fT1 * (ds - thiz->sT1);                  //simple environment simulation.

    thiz->sI += thiz->fs * thiz->sT1;
    
    thiz->s = (float)thiz->sI;
    #ifdef DEF_TargetProxySharedMem                             //allow access to data using inspector.
      step_Target2Proxy_Inspc(&inspcComm.super, thiz, reflection_Test_Ctrl.reflOffs, reflectionOffsetArrays);
    #endif
    if(stepusec >0) {  //only if longer realtime, else fast as possible
      sleepMicroSec_Time_emC(stepusec);
    }
  }

}
