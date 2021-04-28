#ifndef HGUARD_emC_Test__Math_emC
#define HGUARD_emC_Test__Math_emC
#include <compl_adaption.h>


typedef struct Results32_Test_Math_emC_T {

  int32 r[16];
} Results32_Test_Math_emC_s;


typedef struct Test_Data16_Math_emC_T {
  uint16 a; uint16 b; uint32 rs; uint32 ru; uint32 su; 
} Test_Data16_Math_emC_s;


extern_C int testMult16_Math_emC ( Test_Data16_Math_emC_s*  values, int zValues);

extern_C int testMult32Lo_Math_emC ( Test_Data16_Math_emC_s*  values, int zValues);


extern_C int testMult32_Math_emC ( Test_Data16_Math_emC_s*  values, int zValues );

extern_C int test_AddSat_Math_emC ( Test_Data16_Math_emC_T* data, int zdata);

extern_C void test_Q_rsqrt ( );

extern_C int test_cos16 ( bool bPrint );

extern_C int test_atan2nom16_MathemC ( bool bPrint, int16 dangle );

extern_C int test_sin16 ( );

extern_C int test_sqrt16 ( bool bPrint );

extern_C int test_rsqrt2_32 ( bool bPrint );
extern_C void test_rsqrt4_32 ( );

extern_C int test_FixpointMult ( );

extern_C int test_Nom_int16_complex ( );

extern_C int test_Math_emC ( );

#endif //HGUARD_emC_Test__Math_emC
