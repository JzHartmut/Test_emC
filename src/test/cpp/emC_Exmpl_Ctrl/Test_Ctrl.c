#include "emC_Exmpl_Ctrl/Test_Ctrl.h"


#ifdef DEF_REFLECTION_FULL
  #include "emC_Exmpl_Ctrl/genRefl/Test_Ctrl.crefl"
  #if !defined(__DONOTUSE_INSPECTOR__) && !defined(DEF_REFLECTION_NO)
    #define __Use_Inspector__
    #include <emC/Inspc/Srv/Service_Inspc.h>
  #endif

#elif !defined(DEFINED_refl_Test_Ctrl) && !defined(DEF_REFLECTION_NO)  //may defined in the *.refloffs.c file
  ClassJc const refl_Base_Test_Ctrl = INIZ_ClassJc(refl_Base_Test_Ctrl, "Base_Test_Ctrl");
  ClassJc const refl_Test_Ctrl = INIZsuper_ClassJc(refl_Test_Ctrl, "Test_Ctrl", &refl_Base_Test_Ctrl);
#endif


//This is only to note a debug stop line. 
//you can set a breakpoint for all debug stops here. 
static int dbg(){ return 0; }



#if defined(__cplusplus) && defined(DEF_cplusplus_emC)
Test_Ctrl::Test_Ctrl(ObjectJc* othiz) {
  dbg();
  if(othiz == null) {
    CTOR_ObjectJc(&base.object, this, sizeof(*this), refl_Test_Ctrl, 0);
  } else {
    //check whether the initialization is correct, whereby it is also done in ctor_Test_Ctrl(...)
    ASSERT_emC(othiz == &base.object && CHECKstrict_ObjectJc(othiz, sizeof(*this), refl_Test_Ctrl, 0),
              "C++ ObjectJc initialization error", 0, 0);
  }
  //call the C language constructor
  ctor_Test_Ctrl(&base.object, null);
}


Test_Ctrl::~Test_Ctrl ( ) {
  dbg();
}


bool Test_Ctrl::test_Initialized ( ) {
  return isInitialized_ObjectJc(&this->pid.base.obj) && this->pid.par->f->kP == 1.0f;
}
#endif //DEF_cplusplus_emC











Test_Ctrl_s* ctor_Test_Ctrl(ObjectJc* othiz, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_Test_Ctrl");
  Test_Ctrl_s* thiz = (Test_Ctrl_s*) othiz;
  bool ok = CHECKstrict_ObjectJc(&thiz->base.object, sizeof(*thiz), refl_Test_Ctrl, 0);
  if(ok) {
    float Tstep = 0.000050f;
    //iniz_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz), &refl_Test_Ctrl, 0);
    //the inner ObjectJc based instances should be initialized here:
    CTOR_ObjectJc(&thiz->par.base.obj, &thiz->par, sizeof(thiz->par), refl_Par_PIDf_Ctrl_emC, 0);
    CTOR_ObjectJc(&thiz->pid.base.obj, &thiz->pid, sizeof(thiz->pid), refl_PIDf_Ctrl_emC, 0);
    ctor_Par_PIDf_Ctrl_emC(&thiz->par.base.obj, 0.001f);
    ctor_PIDf_Ctrl_emC(&thiz->pid.base.obj, Tstep);
    float kP = 1.0f;
    float Tn = 0.2f;
    float Td = 0.001f;
    //float Tsd1 = 0.001f;
    //float Tsd2 = 0.0f;
    init_Par_PIDf_Ctrl_emC(&thiz->par, Tstep, 1.2f, kP, Tn, Td, Tstep, false, false);
    init_PIDf_Ctrl_emC(&thiz->pid, &thiz->par);
    //
    thiz->ws = 0.63f;
    thiz->fT1 = 0.001f;
    thiz->fs = 0.0001f;
    thiz->par.kP = 10.0f;
  }
  STACKTRC_RETURN thiz;
}


void init_Test_Ctrl(Test_Ctrl_s* thiz) {
  thiz->base.super.bRun = 1;
}

//
void step_Test_Ctrl(Test_Ctrl_s* thiz) {
  float ds;                                                   //PIDctrl
  float wx = thiz->ws - thiz->s;
  stepY_PIDf_Ctrl_emC(&thiz->pid, wx, wx, &ds);
    
  thiz->sT1 += thiz->fT1 * (ds - thiz->sT1);                  //simple environment simulation.

  thiz->sI += thiz->fs * thiz->sT1;
    
  thiz->s = (float)thiz->sI;
}


void stepSlow_Test_Ctrl(Test_Ctrl_s* thiz) {
  set_Par_PIDf_Ctrl_emC(&thiz->par, thiz->par.kP, thiz->par.Tn, thiz->par.Td, thiz->par.dt, false );
  //param_PIDf_Ctrl_emC(&thiz->pid, parFactors);
}



                                                                //calculate a controlling algorithm
