#include "test_ObjectJcpp.h"
#include <emC/Test/testAssert.h>

#include <stdio.h>

#ifdef DEF_REFLECTION_NO_emC
  //Define the reflection as simple ClassJc without Field definition for type test only. 
  ClassJc const reflection_MyData_Test_ObjectJcpp = INIZ_ClassJc(reflection_MyData_Test_ObjectJcpp, "MyData_Test_ObjectJcpp");
  ClassJc const reflection_BaseData_Test_ObjectJcpp = INIZ_ClassJc(reflection_BaseData_Test_ObjectJcpp, "BaseData_Test_ObjectJcpp");
  ClassJc const reflection_BaseData_Test_ObjectJc = INIZ_ClassJc(reflection_BaseData_Test_ObjectJc, "BaseData_Test_ObjectJc");
#else
  //here generated Reflection may be included (*.refl-File from CHeader2Reflection)
  //The simple form is, defined class, without field definition.
  //int32 reflOffs_BaseData_Test_ObjectJc[] = {0};
  //int32 reflOffs_BaseData_Test_ObjectJcpp[] = {0};
  //int32 reflOffs_MyData_Test_ObjectJcpp[] = {0};
  //ClassJc const reflection_BaseData_Test_ObjectJc = INIZreflOffs_ClassJc(reflection_BaseData_Test_ObjectJc, "BaseData_Test_ObjectJc", reflOffs_BaseData_Test_ObjectJc);
  //ClassJc const reflection_BaseData_Test_ObjectJcpp = INIZreflOffsSuper_ClassJc(reflection_BaseData_Test_ObjectJcpp, "BaseData_Test_ObjectJcpp", reflOffs_BaseData_Test_ObjectJcpp, &reflection_BaseData_Test_ObjectJc);
  //ClassJc const reflection_MyData_Test_ObjectJcpp = INIZreflOffsSuper_ClassJc(reflection_MyData_Test_ObjectJcpp, "MyData_Test_ObjectJcpp", reflOffs_MyData_Test_ObjectJcpp, &reflection_BaseData_Test_ObjectJcpp);
  ClassJc const refl_BaseData_Test_ObjectJc = INIZ_ClassJc(refl_BaseData_Test_ObjectJc, "BaseData_Test_ObjectJc");
  ClassJc const refl_BaseData_Test_ObjectJcpp = INIZsuper_ClassJc(refl_BaseData_Test_ObjectJcpp, "BaseData_Test_ObjectJcpp", &refl_BaseData_Test_ObjectJc);
  ClassJc const refl_MyData_Test_ObjectJcpp = INIZsuper_ClassJc(refl_MyData_Test_ObjectJcpp, "MyData_Test_ObjectJcpp", &refl_BaseData_Test_ObjectJcpp);
#endif


//Constructor of the C-data:
void ctor_BaseData_Test_ObjectJcpp(ObjectJc* othiz) {
  //
  //The ObjectJc-data have to be initialized before call of this ctor to assure correct instantiation.
  //check it. At least sizeof(owndata) should be set, reflection and id are not tested.
  bool bObjOk;
  #ifdef DEF_ObjectJc_REFLREF
    bObjOk = checkStrict_ObjectJc(othiz, (int)sizeof(BaseData_Test_ObjectJc_s), &refl_BaseData_Test_ObjectJc, 0, null);  
  #else 
    bObjOk = true; //cannot be checked because derived
  #endif 
  if(bObjOk) {
    //
    //After this check a cast can be done without doubt:
    BaseData_Test_ObjectJc_s* thiz = FORCED_CAST(BaseData_Test_ObjectJc_s*, othiz);
    //
    //now initialize some internal data:
    thiz->d1 = 123;
    thiz->d2 = 234.5f;
  }
}




//Constructor of the base C++ class:
BaseData_Test_ObjectJcpp::BaseData_Test_ObjectJcpp(int size, ClassJc const* refl, int idObj){
  //It should initialize its base class, it is the C-struct data.
  //The ObjectJc-part should be initialized before the C-ctor is invoked.
  //It is a point of safety. 
  //For static data the initializing is done with a INIZ_ObjectJc(...)
  //For dynamic data it is done after allocation. This is the first execution pointer after new,
  //it is the ctor of the C++ inner base class. This ctor will be called firstly after new(...).
  iniz_ObjectJc(&this->base.obj, this, size, refl, idObj); 
  //Now initialize the base struct of this class:
  ctor_BaseData_Test_ObjectJcpp(&this->base.obj);
}


//Constructor of the base C++ class:
BaseData_Test_ObjectJc::BaseData_Test_ObjectJc(int size, ClassJc const* refl, int idObj){
  //It should initialize its base class, it is the C-struct data.
  //The ObjectJc-part should be initialized before the C-ctor is invoked.
  //It is a point of safety. 
  //For static data the initializing is done with a INIZ_ObjectJc(...)
  //For dynamic data it is done after allocation. This is the first execution pointer after new,
  //it is the ctor of the C++ inner base class. This ctor will be called firstly after new(...).
  iniz_ObjectJc(&this->base.obj, this, size, refl, idObj); 
  //Now initialize the base struct of this class:
  ctor_BaseData_Test_ObjectJcpp(&this->base.obj);
}


//Constructor of the base C++ class:
BaseData_Test_PrivateObjectJc::BaseData_Test_PrivateObjectJc(int size, ClassJc const* refl, int idObj){
  //It should initialize its base class, it is the C-struct data.
  //The ObjectJc-part should be initialized before the C-ctor is invoked.
  //It is a point of safety. 
  //For static data the initializing is done with a INIZ_ObjectJc(...)
  //For dynamic data it is done after allocation. This is the first execution pointer after new,
  //it is the ctor of the C++ inner base class. This ctor will be called firstly after new(...).
  iniz_ObjectJc(&this->base.obj, this, size, refl, idObj); 
  //Now initialize the base struct of this class:
  ctor_BaseData_Test_ObjectJcpp(&this->base.obj);
}


