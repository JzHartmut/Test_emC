#ifndef HGUARD_compl_adaption
#define HGUARD_compl_adaption

#pragma diag_suppress = 174  //external/internal linkage conflict with previous declaration: static not written on function prototypes.

#define DSP28_DATA_TYPES //prevent second definition in TI header


#define CPU1_TIHAL  //Faulty here, if CPU2 is compiled.

#define _SYS__STDINT_H_  //prevent including of stdint.h, all necessary stuff is here in a better form.

//Definition of type names. Use define for compatibility of equal but differ in ident types.
#define uint unsigned int

//Note: the int8 type is represented by a char, but it has 16 bit.
#define int8 char
#define int8_t char
#define uint8 unsigned char
#define uint8_t unsigned char

#define int16 int
#define int16_t int
#define uint16 unsigned int
#define uint16_t unsigned int
#define Uint16 unsigned int
#define int32 long
#define int32_t long
#define uint32_t unsigned long
#define uint32 unsigned long
#define Uint32 unsigned long

#define int64 long long
#define int64_t long long
#define uint64 unsigned long long
#define Uint64 unsigned long long
#define float32 float

#if __TI_COMPILER_VERSION__ >= 16006000
//typedef unsigned int bp_16 __attribute__((byte_peripheral));
//typedef unsigned long bp_32 __attribute__((byte_peripheral));
#endif

/**intptr_t is defined in the C99 standard, but maybe conflicting defining here. Hence may better to use intPTR.
 * An address is 32 bit. It is signed because differences should be built. (not unsigned !!)*/
#define intptr_t int32
#define intPTR int32


/**The addresses count in int-step. */
#define BYTE_IN_MemUnit 2
#define MemUnit int

#undef null
#ifdef __cplusplus
  #define null 0
#else
  #define null ((void*)0)
#endif

#ifdef __cplusplus
  #define INLINE_emC inline
#else
  #define INLINE_emC static inline
  #define bool unsigned char
  
#endif

#define MAYBE_UNUSED_emC __attribute__((unused))

#define USED_emC __attribute__((used))

/**It is an attribute before a function definition to determine
 * that the function should be placed in a section which is linked
 * to a RAM location but load into the FLASH memory.
 * This section must be copied on startup to run successfully.
 * It is a designation for embedded hardware with lesser but fast RAM.
 */
#define RAMFUNC_emC __attribute__((ramfunc))


/**This macro defines a struct with a pointer to the given type and a integer number.
 * Usual it can be used to describe exactly an 1-dimensional array. The integer number is the number of elements,
 * the size in memory is (sizeof(TYPE) * numberOfElements).
 * This struct should pass with 2 register for call by value or return by value, usual supported by the compiler.
 */
#define VALTYPE_AddrVal_emC int32
#define STRUCT_AddrVal_emC(NAME, TYPE) struct NAME##_T { TYPE* addr; VALTYPE_AddrVal_emC val; } NAME

/**Bits of length of constant string adequate to VALTYPE_AddrVal_emC. 
 * It have to be a mask with set bits on right side (all last significant bits).
 * The next 2 bits left are used internally for designation of String.
 * see [[mNonPersists__StringJc]], [[mThreadContext__StringJc]].
 * See also [[kIsCharSequence_StringJc]]
 * The following bits left side are used for enhanced references, see kBitBackRef_ObjectJc and mBackRef_ObjectJc.
 * If enhanced references are not used, a StringJc can occupy all bits, for example all 16 bits for 16-bit-integer systems.
 */
#define mLength_StringJc                 0x00003fff



#include <emC/Base/types_def_common.h>
#endif //HGUARD_compl_adaption
