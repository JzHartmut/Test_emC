#ifndef HGUARD_applstdef_emC
#define HGUARD_applstdef_emC

//Projectspecific applstdef_emC.h


//includes the file which is generated from the simulation selector:
#include <emC_TestAll/fDefSelection.h>

#ifndef DEFINED_fDefSelection

/**Define the granularity of the ObjectJc base class: */
#define DEF_ObjectSimple_emC
//#define DEF_ObjectJc_SIMPLE
#define DEF_ObjectJc_REFLREF
//#define DEF_ObjectJc_SYNCHANDLE
//#define DEF_ObjectJcpp_REFLECTION
//#define DEF_ObjectJc_OWNADDRESS

//#define DEF_ObjectJc_LARGESIZE

/**Define of the offering of Reflection information: */
//#define DEF_REFLECTION_NO
#define DEF_REFLECTION_SIMPLE
//#define DEF_REFLECTION_OFFS
//#define DEF_REFLECTION_FULL


//If set then the target should not use string operations
//#define DEF_NO_StringUSAGE
//#define DEF_NO_StringJcCapabilities


/**If set, without complex thread context, without Stacktrace*/
//#define DEF_ThreadContext_HEAP_emC
//#define DEF_ThreadContext_STACKTRC
//#define DEF_ThreadContext_STACKUSAGE
//#define DEF_ThreadContext_STACKTRC_NO

//#define DEF_ThreadContext_SIMPLE

//#define DEF_Exception_TRYCpp
#define DEF_Exception_longjmp
//#define DEF_Exception_NO


//If set, no assertion is done:
//#define ASSERT_IGNORE_emC

/**Selects working with Blockheap*/
//#define USE_BlockHeap_emC
//#define DEF_BlockHeap_GARBAGECOLLECTOR


//To work with handle instead pointer in data struct and 
//DEF_Type_HandleADDR_emC uint32


//
//What to start as main:
//
#ifndef DEF_TESTBasics_emC
/**select only one of this to debug special tests: */
#define DEF_TESTBasics_emC
//#define DEF_TESTALL_emC  //this is the setting for the autmatic test.
//#define DEF_MAIN_emC_TestAll_testSpecialMain
//#define DEF_MAIN_testMain_ObjectJc
//#define DEF_MAIN_TestCtrl_emC
#endif //ndef DEF_TESTALL_emC


#endif //DEFINED_fDefSelection

#define DEF_TestVal_PIDi_Ctrl_emC

//for struct{ addr, val}:
#define VALTYPE_AddrVal_emC int32
/**Bits of length of constant string adequate to VALTYPE_AddrVal_emC. 
 * It have to be a mask with set bits on right side (all last significant bits).
 * The next 2 bits left are used internally for designation of String.
 * see [[mNonPersists__StringJc]], [[mThreadContext__StringJc]].
 * See also [[kIsCharSequence_StringJc]]
 * The following bits left side are used for enhanced references, see kBitBackRef_ObjectJc and mBackRef_ObjectJc.
 * If enhanced references are not used, a StringJc can occupy all bits, for example all 16 bits for 16-bit-integer systems.
 */
#define mLength_StringJc                 0x00003fff




/**This is to compile C++ classes of emC if __cplusplus is set.
  For C compilation this is ineffective because __cplusplus is necessary too*/
#define USE_cplusplus_emC
#define DEF_cplusplus_emC
#define DEF_CPP_COMPILE


#define DEFINED_getVarAddrType_CalcExpr

#define kMaxPathLength_FileDescription_OSAL 512
#define sizeSafetyArea_allocMemC 16


#include <compl_adaption.h>
#ifndef HGUARD_emCBase_types_def_common
  #include <emC/Base/types_def_common.h>    // should be normally included in compl_adaption.h
#endif

//This header defines all basics derived from the settings here:
#include <emC/Base/applstdef_common.h>



//including the project specific reflOffs.h defines DEF_REFLECTION_OFFS 
#ifdef DEF_REFLECTION_OFFS
  //contains DEF_REFLOFFS_...for all defined ClassJc
  #include <emC_Exmpl_Ctrl/genRefl/emC_Exmpl_Ctrl_reflOffs.cpp.h>
  //Note: the adequate *.reloffs.c should be part of the project:
#elif defined(DEF_REFLECTION_FULL)
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif







//only for this test application:
extern_C void outTestConditions ( );

#endif //HGUARD_applstdef_emC
