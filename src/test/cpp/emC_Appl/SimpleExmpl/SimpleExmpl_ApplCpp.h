#ifndef HGUARD_SimpleNumExmpl_ApplCpp
#define HGUARD_SimpleNumExmpl_ApplCpp
#include <applstdef_emC.h>             // clarify which application definitions
#include <SimpleExmpl/SimpleExmpl_Modules.h>    // include of dependencies

//Hint: This is an alternative or concurrent to SimpleNumExmpl_Appl.h as C implementation. 
//      Do not confuse both, use only one!


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
   //it contains C++ code, do not compile per accident in C environment. 


class SimpleNumExmpl : private ObjectJc {

  //--- Consist of this modules:
  /**Module B for other and that Note: Also a composite but otherwhere located.*/
  ModuleB& modB;

  /**Module A for that and that. Note: It is a composite of this class. */
  ModuleA modA;

  /**The construction needs the instance of ModuleB, it can be also derived. 
   * The referenced instance can be gotten from a factory pattern due to other conditions....
   */
  public: SimpleNumExmpl ( ModuleB* modB);

  public: ObjectJc* getObject () { return this; }

  public: bool init ( );
  public: void step ( float val );

  public: float getMultVal ( ) { return modA.getMultVal(); }

  public: float getResult ( ) { return modA.getResult(); }
};




#endif  //__cplusplus
#endif //HGUARD_SimpleNumExmpl_Appl
