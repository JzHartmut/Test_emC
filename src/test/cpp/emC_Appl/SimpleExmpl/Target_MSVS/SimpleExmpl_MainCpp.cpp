#include <applstdef_emC.h>
#include <SimpleExmpl/SimpleExmpl_ApplCpp.h>
#include <stdio.h>
#include <stdlib.h>  //malloc

//global reference of the application data. Only one is admissble.
                            
extern_C void main_Cpp ( );



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)

//=== static data of the application
static SimpleNumExmpl* dataCpp;        // anchor for the whole data of the application which are created in heap.

ModuleB dataB(3.5f);                   // initialized before main, set breakpoint in Ctor,

//=== main for PC base and C++:
void main_Cpp(void) {                  // note: main() itself is in SimpleExmpl_Main.c and calls this.
  dataCpp = new SimpleNumExmpl(&dataB);// needs the aggregate to construct
  float val = -2.0f;
  bool bInitDone;
  do {
    bInitDone = dataCpp->init();       // a repeated call of init till the condition is met.
    val += 1.0f;
  } while(!bInitDone);
  
  printf("is intialized: %f\n", dataCpp->getMultVal());
  //
  int stepCt = 0;
  while(++stepCt < 10) {               // this loop emulates the stepping thread or interrupt. 
    dataCpp->step((float)stepCt * 0.15f);
    printf("step: %f\n", dataCpp->getResult());
  }
  delete dataCpp;
}
#endif  //DEF_cplusplus_emC




