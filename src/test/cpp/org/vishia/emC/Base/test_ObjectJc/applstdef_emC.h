#ifndef HEADERGUARD_applstdef_USER
#define HEADERGUARD_applstdef_USER




#ifdef DEF_ObjectJc_SIMPLE
  #define DEF_REFLECTION_SIMPLE
  #define DEF_ObjectJc_REFLREF


  #include <emC/incApplSpecific/TargetNumericSimple/applstdef_emC.h>
#else 
  #include <emC/incApplSpecific/stdef_ApplCpp64/applstdef_emC.h>
#endif


#endif //HEADERGUARD_applstdef_USER

