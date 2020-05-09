#ifndef HGUARD_emC_Test_ObjectJc__test_ObjectJc
#define HGUARD_emC_Test_ObjectJc__test_ObjectJc
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>



/**Any type for test based on ObjectJc. */
typedef struct MyType_Test_ObjectJc_T {
  union { ObjectJc obj; } base;
  int32 data1;
  float data2;  //respect 4.byte-boundary.
} MyType_Test_ObjectJc_s;

extern_C ClassJc const refl_MyType_Test_ObjectJc;
#define ID_refl_MyType_Test_ObjectJc 0x1fe


/**Initializer necessary for a const Object in Flash, nice for initilizing of a statically data Object in C and C++ */
#define INIZ_VAL_MyType_Test_ObjectJc( OBJ, ID, VAL1, VAL2) { { INIZ_ObjectJc(OBJ, refl_MyType_Test_ObjectJc, ID) }, VAL1, VAL2 }
//Note: Macro must not have whitespaces between Identifier and (, search String: INIZ_VAL_MyType_Test_ObjectJc ( OBJ 

/**Initializer without Values, nice for initilizing of a statically data Object in C and C++ */
#define INIZ_MyType_Test_ObjectJc(OBJ, ID, VAL1, VAL2) { { INIZ_ObjectJc(OBJ, refl_MyType_Test_ObjectJc, ID) }, 0 }
//search string: INIZ_MyType_Test_ObjectJc ( OBJ

#ifdef __cplusplus
/**For C++ usage the same as class, without any dynamic opeation here in this test. */
class MyType_Test_ObjectJc: public MyType_Test_ObjectJc_s {
  /**ctor*/
  MyType_Test_ObjectJc();
};

#endif //__cplusplus


extern_CCpp void test_ObjectJc();

extern_CCpp void test_Alloc_ObjectJc();



#endif  //HGUARD_emC_Test_ObjectJc__test_ObjectJc
