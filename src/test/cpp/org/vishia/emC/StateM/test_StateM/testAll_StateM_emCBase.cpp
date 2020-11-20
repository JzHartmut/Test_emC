#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
#include <org/vishia/emC/StateM/test_StateM/testEventQueue.h>
#include <org/vishia/emC/StateM/test_StateM/testStateFncall_StateMemCBase.h>


void testAll_StateM_emCBase() {
  testEvQueueSimpleOneThread();
  //testEvQueueAddInterrupted();
  testStateFncall_StateMemCBase();
}


#ifdef DEF_DEVELOPER_TEST
int main(char** cmdArgs) {
  STACKTRC_ENTRY("main");
  testAll_StateM_emCBase();
  
  //testStateFncall_StateMemCBase();
  //testEvListener(_thCxt);
  //testEvQueueSimpleOneThread();
  //testEvQueueAddInterrupted();
  //testStringCompactor();
  STACKTRC_RETURN 0;
}
#endif
