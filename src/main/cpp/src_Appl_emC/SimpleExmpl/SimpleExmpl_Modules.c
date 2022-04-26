#include <SimpleExmpl/SimpleExmpl_Modules.h>

//The C file describes only the behavior of this module. No more.

ModuleA_s* ctor_ModuleA(ObjectJc* othiz, float constVal) {
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(ModuleA_s), refl_ModuleA, 0), "faulty instance", 0, 0);
  ModuleA_s* thiz = C_CAST(ModuleA_s*, othiz);  //cast admissible after test
  thiz->cVal = constVal;
  return thiz;
}



bool init_ModuleA(ModuleA_s* thiz, float initVal) {
  if(initVal > 0) {
    thiz->mVal = initVal;
    setInitialized_ObjectJc(&thiz->base.obj);
    return true;
  } else {
    return false;
  }
}


void step_ModuleA(ModuleA_s* thiz, float val) {
  if(val >0) {
    thiz->mVal = val;
  } else {
    //val <=0, the old one is valid.
  }
  thiz->y = thiz->cVal * thiz->mVal;
}




//==============================================================================
//ModuleB



ModuleB_s* ctor_ModuleB(ObjectJc* othiz, float constVal) {
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(ModuleB_s), refl_ModuleB, 0), "faulty type", 0 ,0);
  ModuleB_s* thiz = C_CAST(ModuleB_s*, othiz);  //cast admissible after test
  thiz->cVal = constVal;
  return thiz;
}



bool init_ModuleB(ModuleB_s* thiz, struct ModuleA_T* refA) {
  if(refA !=null && refA->mVal >0) {
    thiz->refA = refA;
    thiz->mVal = refA->mVal;
    setInitialized_ObjectJc(&thiz->base.obj);
    return true;
  } else {
    return false;
  }
}


void step_ModuleB(ModuleB_s* thiz, float val) {
  if(val >0) {
    thiz->mVal = val;
  } else {
    //val <=0, the old one is valid.
  }
  thiz->y = thiz->cVal * thiz->mVal;
}


