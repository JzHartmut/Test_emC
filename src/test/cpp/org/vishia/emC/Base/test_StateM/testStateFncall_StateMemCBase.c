#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_StateM/testStateFncall_StateMemCBase.h>

#include <org/vishia/emC/StateM/StateFnCall_StateM_emC.h>

#include <stdio.h>

#ifdef DEF_DEVELOPER_TEST
  #define PRINTMSG(MSG) printf("%s\n", MSG);
#else 
  #define PRINTMSG(MSG)
#endif

#ifdef DONOTUSE_REFLECTION_emC
  ClassJc const reflection_MyStateM = INIZ_ClassJc(reflection_MyStateM, "MyStateM");
#else
  ClassJc const reflection_MyStateM = INIZ_ClassJc(reflection_MyStateM, "MyStateM");
#endif

typedef struct MyStateM_T {

  StateMnTopFnCall_State_emC statesTop;

  //#define stmRun 1
  //StateMachineFnCall_StateM_emC statesRun; //:for the composite state Run, the nested ones

  #define stmRunP1 1
  StateMachineFnCall_StateM_emC statesRunParallel1; //:for the composite state Run, the nested ones
  #define stmRunP2 2
  StateMachineFnCall_StateM_emC statesRunParallel2; //:for the composite state Run, the nested ones

} MyStateM;


void doEntry_Idle(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn ) {
  if(ASSERTs_emC(instanceof_ObjectJc(&stmn->base.obj, &reflection_MyStateM), "faulty instance", 0, 0)) {
    MyStateM* stmn1 = HARD_CAST(MyStateM*,stmn);
    doEntry_StateFnCall_emC(thiz, &stmn1->statesTop.substmn[0]); //only std, it is inline.
  }
}

void doExit_Idle(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn ) {
  doExit_StateFnCall_emC(thiz, stmn); //only std, it is inline.
}

//StateFnCall_StateM_emC_T const* transIdleRun(int32 idEvent, ObjectJc* dataEvent);
//StateFnCall_StateM_emC_T const* transInit(int32 idEvent, ObjectJc* dataEvent);

extern CheckTrans_StateFnCall_StateM_emC transIdleRun;

extern CheckTrans_StateFnCall_StateM_emC transInit;

extern CheckTrans_StateFnCall_StateM_emC transRun11;
extern CheckTrans_StateFnCall_StateM_emC transRun21;
extern CheckTrans_StateFnCall_StateM_emC transRun22;

extern DoEntry_StateFnCall_StateM_emC doEntryIdle;
extern DoEntry_StateFnCall_StateM_emC doEntryRun;
extern DoEntry_StateFnCall_StateM_emC doEntryRun11;
extern DoEntry_StateFnCall_StateM_emC doEntryRun12;
extern DoEntry_StateFnCall_StateM_emC doEntryRun21;
extern DoEntry_StateFnCall_StateM_emC doEntryRun22;

extern DoExit_StateFnCall_StateM_emC doExitIdle;
extern DoExit_StateFnCall_StateM_emC doExitRun;
extern DoExit_StateFnCall_StateM_emC doExitRun11;
extern DoExit_StateFnCall_StateM_emC doExitRun12;
extern DoExit_StateFnCall_StateM_emC doExitRun21;
extern DoExit_StateFnCall_StateM_emC doExitRun22;