//Constructor of the used C++ class:
MyData_Test_ObjectJcpp::MyData_Test_ObjectJcpp(int size, ClassJc const* refl, int idObj) 
//firstly call the base ctor in C++ syntax:
: BaseData_Test_ObjectJcpp(size, refl, idObj) 
{
  //initialize class data.
  this->val2 = 345.5f;
}



static int test_ObjectJcpp_Base ( ) {
  TEST_START("test_ObjectJcpp_Base");

  //This class bases on ObjectJcpp which contains the virtual toObject():
  MyData_Test_ObjectJcpp* myData = new MyData_Test_ObjectJcpp((int)sizeof(*myData)
    , &refl_MyData_Test_ObjectJcpp, 0
    );

  ObjectJc* obj = myData->toObject();  //get ObjectJc via virtual call.
  
  //printf("\n  - size of an ObjectJc = 0x%2.2X Byte", (uint)sizeof(*obj));

  //It is the position of the ObjectJc inside myData, it is >0 because vtbl in myData before ObjectJc:
  int offsInstance_Obj = OFFSET_MemUnit(myData, obj);

  TEST_TRUE(offsInstance_Obj >0, "offsInstance_Obj is >0 because the class has a virtual table before ObjectJc-data");
  
  #ifdef DEF_ObjectJcpp_REFLECTION
    TEST_TRUE(offsInstance_Obj == obj->offsetToStartAddr, "offsInstance_Obj == as stored in ObjectJc");
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
  //no: MyData_Test_ObjectJcpp* myData2 = dynamic_cast<MyData_Test_ObjectJcpp*>(myDataC);
  //
  //Instead, use as general access type:
  ObjectJcpp* obji = static_cast<ObjectJcpp*>(myData);
  CHECK_TRUE(OFFSET_MemUnit(obji, myData)==0, "ObjectJcpp on same address as myData");

  ObjectJcpp* obji2 = myData;  //implicite cast also ok. 
  CHECK_TRUE(OFFSET_MemUnit(obji2, myData)==0, "implicitely cast for ObjectJcpp on same address as myData");
  MyData_Test_ObjectJcpp* myData2 = dynamic_cast<MyData_Test_ObjectJcpp*>(obji);
  CHECK_TRUE(OFFSET_MemUnit(myData2, obji)==0, "implicitely cast for ObjectJcpp on same address as myData");
  TEST_END;
  //
  return 0;
}



int test_ObjectJc_public  () {
  TEST_START("test_ObjectJc_public");
  //Check an C++ instance which has not additional data nor virtual operations:
  BaseData_Test_ObjectJc* myData2 = new BaseData_Test_ObjectJc((int)sizeof(*myData2)
    , &refl_BaseData_Test_ObjectJc, 0
  );
  //
  ObjectJc* obj2 = &myData2->base.obj; //access immediately to the public inherited data.
                                       //
  int offsInstance_Obj2 = OFFSET_MemUnit(myData2, obj2);
  TEST_TRUE(offsInstance_Obj2 ==0, "offsInstance_Obj ==0 because the class has not a virtual table before ObjectJc-data");
  //
  int size_myData2 = (int)sizeof(BaseData_Test_ObjectJc);  //size of the C++ class
  int size_myDataC2 = (int)sizeof(BaseData_Test_ObjectJc_s);  //size of the C struct
  TEST_TRUE(size_myData2 == size_myDataC2, "sizes C-struct and C++-class are identically because the C++ class does not define any data.");

  (*myData2) *= 3.5f;
  TEST_TRUE(myData2->d2 == (234.5f * 3.5f)," *= operation");
  TEST_END;
  return 0;
}



int test_ObjectJc_private_via_accessOper  () {
  TEST_START("test_ObjectJc_private_via_accessOper");
  
  //Check an C++ instance which has not additional data nor virtual operations:
  BaseData_Test_PrivateObjectJc* myData2 = new BaseData_Test_PrivateObjectJc((int)sizeof(*myData2)
    , &refl_BaseData_Test_ObjectJc, 0
  );
  //
  ObjectJc* obj2 = myData2->toObject(); //access immediately to the public inherited data.
                                       //
  int offsInstance_Obj2 = OFFSET_MemUnit(myData2, obj2);
  TEST_TRUE(offsInstance_Obj2 ==0, "offsInstance_Obj ==0 because the class has not a virtual table before ObjectJc-data");
  //
  int size_myData2 = (int)sizeof(BaseData_Test_PrivateObjectJc);  //size of the C++ class
  int size_myDataC2 = (int)sizeof(BaseData_Test_ObjectJc_s);  //size of the C struct
  TEST_TRUE(size_myData2 == size_myDataC2, "sizes are identically because the C++ class does not define any data.");

  float result = (*myData2) *= 3.5f;
  TEST_TRUE(result == (234.5f * 3.5f), " *= operation");
  TEST_END;
  return 0;
}




int test_ObjectJcpp  () {
  STACKTRC_ENTRY("test_ObjectJcpp");
  TRY {
    test_ObjectJcpp_Base();
    test_ObjectJc_public();
    test_ObjectJc_private_via_accessOper();
  } _TRY
  CATCH(Exception, exc) {
    TEST_EXC(exc);
  }
  END_TRY
  STACKTRC_RETURN 0;
}
