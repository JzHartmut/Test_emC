#ifndef HGUARD_applstdef_emC_Project
#define HGUARD_applstdef_emC_Project

//Projectspecific applstdef_emC.h

//#define _ALLOW_RTCc_IN_STL

//#define DEF_ObjectJc_SIMPLE
//#define DEF_ObjectJc_REFLREF
//#define DEF_ObjectJcpp_REFLECTION
//#define DEF_ObjectJc_OWNADDRESS

//#define DEF_ClassJc_Vtbl 

//#define DEF_NO_StringJcCapabilities



//#define USE_BlockHeap_emC

//If set, without complex thread context, without Stacktrace
//#define DEF_ThreadContext_SIMPLE
//#define DEF_Exception_TRYCpp
//#define DEF_Exception_longjmp
//#define DEF_Exception_NO


//If set, no assertion is done:
//#define ASSERT_IGNORE_emC


//
//What to start as main:
//
#define DEF_TESTALL_emC
//#define DEF_MAIN_emC_TestAll_testSpecialMain
//#define DEF_MAIN_testMain_ObjectJc
//#define DEF_MAIN_TestCtrl_emC

//#define DEF_REFLECTION_FULL
//including the project specific reflOffs.h defines DEF_REFLECTION_OFFS 
//                                               if DEF_REFLECTION_FULL is not set
//#include <emC_Exmpl_Ctrl/genRefl/emc_Exmpl_Ctrl.reflOffs.h>
#ifdef DEF_REFLECTION_FULL
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif

#ifdef DEF_REFLECTION_OFFS
  //contains DEF_REFLOFFS_...for all defined ClassJc
  //Note: the adequate *.reloffs.c should be part of the project:
#endif


#include <compl_adaption.h>
#include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>

  #include <emC/Base/Exception_emC.h>

#define kMaxPathLength_FileDescription_OSAL 512
#define sizeSafetyArea_allocMemC 256

#endif //HGUARD_applstdef_emC_Project

