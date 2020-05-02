#ifndef __Test_Ctrl_h__
#define __Test_Ctrl_h__

//should be the first include!
#include <applstdef_emC.h>



//The ObjectJc base class is used. In an situation of TargetNumericSimple the following include is prevented
//because the guard  __ObjectJc_simple__ is set in  ObjectJc_simple.h included in TargetNumericSimple/applstdef_emC.h
//In another compilation situation this file is necessary and included.
#include <emC/Base/Object_emC.h>

#include <emC/Ctrl/pid_Ctrl.h>

/**A base class to demonstrate which is single inherition in C, for this simpe example. */
typedef struct Test_Ctrl_t {
  /**The struct is based on ObjectJc. In the compilation situation of targetNumericSimple
  * that is only a struct with 2 int32 elements. 
  * Use the notation with union ... base to unify the access
  */
  union { ObjectJc object; } base;

  /**It is 1 on startup. Set to 0 to abort the execution. */
  int32 bRun : 1;

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

  Par_PID_Ctrl_s par;

  PID_Ctrl_s pid;


} Test_Ctrl;

#ifndef ID_refl_Test_Ctrl //may be centralized definined via project specific applstdef_emC.h or in ...refloffs.h
  #define ID_refl_Test_Ctrl 0x301
#endif
extern_C ClassJc const refl_Test_Ctrl;

/**CONST initializer to abstract the usage from the nested complex struct. Only this definition have to be match to the struct nesting. */
#define INIZ_Test_Ctrl(OBJ, ID) { { INIZ_objReflId_ObjectJc(OBJ, refl_Test_Ctrl, ID)}}

/**The constructor to initialize allocated data or static data with calculated values: */
Test_Ctrl* ctor_Test_Ctrl(ObjectJc* othiz);


/**Calculates y = a*b; with 1 ms delay in the main thread.
 * It ends if bRun is set to 0 via external reflection access.
 */
void calculateInLoop_Test_Ctrl(Test_Ctrl* thiz);





#endif //__Test_Ctrl_h__
