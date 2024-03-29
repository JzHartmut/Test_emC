#include <emC_Test_ObjectJc/test_ObjectJc.h>
#include <emC/Test/testAssert.h>
#include <emC/Base/String_emC.h>
//Use in C-Compilation too, with all variants of applstdef_emC.h

//It is a minimal implementation of the Type. 
#ifndef DEF_REFLECTION_NO
  ClassJc const refl_MyBaseType_Test_ObjectJc = INIZ_ClassJc(refl_MyBaseType_Test_ObjectJc, "MyBaseType_Test_ObjectJc");
  ClassJc const refl_MyType_Test_ObjectJc = INIZsuper_ClassJc(refl_MyType_Test_ObjectJc, "MyType_Test_ObjectJc", &refl_MyBaseType_Test_ObjectJc);
#endif

//An ID for the instance:
#define ID_Obj_myData1const 0x234

//initialize as const data possible for Flash ROM with an initializer list. 
//Note: The instance ID is not used for DEF_REFLECTION_NO. 
MyType_Test_ObjectJc_s const myData1const = INIZ_VAL_MyType_Test_ObjectJc(myData1const, ID_Obj_myData1const, 12.45f, 47);




#ifndef DEF_REFLECTION_NO
#  define B_CANNOT_CHECK false
#else
#  define B_CANNOT_CHECK true
#endif


//Test the static and const initialization.
void test_static_ObjectJc() {
  STACKTRC_ENTRY("test_ObjectJc");
  TEST_TRY("test_ObjectJc")
    //StringJc ss = z_StringJc("ccc");

    MyType_Test_ObjectJc_s const* data = &myData1const;
    #ifndef DEF_REFLECTION_NO  //cannot test INSTANCEOF without reflection
      TEST_TRUE(INSTANCEOF_ObjectJc(&data->base.obj, refl_MyType_Test_ObjectJc), "refl type is ok");
    #endif
    TEST_TRUE(myData1const.data1.y == 42.0f, "INIZ_VAL_MyType_Test_ObjectJc");
    bool bOk = CHECKstrict_ObjectJc(&data->base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, 0);
    CHECK_TRUE(bOk, "checkStrict_ObjectJc with refl and without instance id.")
    MAYBE_UNUSED_emC bool bNok = CHECKstrict_ObjectJc(&data->base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, 0xeee);
    #ifndef DEF_REFLECTION_NO
      CHECK_TRUE(!bNok, "checkStrict_ObjectJc with refl but with faulty instance id should fail.")
    #endif
    bOk = CHECKstrict_ObjectJc(&myData1const.base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, ID_Obj_myData1const);
    CHECK_TRUE(bOk, "checkStrict_ObjectJc with refl==null and correct instance id")
    bOk = CHECKstrict_ObjectJc(&myData1const.base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, ID_Obj_myData1const);
    TEST_TRUE(bOk, "checkStrict_ObjectJc");
  TEST_TRY_END;
  STACKTRC_LEAVE;
}



void ctor_MyBaseType_Test_ObjectJc(MyBaseType_Test_ObjectJc_s* thiz, float val) {
  //Try to construct the ObjectJc part. 
  //If this ctor is invoked in a derived environment, it does not change the already done construction.
  STACKTRC_ENTRY("ctor_MyBaseType_Test_ObjectJc");
  ASSERT_emC(CHECKstrict_ObjectJc(&thiz->base.obj, sizeof(*thiz), refl_MyBaseType_Test_ObjectJc, 0), "not matching instance and type", 0,0);
  thiz->data1 = (int32)val;
  thiz->data2 = val;
  STACKTRC_RETURN;
}


void ctor_InnerData_Test_ObjectJc(InnerData_Test_ObjectJc* thiz) {
  thiz->x = 3.14f;
  thiz->y = 42.0f;
  thiz->z = -3.0f;
}


