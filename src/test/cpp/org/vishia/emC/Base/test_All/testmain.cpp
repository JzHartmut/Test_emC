#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_StateM/testAll_StateM_emCBase.h>
#include <org/vishia/emC/Base/test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>



void main()
{
  STACKTRC_ENTRY("main");

  testAll_StateM_emCBase();
  testAll_Stacktrc_Exc_emCBase();
  STACKTRC_LEAVE;
}