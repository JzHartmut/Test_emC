#ifndef HGUARD_MemCpy_emC
#define HGUARD_MemCpy_emC
#include <applstdef_emC.h>


typedef struct TestMemCpy_T {
  char dummy1;
  int32 src[3000];    //:define on an odd address.
  char dummy2[2];
  int32 dst[5000];
  char dummy3; 
} TestMemCpy_s;

extern volatile TestMemCpy_s testMemCpy; 

extern_C void doMemcpy(volatile TestMemCpy_s* data);

extern_C void doStringPackedCpy(volatile TestMemCpy_s* data);


#endif //HGUARD_MemCpy_emC
