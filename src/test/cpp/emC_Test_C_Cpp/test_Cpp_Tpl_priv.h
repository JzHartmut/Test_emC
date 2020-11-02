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



/**One record in the container
 * with the referenced user data as void*
 * and additional information to evaluate. */
typedef struct DataRecordBase_T {
  long time;
  long score;
  void* userData;
} DataRecordBase;


/**One record in the container
 * with the referenced user data
 * and additional information to evaluate. */
template<typename T> struct DataRecord {
  long time;
  long score;
  T* userData;
};



class DataMngBase {
  protected: int zData;
  protected: int capacity;

  protected: DataMngBase(int capacityArg
       , DataRecordBase* dataSet, int sizeElement);

  protected: bool addData_Base(void* userData
       , DataRecordBase* dataSet, long time, long score);

  public: int size();

  protected: void* getNewestOk_Base(DataRecordBase* dataSet);

};






/**The container class itself. */
template<typename T, int capacityArg>
class DataMng
: public DataMngBase {

  DataRecord<T> data[capacityArg];

  public: DataMng() : DataMngBase(capacityArg
      , reinterpret_cast<DataRecordBase*>(this->data)
      , sizeof(this->data[0]) //to check element type
      ) { }

  public: bool addData(T* userData, long time, long score) {
    return addData_Base(userData, reinterpret_cast<DataRecordBase*>(this->data), time, score);
  }

  public: T* getNewestOk() {
    return static_cast<T*>(getNewestOk_Base(reinterpret_cast<DataRecordBase*>(this->data)));
  }

};






template<typename TType> 
inline TType min_Simple(TType a, TType b) {
  return (a < b) ? a : b;
}

template<typename TType> 
inline TType max_Tpl(TType a, TType b);




#endif //HGUARD_test_Cpp_Tpl_priv

