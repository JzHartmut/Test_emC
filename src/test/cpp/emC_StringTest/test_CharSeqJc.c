#include <emC/Base/String_emC.h>
#include <emC/Jc/StringJc.h>



//This is an internal type. To outside only the ObjectJc and the CharSeqJc interface should be visible.
typedef struct Example_CharSeqJc_T {

  union{ ObjectJc obj; CharSeqObjJc CharSeqJc; } base;  

  char internalString[25];



} Example_CharSeqJc_s;


#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Example_CharSeqJc;
#endif

#ifndef ID_refl_Example_CharSeqJc  //may be defined in *.reflOffs.h
#define ID_refl_Example_CharSeqJc 0x0eee
#endif

#ifdef DEF_REFLECTION_FULL
 //TODO #include <emC/Base/genRefl/Time_emC.crefl>
#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_Clock_MinMaxTime_emC)
 //Not defined with DEF_REFLECTION_OFFS but necessary, only as type marker:
 ClassJc const refl_Example_CharSeqJc = INIZ_ClassJc( refl_Example_CharSeqJc, "Example_CharSeqJc");
#endif

//CharSeqJc implementation operation length:
int32 length_Example_CharSeqJc ( CharSeqObjJc const* ithiz, ThCxt* _thCxt) {

  return 5;
}


//CharSeqJc implementation operation charAt:
char charAt_Example_CharSeqJc ( CharSeqObjJc const* ithiz, int32 ix, ThCxt* _thCxt) {
  return 'a' + ix;
}

//CharSeqJc implementation operation subsequence:
//It returns a simple StringJc, not a specific subclass.
CharSeqJc subSequence_Example_CharSeqJc ( CharSeqObjJc const* ithiz, int32 from, int32 to, ThCxt* _thCxt){
  StringJc ret = INIZ_StringJc("", 0);
  return ret;
}



//The virtual table as const for C dynamic linked operation:
#ifdef DEF_ClassJc_Vtbl
struct Vtbl_Example_CharSeqJc_T {
  Vtbl_CharSeqJc tbl; VtblHeadJc end;
} const vtbl_Example_CharSeqJc = 
{ { { sign_Vtbl_CharSeqJc, (struct Size_Vtbl_t*)((3 + 2) * sizeof(void*))}
  , length_Example_CharSeqJc       //overridden opeations of this class
  , charAt_Example_CharSeqJc
  , subSequence_Example_CharSeqJc
  , { {sign_Vtbl_ObjectJc, (struct Size_Vtbl_t*)((5 + 2) * sizeof(void*)) }
    , clone_ObjectJc_F
    , equals_ObjectJc_F
    , finalize_ObjectJc_F
    , hashCode_ObjectJc_F
    , toString_ObjectJc_F
    }
  }
, { signEnd_Vtbl_ObjectJc, null }
};
#endif //DEF_ClassJc_Vtbl


//The reflection of this class contains the reference to the virtual table.
#ifdef DEF_REFLECTION_FULL
const ClassJc refl_Example_CharSeqJc =
{ INIZ_ObjectJc(refl_Example_CharSeqJc, refl_ClassJc, OBJTYPE_ClassJc)
  //CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc)
, "Example_CharSeqJc"
, 0
, sizeof(ObjectJc)
, null //(FieldJcArray const*)&refl_Fields_ObjectJc  //attributes and associations
, null  //method
, { null }  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
#ifdef DEF_ClassJc_Vtbl
, &vtbl_Example_CharSeqJc.tbl.head
#endif
};
#endif //DEF_REFLECTION_FULL



//A static instance of this type:
Example_CharSeqJc_s example_CharSeqJc = 
{ INIZ_ObjectJc(example_CharSeqJc, refl_Example_CharSeqJc, 0)
, "abcedef"
};


//Access to this class, the operation returns the CharSeqJc
CharSeqJc getExample_CharSeqJc ( ) {
  CharSeqJc ret;
  #ifdef DEF_CharSeqJcCapabilities
      
  ret.addr.obj = &example_CharSeqJc.base.obj;
  //TODO other variants
  #endif
  ret.val = kIsCharSeqJc_CharSeqJc + 2 | mNonPersists__StringJc;
  return ret;
}
