#ifndef HGUARD_applstdef_emC_Project
#define HGUARD_applstdef_emC_Project
#define HGUARD_applstdef_emC  //is defined here.

//Projectspecific applstdef_emC.h

#define _ALLOW_RTCc_IN_STL



/**Define the granularity of the ObjectJc base class: */
//#define DEF_ObjectJc_SIMPLEST
#define DEF_ObjectJc_SIMPLE
//#define DEF_ObjectJc_REFLREF
//#define DEF_ObjectJcpp_REFLECTION
//#define DEF_ObjectJc_OWNADDRESS

/**Define of the offering of Reflection information: */
#define DEF_REFLECTION_NO
//#define DEF_REFLECTION_SIMPLE
//#define DEF_REFLECTION_OFFS
//#define DEF_REFLECTION_FULL


//If set then the target should not use string operations
//#define DEF_NO_StringJcCapabilities


//#define USE_BlockHeap_emC

//If set then the target should not use string operations
//#define DEF_NO_StringJcCapabilities

//If set, without complex thread context, without Stacktrace
#define DEF_ThreadContext_SIMPLE

//#define DEF_Exception_TRYCpp
#define DEF_Exception_longjmp
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

//including the project specific reflOffs.h defines DEF_REFLECTION_OFFS 
#ifdef DEF_REFLECTION_OFFS
  //contains DEF_REFLOFFS_...for all defined ClassJc
  #include <emC_Exmpl_Ctrl/genRefl/emc_Exmpl_Ctrl.reflOffs.h>
  //Note: the adequate *.reloffs.c should be part of the project:
#elif defined(DEF_REFLECTION_FULL)
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif





#include <compl_adaption.h>

/**Include Object_emC in the proper way: */
#ifdef DEF_ObjectJc_Simplest
  #include <emC/Base/ObjectSimple_emC.h>
#else 
  #include <emC/Base/Object_emC.h>
#endif

#include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>

#include <emC/Base/Exception_emC.h>

#define kMaxPathLength_FileDescription_OSAL 512
#define sizeSafetyArea_allocMemC 256

//only for this test application:
extern_C void outTestConditions ( );

#endif //HGUARD_applstdef_emC_Project

