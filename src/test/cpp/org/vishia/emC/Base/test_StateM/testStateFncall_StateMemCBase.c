#include <applstdef_emC.h>
#include <org/vishia/emC/Base/test_StateM/testStateFncall_StateMemCBase.h>

#include <org/vishia/emC/StateM/StateFnCall_StateM_emC.h>

#include <stdio.h>

#ifdef DEF_DEVELOPER_TEST
  #define PRINTMSG(MSG) printf("%s\n", MSG);
#else 
  #define PRINTMSG(MSG)
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
  doEntry_StateFnCall_emC(thiz, stmn); //only std, it is inline.
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


void doEntry_Run(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn) {
  doEntry_StateFnCall_emC(thiz, stmn);
  PRINTMSG("entryRun");
  //doEntry_StateFnCall_emC(&stateRun11, stmn);
  //doEntry_StateFnCall_emC(&stateRun22, stmn);
}

void doExit_Run(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  doExit_StateFnCall_emC(thiz, stmn);
}


void doEntry_Run1(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  doEntry_StateFnCall_emC(thiz, stmn);
  PRINTMSG("entryRun1");
}

void doExit_Run1(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  doExit_StateFnCall_emC(thiz, stmn);
  PRINTMSG("exitRun1");
}


void doEntry_Run2(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  doEntry_StateFnCall_emC(thiz, stmn);
  PRINTMSG("entryRun2");
}

void doExit_Run2(struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn){
  doExit_StateFnCall_emC(thiz, stmn);
}



const StateFnCall_StateM_emC stateInit = { "Init", 0, 0, null, null, null, transInit};

const StateFnCall_StateM_emC stateIdle = { "Idle", 0, 0, null, null, null, transIdleRun};

const StateFnCall_StateM_emC stateRun = { "Run", 0, 2, null, doEntry_Run, doExit_Run, checktransDefault_StateFnCall_emC};

//const StateFnCall_StateM_emC stateRunP1 = { "RunP1", stmRunP1, 0, &stateRun, doEntry_Run1, doExit_Run1, null};

//const StateFnCall_StateM_emC stateRunP2 = { "RunP2", stmRunP2, 0, &stateRun, doEntry_Run1, doExit_Run1, null};

const StateFnCall_StateM_emC stateRun11 = { "Run11", stmRunP1, 0, null, doEntry_Run1, doExit_Run1, transRun11};

const StateFnCall_StateM_emC stateRun12 = { "Run12", stmRunP1, 0, null, doEntry_Run2, doExit_Run2, checktransDefault_StateFnCall_emC};

const StateFnCall_StateM_emC stateRun21 = { "Run21", stmRunP2, 0, null, doEntry_Run1, doExit_Run1, transRun21};

const StateFnCall_StateM_emC stateRun22 = { "Run22", stmRunP2, 0, null, doEntry_Run2, doExit_Run2, transRun22};



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
    doEntry_Run(&stateRun, stmn);
    doEntry_Run1(&stateRun11, stmn);
    doEntry_Run1(&stateRun21, stmn);
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
    doExit_Run(&stateRun, stmn);
    doEntry_Idle(&stateIdle, stmn);
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
    doExit_Run(&stateRun11, stmn);
    doEntry_Idle(&stateRun12, stmn);
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
    doExit_Run(&stateRun21, stmn);
    doEntry_Idle(&stateRun22, stmn);
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
    doExit_Run(&stateRun22, stmn);
    doEntry_Idle(&stateIdle, stmn);
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


  MyStateM stmn = {0};

  init_StateFnCall_StateM_emC(&stmn.statesTop, &stateInit); 

  for(int ix = 0; ix < ARRAYLEN_emC(evIdents); ++ix) {

    step_StateFnCall_StateM_emC(&stmn.statesTop, evIdents[ix], null);
  
  }




}

