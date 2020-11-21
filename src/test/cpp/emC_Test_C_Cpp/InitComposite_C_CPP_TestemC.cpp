#include "emc_Test_C_Cpp/InitComposite_C_CPP_TestemC.h"
#include <emC/Base/String_emC.h>



//Set of parameter may be stored in Flash, hence here given as const.
//Usually from another compiling uint.
const Param_s param_test_InitComposite_C_CPP_TestemC = { 2 };

//Static reference to the root of all data, but initially null.
Root* rootData = null;



void test_pitfall(IfcC* ifcC) {
  ifcC->pitfall();
  ifcC->doSomething(6.28f);
}






void test_InitComposite_C_CPP_TestemC () {
  //workB should be created indpendent. 
  WorkB* workB = new WorkB(&param_test_InitComposite_C_CPP_TestemC);
  //Root aggregates WorkB, should be known
  Root* rootData1 = new Root(&param_test_InitComposite_C_CPP_TestemC, workB);
  workB->completeConstruction(rootData1->workA->ifcC);
  //Store rootData in a static reference, for access outside:
  rootData = rootData1;

  IfcC* ifcC = rootData1->workA->ifcC;
  ifcC->doSomething(42.0f);
  MAYBE_UNUSED_emC WorkB* ref1 = dynamic_cast<WorkB*>(ifcC);

  //test_pitfall(ifcC);

  delete (rootData1);
  rootData = null;
  delete workB;
}


Root::Root ( Param_s const* par, WorkB* workB)
: workA(new WorkA(par, workB)), workB(workB)
{ }

Root::~Root(){
  delete this->workA;  
  //do not delete WorkB, it is not an Composition.
}



WorkA::WorkA ( Param_s const* par, WorkB* workB)
: ident("WorkA")
, ifcC(create_WorkC(par))
, workB(workB)
{ }

WorkA::~WorkA() {
  delete this->ifcC;
}


WorkB::WorkB ( Param_s const* par)
  : workC(), ident("WorkB")
{
}

void WorkB::completeConstruction(class IfcC* workC) {
  this->workC = workC;
}


WorkB::~WorkB() {}


IfcC* WorkA::create_WorkC ( Param_s const* par) {
  STACKTRC_ENTRY("WorkA::create_WorkC");
  IfcC* ifcC;
  if(par->use_WorkC ==1) {
    ifcC = new WorkC1(par);
  } else if(par->use_WorkC ==2) {
    ifcC = new WorkC2(par);
  } else {
    ifcC = null;
    THROW_s0(IllegalArgumentException, "Parameter value 'use_WorkC* faulty", par->use_WorkC, 0);
  }
  STACKTRC_RETURN ifcC;
}



WorkC1::WorkC1 ( Param_s const *)
: ident("WorkC1")
{
}


WorkC1::~WorkC1 ( ) {

}


WorkC2::WorkC2 ( Param_s const *)
: ident("WorkC2")
{
}


WorkC2::~WorkC2 ( ) {
}

IfcC::~IfcC ( ) {
}



void WorkC1::doSomething(float val){
  this->f1 = val;
}

void WorkC2::doSomething(float val){
  this->f2 = val;
}

void WorkC1::doOther(float val){
  this->f1 = -val;
}

void WorkC2::doOther(float val){
  this->f2 = -val;
}

void WorkC1::pitfall ( ){
  this->f1 = 5;
}

void WorkC2::pitfall ( ){
  int ix = 0;
  this->array[--ix] +=4;
}

