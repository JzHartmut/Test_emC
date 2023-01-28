#include <SimpleExmpl/SimpleExmpl_Appl.h>
#ifndef DEF_NO_StringUSAGE 
  #include <emC/Base/StringNum_emC.h>
#endif

SimpleNumExmpl_s* ctor_SimpleNumExmpl ( ObjectJc* othiz, ModuleB_s* modB) { 
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(SimpleNumExmpl_s), refl_SimpleNumExmpl, 0), "faulty type", 0, 0);
  SimpleNumExmpl_s* thiz = C_CAST(SimpleNumExmpl_s*, othiz);
  ctor_ModuleA(&thiz->modA.base.obj, 2.5f);
  thiz->modB = modB;
  return thiz;
}



bool init_SimpleNumExmpl ( SimpleNumExmpl_s* thiz) {
  bool isInit = true;                  // the order of initialization should not be determined
  isInit &= init_ModuleB(thiz->modB, &thiz->modA);        // for exmpl firstly init B
  isInit &= init_ModuleA(&thiz->modA, 1.0f );              // then A, but this must not be determined on A (not circular)
  if(isInit) {
    setInitialized_ObjectJc(&thiz->base.obj);
  }
  return isInit;                       // true only if all is initialized.
}



void step_SimpleNumExmpl ( SimpleNumExmpl_s* thiz, float val ) {          // here the stepping order depends on functionality.
  step_ModuleB(thiz->modB, val);
  step_ModuleA(&thiz->modA, getResult_ModuleB(thiz->modB));
  #ifndef DEF_NO_StringUSAGE 
    int ixBuffer = toString_float_emC(thiz->bufferResult, sizeof(thiz->bufferResult)-1, thiz->modA.y, "% 3.2f"); 
    thiz->bufferResult[ixBuffer] = 0;   //0-termination for printf.
  #endif  
}

