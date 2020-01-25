#include <applstdef_emC.h>
#include <org/vishia/emC/StateM/evQueue.h>

#include <stdio.h>
#include <org/vishia/emC/Base/String_emC.h>


void show(char const* text) {
  printf("Test: %s ...", text); 
}

void showok(char const* text) {
  printf("%s\n", text); 
}


void check(bool cond, char const* text) {
  if(!cond){
    printf("ERROR: %s\n", text); 
  }
}



void testEvQueue(ThCxt* _thCxt) {
  STACKTRC_TENTRY("testEvQueue");
  show("textEvQueue");
  ObjectJc* oEvQueue = alloc_ObjectJc(sizeof(EvQueue_StateM_vishiaOrg_s), 0, _thCxt);
  EvQueue_StateM_vishiaOrg_s* evQueue = ctor_EvQueue_StateM_vishiaOrg(oEvQueue, 0.001f, 5, 2, _thCxt);

  int id = 1000;

  bool bOk;
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x10);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x11);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x12);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x13);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x14);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x15);
  check(!bOk,"add on full queue not detected");

  Entry_EvQueue_StateM_vishiaOrg_s* ev;
  id = 1000;
  while( (ev = getNext_EvQueue_StateM_vishiaOrg(evQueue)) !=null) {
    check(ev->id == ++id, "getNext faulty");
    quitNext_EvQueue_StateM_vishiaOrg(evQueue, _thCxt);
  }
  showok("ok");
  STACKTRC_LEAVE;

}



#define TEST_INTR1_ADD_EVQUEUE_StateM_emC add_EvQueue_StateM_vishiaOrg(thiz, 2001, 0x20);
#define TEST_INTR2_ADD_EVQUEUE_StateM_emC add_EvQueue_StateM_vishiaOrg(thiz, 2001, 0x20);
#define TEST_INTR3_ADD_EVQUEUE_StateM_emC add_EvQueue_StateM_vishiaOrg(thiz, 2001, 0x20);


void testEvQueueIntr(ThCxt* _thCxt) {
  STACKTRC_TENTRY("testEvQueue");
  show("textEvQueue");
  ObjectJc* oEvQueue = alloc_ObjectJc(sizeof(EvQueue_StateM_vishiaOrg_s), 0, _thCxt);
  EvQueue_StateM_vishiaOrg_s* evQueue = ctor_EvQueue_StateM_vishiaOrg(oEvQueue, 0.001f, 5, 2, _thCxt);

  int id = 1000;

  bool bOk;
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x10);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x11);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x12);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x13);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x14);
  check(bOk,"add failed");
  bOk = add_EvQueue_StateM_vishiaOrg(evQueue, ++id, 0x15);
  check(!bOk,"add on full queue not detected");

  Entry_EvQueue_StateM_vishiaOrg_s* ev;
  id = 1000;
  while( (ev = getNext_EvQueue_StateM_vishiaOrg(evQueue)) !=null) {
    check(ev->id == ++id, "getNext faulty");
    quitNext_EvQueue_StateM_vishiaOrg(evQueue, _thCxt);
  }
  showok("ok");
  STACKTRC_LEAVE;

}



void testEvListener(ThCxt* _thCxt) {
  STACKTRC_TENTRY("testEvListener");
  show("testEvListener");
  ObjectJc* oEvQueue = alloc_ObjectJc(sizeof(EvQueue_StateM_vishiaOrg_s), 0, _thCxt);
  //deep of queue: 5, sizeEvListner: only 2 for test size overflow
  EvQueue_StateM_vishiaOrg_s* evQueue = ctor_EvQueue_StateM_vishiaOrg(oEvQueue, 0.001f, 5, 2, _thCxt);
  //
  EvCreator_StateM_vishiaOrg_s* evCreator[3];
  EvListener_StateM_vishiaOrg_s* evListners[3];
  for(int ixListn = 0; ixListn < ARRAYLEN_emC(evListners) ;++ixListn) {
    ObjectJc* oEvCreator = alloc_ObjectJc(sizeof(EvCreator_StateM_vishiaOrg_s), 0, _thCxt);
    evCreator[ixListn] = ctor_EvCreator_StateM_vishiaOrg(oEvCreator, 0, _thCxt);
    ObjectJc* oEvListn1 = alloc_ObjectJc(sizeof(EvListener_StateM_vishiaOrg_s), 0, _thCxt);
    evListners[ixListn] = ctor_EvListener_StateM_vishiaOrg(oEvListn1, 0.001f, 0, _thCxt);

    //bool bOk = addListener_EvQueue_StateM_vishiaOrg(evQueue, evListners[ixListn], _thCxt);
    bool bOk;
    TRY {
      bOk = init_EvCreator_StateM_vishiaOrg(evCreator[ixListn], ((uint32)-1), evQueue, null);
      bOk = init_EvListener_StateM_vishiaOrg(evListners[ixListn], evQueue, evCreator[ixListn]);
    } _TRY
    CATCH(Exception, exc) {
      bOk = false;
    }
    END_TRY
    if(ixListn <2) {
      check(bOk,"add evListener failed");
    } else {
      check(!bOk,"too many evListener not detected");

    }
  }
  for(int ixListn = 0; ixListn < ARRAYLEN_emC(evListners); ++ixListn) {
    bool isAdded = isAddedToQueue_EvListener_StateM_vishiaOrg(evListners[ixListn]);
    if(ixListn <2) {
      check(isAdded,"add evListener not marked");
    } else {
      check(!isAdded,"add evListener faulty");
    }
  }
  static const int nrTest[] = {2,3};
  static const int resListnCmp[] = { 0,1,0, 1 };
  int resListn[10];
  int ixResListn = 0;
  for(int ixTest=0; ixTest< ARRAYLEN_emC(nrTest); ++ixTest) {
    for(int ixEv=0; ixEv< nrTest[ixTest]; ++ixEv) {
      add_EvQueue_StateM_vishiaOrg(evQueue, 1001 + ixEv, 0x10);
    }
    while (checkForListener_EvQueue_StateM_vishiaOrg(evQueue, _thCxt)) {
      for (int ixListn = 0; ixListn < ARRAYLEN_emC(evListners); ++ixListn) {
        uint32 h = hasEvent_EvListener_StateM_vishiaOrg(evListners[ixListn], null);
        if (h != 0 && h != ((uint32)-1)) {
          resListn[ixResListn] = ixListn; 
          if(++ixResListn >= ARRAYLEN_emC(resListn)){ ixResListn = ARRAYLEN_emC(resListn)-1; }
        }
      }  
    }

  }
  for(int ixListn=0; ixListn < ARRAYLEN_emC(resListnCmp); ++ixListn){
    if(resListnCmp[ixListn] != resListn[ixListn]){
      //check(false, "faulty listener");
    }
  }

  showok("ok");
  STACKTRC_LEAVE;

}



void testStringCompactor(){
  show("StringCompactor");
  char const* text = "Das ist ein Text in US-ASCII ohne Umlaute. !\"$%&/()=?#+*,.;:-_<>~\"\\";
  int zText = strnlen_emC(text, 200);
  int8 dst[100] = {0};
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
  check(bOk, "character faulty");
  showok("ok");
}



void main(char** cmdArgs) {
  STACKTRC_ENTRY("main");
  testEvListener(_thCxt);
  testEvQueue(_thCxt);
  testStringCompactor();
  STACKTRC_LEAVE;
}
