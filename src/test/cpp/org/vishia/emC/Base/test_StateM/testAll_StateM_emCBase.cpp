#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_StateM/testAll_StateM_emCBase.h>
#include <org/vishia/emC/Base/test_StateM/testEventQueue.h>


void testAll_StateM_emCBase() {
  testEvQueueSimpleOneThread();
  testEvQueueAddInterrupted();
}


#ifdef DEF_DEVELOPER_TEST
void main(char** cmdArgs) {
  STACKTRC_ENTRY("main");
  testAll_StateM_emCBase();
  //testEvListener(_thCxt);
  //testEvQueueSimpleOneThread();
  //testEvQueueAddInterrupted();
  //testStringCompactor();
  STACKTRC_LEAVE;
}
#endif