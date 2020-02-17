#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_StateM/testEventQueue.h>
//#include <iostream>

void test1(){
//  cout<<"xxx";
}

void main(char** cmdArgs) {
  STACKTRC_ENTRY("main");
  //testEvListener(_thCxt);
  //testEvQueueSimpleOneThread();
  testEvQueueAddInterrupted();
  //testStringCompactor();
  STACKTRC_LEAVE;
}
