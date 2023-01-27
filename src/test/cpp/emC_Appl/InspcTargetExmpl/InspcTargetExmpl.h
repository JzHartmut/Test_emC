#ifndef HGUARD_InspcTargetExmpl
#define HGUARD_InspcTargetExmpl
#include <emC/Base/Object_emC.h>

typedef struct InspcTargetExmpl_T {

  union { ObjectJc obj; } base;

  int32 bRun;

  float x,y;

} InspcTargetExmpl_s;


#endif //HGUARD_InspcTargetExmpl
