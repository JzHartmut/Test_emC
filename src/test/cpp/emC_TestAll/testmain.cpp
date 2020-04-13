#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
//#include <org/vishia/emC/Base/test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>
#include <org/vishia/emC/Base/test_ObjectJc/testAll_ObjectJcpp_emCBase.h>
#include <emC_Test_C_Cpp/TestVtblExplicit.h>


#ifdef DEF_TESTALL_emC
int main(int nArgs, char const*const* cmdArgs )
{
  STACKTRC_ENTRY("main");

  testAll_ObjectJcpp_emCBase();
  test_TestVtblExplicit();

  //testAll_Stacktrc_Exc_emCBase();
  testAll_StateM_emCBase();
  STACKTRC_RETURN 0;
}
#endif