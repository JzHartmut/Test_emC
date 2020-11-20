#include "Test_RingBuffer_emC.h"
#include <emC/Test/testAssert.h>
#include <emC/Base/Object_emC.h>
#include <emC/Base/RingBuffer_emC.h>


void testRingBufferSimpleOneThread ( ) {
  STACKTRC_ENTRY("testEvQueue");
  TEST_START("testEvQueueSimpleOneThread");

  float buffer[10];
  RingBuffer_emC_s ringbuffer = INIZ_RingBuffer_emC(ringbuffer, refl_RingBuffer_emC, 0);
  ctor_RingBuffer_emC(&ringbuffer.base.obj, ARRAYLEN_emC(buffer));
  
  float value = 0.1f;
  float sumWr =0, sumRd =0;  
  for(int ix = 0; ix < ARRAYLEN_emC(buffer) -1; ++ix) {
    int ixWr = add_RingBuffer_emC(&ringbuffer);
    if(ixWr >=0) {
      buffer[ixWr] = value;
      sumWr += value;
      value += 0.1f;
    } else {
      TEST_TRUE(false, "cannot write first 9 values");
    }
  }
  { int ixWr = add_RingBuffer_emC(&ringbuffer);
    TEST_TRUE(ixWr <0, "after 9 values, buffer is full");
  }  
  int ixRd;
  while( (ixRd = next_RingBuffer_emC(&ringbuffer)) >=0) {
    sumRd += buffer[ixRd];
    quitNext_RingBuffer_emC(&ringbuffer, ixRd);
  }
  TEST_TRUE(check_testAssert(sumWr - sumRd, 0.0f, 0.0001f), "all values re-read");


  TEST_END;
  STACKTRC_LEAVE
}
