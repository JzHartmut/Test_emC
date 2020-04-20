#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC/Test/testAssert.h>

//Use in C-Compilation too, with all variants of applstdef_emC.h

//It is a minimal implementation of the Type. 
ClassJc const refl_MyType_Test_ObjectJc = INIZ_ClassJc(refl_MyType_Test_ObjectJc, idType_MyType_Test_ObjectJc, "MyType_Test_ObjectJc");

//Use the idType_MyType_Test_ObjectJc for the instance id because it is used for Typetest in a simplest ObjectJc definition
const MyType_Test_ObjectJc_s myData1const = INIZ_VAL_MyType_Test_ObjectJc(myData1const, idType_MyType_Test_ObjectJc, 0x1234, 1.2345f);


void test_ObjectJc() {
  STACKTRC_ENTRY("test_ObjectJc");
  TEST_START("test_ObjectJc");

  TEST_TRUE(myData1const.data1 == 0x1234, "INIZ_VAL_MyType_Test_ObjectJc");
  bool bNok = checkStrict_ObjectJc(&myData1const.base.obj, sizeof(myData1const), null, 1, _thCxt);
  CHECK_TRUE(!bNok, "checkStrict_ObjectJc with refl==null and faulty instance id should fail.")
  bool bOk = checkStrict_ObjectJc(&myData1const.base.obj, sizeof(myData1const), null, idType_MyType_Test_ObjectJc, _thCxt);
  CHECK_TRUE(bOk, "checkStrict_ObjectJc with refl==null and correct instance id")
  bOk = checkStrict_ObjectJc(&myData1const.base.obj, sizeof(myData1const), &refl_MyType_Test_ObjectJc, idType_MyType_Test_ObjectJc, _thCxt);
  TEST_TRUE(bOk, "checkStrict_ObjectJc");
  STACKTRC_LEAVE;
}