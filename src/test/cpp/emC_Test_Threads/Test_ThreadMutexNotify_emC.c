#include "emC_Test_Threads/Test_ThreadMutexNotify_emC.h"
#include <emC/Test/testAssert.h>
#include <emC/Base/Object_emC.h>
#include <emC/OSAL/os_time.h>
#include <emC/OSAL/thread_OSemC.h>
#include <emC/OSAL/sync_OSemC.h>
#include <emC/Base/Time_emC.h>
#include <emC/Base/Timeconversions_emC.h>
#include <emC/OSAL/os_file.h>
#include <stdio.h>

//delay in the compareAndSwap loop to test whether it is effective:
//It forces an interruption (thread switch) inside the sensitive time of cmpAndSwap-loop
//after calculate before compareAndSwap, so that a repetition may forced
//(from coincidence)
//This macro is used in emC/Base/RingBuffer_emC.h for test situation, define it before include.
static int delayTimeInRingBufferCmpAndSwap_g = 0;
#define TEST_INTR1_RingBuffer_emC sleepMicroSec_Time_emC(delayTimeInRingBufferCmpAndSwap_g);


//#define DEF_ShowTime  //can be set for debug and evaluate

#ifdef DEF_ShowTime
#define LINELEN_reportTimeMng 20
char reportTimeBuffer[3000];
RingBuffer_emC_s reportTimeMng = INIZ_RingBuffer_emC(reportTimeMng, refl_RingBuffer_emC, 0, 3000/LINELEN_reportTimeMng);
#endif

//tag::DataTest_ThreadMutexNotify_emC[]
typedef struct DataTest_ThreadMutexNotify_emC_T {

  /**Store the handle for access to the threads, not necessary here. */
  HandleThread_OSemC hThread[2];

  /**Reference to a mutex instance for the data itself. */
  struct Mutex_OSemC_T const* mutexAccess;

  /**Reference to a mutex instance for the wait/notify. */
  struct Mutex_OSemC_T const* mutexNotify;

  /**Reference to the wait/notify management mechanism instances. */
  struct HandleWaitNotify_OSemC_T const* waitNotify;

  /**State variable for synchronization. */
  bool bRunning;  //: set true after first data calculation
  bool bData;     //: notice that data are prepared
  bool bWait;     //: notice that the other thread is really waiting
  bool bNext;     //: notice that next data should be prepared. 

  /**Some example data which needs to be consistent
   */
  struct Data_T {
    int v1, v2;
  } data;

  /**The number of loops in the three threads. */
  int ctLoops0, ctLoops1, ctLoops2;

  /**Some counters if errors occur, remain 0 if all is ok. */
  int errorWaitNext;
  int errorDiff1;
  int errorDiff2;
  int errorDataProgress;
  int error_bData;

  /**field of bits, 0x10, 0x20: run threads, 0x1, 0x2,  set on end threads. */
  int volatile bRunEnd;
} DataTest_ThreadMutexNotify_emC_s;
//end::DataTest_ThreadMutexNotify_emC[]


#define INIZ_DataTest_ThreadMutexNotify_emC(THIS, NROFentries) \
 { {0} }







static int mainThreadRoutine ( DataTest_ThreadMutexNotify_emC_s* thiz) {

  int ctRun = 100; //determines number of expected entries in RingBuffer which are read.

  int baseVal = 0;
  do {
    if(++baseVal >= 10) { baseVal = 0; }
    lockMutex_OSemC(thiz->mutexAccess, 0); {                // write the result of data calculation under lock
      thiz->data.v1 = baseVal;                           // because the result should accessable only consistent
      sleep_Time_emC(1);                                 // -->yield other threads only to provocate accesses during. 
      thiz->data.v2 = baseVal +3;                        // only an example for data calculation.
      thiz->bRunning = true;
    } unlockMutex_OSemC(thiz->mutexAccess);                 // both values should have anytime a difference of 3
    //----------------------------------------------------  Notify the other thread that data are prepared:
    lockMutex_OSemC(thiz->mutexNotify, 0); {                // do all under mutex lock
      thiz->bNext = false;                               // wait for notifying bNext from the other thread.
      thiz->bData = true;                                // notice data are prepared, the other thread can access
      if(thiz->bWait) {                                  // notify only if the other thread is really waiting
        notify_OSemC(thiz->waitNotify, thiz->mutexNotify);
      }
    } unlockMutex_OSemC(thiz->mutexNotify);
    int timeout = 10;
    while(!thiz->bNext && --timeout >0) {        // wait till bNext flag is set by the other thread.    
      sleep_Time_emC(1);                         // yield other threads. Wait 1 ms for new inputs in Ringbuffer.
      thiz->ctLoops0 +=1;
    }
    if(timeout ==0) {
      thiz->errorWaitNext +=1;
    }
  } while(--ctRun >=0);
  thiz->bRunning = false;                        // flag do no more evaluate data 

  return 0;
}


