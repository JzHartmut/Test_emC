#include <applstdef_emC.h>
#include <emC_Test_C_Cpp/TestVtblExplicit.h>
//#include <typeinfo>

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


void ImplAvirt::pitfall ( ){
  int ix = 0;
  this->array[--ix] +=4;
}



//For code generation check: should only contains this poor code. But should not be static!
void testVtbl_virtual_i (  IfcCvirt* ifc ) {
  
  
  ifc->doFirst(2.25f);

  //char const* tnameA = typeid(*ifc).name();
  //does not work: type_info typeA = typeid(*ifc);
 
}


void testVtbl_virtual ( ) {
  ImplAvirt* implA = new ImplAvirt();
  testVtbl_virtual_i(implA);
  
  //pitfall disturbs data because of a small error.
  //after them for 32-bit-compilation the faulty virtual operation is called
  //but typeid throws an exception. 
  //Uncomment it to test. 
  //implA->pitfall();
  
  //second call to test.
  testVtbl_virtual_i(implA);

  delete implA;

}
