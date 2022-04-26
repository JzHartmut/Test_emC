#ifndef HGUARD_SimpleNumExmpl
#define HGUARD_SimpleNumExmpl
#include <applstdef_emC.h>



/**This is one module of the application. Also for pure C programming*/
typedef struct ModuleA_T {
  union { ObjectJc obj; } base;

  float cVal, mVal, y;

} ModuleA_s;


#define INIZ_ModuleA(THIZ, constVal) { INIZ_ObjectJc(THIZ, refl_ModuleA, 0), constVal, 0, 0 }


//------ C-Prototypes for the module (ObjOrient in C)

/**Constructor on startup time. */
extern_C ModuleA_s* ctor_ModuleA(ObjectJc* othiz, float constVal);

/**Initialization after startup before run. */
extern_C bool init_ModuleA(ModuleA_s* thiz, float initVal);

/**The step operation for run time. */
extern_C void step_ModuleA(ModuleA_s* thiz, float val);

#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
                         // Support for C++ programming
/**A wrapper for C++ usage of this ModuleA.*/
class ModuleA: private ModuleA_s {
 // Hint: only a wrapper, no own data and functionality,
 // because the ModuleA should be able to use in pure C too.

 /**C++ constructor only with a given initial value (no default ctor).*/
 public: ModuleA(float constVal);

 /**Access to the ObjectJc base. */ 
 public: ObjectJc* getObject() { return &this->base.obj; }

 /**Access to the C basic data, only for C-operations. */ 
 public: ModuleA_s* get_sdata() { return this; }

 //---- wrapper arround all operations of this ModuleA:
 public: bool init(float initVal) { return init_ModuleA(this, initVal); }

 public: void step(float val) { step_ModuleA(this, val); }

 //---- access (getter) to the encapsulated data, only to necessary data. 
 public: float getConstVal() { return cVal; }

 public: float getMultVal() { return mVal; }

 public: float getResult() { return y; }

};
#endif


/**This is a second module of the application. Also for pure C programming*/
typedef struct ModuleB_T {
  union { ObjectJc obj; } base;

  /**This is a aggregation to the ModuleA, wired on init time before step.*/
  struct ModuleA_T* refA;
  
  float cVal, mVal, y;

} ModuleB_s;

#define INIZ_ModuleB(THIZ, constVal) { INIZ_ObjectJc(THIZ, refl_ModuleB, 0), null, constVal, 0, 0 }

//------ C-Prototypes for the module_B (ObjOrient in C)

/**Constructor on startup time. */
extern_C ModuleB_s* ctor_ModuleB(ObjectJc* othiz, float constVal);

/**Initialization after startup before run. */
extern_C bool init_ModuleB ( ModuleB_s* thiz, struct ModuleA_T* refA);

/**The step operation for run time. */
extern_C void step_ModuleB ( ModuleB_s* thiz, float val);

INLINE_emC float getResult_ModuleB ( ModuleB_s* thiz ) { return thiz->y; }


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
                         // Support for C++ programming
/**A wrapper for C++ usage of this ModuleB.*/
class ModuleB: private ModuleB_s {
 // Hint: only a wrapper, no own data and functionality,
 // because the ModuleB should be able to use in pure C too.

 /**Access to the ObjectJc base. */ 
 public: ObjectJc* getObject() { return &this->base.obj; }

 /**C++ constructor only with a given initial value (no default ctor).*/
 public: ModuleB(float constVal);

 //---- wrapper arround all operations of this ModuleB:
 public: bool init(ModuleA* refA);

 public: void step(float val) { step_ModuleB(this, val); }

 //---- access (getter) to the encapsulated data, only to necessary data. 
 public: float getConstVal() { return cVal; }

 public: float getMultVal() { return mVal; }

 public: float getResult() { return getResult_ModuleB(this); }

};
#endif



#endif //HGUARD_SimpleNumExmpl
