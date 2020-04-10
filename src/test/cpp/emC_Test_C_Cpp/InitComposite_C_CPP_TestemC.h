#ifndef HEADERGUARD_InitComposite_C_CPP_TestemC
#define HEADERGUARD_InitComposite_C_CPP_TestemC
#include <applstdef_emC.h>

typedef struct Param_T {
  /**Set to 1 or 2 to specify which detail functionality should be used. */
  int32 use_WorkC;
} Param_s;


extern_C Param_s const param_test_InitComposite_C_CPP_TestemC;

extern_C void test_InitComposite_C_CPP_TestemC ( );

#ifdef __cplusplus

class IfcC {
  public: virtual void pitfall ( )=0;
  public: virtual void doSomething ( float arg)=0;
  public: virtual void doOther ( float arg)=0;
  public: virtual ~IfcC () =0;

};



class Root {
  public: class WorkA const* const workA;
  public: class WorkB const* const workB;

  public: Root ( Param_s const* par, WorkB* workB );
  public: ~Root ();
};


class WorkA {
  public: char const* const ident;       //Data-Element
  public: class IfcC* const ifcC;  //Composition
  private: class WorkB* const workB;     //Aggregation

  public: WorkA ( Param_s const* param, WorkB* workB );
  private: IfcC* create_WorkC ( Param_s const* par );
  public: ~WorkA ();
};


class WorkB {
  class IfcC* workC;
  public: WorkB ( Param_s const* param);
  public: char const* const ident;
  
  public: void completeConstruction(class IfcC* workC);
  public: ~WorkB ();
};


class WorkC1 : public IfcC {
  public: WorkC1 ( Param_s const* par );
  public: char const* const ident;
  private: float f1;
  public: void doSomething(float val);
  public: void pitfall (  );
  public: void doOther(float val);

  public: ~WorkC1 ();
};


class WorkC2 : public IfcC {
  public: WorkC2 ( Param_s const* par );
  
  public: int array[2];
  public: char const* const ident;
  private: float f2, f3;

  public: void doSomething ( float val );
  public: void doOther(float val);
  public: void pitfall (  );
  public: ~WorkC2 ();
};

#endif //__cplusplus

#endif //HEADERGUARD_InitComposite_C_CPP_TestemC
