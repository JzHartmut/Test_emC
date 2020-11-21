#include <applstdef_emC.h>
#include "emc_Test_C_Cpp/test_Cpp_Tpl.h"
#include "emc_Test_C_Cpp/test_Cpp_Tpl_priv.h"


void test_MinTpl() {

  float a = 5.1f;
  float b = 51.0f / 10.0f;
  int ai = 6;
  int bi = 5;
  short bs = 3;
  float c = min_Simple<float>(a, b);
  float d = max_Tpl(a, b);
  int di = max_Tpl(ai, bi);
  c = Cmp_Tpl<float>::min(a,bs);  //bi produce a warning convert int to float

}


template<typename TType> TType max_Tpl(TType a, TType b){
  if (a > b) return a;
  else return b;
}

//Define a data type for test template
//and some data records to add
typedef struct Data_A_T { float x; } Data_A;

//The Data Manager reference
DataMng<Data_A, 10>* mngA = null;

//Some example data
Data_A dataA1 = { 5.1f};
Data_A dataA2 = { 7.2f};


//Define another data type
//and some data records to add
typedef struct Data_B_T { int a,b; } Data_B;

DataMng<Data_B, 23>* mngB = null;

Data_B dataB1 = { 1, 123};
Data_B dataB2 = { 2, 456};

void test_init_DataMng ( ) { //may thrown an exception
  mngA = new DataMng<Data_A,10>();
  mngB = new DataMng<Data_B,23>();
}

float test_DataMng ( ) {
  //add data to the container.
  //selecting a faulty container cause an error
  //better than void* would be used.
  mngA->addData(&dataA1, 12345, 0xaa);
  mngA->addData(&dataA2, 12345, 0xbf);
  //
  mngB->addData(&dataB1, 12345, 0x82);
  mngB->addData(&dataB2, 12345, 0x01);
  //Access to the container.
  //delivers the correct type.
  Data_A* dataAok = mngA->getNewestOk();
  Data_B* dataBok = mngB->getNewestOk();
  //do anything with the result.
  return dataAok->x + dataBok->a;
}









