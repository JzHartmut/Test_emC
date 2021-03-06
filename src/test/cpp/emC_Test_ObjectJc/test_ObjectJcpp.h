#ifndef HGUARD_emC_Test_ObjectJc__test_ObjectJcpp
#define HGUARD_emC_Test_ObjectJc__test_ObjectJcpp
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>

/**Any C use-able data struct based on ObjectJc. */
typedef struct BaseData_Test_ObjectJc_T {
  union { ObjectJc obj; } base;
  
  int32 d1; //:Any data
  float d2;  //Note: padding any struct to 8-Byte-align if possible, 

} BaseData_Test_ObjectJc_s;

#define ID_refl_BaseData_Test_ObjectJc 0x102

BaseData_Test_ObjectJc_s* ctor_BaseData_Test_ObjectJc(ObjectJc* othiz);


#ifdef __cplusplus
/**The appropriate C++ class which wraps the C data: */
class MyBaseClass_Test_ObjectJcpp :
  protected BaseData_Test_ObjectJc_s               //the C data are private.
{
  /**Returns the ObjectJc base data.
  * This operation should be implemented in this form anytime. */
  public: ObjectJc* toObject() { return &this->base.obj;  }
  
  //public: ObjectJc const* const objectJc;

  public: MyBaseClass_Test_ObjectJcpp();

  protected: MyBaseClass_Test_ObjectJcpp(ObjectJc const* othiz);

  public: int32 get_d1(){ return this->d1; } //encapsulated C data.

  public: float get_d2(){ return this->d2; } //encapsulated C data.

  protected: int xt;
};

#define ID_refl_MyBaseClass_Test_ObjectJcpp 0x103


class MyClass_Test_ObjectJcpp : public MyBaseClass_Test_ObjectJcpp {

  private: float val2;

  public: MyClass_Test_ObjectJcpp(int idObj);

  public: virtual float get_val2(){ return this->val2; } //encapsulated own data

};


#define ID_refl_MyClass_Test_ObjectJcpp 0x104


/**The appropriate C++ class which wraps the C data in public form: */
class BaseData_Test_ObjectJc : public BaseData_Test_ObjectJc_s
{

  public: BaseData_Test_ObjectJc(ObjectJc const* obj, int idObj);

  //some routines or operators
  float add(){ return this->d1 + this->d2; }
  float operator*=(float arg) { this->d2 *= arg; return this->d2; }
};



/**The appropriate C++ class which wraps the C data in public form: */
class BaseData_Test_PrivateObjectJc : private BaseData_Test_ObjectJc_s
{
  /**It enables the access to objectJc via this reference. 
   * The reference must be set in ctor because it is const. */
  public: ObjectJc const* const objectJc;  

  public: BaseData_Test_PrivateObjectJc(ObjectJc const* objectJc, int idObj);

  public: ObjectJc const* toObject() { return objectJc; }
  //some routines or operators
  float add(){ return this->d1 + this->d2; }
  float operator*=(float arg) { this->d2 *= arg; return this->d2; }
};

#endif //__cplusplus

extern_C int test_ObjectJcpp ( );


#endif //HGUARD_emC_Test_ObjectJc__test_ObjectJcpp

