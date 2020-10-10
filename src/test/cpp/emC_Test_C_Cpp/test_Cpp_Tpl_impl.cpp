#include "test_Cpp_Tpl.h"
#include "test_Cpp_Tpl_priv.h"




//bool DataMng<T>::addData(T *) {
//}


DataMngBase::DataMngBase(int capacityData) {
  this->ixData = 0;
  this->capacityData = capacityData;
}


bool DataMngBase::addData_Base(void* data, DataSetBase* dataSet, long time, long score) {
  if(this->ixData >=100) return false;
  DataSetBase* entry = &dataSet[this->ixData];
  entry->data = data;
  entry->date = time;
  entry->score = score;
  this->ixData +=1;
  return true;
}





int DataMngBase::size() {
  return this->ixData;
}

