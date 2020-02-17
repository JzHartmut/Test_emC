#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_StateM/testEventQueue.h>




void main(char** cmdArgs) {
  STACKTRC_ENTRY("main");
  //testEvListener(_thCxt);
  testEvQueueSimpleOneThread();
  //testStringCompactor();
  STACKTRC_LEAVE;
}
