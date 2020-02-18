#include <org/vishia/emC/Base/test_StateM/testEventQueue.h>
#include <org/vishia/emC/Test/testAssert.h>


//Define macros called in the add_EvQueue_StateM_vishiaOrg(...) for test condition. 
void testEvQueueInterrupting(struct EvQueue_StateM_vishiaOrg_T* thiz);
#define TEST_INTR1_ADD_EVQUEUE_StateM_emC testEvQueueInterrupting(thiz);
#define TEST_INTR2_ADD_EVQUEUE_StateM_emC //testEvQueueInterrupting(thiz);




#include <org/vishia/emC/StateM/evQueue.h>

#include <stdio.h>
#include <org/vishia/emC/Base/String_emC.h>




/**Set it >0 to force interrupting of add_EvQueue_StateM_vishiaOrg(...)*/
static int nIntr_testEvQueueInterrupting = 0;
static int nId_testEvQueueInterrupting = 0;




//This special test function is used to interupt the add_EvQueue_StateM_vishiaOrg(...) 
//to EXPECT_TRUEmsg the consistence of data. It is adequate an interrupting access. 
//The macro TEST_INTR1_ADD_EVQUEUE_StateM_emC inside the add_EvQueue_StateM_vishiaOrg(...)
//supports this test. 
//The static variables  
void testEvQueueInterrupting(struct EvQueue_StateM_vishiaOrg_T* thiz) {
  if(nIntr_testEvQueueInterrupting > 0) { //recursively only 2 times
    nIntr_testEvQueueInterrupting -=1;
    add_EvQueue_StateM_vishiaOrg(thiz, nId_testEvQueueInterrupting++, 0x42); //add 
  }
}



void testEvQueueSimpleOneThread() {
  STACKTRC_ENTRY("testEvQueue");
  TEST("testEvQueueSimpleOneThread");
  ObjectJc* oEvQueue = alloc_ObjectJc(sizeof(EvQueue_StateM_vishiaOrg_s), 0, _thCxt);
  int const sizeQueue = 5;  //a less queue
  int const maxNrListener = 5;  //some more different event idents (=^listeners)
  EvQueue_StateM_vishiaOrg_s* evQueue = ctor_EvQueue_StateM_vishiaOrg(oEvQueue, 0.001f, sizeQueue, maxNrListener+1, _thCxt);

  int evIdent = 1;

  //This variable are for status check, should be used as pointer arguments.
  int16 nrofEvents, ctEvents;

  static int evIds[] = { 1, 2, 5, 1, 2, 7, 1};
  int ixEvId = 0;

  bool bOk;
  //Send 4 events to valid listener, 5 is the size of the queue, only 4 can be added.
  for(int ixEvId = 0; ixEvId <4; ++ixEvId) {
    bOk = add_EvQueue_StateM_vishiaOrg(evQueue, evIds[ixEvId], 0x10);
    EXPECT_TRUE(bOk) <<"add failed";
  }
  //
  //The next event cannot store in the queue, hence it returns bOk = 0.
  //The event is lost.
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, evIds[ixEvId++], 0x15);
  EXPECT_FALSE(bOk) << "add on full queue not detected";

  nrofEvents = info_EvQueue_StateM_vishiaOrg(evQueue, null);
  EXPECT_TRUE(nrofEvents == 4) << "faulty event count";

  //get all stored events from queue (usual done in another thread).
  //EXPECT_TRUEmsg its correctness.
  Entry_EvQueue_StateM_vishiaOrg_s* ev;
  evIdent = 1000;
  ixEvId = 0;  //EXPECT_TRUEmsg all
  while( (ev = getNext_EvQueue_StateM_vishiaOrg(evQueue)) !=null) {
    EXPECT_TRUE(ev->evIdent == evIds[ixEvId++]) << "getNext faulty";
    //here the event reference can be processed (references into the queue yet now).
    quitNext_EvQueue_StateM_vishiaOrg(evQueue, _thCxt);
  }
  EXPECT_TRUE(ixEvId == 4) << "ixEvId ==4, read 4 events";
  status__EvQueue_StateM_vishiaOrg(evQueue, &nrofEvents, &ctEvents);
  EXPECT_TRUE(nrofEvents == 0) << "queue is not emtpy";
  //
  //now add a faulty evId. Note: The evId should be in range 0..<maxNrListener, 0..5
  //In a throw-using system this is detect as an internal fatal software error, it is thrown.
  //In a non-throw-using system the add...(...) returns false. Both is ok.
  //Note: The adaption of any desired identification on the event to this idListener 
  //should be done in an algorithm outside. this adaption may need too much calc time for fast calculations. 
  bool bAddFails = false;
  TRY {
    int const faultyEvId = maxNrListener+1;
    bOk = add_EvQueue_StateM_vishiaOrg(evQueue, faultyEvId, 0x15);
    //In a throwing system this line is never reached. In a simple C system the routine returns false.
    bAddFails = !bOk; //bOk should be false.
  }_TRY
    CATCH(Exception, exc) {
    bAddFails = true;
  }
  END_TRY;
  EXPECT_TRUE(bAddFails) << "faulty evId not detected";


  STACKTRC_LEAVE;

}






