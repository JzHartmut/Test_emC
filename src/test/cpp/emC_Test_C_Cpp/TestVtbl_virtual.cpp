#include <emC_Test_C_Cpp/TestVtblExplicit.h>

void ImplAvirt::doFirst ( float val ) { this->f1 = 2.0f * val; }

void ImplAvirt::doOther ( float val ) { this->f1 = -3.5f * val; }

void ImplAvirt::doAny ( int val1, int val2 )  { 
  this->i1 = val1; 
  this->i2 = val1; 
  this->f1 = (float)(val1 + val2); 
}

char const* ImplAvirt::doAnywhat(){ return "it is ImplA"; }

void ImplBvirt::doFirst ( float val ) { this->f1 = 2.5f * val; }

char const* ImplBvirt::doAnywhat(){ return "it is ImplB"; }

void testVtbl_virtual (  IfcCvirt* ifc ) {
  ifc->doFirst(2.25f);
}

