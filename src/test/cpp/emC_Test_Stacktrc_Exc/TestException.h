#ifndef __TestNumericSimple_h__
#define __TestNumericSimple_h__

//should be the first include!
#include <applstdef_emC.h>

#define __DONOTUSE_INSPECTOR__

//The ObjectJc base class is used. In an situation of TargetNumericSimple the following include is prevented
//because the guard  __ObjectJc_simple__ is set in  ObjectJc_simple.h included in TargetNumericSimple/applstdef_emC.h
//In another compilation situation this file is necessary and included.
#include <emC/Base/Object_emC.h>



/**A base class to demonstrate which is single inherition in C, for this simpe example. */
typedef struct MyBaseData_t {
  /**The struct is based on ObjectJc. In the compilation situation of targetNumericSimple
  * that is only a struct with 2 int32 elements. 
  * Use the notation with union ... base to unify the access
  */
  union { ObjectJc object; } base;

  /**It is 1 on startup. Set to 0 to abort the execution. */
  int32 bRun : 1;

} MyBaseData;

/**CONST initializer to abstract the usage from the nested complex struct. Only this definition have to be match to the struct nesting. */
#define INIZ_MyBaseData(OBJ, REFL) { { INIZ_ObjectJc(OBJ, REFL, 0)}, 1}


typedef struct MyData_t {
  /**It is the super class for this type. */
  union { MyBaseData super; ObjectJc object; } base;

  /**Input values.*/
  float a,b;

  /**An output value will be calculated with a*b. */
  float y;

  float array[10];

  float testThrowResult;

} MyData;

/**CONST initializer to abstract the usage from the nested complex struct. Only this definition have to be match to the struct nesting. */
#define INIZ_MyData(OBJ, TYPE) { { INIZ_MyBaseData(OBJ, TYPE)}, 3.5f, 7.4f, 0 }

#define ID_refl_MyData 0x401

/**The constructor to initialize allocated data or static data with calculated values: */
MyData* ctor_MyData(MyData* thiz);


bool test_MyData ( MyData* thiz, float val);

/**This routine contains a TRY...CATCH and continues work. */
float testTry(MyData* thiz);

/**It is a called routine from TRY level without catch.*/
float testTryLevel2(MyData* thiz, ThCxt* _thCxt);

/**This routine throws on faulte index respectively does an replacing code. 
 * @return a value calculated.
 */
float testThrow(MyData* thiz, uint ix, float val, ThCxt* _thCxt);


extern_C int test_Exception ( );



#endif //__TestNumericSimple_h__
