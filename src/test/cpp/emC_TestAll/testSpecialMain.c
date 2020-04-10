#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/test_StateM/testAll_StateM_emCBase.h>
//#include <org/vishia/emC/Base/test_Stacktrc_Exc/testAll_Stacktrc_Exc_emCBase.h>
#include <org/vishia/emC/Base/test_ObjectJc/testAll_ObjectJcpp_emCBase.h>

#include <emC_Test_C_Cpp/InitComposite_C_CPP_TestemC.h>

int main(int nArgs, char const*const* cmdArgs )
{
  STACKTRC_ENTRY("main");

  test_InitComposite_C_CPP_TestemC();

  //testAll_ObjectJcpp_emCBase();
  //testAll_Stacktrc_Exc_emCBase();
  //testAll_StateM_emCBase();
  STACKTRC_RETURN 0;
}
