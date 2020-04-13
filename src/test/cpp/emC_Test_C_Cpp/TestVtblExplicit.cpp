#include "TestVtblExplicit.h"
#include <emC/Base/String_emC.h>
#include <emC/Test/testAssert.h>

Base_ifc::Base_ifc ( Vtbl_Base_ifc_s const* const vtbl)
: vtbl(vtbl)
{}


static void doit_ImplementorA ( Base_ifc* thizi, float val) {
  ImplementorA* thiz = static_cast<ImplementorA*>(thizi);
  thiz->doit(val);  //calls routine from ImplementorA
}

static void doit_ImplementorB ( Base_ifc* thizi, float val) {
  ImplementorB* thiz = static_cast<ImplementorB*>(thizi);
  thiz->doit(val);  //calls routine from ImplementorA
}

static Vtbl_Base_ifc_s const vtbl_ImplementorA_Base_ifc =
{ sign_Vtbl_Base_ifc
, doit_ImplementorA
};

ImplementorA::ImplementorA ( )
: Base_ifc(&vtbl_ImplementorA_Base_ifc)
{ }


void ImplementorA::doit ( float val){ 
  f = val;
}

void ImplementorB::doit ( float val){ 
  f = -2.0f * val;
}


static Vtbl_Base_ifc_s const vtbl_ImplementorB_Base_ifc =
{ sign_Vtbl_Base_ifc
, doit_ImplementorB
};



ImplementorB::ImplementorB ( )
: Base_ifc(&vtbl_ImplementorB_Base_ifc)
{

}

void test_TestVtblExplicit ( ) {
  TEST("TestVtblExplicit");
  ImplementorA* implA = new ImplementorA();
  ImplementorB* implB = new ImplementorB();

  Base_ifc* ifcA = implA;  //automatic static cast
  Base_ifc* ifcB = implB;  //automatic static cast

  //vtbl as stack-local variable, 
  //secured because stack area should be secure anycase
  Vtbl_Base_ifc_s const* const vtblA = ifcA->vtbl;
  if(ASSERT_emC(strcmp(vtblA->sign, sign_Vtbl_Base_ifc)==0, "check implA", 0,0)) {
    vtblA->doit(ifcA, 2.25f);
    //... some more usage of vtblA in this thread
  }
  //This is just as well unsafe as C++ virtual call:
  ifcB->vtbl->doit(ifcB, 2.25f);
  float fA = implA->getVal();
  float fB = implB->getVal();
  EXPECT_TRUE(fA == 2.25f && fB == -4.5f) << "faulty Results";




}

