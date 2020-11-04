#include "TestVtblExplicit.h"
#include <emC/Base/String_emC.h>
#include <emC/Test/testAssert.h>
#include <string.h>

//#include <typeinfo>

IfcExpl::IfcExpl ( Vtbl_IfcExpl_s const* const vtbl)
: vtbl_IfcExpl(vtbl)
{}





/**********************************************************************/
/*Implementation for the explicit vtbl wraps the C++ operations in C  */

static void doFirst_ImplA ( IfcExpl* thizi, float val) {
  ImplA* thiz = static_cast<ImplA*>(thizi);
  thiz->doFirst(val);  //calls routine from ImplementorA
}

static void doOther_ImplA ( IfcExpl* thizi, float val) {
  (static_cast<ImplA*>(thizi))->doOther(val);  //calls routine from ImplementorA
}

static void doAny_ImplA ( IfcExpl* thizi, int val1, int val2) {
  (static_cast<ImplA*>(thizi))->doAny(val1, val2);  //calls routine from ImplementorA
}

static char const* doAnywhat ( ImplA* thizi) {
  return "it is ImplA";
}

//The definition of the vtbl for ImplA, written to const memory area (!)
static Vtbl_ImplA_s const vtbl_ImplA_Def =
{ sign_Vtbl_ImplA
, doFirst_ImplA
, doAnywhat
, { sign_Vtbl_IfcExpl
  , doFirst_ImplA
  , doOther_ImplA
  , doAny_ImplA
  //only possible to set operations of IfcExpl here. 
    //for that it would be necessary that IfcExpl knows all the possible implementor classes
    //that is against the basicly principle of modularity.
  , &IfcExpl::doit_dontUse
    //syntax error; , (&ImplementorA::doit)
  }
};


//not usefull implementation of function pointer in C++ (only for experience)
void IfcExpl::doit_dontUse(float val) {
  //the implementation in the base interface is not able to use
  //without knowledge of implementors. 
  //(It is the only one possibility of C++ function pointer:
  // C++ function pointer are able to use to store function addresses of the same class only,
  // not for inherited classes. )
}






/***************************************************************************************/
/* The implememtations of class ImplA */





ImplA::ImplA ( )
  : IfcExpl(&vtbl_ImplA_Def.IfcExpl)
  , vtbl_ImplA(&vtbl_ImplA_Def)
{ }


ImplA::ImplA ( Vtbl_ImplA_s const* vtblA)
  : IfcExpl(&vtblA->IfcExpl)
  , vtbl_ImplA(vtblA)
{ }


void ImplA::doFirst ( float val){ 
  f = 2.0f * val;
}


void ImplA::doOther ( float val){ 
  f = -3.5f * val;
}


void ImplA::doAny ( int val1, int val2 ){ 
  this->i1 = val1; 
  this->i2 = val1; 
  this->f = (float)(val1 + val2); 
}




/**********************************************************************/
/*Implementation for the explicit vtbl for ImplB wraps the C++ operations in C  */

static void doFirst_ImplB ( IfcExpl* thizi, float val) {
  (static_cast<ImplB*>(thizi))->doFirst(val);  //calls routine from ImplB
}

static char const* doAnywhat_ImplB ( ImplA* thiz) {
  return (static_cast<ImplB*>(thiz))->doAnywhat();  //calls routine from ImplementorA
}



//The definition of the vtbl for ImplA, written to const memory area (!)
static Vtbl_ImplB_s const vtbl_ImplB_Def =
{ sign_Vtbl_ImplB
, doAnywhat_ImplB
, { sign_Vtbl_ImplA
  , doFirst_ImplB
  , doAnywhat_ImplB
  , { sign_Vtbl_IfcExpl
    , doFirst_ImplA
    , doOther_ImplA
    , doAny_ImplA
    //only possible to set operations of IfcExpl here. 
    //for that it would be necessary that IfcExpl knows all the possible implementor classes
    //that is against the basicly principle of modularity.
    , &IfcExpl::doit_dontUse
    //syntax error; , (&ImplementorA::doit)
  } }
};


ImplB::ImplB ( )
  : ImplA(&vtbl_ImplB_Def.ImplA)
  , vtbl_ImplB(&vtbl_ImplB_Def)
{ }




void ImplB::doFirst ( float val){ 
  f = 2.5f * val;
}

char const* ImplB::doAnywhat ( ) {
  return "it is ImplB";
}


void test_TestVtblExplicit ( ) {
  TEST_START("TestVtblExplicit");
  ImplA* implA = new ImplA();
  //ImplA* implA1 = new ImplA1();
  ImplB* implB = new ImplB();

  IfcExpl* ifcA = implA;  //automatic static cast
  //IfcExpl* ifcA1 = implA1;  //automatic static cast
  IfcExpl* ifcB = implB;  //automatic static cast

  //MAYBE_UNUSED_emC char const* tnameA = typeid(*ifcA).name();


  //vtbl as stack-local variable, 
  //secured because stack area should be secure anycase
  Vtbl_IfcExpl_s const* const vtblA = ifcA->vtbl_IfcExpl;
  if(CHECK_ASSERT_emC(strcmp(vtblA->sign, sign_Vtbl_IfcExpl)==0, "check implA", 0,0)) {
    vtblA->doFirst(ifcA, 2.25f);
    //... some more usage of vtblA in this thread
  }
  //This is just as well unsafe as C++ virtual call:
  ifcB->vtbl_IfcExpl->doFirst(ifcB, 2.25f);
  float fA = implA->getVal();
  float fB = implB->getVal();
  TEST_TRUE(fA == 4.5f && fB == 4.5f, "correct results of call virtual operation via FunctionPointer");

  TEST_END;


}