void testEvQueueAddInterrupted() {
  STACKTRC_ENTRY("testEvQueueAddInterrupted");
  TEST("testEvQueueAddInterrupted");
  ObjectJc* oEvQueue = alloc_ObjectJc(sizeof(EvQueue_StateM_vishiaOrg_s), 0, _thCxt);
  int const sizeQueue = 6;  //a less queue
  int const maxNrListener = 5;  //some more different event idents (=^listeners)
  EvQueue_StateM_vishiaOrg_s* evQueue = ctor_EvQueue_StateM_vishiaOrg(oEvQueue, 0.001f, sizeQueue, maxNrListener+1, _thCxt);

  int evIdent = 1;

  //This variable are for status check, should be used as pointer arguments.
  int16 nrofEvents, ctEvents;

  static int evIdsWr[] = { 1, 2, 5};
  static int evIdsRd[] = { 4, 3, 1, 2, 5}; //firstly the interrupted ids are in the queue.
  int ixEvId = 0;

  bool bOk;
  //Send 3 events to valid listener.
  nIntr_testEvQueueInterrupting = 2; //but 2 events are added in interruption, summe is 5 events.
  nId_testEvQueueInterrupting = 3;   //add id=3 and id=4 in interrupt. 
  for(int ixEvId = 0; ixEvId <3; ++ixEvId) {
    bOk = add_EvQueue_StateM_vishiaOrg(evQueue, evIdsWr[ixEvId], 0x10);
    EXPECT_TRUE(bOk) << "add failed";
  }
  //
  //The next event cannot store in the queue, hence it returns bOk = 0.
  //The event is lost.
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, 0, 0x15);
  EXPECT_FALSE(bOk) << "add on full queue not detected";

  nrofEvents = info_EvQueue_StateM_vishiaOrg(evQueue, null);
  EXPECT_TRUE(nrofEvents == 5) << "faulty event count";

  //get all stored events from queue (usual done in another thread).
  //EXPECT_TRUEmsg its correctness.
  Entry_EvQueue_StateM_vishiaOrg_s* ev;
  evIdent = 1000;
  ixEvId = 0;  //EXPECT_TRUEmsg all
  while( (ev = getNext_EvQueue_StateM_vishiaOrg(evQueue)) !=null) {
    EXPECT_TRUE(ev->evIdent == evIdsRd[ixEvId++]) << "getNext faulty";
    //here the event reference can be processed (references into the queue yet now).
    quitNext_EvQueue_StateM_vishiaOrg(evQueue, _thCxt);
  }
  EXPECT_TRUE(ixEvId == 5) << "ixEvId !=5, read 5 events";
  nrofEvents = info_EvQueue_StateM_vishiaOrg(evQueue, &ctEvents);
  EXPECT_TRUE(nrofEvents == 0) << "queue is not emtpy";
  EXPECT_TRUE(ctEvents == 5) << "faulty count";
}









