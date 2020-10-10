#include "test_Cpp_Tpl.h"
#include "test_Cpp_Tpl_priv.h"


void test_MinTpl() {

  float a = 5.1f;
  float b = 51.0f / 10.0f;
  int ai = 6;
  int bi = 5;
  short bs = 3;
  float c = min_Tpl(a, b);
  float d = max_Tpl(a, b);
  int di = max_Tpl(ai, bi);
  c = Cmp_Tpl<float>::min(a,bs);  //bi produce a warning convert int to float

}


template<typename TType> TType max_Tpl(TType a, TType b){
  if (a > b) return a;
  else return b;
}


typedef struct Data_A_T { float x; } Data_A;


int test_DataMng() {

  DataMng<Data_A, 10> mng1;  //calls ctor for the instance
  
  Data_A data1 = { 5.0f};

  mng1.addData(&data1, 0,0);

  return mng1.size();
}



template<typename T, int capacity> DataMng<T, capacity>::DataMng() 
: DataMngBase(capacity) {
 
}







