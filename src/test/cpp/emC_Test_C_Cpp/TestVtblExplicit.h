#ifndef HEADERGUARD_TestVtblExplicit
#define HEADERGUARD_TestVtblExplicit


typedef void Oper_doit_Base_ifc(class Base_ifc* thiz, float val);

#define sign_Vtbl_Base_ifc "sign_Vtbl_Base_ifc_MyAppl"

typedef struct Vtbl_Base_ifc_T {
  char const* sign;
  Oper_doit_Base_ifc* doit;
} Vtbl_Base_ifc_s;



class Base_ifc {
  public: Vtbl_Base_ifc_s const* const vtbl;
  public: Base_ifc ( Vtbl_Base_ifc_s const* const);
};


class DataClass {
  protected: float f;
};

class ImplementorA : public Base_ifc, protected DataClass {
  public: ImplementorA ( );
  public: void doit ( float val);
  public: float getVal ( ){ return this->f; } 
};


class ImplementorB : public Base_ifc, protected DataClass{
  public: ImplementorB ( );
  public: void doit ( float val);
  public: float getVal ( ){ return this->f; } 
};




void test_TestVtblExplicit ( );


#endif //HEADERGUARD_TestVtblExplicit
