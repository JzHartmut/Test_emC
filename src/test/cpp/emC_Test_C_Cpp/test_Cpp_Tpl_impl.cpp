#include <applstdef_emC.h>
#include "emc_Test_C_Cpp/test_Cpp_Tpl.h"
#include "emc_Test_C_Cpp/test_Cpp_Tpl_priv.h"




//bool DataMng<T>::addData(T *) {
//}


DataMngBase::DataMngBase ( int capacityArg
    , DataRecordBase* dataSet, int sizeElement) {
  this->zData = 0;
  this->capacity = capacityArg;
  ASSERT_emC(sizeElement == sizeof(DataRecordBase)
             , "faulty data record size", 0, 0);
  DataRecordBase emptyRecord = { -1, 0, null};
  for(int ix = 0; ix < this->capacity; ++ix) {
    dataSet[ix] = emptyRecord; //(memcpy)
  }
}


bool DataMngBase::addData_Base ( void* userData, DataRecordBase* dataSet, long time, long score) {
  if(this->zData >=100) return false;
  DataRecordBase* entry = &dataSet[this->zData];
  entry->userData = userData;
  entry->time = time;
  entry->score = score;
  this->zData +=1;
  return true;
}



void* DataMngBase::getNewestOk_Base ( DataRecordBase* dataSet) {
  return this->zData == 0 ? null
      : dataSet[0].userData;  //...simple impl.
}



int DataMngBase::size() {
  return this->zData;
}

