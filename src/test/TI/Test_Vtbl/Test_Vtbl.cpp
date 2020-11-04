

class ClassBase {
  public: virtual void doit() = 0;
};

class MyClassY : public ClassBase {

  public: virtual void doit() {
    //algorithm variant Y
  }
};


void test_Vtbl ( ) {
  ClassBase* ref = new MyClassY();
  ref->doit();
}