static int threadRoutine1_Test_ThreadMutexNtify_emC(void* data) {      //Thread routine which emulates the interrupt.
  STACKTRC_ENTRY("threadRoutine1_Test_ThreadMutexNtify_emC");
  DataTest_ThreadMutexNotify_emC_s* thiz = C_CAST(DataTest_ThreadMutexNotify_emC_s*, data);
  while(thiz->bRunEnd & 0x10) {
    thiz->ctLoops1 +=1;
    int v1, v2;
    lockMutex_OSemC(thiz->mutexAccess, 0); {                // write the result of data calculation under lock
      v1 = thiz->data.v1;                           // because the result should accessable only consistent
      v2 = thiz->data.v2;                        // only an example for data calculation.
    } unlockMutex_OSemC(thiz->mutexAccess);                 // both values should have anytime a difference of 3
    int diff = v2 - v1;
    if(thiz->bRunning && diff !=3) {
      thiz->errorDiff1 +=1;
    }
    sleepMicroSec_Time_emC(100);                          //important: yield the CPU, wait a moment.
  }
  //while(true){ sleepMicroSec_Time_emC(2000); }
  thiz->bRunEnd |= 0x1;                // flag set to notice, thread operation is finished. 
  STACKTRC_RETURN 0;
}



static int threadRoutine2_Test_ThreadMutexNtify_emC(void* data) {      //Thread routine which emulates the interrupt.
  DataTest_ThreadMutexNotify_emC_s* thiz = C_CAST(DataTest_ThreadMutexNotify_emC_s*, data);
  int v1z = 0;
  while(thiz->bRunEnd & 0x20) {
    thiz->ctLoops2 +=1;
    lockMutex_OSemC(thiz->mutexNotify, 0); {                  // should be wrappend with mutex
      if(!thiz->bData) {
        thiz->bWait = true;
        wait_OSemC(thiz->waitNotify, thiz->mutexNotify, 1000000);      // wait for notify, in the wait, mutex is freed
        thiz->bWait = false;
      }
      if(thiz->bRunning && !thiz->bData) {
        thiz->error_bData +=1;
      }
      thiz->bData = false;
    } unlockMutex_OSemC(thiz->mutexNotify);

    //------------------------------------------------------- access to the data
    int v1, v2;
    lockMutex_OSemC(thiz->mutexAccess, 0); {                // write the result of data calculation under lock
      v1 = thiz->data.v1;                           // because the result should accessable only consistent
      v2 = thiz->data.v2;                        // only an example for data calculation.
    } unlockMutex_OSemC(thiz->mutexAccess);                 // both values should have anytime a difference of 3
    //
    thiz->bNext = true;                          // bNext set after access, does not need mutex, it is atomic.
    //-----------------------------------------------------   evaluate the data.
    if(thiz->bRunning) {
      int diff = v2 - v1;              // mutex is not necessary because the other thread waits for new calculation. 
      if(diff !=3) {
        thiz->errorDiff2 +=1;
      }
      if( v1 !=0 && (v1 - v1z) !=1) {
        thiz->errorDataProgress +=1;
      } 
      v1z = v1;
    }
    //sleepMicroSec_Time_emC(1025);                          //important: yield the CPU, wait a moment.
  }
  //while(true){ sleepMicroSec_Time_emC(2000); }
  thiz->bRunEnd |= 0x2;                // flag set to notice, thread operation is finished. 
  return 0;
}




