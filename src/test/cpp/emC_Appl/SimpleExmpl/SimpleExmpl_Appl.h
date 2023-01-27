#ifndef HGUARD_SimpleNumExmpl_Appl
#define HGUARD_SimpleNumExmpl_Appl
#include <applstdef_emC.h>
#include <SimpleExmpl/SimpleExmpl_Modules.h>


typedef struct SimpleNumExmpl_T {
  union { ObjectJc obj; } base;

  //--- Consist of this modules:
  /**Module B for other and that Note: Also a composite but otherwhere located.*/
  struct ModuleB_T* modB;

  /**Module A for that and that. Note: It is a composite of this class. */
  ModuleA_s modA;

  #ifndef DEF_NO_StringUSAGE 
    /**A buffer to present a numeric result. */
    char bufferResult[10];
  #endif //ndef DEF_NO_StringUSAGE 

} SimpleNumExmpl_s;


#define INIZ_SimpleNumExmpl(THIZ) { INIZ_ObjectJc(THIZ, refl_SimpleNumExmpl, 0), null, INIZ_ModuleA((THIZ).modA, 2.0f) } 



/**The construction needs the instance of ModuleB, it can be also derived. 
  * The referenced instance can be gotten from a factory pattern due to other conditions....
  */
SimpleNumExmpl_s* ctor_SimpleNumExmpl ( ObjectJc* othiz, ModuleB_s* modB);


bool init_SimpleNumExmpl ( SimpleNumExmpl_s* thiz );

void step_SimpleNumExmpl ( SimpleNumExmpl_s* thiz, float val );





#endif //HGUARD_SimpleNumExmpl_Appl
