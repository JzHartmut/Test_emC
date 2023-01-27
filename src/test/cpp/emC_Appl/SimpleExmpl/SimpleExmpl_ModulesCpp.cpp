#include <SimpleExmpl/SimpleExmpl_Modules.h>

//The C file describes only the behavior of this module. No more.


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
 

ModuleA::ModuleA(float constVal) {
  //for non derived class:                       // should call the CTOR here!
  CTOR_ObjectJc(&this->base.obj, this, sizeof(ModuleA), refl_ModuleA, 0);
  ctor_ModuleA(&this->base.obj, constVal);       // C-lang ctor of data.
}

#endif



//==============================================================================
//ModuleB


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)


ModuleB::ModuleB(float constVal) {
  //for non derived class:                       // should call the CTOR here!
  CTOR_ObjectJc(&this->base.obj, this, sizeof(ModuleB), refl_ModuleB, 0);
  ctor_ModuleB(&this->base.obj, constVal);       // C-lang ctor of data.
}



bool ModuleB::init(ModuleA* refA) { 

  ModuleA_s* refA_s = refA->get_sdata();
  return init_ModuleB(this, refA_s); 
}

#endif  //DEF_cplusplus_emC
