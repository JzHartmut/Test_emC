#include "emc_Test_C_Cpp/test_C_Cpp_TestemC.h"

typedef struct TestStructConst_T {
  const int x;
  int y;
} TestStructConst;

TestStructConst testDataStruct = { 123, 456 };

void test_TestStructConst(){

  testDataStruct.y = 34;
}


int a = 0;

typedef struct TestStructAB_T {
  int a, a1;
  int array[1224];
  int b, b1;
} TestStructAB;

TestStructAB testStructAB = { 0 } ;

int b = 0;

int x,y;






int array[23];

int a1, b1;

void testAccessABstatic(int val) {

  a = val;
  b = val;
  testStructAB.a1 = val;
  testStructAB.b1 = val;




  a1 = 0x3af;
  a = val;
  testStructAB.a = 0x2aa;
  testStructAB.b = 0x2ab;
}

void testabref_TestStructAB(TestStructAB* thiz, int arg) {
  thiz->a = arg;
  thiz->b = arg;
}


float get_Pi_value(){ return 3.1456f; }


MyData_s const myData = { 12, 23, 3.14f };
MyData_s myData2 = { 0 };
MyData_s myData3 = { 0, 0x16 };
MyData_s myData4 = { 12, 23, 3.14f };


#ifdef __cplusplus

float pi = get_Pi_value();
MyData_s const myData1 = { 12, 23, pi };

class TestClassAB: private TestStructAB
{
  public: void testabref(int arg) { testabref_TestStructAB(this, arg); }
};

void useClassAB(TestClassAB* data){
  int val = 123;
  data->testabref(val);
}


class Comm_Example{
  int x;
  public: Comm_Example();

  public: ~Comm_Example();
};

Comm_Example::Comm_Example(){
  this->x = 1;
}

Comm_Example::~Comm_Example(){
  this->x = 0;
}


int test_Comm_new(){

  Comm_Example* comm = new Comm_Example(); 

  delete(comm);
  return 0;
}

class X { int b; };



MyDataClass myDataClass = MyDataClass(12,23,3.14f);
//default ctor missing: MyDataClass myDataClass2;

//MyDataClass const myDataClassC = { 12, 23, 3.14f };


#endif //__cplusplus

