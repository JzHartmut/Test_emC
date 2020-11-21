#include "emc_Test_Container/Test_RingBuffer_emC.h"
#include <emC/Test/testAssert.h>
#include <emC/Base/Object_emC.h>
#include <emC/OSAL/os_time.h>
#include <emC/OSAL/os_thread.h>
#include <emC/Base/Time_emC.h>
#include <stdio.h>

//delay in the compareAndSwap loop to test whether it is effective:
#define TEST_INTR1_RingBuffer_emC sleepMicroSec_Time_emC(200);

#include <emC/Base/RingBuffer_emC.h>


typedef struct DataTest_RingBuffer_emC_T {

  struct { float val; int thread; } buffer[10];
  RingBuffer_emC_s ringbuffer;
  
  /**Increment the input values with a thread specific step with
   * to mark the values from which thread, for test, for detect the correct order. 
   */
  float valInp[3];

  /**Compare the last read value with the current for the specified thread,
   * to detect the correct progress (correct order of values) for the thread. 
   */ 
  float valLastRead[3];

  float sum[3];

  /**field of bits, 0x1: run threads, 0x2, 0x4, 0x8 set on end threads. */
  int volatile bRunEnd;

  OS_HandleThread hThread[3];


} DataTest_RingBuffer_emC_s;

#define INIZ_DataTest_RingBuffer_emC(THIS) \
 { {0}, INIZ_RingBuffer_emC((THIS).ringbuffer, refl_RingBuffer_emC, 0) }


void testRingBufferSimpleOneThread ( ) {
  STACKTRC_ENTRY("testEvQueue");
  TEST_START("testEvQueueSimpleOneThread");

  DataTest_RingBuffer_emC_s data = INIZ_DataTest_RingBuffer_emC(data);
  ctor_RingBuffer_emC(&data.ringbuffer.base.obj, ARRAYLEN_emC(data.buffer));
  
  float value = 0.1f;
  float sumWr =0, sumRd =0;  
  for(int ix = 0; ix < ARRAYLEN_emC(data.buffer) -1; ++ix) {
    int ixWr = add_RingBuffer_emC(&data.ringbuffer);
    if(ixWr >=0) {
      data.buffer[ixWr].val = value;
      sumWr += value;
      value += 0.1f;
    } else {
      TEST_TRUE(false, "cannot write first 9 values");
    }
  }
  { int ixWr = add_RingBuffer_emC(&data.ringbuffer);
    TEST_TRUE(ixWr <0, "after 9 values, buffer is full");
  }  
  int ixRd;
  while( (ixRd = next_RingBuffer_emC(&data.ringbuffer)) >=0) {
    sumRd += data.buffer[ixRd].val;
    quitNext_RingBuffer_emC(&data.ringbuffer, ixRd);
  }
  TEST_TRUE(check_testAssert(sumWr - sumRd, 0.0f, 0.0001f), "all values re-read");


  TEST_END;
  STACKTRC_LEAVE
}


static int threadRoutine1_TestRingBuffer(void* data) {      //Thread routine which emulates the interrupt.
  DataTest_RingBuffer_emC_s* thiz = C_CAST(DataTest_RingBuffer_emC_s*, data);
  while(thiz->bRunEnd & 1) {
    int ixWr = add_RingBuffer_emC(&thiz->ringbuffer);
    if(ixWr >=0) {
      thiz->valInp[0] += 0.25f;
      thiz->buffer[ixWr].val = thiz->valInp[0];
      thiz->buffer[ixWr].thread = 1;     //write at last to set data as valid for read.                  
      thiz->sum[0] += thiz->valInp[0];
    }
    sleepMicroSec_Time_emC(1000);                          //important: yield the CPU, wait a moment.
  }
  andInt_Atomic_emC(&thiz->bRunEnd, ~0x2);                 //reset the bit to signal finish.
  return 0;
}



