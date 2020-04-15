#ifndef HEADERGUARD_applstdef_emC_Project
#define HEADERGUARD_applstdef_emC_Project

//Projectspecific applstdef_emC.h

#define DEF_TESTALL_emC

//#define DEF_REFLECTION_OFFS
#define USE_BlockHeap_emC

//contains DEF_REFLOFFS_...for all defined ClassJc
#ifdef DEF_REFLECTION_OFFS
#  include <src_emC_Exmpl_Ctrl/genRefl/emc_Exmpl_Ctrl.reflOffs.h>
#endif



#include <emC_inclApplSpec/TargetNumericSimple/applstdef_emC.h>
#endif //HEADERGUARD_applstdef_emC_Project

