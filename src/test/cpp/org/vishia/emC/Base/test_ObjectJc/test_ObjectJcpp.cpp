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
  ClassJc const reflection_BaseData_Test_ObjectJc = INIZ_ClassJc(reflection_BaseData_Test_ObjectJc, "BaseData_Test_ObjectJc");
  ClassJc const reflection_BaseData_Test_ObjectJcpp = INIZsuper_ClassJc(reflection_BaseData_Test_ObjectJcpp, "BaseData_Test_ObjectJcpp", &reflection_BaseData_Test_ObjectJc);
  ClassJc const reflection_MyData_Test_ObjectJcpp = INIZsuper_ClassJc(reflection_MyData_Test_ObjectJcpp, "MyData_Test_ObjectJcpp", &reflection_BaseData_Test_ObjectJcpp);
#endif


//Constructor of the C-data:
void ctor_BaseData_Test_ObjectJcpp(ObjectJc* othiz) {
  //
  //The ObjectJc-data have to be initialized before call of this ctor to assure correct instantiation.
  //check it. At least sizeof(owndata) should be set, reflection and id are not tested.
  #ifdef DEF_ObjectJc_REFLREF
    ClassJc const* refl = &reflection_BaseData_Test_ObjectJc;
  #else 
    ClassJc const* refl = null; //cannot be checked because derived
  #endif 
  if(checkStrict_ObjectJc(othiz, (int)sizeof(BaseData_Test_ObjectJc_s), 0, refl, null)) {
    //
    //After this check a cast can be done without doubt:
    BaseData_Test_ObjectJc_s* thiz = (BaseData_Test_ObjectJc_s*)othiz;
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



int test_ObjectifcBaseJcpp  () {

  MyData_Test_ObjectJcpp* myData = new MyData_Test_ObjectJcpp((int)sizeof(*myData)
    , &reflection_MyData_Test_ObjectJcpp, 0
    );

  ObjectJc* obj = myData->toObject();
  
  printf("\n  - size of an ObjectJc = 0x%2.2X Byte", (uint)sizeof(*obj));

  //It is the position of the ObjectJc inside myData:
  int offsInstance_Obj = OFFSET_MemUnit(myData, obj);
  EXPECT_TRUE(offsInstance_Obj >0) << "offsInstance_Obj should be >0 because the class has a virtual table before ObjectJc-data"; 
  #ifndef DEF_ObjectJc_SIMPLE
    EXPECT_TRUE(offsInstance_Obj == obj->state.b.offsetToStartAddr) << "offsInstance_Obj should be same a stored in ObjectJc"; 
  #endif
  EXPECT_FALSE(isInitialized_ObjectJc(obj)) << "Initializing should be set in the post-initializing phase. Should be 0 here.";
  //Because of the class has no more aggregation, set initialized on user level. 
  setInitialized_ObjectJc(myData->toObject());  
  EXPECT_TRUE(isInitialized_ObjectJc(obj)) << "Initializing is not recognized";
  EXPECT_TRUE(myData->get_d1() == 123) << "faulty C-Data";
  EXPECT_TRUE(myData->get_val2() == 345.5f) << "faulty C-Data";  //attentive: should have not rounding problems in float
  //
  //This C_CAST is admissible, better is assertion with type check.
  BaseData_Test_ObjectJc_s* myDataC = C_CAST(BaseData_Test_ObjectJc_s*, obj);
  //The following downcast forces a compiler error, cannot be done: 
  //no: MyData_Test_ObjectJcpp* myData2 = dynamic_cast<MyData_Test_ObjectJcpp*>(myDataC);
  //
  //Instead, use as general access type:
  ObjectJcpp* obji = static_cast<ObjectJcpp*>(myData);
  ObjectJcpp* obji2 = myData;  //implicite cast also ok. 
  MyData_Test_ObjectJcpp* myData2 = dynamic_cast<MyData_Test_ObjectJcpp*>(obji);

  //
  return 0;
}



int test_publicObjectJcpp  () {

  //Check an C++ instance which has not additional data nor virtual operations:
  BaseData_Test_ObjectJc* myData2 = new BaseData_Test_ObjectJc((int)sizeof(*myData2)
    , &reflection_BaseData_Test_ObjectJc, 0
  );
  //
  ObjectJc* obj2 = &myData2->base.obj; //access immediately to the public inherited data.
                                       //
  int offsInstance_Obj2 = OFFSET_MemUnit(myData2, obj2);
  EXPECT_TRUE(offsInstance_Obj2 ==0) << "offsInstance_Obj should be ==0 because the class has not virtual table before ObjectJc-data"; 
  //
  int size_myData2 = (int)sizeof(BaseData_Test_ObjectJc);  //size of the C++ class
  int size_myDataC2 = (int)sizeof(BaseData_Test_ObjectJc_s);  //size of the C struct
  EXPECT_TRUE(size_myData2 == size_myDataC2) << "sizes should be identically because the C++ class does not define any data."; 

  (*myData2) *= 3.5f;
  EXPECT_TRUE(myData2->d2 == (234.5f * 3.5f)) <<" *= operation faulty";

  return 0;
}

int test_privateObjectJcpp  () {

  //Check an C++ instance which has not additional data nor virtual operations:
  BaseData_Test_PrivateObjectJc* myData2 = new BaseData_Test_PrivateObjectJc((int)sizeof(*myData2)
    , &reflection_BaseData_Test_ObjectJc, 0
  );
  //
  ObjectJc* obj2 = myData2->toObject(); //access immediately to the public inherited data.
                                       //
  int offsInstance_Obj2 = OFFSET_MemUnit(myData2, obj2);
  EXPECT_TRUE(offsInstance_Obj2 ==0) << "offsInstance_Obj should be ==0 because the class has not virtual table before ObjectJc-data"; 
  //
  int size_myData2 = (int)sizeof(BaseData_Test_PrivateObjectJc);  //size of the C++ class
  int size_myDataC2 = (int)sizeof(BaseData_Test_ObjectJc_s);  //size of the C struct
  EXPECT_TRUE(size_myData2 == size_myDataC2) << "sizes should be identically because the C++ class does not define any data."; 

  float result = (*myData2) *= 3.5f;
  EXPECT_TRUE(result == (234.5f * 3.5f)) <<" *= operation faulty";

  return 0;
}


int test_ObjectJcpp  () {
  STACKTRC_ENTRY("test_ObjectJcpp");
  printf("\n  test_ObjectJcpp:");
  TRY {
    test_ObjectifcBaseJcpp();
    test_publicObjectJcpp();
    test_privateObjectJcpp();
    printf("\n  - ok test_ObjectJcpp\n");
  } _TRY
  CATCH(Exception, exc) {
    EXPECT_FALSE(true)<< "Exception" ; //getMessage_ExceptionJc(exc);
    printf("\n  - exception test_ObjectJcpp\n");
  }
  END_TRY
  STACKTRC_RETURN 0;
}
