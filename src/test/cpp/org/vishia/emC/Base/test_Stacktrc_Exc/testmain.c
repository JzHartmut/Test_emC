#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_Stacktrc_Exc/testAllocInThCxt.h>
#include <org/vishia/emC/Base/test_Stacktrc_Exc/testLongJmp.h>



void main()
{
  STACKTRC_ENTRY("main");

  testAllocInThCxt();
  //testLongjmp();
  STACKTRC_LEAVE;
}