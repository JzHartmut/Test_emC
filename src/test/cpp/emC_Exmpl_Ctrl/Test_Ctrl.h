#ifndef __Test_Ctrl_h__
#define __Test_Ctrl_h__

//should be the first include!
#include <applstdef_emC.h>



//The ObjectJc base class is used. In an situation of TargetNumericSimple the following include is prevented
//because the guard  __ObjectJc_simple__ is set in  ObjectJc_simple.h included in TargetNumericSimple/applstdef_emC.h
//In another compilation situation this file is necessary and included.
#include <emC/Base/Object_emC.h>

#include <emC/Ctrl/PIDf_Ctrl_emC.h>


/**A base class to demonstrate which is single inherition in C, for this simpe example. */
typedef struct Base_Test_Ctrl_t {
  /**The struct is based on ObjectJc. In the compilation situation of targetNumericSimple
  * that is only a struct with 2 int32 elements. 
  * Use the notation with union ... base to unify the access
  */
  union { ObjectJc object; } base;

  /**It is 1 on startup. Set to 0 to abort the execution. */
  int32 bRun : 1;

} Base_Test_Ctrl_s;


/**A base class to demonstrate which is single inherition in C, for this simpe example. */
typedef struct Test_Ctrl_T {
  /**The struct is based on ObjectJc. In the compilation situation of targetNumericSimple
  * that is only a struct with 2 int32 elements. 
  * Use the notation with union ... base to unify the access
  */
  union { Base_Test_Ctrl_s super; ObjectJc object; } base;

  /**Reference value. */
  float ws;

  /**A smoothing factor. */
  float fT1;

  /**growth factor per step*/
  float fs;

  /**state value, a smoothing. */
  double sT1;

  /**state values, an integrator.*/
  double sI;

  float s;

  Par_PIDf_Ctrl_emC_s par;

  PIDf_Ctrl_emC_s pid;


} Test_Ctrl_s;



#ifndef ID_refl_Test_Ctrl //may be centralized definined via project specific applstdef_emC.h or in ...refloffs.h
  #define ID_refl_Test_Ctrl 0x301
  #define ID_refl_Base_Test_Ctrl 0x302
#endif

#ifndef DEF_REFLECTION_NO
extern_C ClassJc const refl_Base_Test_Ctrl;
extern_C ClassJc const refl_Test_Ctrl;
#endif

/**CONST initializer to abstract the usage from the nested complex struct. Only this definition have to be match to the struct nesting. */
#define INIZ_Test_Ctrl(OBJ, ID) { { INIZ_ObjectJc(OBJ, refl_Test_Ctrl, ID)}}

/**The constructor to initialize allocated data or static data with calculated values: */
//extern_CCpp 
Test_Ctrl_s* ctor_Test_Ctrl ( ObjectJc* othiz, ThCxt* _thCxt);


/**Algorithm of initialization. It should be invoked before any step, 
 * 
 */
extern_C void init_Test_Ctrl(Test_Ctrl_s* thiz);

/**Algorithm of the fast step cycle, it should be invoked strongly time cyclically, 
 * for example in a hardware interrupt of a controller. 
 */
extern_C void step_Test_Ctrl(Test_Ctrl_s* thiz);

/**Algorithm of the slow step cycle for parametrizing or such. 
 * It should be invoked enough often, not strongly, 
 * for example in the back loop of a controller or in a slower thread if a RTOS is used.  
 */
extern_C void stepSlow_Test_Ctrl(Test_Ctrl_s* thiz);


#if defined(__cplusplus) && defined(DEF_cplusplus_emC)
/**
 */
class Test_Ctrl : protected Test_Ctrl_s {
  //Writing hint: use public for any member as in Java.

  /**The ctor. Because it may be a base class and the ObjectJc part should be initialize firstly 
   * with the instance data, the reference to the own ObjectJc is required. 
   * @arg othiz you can deliver null, then the ObjectJc initialization are done with the given this as instance. 
   */
  public: Test_Ctrl(ObjectJc* othiz);

  /**Explicitely destructor. Note: Do not define it as virtual, prevent virtual.
   * But: never use a pointer to a base class to delete an instance.
   */
  public: ~Test_Ctrl();

  /**Gets the ObjectJc part, for public access.*/
  public: ObjectJc const* object ( ) { return &this->base.object; }

  /**Step routine for the cyclically controller functionality. */
  public: void step ( ) { step_Test_Ctrl(this); }  //hint: calls the C routine. 

  /**Step routine for parametrizing, for a slow cycle. */
  public: void stepSlow ( ) { stepSlow_Test_Ctrl(this); }  //hint: calls the C routine. 

  /**Access to the variable run. Note: It may be clear be an inspector access. */
  public: bool run ( ) { return this->base.super.bRun !=0; }

  /**Access to the controlled value. */
  public: float get_s() { return this->s; }

  /**Only a test routine. Not necessary for operation. */
  public: bool test_Initialized();
};
#endif




#endif //__Test_Ctrl_h__
