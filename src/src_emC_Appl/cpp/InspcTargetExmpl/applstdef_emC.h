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


/**Define the granularity of the ObjectJc base class: */
//#define DEF_ObjectSimple_emC
//#define DEF_ObjectJc_SIMPLE
//#define DEF_ObjectJc_REFLREF
#define DEF_ObjectJc_SYNCHANDLE
#define DEF_ObjectJcpp_REFLECTION
#define DEF_ObjectJc_OWNADDRESS
#define DEF_ObjectJc_LARGESIZE

//#define DEF_ObjectJc_LARGESIZE

/**Define of the offering of Reflection information: */
//#define DEF_REFLECTION_NO
//#define DEF_REFLECTION_SIMPLE
//#define DEF_REFLECTION_OFFS
#define DEF_REFLECTION_FULL


//If set then the target should not use string operations
//#define DEF_NO_StringJcCapabilities


//#define USE_BlockHeap_emC
//#define DEF_BlockHeap_GARBAGECOLLECTOR


//If set, without complex thread context, without Stacktrace
#define DEF_ThreadContext_HEAP_emC
#define DEF_ThreadContext_STACKTRC

//#define DEF_Exception_TRYCpp
#define DEF_Exception_longjmp
//#define DEF_Exception_NO


//If set, no assertion is done:
//#define ASSERT_IGNORE_emC



//
//What to start as main:
//
#undef DEF_INSPC_REMOTEACCESS



/**This is to compile C++ classes of emC if __cplusplus is set.
  For C compilation this is ineffective because __cplusplus is necessary too*/
#define USE_cplusplus_emC
#define VIRTUAL_emC virtual

#define DEFINED_getVarAddrType_CalcExpr




//including the project specific reflOffs.h defines DEF_REFLECTION_OFFS 
#ifdef DEF_REFLECTION_OFFS
  //contains DEF_REFLOFFS_...for all defined ClassJc
  #include <emC_Exmpl_Ctrl/genRefl/emc_Exmpl_Ctrl.reflOffs.h>
  //Note: the adequate *.reloffs.c should be part of the project:
#elif defined(DEF_REFLECTION_FULL)
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif


#define kMaxPathLength_FileDescription_OSAL 512
#define sizeSafetyArea_allocMemC 256




#include <compl_adaption.h>
#include <emC/Base/Assert_emC.h>

#include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>
#include <emC/Base/Exception_emC.h>



//only for this test application:
extern_C void outTestConditions ( );

#endif //HGUARD_applstdef_emC_Project

