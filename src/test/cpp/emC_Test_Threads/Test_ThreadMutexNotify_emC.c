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

//#define DEF_ShowTime  //can be set for debug and evaluate

#ifdef DEF_ShowTime
#define LINELEN_reportTimeMng 20
char reportTimeBuffer[3000];
RingBuffer_emC_s reportTimeMng = INIZ_RingBuffer_emC(reportTimeMng, refl_RingBuffer_emC, 0, 3000/LINELEN_reportTimeMng);
#endif

//tag::DataTest_ThreadMutexNotify_emC[]
typedef struct DataTest_ThreadMutexNotify_emC_T {

  /**Store the handle for access to the threads, not necessary here. */
  Thread_OSemC* hThread[3];

  /**Mutex instance for the data itself. */
  Mutex_OSemC_s mutexAccess;

  /**Mutex instance for the wait/notify. */
  Mutex_OSemC_s mutexNotify;

  /**Wait/notify management mechanism instances. */
  HandleWaitNotify_OSemC waitNotify;

  /**State variable for synchronization. */
  bool bFirstData;//: true on first transmission of new data from v1=0
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
  int ctFirstData;
  int errorWaitNext;
  int errorTimeoutLockReentrant;
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


/**If this routine is called under lock, it tests twice:
 * either the timeout should come because reentrant lock is not supported, 
 * then thiz->errorTimeoutLockReentrant is incremented after 100 ms. 
 * Or the reentrant lock works.
 * @return false if the reentrant lock fails. Then the number of loops should be reduced
 *         to prevent a too long running time. 
 */
static bool setDataUnderLock ( DataTest_ThreadMutexNotify_emC_s* thiz, int baseVal) {
  bool bLockOk = lockMutex_OSemC(&thiz->mutexAccess); { // write the result of data calculation under lock
    if(!bLockOk) {      
      thiz->errorTimeoutLockReentrant +=1;
    }
    thiz->data.v1 = baseVal;                           // because the result should accessable only consistent
    thiz->data.v2 = baseVal +3;                        // only an example for data calculation.
    thiz->bRunning = true;
  } unlockMutex_OSemC(&thiz->mutexAccess);                 // both values should have anytime a difference of 3
  return bLockOk;
}


//tag::mainThreadRoutine_start[]
static int mainThreadRoutine ( DataTest_ThreadMutexNotify_emC_s* thiz, bool bUseReentrantLock) {

  int ctRun = 100; //determines number of expected entries in RingBuffer which are read.
  thiz->bFirstData = true;
  int baseVal = 0;
  do {
    if(++baseVal >= 10) { baseVal = 0; }
    lockMutex_OSemC(&thiz->mutexAccess); {     // write the result of data calculation under lock
      if(bUseReentrantLock) {
        bool bOkReentrant = setDataUnderLock(thiz, baseVal);    // call a given funktion which also locks.
        if(!bOkReentrant && ctRun >3) {
          ctRun = 3;                             // shorten the number of loops dont spend too much test time.
        }
      } else {
        thiz->data.v1 = baseVal;                 // because the result should accessable only consistent
        sleep_Time_emC(1);                       // -->yield other threads only to provocate accesses during. 
        thiz->data.v2 = baseVal +3;              // only an example for data calculation.
        thiz->bRunning = true;
      }
    } unlockMutex_OSemC(&thiz->mutexAccess);                 // both values should have anytime a difference of 3
//end::mainThreadRoutine_start[]
//tag::mainThreadRoutine_notify[]
    //----------------------------------------------------  Notify the other thread that data are prepared:
    lockMutex_OSemC(&thiz->mutexNotify); {                // do all under mutex lock
      thiz->bNext = false;                               // wait for notifying bNext from the other thread.
      thiz->bData = true;                                // notice data are prepared, the other thread can access
      if(thiz->bWait) {                                  // notify only if the other thread is really waiting
        notify_OSemC(thiz->waitNotify, &thiz->mutexNotify);
      }
    } unlockMutex_OSemC(&thiz->mutexNotify);
//end::mainThreadRoutine_notify[]
//tag::mainThreadRoutine_waitNext[]
    int timeout = 2;
    while(!thiz->bNext && --timeout >0) {        // wait till bNext flag is set by the other thread.    
      sleep_Time_emC(1);                         // yield other threads. Wait 1 ms for new inputs in Ringbuffer.
      thiz->ctLoops0 +=1;
    }
    if(timeout ==0) {
      thiz->errorWaitNext +=1;
    }
    thiz->bFirstData = false;
//end::mainThreadRoutine_waitNext[]
//tag::mainThreadRoutine_end[]
  } while(--ctRun >=0);
  return 0;
}
//end::mainThreadRoutine_end[]


//tag::threadRoutine1[]
static int threadRoutine1_Test_ThreadMutexNtify_emC(void* data) {      //Thread routine which emulates the interrupt.
  int err = 0;
  STACKTRC_ENTRY("threadRoutine1_Test_ThreadMutexNtify_emC");
  printf("threadRoutine2_Test_ThreadMutexNtify_emC\n");
  TRY {
    DataTest_ThreadMutexNotify_emC_s* thiz = C_CAST(DataTest_ThreadMutexNotify_emC_s*, data);
    while(thiz->bRunEnd & 0x10) {
      thiz->ctLoops1 +=1;
      int v1, v2;
      lockMutex_OSemC(&thiz->mutexAccess); {                // write the result of data calculation under lock
        v1 = thiz->data.v1;                           // because the result should accessable only consistent
        v2 = thiz->data.v2;                        // only an example for data calculation.
      } unlockMutex_OSemC(&thiz->mutexAccess);                 // both values should have anytime a difference of 3
      int diff = v2 - v1;
      if(thiz->bRunning && diff !=3) {
        thiz->errorDiff1 +=1;
      }
      sleepMicroSec_Time_emC(10);                          //important: yield the CPU, wait a moment.
    }
    //while(true){ sleepMicroSec_Time_emC(2000); }
    thiz->bRunEnd |= 0x1;                // flag set to notice, thread operation is finished.
  }_TRY
  CATCH(Exception, exc) {
    err = 99;
  }
  END_TRY
  STACKTRC_RETURN err;
}
//end::threadRoutine1[]



//tag::threadRoutine2_start[]
static int threadRoutine2_Test_ThreadMutexNtify_emC(void* data) {      //Thread routine which emulates the interrupt.
  int err = 0;
  STACKTRC_ENTRY("threadRoutine1_Test_ThreadMutexNtify_emC");
  printf("threadRoutine2_Test_ThreadMutexNtify_emC\n");

  TRY {
    DataTest_ThreadMutexNotify_emC_s* thiz = C_CAST(DataTest_ThreadMutexNotify_emC_s*, data);
    int v1z = 0;
    while(thiz->bRunEnd & 0x20) {
      thiz->ctLoops2 +=1;
      lockMutex_OSemC(&thiz->mutexNotify); {                  // should be wrappend with mutex
        if(!thiz->bData) {
          thiz->bWait = true;                      // wait for notify, in the wait,
          wait_OSemC(thiz->waitNotify, &thiz->mutexNotify, 100); // notice: mutex is freed inside wait)
          thiz->bWait = false;
        }
        if(thiz->bRunning && !thiz->bData) {       // check whether wait is woken up with bData, should be
          thiz->error_bData +=1;
        }
        thiz->bData = false;                       // set false for next loop
      } unlockMutex_OSemC(&thiz->mutexNotify);
  //end::threadRoutine2_start[]
  //tag::threadRoutine2_accessData[]
      //------------------------------------------------------- access to the data
      int v1, v2;
      bool bFirstData;
      lockMutex_OSemC(&thiz->mutexAccess); {                // write the result of data calculation under lock
        v1 = thiz->data.v1;                           // because the result should accessable only consistent
        v2 = thiz->data.v2;                        // only an example for data calculation.
        bFirstData = thiz->bFirstData;
      } unlockMutex_OSemC(&thiz->mutexAccess);                 // both values should have anytime a difference of 3
      //
      thiz->bNext = true;                          // bNext set after access, does not need mutex, it is atomic.
  //end::threadRoutine2_accessData[]
  //tag::threadRoutine2_checkData[]
      //-----------------------------------------------------   evaluate the data.
      if(thiz->bRunning) {
        int diff = v2 - v1;              // mutex is not necessary because the other thread waits for new calculation.
        if(diff !=3) {
          thiz->errorDiff2 +=1;
        }
        if(bFirstData) {
          thiz->ctFirstData +=1;
        }
        else if( v1 !=0 && (v1 - v1z) !=1) {
          thiz->errorDataProgress +=1;
        }
        v1z = v1;
      }
    } //while thread loop
  //end::threadRoutine2_checkData[]
  //tag::threadRoutine2_end[]
    thiz->bRunEnd |= 0x2;                // flag set to notice, thread operation is finished.
  }_TRY
  CATCH(Exception, exc) {
    err = 99;
  }
  END_TRY
  STACKTRC_RETURN err;
}
//end::threadRoutine2_end[]
static DataTest_ThreadMutexNotify_emC_s data = INIZ_DataTest_ThreadMutexNotify_emC(data, ARRAYLEN_emC(data.buffer));



//tag::testThreadMutexNotify_emC_start[]
void testThreadMutexNotify_emC ( ) {
  STACKTRC_ENTRY("testThreadMutexNotify_emC");
  TEST_TRY("testThreadMutexNotify_emC");
    #ifdef DEF_ShowTime
      TimeAbs_emC timeAbs = {0};
    #endif
    DataTest_ThreadMutexNotify_emC_s* thiz = &data;
    data.bRunEnd = 0x70;
    printf("started\n");
    //--------------------------------------------------------- Create mutex and threads
    int ok = createMutex_OSemC(&thiz->mutexAccess, "mutexAccess");       // first create mutexs
    TEST_TRUE(ok ==0, "createMutexAccess successful");
    ok = createMutex_OSemC(&thiz->mutexNotify, "mutexNotify");       // because the threads are immediately started.
    TEST_TRUE(ok ==0, "createMutexNotify successful");
    ok = createWaitNotifyObj_OSemC("waitNotify", &thiz->waitNotify);
    TEST_TRUE(ok ==0, "createWaitNotify");
    //                                                       //create a threads
    data.hThread[0] = main_Thread_OSemC();
    data.hThread[1] = alloc_Thread_OSemC("Thread1", threadRoutine1_Test_ThreadMutexNtify_emC, &data, 128, 0);
    data.hThread[2] = alloc_Thread_OSemC("thread2", threadRoutine2_Test_ThreadMutexNtify_emC, &data, 128, 0);
    //
    start_Thread_OSemC(data.hThread[1]);
    start_Thread_OSemC(data.hThread[2]);
    //
    printf("threads started\n");
    TimeAbs_emC timeStart; setCurrent_TimeAbs_emC(&timeStart);

    mainThreadRoutine(&data, false);
    mainThreadRoutine(&data, true);
  
    //end::testThreadMutexNotify_emC_start[]
    //tag::testThreadMutexNotify_emC_threadtermination[]
    thiz->bRunEnd = 0x0;                           // the threads should terminate, atomic write access
    thiz->bRunning = false;                        // flag do no more evaluate data 
    lockMutex_OSemC(&thiz->mutexNotify); {          // one thread is waiting. 
      if(thiz->bWait) {                            // notify only if the other thread is really waiting
        notify_OSemC(thiz->waitNotify, &thiz->mutexNotify);      // to end this thread.
      }
    } unlockMutex_OSemC(&thiz->mutexNotify);
    int ctAbort = 100;
    while(thiz->bRunEnd !=3 && --ctAbort >0) {     // wait for termination of both threads
      //wait for ending thread.
      sleep_Time_emC(1);
    }
    CHECK_TRUE(ctAbort >0, "Other Threads are stopped");
    delete_Thread_OSemC(data.hThread[1]);
    delete_Thread_OSemC(data.hThread[2]);
    deleteMutex_OSemC(&thiz->mutexAccess);
    deleteMutex_OSemC(&thiz->mutexNotify);
    deleteWaitNotifyObj_OSemC(thiz->waitNotify);
    //end::testThreadMutexNotify_emC_threadtermination[]
    //tag::testThreadMutexNotify_emC_end[]
    //
    TimeAbs_emC timeEnd; setCurrent_TimeAbs_emC(&timeEnd);
    float timeCalc = diffMicroSec_TimeAbs_emC(&timeEnd, &timeStart) / 1000000.0f;
    TEST_TRUE(thiz->ctLoops1 >1000, "Thread1 has accessed often enough: %d", thiz->ctLoops1);
    TEST_TRUE(thiz->ctLoops2 < 500, "Thread2 get bNext in a short time 1..2 ms: %d", thiz->ctLoops2);
    TEST_TRUE(thiz->ctFirstData == 2, "two times start with first data");
    TEST_TRUE(thiz->errorWaitNext == 0, "MainThread get bNext in a time < 10 ms");
    TEST_TRUE(thiz->errorDiff1 == 0, "Thread1 data are consistent");
    TEST_TRUE(thiz->errorDiff2 == 0, "Thread2 data are consistent");
    TEST_TRUE(thiz->errorDataProgress == 0, "Thread2 data are in exact order in progress");
    TEST_TRUE(thiz->error_bData == 0, "Thread2 has always data on notify");
    TEST_TRUE(thiz->errorTimeoutLockReentrant == 0, "reentrant lock in the same thread is supported.");
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

  TEST_TRY_END;
  STACKTRC_LEAVE;
}
//end::testThreadMutexNotify_emC_end[]


