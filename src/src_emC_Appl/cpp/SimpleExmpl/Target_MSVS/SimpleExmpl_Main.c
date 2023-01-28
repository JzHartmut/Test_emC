#include <applstdef_emC.h>
#include <SimpleExmpl/SimpleExmpl_ApplCpp.h>
#include <SimpleExmpl/SimpleExmpl_Appl.h>
#include <emC/Base/StringNum_emC.h>
#include <stdio.h>
#include <stdlib.h>  //malloc

//global reference of the application data. Only one is admissble.
                            


extern_C void main_C ( void );

extern_C void main_Cpp ( );


void main(int nCmdArgs, char** sCmdArgs) {
  #if defined(DEF_cplusplus_emC) && defined(__cplusplus)

    main_Cpp();
  #else
    main_C();
  #endif
}






#if !defined(DEF_cplusplus_emC) || !defined(__cplusplus)

/**Static data definition for the application. */
SimpleNumExmpl_s dataC = INIZ_SimpleNumExmpl(dataC);

/**Independent static data definition for a referenced module,
 * may be a derived type also, hence references in the application data. */
ModuleB_s modB = INIZ_ModuleB(modB, 3.5f);



void main_C(void) {
  //This is only for PC simulation, Visual studio
  //ModuleB_s* dataB = ctor_ModuleB(ALLOC_ObjectJc( sizeof(ModuleB_s ), refl_ModuleB, 0), 3.5f);     // initializing before main, set breakpoint in Ctor,
  SimpleNumExmpl_s* thiz = ctor_SimpleNumExmpl(&dataC.base.obj, &modB);
  float val = -2.0f;
  bool bInitDone;
  do {
    bInitDone = init_SimpleNumExmpl(thiz);                   // a repeated call of init till the condition is met.
    val += 1.0f;
  } while(!bInitDone);
  
  printf("is intialized: %f\n", thiz->modA.mVal);
  //
  int stepCt = 0;
  while(++stepCt < 10) {               // this loop emulates the stepping thread or interrupt. 
    step_SimpleNumExmpl(thiz, (float)stepCt * 0.15f);
    #ifndef DEF_NO_StringUSAGE 
      printf("step: %s\n", thiz->bufferResult);
    #else  //def DEF_NO_StringUSAGE, then the application cannot String, but for PC test use printf
      printf("step: %3.2f\n", thiz->modA.y);
    #endif
  }
  //free_MemC(dataB);
}

#endif  // not DEF_cplusplus_emC



void* alloc_MemC(int size) { return malloc(size); }                      

extern_C int free_MemC(void const* addr) { 
  if(addr !=null) {
    free((void*)addr); 
  }
  return 0; 
}






#ifdef DEF_NO_ObjectJc_emC

ObjectJc* alloc_ObjectJc_verySimple_emC(int size, int id) {
  ObjectJc* othiz = C_CAST(ObjectJc*, alloc_MemC(size));
  othiz->identSize = id;
  return othiz;
}
#endif  //DEF_NO_ObjectJc_emC