void testThreadMutexNotify_emC ( ) {
  STACKTRC_ENTRY("testThreadMutexNotify_emC");
  TEST_START("testThreadMutexNotify_emC");
  //delayTimeInRingBufferCmpAndSwap_g = delayTimeInRingBufferCmpAndSwap;  //the delay for cmpAndSwap test
  #ifdef DEF_ShowTime
    TimeAbs_emC timeAbs = {0};
  #endif
  DataTest_ThreadMutexNotify_emC_s data = INIZ_DataTest_ThreadMutexNotify_emC(data, ARRAYLEN_emC(data.buffer));
  DataTest_ThreadMutexNotify_emC_s* thiz = &data;
  data.bRunEnd = 0x70;
  //--------------------------------------------------------- Create mutex and threads
  thiz->mutexAccess = createMutex_OSemC("mutexAccess");       // first create mutexs
  thiz->mutexNotify = createMutex_OSemC("mutexNotify");       // because the threads are immediately started.
  int ok = createWaitNotifyObj_OSemC("waitNotify", &thiz->waitNotify);
  //                                                       //create a threads
  os_createThread(&data.hThread[0], threadRoutine1_Test_ThreadMutexNtify_emC, &data, "Test_RingBuffer_Th1", 128, 0);
  os_createThread(&data.hThread[1], threadRoutine2_Test_ThreadMutexNtify_emC, &data, "Test_RingBuffer_Th2", 128, 0);
  //
  TimeAbs_emC timeStart; setCurrent_TimeAbs_emC(&timeStart);

  mainThreadRoutine(&data);

  thiz->bRunEnd = 0x0;                           // the threads should terminate, atomic write access
  lockMutex_OSemC(thiz->mutexNotify, 0); {          // one thread is waiting. 
    if(thiz->bWait) {                            // notify only if the other thread is really waiting
      notify_OSemC(thiz->waitNotify, thiz->mutexNotify);      // to end this thread.
    }
  } unlockMutex_OSemC(thiz->mutexNotify);
  int ctAbort = 100;
  while(thiz->bRunEnd !=3 && --ctAbort >0) {     // wait for termination of both threads
    //wait for ending thread.
    sleep_Time_emC(1);
  }
  CHECK_TRUE(ctAbort >0, "Other Threads are stopped");
  //
  TimeAbs_emC timeEnd; setCurrent_TimeAbs_emC(&timeEnd);
  float timeCalc = diffMicroSec_TimeAbs_emC(&timeEnd, &timeStart) / 1000000.0f;
  TEST_TRUE(thiz->ctLoops1 > 500, "Thread1 has accessed often enough");
  TEST_TRUE(thiz->ctLoops2 < 200, "Thread2 get bNext in a short time 1..2 ms");
  TEST_TRUE(thiz->errorWaitNext == 0, "MainThread get bNext in a time < 10 ms");
  TEST_TRUE(thiz->errorDiff1 == 0, "Thread1 data are consistent");
  TEST_TRUE(thiz->errorDiff2 == 0, "Thread2 data are consistent");
  TEST_TRUE(thiz->errorDataProgress == 0, "Thread2 data are in exact order in progress");
  TEST_TRUE(thiz->error_bData == 0, "Thread2 has always data on notify");
  #ifdef DEF_ShowTime
    OS_HandleFile hout = os_fopenToWrite("Debug/Test_ThreadMutexNtify_emCTimes.txt", false);
    if(hout ==null) {
      hout = os_fopenToWrite("build/Test_ThreadMutexNtify_emCTimes.txt", false);
    }
    if(hout !=null) {
      os_fwrite(hout, reportTimeBuffer, sizeof(reportTimeBuffer));
      os_fclose(hout);
    }
  #endif
  //Now all threads are guaranteed finished, note that there data are in this stack (!)
  TEST_TRUE(timeCalc < 0.5f, "The test runs < 0.5 seconds");
  //TODO should be evaluated, repeatCtMax is 1 in test.
  //TEST_TRUE(thiz->ringbuffer.repeatCtMax >2, "More as 2 repeatings on cmpAndSwap occurred");
  //printf("    compareAndSwap repeat max: %d, works %f sec\n", thiz->ringbuffer.repeatCtMax, timeCalc);
  TEST_END;
  STACKTRC_LEAVE;

}


