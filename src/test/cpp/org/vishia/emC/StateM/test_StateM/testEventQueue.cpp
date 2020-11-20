#include <org/vishia/emC/StateM/test_StateM/testEventQueue.h>
#include <emC/Test/testAssert.h>
#include <emC/Base/Object_emC.h>


//Define macros called in the add_EvQueue_emC(...) for test condition. 
void testEvQueueInterrupting(struct EvQueue_emC_T* thiz);
#define TEST_INTR1_ADD_EVQUEUE_StateM_emC testEvQueueInterrupting(thiz);
#define TEST_INTR2_ADD_EVQUEUE_StateM_emC //testEvQueueInterrupting(thiz);




#include <emC/Base/EventQu_emC.h>

#include <stdio.h>
#include <emC/Base/String_emC.h>




/**Set it >0 to force interrupting of add_EvQueue_emC(...)*/
static int nIntr_testEvQueueInterrupting = 0;
static int nId_testEvQueueInterrupting = 0;




//This special test function is used to interupt the add_EvQueue_emC(...) 
//to TEST_TRUEmsg the consistence of data. It is adequate an interrupting access. 
//The macro TEST_INTR1_ADD_EVQUEUE_StateM_emC inside the add_EvQueue_emC(...)
//supports this test. 
//The static variables  
void testEvQueueInterrupting(struct EvQueue_emC_T* thiz) {
  if(nIntr_testEvQueueInterrupting > 0) { //recursively only 2 times
    nIntr_testEvQueueInterrupting -=1;
    //TODO add_EvQueue_emC(thiz, nId_testEvQueueInterrupting++, 0x42); //add 
  }
}



void testEvQueueSimpleOneThread() {
  STACKTRC_ENTRY("testEvQueue");
  TEST_START("testEvQueueSimpleOneThread");
  
  EvQueue_emC_s evqu = INIZ_EvQueue_emC(evqu, refl_EvQueue_emC, 0);
  ctor_EvQueue_emC(&evqu.base.obj, 0.001f, 5);  //size 5,                 //the event queue itself

  EventData_emC_s* evdataArray[15];

  for(int ix = 0; ix < ARRAYLEN_emC(evdataArray); ++ix) {
    ObjectJc* odata = ALLOC_ObjectJc(sizeof(EventData_emC_s), refl_EventData_emC, 0);
    EventData_emC_s* evdata = ctor_EventData_emC(odata, "");
    init_EventData_emC(evdata, null, ix, &evqu, null);
    evdataArray[ix] = evdata;
  }

  //This variable are for status check, should be used as pointer arguments.
  int16 nrofEvents, ctEvents;

  static uint32 evIds[] = { 1, 2, 5, 8};
  int ixEvId = 0;

  bool bOk;
  //Send 4 events to valid listener, 5 is the size of the queue, only 4 can be added.
  for(int ixEvId = 0; ixEvId <4; ++ixEvId) {
    bOk = add_EvQueue_emC(&evqu, evdataArray[ixEvId]);
    TEST_TRUE(bOk,"add failed");
  }

#if 0
  //
  //The next event cannot store in the queue, hence it returns bOk = 0.
  //The event is lost.
  bOk = add_EvQueue_emC(evQueue, evIds[ixEvId++], 0x15);
  TEST_TRUE(!bOk, "add on full queue not detected");

  nrofEvents = info_EvQueue_emC(evQueue, null);
  TEST_TRUE(nrofEvents == 4, "faulty event count");

  //get all stored events from queue (usual done in another thread).
  //TEST_TRUEmsg its correctness.
  Entry_EvQueue_emC_s* ev;
  //evIdent = 1000;
  ixEvId = 0;  //TEST_TRUEmsg all
  while( (ev = getNext_EvQueue_emC(evQueue)) !=null) {
    TEST_TRUE(ev->evIdent == evIds[ixEvId++], "getNext faulty");
    //here the event reference can be processed (references into the queue yet now).
    quitNext_EvQueue_emC(evQueue, _thCxt);
  }
  TEST_TRUE(ixEvId == 4, "ixEvId ==4, read 4 events");
  status__EvQueue_emC(evQueue, &nrofEvents, &ctEvents);
  TEST_TRUE(nrofEvents == 0, "queue is not emtpy");
  //
  //now add a faulty evId. Note: The evId should be in range 0..<maxNrListener, 0..5
  //In a throw-using system this is detect as an internal fatal software error, it is thrown.
  //In a non-throw-using system the add...(...) returns false. Both is ok.
  //Note: The adaption of any desired identification on the event to this idListener 
  //should be done in an algorithm outside. this adaption may need too much calc time for fast calculations. 
  bool bAddFails = false;
  TRY {
    int const faultyEvId = maxNrListener+1;
    bOk = add_EvQueue_emC(evQueue, faultyEvId, 0x15);
    //In a throwing system this line is never reached. In a simple C system the routine returns false.
    bAddFails = !bOk; //bOk should be false.
  }_TRY
    CATCH(Exception, exc) {
    bAddFails = true;
  }
  END_TRY;
  TEST_TRUE(bAddFails, "faulty evId not detected");
#endif //0
  dtor_EvQueue_emC(&evqu);
  TEST_END;

  STACKTRC_LEAVE;

}




