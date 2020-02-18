#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_Stacktrc_Exc/testAllocInThCxt.h>
#include <org/vishia/emC/Base/test_Stacktrc_Exc/testLongJmp.h>
#include <org/vishia/emC/Base/test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>

void testAll_Stacktrc_Exc_emCBase() {
  testAllocInThCxt();
  //testLongjmp();  //This does not work in VS15, todo test anywhere other.
}


#ifdef DEF_DEVELOPER_TEST
void main()
{
  STACKTRC_ENTRY("main");

  testAllocInThCxt();
  //testLongjmp();
  STACKTRC_LEAVE;
}
#endif