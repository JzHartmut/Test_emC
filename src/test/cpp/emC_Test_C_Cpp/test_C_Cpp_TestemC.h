#ifndef HEADERGUARD_test_C_Cpp_TestemC


typedef struct MyData_T { int a, b; float f; } MyData_s;

extern MyData_s const myData, myData1;

float getData_const();

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