#if 0

void testEvQueueAddInterrupted() {
  STACKTRC_ENTRY("testEvQueueAddInterrupted");
  TEST_START("testEvQueueAddInterrupted");
  ObjectJc* oEvQueue = ALLOC_ObjectJc(sizeof(EvQueue_emC_s), refl_EvQueue_emC, 0);
  int const sizeQueue = 6;  //a less queue
  int const maxNrListener = 5;  //some more different event idents (=^listeners)
  EvQueue_emC_s* evQueue = ctor_EvQueue_emC(oEvQueue, 0.001f, sizeQueue, maxNrListener+1, _thCxt);

  //int evIdent = 1;

  //This variable are for status check, should be used as pointer arguments.
  int16 nrofEvents, ctEvents;

  static uint32 evIdsWr[] = { 1, 2, 5};
  static uint32 evIdsRd[] = { 4, 3, 1, 2, 5}; //firstly the interrupted ids are in the queue.
  int ixEvId = 0;

  bool bOk;
  //Send 3 events to valid listener.
  nIntr_testEvQueueInterrupting = 2; //but 2 events are added in interruption, summe is 5 events.
  nId_testEvQueueInterrupting = 3;   //add id=3 and id=4 in interrupt. 
  for(int ixEvId = 0; ixEvId <3; ++ixEvId) {
    bOk = add_EvQueue_emC(evQueue, evIdsWr[ixEvId], 0x10);
    TEST_TRUE(bOk, "add failed");
  }
  //
  //The next event cannot store in the queue, hence it returns bOk = 0.
  //The event is lost.
  bOk = add_EvQueue_emC(evQueue, 0, 0x15);
  TEST_TRUE(!bOk, "add on full queue not detected");

  nrofEvents = info_EvQueue_emC(evQueue, null);
  TEST_TRUE(nrofEvents == 5, "faulty event count");

  //get all stored events from queue (usual done in another thread).
  //TEST_TRUEmsg its correctness.
  Entry_EvQueue_emC_s* ev;
  //evIdent = 1000;
  ixEvId = 0;  //TEST_TRUEmsg all
  while( (ev = getNext_EvQueue_emC(evQueue)) !=null) {
    TEST_TRUE(ev->evIdent == evIdsRd[ixEvId++], "getNext faulty");
    //here the event reference can be processed (references into the queue yet now).
    quitNext_EvQueue_emC(evQueue, _thCxt);
  }
  TEST_TRUE(ixEvId == 5, "ixEvId !=5, read 5 events");
  nrofEvents = info_EvQueue_emC(evQueue, &ctEvents);
  TEST_TRUE(nrofEvents == 0, "queue is not emtpy");
  TEST_TRUE(ctEvents == 5, "faulty count");
  TEST_END;
}









void testAddSomeListener(ThCxt* _thCxt) {
  STACKTRC_TENTRY("testEvListener");
  STACKTRC_LEAVE;
}




