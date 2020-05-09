#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC/Test/testAssert.h>
#include <emC/Base/String_emC.h>
//Use in C-Compilation too, with all variants of applstdef_emC.h

//It is a minimal implementation of the Type. 
#ifdef DEF_ObjectJc_REFLREF
  ClassJc const refl_MyType_Test_ObjectJc = INIZ_ClassJc(refl_MyType_Test_ObjectJc, "MyType_Test_ObjectJc");
#endif

#define ID_Obj_myData1const 0x234

//Use the id_refl_MyType_Test_ObjectJc for the instance id because it is used for Typetest in a simplest ObjectJc definition
MyType_Test_ObjectJc_s const myData1const = INIZ_VAL_MyType_Test_ObjectJc(myData1const, ID_Obj_myData1const, 12, 1.2345f);







#ifdef DEF_ObjectJc_REFLREF
#  define B_CANNOT_CHECK false
#else
#  define B_CANNOT_CHECK true
#endif


void test_static_ObjectJc() {
  STACKTRC_ENTRY("test_ObjectJc");
  TEST_START("test_ObjectJc");
  //StringJc ss = z_StringJc("ccc");

  MyType_Test_ObjectJc_s const* data = &myData1const;
  TEST_TRUE(myData1const.data1 == 12, "INIZ_VAL_MyType_Test_ObjectJc");
  bool bOk = CHECKstrict_ObjectJc(&data->base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, 0);
  CHECK_TRUE(bOk, "checkStrict_ObjectJc with refl and without instance id.")
  MAYBE_UNUSED_emC bool bNok = CHECKstrict_ObjectJc(&data->base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, 0xeee);
  #ifdef DEF_ObjectJc_REFLREF
    CHECK_TRUE(!bNok, "checkStrict_ObjectJc with refl but with faulty instance id should fail.")
  #endif
  bOk = CHECKstrict_ObjectJc(&myData1const.base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, ID_Obj_myData1const);
  CHECK_TRUE(bOk, "checkStrict_ObjectJc with refl==null and correct instance id")
  bOk = CHECKstrict_ObjectJc(&myData1const.base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, ID_Obj_myData1const);
  TEST_TRUE(bOk, "checkStrict_ObjectJc");
  TEST_END;
  STACKTRC_LEAVE;
}



void test_Alloc_ObjectJc() {
  STACKTRC_ENTRY("test_Alloc_ObjectJc");
  TEST_START("test_ALLOC_ObjectJc");
  TRY {
    MyType_Test_ObjectJc_s* myData = (MyType_Test_ObjectJc_s*)ALLOC_ObjectJc(sizeof(MyType_Test_ObjectJc_s), refl_MyType_Test_ObjectJc, 0);
    bool bOk = CHECKstrict_ObjectJc(&myData->base.obj, sizeof(MyType_Test_ObjectJc_s), refl_MyType_Test_ObjectJc, 0);
    CHECK_TRUE(bOk, "allocated ObjectJc is initialized")
    free_ObjectJc(&myData->base.obj);
  }_TRY
  CATCH(Exception, exc){
    TEST_EXC(exc);
  }
  END_TRY;

  TEST_END;
  STACKTRC_LEAVE;
}



void test_ObjectJc() {
  test_static_ObjectJc();
  test_Alloc_ObjectJc();
}
