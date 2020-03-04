#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
#include <org/vishia/emC/StateM/test_StateM/testEventQueue.h>
#include <org/vishia/emC/StateM/test_StateM/testStateFncall_StateMemCBase.h>


void testAll_StateM_emCBase() {
  #ifndef GCC_TI2000
  testEvQueueSimpleOneThread();
  testEvQueueAddInterrupted();
  #endif
  testStateFncall_StateMemCBase();
}


#ifdef DEF_DEVELOPER_TEST
void main(char** cmdArgs) {
  STACKTRC_ENTRY("main");
  testAll_StateM_emCBase();
  
  //testStateFncall_StateMemCBase();
  //testEvListener(_thCxt);
  //testEvQueueSimpleOneThread();
  //testEvQueueAddInterrupted();
  //testStringCompactor();
  STACKTRC_LEAVE;
}
#endif
