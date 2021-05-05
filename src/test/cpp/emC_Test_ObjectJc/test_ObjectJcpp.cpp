#include "emC_Test_ObjectJc/test_ObjectJcpp.h"
#include <emC/Test/testAssert.h>
#include <emC/Base/MemC_emC.h>
#include <stdio.h>

//This reflection supports only type check, it is not intent to use symbolic access.
//Independent of the definition of the ClassJc only the simple ClassJc is defined here supporting type check.
//See another example
ClassJc const refl_BaseData_Test_ObjectJc = INIZ_ClassJc(refl_BaseData_Test_ObjectJc, "BaseData_Test_ObjectJc");
ClassJc const refl_MyBaseClass_Test_ObjectJcpp = INIZsuper_ClassJc(refl_MyBaseClass_Test_ObjectJcpp, "MyBaseClass_Test_ObjectJcpp", &refl_BaseData_Test_ObjectJc);
ClassJc const refl_MyClass_Test_ObjectJcpp = INIZsuper_ClassJc(refl_MyClass_Test_ObjectJcpp, "MyClass_Test_ObjectJcpp", &refl_MyBaseClass_Test_ObjectJcpp);


//Constructor of the C-data:
BaseData_Test_ObjectJc_s* ctor_BaseData_Test_ObjectJc(ObjectJc* othiz) {
  //
  //The ObjectJc-data have to be initialized before call of this ctor to assure correct instantiation.
  //check it. At least sizeof(owndata) should be set, reflection and id are not tested.
  BaseData_Test_ObjectJc_s* thiz = C_CAST(BaseData_Test_ObjectJc_s*, othiz);
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, (int)sizeof(*thiz), refl_BaseData_Test_ObjectJc, 0)
            , "faulty ObjectJc initialization", (int)sizeof(*thiz), 0);  
  //
  //After this check thiz can be used without doubt, but if ASSERT_emC is disabled, it should be tested well.
  //
  //now initialize all internal data of thiz. Note: Usage of memset may be prevented, it may not be efficient, 
  //instead use immediately 0-initialization to the members if necessary.
  //All members should be handled here.  
  thiz->d1 = 123;
  thiz->d2 = 234.5f;
  return thiz;
}


//Constructor of the base C++ class:
MyBaseClass_Test_ObjectJcpp::MyBaseClass_Test_ObjectJcpp(ObjectJc const* othiz)
{
  ASSERT_emC(othiz == &this->base.obj, "C++ ObjectJc initialization error", 0,0);
  //It should initialize its base class, it is the C-struct data.
  //The ObjectJc-part should be initialized before the C-ctor is invoked.
  //It is a point of safety. 
  //For static data the initializing is done with a INIZ_ObjectJc(...)
  //For dynamic data it is done after allocation. This is the first execution pointer after new,
  //it is the ctor of the C++ inner base class. This ctor will be called firstly after new(...).
  //ctor_ObjectJc(&this->base.obj, this, size, refl, idObj); 
  //Now initialize the base struct of this class:
  ctor_BaseData_Test_ObjectJc(&this->base.obj);
}


//Constructor of the base C++ class:
MyBaseClass_Test_ObjectJcpp::MyBaseClass_Test_ObjectJcpp()
{
  //Because it is the public ctor without ObjectJc, is it the ctor of the instance, not for deviation.
  //Hence initialize ObjectJc with the correct size. 
  CTOR_ObjectJc(&this->base.obj, this, sizeof(*this), refl_MyBaseClass_Test_ObjectJcpp, 0);
  //It should initialize its base class, it is the C-struct data.
  //The ObjectJc-part should be initialized before the C-ctor is invoked.
  //It is a point of safety. 
  //For static data the initializing is done with a INIZ_ObjectJc(...)
  //For dynamic data it is done after allocation. This is the first execution pointer after new,
  //it is the ctor of the C++ inner base class. This ctor will be called firstly after new(...).
  //ctor_ObjectJc(&this->base.obj, this, size, refl, idObj); 
  //Now initialize the base struct of this class:
  ctor_BaseData_Test_ObjectJc(&this->base.obj);
}


