#include "Test_Ctrl.h"

#include <emC/OSAL/os_time.h>

#include <stdio.h>


#ifdef DEF_REFLECTION_FULL
  #include "genRefl/Test_Ctrl.crefl"
  #if !defined(__DONOTUSE_INSPECTOR__) && !defined(DEF_REFLECTION_NO)
    #define __Use_Inspector__
    #include <emC/Inspc/Service_Inspc.h>
  #endif

#elif defined(DEF_REFLECTION_OFFS)
  extern_C ClassJc const reflection_Test_Ctrl;
  #ifdef DEF_TargetProxySharedMem
    #include <emC/InspcTargetSimple/Target2ProxySharedMem_Inspc.h>
    Target2ProxySharedMem_Inspc inspcComm = {0};
  #else
    //other targetProxy, TODO
  #endif
#else 
  ClassJc const refl_Test_Ctrl = INIZ_ClassJc(refl_Test_Ctrl, "Test_Ctrl");
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
  //test_Comm_new();

  ctor_Test_Ctrl(&maindata.base.object);
#ifdef __Use_Inspector__
  ctorO_Inspector_Inspc(&theInspector.base.object, s0_StringJc("UDP:0.0.0.0:60094"), _thCxt);
  start_Inspector_Inspc_F(&theInspector, &maindata.base.object, _thCxt);
#elif defined(DEF_REFLECTION_OFFS)
  #ifdef DEF_TargetProxySharedMem
    ctor_Target2ProxySharedMem_Inspc(&inspcComm, "emC_Exmpl_TestCtrl");
  #endif
#endif //__Use_Inspector__

  TRY{
    calculateInLoop_Test_Ctrl(&maindata);    //to test reflection access via inspector.
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_ExceptionJc(exc, _thCxt);
  } 
  END_TRY;
  #ifdef DEF_TargetProxySharedMem
    dtor_Target2ProxySharedMem_Inspc(&inspcComm);
  #endif
  STACKTRC_LEAVE; return 0;
}
#endif //DEF_MAIN_TestCtrl_emC

Test_Ctrl* ctor_Test_Ctrl(ObjectJc* othiz) {
  Test_Ctrl* thiz = (Test_Ctrl*) othiz;
  iniz_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz), &refl_Test_Ctrl, 0);
  ctor_Par_PID_Ctrl(&thiz->par.base.obj, 0.001f);
  ctor_PID_Ctrl(&thiz->pid.base.obj, 0.001f);
  init_PID_Ctrl(&thiz->pid, &thiz->par);
  //
  thiz->ws = 0.63f;
  thiz->fT1 = 0.001f;
  thiz->fs = 0.0001f;
  thiz->par.kP = 10.0f;
  return thiz;
}



void calculateInLoop_Test_Ctrl(Test_Ctrl* thiz) {
  thiz->bRun = 1;
  int ctSlow = 0;
  while (thiz->bRun) {
    if (--ctSlow < 0) {
      ctSlow = 0x100;
      reparam_PID_Ctrl(&thiz->pid);
    }
    float ds;
    step_PID_Ctrl(&thiz->pid, thiz->ws - thiz->s, &ds);
    
    thiz->sT1 += thiz->fT1 * (ds - thiz->sT1);

    thiz->sI += thiz->fs * thiz->sT1;
    
    thiz->s = (float)thiz->sI;
    #ifdef DEF_TargetProxySharedMem
      step_Target2Proxy_Inspc(&inspcComm.super, thiz, reflection_Test_Ctrl.reflOffs, reflectionOffsetArrays);
    #endif
    os_delayThread(1);
  }

}