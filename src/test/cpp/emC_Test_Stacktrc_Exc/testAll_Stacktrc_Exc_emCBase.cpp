#include <applstdef_emC.h>
#include <emC_Test_Stacktrc_Exc/testAllocInThCxt.h>
#include <emC_Test_Stacktrc_Exc/testLongJmp.h>
#include <emC_Test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>

void testAll_Stacktrc_Exc_emCBase() {
  testAllocInThCxt();
  //testLongjmp();  //This does not work in VS15, todo test anywhere other.
}


