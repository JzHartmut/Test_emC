#ifndef HGUARD_emC_Test__Math_emC
#define HGUARD_emC_Test__Math_emC
#include <compl_adaption.h>


typedef struct Results32_Test_Math_emC_T {

  int32 r[16];
} Results32_Test_Math_emC_s;


typedef struct Test_Mult16_Math_emC_T {
  uint16 a; uint16 b; uint32 rs; uint32 ru; 
} Test_Mult16_Math_emC_s;

extern_C int testMult16_Math_emC ( Test_Mult16_Math_emC_s*  values, int zValues);



extern_C void test_Q_rsqrt ( );

extern_C void test_math16 ( );

extern_C int test_FixpointMult ( );


extern_C int test_Math_emC ( );

#endif //HGUARD_emC_Test__Math_emC