static int threadRoutine2_TestRingBuffer(void* data) {      //Thread routine which emulates the interrupt.
  DataTest_RingBuffer_emC_s* thiz = C_CAST(DataTest_RingBuffer_emC_s*, data);
  while(thiz->bRunEnd & 1) {
    int ixWr = add_RingBuffer_emC(&thiz->ringbuffer);
    if(ixWr >=0) {
      thiz->valInp[1] += 0.5f;
      thiz->buffer[ixWr].val = thiz->valInp[1];
      thiz->buffer[ixWr].thread = 2;     //write at last to set data as valid for read.                  
      thiz->sum[1] += thiz->valInp[1];
    }
    sleepMicroSec_Time_emC(1025);                          //important: yield the CPU, wait a moment.
  }
  andInt_Atomic_emC(&thiz->bRunEnd, ~0x4);                 //reset the bit to signal finish.
  return 0;
}



static int threadRoutine3_TestRingBuffer(void* data) {      //Thread routine which emulates the interrupt.
  DataTest_RingBuffer_emC_s* thiz = C_CAST(DataTest_RingBuffer_emC_s*, data);
  while(thiz->bRunEnd & 1) {
    int ixWr = add_RingBuffer_emC(&thiz->ringbuffer);
    if(ixWr >=0) {
      thiz->valInp[2] += 0.75f;
      thiz->buffer[ixWr].val = thiz->valInp[2];
      thiz->buffer[ixWr].thread = 3;     //write at last to set data as valid for read.                  
      thiz->sum[2] += thiz->valInp[2];
    }
    sleepMicroSec_Time_emC(2050);                          //important: yield the CPU, wait a moment.
  }
  andInt_Atomic_emC(&thiz->bRunEnd, ~0x8);                 //reset the bit to signal finish.
  return 0;
}




void testRingBufferMultiThread ( ) {
  STACKTRC_ENTRY("testEvQueue");
  TEST_START("testEvQueueSimpleOneThread");

  DataTest_RingBuffer_emC_s data = INIZ_DataTest_RingBuffer_emC(data);
  DataTest_RingBuffer_emC_s* thiz = &data;
  ctor_RingBuffer_emC(&data.ringbuffer.base.obj, ARRAYLEN_emC(data.buffer));
  data.bRunEnd = 1;

  //                                                       //create a thread for the interrupt of target
  os_createThread(&data.hThread[0], threadRoutine1_TestRingBuffer, &data, "Test_RingBuffer_Th1", 128, 0);
  os_createThread(&data.hThread[1], threadRoutine2_TestRingBuffer, &data, "Test_RingBuffer_Th2", 128, 0);
  os_createThread(&data.hThread[2], threadRoutine3_TestRingBuffer, &data, "Test_RingBuffer_Th3", 128, 0);

  TimeAbs_emC timeStart; setCurrent_TimeAbs_emC(&timeStart);
  int ctRun = 1000;
  do {
    int ixRd;
    while( (ixRd = next_RingBuffer_emC(&data.ringbuffer)) >=0) {
      int thread = data.buffer[ixRd].thread;               //one access to the stored element
      float val = data.buffer[ixRd].val;
      if(thread !=0) {                                     //data are written?
        if(CHECK_ASSERT_emC(thread >=1 && thread <= ARRAYLEN_emC(data.sum), "faulty thread nr", thread, 0)) {
          //do check the thread, because it is used for index, maybe faulty (!)
          float diff = val - thiz->valLastRead[thread-1];
          thiz->valLastRead[thread-1] = val;
          CHECK_TRUE(diff == thread * 0.25f, "correct difference"); //hint: it is exactly mapped in float bits, == adminssible.
          data.sum[thread-1] += val;
        }
        data.buffer[ixRd].thread = 0;    //mark the position as free after complete read!
        quitNext_RingBuffer_emC(&data.ringbuffer, ixRd);
        ctRun -=1;
      }
    }
    sleep_Time_emC(0);  //yield other threads.
  } while(ctRun >=0);
  thiz->bRunEnd = 0x0e;  //till now the threads terminates, atomic write access
  TimeAbs_emC timeEnd; setCurrent_TimeAbs_emC(&timeEnd);
  float timeCalc = diffMicroSec_TimeAbs_emC(&timeEnd, &timeStart) / 1000000.0f;

  while(thiz->bRunEnd !=0) {
    //wait for ending thread.
    sleep_Time_emC(1);
  }
  //Now all threads are guaranteed finished, note that there data are in this stack (!)
  printf("    compareAndSwap repeat max: %d\n", thiz->ringbuffer.repeatCtMax);
  TEST_END;
  STACKTRC_LEAVE;

}



