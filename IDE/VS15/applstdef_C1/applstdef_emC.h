#ifndef HGUARD_applstdef_emC_Project
#define HGUARD_applstdef_emC_Project
#define HGUARD_applstdef_emC  //is defined here.

//Projectspecific applstdef_emC.h

/**It seems to be a specifica in Visual Studio. 
 * The VS-File Microsoft Visual Studio 14.0\VC\include\yvals.h
 * contains a assert-message with is prevented with this define. 
 * What ist it, what means it? not clarified yet.
 * Note: This applstdef_emC.h is only for the visual studio project.
 */
#define _ALLOW_RTCc_IN_STL  //what is it? a specialism of Visual Studio??

//includes the file which is generated from the simulation selector:
#include <emC_TestAll\fDefSelection.h>

#ifndef DEFINED_fDefSelection

/**Define the granularity of the ObjectJc base class: */
//#define DEF_ObjectSimple_emC
//#define DEF_ObjectJc_SYNCHANDLE
#define DEF_ObjectJcpp_REFLECTION
//#define DEF_ObjectJc_OWNADDRESS

//#define DEF_ObjectJc_LARGESIZE

/**Define of the offering of Reflection information: */
//#define DEF_REFLECTION_NO
//#define DEF_REFLECTION_SIMPLE
//#define DEF_REFLECTION_OFFS
#define DEF_REFLECTION_FULL


//If set then the target should not use string operations
#define DEF_NO_StringUSAGE
//#define DEF_CharSeqJcCapabilities


//#define USE_BlockHeap_emC

//If set, without complex thread context, without Stacktrace
//#define DEF_ThreadContext_HEAP_emC
//#define DEF_ThreadContext_STACKUSAGE
//#define DEF_ThreadContext_STACKTRC
#define DEF_ThreadContext_STACKTRC_NO

//#define DEF_Exception_TRYCpp
#define DEF_Exception_longjmp
//#define DEF_Exception_NO


//If set, no assertion is done:
//#define ASSERT_IGNORE_emC


#endif //DEFINED_fDefSelection

//
//What to start as main:
//
//#define DEF_TESTALL_emC  //this is the setting for the autmatic test.

#ifndef DEF_TESTALL_emC
/**select only one of this to debug special tests: */
//#define DEF_MAIN_emC_TestAll_testSpecialMain
//#define DEF_MAIN_testMain_ObjectJc
//#define DEF_MAIN_TestCtrl_emC
#endif //ndef DEF_TESTALL_emC

/**This is to compile C++ classes of emC if __cplusplus is set.
  For C compilation this is ineffective because __cplusplus is necessary too*/
#define USE_cplusplus_emC


#define DEFINED_getVarAddrType_CalcExpr




//including the project specific reflOffs.h defines DEF_REFLECTION_OFFS 
#ifdef DEF_REFLECTION_OFFS
  //contains DEF_REFLOFFS_...for all defined ClassJc
  #include <emC_Exmpl_Ctrl/genRefl/emc_Exmpl_Ctrl.reflOffs.h>
  //Note: the adequate *.reloffs.c should be part of the project:
#elif defined(DEF_REFLECTION_FULL)
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif





#include <compl_adaption.h>
#include <emC/Base/Assert_emC.h>

#include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>
#include <emC/Base/Exception_emC.h>



#define kMaxPathLength_FileDescription_OSAL 512
//#define DEF_OSAL_FileSystem_NO

#define sizeSafetyArea_allocMemC 256

//only for this test application:
extern_C void outTestConditions ( );

#endif //HGUARD_applstdef_emC_Project