//Constructor of the base C++ class:
BaseData_Test_ObjectJc::BaseData_Test_ObjectJc(ObjectJc const* obj, int idObj){
  //The ObjectJc-part should be initialized either before the C-ctor is invoked.
  // 
  if(obj == null) { //or, if it is the instance constructor, obj == null
    //then initialize here.
    CTOR_ObjectJc(&this->base.obj, this, sizeof(*this), refl_BaseData_Test_ObjectJc, idObj);
  }
  //Now initialize the base struct of this class:
  ctor_BaseData_Test_ObjectJc(&this->base.obj);
}


//Constructor of the base C++ class:
BaseData_Test_PrivateObjectJc::BaseData_Test_PrivateObjectJc(ObjectJc const* othiz, int idObj)
: objectJc(othiz !=null ? othiz :   //The ObjectJc-part should be initialized either before the C-ctor is invoked.
    CTOR_ObjectJc(&this->base.obj, this, sizeof(*this), refl_BaseData_Test_ObjectJc, idObj))
{
  //Now initialize the base struct of this class:
  ctor_BaseData_Test_ObjectJc(&this->base.obj);
}


//Constructor of the used C++ class:
MyClass_Test_ObjectJcpp::MyClass_Test_ObjectJcpp(int idObj) 
//firstly call the base ctor in C++ syntax:
: MyBaseClass_Test_ObjectJcpp(
      CTOR_ObjectJc(&this->base.obj, this, sizeof(*this)
                    , refl_MyClass_Test_ObjectJcpp, idObj)) 
{
  //initialize class data.
  this->val2 = 345.5f;
}






static int test_ObjectJcpp_Base ( ) {
  STACKTRC_ENTRY("test_ObjectJcpp_Base");
  TEST_TRY("test_ObjectJcpp_Base") {

    //This class bases on ObjectJcpp which contains the virtual toObject():
    MyClass_Test_ObjectJcpp* myData = new MyClass_Test_ObjectJcpp( 0 );

    ObjectJc* obj = myData->toObject();  //get ObjectJc via virtual call.
    #ifndef DEF_REFLECTION_NO  //Baseclass can only be tested with at least DEF_REFLECTION_SIMPLE
    bool bOk = checkStrict_ObjectJc(obj, (int)sizeof(BaseData_Test_ObjectJc_s), &refl_BaseData_Test_ObjectJc, 0);  
    TEST_TRUE(bOk, "C++ class detects base struct tyoe via reflection");
    #endif
    //printf("\n  - size of an ObjectJc = 0x%2.2X Byte", (uint)sizeof(*obj));

    //It is the position of the ObjectJc inside myData, it is >0 because vtbl in myData before ObjectJc:
    int offsInstance_Obj = (int)OFFSET_MemUnit(myData, obj);

    TEST_TRUE(offsInstance_Obj >0, "offsInstance_Obj is >0 because the class has a virtual table before ObjectJc-data");
  
    #ifdef DEF_ObjectJcpp_REFLECTION
      TEST_TRUE(offsInstance_Obj == obj->offsetToInstanceAddr, "offsInstance_Obj == as stored in ObjectJc");
    #endif
    TEST_TRUE(! isInitialized_ObjectJc(obj), "Initializing should be set in the post-initializing phase. Is be 0 here.");
    //Because of the class has no more aggregation, set initialized on user level. 
    setInitialized_ObjectJc(myData->toObject());  
    TEST_TRUE(isInitialized_ObjectJc(obj), "Initializing is recognized");
    TEST_TRUE(myData->get_d1() == 123, "getter for int C-Data");
    TEST_TRUE(myData->get_val2() == 345.5f, "getter for float C-Data");  //attentive: should have not rounding problems in float
    //
    //This C_CAST is admissible, better is assertion with type check.
    BaseData_Test_ObjectJc_s* myDataC = C_CAST(BaseData_Test_ObjectJc_s*, obj);
    CHECK_TRUE(myDataC->d1 == 123, "cast from obj to C-data");
    //The following downcast forces a compiler error, cannot be done: 
    //no: MyClass_Test_ObjectJcpp* myData2 = dynamic_cast<MyClass_Test_ObjectJcpp*>(myDataC);
    //
    //Instead, use as general access type:
    //ObjectJcpp* obji = static_cast<ObjectJcpp*>(myData);
    //CHECK_TRUE(OFFSET_MemUnit(obji, myData)==0, "ObjectJcpp on same address as myData");

    //ObjectJcpp* obji2 = myData;  //implicite cast also ok. 
    //CHECK_TRUE(OFFSET_MemUnit(obji2, myData)==0, "implicitely cast for ObjectJcpp on same address as myData");
    //MyClass_Test_ObjectJcpp* myData2 = static_cast<MyClass_Test_ObjectJcpp*>(obji);
    //CHECK_TRUE(OFFSET_MemUnit(myData2, obji)==0, "implicitely cast for ObjectJcpp on same address as myData");
    delete myData;
  }_TEST_TRY_END
  //
  STACKTRC_RETURN 0;
}