void ctor_MyType_Test_ObjectJc(MyType_Test_ObjectJc_s* thiz, float val1, int32 val2) {
  //Try to construct the ObjectJc part. 
  //If this ctor is invoked in a derived environment, it does not change the already done construction.
  STACKTRC_ENTRY("ctor_MyType_Test_ObjectJc");
  ASSERT_emC(CHECKstrict_ObjectJc(&thiz->base.obj, sizeof(*thiz), refl_MyType_Test_ObjectJc, 0), "not matching instance and type", 0,0);
  //do not use the refl argument, it is for DEF_REFLECTION_NO, refl may be unknown.
  //It is not necessary because the ObjectJc is initialized already.
  ctor_MyBaseType_Test_ObjectJc(&thiz->base.MyBaseType_Test_ObjectJc, val1);
  thiz->m = val2;
  thiz->n = -val2;
  ctor_InnerData_Test_ObjectJc(&thiz->data1);
  thiz->p = 0;  //do nothing left uninitialized!
  thiz->q = 0;
  STACKTRC_RETURN;
}




//Test the static and const initialization.
void test_ctor_ObjectJc ( ) {
  STACKTRC_ENTRY("test_ctor_ObjectJc");
  TEST_START("test_ctor_ObjectJc");
  //StringJc ss = z_StringJc("ccc");
  TRY {
    MyType_Test_ObjectJc_s data = {0} ; //construct in stack with recommended 0-initialization
    //firstly always intialize the ObjectJc base data. It will be checked in the derived ctor.
    CTOR_ObjectJc(&data.base.obj, &data, sizeof(data), refl_MyType_Test_ObjectJc, ID_Obj_myData1const);
    //Then construct the instance.
    ctor_MyType_Test_ObjectJc(&data, 42.0f, 234);

    TEST_TRUE(INSTANCEOF_ObjectJc(&data.base.obj, refl_MyType_Test_ObjectJc), "refl type is ok");
    TEST_TRUE(data.data1.y == 42.0f, "INIZ_VAL_MyType_Test_ObjectJc");
    bool bOk = CHECKstrict_ObjectJc(&data.base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, 0);
    CHECK_TRUE(bOk, "checkStrict_ObjectJc with refl and without instance id.")
    MAYBE_UNUSED_emC bool bNok = CHECKstrict_ObjectJc(&data.base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, 0xeee);
    #ifndef DEF_REFLECTION_NO
      CHECK_TRUE(!bNok, "checkStrict_ObjectJc with refl but with faulty instance id should fail.")
    #endif
    bOk = CHECKstrict_ObjectJc(&data.base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, ID_Obj_myData1const);
    CHECK_TRUE(bOk, "checkStrict_ObjectJc with refl==null and correct instance id")
    bOk = CHECKstrict_ObjectJc(&data.base.obj, sizeof(myData1const), refl_MyType_Test_ObjectJc, ID_Obj_myData1const);
    TEST_TRUE(bOk, "checkStrict_ObjectJc");
  }_TRY;
  CATCH(Exception, exc) {
    TEST_EXC(exc);
  }
  END_TRY;
  TEST_END;
  STACKTRC_LEAVE;
}


void test_Alloc_ObjectJc ( ) {
  STACKTRC_ENTRY("test_Alloc_ObjectJc");
  TEST_START("test_ALLOC_ObjectJc");
  #ifndef DEF_ObjectJc_SIMPLEST
  TRY {
    MyType_Test_ObjectJc_s* myData = (MyType_Test_ObjectJc_s*)ALLOC_ObjectJc(sizeof(MyType_Test_ObjectJc_s), refl_MyType_Test_ObjectJc, 0);
    bool bOk = CHECKstrict_ObjectJc(&myData->base.obj, sizeof(MyType_Test_ObjectJc_s), refl_MyType_Test_ObjectJc, 0);
    CHECK_TRUE(bOk, "allocated ObjectJc is initialized")
    #ifdef DEF_ObjectJc_FULLCAPABILITY
      //free is not intended to use for ObjectSimple_emC.h, not for embedded platforms. 
      //free is executed on end of the process.
      free_ObjectJc(&myData->base.obj);
    #endif
  }_TRY
  CATCH(Exception, exc){
    TEST_EXC(exc);
  }
  END_TRY;
  #endif //DEF_ObjectJc_SIMPLEST

  TEST_END;
  STACKTRC_LEAVE;
}



void test_ObjectJc() {
  test_static_ObjectJc();
  test_ctor_ObjectJc();
  test_Alloc_ObjectJc();
}
