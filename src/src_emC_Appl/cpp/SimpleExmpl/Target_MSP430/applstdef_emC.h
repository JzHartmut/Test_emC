#ifndef HGUARD_applstdef_emC
#define HGUARD_applstdef_emC

//Projectspecific applstdef_emC.h


//tag::ObjectJc[]
/**Define the granularity of the ObjectJc base class: */
#define DEF_NO_ObjectJc_emC
//#define DEF_ObjectSimple_emC
//#define DEF_ObjectJc_SYNCHANDLE
//#define DEF_ObjectJcpp_REFLECTION
//#define DEF_ObjectJc_OWNADDRESS
//#define DEF_ObjectJc_LARGESIZE

//tag::Refl[]
/**Define of the offering of Reflection information: */
#define DEF_REFLECTION_NO
//#define DEF_REFLECTION_SIMPLE
//#define DEF_REFLECTION_OFFS
//#define DEF_REFLECTION_FULL
//end::Refl[]
//end::ObjectJc[]


//tag::StringJc[]
/**If set then the target should not use string operations */
//#define DEF_NO_StringUSAGE
//#define DEF_CharSeqJcCapabilities
//end::StringJc[]


//tag::ThCxt[]
/**If set, without complex thread context, without Stacktrace*/
#define DEF_NO_THCXT_STACKTRC_EXC_emC
//#define DEF_ThreadContext_NO_STACKTRC_emC
//#define DEF_ThreadContext_STACKUSAGE
//#define DEF_ThreadContext_STACKTRC

/**The following compiler switch can be applicate independently with all three above:
 * It clarifies that there is a thread local heap which offers some more possibiities
 * for memory allocation valid in one thread respectively Stack usage. */ 
//#define DEF_ThreadContext_HEAP_emC
//end::ThCxt[]

//tag::Exc[]
#define DEF_NO_Exception_emC
//#define DEF_Exception_Log_emC
//#define DEF_Exception_longjmp
//#define DEF_Exception_TRYCpp
//end::Exc[]

//tag::assert[]
//If set, no assertion is done:
#define ASSERT_IGNORE_emC
//end::assert[]


//tag::Blockheap[]
/**Selects working with Blockheap*/
//#define USE_BlockHeap_emC
//#define DEF_BlockHeap_GARBAGECOLLECTOR
//end::Blockheap[]


//
//What to start as main:
//
#ifndef DEF_TESTBasics_emC
/**select only one of this to debug special tests: */
//#define DEF_TESTBasics_emC
//#define DEF_TESTALL_emC  //this is the setting for the autmatic test.
//#define DEF_MAIN_emC_TestAll_testSpecialMain
//#define DEF_MAIN_testMain_ObjectJc
//#define DEF_MAIN_TestCtrl_emC
#endif //ndef DEF_TESTALL_emC



//tag::AddrVal[]
/**Defines the type for the length or value in a struct{ addr, val} defined with STRUCT_AddrVal_emC(...). */
#define VALTYPE_AddrVal_emC int32
//end::AddrVal[]


//tag::StringJcLen[]
/**Bits of length of constant string adequate to VALTYPE_AddrVal_emC. 
 * It have to be a mask with set bits on right side (all last significant bits).
 * The next 2 bits left are used internally for designation of String.
 * see [[mNonPersists__StringJc]], [[mThreadContext__StringJc]].
 * See also [[kIsCharSequence_StringJc]]
 * The following bits left side are used for enhanced references, see kBitBackRef_ObjectJc and mBackRef_ObjectJc.
 * If enhanced references are not used, a StringJc can occupy all bits, for example all 16 bits for 16-bit-integer systems.
 */
//#define mLength_StringJc 0x00003fff
//end::StringJcLen[]




//tag::UseCpp[]
/**This is to compile C++ classes of emC if also __cplusplus is set.
  For C compilation this is ineffective because __cplusplus is necessary too*/
#define DEF_cplusplus_emC
//end::UseCpp[]


//tag::specSizes[]
#define kMaxPathLength_FileDescription_OSAL 512
//#define sizeSafetyArea_allocMemC 0
//end::specSizes[]


//tag::includes[]
#include <compl_adaption.h>
//#include <emC/Base/types_def_common.h>
//#include <emC/BlockHeap/BlockHeap_emC.h>
//#include <emC/Base/Assert_emC.h>
#include <emC/Base/applstdef_common.h>
//end::includes[]



//tag::reflOffs[]
//including the project specific reflOffs.h defines DEF_REFLECTION_OFFS 
#ifdef DEF_REFLECTION_OFFS
  //contains DEF_REFLOFFS_...for all defined ClassJc
  #include <emC_Exmpl_Ctrl/genRefl/emC_Exmpl_Ctrl_reflOffs.cpp.h>
  //Note: the adequate *.reloffs.c should be part of the project:
#endif
//end::reflOffs[]








#endif //HGUARD_applstdef_emC
