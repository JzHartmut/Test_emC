#include <emC_Test_Ipc/test_Ipc.h>
#include <emC/HAL/SharedMem_HALemC.h>
#include <emC/Base/Time_emC.h>

void* open_MemFile_HALemC ( char const* name, int size);

void test_Ipc(void) {

  SharedMem_HALemC_s thiz = {0};

  int32* data;

  void* datav = open_SharedMem_HALemC(&thiz, "t:\\sharedMemTest.txt", 1000);

  data = C_CAST(int32*, datav);

  int dataCmp = 0;

  data[2] = 0x61747362;
  
  for(int i = 0; i <=1000; ++i) {
    data[2] = i;
    sleepMicroSec_Time_emC(10000);
  }

  while(false && data[1] != 10000000) {
    if(data[1] != dataCmp) {
      data[2] = dataCmp = data[1];
    } else {
      sleepMicroSec_Time_emC(10);
    }
  }
  close_SharedMem_HALemC(&thiz);
}
