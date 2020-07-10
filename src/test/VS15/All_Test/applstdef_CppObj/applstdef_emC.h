#ifndef HEADERGUARD_applstdef_emC_Project
#define HEADERGUARD_applstdef_emC_Project

//Projectspecific applstdef_emC.h

#define _ALLOW_RTCc_IN_STL

//#define DEF_REFLECTION_FULL
//including the project specific reflOffs.h defines DEF_REFLECTION_OFFS 
//    if DEF_REFLECTION_FULL is not set
//#include <emC_Exmpl_Ctrl/genRefl/emc_Exmpl_Ctrl.reflOffs.h>
#ifdef DEF_REFLECTION_FULL
#define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif

//#define DEF_ObjectJc_SIMPLE
#define DEF_ObjectJc_REFLREF
//#define DEF_ObjectJcpp_REFLECTION
//#define DEF_ObjectJc_OWNADDRESS

//#define DEF_ClassJc_Vtbl 



//#define USE_BlockHeap_emC

//If set, no assertion is done:
//#define ASSERT_IGNORE_emC


//
//What to start as main:
//
//#define DEF_TESTALL_emC
#define DEF_MAIN_emC_TestAll_testSpecialMain
//#define DEF_MAIN_testMain_ObjectJc
//#define DEF_MAIN_TestCtrl_emC

//contains DEF_REFLOFFS_...for all defined ClassJc
#ifdef DEF_REFLECTION_OFFS
  //Note: the adequate *.reloffs.c should be part of the project:
#endif


//If set then the target should not use string operations
//#define DEF_NO_StringJcCapabilities

//If set, without complex thread context, without Stacktrace
#define DEF_ThreadContext_SIMPLE

//#define DEF_Exception_TRYCpp
//#define DEF_Exception_longjmp
#define DEF_Exception_NO

#include <compl_adaption.h>
#include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>

//#ifdef DEF_ThreadContext_SIMPLE
//  #include <emC_srcApplSpec/SimpleNumCNoExc/ExcStacktrcNo_emC.h>
//#else
//  #include <emC_srcApplSpec/applConv/ThreadContextStacktrc_emC.h>
#include <emC/Base/Exception_emC.h>
//#endif

#define kMaxPathLength_FileDescription_OSAL 512
#define sizeSafetyArea_allocMemC 256

//only for this test application:
extern_C void outTestConditions ( );

#endif //HEADERGUARD_applstdef_emC_Project

