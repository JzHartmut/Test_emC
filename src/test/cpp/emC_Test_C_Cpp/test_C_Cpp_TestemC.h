#ifndef HEADERGUARD_test_C_Cpp_TestemC
#include <applstdef_emC.h>

typedef struct MyData_T { int a, b; float f; } MyData_s;

extern MyData_s const myData, myData1;

extern_C float getData_const();

extern_C void main_test_C_Cpp ( );

#ifdef __cplusplus
class MyDataClass {
  int a, b; float f;

  public: MyDataClass(int a, int b, float f) {
    this->a = a; this->b = b; this->f = f;
  }

  public: void set_f(float f){ this->f = f; }
};
#endif //__cplusplus

#endif
