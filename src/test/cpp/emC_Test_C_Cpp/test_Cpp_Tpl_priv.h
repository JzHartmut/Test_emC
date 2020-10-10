#ifndef HGUARD_test_Cpp_Tpl_priv
#define HGUARD_test_Cpp_Tpl_priv


template<typename T> class Cmp_Tpl {

  public: static T min(T a, T b) {
    if(a < b) return a;
    else return b;
  }

  public: static T max(T a, T b) {
    if (a > b) return a;
    else return b;
  }

};




typedef struct DataSetBase_T {
  long date;
  long score;
  void* data;
} DataSetBase;

template<typename T> struct DataSetTpl {
  long date;
  long score;
  T* data;
};



class DataMngBase {
  int ixData;
  int capacityData;

  public: DataMngBase(int capacityData);

  protected: bool addData_Base(void* data, DataSetBase* dataSet, long time, long score);

  public: int size();

  protected: void* getNewestOk_Base();

};







template<typename T, int capacity> class DataMng 
: public DataMngBase {


  DataSetTpl<T> data[capacity];
  

  public: DataMng();

  public: bool addData(T* data, long time, long score) {
    return addData_Base(data, reinterpret_cast<DataSetBase*>(data), time, score);
  }


  public: T* getNewestOk() {
    return static_cast<T*>(getNewestOk_Base());
  }

};





template<typename TType> 
inline TType min_Tpl(TType a, TType b) {
  if(a < b) return a;
  else return b;
}

template<typename TType> 
inline TType max_Tpl(TType a, TType b);




#endif //HGUARD_test_Cpp_Tpl_priv

