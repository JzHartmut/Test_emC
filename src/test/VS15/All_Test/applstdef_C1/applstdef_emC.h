#ifndef HEADERGUARD_applstdef_emC_Project
#define HEADERGUARD_applstdef_emC_Project

//Projectspecific applstdef_emC.h

//#define DEF_REFLECTION_OFFS
#define USE_BlockHeap_emC
#define DEF_ObjectJc_REFLREF
//#define DEF_ObjectJc_FULL

#define DEF_TESTALL_emC


//contains DEF_REFLOFFS_...for all defined ClassJc
#ifdef DEF_REFLECTION_OFFS
  //Note: the adequate *.reloffs.c should be part of the project:
  #include <src_emC_Exmpl_Ctrl/genRefl/emc_Exmpl_Ctrl.reflOffs.h>
#endif

#ifdef DEF_ObjectJc_FULL
#  include <emC_inclApplSpec/applJcpp_emC/applstdef_emC.h>
#else
#  include <emC_inclApplSpec/TargetNumericSimple/applstdef_emC.h>
#endif
#endif //HEADERGUARD_applstdef_emC_Project