void testAddSomeListener(ThCxt* _thCxt) {
  STACKTRC_TENTRY("testEvListener");
}




void testEvListener(ThCxt* _thCxt) {
  STACKTRC_TENTRY("testEvListener");
  TEST("testEvListener");
  ObjectJc* oEvQueue = alloc_ObjectJc(sizeof(EvQueue_StateM_vishiaOrg_s), 0, _thCxt);
  //deep of queue: 5, sizeEvListner: only 2 for test size overflow
  EvQueue_StateM_vishiaOrg_s* evQueue = ctor_EvQueue_StateM_vishiaOrg(oEvQueue, 0.001f, 5, 10, _thCxt);
  //
  EvInstance_StateM_vishiaOrg_s* evInstances[3];
  for(int ixListn = 0; ixListn < ARRAYLEN_emC(evInstances) ;++ixListn) {
    ObjectJc* oEvCreator = alloc_ObjectJc(sizeof(EvInstance_StateM_vishiaOrg_s), 0, _thCxt);
    evInstances[ixListn] = ctor_EvInstance_StateM_vishiaOrg(oEvCreator, 0, _thCxt);

    //bool bOk = addListener_EvQueue_StateM_vishiaOrg(evQueue, evListners[ixListn], _thCxt);
    bool bOk;
    TRY {
      bOk = init_EvInstance_StateM_vishiaOrg(evInstances[ixListn], ((uint32)-1), 0, evQueue, null);
    } _TRY
      CATCH(Exception, exc) {
      bOk = false;
    }
    END_TRY
      if(ixListn <2) {
        EXPECT_TRUEmsg(bOk,"add evListener failed");
      } else {
        EXPECT_TRUEmsg(!bOk,"too many evListener not detected");

      }
  }
  for(int ixListn = 0; ixListn < ARRAYLEN_emC(evInstances); ++ixListn) {
    bool isAdded = isAddedToQueue_EvInstance_StateM_vishiaOrg(evInstances[ixListn]);
    if(ixListn <2) {
      EXPECT_TRUEmsg(isAdded,"add evListener not marked");
    } else {
      EXPECT_TRUEmsg(!isAdded,"add evListener faulty");
    }
  }
  static const int nrTest[] = {2,3};
  static const int resListnCmp[] = { 0,1,0, 1 };
  int resListn[10];
  int ixResListn = 0;
  for(int ixTest=0; ixTest< ARRAYLEN_emC(nrTest); ++ixTest) {
    for(int ixEv=0; ixEv< nrTest[ixTest]; ++ixEv) {
      add_EvQueue_StateM_vishiaOrg(evQueue, 1 + ixEv, 0x10);
    }
    while (checkForListener_EvQueue_StateM_vishiaOrg(evQueue, _thCxt)) {
      for (int ixListn = 0; ixListn < ARRAYLEN_emC(evInstances); ++ixListn) {
        uint32 h = hasEvent_EvInstance_StateM_vishiaOrg(evInstances[ixListn], null, null);
        if (h != 0 && h != ((uint32)-1)) {
          resListn[ixResListn] = ixListn; 
          if(++ixResListn >= ARRAYLEN_emC(resListn)){ ixResListn = ARRAYLEN_emC(resListn)-1; }
        }
      }  
    }

  }
  for(int ixListn=0; ixListn < ARRAYLEN_emC(resListnCmp); ++ixListn){
    if(resListnCmp[ixListn] != resListn[ixListn]){
      //EXPECT_TRUEmsg(false, "faulty listener");
    }
  }

  STACKTRC_LEAVE;

}



void testStringCompactor(){
  TEST("StringCompactor");
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
  EXPECT_TRUE(bOk) << "character faulty";
}
