#ifndef HGUARD_emC_Test_ObjectJc__test_ObjectJc
#define HGUARD_emC_Test_ObjectJc__test_ObjectJc
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>



/**Any type for test based on ObjectJc. */
typedef struct MyBaseType_Test_ObjectJc_T {
  union { ObjectJc obj; } base;
  int32 data1;
  float data2;  //respect 4.byte-boundary.
} MyBaseType_Test_ObjectJc_s;

/**Initializer necessary for a const Object in Flash, nice for initilizing of a statically data Object in C and C++ */
#define INIZ_VAL_MyBaseType_Test_ObjectJc( OBJ, REFL, ID, VAL) \
  { { INIZ_ObjectJc(OBJ, REFL, ID) } \
  , (int32)VAL, (float)VAL \
  }
//Note: Macro must not have whitespaces between Identifier and (, 

extern_C void ctor_MyBaseType_Test_ObjectJc(MyBaseType_Test_ObjectJc_s* thiz, float val);


typedef struct InnerData_Test_ObjectJc_T {
  float x,y,z; 
} InnerData_Test_ObjectJc;

#define INIZ_InnerData_Test_ObjectJc( ) \
  { 3.14f, 42.0f, -3.0f }  //it is only a const initizalization

extern_C void ctor_InnerData_Test_ObjectJc(InnerData_Test_ObjectJc* thiz);


typedef struct MyType_Test_ObjectJc_T {
  union { MyBaseType_Test_ObjectJc_s MyBaseType_Test_ObjectJc; ObjectJc obj; } base;
  int32 m, n;
  InnerData_Test_ObjectJc data1;
  int p,q;
} MyType_Test_ObjectJc_s;

#define ID_refl_MyType_Test_ObjectJc 0x1fe
#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_MyType_Test_ObjectJc;
#endif


/**Initializer necessary for a const Object in Flash, nice for initilizing of a statically data Object in C and C++ */
#define INIZ_VAL_MyType_Test_ObjectJc( OBJ, ID, VAL1, VAL2) \
{ { INIZ_VAL_MyBaseType_Test_ObjectJc(OBJ, refl_MyType_Test_ObjectJc, ID, VAL1) } \
, VAL2, -(VAL2) \
, INIZ_InnerData_Test_ObjectJc() \
, 0,0 \
}

/**Construction on runtime. */
extern_C void ctor_MyType_Test_ObjectJc(MyType_Test_ObjectJc_s* thiz, float val1, int32 val2);


#ifdef __cplusplus
/**For C++ usage the same as class, without any dynamic opeation here in this test. */
class MyType_Test_ObjectJc: public MyType_Test_ObjectJc_s {
  /**ctor*/
  MyType_Test_ObjectJc();
};

#endif //__cplusplus


extern_CCpp void test_ObjectJc ( );

extern_CCpp void test_Alloc_ObjectJc ( );

extern_CCpp void test_ctor_ObjectJc ( );


#endif  //HGUARD_emC_Test_ObjectJc__test_ObjectJc
