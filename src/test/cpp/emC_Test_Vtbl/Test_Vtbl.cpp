#include <compl_adaption.h>

class ClassBase {
  public: virtual void check();
  public: virtual int doit() = 0;
};

void ClassBase::check(){}


class classBaseVtableCheck : public ClassBase {
  virtual int doit(){ return 0; } //only a dummy.
};

const classBaseVtableCheck _classBase;


class MyClassY : public ClassBase {

  public: int doit();
};



int MyClassY::doit()  {
    //algorithm variant Y
  return 'Y';  //0x59
}


typedef struct intPTR20_T {
  intPTR addr[20];
} intPTR20;


void test_Vtbl_CheckFirstOper ( ) {

  //void (ClassBase::*check)() = &ClassBase::check;
  
  MAYBE_UNUSED_emC intPTR20 const* const* addrCheck = C_CAST(intPTR20 const* const*, &_classBase);
  //intPTR* pOp = (intPTR*)&op;
  ClassBase* ref = new MyClassY();
  MAYBE_UNUSED_emC intPTR20** pRef = (intPTR20**) ref;
  //void* vtbl = &ref->doit();
  ref->doit();
}