/*@ All states @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

const StateFnCall_StateM_emC stateInit = { "Init", 0, 0, null, null, null, transInit};

const StateFnCall_StateM_emC stateIdle = { "Idle", 0, 0, null, null, null, transIdleRun};

const StateFnCall_StateM_emC stateRun = { "Run", 0, 2, null, doEntryRun, doExitRun, checktransDefault_StateFnCall_emC};

//const StateFnCall_StateM_emC stateRunP1 = { "RunP1", stmRunP1, 0, &stateRun, doEntry_Run1, doExit_Run1, null};

//const StateFnCall_StateM_emC stateRunP2 = { "RunP2", stmRunP2, 0, &stateRun, doEntry_Run1, doExit_Run1, null};

const StateFnCall_StateM_emC stateRun11 = { "Run11", stmRunP1, 0, null, doEntryRun11, null, transRun11};

const StateFnCall_StateM_emC stateRun12 = { "Run12", stmRunP1, 0, null, doEntryRun12, doExitRun21, checktransDefault_StateFnCall_emC};

const StateFnCall_StateM_emC stateRun21 = { "Run21", stmRunP2, 0, null, doEntryRun21, null, transRun21};

const StateFnCall_StateM_emC stateRun22 = { "Run22", stmRunP2, 0, null, doEntryRun22, null, transRun22};


/*@ Implementation of all entry, exit, trans @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


void doEntryIdle(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn) {
  if(ASSERTs_emC(instanceof_ObjectJc(&stmn->base.obj, &reflection_MyStateM), "faulty instance", 0, 0)) {
    MyStateM* stmn1 = HARD_CAST(MyStateM*,stmn);
    doEntry_StateFnCall_emC(&stateIdle, &stmn1->statesTop.substmn[0]);
    PRINTMSG("entryIdle");
    //doEntry_StateFnCall_emC(&stateRun11, stmn);
    //doEntry_StateFnCall_emC(&stateRun22, stmn);
  }
}

void doEntryRun(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn) {
  if(ASSERTs_emC(instanceof_ObjectJc(&stmn->base.obj, &reflection_MyStateM), "faulty instance", 0, 0)) {
    MyStateM* stmn1 = HARD_CAST(MyStateM*,stmn);
    doEntry_StateFnCall_emC(&stateRun, &stmn1->statesTop.substmn[0]);
    PRINTMSG("entryRun");
    //doEntry_StateFnCall_emC(&stateRun11, stmn);
    //doEntry_StateFnCall_emC(&stateRun22, stmn);
  }
}

void doExitRun(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  doExit_StateFnCall_emC(thiz, stmn);
}

void doExitRun21(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  doExit_StateFnCall_emC(thiz, stmn);
}


void doEntryRun11(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  ASSERTs_emC(instanceof_ObjectJc(&stmn->base.obj, &reflection_MyStateM), "faulty instance", 0, 0);
  MyStateM* stmn1 = HARD_CAST(MyStateM*,stmn);
  doEntry_StateFnCall_emC(&stateRun11, &stmn1->statesRunParallel1);
  PRINTMSG("entryRun11");
}

void doEntryRun12(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  ASSERTs_emC(instanceof_ObjectJc(&stmn->base.obj, &reflection_MyStateM), "faulty instance", 0, 0);
  MyStateM* stmn1 = HARD_CAST(MyStateM*,stmn);
  doEntry_StateFnCall_emC(&stateRun12, &stmn1->statesRunParallel1);
  PRINTMSG("entryRun11");
}

void doEntryRun21(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  ASSERTs_emC(instanceof_ObjectJc(&stmn->base.obj, &reflection_MyStateM), "faulty instance", 0, 0);
  MyStateM* stmn1 = HARD_CAST(MyStateM*,stmn);
  doEntry_StateFnCall_emC(&stateRun21, &stmn1->statesRunParallel2);
  PRINTMSG("entryRun11");
}

void doEntryRun22(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  ASSERTs_emC(instanceof_ObjectJc(&stmn->base.obj, &reflection_MyStateM), "faulty instance", 0, 0);
  MyStateM* stmn1 = HARD_CAST(MyStateM*,stmn);
  doEntry_StateFnCall_emC(&stateRun22, &stmn1->statesRunParallel2);
  PRINTMSG("entryRun11");
}

void doExit_Run1(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  doExit_StateFnCall_emC(thiz, stmn);
  PRINTMSG("exitRun1");
}






static StateFnCall_StateM_emC const* transInit(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32 idEvent, ObjectJc* dataEvent) {
  doExit_StateFnCall_emC(&stateInit, stmn);
  doEntry_Idle(&stateIdle, stmn);
  return &stateIdle;
}


///Implementation of the transition between Idle and Run1 in Run,
//It checks the idEvent==1
static StateFnCall_StateM_emC const* transIdleRun(
    struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
    int32 idEvent, ObjectJc* dataEvent
  ) {
  if(idEvent ==2) {
    doExit_Idle(&stateIdle, stmn);
    doEntryRun(&stateRun, stmn);
    doEntryRun11(&stateRun11, stmn);
    doEntryRun21(&stateRun21, stmn);
    return &stateRun;
  }
  else {
    return null;
  }
}



static StateFnCall_StateM_emC const* transRunIdle(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32 idEvent, ObjectJc* dataEvent
) {
  if(idEvent ==3) {
    doExitRun(&stateRun, stmn);
    doEntryIdle(&stateIdle, stmn);
    return &stateIdle;
  }
  else {
    return null;
  }
}


static StateFnCall_StateM_emC const* transRun11(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32 idEvent, ObjectJc* dataEvent
) {
  if(idEvent ==11) {
    doExitRun(&stateRun11, stmn);
    doEntryIdle(&stateRun12, stmn);
    return &stateRun12;
  }
  else {
    return null;
  }
}


static StateFnCall_StateM_emC const* transRun21(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32 idEvent, ObjectJc* dataEvent
) {
  if(idEvent ==11) {
    doExitRun(&stateRun21, stmn);
    doEntryIdle(&stateRun22, stmn);
    return &stateRun22;
  }
  else {
    return null;
  }
}


//Join-Transition
static StateFnCall_StateM_emC const* transRun22(
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32 idEvent, ObjectJc* dataEvent
) {
  if(idEvent ==21) {
    doExitRun(&stateRun22, stmn);
    doEntryIdle(&stateIdle, stmn);
    return &stateIdle;
  }
  else {
    return null;
  }
}




int evIdents[] = { -1 //note: first call from init should be done before active event processing
  , 2     //Idle->Run11, Run12
  , 1     //not used
  , 11    // ->Run12, Run22
  , 21    // ->Join to Idle
  };


void testStateFncall_StateMemCBase(){

  MyStateM stmn = { {{ INIZ_objReflId_ObjectJc(stmn, &reflection_MyStateM, 0)}} ,0};

  init_StateFnCall_StateM_emC(&stmn.statesTop, &stateInit); 
  int ix;
  for(ix = 0; ix < ARRAYLEN_emC(evIdents); ++ix) {

    step_StateFnCall_StateM_emC(&stmn.statesTop, evIdents[ix], null);
  
  }




}

