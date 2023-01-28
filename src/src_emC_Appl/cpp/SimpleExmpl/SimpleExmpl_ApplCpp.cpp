
#include <SimpleExmpl/SimpleExmpl_ApplCpp.h>
#if defined(DEF_cplusplus_emC) && defined(__cplusplus)


//
//C++ constructor of the application class:
//
SimpleNumExmpl::SimpleNumExmpl(ModuleB* modB_arg) 
: modA(2.5f)
, modB(*modB_arg)    //unfortunatelly C++ does not allow using this-> here, hence modB_arg
{ 
  CTOR_ObjectJc(this, this, sizeof(*this), refl_SimpleNumExmpl, 0);  //should construct anyway its ObjectJc base.
  //no more other construction necessary. But look for initialization. 
}



//
//initilization after ctor, before run mode of the application. 
// returns true if succeeded, false if not complete.
//Should be organized in startup phase (main) 
//
bool SimpleNumExmpl::init() {
  bool isInit = true;                  // the order of initialization should not be determined
  isInit &= this->modB.init(&this->modA);        // for exmpl firstly init B
  isInit &= this->modA.init(1.0f );              // then A, but this must not be determined on A (not circular)
  if(isInit) {
    setInitialized_ObjectJc(this);
  }
  return isInit;                       // true only if all is initialized.
}


//
//Step routine for one cycle. Should be organized in especially threads, here for simple test in main.
//
void SimpleNumExmpl::step ( float val ) {        // here the stepping order depends on functionality.
  this->modB.step(val);
  this->modA.step(this->modB.getResult());
}

#endif //def DEF_cplusplus_emC