void testEvListener(ThCxt* _thCxt) {
  STACKTRC_TENTRY("testEvListener");
  TEST_START("testEvListener");
  ObjectJc* oEvQueue = ALLOC_ObjectJc(sizeof(EvQueue_emC_s), refl_EvQueue_emC, 0);
  //deep of queue: 5, sizeEvListner: only 2 for test size overflow
  EvQueue_emC_s* evQueue = ctor_EvQueue_emC(oEvQueue, 0.001f, 5, 10, _thCxt);
  //
  EvInstance_emC_s* evInstances[3];
  for(uint ixListn = 0; ixListn < ARRAYLEN_emC(evInstances) ;++ixListn) {
    ObjectJc* oEvCreator = ALLOC_ObjectJc(sizeof(EvInstance_emC_s), refl_EvInstance_emC, 0);
    evInstances[ixListn] = ctor_EvInstance_emC(oEvCreator, 0, _thCxt);

    //bool bOk = addListener_EvQueue_emC(evQueue, evListners[ixListn], _thCxt);
    bool bOk;
    TRY {
      bOk = init_EvInstance_emC(evInstances[ixListn], ((uint32)-1), 0, evQueue, null);
    } _TRY
      CATCH(Exception, exc) {
      bOk = false;
    }
    END_TRY
      if(ixListn <2) {
        TEST_TRUE(bOk,"add evListener failed");
      } else {
        TEST_TRUE(!bOk,"too many evListener not detected");

      }
  }
  for(uint ixListn = 0; ixListn < ARRAYLEN_emC(evInstances); ++ixListn) {
    bool isAdded = isAddedToQueue_EvInstance_emC(evInstances[ixListn]);
    if(ixListn <2) {
      TEST_TRUE(isAdded,"add evListener not marked");
    } else {
      TEST_TRUE(!isAdded,"add evListener faulty");
    }
  }
  static const uint nrTest[] = {2,3};
  static const uint resListnCmp[] = { 0,1,0, 1 };
  uint resListn[10];
  uint ixResListn = 0;
  for(uint ixTest=0; ixTest< ARRAYLEN_emC(nrTest); ++ixTest) {
    for(uint ixEv=0; ixEv< nrTest[ixTest]; ++ixEv) {
      add_EvQueue_emC(evQueue, 1 + ixEv, 0x10);
    }
    while (checkForListener_EvQueue_emC(evQueue, _thCxt)) {
      for (uint ixListn = 0; ixListn < ARRAYLEN_emC(evInstances); ++ixListn) {
        uint32 h = hasEvent_EvInstance_emC(evInstances[ixListn], null, null);
        if (h != 0 && h != ((uint32)-1)) {
          resListn[ixResListn] = ixListn; 
          if(++ixResListn >= ARRAYLEN_emC(resListn)){ ixResListn = ARRAYLEN_emC(resListn)-1; }
        }
      }  
    }

  }
  for(uint ixListn=0; ixListn < ARRAYLEN_emC(resListnCmp); ++ixListn){
    if(resListnCmp[ixListn] != resListn[ixListn]){
      //TEST_TRUEmsg(false, "faulty listener");
    }
  }

  STACKTRC_LEAVE;

}
#endif //0

#if 0
void testStringCompactor(){
  TEST_START("StringCompactor");
  char const* text = "Das ist ein Text in US-ASCII ohne Umlaute. !\"$%&/()=?#+*,.;:-_<>~\"\\";
  int zText = strnlen_emC(text, 200);
  uint8 dst[100] = {0};
  int zBytes = encode_StringCompactor_emC(dst, 100, text, strnlen_emC(text, 1000));
  char txt2[100];
  int nChars = decode_StringCompactor_emC(txt2, 100, dst, zBytes);
  bool bOk = false;
  if(nChars == zText){
    bOk = true;
    for(int ix=0; ix < nChars; ++ix){
      if(text[ix] != txt2[ix]) {
        bOk = false;
        break;
      }
    }
  }
  TEST_TRUE(bOk, "character faulty");
  TEST_END;
}
#endif