int test_ObjectJc_public  () {
  STACKTRC_ENTRY("test_ObjectJc_public");
  TEST_TRY("test_ObjectJc_public") {
    //Check an C++ instance which has not additional data nor virtual operations:
    BaseData_Test_ObjectJc* myData2 = new BaseData_Test_ObjectJc(null, 0); //Note: The ObjectJc* ref left null, not able to provide.
    //
    ObjectJc* obj2 = &myData2->base.obj; //access immediately to the public inherited data.
                                         //
    int offsInstance_Obj2 = (int)OFFSET_MemUnit(myData2, obj2);
    TEST_TRUE(offsInstance_Obj2 ==0, "offsInstance_Obj ==0 because the class has not a virtual table before ObjectJc-data");
    //
    //activate it to test whether the test with Exception runs.
    //ASSERT_emC(false, "Test-TRY", 0,0);
    //
    int size_myData2 = (int)sizeof(BaseData_Test_ObjectJc);  //size of the C++ class
    int size_myDataC2 = (int)sizeof(BaseData_Test_ObjectJc_s);  //size of the C struct
    TEST_TRUE(size_myData2 == size_myDataC2, "sizes C-struct and C++-class are identically because the C++ class does not define any data.");

    (*myData2) *= 3.5f;
    TEST_TRUE(myData2->d2 == (234.5f * 3.5f)," *= operation");
  }_TEST_TRY_END
  /*activate it to test internally of macro _TEST_TRY_END
  } msgEndFileLine_testAssert_emC(bTESTok);} _TRY  CATCH(Exception, exc) { 
    exceptionFileLine_testAssert_emC(exc, __FILE__, __LINE__); 
  } END_TRY
  */
  STACKTRC_RETURN 0;
}



int test_ObjectJc_private_via_accessOper  () {
  STACKTRC_ENTRY("test_ObjectJc_private_via_accessOper");
  TEST_TRY("test_ObjectJc_private_via_accessOper") {
  
    //Check an C++ instance which has not additional data nor virtual operations:
    BaseData_Test_PrivateObjectJc* myData2 = new BaseData_Test_PrivateObjectJc(null, 0);
    //
    ObjectJc const* obj2 = myData2->toObject(); //access immediately to the public inherited data.
                                         //
    int offsInstance_Obj2 = (int)OFFSET_MemUnit(myData2, obj2);
    TEST_TRUE(offsInstance_Obj2 ==0, "offsInstance_Obj ==0 because the class has not a virtual table before ObjectJc-data");
    //
    int size_myData2 = (int)sizeof(BaseData_Test_PrivateObjectJc);  //size of the C++ class
    int size_myDataC2 = (int)sizeof(BaseData_Test_ObjectJc_s);  //size of the C struct
    TEST_TRUE(size_myData2 > size_myDataC2, "class size is greater because of objectJc element.");

    float result = (*myData2) *= 3.5f;
    TEST_TRUE(result == (234.5f * 3.5f), " *= operation");
  }_TEST_TRY_END
  STACKTRC_RETURN 0;
}




int test_ObjectJcpp  () {
  STACKTRC_ENTRY("test_ObjectJcpp");
  test_ObjectJcpp_Base();
  test_ObjectJc_public();
  test_ObjectJc_private_via_accessOper();
  STACKTRC_RETURN 0;
}
